/*********************************************************\
 *  File: wchar_template.h                                 *
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

#ifndef __PLUNITTESTS_UNITTESTADDINS_WCHAR_TEMPLATE_H_
#define __PLUNITTESTS_UNITTESTADDINS_WCHAR_TEMPLATE_H_
#pragma once

//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <UnitTest++/TestDetails.h>
#include <UnitTest++/TestResults.h>

// forward declarations needed
class TestResults;
class TestDetails;

//[-------------------------------------------------------]
//[ Declarations                                          ]
//[-------------------------------------------------------]

// adds specialization functions to CheckEqual Template with wchar_t support 
namespace UnitTest {
	void CheckWcharEqual(TestResults& results, wchar_t const* expected, wchar_t const* actual, 
		TestDetails const& details);
	void CheckEqual(TestResults& results, wchar_t const* expected, wchar_t const* actual, TestDetails const& details);
	void CheckEqual(TestResults& results, wchar_t* expected, wchar_t* actual, TestDetails const& details);
	void CheckEqual(TestResults& results, wchar_t* expected, wchar_t const* actual, TestDetails const& details);
	void CheckEqual(TestResults& results, wchar_t const* expected, wchar_t* actual, TestDetails const& details);
}

#endif __PLUNITTESTS_UNITTESTADDINS_WCHAR_TEMPLATE_H_
