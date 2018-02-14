/*
 * CallContextData.cpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#include <stdexcept>
#include <cstdio>
#include <cstring>

#include "CallContextData.hpp"
#include "common.hpp"

using namespace std;
using namespace CallCostCalculator;

#define CONVERT(VAR, FORMAT)                  \
sscanfRes = ::sscanf(str##VAR##P.c_str(), FORMAT, &m_##VAR);  \
if((EOF == sscanfRes) || (0 == sscanfRes))            \
{                                \
  string errMessage("Failed to convert key: ");        \
  throw invalid_argument(errMessage +cstr##VAR);        \
}

CallContextData::CallContextData(
    const TFixedConnectionFee fixedConnectionFeeP,
    const TCostPerMinuteInsideOperator costPerMinuteInsideOperatorP,
    const TFreeTalkingDaysSinceCredit freeTalkingDaysSinceCreditP,
    const TFreeMinutesInsideOperatorLeft freeMinutesInsideOperatorLeftP,
    const TDateTimeCredidAdded &dateTimeCredidAddedP,
    const TCostPerMinuteOutsideOperator costPerMinuteOutsideOperatorP,
    const TFreeMinutesOnWeekends freeMinutesOnWeekendsP,
    const THomeNetworkNumbersPrefix& homeNetworkNumbersPrefixP)
:
m_FixedConnectionFee(fixedConnectionFeeP),
m_CostPerMinuteInsideOperator(costPerMinuteInsideOperatorP),
m_FreeTalkingDaysSinceCredit(freeTalkingDaysSinceCreditP),
m_FreeMinutesInsideOperatorLeft(freeMinutesInsideOperatorLeftP),
m_DateTimeCredidAdded(dateTimeCredidAddedP),
m_CostPerMinuteOutsideOperator(costPerMinuteOutsideOperatorP),
m_FreeMinutesOnWeekends(freeMinutesOnWeekendsP),
m_HomeNetworkNumbersPrefix(homeNetworkNumbersPrefixP)
{

}

CallContextData::CallContextData(
    const TextKeyValueParserInterface& parser,
    const std::string& strFixedConnectionFeeP,
    const std::string& strCostPerMinuteInsideOperatorP,
    const std::string& strFreeTalkingDaysSinceCreditP,
    const std::string& strFreeMinutesInsideOperatorLeftP,
    const std::string& strDateTimeCredidAddedP,
    const std::string& strCostPerMinuteOutsideOperatorP,
    const std::string& strFreeMinutesOnWeekendsP,
    const std::string& strHomeNetworkNumbersPrefixP)
:
    m_FixedConnectionFee(),
    m_CostPerMinuteInsideOperator(),
    m_FreeTalkingDaysSinceCredit(),
    m_FreeMinutesInsideOperatorLeft(),
    m_DateTimeCredidAdded(strDateTimeCredidAddedP, cstrDateTimeFormat),
    m_CostPerMinuteOutsideOperator(),
    m_FreeMinutesOnWeekends(),
    m_HomeNetworkNumbersPrefix()
{
  //Format check & conversion:

  int sscanfRes = 0;

  CONVERT(FixedConnectionFee, "%lf");
  CONVERT(CostPerMinuteInsideOperator, "%lf");
  CONVERT(FreeTalkingDaysSinceCredit, "%d");
  CONVERT(FreeMinutesInsideOperatorLeft, "%d");
  CONVERT(CostPerMinuteOutsideOperator, "%lf");
  CONVERT(FreeMinutesOnWeekends, "%d");

  TKeyValue keyValue = parser(
      strHomeNetworkNumbersPrefixP,
      cstrOperatorPrefixSeparators.c_str()[0]);

  if(0 == keyValue.first.length())
  {
    throw invalid_argument(
    "Error while converting operator number prefixes! Check format!");
  }

  m_HomeNetworkNumbersPrefix.insert(keyValue.first);

  while(0 < keyValue.second.length())
  {
    keyValue = parser(
        keyValue.second,
        cstrOperatorPrefixSeparators.c_str()[0]);

    m_HomeNetworkNumbersPrefix.insert(keyValue.first);
  }

  //set of string-numbers must contain only numbers
  THomeNetworkNumbersPrefix::const_iterator it;

  for(it=m_HomeNetworkNumbersPrefix.begin();
    it != m_HomeNetworkNumbersPrefix.end();
    it++)
  {
    if(!isDigitsOnly(*it))
    {
      throw invalid_argument(
      "Operator network prefixes must contain digits only!"
      " Check format!");
    }

    if(ciOperatorPrefixLength != it->length())
    {
      throw invalid_argument(
          string("Operator prefix must have length of ") +
          Num2Str(ciOperatorPrefixLength) +
          string(" digits! Check format!"));
    }
  }
}

TFixedConnectionFee CallContextData::getFixedConnectionFee() const
{
  return m_FixedConnectionFee;
}

TCostPerMinuteInsideOperator CallContextData::getCostPerMinuteInsideOperator() const
{
  return m_CostPerMinuteInsideOperator;
}

TFreeTalkingDaysSinceCredit CallContextData::getFreeTalkingDaysSinceCredit() const
{
  return m_FreeTalkingDaysSinceCredit;
}

TFreeMinutesInsideOperatorLeft
CallContextData::getFreeMinutesInsideOperatorLeft() const
{
  return m_FreeMinutesInsideOperatorLeft;
}
const TDateTimeCredidAdded& CallContextData::getDateTimeCredidAdded() const
{
  return m_DateTimeCredidAdded;
}

TCostPerMinuteOutsideOperator CallContextData::getCostPerMinuteOutsideOperator() const
{
  return m_CostPerMinuteOutsideOperator;
}

TFreeMinutesOnWeekends CallContextData::getFreeMinutesOnWeekendsP() const
{
  return m_FreeMinutesOnWeekends;
}

const THomeNetworkNumbersPrefix& CallContextData::getHomeNetworkNumbersPrefix() const
{
  return m_HomeNetworkNumbersPrefix;
}

