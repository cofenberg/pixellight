/*********************************************************\
 *  File: Time.cpp                                       *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/RegEx.h"
#include "PLGeneral/Tools/Time.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const Time   Time::Null;
const Time   Time::UnixEpochStart(1970, January, 1, Thursday, 0, 0, 0, 0);
const Time   Time::DOSEpochStart (1980, January, 1, Tuesday,  0, 0, 0, 0);
const String Time::ShortMonthName[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const String Time::ShortDayName[7]    = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns whether or not the given year is a leap year
*/
bool Time::IsLeapYear(uint32 nYear)
{
	// The Gregorian calendar was introduced in 1582...
	// Rule: "Every fourth year is a leap year except for century years that are not divisible by 400"
	return ((nYear >= 1582) ? !(nYear%4) && ((nYear%100) || !(nYear%400)) : !(nYear % 4));
}

/**
*  @brief
*    Returns the number of days in a month
*/
uint8 Time::GetDaysPerMonth(EMonth nMonth, uint32 nYear)
{
	switch (nMonth) {
		case January:
		case March:
		case May:
		case July:
		case August:
		case October:
		case December:
			return 31;

		case February:
			if (nYear > 0 && IsLeapYear(nYear))
				return 29;
			else
				return 28;

		default:
			return 30;
	}
}

/**
*  @brief
*    Calculates the day of a week
*/
Time::EDay Time::CalculateDayOfWeek(uint8 nDayOfMonth, EMonth nMonth, uint16 nYear)
{
	int nFebruaryDays = IsLeapYear(nYear) ? 29 : 28;
	int a = nYear - 2000;
	int t = a > 0;
	int b = (a - t)/4 + t;
	int c = (a - t)/100;
	c -= c/4;
	int nDayOfWeek = a + b - c;
	int nCurrentMonth = nMonth;
	while (nCurrentMonth--) {
		if (nCurrentMonth == 1 || nCurrentMonth == 3 || nCurrentMonth == 5 ||
			nCurrentMonth == 7 || nCurrentMonth == 8 || nCurrentMonth == 10)
			nDayOfWeek += 31;
		else nDayOfWeek += (nCurrentMonth != 2) ? 30 : nFebruaryDays;
	}
	nDayOfWeek += nDayOfMonth + 3;
	nDayOfWeek %= 7;
	return EDay((nDayOfWeek >= 0) ? nDayOfWeek : nDayOfWeek + 7);
}

//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Time::Time() :
	m_nYear(0),
	m_nMonth(January),
	m_nDayOfMonth(1),
	m_nDayOfWeek(Sunday),
	m_nHour(0),
	m_nMinute(0),
	m_nSecond(0),
	m_nMillisecond(0)
{
}

/**
*  @brief
*    Constructor
*/
Time::Time(uint16 nYear, EMonth nMonth, uint8 nDayOfMonth, EDay nDayOfWeek, uint8 nHour, uint8 nMinute, uint8 nSecond, uint16 nMillisecond) :
	m_nYear(nYear),
	m_nMonth(nMonth),
	m_nDayOfMonth(nDayOfMonth),
	m_nDayOfWeek(nDayOfWeek),
	m_nHour(nHour),
	m_nMinute(nMinute),
	m_nSecond(nSecond),
	m_nMillisecond(nMillisecond)
{
}

/**
*  @brief
*    Destructor
*/
Time::~Time()
{
}

/**
*  @brief
*    Get the year
*/
uint16 Time::GetYear() const
{
	return m_nYear;
}

/**
*  @brief
*    Set the year
*/
void Time::SetYear(uint16 nYear)
{
	m_nYear = nYear;
}

/**
*  @brief
*    Get the month
*/
Time::EMonth Time::GetMonth() const
{
	return m_nMonth;
}

/**
*  @brief
*    Set the month
*/
void Time::SetMonth(EMonth nMonth)
{
	m_nMonth = nMonth;
}

