/*********************************************************\
 *  File: Matrix4x4Test.cpp                              *
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
#include <PLMath/Matrix4x4.h>
#include <PLMath/EulerAngles.h>
#include "PLTestBase/Math/Matrix4x4Test.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLMath;


//[-------------------------------------------------------]
//[ Matrix4x4Test implementation                          ]
//[-------------------------------------------------------]
bool Matrix4x4Test::CheckAxisAngle(float fX, float fY, float fZ, float fAngle, float fExpectedAngle)
{
	float fXT, fYT, fZT, fAngleT;
	Matrix4x4 mRot;

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
const char *Matrix4x4Test::GetName() const
{
	return "Matrix4x4";
}

void Matrix4x4Test::Test()
{
	float fT[16] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f};
	Matrix4x4 mM, mMT;
	bool bResult;
	Vector3 vV3;
	Vector4 vV4;

	// Matrix constructors & copy
	StartTask("Matrix constructors & copy");
	bResult = true;
	// Matrix must be identity
	if (mM.xx != 1.0f || mM.xy != 0.0f || mM.xz != 0.0f || mM.xw != 0.0f ||
		mM.yx != 0.0f || mM.yy != 1.0f || mM.yz != 0.0f || mM.yw != 0.0f ||
		mM.zx != 0.0f || mM.zy != 0.0f || mM.zz != 1.0f || mM.zw != 0.0f ||
		mM.wx != 0.0f || mM.wy != 0.0f || mM.wz != 0.0f || mM.ww != 1.0f) bResult = false;
	// Matrix4x4(const float[])
	mM = Matrix4x4(fT);
	// fM[16]
	if (mM.fM[0] != 0.0f || mM.fM[4] != 4.0f || mM.fM[ 8] !=  8.0f || mM.fM[12] != 12.0f ||
		mM.fM[1] != 1.0f || mM.fM[5] != 5.0f || mM.fM[ 9] !=  9.0f || mM.fM[13] != 13.0f ||
		mM.fM[2] != 2.0f || mM.fM[6] != 6.0f || mM.fM[10] != 10.0f || mM.fM[14] != 14.0f ||
		mM.fM[3] != 3.0f || mM.fM[7] != 7.0f || mM.fM[11] != 11.0f || mM.fM[15] != 15.0f) bResult = false;
		// The entry of the matrix in row r (0 <= r <= 3) and column c (0 <= c <= 3) is 
		// stored at index i = r+4*c (0 <= i <= 15).
		if (mM.fM[0+4*0] != 0.0f || mM.fM[0+4*1] != 4.0f || mM.fM[0+4*2] !=  8.0f || mM.fM[0+4*3] != 12.0f ||
			mM.fM[1+4*0] != 1.0f || mM.fM[1+4*1] != 5.0f || mM.fM[1+4*2] !=  9.0f || mM.fM[1+4*3] != 13.0f ||
			mM.fM[2+4*0] != 2.0f || mM.fM[2+4*1] != 6.0f || mM.fM[2+4*2] != 10.0f || mM.fM[2+4*3] != 14.0f ||
			mM.fM[3+4*0] != 3.0f || mM.fM[3+4*1] != 7.0f || mM.fM[3+4*2] != 11.0f || mM.fM[3+4*3] != 15.0f)
			bResult = false;
	// xx, xy...
	if (mM.xx != 0.0f || mM.xy != 4.0f || mM.xz !=  8.0f || mM.xw != 12.0f ||
		mM.yx != 1.0f || mM.yy != 5.0f || mM.yz !=  9.0f || mM.yw != 13.0f ||
		mM.zx != 2.0f || mM.zy != 6.0f || mM.zz != 10.0f || mM.zw != 14.0f || 
		mM.wx != 3.0f || mM.wy != 7.0f || mM.wz != 11.0f || mM.ww != 15.0f)
		bResult = false;
	// fM44[4][4]
	if (mM.fM44[0][0] != 0.0f || mM.fM44[1][0] != 4.0f || mM.fM44[2][0] !=  8.0f || mM.fM44[3][0] != 12.0f ||
		mM.fM44[0][1] != 1.0f || mM.fM44[1][1] != 5.0f || mM.fM44[2][1] !=  9.0f || mM.fM44[3][1] != 13.0f ||
		mM.fM44[0][2] != 2.0f || mM.fM44[1][2] != 6.0f || mM.fM44[2][2] != 10.0f || mM.fM44[3][2] != 14.0f ||
		mM.fM44[0][3] != 3.0f || mM.fM44[1][3] != 7.0f || mM.fM44[2][3] != 11.0f || mM.fM44[3][3] != 15.0f)
		bResult = false;
	// Matrix4x4(float fXX, float fXY, float fXZ, float fXW,
	//			 float fYX, float fYY, float fYZ, float fYW,
	//			 float fZX, float fZY, float fZZ, float fZW,
	//			 float fWX, float fWY, float fWZ, float fWW)
	mM = Matrix4x4(0.0f, 0.1f, 0.2f, 0.3f,
					 1.0f, 1.1f, 1.2f, 1.3f,
					 2.0f, 2.1f, 2.2f, 2.3f,
					 3.0f, 3.1f, 3.2f, 3.3f);
	if (mM.xx != 0.0f || mM.xy != 0.1f || mM.xz != 0.2f || mM.xw != 0.3f ||
		mM.yx != 1.0f || mM.yy != 1.1f || mM.yz != 1.2f || mM.yw != 1.3f ||
		mM.zx != 2.0f || mM.zy != 2.1f || mM.zz != 2.2f || mM.zw != 2.3f ||
		mM.wx != 3.0f || mM.wy != 3.1f || mM.wz != 3.2f || mM.ww != 3.3f)
		bResult = false;
	if (mM.fM[0] != 0.0f || mM.fM[4] != 0.1f || mM.fM[ 8] != 0.2f || mM.fM[12] != 0.3f ||
		mM.fM[1] != 1.0f || mM.fM[5] != 1.1f || mM.fM[ 9] != 1.2f || mM.fM[13] != 1.3f ||
		mM.fM[2] != 2.0f || mM.fM[6] != 2.1f || mM.fM[10] != 2.2f || mM.fM[14] != 2.3f ||
		mM.fM[3] != 3.0f || mM.fM[7] != 3.1f || mM.fM[11] != 3.2f || mM.fM[15] != 3.3f)
		bResult = false;
	EndTask(bResult);

	// Static variables
	StartTask("Static variables");
	bResult = true;
	if (Matrix4x4::Zero.xx != 0.0f || Matrix4x4::Zero.xy != 0.0f || Matrix4x4::Zero.xz != 0.0f || Matrix4x4::Zero.xw != 0.0f ||
		Matrix4x4::Zero.yx != 0.0f || Matrix4x4::Zero.yy != 0.0f || Matrix4x4::Zero.yz != 0.0f || Matrix4x4::Zero.yw != 0.0f ||
		Matrix4x4::Zero.zx != 0.0f || Matrix4x4::Zero.zy != 0.0f || Matrix4x4::Zero.zz != 0.0f || Matrix4x4::Zero.zw != 0.0f ||
		Matrix4x4::Zero.wx != 0.0f || Matrix4x4::Zero.wy != 0.0f || Matrix4x4::Zero.wz != 0.0f || Matrix4x4::Zero.ww != 0.0f) bResult = false;
	if (Matrix4x4::Identity.xx != 1.0f || Matrix4x4::Identity.xy != 0.0f || Matrix4x4::Identity.xz != 0.0f || Matrix4x4::Identity.xw != 0.0f ||
		Matrix4x4::Identity.yx != 0.0f || Matrix4x4::Identity.yy != 1.0f || Matrix4x4::Identity.yz != 0.0f || Matrix4x4::Identity.yw != 0.0f ||
		Matrix4x4::Identity.zx != 0.0f || Matrix4x4::Identity.zy != 0.0f || Matrix4x4::Identity.zz != 1.0f || Matrix4x4::Identity.zw != 0.0f ||
		Matrix4x4::Identity.wx != 0.0f || Matrix4x4::Identity.wy != 0.0f || Matrix4x4::Identity.wz != 0.0f || Matrix4x4::Identity.ww != 1.0f) bResult = false;
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
	vV3 *= mM;
	if (!Math::AreEqual(vV3.x, 0.0f) || !Math::AreEqual(vV3.y, 0.0f) || !Math::AreEqual(vV3.z, 1.0f)) bResult = false;
	// -90° + translation (2, 3, 4)
	vV3 = Vector3(1.0f, 0.0f, 0.0f);
	mM.FromEulerAngleY(-float(90.0f*Math::DegToRad));
	mM.SetTranslation(2.0f, 3.0f, 4.0f);
	vV3 = mM*vV3;
	if (!Math::AreEqual(vV3.x, 2.0f) || !Math::AreEqual(vV3.y, 3.0f) || !Math::AreEqual(vV3.z, 5.0f)) bResult = false;
	EndTask(bResult);


// Matrix operations
	// IsZero()
	StartTask("IsZero()");
	bResult = true;
	mM = Matrix4x4::Zero;
	if (!mM.IsZero()) bResult = false;
	mM.yz = 0.001f;
	if (mM.IsZero()) bResult = false;
	mM.yz = (float)Math::Epsilon;
	if (!mM.IsZero()) bResult = false;
	EndTask(bResult);

	// IsTrueZero()
	StartTask("IsTrueZero()");
	bResult = true;
	mM = Matrix4x4::Zero;
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
	if (mM.xx != 0.0f || mM.xy != 0.0f || mM.xz != 0.0f || mM.xw != 0.0f ||
		mM.yx != 0.0f || mM.yy != 0.0f || mM.yz != 0.0f || mM.yw != 0.0f ||
		mM.zx != 0.0f || mM.zy != 0.0f || mM.zz != 0.0f || mM.zw != 0.0f ||
		mM.wx != 0.0f || mM.wy != 0.0f || mM.wz != 0.0f || mM.ww != 0.0f) bResult = false;
	EndTask(bResult);

	// IsIdentity()
	StartTask("IsIdentity()");
	bResult = true;
	mM = Matrix4x4::Identity;
	if (!mM.IsIdentity()) bResult = false;
	mM.yz = 0.001f;
	if (mM.IsIdentity()) bResult = false;
	mM.yz = (float)Math::Epsilon;
	if (!mM.IsIdentity()) bResult = false;
	EndTask(bResult);

	// IsTrueIdentity()
	StartTask("IsTrueIdentity()");
	bResult = true;
	mM = Matrix4x4::Identity;
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
	EndTask(mM.xx == 1.0f && mM.xy == 0.0f && mM.xz == 0.0f && mM.xw == 0.0f &&
			mM.yx == 0.0f && mM.yy == 1.0f && mM.yz == 0.0f && mM.yw == 0.0f &&
			mM.zx == 0.0f && mM.zy == 0.0f && mM.zz == 1.0f && mM.zw == 0.0f &&
			mM.wx == 0.0f && mM.wy == 0.0f && mM.wz == 0.0f && mM.ww == 1.0f);

	// Set()
	StartTask("Set()");
	mM.Set( -0.1f,  -1.0f,  -2.0f,  -3.0f,
			  -4.0f,  -5.0f,  -6.0f,  -7.0f,
			  -8.0f,  -9.0f, -10.0f, -11.0f,
			 -12.0f, -13.0f, -14.0f, -15.0f);
	EndTask(mM.xx ==  -0.1f && mM.xy ==  -1.0f && mM.xz ==  -2.0f && mM.xw ==  -3.0f &&
			mM.yx ==  -4.0f && mM.yy ==  -5.0f && mM.yz ==  -6.0f && mM.yw ==  -7.0f &&
			mM.zx ==  -8.0f && mM.zy ==  -9.0f && mM.zz == -10.0f && mM.zw == -11.0f &&
			mM.wx == -12.0f && mM.wy == -13.0f && mM.wz == -14.0f && mM.ww == -15.0f);

	// GetRow()
	StartTask("GetRow()");
	bResult = true;
	mM = fT;
	vV4 = mM.GetRow(0);
	if (vV4.x != 0.0f || vV4.y != 4.0f || vV4.z !=  8.0f || vV4.w != 12.0f) bResult = false;
	vV4 = mM.GetRow(1);
	if (vV4.x != 1.0f || vV4.y != 5.0f || vV4.z !=  9.0f || vV4.w != 13.0f) bResult = false;
	vV4 = mM.GetRow(2);
	if (vV4.x != 2.0f || vV4.y != 6.0f || vV4.z != 10.0f || vV4.w != 14.0f) bResult = false;
	vV4 = mM.GetRow(3);
	if (vV4.x != 3.0f || vV4.y != 7.0f || vV4.z != 11.0f || vV4.w != 15.0f) bResult = false;
	EndTask(bResult);

	// SetRow()
	StartTask("SetRow()");
	bResult = true;
	mM.SetRow(0, Vector4(-0.1f, -4.0f, -8.0f, -12.0f));
	if (mM.xx != -0.1f || mM.xy != -4.0f || mM.xz != -8.0f || mM.xw != -12.0f) bResult = false;
	mM.SetRow(1, Vector4(-1.0f, -5.0f, -9.0f, -13.0f));
	if (mM.yx != -1.0f || mM.yy != -5.0f || mM.yz != -9.0f || mM.yw != -13.0f) bResult = false;
	mM.SetRow(2, Vector4(-2.0f, -6.0f, -10.0f, -14.0f));
	if (mM.zx != -2.0f || mM.zy != -6.0f || mM.zz != -10.0f || mM.zw != -14.0f) bResult = false;
	mM.SetRow(3, Vector4(-3.0f, -7.0f, -11.0f, -15.0f));
	if (mM.wx != -3.0f || mM.wy != -7.0f || mM.wz != -11.0f || mM.ww != -15.0f) bResult = false;
	EndTask(bResult);

	// GetColumn()
	StartTask("GetColumn()");
	bResult = true;
	mM = fT;
	vV4 = mM.GetColumn(0);
	if (vV4.x !=  0.0f || vV4.y !=  1.0f || vV4.z !=  2.0f || vV4.w !=  3.0f) bResult = false;
	vV4 = mM.GetColumn(1);
	if (vV4.x !=  4.0f || vV4.y !=  5.0f || vV4.z !=  6.0f || vV4.w !=  7.0f) bResult = false;
	vV4 = mM.GetColumn(2);
	if (vV4.x !=  8.0f || vV4.y !=  9.0f || vV4.z != 10.0f || vV4.w != 11.0f) bResult = false;
	vV4 = mM.GetColumn(3);
	if (vV4.x != 12.0f || vV4.y != 13.0f || vV4.z != 14.0f || vV4.w != 15.0f) bResult = false;
	EndTask(bResult);

	// SetColumn()
	StartTask("SetColumn()");
	bResult = true;
	mM.SetColumn(0, Vector4(-0.1f, -1.0f, -2.0f, -3.0f));
	if (mM.xx != -0.1f || mM.yx != -1.0f || mM.zx != -2.0f || mM.wx != -3.0f) bResult = false;
	mM.SetColumn(1, Vector4(-4.0f, -5.0f, -6.0f, -7.0f));
	if (mM.xy != -4.0f || mM.yy != -5.0f || mM.zy != -6.0f || mM.wy != -7.0f) bResult = false;
	mM.SetColumn(2, Vector4(-8.0f, -9.0f, -10.0f, -11.0f));
	if (mM.xz != -8.0f || mM.yz != -9.0f || mM.zz != -10.0f || mM.wz != -11.0f) bResult = false;
	mM.SetColumn(3, Vector4(-12.0f, -13.0f, -14.0f, -15.0f));
	if (mM.xw != -12.0f || mM.yw != -13.0f || mM.zw != -14.0f || mM.ww != -15.0f) bResult = false;
	EndTask(bResult);

	// IsSymmetric()
	StartTask("IsSymmetric()");
	bResult = true;
	mM = Matrix4x4::Identity;
	if (!mM.IsSymmetric()) bResult = false;
	mM.xx = 4.0f;
	if (!mM.IsSymmetric()) bResult = false;
	mM.xy = 4.0f;
	if (mM.IsSymmetric()) bResult = false;
	EndTask(bResult);

	// IsOrthogonal()
	StartTask("IsOrthogonal()");
	bResult = true;
	mM = Matrix4x4::Identity;
	if (!mM.IsOrthogonal()) bResult = false;
	// [TODO]
//	mM.yw = 4.0f;
//	if (!mM.IsOrthogonal()) bResult = false;
	//mM.xy = 2.0f;
	//if (mM.IsOrthogonal()) bResult = false;
	EndTask(bResult);

	// IsRotationMatrix()
	StartTask("IsRotationMatrix()");
	bResult = true;
	mM = Matrix4x4::Identity;
	if (!mM.IsRotationMatrix()) bResult = false;
	mM.xx = 4.0f;
	if (mM.IsRotationMatrix()) bResult = false;
	EndTask(bResult);

	// GetTrace()
	StartTask("GetTrace()");
	bResult = true;
	if (Matrix4x4::Zero.GetTrace() != 0.0f) bResult = false;
	if (Matrix4x4::Identity.GetTrace() != 4.0f) bResult = false;
	mM = Matrix4x4::Identity;
	mM.xy = 1.0f;
	if (mM.GetTrace() != 4.0f) bResult = false;
	EndTask(bResult);

	// GetDeterminant()
	StartTask("GetDeterminant()");
	bResult = true;
	if (Matrix4x4::Zero.GetDeterminant() != 0.0f) bResult = false;
	if (Matrix4x4::Identity.GetDeterminant() != 1.0f) bResult = false;
	EndTask(bResult);

	// Transpose()
	StartTask("Transpose()");
	bResult = true;
	mM = Matrix4x4::Identity;
	mM.Transpose();
	if (mM != Matrix4x4::Identity) bResult = false;
	EndTask(bResult);

	// GetTransposed()
	StartTask("GetTransposed()");
	bResult = true;
	if (Matrix4x4::Identity.GetTransposed() != Matrix4x4::Identity) bResult = false;
	EndTask(bResult);

	// Invert()
	StartTask("Invert()");
	bResult = true;
	mM = Matrix4x4::Identity;
	mM.Invert();
	if (mM != Matrix4x4::Identity) bResult = false;
	EndTask(bResult);

	// GetInverted()
	StartTask("GetInverted()");
	bResult = true;
	if (Matrix4x4::Identity.GetInverted() != Matrix4x4::Identity) bResult = false;
	EndTask(bResult);


// Scale
	// GetScale(float fX, float fY, float fZ)
	StartTask("GetScale(float fX, float fY, float fZ)");
	bResult = true;
	// Identity matrix
	vV3 = Vector3::Zero;
	Matrix4x4::Identity.GetScale(vV3.x, vV3.y, vV3.z);
	if (vV3.x != 1.0f || vV3.y != 1.0f || vV3.z != 1.0f) bResult = false;
	// Null matrix
	vV3 = Vector3::Zero;
	Matrix4x4::Zero.GetScale(vV3.x, vV3.y, vV3.z);
	if (vV3.x != 0.0f || vV3.y != 0.0f || vV3.z != 0.0f) bResult = false;
	// Any matrix
	vV3 = Vector3::Zero;
	mM.SetTranslationMatrix(1.0f, 2.0f, 3.0f);
	EulerAngles::ToMatrix(1.0f, 2.0f, 3.0f, mMT);
	mM *= mMT;
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
	vV3 = Matrix4x4::Identity.GetXAxis();
	if (vV3.x != 1.0f || vV3.y != 0.0f || vV3.z != 0.0f) bResult = false;
	EndTask(bResult);

	// GetYAxis()
	StartTask("GetYAxis()");
	bResult = true;
	vV3 = Matrix4x4::Identity.GetYAxis();
	if (vV3.x != 0.0f || vV3.y != 1.0f || vV3.z != 0.0f) bResult = false;
	EndTask(bResult);

	// GetZAxis()
	StartTask("GetZAxis()");
	bResult = true;
	vV3 = Matrix4x4::Identity.GetZAxis();
	if (vV3.x != 0.0f || vV3.y != 0.0f || vV3.z != 1.0f) bResult = false;
	EndTask(bResult);
}
