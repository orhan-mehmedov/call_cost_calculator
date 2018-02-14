/*
 * CallData.hpp
 *
 * Created on: Jun 15, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_CALLDATA_HPP_
#define CALLCOSTCALCULATOR_CODE_CALLDATA_HPP_

#include <string>
#include <memory>

#include "DateTime.hpp"

namespace CallCostCalculator
{

class CallData;

typedef std::auto_ptr<CallData> TCallData;

class CallData
{
	DateTime m_CallStartDateTime;
	DateTime m_CallEndDateTime;
	std::string m_strNumberCalled;

public:
	CallData(
			std::string strCallStartDateTime,
			std::string strCallEndDateTime,
			std::string strNumberCalled);

	const DateTime& getCallStartDateTime() const;
	const DateTime& getCallEndDateTime() const;
	const std::string& getNumberCalled() const;
};

}

#endif /* CALLCOSTCALCULATOR_CODE_CALLDATA_HPP_ */
