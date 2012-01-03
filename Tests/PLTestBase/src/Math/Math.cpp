/*********************************************************\
 *  File: Math.cpp                                       *
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
#include "PLTestBase/Math/MiscTest.h"
#include "PLTestBase/Math/MathTest.h"
#include "PLTestBase/Math/Vector2Test.h"
#include "PLTestBase/Math/Vector3Test.h"
#include "PLTestBase/Math/Vector4Test.h"
#include "PLTestBase/Math/Matrix3x3Test.h"
#include "PLTestBase/Math/Matrix3x4Test.h"
#include "PLTestBase/Math/Matrix4x4Test.h"
#include "PLTestBase/Math/QuaternionTest.h"
#include "PLTestBase/Math/EulerAnglesTest.h"
#include "PLTestBase/Math/GraphTest.h"
#include "PLTestBase/Math/GraphPathTest.h"
#include "PLTestBase/Math/MathClassTest.h"


//[-------------------------------------------------------]
//[ Functions                                             ]
//[-------------------------------------------------------]
/**
*  @brief
*    Math tests
*/
void MathTests()
{
	// Perform the test cases
	TestManager cTestManager("PLMath");
	cTestManager.Perform(new MiscTest());
	cTestManager.Perform(new MathTest());
	cTestManager.Perform(new Vector2Test());
	cTestManager.Perform(new Vector3Test());
	cTestManager.Perform(new Vector4Test());
	cTestManager.Perform(new Matrix3x3Test());
	cTestManager.Perform(new Matrix3x4Test());
	cTestManager.Perform(new Matrix4x4Test());
	cTestManager.Perform(new QuaternionTest());
	cTestManager.Perform(new EulerAnglesTest());
	cTestManager.Perform(new GraphTest());
	cTestManager.Perform(new GraphPathTest());
	cTestManager.Perform(new MathClassTest());
}
