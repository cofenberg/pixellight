/*********************************************************\
 *  File: Matrix3x3Test.cpp                              *
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
#include <PLMath/EulerAngles.h>
#include "PLTestBase/Math/Matrix3x3Test.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLMath;


//[-------------------------------------------------------]
//[ Matrix3x3Test implementation                          ]
//[-------------------------------------------------------]
bool Matrix3x3Test::CheckAxisAngle(float fX, float fY, float fZ, float fAngle, float fExpectedAngle)
{
	float fXT, fYT, fZT, fAngleT;
	Matrix3x3 mRot;

	// Degree to radian
	fAngle         = float(fAngle*Math::DegToRad);
	fExpectedAngle = float(fExpectedAngle*Math::DegToRad);
	
	mRot.FromAxisAngle(fX, fY, fZ, fAngle);
	mRot.ToAxisAngle(fXT, fYT, fZT, fAngleT);
	if (Math::AreEqual(fX, fXT) && Math::AreEqual(fY, fYT) && Math::AreEqual(fZ, fZT) &&
		Math::AreEqual(fAngleT, fExpectedAngle))
		return true; // Success
	else return false; // Error!
}


//[-------------------------------------------------------]
//[ Virtual TestCase functions                            ]
//[-------------------------------------------------------]
const char *Matrix3x3Test::GetName() const
{
	return "Matrix3x3";
}

void Matrix3x3Test::Test()
{
	float fT[9] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
	Matrix3x3 mM, mMT;
	bool bResult;
	Vector3 vV3;

	// Matrix constructors & copy
	StartTask("Matrix constructors & copy");
	bResult = true;
	// Matrix must be identity
	if (mM.xx != 1.0f || mM.xy != 0.0f || mM.xz != 0.0f ||
		mM.yx != 0.0f || mM.yy != 1.0f || mM.yz != 0.0f ||
		mM.zx != 0.0f || mM.zy != 0.0f || mM.zz != 1.0f) bResult = false;
	// Matrix3x3(const float[])
	mM = Matrix3x3(fT);
	// fM[9]
	if (mM.fM[0] != 0.0f || mM.fM[3] != 3.0f || mM.fM[6] != 6.0f ||
		mM.fM[1] != 1.0f || mM.fM[4] != 4.0f || mM.fM[7] != 7.0f ||
		mM.fM[2] != 2.0f || mM.fM[5] != 5.0f || mM.fM[8] != 8.0f) bResult = false;
		// The entry of the matrix in row r (0 <= r <= 2) and column c (0 <= c <= 2) is 
		// stored at index i = r+3*c (0 <= i <= 8).
		if (mM.fM[0+3*0] != 0.0f || mM.fM[0+3*1] != 3.0f || mM.fM[0+3*2] != 6.0f ||
			mM.fM[1+3*0] != 1.0f || mM.fM[1+3*1] != 4.0f || mM.fM[1+3*2] != 7.0f ||
			mM.fM[2+3*0] != 2.0f || mM.fM[2+3*1] != 5.0f || mM.fM[2+3*2] != 8.0f) bResult = false;
	// xx, xy...
	if (mM.xx != 0.0f || mM.xy != 3.0f || mM.xz != 6.0f ||
		mM.yx != 1.0f || mM.yy != 4.0f || mM.yz != 7.0f ||
		mM.zx != 2.0f || mM.zy != 5.0f || mM.zz != 8.0f) bResult = false;
	// fM33[3][3]
	if (mM.fM33[0][0] != 0.0f || mM.fM33[1][0] != 3.0f || mM.fM33[2][0] != 6.0f ||
		mM.fM33[0][1] != 1.0f || mM.fM33[1][1] != 4.0f || mM.fM33[2][1] != 7.0f ||
		mM.fM33[0][2] != 2.0f || mM.fM33[1][2] != 5.0f || mM.fM33[2][2] != 8.0f) bResult = false;
	// Matrix3x3(float fXX, float fXY, float fXZ,
	//			 float fYX, float fYY, float fYZ,
	//			 float fZX, float fZY, float fZZ)
	mM = Matrix3x3(0.0f, 0.1f, 0.2f,
				   1.0f, 1.1f, 1.2f,
				   2.0f, 2.1f, 2.2f);
	if (mM.xx != 0.0f || mM.xy != 0.1f || mM.xz != 0.2f ||
		mM.yx != 1.0f || mM.yy != 1.1f || mM.yz != 1.2f ||
		mM.zx != 2.0f || mM.zy != 2.1f || mM.zz != 2.2f) bResult = false;
	if (mM.fM[0] != 0.0f || mM.fM[3] != 0.1f || mM.fM[6] != 0.2f ||
		mM.fM[1] != 1.0f || mM.fM[4] != 1.1f || mM.fM[7] != 1.2f ||
		mM.fM[2] != 2.0f || mM.fM[5] != 2.1f || mM.fM[8] != 2.2f) bResult = false;
	EndTask(bResult);

	// Static variables
	StartTask("Static variables");
	bResult = true;
	if (Matrix3x3::Zero.xx != 0.0f || Matrix3x3::Zero.xy != 0.0f || Matrix3x3::Zero.xz != 0.0f ||
		Matrix3x3::Zero.yx != 0.0f || Matrix3x3::Zero.yy != 0.0f || Matrix3x3::Zero.yz != 0.0f ||
		Matrix3x3::Zero.zx != 0.0f || Matrix3x3::Zero.zy != 0.0f || Matrix3x3::Zero.zz != 0.0f) bResult = false;
	if (Matrix3x3::Identity.xx != 1.0f || Matrix3x3::Identity.xy != 0.0f || Matrix3x3::Identity.xz != 0.0f ||
		Matrix3x3::Identity.yx != 0.0f || Matrix3x3::Identity.yy != 1.0f || Matrix3x3::Identity.yz != 0.0f ||
		Matrix3x3::Identity.zx != 0.0f || Matrix3x3::Identity.zy != 0.0f || Matrix3x3::Identity.zz != 1.0f) bResult = false;
	EndTask(bResult);


// Operators
	// * Vector3
	StartTask("* Vector3");
	bResult = true;
	// 90°
	vV3 = Vector3(1.0f, 0.0f, 0.0f);
	mM.FromEulerAngleY(float(90.0f*Math::DegToRad));
	vV3 = mM*vV3;
	if (!Math::AreEqual(vV3.x, 0.0f) || !Math::AreEqual(vV3.y, 0.0f) || !Math::AreEqual(vV3.z, -1.0f)) bResult = false;
	// -90°
	vV3 = Vector3(1.0f, 0.0f, 0.0f);
	mM.FromEulerAngleY(-float(90.0f*Math::DegToRad));
	vV3 = mM*vV3;
	if (!Math::AreEqual(vV3.x, 0.0f) || !Math::AreEqual(vV3.y, 0.0f) || !Math::AreEqual(vV3.z, 1.0f)) bResult = false;
	EndTask(bResult);


// Matrix operations
	// IsZero()
	StartTask("IsZero()");
	bResult = true;
	mM = Matrix3x3::Zero;
	if (!mM.IsZero()) bResult = false;
	mM.yz = 0.001f;
	if (mM.IsZero()) bResult = false;
	mM.yz = (float)Math::Epsilon;
	if (!mM.IsZero()) bResult = false;
	EndTask(bResult);

	// IsTrueZero()
	StartTask("IsTrueZero()");
	bResult = true;
	mM = Matrix3x3::Zero;
	if (!mM.IsTrueZero()) bResult = false;
	mM.yz = 0.001f;
	if (mM.IsTrueZero()) bResult = false;
	mM.yz = (float)Math::Epsilon;
	if (mM.IsTrueZero()) bResult = false;
	EndTask(bResult);

	// SetZero()
	StartTask("SetZero()");
	bResult = true;
	mM.yz = 0.001f;
	mM.xx = 0.101f;
	mM.SetZero();
	if (mM.xx != 0.0f || mM.xy != 0.0f || mM.xz != 0.0f ||
		mM.yx != 0.0f || mM.yy != 0.0f || mM.yz != 0.0f ||
		mM.zx != 0.0f || mM.zy != 0.0f || mM.zz != 0.0f) bResult = false;
	EndTask(bResult);

	// IsIdentity()
	StartTask("IsIdentity()");
	bResult = true;
	mM = Matrix3x3::Identity;
	if (!mM.IsIdentity()) bResult = false;
	mM.yz = 0.001f;
	if (mM.IsIdentity()) bResult = false;
	mM.yz = (float)Math::Epsilon;
	if (!mM.IsIdentity()) bResult = false;
	EndTask(bResult);

	// IsTrueIdentity()
	StartTask("IsTrueIdentity()");
	bResult = true;
	mM = Matrix3x3::Identity;
	if (!mM.IsTrueIdentity()) bResult = false;
	mM.yz = 0.001f;
	if (mM.IsTrueIdentity()) bResult = false;
	mM.yz = (float)Math::Epsilon;
	if (mM.IsTrueIdentity()) bResult = false;
	EndTask(bResult);

	// SetIdentity()
	StartTask("SetIdentity()");
	mM.yz = 0.001f;
	mM.xx = 0.101f;
	mM.SetIdentity();
	EndTask(mM.xx == 1.0f && mM.xy == 0.0f && mM.xz == 0.0f &&
			mM.yx == 0.0f && mM.yy == 1.0f && mM.yz == 0.0f &&
			mM.zx == 0.0f && mM.zy == 0.0f && mM.zz == 1.0f);

	// Set()
	StartTask("Set()");
	mM.Set(-0.1f, -1.0f, -2.0f,
			 -3.0f, -4.0f, -5.0f,
			 -6.0f, -7.0f, -8.0f);
	EndTask(mM.xx == -0.1f && mM.xy == -1.0f && mM.xz == -2.0f &&
			mM.yx == -3.0f && mM.yy == -4.0f && mM.yz == -5.0f &&
			mM.zx == -6.0f && mM.zy == -7.0f && mM.zz == -8.0f);

	// GetRow()
	StartTask("GetRow()");
	bResult = true;
	mM = fT;
	vV3 = mM.GetRow(0);
	if (vV3.x != 0.0f || vV3.y != 3.0f || vV3.z != 6.0f) bResult = false;
	vV3 = mM.GetRow(1);
	if (vV3.x != 1.0f || vV3.y != 4.0f || vV3.z != 7.0f) bResult = false;
	vV3 = mM.GetRow(2);
	if (vV3.x != 2.0f || vV3.y != 5.0f || vV3.z != 8.0f) bResult = false;
	EndTask(bResult);

	// SetRow()
	StartTask("SetRow()");
	bResult = true;
	mM.SetRow(0, Vector3(-0.1f, -3.0f, -6.0f));
	if (mM.xx != -0.1f || mM.xy != -3.0f || mM.xz != -6.0f) bResult = false;
	mM.SetRow(1, Vector3(-1.0f, -4.0f, -7.0f));
	if (mM.yx != -1.0f || mM.yy != -4.0f || mM.yz != -7.0f) bResult = false;
	mM.SetRow(2, Vector3(-2.0f, -5.0f, -8.0f));
	if (mM.zx != -2.0f || mM.zy != -5.0f || mM.zz != -8.0f) bResult = false;
	EndTask(bResult);

	// GetColumn()
	StartTask("GetColumn()");
	bResult = true;
	mM = fT;
	vV3 = mM.GetColumn(0);
	if (vV3.x != 0.0f || vV3.y != 1.0f || vV3.z != 2.0f) bResult = false;
	vV3 = mM.GetColumn(1);
	if (vV3.x != 3.0f || vV3.y != 4.0f || vV3.z != 5.0f) bResult = false;
	vV3 = mM.GetColumn(2);
	if (vV3.x != 6.0f || vV3.y != 7.0f || vV3.z != 8.0f) bResult = false;
	EndTask(bResult);

	// SetColumn()
	StartTask("SetColumn()");
	bResult = true;
	mM.SetColumn(0, Vector3(-0.1f, -1.0f, -2.0f));
	if (mM.xx != -0.1f || mM.yx != -1.0f || mM.zx != -2.0f) bResult = false;
	mM.SetColumn(1, Vector3(-3.0f, -4.0f, -5.0f));
	if (mM.xy != -3.0f || mM.yy != -4.0f || mM.zy != -5.0f) bResult = false;
	mM.SetColumn(2, Vector3(-6.0f, -7.0f, -8.0f));
	if (mM.xz != -6.0f || mM.yz != -7.0f || mM.zz != -8.0f) bResult = false;
	EndTask(bResult);

	// IsSymmetric()
	StartTask("IsSymmetric()");
	bResult = true;
	mM = Matrix3x3::Identity;
	if (!mM.IsSymmetric()) bResult = false;
	mM.xx = 4.0f;
	if (!mM.IsSymmetric()) bResult = false;
	mM.xy = 4.0f;
	if (mM.IsSymmetric()) bResult = false;
	EndTask(bResult);

	// IsOrthogonal()
	StartTask("IsOrthogonal()");
	bResult = true;
	mM = Matrix3x3::Identity;
	if (!mM.IsOrthogonal()) bResult = false;
	mM.yy = 4.0f;
	if (mM.IsOrthogonal()) bResult = false;
	// [TODO]
	//mM.xy = 2.0f;
	//if (mM.IsOrthogonal()) bResult = false;
	EndTask(bResult);

	// IsRotationMatrix()
	StartTask("IsRotationMatrix()");
	bResult = true;
	mM = Matrix3x3::Identity;
	if (!mM.IsRotationMatrix()) bResult = false;
	mM.xx = 4.0f;
	if (mM.IsRotationMatrix()) bResult = false;
	EndTask(bResult);

	// GetTrace()
	StartTask("GetTrace()");
	bResult = true;
	if (Matrix3x3::Zero.GetTrace() != 0.0f) bResult = false;
	if (Matrix3x3::Identity.GetTrace() != 3.0f) bResult = false;
	mM = Matrix3x3::Identity;
	mM.xy = 1.0f;
	if (mM.GetTrace() != 3.0f) bResult = false;
	EndTask(bResult);

	// GetDeterminant()
	StartTask("GetDeterminant()");
	bResult = true;
	if (Matrix3x3::Zero.GetDeterminant() != 0.0f) bResult = false;
	if (Matrix3x3::Identity.GetDeterminant() != 1.0f) bResult = false;
	EndTask(bResult);

	// Transpose()
	StartTask("Transpose()");
	bResult = true;
	mM = Matrix3x3::Identity;
	mM.Transpose();
	if (mM != Matrix3x3::Identity) bResult = false;
	EndTask(bResult);

	// GetTransposed()
	StartTask("GetTransposed()");
	bResult = true;
	if (Matrix3x3::Identity.GetTransposed() != Matrix3x3::Identity) bResult = false;
	EndTask(bResult);

	// Invert()
	StartTask("Invert()");
	bResult = true;
	mM = Matrix3x3::Identity;
	mM.Invert();
	if (mM != Matrix3x3::Identity) bResult = false;
	EndTask(bResult);

	// GetInverted()
	StartTask("GetInverted()");
	bResult = true;
	if (Matrix3x3::Identity.GetInverted() != Matrix3x3::Identity) bResult = false;
	EndTask(bResult);


// Scale
	// GetScale(float fX, float fY, float fZ)
	StartTask("GetScale(float fX, float fY, float fZ)");
	bResult = true;
	// Identity matrix
	vV3 = Vector3::Zero;
	Matrix3x3::Identity.GetScale(vV3.x, vV3.y, vV3.z);
	if (vV3.x != 1.0f || vV3.y != 1.0f || vV3.z != 1.0f) bResult = false;
	// Null matrix
	vV3 = Vector3::Zero;
	Matrix3x3::Zero.GetScale(vV3.x, vV3.y, vV3.z);
	if (vV3.x != 0.0f || vV3.y != 0.0f || vV3.z != 0.0f) bResult = false;
	// Any matrix
	vV3 = Vector3::Zero;
	EulerAngles::ToMatrix(1.0f, 2.0f, 3.0f, mM);
	mMT.SetScaleMatrix(1.0f, 2.0f, 3.0f);
	mM *= mMT;
	mM.GetScale(vV3.x, vV3.y, vV3.z);
	if (!Math::AreEqual(vV3.x, 1.0f, 0.000001f) || !Math::AreEqual(vV3.y, 2.0f, 0.000001f) || !Math::AreEqual(vV3.z, 3.0f, 0.000001f))
		bResult = false;
	EndTask(bResult);


 // Rotation
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
//	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f, 225.0f, 225.0f)) bResult = false;
//	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f, 270.0f, 270.0f)) bResult = false;
//	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f, 315.0f, 315.0f)) bResult = false;
//	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f, 360.0f, 360.0f)) bResult = false;
	// Check only y rotation
//	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f,   0.0f,   0.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f,  45.0f,  45.0f)) bResult = false;
//	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, -45.0f,  45.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f,  90.0f,  90.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, 135.0f, 135.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, 180.0f, 180.0f)) bResult = false;
//	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, 225.0f, 225.0f)) bResult = false;
//	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, 270.0f, 270.0f)) bResult = false;
//	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, 315.0f, 315.0f)) bResult = false;
//	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, 360.0f, 360.0f)) bResult = false;
	// Check only z rotation
//	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f,   0.0f,   0.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f,  45.0f,  45.0f)) bResult = false;
//	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, -45.0f,  45.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f,  90.0f,  90.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, 135.0f, 135.0f)) bResult = false;
	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, 180.0f, 180.0f)) bResult = false;
//	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, 225.0f, 225.0f)) bResult = false;
//	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, 270.0f, 270.0f)) bResult = false;
//	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, 315.0f, 315.0f)) bResult = false;
//	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, 360.0f, 360.0f)) bResult = false;
	EndTask(bResult);

	// GetXAxis()
	StartTask("GetXAxis()");
	bResult = true;
	vV3 = Matrix3x3::Identity.GetXAxis();
	if (vV3.x != 1.0f || vV3.y != 0.0f || vV3.z != 0.0f) bResult = false;
	EndTask(bResult);

	// GetYAxis()
	StartTask("GetYAxis()");
	bResult = true;
	vV3 = Matrix3x3::Identity.GetYAxis();
	if (vV3.x != 0.0f || vV3.y != 1.0f || vV3.z != 0.0f) bResult = false;
	EndTask(bResult);

	// GetZAxis()
	StartTask("GetZAxis()");
	bResult = true;
	vV3 = Matrix3x3::Identity.GetZAxis();
	if (vV3.x != 0.0f || vV3.y != 0.0f || vV3.z != 1.0f) bResult = false;
	EndTask(bResult);
}
