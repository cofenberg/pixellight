/*********************************************************\
 *  File: EulerAngles.cpp                                *
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
#include "PLMath/Matrix3x3.h"
#include "PLMath/Matrix3x4.h"
#include "PLMath/Matrix4x4.h"
#include "PLMath/Quaternion.h"
#include "PLMath/EulerAngles.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
static const float FloatEpsilon = 1.192092896e-07f; // Smallest such that 1.0f+FloatEpsilon != 1.0
 // EulGetOrd unpacks all useful information about order simultaneously
#define EulSafe "\000\001\002\000"
#define EulNext "\001\002\000\001"
#define EulGetOrd(ord,i,j,k,h,n,s,f) {unsigned o=ord;f=o&1;o>>=1;s=o&1;o>>=1;\
    n=o&1;o>>=1;i=EulSafe[o&3];j=EulNext[i+n];k=EulNext[i+1-n];h=s?k:i;}


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets a rotation quaternion by using three given Euler angles
*/
void EulerAngles::ToQuaternion(float fAngleX, float fAngleY, float fAngleZ, Quaternion &qRotation, EOrder nOrder)
{
	int i, j, k, h, n, s, f;
	EulGetOrd(nOrder, i, j, k, h, n, s, f);
	if (f == 1) {
		float t = fAngleX;
		fAngleX = fAngleZ;
		fAngleZ = t;
	}
	if (n == 1)
		fAngleY = -fAngleY;

	double ti = fAngleX*0.5;
	double tj = fAngleY*0.5;
	double th = fAngleZ*0.5;
	double ci = Math::Cos(ti);
	double cj = Math::Cos(tj);
	double ch = Math::Cos(th);
	double si = Math::Sin(ti);
	double sj = Math::Sin(tj);
	double sh = Math::Sin(th);
	double cc = ci*ch;
	double cs = ci*sh;
	double sc = si*ch;
	double ss = si*sh;

	double a[3];
	if (s == 1) {
		a[i] = cj*(cs + sc);	// Could speed up with trig identities
		a[j] = sj*(cc + ss);
		a[k] = sj*(cs - sc);
		qRotation.w = float(cj*(cc - ss));
	} else {
		a[i] = cj*sc - sj*cs;
		a[j] = cj*ss + sj*cc;
		a[k] = cj*cs - sj*sc;
		qRotation.w = float(cj*cc + sj*ss);
	}
	if (n == 1)
		a[j] = -a[j];

	qRotation.x = float(a[0]);
	qRotation.y = float(a[1]);
	qRotation.z = float(a[2]);
}