/**
*  @brief
*    Get the day of the month
*/
uint8 Time::GetDayOfMonth() const
{
	return m_nDayOfMonth;
}

/**
*  @brief
*    Set the day of the month
*/
void Time::SetDayOfMonth(uint8 nDayOfMonth)
{
	if (nDayOfMonth >= 1 && nDayOfMonth <= 31)
		m_nDayOfMonth = nDayOfMonth;
}

/**
*  @brief
*    Get the day of the week
*/
Time::EDay Time::GetDayOfWeek() const
{
	return m_nDayOfWeek;
}

/**
*  @brief
*    Set the day of the week
*/
void Time::SetDayOfWeek(EDay nDayOfWeek)
{
	m_nDayOfWeek = nDayOfWeek;
}

/**
*  @brief
*    Get the hour
*/
uint8 Time::GetHour() const
{
	return m_nHour;
}

/**
*  @brief
*    Set the hour
*/
void Time::SetHour(uint8 nHour)
{
	if (nHour <= 23)
		m_nHour = nHour;
}

/**
*  @brief
*    Get the minute
*/
uint8 Time::GetMinute() const
{
	return m_nMinute;
}

/**
*  @brief
*    Set the minute
*/
void Time::SetMinute(uint8 nMinute)
{
	if (nMinute <= 59)
		m_nMinute = nMinute;
}

/**
*  @brief
*    Get the second
*/
uint8 Time::GetSecond() const
{
	return m_nSecond;
}

/**
*  @brief
*    Set the second
*/
void Time::SetSecond(uint8 nSecond)
{
	if (nSecond <= 59)
		m_nSecond = nSecond;
}

/**
*  @brief
*    Get the millisecond
*/
uint16 Time::GetMillisecond() const
{
	return m_nMillisecond;
}

/**
*  @brief
*    Set the millisecond
*/
void Time::SetMillisecond(uint16 nMillisecond)
{
	if (nMillisecond <= 999)
		m_nMillisecond = nMillisecond;
}

/**
*  @brief
*    Returns a string representation of the time
*/
String Time::ToString() const
{
	return String::Format("%.3s %.3s%3d %.2d:%.2d:%.2d %d",
						  ShortDayName[m_nDayOfWeek].GetASCII(), ShortMonthName[m_nMonth-1].GetASCII(),
						  m_nDayOfMonth, m_nHour, m_nMinute, m_nSecond, m_nYear);
}

/**
*  @brief
*    Set time from string representation
*/
void Time::FromString(const String &sString)
{
	// Parse string
	RegEx cRegEx("(?<dow>\\w+)\\s(?<month>\\w+)\\s(?<day>\\w+)\\s(?<hour>\\w+):(?<min>\\w+):(?<sec>\\w+)\\s(?<year>\\w+)");
	if (cRegEx.Match(sString)) {
		// Read time
		m_nYear		   = (uint16)cRegEx.GetNameResult("year") .GetInt();
		m_nMonth	   = (EMonth)cRegEx.GetNameResult("month").GetInt();
		m_nDayOfMonth  = (uint8) cRegEx.GetNameResult("day")  .GetInt();
		m_nHour		   = (uint8) cRegEx.GetNameResult("hour") .GetInt();
		m_nMinute	   = (uint8) cRegEx.GetNameResult("min")  .GetInt();
		m_nSecond	   = (uint8) cRegEx.GetNameResult("sec")  .GetInt();
		m_nMillisecond = 0;

		// Get day of week
		String sDayOfWeek = cRegEx.GetNameResult("dow");
		int nDay = -1;
		for (int i=0; i<7; i++) {
			// Day of week found?
			if (ShortDayName[i] == sDayOfWeek) {
				nDay = i;
				break;
			}
		}

		// Set day of week, if the string was not found, try to calculate it from the date
		if (nDay >= 0)
			m_nDayOfWeek = (EDay)nDay;
		else
			m_nDayOfWeek = Time::CalculateDayOfWeek(m_nDayOfMonth, m_nMonth, m_nYear);
	}
}

