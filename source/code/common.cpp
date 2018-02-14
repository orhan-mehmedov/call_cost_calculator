/*
 * common.cpp
 *
 * Created on: Jun 18, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#include <cctype>

#include "common.hpp"

namespace CallCostCalculator
{
using namespace std;

extern const std::string cstrOperatorPrefixSeparators = ",";
extern const unsigned int ciOperatorPrefixLength = 3;
extern const char fileInputParamValueDelimiter = '=';
extern const char fileInputCommentStart = '#';

extern const std::string cstrFixedConnectionFee = "fixedConnectionFee";
extern const std::string cstrFreeMinutesInsideOperator = "freeMinutesInsideOperator";
extern const std::string cstrCostPerMinuteInsideOperator = "costPerMinuteInsideOperator";
extern const std::string cstrFreeTalkingDaysSinceCredit = "freeTalkingDaysSinceCredit";
extern const std::string cstrFreeMinutesInsideOperatorLeft = "freeMinutesInsideOperatorLeft";
extern const std::string cstrDateTimeCredidAdded = "dateTimeCredidAdded";
extern const std::string cstrCostPerMinuteOutsideOperator = "costPerMinuteOutsideOperator";
extern const std::string cstrFreeMinutesOnWeekends = "freeMinutesOnWeekends";
extern const std::string cstrHomeNetworkNumbersPrefix = "homeNetworkNumbersPrefix";

extern const std::string cstrFrontEndNO = "NO";
extern const char stdInputParamValueDelimiter = '=';

extern const std::string cstrFrontend = "frontend";
extern const std::string cstrSubscriberAccount = "subscriber_account";

extern const std::string cstrCallStartDateTime = "call_start_date_time";
extern const std::string cstrCallEndDateTime = "call_end_date_time";
extern const std::string cstrNumberCalled = "number_called";

extern const string cstrDateTimeFormat = "%Y-%m-%d %H:%M:%S";

bool isDigitsOnly(const string str)
{
  bool result = true;

  size_t i = 0;

  while (str[i] != '\0')
  {
    if(!isdigit(str[i]))
    {
      result = false;
      break;
    }
    ++i;
  }

  return result;
}

} // namespace CallCalculator