/**
*  @brief
*    Returns the Euler angles from a rotation quaternion
*/
void EulerAngles::FromQuaternion(const Quaternion &q, float &fAngleX, float &fAngleY, float &fAngleZ, EOrder nOrder)
{
	// Construct 3x3 matrix
	enum EComponent {X, Y, Z};
	float M[3][3]; // Right-handed, for column vectors
	{
		double Nq = q.x*q.x+q.y*q.y+q.z*q.z+q.w*q.w;
		double s  = (Nq > 0.0) ? (2.0 / Nq) : 0.0;
		double xs = q.x*s,  ys = q.y*s,  zs = q.z*s;
		double wx = q.w*xs, wy = q.w*ys, wz = q.w*zs;
		double xx = q.x*xs, xy = q.x*ys, xz = q.x*zs;
		double yy = q.y*ys, yz = q.y*zs, zz = q.z*zs;
		M[X][X] = float(1.0-(yy+zz)); M[X][Y] = float(xy-wz);       M[X][Z] = float(xz+wy);
		M[Y][X] = float(xy+wz);       M[Y][Y] = float(1.0-(xx+zz)); M[Y][Z] = float(yz-wx);
		M[Z][X] = float(xz-wy);       M[Z][Y] = float(yz+wx);       M[Z][Z] = float(1.0-(xx+yy));
	}

	// Convert 3x3 matrix to Euler angles (in radians)
	int i, j, k, h, n, s, f;
	EulGetOrd(nOrder, i, j, k, h, n, s, f);
	if (s == 1) {
		double sy = Math::Sqrt(M[i][j]*M[i][j] + M[i][k]*M[i][k]);
		if (sy > 16*FloatEpsilon) {
			fAngleX = float(Math::ATan2(M[i][j], M[i][k]));
			fAngleY = float(Math::ATan2(sy, (double)M[i][i]));
			fAngleZ = float(Math::ATan2(M[j][i], -M[k][i]));
		} else {
			fAngleX = float(Math::ATan2(-M[j][k], M[j][j]));
			fAngleY = float(Math::ATan2(sy, (double)M[i][i]));
			fAngleZ = 0.0f;
		}
	} else {
		double cy = Math::Sqrt(M[i][i]*M[i][i] + M[j][i]*M[j][i]);
		if (cy > 16*FloatEpsilon) {
			fAngleX = float(Math::ATan2(M[k][j], M[k][k]));
			fAngleY = float(Math::ATan2((double)-M[k][i], cy));
			fAngleZ = float(Math::ATan2(M[j][i], M[i][i]));
		} else {
			fAngleX = float(Math::ATan2(-M[j][k], M[j][j]));
			fAngleY = float(Math::ATan2((double)-M[k][i], cy));
			fAngleZ = 0.0f;
		}
	}
	if (n == 1) {
		fAngleX = -fAngleX;
		fAngleY = -fAngleY;
		fAngleZ = -fAngleZ;
	}
	if (f == 1) {
		float t = fAngleX;
		fAngleX = fAngleZ;
		fAngleZ = t;
	}
}

/**
*  @brief
*    Sets a rotation matrix by using three given Euler angles
*/
void EulerAngles::ToMatrix(float fAngleX, float fAngleY, float fAngleZ, Matrix3x3 &mRot, EOrder nOrder)
{
	int i, j, k, h, n, s, f;
	EulGetOrd(nOrder, i, j, k, h, n, s, f);
	if (f == 1) {
		float t = fAngleX;
		fAngleX = fAngleZ;
		fAngleZ = t;
	}
	if (n == 1) {
		fAngleX = -fAngleX;
		fAngleY = -fAngleY;
		fAngleZ = -fAngleZ;
	}

	double ti = fAngleX;
	double tj = fAngleY;
	double th = fAngleZ;
	double ci = Math::Cos(ti);
	double cj = Math::Cos(tj);
	double ch = Math::Cos(th);
	double si = Math::Sin(ti);
	double sj = Math::Sin(tj);
	double sh = Math::Sin(th);
	double cc = ci*ch;
	double cs = ci*sh;
	double sc = si*ch;
	double ss = si*sh;

	if (s == 1) {
		mRot.fM33[i][i] = float(cj);     mRot.fM33[i][j] = float(sj*si);     mRot.fM33[i][k] = float(sj*ci);
		mRot.fM33[j][i] = float(sj*sh);  mRot.fM33[j][j] = float(-cj*ss+cc); mRot.fM33[j][k] = float(-cj*cs-sc);
		mRot.fM33[k][i] = float(-sj*ch); mRot.fM33[k][j] = float(cj*sc+cs);  mRot.fM33[k][k] = float(cj*cc-ss);
	} else {
		mRot.fM33[i][i] = float(cj*ch);  mRot.fM33[i][j] = float(sj*sc-cs);  mRot.fM33[i][k] = float(sj*cc+ss);
		mRot.fM33[j][i] = float(cj*sh);  mRot.fM33[j][j] = float(sj*ss+cc);  mRot.fM33[j][k] = float(sj*cs-sc);
		mRot.fM33[k][i] = float(-sj);    mRot.fM33[k][j] = float(cj*si);     mRot.fM33[k][k] = float(cj*ci);
	}
}

