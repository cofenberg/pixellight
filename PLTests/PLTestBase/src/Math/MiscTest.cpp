/*********************************************************\
 *  File: MiscTest.cpp                                   *
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
#include <PLMath/Math.h>
#include "PLTestBase/Math/MiscTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLMath;


//[-------------------------------------------------------]
//[ MiscTest implementation                               ]
//[-------------------------------------------------------]
const char *MiscTest::GetName() const
{
	return "Misc";
}

void MiscTest::Test()
{
	double dDouble;
	bool bResult;
	float fFloat;

	// Degree to Radian & Radian to Degree
	StartTask("Degree to Radian & Radian to Degree");
	bResult = true;
	// Degree to Radian
	fFloat = float(50.0f*Math::DegToRad);
	if (!Math::AreEqual(float(fFloat*Math::RadToDeg), 50.0f)) bResult = false;
	dDouble = 50.0*Math::DegToRad;
	if (!Math::AreEqual(dDouble*Math::RadToDeg, 50.0)) bResult = false;
	// Radian to Degree
	fFloat = float(50.0f*Math::RadToDeg);
	if (!Math::AreEqual(float(fFloat*Math::DegToRad), 50.0f)) bResult = false;
	dDouble = 50.0*Math::RadToDeg;
	if (!Math::AreEqual(dDouble*Math::DegToRad, 50.0)) bResult = false;
	EndTask(bResult);
}

