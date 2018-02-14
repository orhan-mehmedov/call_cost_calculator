/*
 * DateTimeClass.cpp
 *
 * Created on: Jun 15, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>

#include "DateTime.hpp"

using namespace std;
using namespace CallCostCalculator;

DateTime::DateTime() : m_DateTime(), m_TimeInSeconds()
{
  initWithLocalTime();
}

DateTime::DateTime(time_t rawTimeP) : m_DateTime(), m_TimeInSeconds()
{
  struct tm *pMyDateTime = new tm();
  struct tm *pLocalDateTime;

  pLocalDateTime = localtime(&rawTimeP);

  //normalize
  m_TimeInSeconds = mktime(pLocalDateTime);
  *pMyDateTime = *pLocalDateTime;
  m_DateTime.reset(pMyDateTime);
}

DateTime::DateTime(const DateTime& dateTimeP)
:
    m_DateTime(new tm()), m_TimeInSeconds()
{
  *m_DateTime = *(dateTimeP.m_DateTime);
  m_TimeInSeconds = mktime(m_DateTime.get());
}

DateTime::DateTime(const string& strDateTime, const string& strFormat)
:
  m_DateTime(), m_TimeInSeconds()
{
  initWithLocalTime();

  char *pUnparsed = strptime(
      strDateTime.c_str(), strFormat.c_str(), m_DateTime.get());

  if(0 == pUnparsed)
  {

    string err("Failed to convert time! Check input values!\n");
    throw invalid_argument(err);
  }

  if('\0' != pUnparsed[0])
    cerr << "WARNING! Unparsed character(s) left after date time conversion!"
    " Check for extra character(s) after date/time (including space(s)).\n";

  //normalize
  m_TimeInSeconds = mktime(m_DateTime.get());
}

DateTime::DateTime(const tm& dateTimeP)
:
  m_DateTime(new tm()), m_TimeInSeconds()
{
  *m_DateTime = dateTimeP;
  //normalize
  m_TimeInSeconds = mktime(m_DateTime.get());
}

void DateTime::initWithLocalTime()
{
  struct tm *pMyDateTime = new tm();
  struct tm *pLocalDateTime;
  time_t rawtime;

  if (-1 == time(&rawtime))
  {
    throw runtime_error("Runtime error: time() failed.");
  }

  pLocalDateTime = localtime(&rawtime);

  //normalize
  m_TimeInSeconds = mktime(pLocalDateTime);
  *pMyDateTime = *pLocalDateTime;
  m_DateTime.reset(pMyDateTime);
}

int DateTime::getSeconds() const
{
  return m_DateTime->tm_sec;
}

int DateTime::getMinutes() const
{
  return m_DateTime->tm_min;
}

int DateTime::getHours() const
{
  return m_DateTime->tm_hour;
}

int DateTime::getDayOfMonth() const
{
  return m_DateTime->tm_mday;
}

int DateTime::getMonth() const
{
  return m_DateTime->tm_mon;
}

int DateTime::getYear() const
{
  return m_DateTime->tm_year;
}

int DateTime::getDayOfWeek() const
{
  return m_DateTime->tm_wday;
}

bool DateTime::isWeekend() const
{
  if((0 == m_DateTime->tm_wday) || (6 == m_DateTime->tm_wday))
    return true;

  return false;
}

void DateTime::resetToBeginningOfTheDay()
{
  m_DateTime->tm_hour = 0;
  m_DateTime->tm_min = 0;
  m_DateTime->tm_sec = 0;

  //normalize
  m_TimeInSeconds = mktime(m_DateTime.get());
}

int DateTime::operator -(const DateTime& otherObject) const
{
  return static_cast<int>(difftime(
      m_TimeInSeconds,
      otherObject.m_TimeInSeconds));
}

time_t DateTime::getTime() const
{
  return m_TimeInSeconds;
}

DateTime& DateTime::operator+=(int seconds)
{
  m_DateTime->tm_sec += seconds;
  //normalize
  m_TimeInSeconds = mktime(m_DateTime.get());
  return *this;
}

DateTime& DateTime::operator=(const DateTime& other)
{
  *m_DateTime = *(other.m_DateTime);
  //normalize
  m_TimeInSeconds = mktime(m_DateTime.get());

  return *this;
}

bool DateTime::operator<(const DateTime& otherObject) const
{
  return 0 > difftime(m_TimeInSeconds, otherObject.m_TimeInSeconds);
}

bool DateTime::operator>(const DateTime& otherObject) const
{
  return 0 < difftime(m_TimeInSeconds, otherObject.m_TimeInSeconds);
}

bool DateTime::operator<=(const DateTime& otherObject) const
{
  return 0 >= static_cast<int>(
      difftime(m_TimeInSeconds, otherObject.m_TimeInSeconds));
}

bool DateTime::operator>=(const DateTime& otherObject) const
{
  return 0 <= static_cast<int>(
      difftime(m_TimeInSeconds, otherObject.m_TimeInSeconds));
}

bool DateTime::operator==(const DateTime& otherObject) const
{
  return 0 == static_cast<int>(
      difftime(m_TimeInSeconds, otherObject.m_TimeInSeconds));
}

bool DateTime::operator!=(const DateTime& otherObject) const
{
  return 0 != static_cast<int>(
      difftime(m_TimeInSeconds, otherObject.m_TimeInSeconds));
}

ostream& CallCostCalculator::operator <<(ostream& os, const DateTime& dateTime)
{
  os << "DateTimeClass: ";
  os << (1900 + dateTime.getYear());
  os << "-" << (1 + dateTime.getMonth());
  os << "-" << dateTime.getDayOfMonth();
  os << "\t" << dateTime.getHours();
  os << ":" << dateTime.getMinutes();
  os << ":" << dateTime.getSeconds() << endl;
  return os;
}
