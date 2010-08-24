/*********************************************************\
 *  File: EulerAnglesTest.cpp                            *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLMath/Matrix3x3.h>
#include <PLMath/Quaternion.h>
#include <PLMath/EulerAngles.h>
#include "PLTestBase/Math/EulerAnglesTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLMath;


//[-------------------------------------------------------]
//[ EulerAnglesTest implementation                        ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Matrix3x3Test implementation                          ]
//[-------------------------------------------------------]
bool EulerAnglesTest::CheckEulerAngleX(float fAngle, float fExpectedAngle)
{
	float fAngleX, fAngleY, fAngleZ;
	Matrix3x3 mRot;
	Quaternion qRot;

	// Degree to radian
	fAngle         = float(fAngle*Math::DegToRad);
	fExpectedAngle = float(fExpectedAngle*Math::DegToRad);

	// FromEulerAngleX() & FromMatrix()
	mRot.FromEulerAngleX(fAngle);
	EulerAngles::FromMatrix(mRot, fAngleX, fAngleY, fAngleZ);
	if (!Math::AreEqual(fAngleX, fExpectedAngle) || fAngleY != 0.0f || fAngleZ != 0.0f) return false; // Error!

	// The other functions must return the same values...
	Matrix3x3 mRotT;
	EulerAngles::ToMatrix(fAngle, 0.0f, 0.0f, mRot);
	if (mRot != mRotT) return false; // Error!

	// ToQuaternion() & FromQuaternion()
	EulerAngles::ToQuaternion(fAngle, 0.0f, 0.0f, qRot);
	EulerAngles::FromQuaternion(qRot, fAngleX, fAngleY, fAngleZ);
	if (!Math::AreEqual(fAngleX, fExpectedAngle) || fAngleY != 0.0f || fAngleZ != 0.0f) return false; // Error!

	// Success
	return true;
}

bool EulerAnglesTest::CheckEulerAngleY(float fAngle, float fExpectedAngle)
{
	float fAngleX, fAngleY, fAngleZ;
	Matrix3x3 mRot;
	Quaternion qRot;

	// Degree to radian
	fAngle         = float(fAngle*Math::DegToRad);
	fExpectedAngle = float(fExpectedAngle*Math::DegToRad);

	// FromEulerAngleY() & FromMatrix()
	mRot.FromEulerAngleY(fAngle);
	EulerAngles::FromMatrix(mRot, fAngleX, fAngleY, fAngleZ);
	if (fAngleX != 0.0f || !Math::AreEqual(fAngleY, fExpectedAngle) || fAngleZ != 0.0f) return false; // Error!

	// The other functions must return the same values...
	Matrix3x3 mRotT;
	EulerAngles::ToMatrix(0.0f, fAngle, 0.0f, mRot);
	if (mRot != mRotT) return false; // Error!

	// ToQuaternion() & FromQuaternion()
	EulerAngles::ToQuaternion(0.0f, fAngle, 0.0f, qRot);
	EulerAngles::FromQuaternion(qRot, fAngleX, fAngleY, fAngleZ);
	if (fAngleX != 0.0f || !Math::AreEqual(fAngleY, fExpectedAngle) || fAngleZ != 0.0f) return false; // Error!

	// Success
	return true;
}

bool EulerAnglesTest::CheckEulerAngleZ(float fAngle, float fExpectedAngle)
{
	float fAngleX, fAngleY, fAngleZ;
	Matrix3x3 mRot;
	Quaternion qRot;

	// Degree to radian
	fAngle         = float(fAngle*Math::DegToRad);
	fExpectedAngle = float(fExpectedAngle*Math::DegToRad);

	// FromEulerAngleZ() & FromMatrix()
	mRot.FromEulerAngleZ(fAngle);
	EulerAngles::FromMatrix(mRot, fAngleX, fAngleY, fAngleZ);
	if (fAngleX != 0.0f || fAngleY != 0.0f || !Math::AreEqual(fAngleZ, fExpectedAngle)) return false; // Error!

	// The other functions must return the same values...
	Matrix3x3 mRotT;
	EulerAngles::ToMatrix(0.0f, 0.0f, fAngle, mRot);
	if (mRot != mRotT) return false; // Error!

	// ToQuaternion() & FromQuaternion()
	EulerAngles::ToQuaternion(0.0f, 0.0f, fAngle, qRot);
	EulerAngles::FromQuaternion(qRot, fAngleX, fAngleY, fAngleZ);
	if (fAngleX != 0.0f || fAngleY != 0.0f || !Math::AreEqual(fAngleZ, fExpectedAngle)) return false; // Error!

	// Success
	return true;
}


//[-------------------------------------------------------]
//[ Virtual TestCase functions                            ]
//[-------------------------------------------------------]
const char *EulerAnglesTest::GetName() const
{
	return "EulerAnglesTest";
}

void EulerAnglesTest::Test()
{
	// [TODO] Check this tests
	StartTask("Euler angles");
	bool bResult = true;
	// Check only x rotation
	if (!CheckEulerAngleX(   0.0f,   0.0f)) bResult = false;
	if (!CheckEulerAngleX(  45.0f,  45.0f)) bResult = false;
	if (!CheckEulerAngleX( -45.0f, 315.0f)) bResult = false;
	if (!CheckEulerAngleX(  90.0f,  90.0f)) bResult = false;
	if (!CheckEulerAngleX( -90.0f, 270.0f)) bResult = false;
	if (!CheckEulerAngleX( 135.0f, 135.0f)) bResult = false;
	if (!CheckEulerAngleX( 180.0f, 180.0f)) bResult = false;
	if (!CheckEulerAngleX(-180.0f, 180.0f)) bResult = false;
	if (!CheckEulerAngleX( 225.0f, 225.0f)) bResult = false;
	if (!CheckEulerAngleX( 270.0f, 270.0f)) bResult = false;
	if (!CheckEulerAngleX( 315.0f, 315.0f)) bResult = false;
	if (!CheckEulerAngleX( 360.0f,   0.0f)) bResult = false;
	// Check only y rotation
	if (!CheckEulerAngleY(   0.0f,   0.0f)) bResult = false;
	if (!CheckEulerAngleY(  45.0f,  45.0f)) bResult = false;
	if (!CheckEulerAngleY( -45.0f, 315.0f)) bResult = false;
	if (!CheckEulerAngleY(  90.0f,  90.0f)) bResult = false;
	if (!CheckEulerAngleY( -90.0f, 270.0f)) bResult = false;
	if (!CheckEulerAngleY( 110.0f, 110.0f)) bResult = false;
	if (!CheckEulerAngleY( 135.0f, 135.0f)) bResult = false;
	if (!CheckEulerAngleY( 180.0f, 180.0f)) bResult = false;
	if (!CheckEulerAngleY(-180.0f, 180.0f)) bResult = false;
	if (!CheckEulerAngleY( 225.0f, 225.0f)) bResult = false;
	if (!CheckEulerAngleY( 260.0f, 260.0f)) bResult = false;
	if (!CheckEulerAngleY( 270.0f, 270.0f)) bResult = false;
	if (!CheckEulerAngleY( 315.0f, 315.0f)) bResult = false;
	if (!CheckEulerAngleY( 360.0f,   0.0f)) bResult = false;
	// Check only z rotation
	if (!CheckEulerAngleZ(   0.0f,   0.0f)) bResult = false;
	if (!CheckEulerAngleZ(  45.0f,  45.0f)) bResult = false;
	if (!CheckEulerAngleZ( -45.0f, 315.0f)) bResult = false;
	if (!CheckEulerAngleZ(  90.0f,  90.0f)) bResult = false;
	if (!CheckEulerAngleZ( -90.0f, 270.0f)) bResult = false;
	if (!CheckEulerAngleZ( 135.0f, 135.0f)) bResult = false;
	if (!CheckEulerAngleZ( 180.0f, 180.0f)) bResult = false;
	if (!CheckEulerAngleZ(-180.0f, 180.0f)) bResult = false;
	if (!CheckEulerAngleZ( 225.0f, 225.0f)) bResult = false;
	if (!CheckEulerAngleZ( 270.0f, 270.0f)) bResult = false;
	if (!CheckEulerAngleZ( 315.0f, 315.0f)) bResult = false;
	if (!CheckEulerAngleZ( 360.0f,   0.0f)) bResult = false;
	EndTask(bResult);
}
