/*********************************************************\
 *  File: General.cpp                                    *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLTest/TestManager.h>
#include "PLTestBase/General/TimeTest.h"
#include "PLTestBase/General/UTF8ToolsTest.h"
#include "PLTestBase/General/SingletonTest.h"
#include "PLTestBase/General/XmlTest.h"
#include "PLTestBase/General/QuickSortTest.h"
#include "PLTestBase/General/MultiThreadingTest.h"
#include "PLTestBase/General/TokenizerTest.h"
#include "PLTestBase/General/SystemTest.h"


//[-------------------------------------------------------]
//[ Functions                                             ]
//[-------------------------------------------------------]
/**
*  @brief
*    General tests
*/
void GeneralTests()
{
	// Perform the test cases
	TestManager cTestManager("PLCore");
	cTestManager.Perform(new TimeTest());
	cTestManager.Perform(new UTF8ToolsTest());
	cTestManager.Perform(new SingletonTest());
	cTestManager.Perform(new XmlTest());
	cTestManager.Perform(new QuickSortTest());
	cTestManager.Perform(new MultiThreadingTest());
	cTestManager.Perform(new TokenizerTest());
	cTestManager.Perform(new SystemTest());

	// [TEST]
//	cTestManager.Perform(new PerformanceTest());
}