void EulerAngles::ToMatrix(float fAngleX, float fAngleY, float fAngleZ, Matrix3x4 &mRot, EOrder nOrder)
{
	int i, j, k, h, n, s, f;
	EulGetOrd(nOrder, i, j, k, h, n, s, f);
	if (f == 1) {
		float t = fAngleX;
		fAngleX = fAngleZ;
		fAngleZ = t;
	}
	if (n == 1) {
		fAngleX = -fAngleX;
		fAngleY = -fAngleY;
		fAngleZ = -fAngleZ;
	}

	double ti = fAngleX;
	double tj = fAngleY;
	double th = fAngleZ;
	double ci = Math::Cos(ti);
	double cj = Math::Cos(tj);
	double ch = Math::Cos(th);
	double si = Math::Sin(ti);
	double sj = Math::Sin(tj);
	double sh = Math::Sin(th);
	double cc = ci*ch;
	double cs = ci*sh;
	double sc = si*ch;
	double ss = si*sh;

	if (s == 1) {
		mRot.fM43[i][i] = float(cj);     mRot.fM43[i][j] = float(sj*si);     mRot.fM43[i][k] = float(sj*ci);     mRot.xw = 0.0f;
		mRot.fM43[j][i] = float(sj*sh);  mRot.fM43[j][j] = float(-cj*ss+cc); mRot.fM43[j][k] = float(-cj*cs-sc); mRot.yw = 0.0f;
		mRot.fM43[k][i] = float(-sj*ch); mRot.fM43[k][j] = float(cj*sc+cs);  mRot.fM43[k][k] = float(cj*cc-ss);  mRot.zw = 0.0f;
	} else {
		mRot.fM43[i][i] = float(cj*ch);  mRot.fM43[i][j] = float(sj*sc-cs);  mRot.fM43[i][k] = float(sj*cc+ss); mRot.xw = 0.0f;
		mRot.fM43[j][i] = float(cj*sh);  mRot.fM43[j][j] = float(sj*ss+cc);  mRot.fM43[j][k] = float(sj*cs-sc); mRot.yw = 0.0f;
		mRot.fM43[k][i] = float(-sj);    mRot.fM43[k][j] = float(cj*si);     mRot.fM43[k][k] = float(cj*ci);    mRot.zw = 0.0f;
	}
}

void EulerAngles::ToMatrix(float fAngleX, float fAngleY, float fAngleZ, Matrix4x4 &mRot, EOrder nOrder)
{
	int i, j, k, h, n, s, f;
	EulGetOrd(nOrder, i, j, k, h, n, s, f);
	if (f == 1) {
		float t = fAngleX;
		fAngleX = fAngleZ;
		fAngleZ = t;
	}
	if (n == 1) {
		fAngleX = -fAngleX;
		fAngleY = -fAngleY;
		fAngleZ = -fAngleZ;
	}

	double ti = fAngleX;
	double tj = fAngleY;
	double th = fAngleZ;
	double ci = Math::Cos(ti);
	double cj = Math::Cos(tj);
	double ch = Math::Cos(th);
	double si = Math::Sin(ti);
	double sj = Math::Sin(tj);
	double sh = Math::Sin(th);
	double cc = ci*ch;
	double cs = ci*sh;
	double sc = si*ch;
	double ss = si*sh;

	if (s == 1) {
		mRot.fM44[i][i] = float(cj);     mRot.fM44[i][j] = float(sj*si);     mRot.fM44[i][k] = float(sj*ci);     mRot.xw = 0.0f;
		mRot.fM44[j][i] = float(sj*sh);  mRot.fM44[j][j] = float(-cj*ss+cc); mRot.fM44[j][k] = float(-cj*cs-sc); mRot.yw = 0.0f;
		mRot.fM44[k][i] = float(-sj*ch); mRot.fM44[k][j] = float(cj*sc+cs);  mRot.fM44[k][k] = float(cj*cc-ss);  mRot.zw = 0.0f;
		mRot.wx         = 0.0f;          mRot.wy         = 0.0f;             mRot.wz         = 0.0f;             mRot.ww = 1.0f;
	} else {
		mRot.fM44[i][i] = float(cj*ch);  mRot.fM44[i][j] = float(sj*sc-cs);  mRot.fM44[i][k] = float(sj*cc+ss);  mRot.xw = 0.0f;
		mRot.fM44[j][i] = float(cj*sh);  mRot.fM44[j][j] = float(sj*ss+cc);  mRot.fM44[j][k] = float(sj*cs-sc);  mRot.yw = 0.0f;
		mRot.fM44[k][i] = float(-sj);    mRot.fM44[k][j] = float(cj*si);     mRot.fM44[k][k] = float(cj*ci);     mRot.zw = 0.0f;
		mRot.wx         = 0.0f;          mRot.wy         = 0.0f;             mRot.wz         = 0.0f;             mRot.ww = 1.0f;
	}
}

