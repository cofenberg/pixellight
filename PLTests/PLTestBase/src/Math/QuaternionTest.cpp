/*********************************************************\
 *  File: QuaternionTest.cpp                             *
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
#include <PLMath/Matrix3x3.h>
#include <PLMath/Matrix4x4.h>
#include <PLMath/Quaternion.h>
#include <PLMath/EulerAngles.h>
#include "PLTestBase/Math/QuaternionTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLMath;


//[-------------------------------------------------------]
//[ QuaternionTest implementation                         ]
//[-------------------------------------------------------]
bool QuaternionTest::CheckAxisAngle(float fX, float fY, float fZ, float fAngle, float fExpectedAngle)
{
	float fXT, fYT, fZT, fAngleT;
	Quaternion qQ;

	// Degree to radian
	fAngle         = static_cast<float>(fAngle*Math::DegToRad);
	fExpectedAngle = static_cast<float>(fExpectedAngle*Math::DegToRad);

	qQ.FromAxisAngle(fX, fY, fZ, fAngle);
	qQ.ToAxisAngle(fXT, fYT, fZT, fAngleT);
	if (Math::AreEqual(fX, fXT) && Math::AreEqual(fY, fYT) && Math::AreEqual(fZ, fZT) &&
		Math::AreEqual(fAngleT, fExpectedAngle))
		return true; // Success
	else return false; // Error!
}

bool QuaternionTest::CheckFromRotationMatrix3x3(float fAngleX, float fAngleY, float fAngleZ)
{
	// Degree to radian
	fAngleX = static_cast<float>(fAngleX*Math::DegToRad);
	fAngleY = static_cast<float>(fAngleY*Math::DegToRad);
	fAngleZ = static_cast<float>(fAngleZ*Math::DegToRad);

	Quaternion qQ, qQT;
	Matrix3x3 m3x3;
	EulerAngles::ToMatrix(fAngleX, fAngleY, fAngleZ, m3x3);
	qQ.FromRotationMatrix(m3x3);
	EulerAngles::ToQuaternion(fAngleX, fAngleY, fAngleZ, qQT);
	return qQ.Compare(qQT);
}

bool QuaternionTest::CheckToRotationMatrix3x3(float fAngleX, float fAngleY, float fAngleZ)
{
	// Degree to radian
	fAngleX = static_cast<float>(fAngleX*Math::DegToRad);
	fAngleY = static_cast<float>(fAngleY*Math::DegToRad);
	fAngleZ = static_cast<float>(fAngleZ*Math::DegToRad);

	Matrix3x3 m3x3, mT3x3;
	Quaternion qQ;
	EulerAngles::ToMatrix(fAngleX, fAngleY, fAngleZ, m3x3);
	EulerAngles::ToQuaternion(fAngleX, fAngleY, fAngleZ, qQ);
	qQ.ToRotationMatrix(mT3x3);
	return m3x3.CompareRotation(mT3x3);
}

bool QuaternionTest::CheckFromRotationMatrix4x4(float fAngleX, float fAngleY, float fAngleZ)
{
	// Degree to radian
	fAngleX = static_cast<float>(fAngleX*Math::DegToRad);
	fAngleY = static_cast<float>(fAngleY*Math::DegToRad);
	fAngleZ = static_cast<float>(fAngleZ*Math::DegToRad);

	Quaternion qQ, qQT;
	Matrix4x4 m4x4;
	EulerAngles::ToMatrix(fAngleX, fAngleY, fAngleZ, m4x4);
	qQ.FromRotationMatrix(m4x4);
	EulerAngles::ToQuaternion(fAngleX, fAngleY, fAngleZ, qQT);
	return qQ.Compare(qQT);
}

bool QuaternionTest::CheckToRotationMatrix4x4(float fAngleX, float fAngleY, float fAngleZ)
{
	// Degree to radian
	fAngleX = static_cast<float>(fAngleX*Math::DegToRad);
	fAngleY = static_cast<float>(fAngleY*Math::DegToRad);
	fAngleZ = static_cast<float>(fAngleZ*Math::DegToRad);

	Matrix4x4 m4x4, mT4x4;
	Quaternion qQ;
	EulerAngles::ToMatrix(fAngleX, fAngleY, fAngleZ, m4x4);
	EulerAngles::ToQuaternion(fAngleX, fAngleY, fAngleZ, qQ);
	qQ.ToRotationMatrix(mT4x4);
	return m4x4.CompareRotation(mT4x4);
}


//[-------------------------------------------------------]
//[ Virtual TestCase functions                            ]
//[-------------------------------------------------------]
const char *QuaternionTest::GetName() const
{
	return "Quaternion";
}

void QuaternionTest::Test()
{
	float fT4[4] = {2.0f, 3.0f, 4.0f, 5.0f};
	Matrix3x3 m3x3;
	Matrix4x4 m4x4;
	Quaternion qQ;
	bool bResult;
	Vector3 vV3;

	// Quaternion constructors & copy
	StartTask("Quaternion constructors & copy");
	bResult = true;
	// Quaternion must be identity
	if (qQ.w != 1.0f || qQ.x != 0.0f || qQ.y != 0.0f || qQ.z != 0.0f) bResult = false;
	qQ = Quaternion(0.0f, 1.0f, 2.0f, 3.0f);
	if (qQ.w != 0.0f || qQ.x != 1.0f || qQ.y != 2.0f || qQ.z != 3.0f) bResult = false;
	qQ = Quaternion(Quaternion(5.0f, 6.0f, 7.0f, 8.0f));
	if (qQ.w != 5.0f || qQ.x != 6.0f || qQ.y != 7.0f || qQ.z != 8.0f) bResult = false;
	/* [TODO]
		PLMATH_API Quaternion(float fAngleX, float fAngleY, float fAngleZ);
		PLMATH_API Quaternion(const Vector3 &vAngle);
		PLMATH_API Quaternion(const Vector3 &vAxis, float fAngle);
		PLMATH_API Quaternion(const Matrix3x3 &mRot);
		PLMATH_API Quaternion(const Matrix4x4 &mRot);
	*/
	EndTask(bResult);

	// Static variables
	StartTask("Static variables");
	bResult = true;
	if (Quaternion::Zero.w != 0.0f || Quaternion::Zero.x != 0.0f || 
		Quaternion::Zero.y != 0.0f || Quaternion::Zero.z != 0.0f) bResult = false;
	if (Quaternion::Identity.w != 1.0f || Quaternion::Identity.x != 0.0f || 
		Quaternion::Identity.y != 0.0f || Quaternion::Identity.z != 0.0f) bResult = false;
	EndTask(bResult);


