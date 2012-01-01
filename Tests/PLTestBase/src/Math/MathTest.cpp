/*********************************************************\
 *  File: MathTest.cpp                                   *
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
#include <PLMath/Math.h>
#include "PLTestBase/Math/MathTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLMath;


//[-------------------------------------------------------]
//[ MathTest implementation                               ]
//[-------------------------------------------------------]
const char *MathTest::GetName() const
{
	return "Math";
}

void MathTest::Test()
{
	// IsPowerOfTwo()
	StartTask("IsPowerOfTwo()");
	EndTask(Math::IsPowerOfTwo(8) && !Math::IsPowerOfTwo(3));

	// GetNearestPowerOfTwo()
	StartTask("GetNearestPowerOfTwo()");
	EndTask(Math::GetNearestPowerOfTwo(5, true)  == 4 && Math::GetNearestPowerOfTwo(15, true)  == 8 &&
			Math::GetNearestPowerOfTwo(5, false) == 8 && Math::GetNearestPowerOfTwo(15, false) == 16);

	// AreEqual()
	StartTask("AreEqual()");
	EndTask(Math::AreEqual(4.0f, 4.0f) && Math::AreEqual(4.0f, 3.9f, 0.1f) &&
			!Math::AreEqual(4.0f, 3.89f, 0.1f));

	// Min(float, float)
	StartTask("Min(float, float)");
	EndTask(Math::Min(1.0f, 2.0f) == 1.0f && Math::Min(2.0f, 1.0f) == 1.0f);

	// Max(float, float)
	StartTask("Max(float, float)");
	EndTask(Math::Max(1.0f, 2.0f) == 2.0f && Math::Max(2.0f, 1.0f) == 2.0f);

	// Min(float, float, float, float)
	StartTask("Min(float, float, float, float)");
	EndTask(Math::Min(1.0f, 2.0f, 3.0f, 4.0f) == 1.0f && Math::Min(4.0f, 3.0f, 2.0f, 1.0f) == 1.0f);

	// Max(float, float, float, float)
	StartTask("Max(float, float, float, float)");
	EndTask(Math::Max(1.0f, 2.0f, 3.0f, 4.0f) == 4.0f && Math::Max(4.0f, 3.0f, 2.0f, 1.0f) == 4.0f);

	// Sign()
	StartTask("Sign()");
	EndTask(Math::Sign(1.0f) == 1.0f && Math::Sign(-1.0f) == -1.0f && Math::Sign(0.0f) == 1.0f);

	// Abs(float)
	StartTask("Abs(float)");
	EndTask(Math::Abs(1.0f) == 1.0f && Math::Abs(-1.0f) == 1.0f && Math::Abs(0.0f) == 0.0f);

	// Abs(double)
	StartTask("Abs(double)");
	EndTask(Math::Abs(1.0) == 1.0 && Math::Abs(-1.0) == 1.0 && Math::Abs(0.0) == 0.0);

	// Swap()
	StartTask("Swap()");
	float a = 1.0f;
	float b = 2.0f;
	Math::Swap(a, b);
	EndTask(a == 2.0f && b == 1.0f);
}
