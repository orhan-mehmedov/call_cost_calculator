/*
 * TextKeyValueParserStandard.hpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_TEXTKEYVALUEPARSERSTANDARD_HPP_
#define CALLCOSTCALCULATOR_CODE_TEXTKEYVALUEPARSERSTANDARD_HPP_

#include "TextKeyValueParserInterface.hpp"

namespace CallCostCalculator
{
class TextKeyValueParserStandard : public TextKeyValueParserInterface
{
public:
	virtual TKeyValue operator()(const std::string& str, const char delimiter) const;
	virtual ~TextKeyValueParserStandard();
};

}

#endif /* CALLCOSTCALCULATOR_CODE_TEXTKEYVALUEPARSERSTANDARD_HPP_ */