// Operators
	// Quaternion*Vector3
	StartTask("Quaternion*Vector3");
	bResult = true;
	// 90°
	vV3 = Vector3(1.0f, 0.0f, 0.0f);
	EulerAngles::ToQuaternion(0.0f, static_cast<float>(90.0f*Math::DegToRad), 0.0f, qQ);
	vV3 = qQ*vV3;
	if (!Math::AreEqual(vV3.x, 0.0f) || !Math::AreEqual(vV3.y, 0.0f) || !Math::AreEqual(vV3.z, -1.0f)) bResult = false;
	// -90°
	vV3 = Vector3(1.0f, 0.0f, 0.0f);
	EulerAngles::ToQuaternion(0.0f, -static_cast<float>(90.0f*Math::DegToRad), 0.0f, qQ);
	vV3 = qQ*vV3;
	if (!Math::AreEqual(vV3.x, 0.0f) || !Math::AreEqual(vV3.y, 0.0f) || !Math::AreEqual(vV3.z, 1.0f)) bResult = false;
	EndTask(bResult);

	/*

		//[-------------------------------------------------------]
		//[ Operators                                             ]
		//[-------------------------------------------------------]
		PLMATH_API Quaternion  operator +(const Quaternion &qQ) const;
		PLMATH_API Quaternion &operator +=(const Quaternion &qQ);
		PLMATH_API Quaternion  operator -() const;
		PLMATH_API Quaternion  operator -(const Quaternion &qQ) const;
		PLMATH_API Quaternion &operator -=(const Quaternion &qQ);
		PLMATH_API Quaternion  operator *(float f) const;
		PLMATH_API Quaternion &operator *=(float f);
		PLMATH_API Quaternion  operator *(const Quaternion &qQ) const;
		PLMATH_API Quaternion &operator *=(const Quaternion &qQ);
		PLMATH_API Vector3     operator *(const Vector3 &vV) const;
		PLMATH_API Vector4     operator *(const Vector4 &vV) const;
		PLMATH_API Quaternion  operator /(float f) const;
		PLMATH_API Quaternion &operator /=(float f);
		PLMATH_API Quaternion &operator =(const Quaternion &qQ);
		PLMATH_API bool        operator ==(const Quaternion &qQ) const;
		PLMATH_API bool        operator !=(const Quaternion &qQ) const;
		PLMATH_API             operator float *() const;
		PLMATH_API             operator const float *() const;
	*/


