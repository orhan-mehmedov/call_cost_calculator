/*
 * common.hpp
 *
 * Created on: Jun 18, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_COMMON_HPP_
#define CALLCOSTCALCULATOR_CODE_COMMON_HPP_

#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <string>
#include <set>
#include <string>
#include <sstream>
#include <memory>

#include "DateTime.hpp"

#define SECONDS_PER_HOUR	3600
#define HOURS_PER_DAY		24
#define SECONDS_PER_MINUTE	60

namespace CallCostCalculator
{
extern const char fileInputCommentStart;
extern const char fileInputParamValueDelimiter;
extern const char stdInputParamValueDelimiter;
extern const unsigned int ciOperatorPrefixLength;
extern const std::string cstrCallEndDateTime;
extern const std::string cstrCallStartDateTime;
extern const std::string cstrCostPerMinuteInsideOperator;
extern const std::string cstrCostPerMinuteInsideOperator;
extern const std::string cstrCostPerMinuteInsideOperator;
extern const std::string cstrCostPerMinuteOutsideOperator;
extern const std::string cstrCostPerMinuteOutsideOperator;
extern const std::string cstrCostPerMinuteOutsideOperator;
extern const std::string cstrDateTimeCredidAdded;
extern const std::string cstrDateTimeCredidAdded;
extern const std::string cstrDateTimeFormat;
extern const std::string cstrFixedConnectionFee;
extern const std::string cstrFixedConnectionFee;
extern const std::string cstrFixedConnectionFee;
extern const std::string cstrFreeMinutesInsideOperator;
extern const std::string cstrFreeMinutesInsideOperatorLeft;
extern const std::string cstrFreeMinutesInsideOperatorLeft;
extern const std::string cstrFreeMinutesInsideOperatorLeft;
extern const std::string cstrFreeMinutesOnWeekends;
extern const std::string cstrFreeMinutesOnWeekends;
extern const std::string cstrFreeMinutesOnWeekends;
extern const std::string cstrFreeTalkingDaysSinceCredit;
extern const std::string cstrFreeTalkingDaysSinceCredit;
extern const std::string cstrFreeTalkingDaysSinceCredit;
extern const std::string cstrFrontend;
extern const std::string cstrFrontEndNO;
extern const std::string cstrHomeNetworkNumbersPrefix;
extern const std::string cstrHomeNetworkNumbersPrefix;
extern const std::string cstrNumberCalled;
extern const std::string cstrOperatorPrefixSeparators;
extern const std::string cstrSubscriberAccount;

typedef enum EEvents
{
	eEventStartWeekendCall,
	eEventStartFreeMinutes,
	eEventStartNormalCall,

	eEventTimeSinceLastCreditAddedOver,
	eEventNoFreeMinutesLeft,
	eEventWeekendFirstNFreeMinutesOver,
	eEventWeekendOver,
	eEventWeekendStarted,

	eEventCallEnd
}TEventID;

typedef struct SEvent
{
	TEventID eventID;
	time_t timestamp;

	SEvent() : eventID(eEventCallEnd), timestamp(0) {}

	bool operator()(const SEvent& ev1, const SEvent& ev2)
	{
		return (0 < difftime(ev1.timestamp, ev2.timestamp));
	}
}TEvent;

typedef std::priority_queue<TEvent, std::vector<TEvent>, TEvent> TEventsQueue;
typedef std::auto_ptr<TEventsQueue>	TEventsQueueAuto;

////////////////////////////////////////////////////////////////////////////////

class DateTime;

typedef double TFixedConnectionFee;
typedef double TCostPerMinuteInsideOperator;
typedef int TFreeTalkingDaysSinceCredit;
typedef int TFreeMinutesInsideOperatorLeft;
typedef DateTime TDateTimeCredidAdded;
typedef double TCostPerMinuteOutsideOperator;
typedef int TFreeMinutesOnWeekends;
typedef std::set<std::string> THomeNetworkNumbersPrefix;

////////////////////////////////////////////////////////////////////////////////

template <class C>
std::string Num2Str(C num)
{
	std::stringstream convert;
	convert << num;
	return convert.str();
}

bool isDigitsOnly(const std::string str);

} // namespace CallCalculator

#endif /* CALLCOSTCALCULATOR_CODE_COMMON_HPP_ */
