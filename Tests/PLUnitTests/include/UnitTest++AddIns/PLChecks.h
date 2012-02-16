/*********************************************************\
*  File: PLChecks.h
*
*  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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

#ifndef __PLCHECKS_H_
#define __PLCHECKS_H_
#pragma once

#include <UnitTest++/UnitTest++.h>
#include <UnitTest++/TestResults.h>
#include <PLMath/Matrix3x3.h>

namespace UnitTest {
	void CheckMatrix3x3(TestResults& results, PLMath::Matrix3x3 const& expected, PLMath::Matrix3x3 const& actual, float const& tolerance,
		TestDetails const& details);

	void CheckMissingImplementation(TestResults& results, TestDetails const& details);
}

#endif // __PLCHECKS_H_