// Get and set functions
	// SetWXYZ(float, float, float, float)
	StartTask("SetWXYZ(float, float, float, float)");
	qQ = Quaternion::Identity;
	qQ.SetWXYZ(2.0f, 3.0f, 4.0f, 5.0f);
	EndTask(qQ.w == 2.0f && qQ.x == 3.0f && qQ.y == 4.0f && qQ.z == 5);

	// SetWXYZ(float*)
	StartTask("SetWXYZ(float*)");
	qQ = Quaternion::Identity;
	qQ.SetWXYZ(fT4);
	EndTask(qQ.w == 2.0f && qQ.x == 3.0f && qQ.y == 4.0f && qQ.z == 5);

	// ToAxisAngle() and FromAxisAngle()
	StartTask("ToAxisAngle() and FromAxisAngle()");
	bResult = true;
	// Check only x rotation
	// [TODO] Some tests will fail...
//	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f,   0.0f,   0.0f)) bResult = false;
	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f,  45.0f,  45.0f)) bResult = false;
//	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f, -45.0f,  45.0f)) bResult = false;
	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f,  90.0f,  90.0f)) bResult = false;
	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f, 135.0f, 135.0f)) bResult = false;
	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f, 180.0f, 180.0f)) bResult = false;
	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f, 225.0f, 225.0f)) bResult = false;
	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f, 270.0f, 270.0f)) bResult = false;
	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f, 315.0f, 315.0f)) bResult = false;
//	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f, 360.0f, 360.0f)) bResult = false;
	// Check only y rotation
//	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f,   0.0f,   0.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f,  45.0f,  45.0f)) bResult = false;
//	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, -45.0f,  45.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f,  90.0f,  90.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, 135.0f, 135.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, 180.0f, 180.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, 225.0f, 225.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, 270.0f, 270.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, 315.0f, 315.0f)) bResult = false;
//	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, 360.0f, 360.0f)) bResult = false;
	// Check only z rotation
//	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f,   0.0f,   0.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f,  45.0f,  45.0f)) bResult = false;
//	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, -45.0f,  45.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f,  90.0f,  90.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, 135.0f, 135.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, 180.0f, 180.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, 225.0f, 225.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, 270.0f, 270.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, 315.0f, 315.0f)) bResult = false;
	// [TODO] Sign troubles...
