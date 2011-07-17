/*********************************************************\
 *  File: TimeTest.cpp                                   *
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Tools/Time.h>
#include "PLTestBase/General/TimeTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *TimeTest::GetName() const
{
	return "Time";
}

//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void TimeTest::Test()
{
	String sTime;
	bool bResult;
	Time cTime;

	// Time() and Null constant
	StartTask("Time() and Null constant");
	EndTask(cTime == Time::Null);

	// SetUnixDate()
	StartTask("SetUnixDate()");
	bResult = true;
	cTime.SetUnixDate(0);
	if (cTime != Time::UnixEpochStart) bResult = false;
	cTime.SetUnixDate(1141408532);
	if (cTime != Time(2006, Time::March, 3, Time::Friday, 0, 51, 20, 0)) bResult = false;
	EndTask(bResult);

	// SetDOSDate()
	StartTask("SetDOSDate()");
	cTime.SetDOSDate(0);
	if (cTime != Time::DOSEpochStart) bResult = false;
	EndTask(bResult);

	// ToString()
	StartTask("ToString()");
	EndTask(cTime.Null          .ToString() == "Sun Jan  1 00:00:00 0"    &&
			cTime.UnixEpochStart.ToString() == "Thu Jan  1 00:00:00 1970" &&
			cTime.DOSEpochStart. ToString() == "Tue Jan  1 00:00:00 1980");
}
