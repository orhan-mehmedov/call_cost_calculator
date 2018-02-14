/*
 * DateTime.hpp
 *
 * Created on: Jun 15, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_DATETIME_HPP_
#define CALLCOSTCALCULATOR_CODE_DATETIME_HPP_

#include <ctime>
#include <memory>

namespace CallCostCalculator
{

class DateTime
{
	std::auto_ptr<struct tm> m_DateTime;
	time_t m_TimeInSeconds;//since UNIX epoch

	void initWithLocalTime();
public:
	DateTime();
	explicit DateTime(time_t rawTimeP);
	DateTime(const DateTime& dateTimeP);
	explicit DateTime(const tm& dateTimeP);
	DateTime(const std::string& strDateTime, const std::string& strFormat);

	int getSeconds() const;
	int getMinutes() const;
	int getHours() const;
	int getDayOfMonth() const;
	int getMonth() const;
	int getYear() const;
	int getDayOfWeek() const;

	bool isWeekend() const;
	void resetToBeginningOfTheDay();

	//return difference in seconds
	int operator -(const DateTime& otherObject) const;

	time_t getTime() const;

	//adding seconds to current time
	DateTime& operator+=(int seconds);
	DateTime& operator=(const DateTime& other);

	bool operator<(const DateTime& otherObject) const;
	bool operator>(const DateTime& otherObject) const;
	bool operator<=(const DateTime& otherObject) const;
	bool operator>=(const DateTime& otherObject) const;
	bool operator==(const DateTime& otherObject) const;
	bool operator!=(const DateTime& otherObject) const;
};

std::ostream& operator <<(std::ostream& os, const DateTime& dateTime);

}

#endif /* CALLCOSTCALCULATOR_CODE_DATETIME_HPP_ */
