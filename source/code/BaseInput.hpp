/*
 * BaseInput.hpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_BASEINPUT_HPP_
#define CALLCOSTCALCULATOR_CODE_BASEINPUT_HPP_

#include <map>

#include "InputInterface.hpp"

namespace CallCostCalculator
{

typedef std::map<TKey, TValue> TInputParam;

class BaseInput : public InputInterface
{
protected:
	TInputParam m_KeyValues;

	virtual void parseInput() = 0;

public:
	BaseInput();
	bool isKeyExist(const TKey& param) const;
	const TValue& getParamValue(const TKey& param) const;
	virtual ~BaseInput();
};

}

#endif /* CALLCOSTCALCULATOR_CODE_BASEINPUT_HPP_ */

