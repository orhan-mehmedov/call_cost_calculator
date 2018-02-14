/*
 * BaseInput.cpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#include "BaseInput.hpp"

using namespace std;
using namespace CallCostCalculator;

BaseInput::BaseInput()
:
	m_KeyValues()
{

}

bool BaseInput::isKeyExist(const TKey& param) const
{
	bool result = false;

	TInputParam::const_iterator it;

	if (m_KeyValues.end() != m_KeyValues.find(param))
	{
		result = true;
	}

	return result;
}

const TValue& BaseInput::getParamValue(const TKey& param) const
{
	return (m_KeyValues.find(param))->second;
}

BaseInput::~BaseInput()
{

}


