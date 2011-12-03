/*********************************************************\
 *  File: Time.inl                                       *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
inline Time::~Time()
{
}

/**
*  @brief
*    Get the year
*/
inline uint16 Time::GetYear() const
{
	return m_nYear;
}

/**
*  @brief
*    Set the year
*/
inline void Time::SetYear(uint16 nYear)
{
	m_nYear = nYear;
}

/**
*  @brief
*    Get the month
*/
inline Time::EMonth Time::GetMonth() const
{
	return m_nMonth;
}

/**
*  @brief
*    Set the month
*/
inline void Time::SetMonth(EMonth nMonth)
{
	m_nMonth = nMonth;
}

/**
*  @brief
*    Get the day of the month
*/
inline uint8 Time::GetDayOfMonth() const
{
	return m_nDayOfMonth;
}

/**
*  @brief
*    Set the day of the month
*/
inline void Time::SetDayOfMonth(uint8 nDayOfMonth)
{
	if (nDayOfMonth >= 1 && nDayOfMonth <= 31)
		m_nDayOfMonth = nDayOfMonth;
}

/**
*  @brief
*    Get the day of the week
*/
inline Time::EDay Time::GetDayOfWeek() const
{
	return m_nDayOfWeek;
}

/**
*  @brief
*    Set the day of the week
*/
inline void Time::SetDayOfWeek(EDay nDayOfWeek)
{
	m_nDayOfWeek = nDayOfWeek;
}

/**
*  @brief
*    Get the hour
*/
inline uint8 Time::GetHour() const
{
	return m_nHour;
}

/**
*  @brief
*    Set the hour
*/
inline void Time::SetHour(uint8 nHour)
{
	if (nHour <= 23)
		m_nHour = nHour;
}

/**
*  @brief
*    Get the minute
*/
inline uint8 Time::GetMinute() const
{
	return m_nMinute;
}

/**
*  @brief
*    Set the minute
*/
inline void Time::SetMinute(uint8 nMinute)
{
	if (nMinute <= 59)
		m_nMinute = nMinute;
}

/**
*  @brief
*    Get the second
*/
inline uint8 Time::GetSecond() const
{
	return m_nSecond;
}

/**
*  @brief
*    Set the second
*/
inline void Time::SetSecond(uint8 nSecond)
{
	if (nSecond <= 59)
		m_nSecond = nSecond;
}

/**
*  @brief
*    Get the millisecond
*/
inline uint16 Time::GetMillisecond() const
{
	return m_nMillisecond;
}

/**
*  @brief
*    Set the millisecond
*/
inline void Time::SetMillisecond(uint16 nMillisecond)
{
	if (nMillisecond <= 999)
		m_nMillisecond = nMillisecond;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
