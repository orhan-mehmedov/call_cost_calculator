/*
 * CallContextData.hpp
 *
 * Created on: Jun 15, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_CALLCONTEXTDATA_HPP_
#define CALLCOSTCALCULATOR_CODE_CALLCONTEXTDATA_HPP_

#include <set>
#include <memory>
#include <string>

#include "common.hpp"
#include "DateTime.hpp"
#include "TextKeyValueParserInterface.hpp"

namespace CallCostCalculator
{

class CallContextData;

typedef std::auto_ptr<CallContextData> TContext;

class CallContextData
{
  // Fixed connection fee of 0.33 that is added to any call cost.
  TFixedConnectionFee m_FixedConnectionFee;

  // After free minutes expire, calls inside home operator network are
  // charged 0.50 per minute.
  TCostPerMinuteInsideOperator m_CostPerMinuteInsideOperator;//[0...+MAX]

  // valid for 30 days since the date when last
  // credit was added
  TFreeTalkingDaysSinceCredit m_FreeTalkingDaysSinceCredit;

  //how much free minutes left:
  TFreeMinutesInsideOperatorLeft m_FreeMinutesInsideOperatorLeft;

  //date/time credit was added -> format is "%Y-%m-%d %H:%M:%S"
  TDateTimeCredidAdded m_DateTimeCredidAdded;

  // When calling numbers outside of home network, minute cost is 0.95.
  TCostPerMinuteOutsideOperator m_CostPerMinuteOutsideOperator;//[0...+MAX]

  // On weekends, first five minutes of every call are free.
  TFreeMinutesOnWeekends m_FreeMinutesOnWeekends;//[0...+MAX]

  // We define home network of the operator as a set of phone numbers
  // starting with one of the given prefixes (050, 066, 095, and 099).
  THomeNetworkNumbersPrefix m_HomeNetworkNumbersPrefix;

public:
  CallContextData(
      const TFixedConnectionFee fixedConnectionFeeP,
      const TCostPerMinuteInsideOperator costPerMinuteInsideOperatorP,
      const TFreeTalkingDaysSinceCredit freeTalkingDaysSinceCreditP,
      const TFreeMinutesInsideOperatorLeft freeMinutesInsideOperatorLeftP,
      const TDateTimeCredidAdded &dateTimeCredidAddedP,
      const TCostPerMinuteOutsideOperator costPerMinuteOutsideOperatorP,
      const TFreeMinutesOnWeekends freeMinutesOnWeekendsP,
      const THomeNetworkNumbersPrefix& homeNetworkNumbersPrefixP);

  CallContextData(
      const TextKeyValueParserInterface& parser,
      const std::string& strFixedConnectionFeeP,
      const std::string& strCostPerMinuteInsideOperatorP,
      const std::string& strFreeTalkingDaysSinceCreditP,
      const std::string& strFreeMinutesInsideOperatorLeftP,
      const std::string& strDateTimeCredidAddedP,
      const std::string& strCostPerMinuteOutsideOperatorP,
      const std::string& strFreeMinutesOnWeekendsP,
      const std::string& strHomeNetworkNumbersPrefixP);

  TFixedConnectionFee getFixedConnectionFee() const;
  TCostPerMinuteInsideOperator getCostPerMinuteInsideOperator() const;
  TFreeTalkingDaysSinceCredit getFreeTalkingDaysSinceCredit() const;
  TFreeMinutesInsideOperatorLeft getFreeMinutesInsideOperatorLeft() const;
  const TDateTimeCredidAdded& getDateTimeCredidAdded() const;
  TCostPerMinuteOutsideOperator getCostPerMinuteOutsideOperator() const;
  TFreeMinutesOnWeekends getFreeMinutesOnWeekendsP() const;
  const THomeNetworkNumbersPrefix& getHomeNetworkNumbersPrefix() const;
};

}

#endif /* CALLCOSTCALCULATOR_CODE_CALLCONTEXTDATA_HPP_ */
