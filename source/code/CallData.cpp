/*
 * CallData.cpp
 *
 * Created on: Jun 17, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#include <stdexcept>

#include "CallData.hpp"
#include "common.hpp"

using namespace std;
using namespace CallCostCalculator;

CallData::CallData(
    std::string strCallStartDateTime,
    std::string strCallEndDateTime,
    std::string strNumberCalled)
:
    m_CallStartDateTime(strCallStartDateTime, cstrDateTimeFormat),
    m_CallEndDateTime(strCallEndDateTime, cstrDateTimeFormat),
    m_strNumberCalled(strNumberCalled)
{
  if(!isDigitsOnly(m_strNumberCalled))
  {
    throw invalid_argument("Number called must contain digits only!");
  }
}

const DateTime& CallData::getCallStartDateTime() const
{
  return m_CallStartDateTime;
}

const DateTime& CallData::getCallEndDateTime() const
{
  return m_CallEndDateTime;
}

const std::string& CallData::getNumberCalled() const
{
  return m_strNumberCalled;
}



