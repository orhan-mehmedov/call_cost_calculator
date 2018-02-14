/*
 * CallFeeCalculatorNoFrontend.cpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#include <iostream>
#include <stdexcept>
#include <cstdio>

#include "CallFeeCalculatorNoFrontend.hpp"
#include "common.hpp"

#define CHECK_KEY_EXIST(INPUT, KEY)        \
if(!INPUT->isKeyExist(KEY))            \
{                        \
  string errMessage("Cannot find key: ");    \
  throw invalid_argument(errMessage + KEY);  \
}

using namespace std;
using namespace CallCostCalculator;

namespace CallCostCalculator
{
extern const string cstrCallStartDateTime;
extern const string cstrCallEndDateTime;
extern const string cstrNumberCalled;
}

CallFeeCalculatorNoFrontend::CallFeeCalculatorNoFrontend(
    auto_ptr<InputInterface> stdInputCallInfo,
    auto_ptr<InputInterface> fileAccountInfoInput,
    auto_ptr<TextKeyValueParserInterface> parser,
    auto_ptr<FeeCalculationAlgorithmInterface> algorithm)
:
  m_stdInputCallInfo(stdInputCallInfo),
  m_fileAccountInfoInput(fileAccountInfoInput),
  m_parser(parser),
  m_algorithm(algorithm)
{

}

TContext CallFeeCalculatorNoFrontend::getContextData()
{
  CHECK_KEY_EXIST(m_fileAccountInfoInput, cstrFixedConnectionFee);
  CHECK_KEY_EXIST(m_fileAccountInfoInput, cstrCostPerMinuteInsideOperator);
  CHECK_KEY_EXIST(m_fileAccountInfoInput, cstrFreeTalkingDaysSinceCredit);
  CHECK_KEY_EXIST(m_fileAccountInfoInput, cstrFreeMinutesInsideOperatorLeft);
  CHECK_KEY_EXIST(m_fileAccountInfoInput, cstrDateTimeCredidAdded);
  CHECK_KEY_EXIST(m_fileAccountInfoInput, cstrCostPerMinuteOutsideOperator);
  CHECK_KEY_EXIST(m_fileAccountInfoInput, cstrFreeMinutesOnWeekends);
  CHECK_KEY_EXIST(m_fileAccountInfoInput, cstrHomeNetworkNumbersPrefix);

  TContext context(
    new CallContextData(
      *m_parser,
      m_fileAccountInfoInput->getParamValue(cstrFixedConnectionFee),
      m_fileAccountInfoInput->getParamValue(cstrCostPerMinuteInsideOperator),
      m_fileAccountInfoInput->getParamValue(cstrFreeTalkingDaysSinceCredit),
      m_fileAccountInfoInput->getParamValue(cstrFreeMinutesInsideOperatorLeft),
      m_fileAccountInfoInput->getParamValue(cstrDateTimeCredidAdded),
      m_fileAccountInfoInput->getParamValue(cstrCostPerMinuteOutsideOperator),
      m_fileAccountInfoInput->getParamValue(cstrFreeMinutesOnWeekends),
      m_fileAccountInfoInput->getParamValue(cstrHomeNetworkNumbersPrefix)
      ));

  return context;
}

TCallData CallFeeCalculatorNoFrontend::getCallInfo()
{
  CHECK_KEY_EXIST(m_stdInputCallInfo, cstrCallStartDateTime);
  CHECK_KEY_EXIST(m_stdInputCallInfo, cstrCallEndDateTime);
  CHECK_KEY_EXIST(m_stdInputCallInfo, cstrNumberCalled);

  TCallData callData(
      new CallData(
          m_stdInputCallInfo->getParamValue(cstrCallStartDateTime),
          m_stdInputCallInfo->getParamValue(cstrCallEndDateTime),
          m_stdInputCallInfo->getParamValue(cstrNumberCalled)));

  return callData;
}

TCallCost CallFeeCalculatorNoFrontend::callCalculation(TContext context, TCallData callData)
{
  double result =  m_algorithm->calculateCallCost(context, callData);

  //internal check:
  if (0 > result)
  {
    throw logic_error(
        string("Internal programming error:\n"
             "Call cast calculated as negative number = ") +
        Num2Str(result) + string("! Not allowed!"));
  }

  return result;
}

void CallFeeCalculatorNoFrontend::provideResult(TCallCost result)
{
  cout << result << endl;
}

CallFeeCalculatorNoFrontend::~CallFeeCalculatorNoFrontend()
{

}

