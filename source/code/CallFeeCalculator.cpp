/*
 * CallFeeCalculator.cpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#include <stdexcept>

#include "CallFeeCalculator.hpp"
#include "common.hpp"

#define SECONDS_PER_HALF_DAY  43200

using namespace std;
using namespace CallCostCalculator;

void CallFeeCalculator::Calculate()
{
  CallCostCalculator::TContext context;
  CallCostCalculator::TCallData callData;
  TCallCost fee;

  context = getContextData();

  callData = getCallInfo();

  inputLogicalControl(context, callData);

  fee = callCalculation(context, callData);

  provideResult(fee);
}

void CallFeeCalculator::inputLogicalControl(
    TContext& context, TCallData& callData)
{
  if (0 > context->getFixedConnectionFee())
  {
    throw invalid_argument(
        "Fixed connection fee can not be negative!");
  }

  if (0 > context->getFreeMinutesInsideOperatorLeft())
  {
    throw invalid_argument(
        "Free minutes inside operator can not be negative!");
  }

  if (0 > context->getFreeTalkingDaysSinceCredit())
  {
    throw invalid_argument(
        "Free talking days since credit can not be negative!");
  }

  if (0 > context->getFreeMinutesInsideOperatorLeft())
  {
    throw invalid_argument(
        "Free minutes inside operator can not be negative!");
  }

  if (0 > context->getCostPerMinuteOutsideOperator())
  {
    throw invalid_argument(
        "Cost per minute outside operator can not be negative!");
  }

  if (0 > context->getFreeMinutesOnWeekendsP())
  {
    throw invalid_argument(
        "Free minutes on weekends can not be negative!");
  }

  if (0 > context->getCostPerMinuteInsideOperator())
  {
    throw invalid_argument(
        "Cost per minute inside operator can not be negative!");
  }

  if(callData->getCallEndDateTime() <= callData->getCallStartDateTime())
  {
    throw invalid_argument(
        "Call info: End time <= Start time! Not allowed!");
  }

  if((callData->getCallEndDateTime() - callData->getCallStartDateTime())
      > SECONDS_PER_HALF_DAY)
  {
    throw invalid_argument(
        "Call info: Call can not be longer than 12 hours!");
  }

  if(context->getDateTimeCredidAdded() >= callData->getCallStartDateTime())
  {
    throw invalid_argument(
        "Last credit added after or match the start call time? "
        "Not allowed!");
  }

  //it is not clear how long number could be
  //assumed that a number must be longer than operator prefix
  if (ciOperatorPrefixLength >= callData->getNumberCalled().length())
  {
    throw invalid_argument(
        string("Number called must be longer than operator network prefix (") +
        Num2Str(ciOperatorPrefixLength) + " digits)!");
  }

  DateTime dateTimeCurrent;

  if(dateTimeCurrent < callData->getCallStartDateTime())
  {
    throw invalid_argument(
        "Call started in the future? Not allowed! "
        "Check system clock / input data.");
  }
}

CallFeeCalculator::~CallFeeCalculator()
{

}


