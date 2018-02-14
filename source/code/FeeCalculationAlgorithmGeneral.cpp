/*
 * FeeCalculationAlgorithmGeneral.cpp
 *
 * Created on: Jun 17, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#include <stdexcept>
#include <memory>
#include <ctime>

#include "FeeCalculationAlgorithmGeneral.hpp"
#include "common.hpp"
#include "SolverGeneral.hpp"

using namespace std;
using namespace CallCostCalculator;

//In general this method prepares input for solver
//according requirements
//and calculates the result based on solver return value
double
FeeCalculationAlgorithmGeneral::calculateCallCost(
    TContext context, TCallData callData)
{
  double result = 0.0;
  double callCost = context->getCostPerMinuteOutsideOperator();
  bool bIsHomeNetworkCall = false;
  TEventsQueueAuto events(new TEventsQueue());

  ////////////////////////////////////////////////////////////////////////////

  THomeNetworkNumbersPrefix::const_iterator it;

  //check number - if inside home network call -> adjust call cost
  for(it = context->getHomeNetworkNumbersPrefix().begin();
    it != context->getHomeNetworkNumbersPrefix().end();
    it++)
  {
    if(0 == callData->getNumberCalled().find(*it))
    {
      callCost = context->getCostPerMinuteInsideOperator();
      bIsHomeNetworkCall = true;
      break;
    }
  }

  ////////////////////////////////////////////////////////////////////////////

  TEvent e_start;

  //when credit time over?
  DateTime endCreditTimeDate(context->getDateTimeCredidAdded().getTime());

  endCreditTimeDate +=
      (context->getFreeTalkingDaysSinceCredit()*
          SECONDS_PER_HOUR*HOURS_PER_DAY);

  e_start.timestamp = callData->getCallStartDateTime().getTime();

  //decide call mode at start - was it weekend call (5min free)
  //or normal call but subscriber has some free minutes etc.

  if(!callData->getCallStartDateTime().isWeekend()
      &&
   (endCreditTimeDate > callData->getCallStartDateTime())
   &&
   (0 < context->getFreeTalkingDaysSinceCredit())
   &&
   (0 < context->getFreeMinutesInsideOperatorLeft())
   &&
   bIsHomeNetworkCall)
  {
    e_start.eventID = eEventStartFreeMinutes;
    e_start.timestamp = callData->getCallStartDateTime().getTime();
  }
  else
  {
    if(callData->getCallStartDateTime().isWeekend())
    {
      e_start.eventID = eEventStartWeekendCall;
      e_start.timestamp = callData->getCallStartDateTime().getTime();
    }
    else
    {
      e_start.eventID = eEventStartNormalCall;
      e_start.timestamp = callData->getCallStartDateTime().getTime();
    }
  }

  events->push(e_start);

  ////////////////////////////////////////////////////////////////////////////

  if((endCreditTimeDate > callData->getCallStartDateTime())
      &&
    bIsHomeNetworkCall)
  {
    TEvent e_creditDateOver;
    e_creditDateOver.eventID = eEventTimeSinceLastCreditAddedOver;
    e_creditDateOver.timestamp = endCreditTimeDate.getTime();
    events->push(e_creditDateOver);
  }

  ////////////////////////////////////////////////////////////////////////////

  TEvent e_end;
  e_end.eventID = eEventCallEnd;
  e_end.timestamp = callData->getCallEndDateTime().getTime();

  events->push(e_end);

  ////////////////////////////////////////////////////////////////////////////

  TEvent e_WeekendWeekDayTransition;

  //weekend start/over during call ???
  if(callData->getCallStartDateTime().isWeekend()
      &&
     (!callData->getCallEndDateTime().isWeekend()))
  {
    e_WeekendWeekDayTransition.eventID = eEventWeekendOver;
    DateTime temp = callData->getCallEndDateTime();
    temp.resetToBeginningOfTheDay();
    e_WeekendWeekDayTransition.timestamp = temp.getTime();

    events->push(e_WeekendWeekDayTransition);
  }
  else if(callData->getCallEndDateTime().isWeekend() &&
     (!callData->getCallStartDateTime().isWeekend()))
  {
    e_WeekendWeekDayTransition.eventID = eEventWeekendStarted;
    DateTime temp = callData->getCallEndDateTime();
    temp.resetToBeginningOfTheDay();
    e_WeekendWeekDayTransition.timestamp = temp.getTime();

    events->push(e_WeekendWeekDayTransition);
  }

  ////////////////////////////////////////////////////////////////////////////

  //free minutes are meaningless if talking days == 0
  int freeMinutesInsideOperator =
      (0 < context->getFreeTalkingDaysSinceCredit())  ?
      (context->getFreeMinutesInsideOperatorLeft())  :
      0;

  if((0 >= context->getFreeTalkingDaysSinceCredit()) ||
    !bIsHomeNetworkCall)
  {
    freeMinutesInsideOperator = 0;
  }

  ////////////////////////////////////////////////////////////////////////////

  SolverGeneral solver(
      events,
      context->getFreeMinutesOnWeekendsP(),
      freeMinutesInsideOperator);

  solver.solve();

  int solverRes = solver.getResult();

  ////////////////////////////////////////////////////////////////////////////

  int minutesToBeCharged = static_cast<int>(
                static_cast<double>(solverRes) / 60.0);

  //- Minute fee is charged at the beginning of each minute,
  //so if call duration is 1:03, two minutes cost should be paid
  if(solverRes % 60)
    minutesToBeCharged++;

  result += minutesToBeCharged * callCost +
      context->getFixedConnectionFee();//- Fixed connection fee of 0.33
                       //that is added to any call cost.

  return result;
}