/**
*  @brief
*    Returns the Euler angles from a rotation matrix
*/
void EulerAngles::FromMatrix(const Matrix3x3 &mRot, float &fAngleX, float &fAngleY, float &fAngleZ, EOrder nOrder)
{
	int i, j, k, h, n, s, f;
	EulGetOrd(nOrder, i, j, k, h, n, s, f);

	if (s == 1) {
		double sy = Math::Sqrt(mRot.fM33[i][j]*mRot.fM33[i][j] + mRot.fM33[i][k]*mRot.fM33[i][k]);
		if (sy > 16*FloatEpsilon) {
			fAngleX = float(Math::ATan2(mRot.fM33[i][j], mRot.fM33[i][k]));
			fAngleY = float(Math::ATan2(sy, (double)mRot.fM33[i][i]));
			fAngleZ = float(Math::ATan2(mRot.fM33[j][i], -mRot.fM33[k][i]));
		} else {
			fAngleX = float(Math::ATan2(-mRot.fM33[j][k], mRot.fM33[j][j]));
			fAngleY = float(Math::ATan2(sy, (double)mRot.fM33[i][i]));
			fAngleZ = 0.0f;
		}
	} else {
		double cy = Math::Sqrt(mRot.fM33[i][i]*mRot.fM33[i][i] + mRot.fM33[j][i]*mRot.fM33[j][i]);
		if (cy > 16*FloatEpsilon) {
			fAngleX = float(Math::ATan2(mRot.fM33[k][j], mRot.fM33[k][k]));
			fAngleY = float(Math::ATan2((double)-mRot.fM33[k][i], cy));
			fAngleZ = float(Math::ATan2(mRot.fM33[j][i], mRot.fM33[i][i]));
		} else {
			fAngleX = float(Math::ATan2(-mRot.fM33[j][k], mRot.fM33[j][j]));
			fAngleY = float(Math::ATan2((double)-mRot.fM33[k][i], cy));
			fAngleZ = 0.0f;
		}
	}

	if (n == 1) {
		fAngleX = -fAngleX;
		fAngleY = -fAngleY;
		fAngleZ = -fAngleZ;
	}
	if (f == 1) {
		float t = fAngleX;
		fAngleX = fAngleZ;
		fAngleZ = t;
	}
}

