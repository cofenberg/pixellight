/*********************************************************\
 *  File: RunAllTests.h                                 *
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

#ifndef __PLUNITTESTS_UNITTESTADDINS_RUNALLTESTS_H_
#define __PLUNITTESTS_UNITTESTADDINS_RUNALLTESTS_H_
#pragma once

//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <UnitTest++/TestReporterStdout.h>
#include <UnitTest++/TestRunner.h>

#include <UnitTest++AddIns/MyTestReporter.h>

//[-------------------------------------------------------]
//[ Declarations                                          ]
//[-------------------------------------------------------]


namespace UnitTest {
	// overload to RunAllTests to use given SuiteName and TestReporter
	int RunAllTests(TestReporter& rep, char* const SuiteName = NULL);
}

#endif // __PLUNITTESTS_UNITTESTADDINS_RUNALLTESTS_H_
