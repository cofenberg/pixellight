/*********************************************************\
 *  File: General.cpp                                    *
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
#include <PLTest/TestManager.h>
#include "PLTestBase/General/TimeTest.h"
#include "PLTestBase/General/StackTest.h"
#include "PLTestBase/General/QueueTest.h"
#include "PLTestBase/General/UTF8ToolsTest.h"
#include "PLTestBase/General/StringTest.h"
#include "PLTestBase/General/ListTest.h"
#include "PLTestBase/General/SimpleListTest.h"
#include "PLTestBase/General/ArrayTest.h"
#include "PLTestBase/General/PoolTest.h"
#include "PLTestBase/General/FastPoolTest.h"
#include "PLTestBase/General/BitsetTest.h"
#include "PLTestBase/General/SimpleMapTest.h"
#include "PLTestBase/General/HashMapTest.h"
#include "PLTestBase/General/BinaryHeapTest.h"
#include "PLTestBase/General/BinominalHeapTest.h"
#include "PLTestBase/General/FibonacciHeapTest.h"
#include "PLTestBase/General/SingletonTest.h"
#include "PLTestBase/General/XmlTest.h"
#include "PLTestBase/General/QuickSortTest.h"
#include "PLTestBase/General/PerformanceTest.h"
#include "PLTestBase/General/FileSystemTest.h"
#include "PLTestBase/General/MultiThreadingTest.h"
#include "PLTestBase/General/TokenizerTest.h"
#include "PLTestBase/General/SystemTest.h"
#include "PLTestBase/General/ChecksumTest.h"
#include "PLTestBase/General/LogTest.h"


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
	TestManager cTestManager("PLGeneral");
	cTestManager.Perform(new TimeTest());
	cTestManager.Perform(new StackTest());
	cTestManager.Perform(new QueueTest());
	cTestManager.Perform(new UTF8ToolsTest());
	cTestManager.Perform(new StringTest());
	cTestManager.Perform(new ListTest());
	cTestManager.Perform(new SimpleListTest());
	cTestManager.Perform(new ArrayTest());
	cTestManager.Perform(new PoolTest());
	cTestManager.Perform(new FastPoolTest());
	cTestManager.Perform(new BitsetTest());
	cTestManager.Perform(new SimpleMapTest());
	cTestManager.Perform(new HashMapTest());
	cTestManager.Perform(new BinaryHeapTest());
	cTestManager.Perform(new BinominalHeapTest());
	cTestManager.Perform(new FibonacciHeapTest());
	cTestManager.Perform(new SingletonTest());
	cTestManager.Perform(new XmlTest());
	cTestManager.Perform(new QuickSortTest());
	cTestManager.Perform(new FileSystemTest());
	cTestManager.Perform(new MultiThreadingTest());
	cTestManager.Perform(new TokenizerTest());
	cTestManager.Perform(new SystemTest());
	cTestManager.Perform(new ChecksumTest());
	cTestManager.Perform(new LogTest());

	// [TEST]
//	cTestManager.Perform(new PerformanceTest());
}
