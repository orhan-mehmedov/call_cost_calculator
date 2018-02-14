/*
 * SolverGeneral.cpp
 *
 * Created on: Jun 18, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#include <iostream>

#include <stdexcept>

#include "SolverGeneral.hpp"

using namespace std;
using namespace CallCostCalculator;

StateBase::StateBase(SolverGeneral& solver) : m_solver(solver) { }

StateStart::StateStart(SolverGeneral& solver) : StateBase(solver) { }

void StateStart::handle(TEvent event)
{
	m_solver.m_callStartTimestamp = event.timestamp;
	m_solver.m_lastTimeStamp = event.timestamp;

	switch(event.eventID)
	{
	case eEventStartWeekendCall:
	{
		if(0 >= m_solver.m_freeWeekendTalkingTimeSeconds)
		{
			throw logic_error("Internal program error! Solver: "
					"Requested to start weekend free call with no "
					"weekend free minutes left!");
		}

		DateTime whenFreeWeekendMinOver(event.timestamp);

		whenFreeWeekendMinOver += m_solver.m_freeWeekendTalkingTimeSeconds;

		//we must prepare the event about first N minutes on
		//weekends over...
		m_solver.injectEvent(
				eEventWeekendFirstNFreeMinutesOver,
				whenFreeWeekendMinOver.getTime());

		//go to requested state
		m_solver.m_state.reset(new StateWeekendCall(m_solver));
	}
	break;

	case eEventStartFreeMinutes:
	{
		if(0 >= m_solver.m_freeTalkingTimeInOperatorNetSeconds)
		{
			throw logic_error("Internal program error! Solver: "
					"Requested to start free call with no "
					"free minutes left!");
		}

		DateTime whenFreeMinInsideOperatorOver(event.timestamp);

		whenFreeMinInsideOperatorOver +=
				m_solver.m_freeTalkingTimeInOperatorNetSeconds;

		//we must prepare the event about free minutes inside operator over
		//if free minutes over before the end of the call it will be handled
		m_solver.injectEvent(
				eEventNoFreeMinutesLeft,
				whenFreeMinInsideOperatorOver.getTime());

		m_solver.m_state.reset(new StateFreeMinutes(m_solver));
	}
	break;

	case eEventStartNormalCall:
	{
		m_solver.m_state.reset(new StateNormalCall(m_solver));
	}
	break;

	default:
	{
		//nothing
	}
	break;
	}
}

StateWeekendCall::StateWeekendCall(SolverGeneral& solver) : StateBase(solver) { }

void StateWeekendCall::handle(TEvent event)
{
	switch(event.eventID)
	{
	case eEventNoFreeMinutesLeft:
	{
		m_solver.m_ConsumeFreeMinutesEndEvent = false;
	}
	break;

	case eEventTimeSinceLastCreditAddedOver:
	{
		m_solver.m_freeTalkingTimeInOperatorNetSeconds = 0;
		break;
	}
	case eEventWeekendFirstNFreeMinutesOver:
	case eEventWeekendOver:
		m_solver.m_freeWeekendTalkingTimeSeconds = 0;

		//always save last time-stamp on state transition
		m_solver.m_lastTimeStamp = event.timestamp;

		if (m_solver.m_freeTalkingTimeInOperatorNetSeconds > 0)
		{
			DateTime whenFreeMinInOperatorOver(event.timestamp);

			whenFreeMinInOperatorOver +=
					m_solver.m_freeTalkingTimeInOperatorNetSeconds;

			//we are going in state free minutes,
			//but prepare when minutes will over
			//i.e. start "consuming" free minutes from this very moment (after
			//free weekend call)
			m_solver.injectEvent(
					eEventNoFreeMinutesLeft,
					whenFreeMinInOperatorOver.getTime());

			m_solver.m_state.reset(new StateFreeMinutes(m_solver));
		}
		else
		{
			m_solver.m_state.reset(new StateNormalCall(m_solver));
		}

		break;

	case eEventCallEnd:
		m_solver.m_lastTimeStamp = event.timestamp;
		m_solver.m_state.reset(new StateEnd(m_solver));
		break;

	default:
		//nothing
		break;
	}
}

StateNormalCall::StateNormalCall(SolverGeneral& solver) : StateBase(solver) { }

void StateNormalCall::handle(TEvent event)
{
	switch(event.eventID)
	{
	case eEventWeekendStarted:
	{
		//check if we are still in first N free minutes range
		//if yes, exit m_ConsumeFreeMinutesEndEventnormal call state
		//and go to weekend first N minutes free
		//for example call started at Friday 23:58 and there are
		//first 5 minutes of the call free at weekends, so user has the right to
		//talk 3 minutes free due to overlap of weekend start and
		//first N minutes...

		int secondsSinceCallStart =
				static_cast<int>(difftime(
						event.timestamp,
						m_solver.m_callStartTimestamp));

		if ((m_solver.m_freeWeekendTalkingTimeSeconds > 0)
				&&
				(secondsSinceCallStart
				<
				m_solver.m_freeWeekendTalkingTimeSeconds))
		{
			//store talked time so far / prepare for state transition
			m_solver.m_result +=
					static_cast<int>(
							difftime(
									event.timestamp,
									m_solver.m_lastTimeStamp));

			m_solver.m_lastTimeStamp = event.timestamp;

			DateTime whenWeekendFirstNMinFreeOver(event.timestamp);

			whenWeekendFirstNMinFreeOver +=
					m_solver.m_freeWeekendTalkingTimeSeconds
					-
					secondsSinceCallStart;

			m_solver.injectEvent(
					eEventWeekendFirstNFreeMinutesOver,
					whenWeekendFirstNMinFreeOver.getTime());

			m_solver.m_state.reset(new StateWeekendCall(m_solver));
		}
		//else too late - call started far before "first N minutes free"
		//and current call don't overlap with the weekend
	}
		break;

	case eEventCallEnd:
		m_solver.m_result +=
				static_cast<int>(difftime(
						event.timestamp,
						m_solver.m_lastTimeStamp));

		m_solver.m_lastTimeStamp = event.timestamp;
		m_solver.m_state.reset(new StateEnd(m_solver));
		break;

	default:
		//nothing
		break;
	}
}

StateFreeMinutes::StateFreeMinutes(SolverGeneral& solver) : StateBase(solver) { }

void StateFreeMinutes::handle(TEvent event)
{
 	switch(event.eventID)
	{
	case eEventTimeSinceLastCreditAddedOver:
		m_solver.m_freeTalkingTimeInOperatorNetSeconds = 0;
		m_solver.m_lastTimeStamp = event.timestamp;
		m_solver.m_state.reset(new StateNormalCall(m_solver));
		break;

	case eEventNoFreeMinutesLeft:
		if(m_solver.m_ConsumeFreeMinutesEndEvent)
		{
			m_solver.m_ConsumeFreeMinutesEndEvent = false;
			//skip this event
			//there is expected another one
			//this is because transition to weekend call
		}
		else
		{
			m_solver.m_freeTalkingTimeInOperatorNetSeconds = 0;
			m_solver.m_lastTimeStamp = event.timestamp;
			m_solver.m_state.reset(new StateNormalCall(m_solver));
		}
		break;

	case eEventWeekendStarted:
	{
		//weekend started during consuming free minutes
		//store consumed minutes so far -------->>> !!!
		//later re-inject event to add more free minutes

		//prepare to skip one eEventNoFreeMinutesLeft
		m_solver.m_ConsumeFreeMinutesEndEvent = true;

		//check if we are still in first N free minutes range
		//if yes, exit m_ConsumeFreeMinutesEndEventnormal call state
		//and go to weekend first N minutes free
		//for example call started at Friday 23:58 and there are
		//first 5 minutes of the call free at weekends, so user has the right to
		//talk 3 minutes free due to overlap of weekend start and
		//first N minutes...

		int secondsSinceCallStart =
				static_cast<int>(difftime(
						event.timestamp,
						m_solver.m_callStartTimestamp));

		if ((m_solver.m_freeWeekendTalkingTimeSeconds > 0)
				&&
				(secondsSinceCallStart
				<
				(m_solver.m_freeWeekendTalkingTimeSeconds)))
		{
			//store consumed free time so far / prepare for state transition
			m_solver.m_freeTalkingTimeInOperatorNetSeconds -=
					static_cast<int>(difftime(
							event.timestamp,
							m_solver.m_lastTimeStamp));

			m_solver.m_lastTimeStamp = event.timestamp;

			DateTime whenWeekendFirstNMinFreeOver(event.timestamp);

			whenWeekendFirstNMinFreeOver +=
					m_solver.m_freeWeekendTalkingTimeSeconds
					-
					secondsSinceCallStart;

			m_solver.injectEvent(
					eEventWeekendFirstNFreeMinutesOver,
					whenWeekendFirstNMinFreeOver.getTime());

			m_solver.m_state.reset(new StateWeekendCall(m_solver));
		}
	}
		break;

	case eEventCallEnd:
	{
		m_solver.m_lastTimeStamp = event.timestamp;
		m_solver.m_state.reset(new StateEnd(m_solver));
	}
		break;

	default:
	{
		//nothing
	}
		break;
	}//switch
}

StateEnd::StateEnd(SolverGeneral& solver) : StateBase(solver) { }

void StateEnd::handle(TEvent event)
{
	//avoid warnings
	event = event;
	//no events can be handled here
}

SolverGeneral::SolverGeneral(
		TEventsQueueAuto eventsQueue,
		int freeWeekendTalkingTimeLeftMinutesP,
		int freeTalkingTimeInOperatorLeftMinutesP)
:
	m_eventsQueue(eventsQueue),
	m_freeWeekendTalkingTimeSeconds(
			freeWeekendTalkingTimeLeftMinutesP * SECONDS_PER_MINUTE),
	m_freeTalkingTimeInOperatorNetSeconds(
			freeTalkingTimeInOperatorLeftMinutesP * SECONDS_PER_MINUTE),
	m_state(new StateStart(*this)),
	m_lastTimeStamp(0),
	m_result(0),
	m_callStartTimestamp(0),
	m_ConsumeFreeMinutesEndEvent(false)
{
	if (0 > m_freeWeekendTalkingTimeSeconds)
	{
		throw logic_error("Internal program error! Solver: "
				"First N free minutes at weekends can not be negative!");
	}

	if (0 > m_freeTalkingTimeInOperatorNetSeconds)
	{
		throw logic_error("Internal program error! Solver: "
				"Free minutes inside operator network can not be negative!");
	}
}

void SolverGeneral::injectEvent(TEventID eventID, time_t timestamp)
{
	TEvent newEvent;

	newEvent.timestamp = timestamp;
	newEvent.eventID = eventID;

	m_eventsQueue->push(newEvent);
}

void SolverGeneral::solve()
{
	while(!m_eventsQueue->empty())
	{
		m_state->handle(m_eventsQueue->top());
		m_eventsQueue->pop();
	}
}

int SolverGeneral::getResult() const
{
	return m_result;
}