//	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, 360.0f, 360.0f)) bResult = false;
	EndTask(bResult);

	// GetXAxis()
	StartTask("GetXAxis()");
	bResult = true;
	vV3 = Quaternion::Identity.GetXAxis();
	if (vV3.x != 1.0f || vV3.y != 0.0f || vV3.z != 0.0f) bResult = false;
	EndTask(bResult);

	// GetYAxis()
	StartTask("GetYAxis()");
	bResult = true;
	vV3 = Quaternion::Identity.GetYAxis();
	if (vV3.x != 0.0f || vV3.y != 1.0f || vV3.z != 0.0f) bResult = false;
	EndTask(bResult);

	// GetZAxis()
	StartTask("GetZAxis()");
	bResult = true;
	vV3 = Quaternion::Identity.GetZAxis();
	if (vV3.x != 0.0f || vV3.y != 0.0f || vV3.z != 1.0f) bResult = false;
	EndTask(bResult);

	// FromRotationMatrix(Matrix3x3)
	StartTask("FromRotationMatrix(Matrix3x3)");
	bResult = true;
	// Identity
	qQ.FromRotationMatrix(Matrix3x3::Identity);
	if (!qQ.Compare(Quaternion::Identity)) bResult = false;
	bResult = true;
	// Check only x rotation
	if (!CheckFromRotationMatrix3x3(  45.0f, 0.0f, 0.0f)) bResult = false;
	if (!CheckFromRotationMatrix3x3( -45.0f, 0.0f, 0.0f)) bResult = false;
	if (!CheckFromRotationMatrix3x3( 210.0f, 0.0f, 0.0f)) bResult = false;
	if (!CheckFromRotationMatrix3x3(-210.0f, 0.0f, 0.0f)) bResult = false;
	// Check only y rotation
	if (!CheckFromRotationMatrix3x3(0.0f,   45.0f, 0.0f)) bResult = false;
	if (!CheckFromRotationMatrix3x3(0.0f,  -45.0f, 0.0f)) bResult = false;
	if (!CheckFromRotationMatrix3x3(0.0f,  210.0f, 0.0f)) bResult = false;
	if (!CheckFromRotationMatrix3x3(0.0f, -210.0f, 0.0f)) bResult = false;
	// Check only z rotation
	if (!CheckFromRotationMatrix3x3(0.0f, 0.0f,   45.0f)) bResult = false;
	if (!CheckFromRotationMatrix3x3(0.0f, 0.0f,  -45.0f)) bResult = false;
	if (!CheckFromRotationMatrix3x3(0.0f, 0.0f,  210.0f)) bResult = false;
	if (!CheckFromRotationMatrix3x3(0.0f, 0.0f, -210.0f)) bResult = false;
	EndTask(bResult);

	// ToRotationMatrix(Matrix3x3)
	StartTask("ToRotationMatrix(Matrix3x3)");
	bResult = true;
	// Identity
	Quaternion::Identity.ToRotationMatrix(m3x3);
	if (!Matrix3x3::Identity.CompareRotation(m3x3)) bResult = false;
	bResult = true;
	// Check only x rotation
	if (!CheckToRotationMatrix3x3(  45.0f, 0.0f, 0.0f)) bResult = false;
	if (!CheckToRotationMatrix3x3( -45.0f, 0.0f, 0.0f)) bResult = false;
	if (!CheckToRotationMatrix3x3( 210.0f, 0.0f, 0.0f)) bResult = false;
	if (!CheckToRotationMatrix3x3(-210.0f, 0.0f, 0.0f)) bResult = false;
	// Check only y rotation
	if (!CheckToRotationMatrix3x3(0.0f,   45.0f, 0.0f)) bResult = false;
	if (!CheckToRotationMatrix3x3(0.0f,  -45.0f, 0.0f)) bResult = false;
	if (!CheckToRotationMatrix3x3(0.0f,  210.0f, 0.0f)) bResult = false;
	if (!CheckToRotationMatrix3x3(0.0f, -210.0f, 0.0f)) bResult = false;
	// Check only z rotation
	if (!CheckToRotationMatrix3x3(0.0f, 0.0f,   45.0f)) bResult = false;
	if (!CheckToRotationMatrix3x3(0.0f, 0.0f,  -45.0f)) bResult = false;
	if (!CheckToRotationMatrix3x3(0.0f, 0.0f,  210.0f)) bResult = false;
	if (!CheckToRotationMatrix3x3(0.0f, 0.0f, -210.0f)) bResult = false;
	EndTask(bResult);

	// FromRotationMatrix(Matrix4x4)
	StartTask("FromRotationMatrix(Matrix4x4)");
	bResult = true;
	// Identity
	qQ.FromRotationMatrix(Matrix4x4::Identity);
	if (!qQ.Compare(Quaternion::Identity)) bResult = false;
	// Check only x rotation
	if (!CheckFromRotationMatrix4x4(  45.0f, 0.0f, 0.0f)) bResult = false;
	if (!CheckFromRotationMatrix4x4( -45.0f, 0.0f, 0.0f)) bResult = false;
	if (!CheckFromRotationMatrix4x4( 210.0f, 0.0f, 0.0f)) bResult = false;
	if (!CheckFromRotationMatrix4x4(-210.0f, 0.0f, 0.0f)) bResult = false;
	// Check only y rotation
	if (!CheckFromRotationMatrix4x4(0.0f,   45.0f, 0.0f)) bResult = false;
	if (!CheckFromRotationMatrix4x4(0.0f,  -45.0f, 0.0f)) bResult = false;
	if (!CheckFromRotationMatrix4x4(0.0f,  210.0f, 0.0f)) bResult = false;
	if (!CheckFromRotationMatrix4x4(0.0f, -210.0f, 0.0f)) bResult = false;
	// Check only z rotation
	if (!CheckFromRotationMatrix4x4(0.0f, 0.0f,   45.0f)) bResult = false;
	if (!CheckFromRotationMatrix4x4(0.0f, 0.0f,  -45.0f)) bResult = false;
	if (!CheckFromRotationMatrix4x4(0.0f, 0.0f,  210.0f)) bResult = false;
	if (!CheckFromRotationMatrix4x4(0.0f, 0.0f, -210.0f)) bResult = false;
	EndTask(bResult);

	// ToRotationMatrix(Matrix4x4)
	StartTask("ToRotationMatrix(Matrix4x4)");
	bResult = true;
	// Identity
	Quaternion::Identity.ToRotationMatrix(m4x4);
	if (!Matrix4x4::Identity.CompareRotation(m4x4)) bResult = false;
	// Check only x rotation
	if (!CheckToRotationMatrix4x4(  45.0f, 0.0f, 0.0f)) bResult = false;
	if (!CheckToRotationMatrix4x4( -45.0f, 0.0f, 0.0f)) bResult = false;
	if (!CheckToRotationMatrix4x4( 210.0f, 0.0f, 0.0f)) bResult = false;
	if (!CheckToRotationMatrix4x4(-210.0f, 0.0f, 0.0f)) bResult = false;
	// Check only y rotation
	if (!CheckToRotationMatrix4x4(0.0f,   45.0f, 0.0f)) bResult = false;
	if (!CheckToRotationMatrix4x4(0.0f,  -45.0f, 0.0f)) bResult = false;
	if (!CheckToRotationMatrix4x4(0.0f,  210.0f, 0.0f)) bResult = false;
	if (!CheckToRotationMatrix4x4(0.0f, -210.0f, 0.0f)) bResult = false;
	// Check only z rotation
	if (!CheckToRotationMatrix4x4(0.0f, 0.0f,   45.0f)) bResult = false;
	if (!CheckToRotationMatrix4x4(0.0f, 0.0f,  -45.0f)) bResult = false;
	if (!CheckToRotationMatrix4x4(0.0f, 0.0f,  210.0f)) bResult = false;
	if (!CheckToRotationMatrix4x4(0.0f, 0.0f, -210.0f)) bResult = false;
	EndTask(bResult);



// Misc
	/*
		PLMATH_API float GetLength() const;
		PLMATH_API float GetSquaredLength() const;
		PLMATH_API float DotProduct(const Quaternion &qQ) const;
		PLMATH_API Quaternion &Normalize();
		PLMATH_API void Conjugate();
		PLMATH_API Quaternion GetConjugated() const;
		PLMATH_API void Invert();
		PLMATH_API Quaternion GetInverted() const;
		PLMATH_API void UnitInvert();
		PLMATH_API Quaternion GetUnitInverted() const;
*/

}
