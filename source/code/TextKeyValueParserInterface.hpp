/*
 * TextKeyValueParserInterface.hpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_TEXTKEYVALUEPARSERINTERFACE_HPP_
#define CALLCOSTCALCULATOR_CODE_TEXTKEYVALUEPARSERINTERFACE_HPP_

#include <string>
#include <utility>

namespace CallCostCalculator
{

typedef std::string TKey;
typedef std::string TValue;
typedef std::pair<TKey, TValue> TKeyValue;

class TextKeyValueParserInterface
{
public:
  virtual TKeyValue operator()(const std::string& str, const char delimiter) const = 0;
  virtual ~TextKeyValueParserInterface(){}
};

}

#endif /* CALLCOSTCALCULATOR_CODE_TEXTKEYVALUEPARSERINTERFACE_HPP_ */
