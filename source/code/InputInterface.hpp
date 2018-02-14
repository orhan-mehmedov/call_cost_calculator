/*
 * InputInterface.hpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_INPUTINTERFACE_HPP_
#define CALLCOSTCALCULATOR_CODE_INPUTINTERFACE_HPP_

#include "TextKeyValueParserInterface.hpp"

namespace CallCostCalculator
{

class InputInterface
{
public:
	virtual bool isKeyExist(const TKey& param) const = 0;
	virtual const TValue& getParamValue(const TKey& param) const = 0;
	virtual ~InputInterface(){}
};

}

#endif /* CALLCOSTCALCULATOR_CODE_INPUTINTERFACE_HPP_ */