/**
*  @brief
*    Converts a date from Unix/POSIX format
*/
void Time::SetUnixDate(uint32 nUnixDate)
{
	// Seconds per day
	static const uint32 SecondsPerDay = 24*60*60;

	// Days per month - nonleap
	static const uint32 DaysPerMonth[12] = {
		0,
		(31),
		(31+28),
		(31+28+31),
		(31+28+31+30),
		(31+28+31+30+31),
		(31+28+31+30+31+30),
		(31+28+31+30+31+30+31),
		(31+28+31+30+31+30+31+31),
		(31+28+31+30+31+30+31+31+30),
		(31+28+31+30+31+30+31+31+30+31),
		(31+28+31+30+31+30+31+31+30+31+30),
	};

	uint32 nWork = nUnixDate%SecondsPerDay;
	m_nSecond = (uint8)nWork%60;
	nWork /= 60;
	m_nMinute = (uint8)nWork%60;
	m_nHour = (uint8)nWork/60;
	nWork = nUnixDate/SecondsPerDay;
	m_nDayOfWeek = (EDay)((4 + nWork)%7);
	uint32 i = 1970;
	for (;; i++) {
		uint32 k = IsLeapYear(i) ? 366 : 365;
		if (nWork >= k) nWork -= k;
		else			break;
	}
	m_nYear = (uint16)i;
	m_nDayOfMonth = 1;
	if (IsLeapYear(i) && (nWork>58)) {
		if (nWork == 59) m_nDayOfMonth; // 29.2.
		nWork -= 1;
	}

	for (i=11; i && (DaysPerMonth[i]>nWork); i--) ;
	m_nMonth = (EMonth)(i+1);
	m_nDayOfMonth = uint8(m_nDayOfMonth + (nWork - DaysPerMonth[i]));
}

/**
*  @brief
*    Converts a date from DOS format
*/
void Time::SetDOSDate(uint32 nDOSDate)
{
	uint32 nDate = nDOSDate >> 16;
	m_nYear        = (uint16)(((nDate    & 0x0FE00) / 0x0200) + 1980);
	m_nMonth       = (EMonth)(((nDate    & 0x1E0)   / 0x20) + 1);
	m_nDayOfMonth  = (uint8)   (nDate    & 0x1f) + 1;
	m_nDayOfWeek   = CalculateDayOfWeek(m_nDayOfMonth, m_nMonth, m_nYear);
	m_nHour        = (uint8)  ((nDOSDate & 0xF800)  / 0x800);
	m_nMinute      = (uint8)  ((nDOSDate & 0x7E0)   / 0x20);
	m_nSecond      = (uint8)  ((nDOSDate & 0x1f)    * 2);
	m_nMillisecond = 0;
}


//[-------------------------------------------------------]
//[ Comparison                                            ]
//[-------------------------------------------------------]
bool Time::operator ==(const Time &cTime) const
{
	return (m_nYear        == cTime.m_nYear       &&
			m_nMonth       == cTime.m_nMonth      &&
			m_nDayOfMonth  == cTime.m_nDayOfMonth &&
			m_nDayOfWeek   == cTime.m_nDayOfWeek  &&
			m_nHour        == cTime.m_nHour       &&
			m_nMinute      == cTime.m_nMinute     &&
			m_nSecond      == cTime.m_nSecond     &&
			m_nMillisecond == cTime.m_nMillisecond);
}

bool Time::operator !=(const Time &cTime) const
{
	return (m_nYear        != cTime.m_nYear       ||
			m_nMonth       != cTime.m_nMonth      ||
			m_nDayOfMonth  != cTime.m_nDayOfMonth ||
			m_nDayOfWeek   != cTime.m_nDayOfWeek  ||
			m_nHour        != cTime.m_nHour       ||
			m_nMinute      != cTime.m_nMinute     ||
			m_nSecond      != cTime.m_nSecond     ||
			m_nMillisecond != cTime.m_nMillisecond);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
