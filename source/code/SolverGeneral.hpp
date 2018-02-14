/*
 * SolverGeneral.hpp
 *
 * Created on: Jun 18, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_SOLVERGENERAL_HPP_
#define CALLCOSTCALCULATOR_CODE_SOLVERGENERAL_HPP_

#include <memory>

#include "common.hpp"
#include "SolverStateInterface.hpp"

namespace CallCostCalculator
{
class StateBase;

class StateStart;
class StateWeekendCall;
class StateNormalCall;
class StateFreeMinutes;
class StateEnd;

class SolverGeneral;

class StateBase : public SolverStateInterface
{
protected:
	SolverGeneral& m_solver;
public:
	StateBase(SolverGeneral& solver);
};

class StateStart : public StateBase
{
public:
	StateStart(SolverGeneral& solver);
	virtual void handle(TEvent event);
};

class StateWeekendCall : public StateBase
{
public:
	StateWeekendCall(SolverGeneral& solver);
	virtual void handle(TEvent event);
};

class StateNormalCall : public StateBase
{
public:
	StateNormalCall(SolverGeneral& solver);
	virtual void handle(TEvent event);
};

class StateFreeMinutes : public StateBase
{
public:
	StateFreeMinutes(SolverGeneral& solver);
	virtual void handle(TEvent event);
};

class StateEnd : public StateBase
{
public:
	StateEnd(SolverGeneral& solver);
	virtual void handle(TEvent event);
};

class SolverGeneral
{
	TEventsQueueAuto m_eventsQueue;
	int m_freeWeekendTalkingTimeSeconds;
	int m_freeTalkingTimeInOperatorNetSeconds;

	std::auto_ptr<SolverStateInterface> m_state;
	time_t m_lastTimeStamp;
	int m_result;
	time_t m_callStartTimestamp;

	//this is used if FreeMinutes state is interrupted
	//and no all free minutes consumed, so there are more free minutes to consume
	bool m_ConsumeFreeMinutesEndEvent;
	//this is because transitions between FreeMinutesState <-> WeekendCall

	friend class StateStart;
	friend class StateWeekendCall;
	friend class StateNormalCall;
	friend class StateFreeMinutes;
	friend class StateEnd;

protected:

	void injectEvent(TEventID eventID, time_t timestamp);

public:
	SolverGeneral(
			TEventsQueueAuto eventsQueue,
			int freeWeekendTalkingTimeLeftMinutesP,
			int freeTalkingTimeInOperatorLeftMinutesP);

	void solve();

	int getResult() const;
};

}

#endif /* CALLCOSTCALCULATOR_CODE_SOLVERGENERAL_HPP_ */