void EulerAngles::FromMatrix(const Matrix3x4 &mRot, float &fAngleX, float &fAngleY, float &fAngleZ, EOrder nOrder)
{
	int i, j, k, h, n, s, f;
	EulGetOrd(nOrder, i, j, k, h, n, s, f);

	if (s == 1) {
		double sy = Math::Sqrt(mRot.fM43[i][j]*mRot.fM43[i][j] + mRot.fM43[i][k]*mRot.fM43[i][k]);
		if (sy > 16*FloatEpsilon) {
			fAngleX = float(Math::ATan2(mRot.fM43[i][j], mRot.fM43[i][k]));
			fAngleY = float(Math::ATan2(sy, (double)mRot.fM43[i][i]));
			fAngleZ = float(Math::ATan2(mRot.fM43[j][i], -mRot.fM43[k][i]));
		} else {
			fAngleX = float(Math::ATan2(-mRot.fM43[j][k], mRot.fM43[j][j]));
			fAngleY = float(Math::ATan2(sy, (double)mRot.fM43[i][i]));
			fAngleZ = 0.0f;
		}
	} else {
		double cy = Math::Sqrt(mRot.fM43[i][i]*mRot.fM43[i][i] + mRot.fM43[j][i]*mRot.fM43[j][i]);
		if (cy > 16*FloatEpsilon) {
			fAngleX = float(Math::ATan2(mRot.fM43[k][j], mRot.fM43[k][k]));
			fAngleY = float(Math::ATan2((double)-mRot.fM43[k][i], cy));
			fAngleZ = float(Math::ATan2(mRot.fM43[j][i], mRot.fM43[i][i]));
		} else {
			fAngleX = float(Math::ATan2(-mRot.fM43[j][k], mRot.fM43[j][j]));
			fAngleY = float(Math::ATan2((double)-mRot.fM43[k][i], cy));
			fAngleZ = 0.0f;
		}
	}

	if (n == 1) {
		fAngleX = -fAngleX;
		fAngleY = -fAngleY;
		fAngleZ = -fAngleZ;
	}
	if (f == 1) {
		float t = fAngleX;
		fAngleX = fAngleZ;
		fAngleZ = t;
	}
}

void EulerAngles::FromMatrix(const Matrix4x4 &mRot, float &fAngleX, float &fAngleY, float &fAngleZ, EOrder nOrder)
{
	int i, j, k, h, n, s, f;
	EulGetOrd(nOrder, i, j, k, h, n, s, f);

	if (s == 1) {
		double sy = Math::Sqrt(mRot.fM44[i][j]*mRot.fM44[i][j] + mRot.fM44[i][k]*mRot.fM44[i][k]);
		if (sy > 16*FloatEpsilon) {
			fAngleX = float(Math::ATan2(mRot.fM44[i][j], mRot.fM44[i][k]));
			fAngleY = float(Math::ATan2(sy, (double)mRot.fM44[i][i]));
			fAngleZ = float(Math::ATan2(mRot.fM44[j][i], -mRot.fM44[k][i]));
		} else {
			fAngleX = float(Math::ATan2(-mRot.fM44[j][k], mRot.fM44[j][j]));
			fAngleY = float(Math::ATan2(sy, (double)mRot.fM44[i][i]));
			fAngleZ = 0.0f;
		}
	} else {
		double cy = Math::Sqrt(mRot.fM44[i][i]*mRot.fM44[i][i] + mRot.fM44[j][i]*mRot.fM44[j][i]);
		if (cy > 16*FloatEpsilon) {
			fAngleX = float(Math::ATan2(mRot.fM44[k][j], mRot.fM44[k][k]));
			fAngleY = float(Math::ATan2((double)-mRot.fM44[k][i], cy));
			fAngleZ = float(Math::ATan2(mRot.fM44[j][i], mRot.fM44[i][i]));
		} else {
			fAngleX = float(Math::ATan2(-mRot.fM44[j][k], mRot.fM44[j][j]));
			fAngleY = float(Math::ATan2((double)-mRot.fM44[k][i], cy));
			fAngleZ = 0.0f;
		}
	}

	if (n == 1) {
		fAngleX = -fAngleX;
		fAngleY = -fAngleY;
		fAngleZ = -fAngleZ;
	}
	if (f == 1) {
		float t = fAngleX;
		fAngleX = fAngleZ;
		fAngleZ = t;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
