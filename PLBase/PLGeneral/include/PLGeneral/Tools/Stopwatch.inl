/*********************************************************\
 *  File: Stopwatch.inl                                  *
 *      Stopwatch inline implementation
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
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
inline Stopwatch::Stopwatch() :
	m_bRunning(false),
	m_nStart(0),
	m_nStop(0)
{
}

/**
*  @brief
*    Destructor
*/
inline Stopwatch::~Stopwatch()
{
}

/**
*  @brief
*    Returns the number of weeks since the stopwatch was started
*/
inline float Stopwatch::GetWeeks() const
{
	return GetDays()/7.0f;
}

/**
*  @brief
*    Returns the number of days since the stopwatch was started
*/
inline float Stopwatch::GetDays() const
{
	return GetHours()/24.0f;
}

/**
*  @brief
*    Returns the number of hours since the stopwatch was started
*/
inline float Stopwatch::GetHours() const
{
	return GetMinutes()/60.0f;
}

/**
*  @brief
*    Returns the number of minutes since the stopwatch was started
*/
inline float Stopwatch::GetMinutes() const
{
	return GetSeconds()/60.0f;
}

/**
*  @brief
*    Returns the number of seconds since the stopwatch was started
*/
inline float Stopwatch::GetSeconds() const
{
	return GetMilliseconds()/1000.0f;
}

/**
*  @brief
*    Returns the number of milliseconds since the stopwatch was started
*/
inline float Stopwatch::GetMilliseconds() const
{
	return GetMicroseconds()/1000.0f;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
