/*********************************************************\
 *  File: Vector4.cpp                                    *
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
#include <PLCore/String/RegEx.h>
#include "PLMath/Matrix4x4.h"
#include "PLMath/Vector4.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLMath {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const Vector4 Vector4::Zero			( 0.0f,  0.0f,  0.0f,  0.0f);
const Vector4 Vector4::One			( 1.0f,  1.0f,  1.0f,  1.0f);
const Vector4 Vector4::NegativeOne	(-1.0f, -1.0f, -1.0f, -1.0f);
const Vector4 Vector4::UnitX		( 1.0f,  0.0f,  0.0f,  1.0f);
const Vector4 Vector4::UnitY		( 0.0f,  1.0f,  0.0f,  1.0f);
const Vector4 Vector4::UnitZ		( 0.0f,  0.0f,  1.0f,  1.0f);
const Vector4 Vector4::UnitW		( 0.0f,  0.0f,  0.0f,  1.0f);
const Vector4 Vector4::NegativeUnitX(-1.0f,  0.0f,  0.0f,  1.0f);
const Vector4 Vector4::NegativeUnitY( 0.0f, -1.0f,  0.0f,  1.0f);
const Vector4 Vector4::NegativeUnitZ( 0.0f,  0.0f, -1.0f,  1.0f);
const Vector4 Vector4::NegativeUnitW( 0.0f,  0.0f,  0.0f, -1.0f);


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Constructors                                          ]
//[-------------------------------------------------------]
Vector4::Vector4(const Vector2 &vV, float fZ, float fW) :
	x(vV.x),
	y(vV.y),
	z(fZ),
	w(fW)
{
}

Vector4::Vector4(const Vector3 &vV, float fW) :
	x(vV.x),
	y(vV.y),
	z(vV.z),
	w(fW)
{
}


//[-------------------------------------------------------]
//[ Assignment operators                                  ]
//[-------------------------------------------------------]
Vector4 &Vector4::operator =(const Vector2 &vV)
{
	x = vV.x;
	y = vV.y;
	z = 0.0f;
	w = 1.0f;
	return *this;
}

Vector4 &Vector4::operator =(const Vector3 &vV)
{
	x = vV.x;
	y = vV.y;
	z = vV.z;
	w = 1.0f;
	return *this;
}

/**
*  @brief
*    Transforms the vector
*/
Vector4 &Vector4::operator *=(const Matrix4x4 &mTrans)
{
	float xt = x, yt = y, zt = z, wt = w;
	x = mTrans.xx*xt + mTrans.xy*yt + mTrans.xz*zt + mTrans.xw*wt;
	y = mTrans.yx*xt + mTrans.yy*yt + mTrans.yz*zt + mTrans.yw*wt;
	z = mTrans.zx*xt + mTrans.zy*yt + mTrans.zz*zt + mTrans.zw*wt;
	w = mTrans.wx*xt + mTrans.wy*yt + mTrans.wz*zt + mTrans.ww*wt;
	return *this;
}


//[-------------------------------------------------------]
//[ Get and set                                           ]
//[-------------------------------------------------------]
Vector4::operator Vector3()
{
	return w ? Vector3(x/w, y/w, z/w) : Vector3(x, y, z);
}

void Vector4::SetXYZ(const Vector3 &vV)
{
	x = vV.x;
	y = vV.y;
	z = vV.z;
}

void Vector4::SetXYZW(const Vector3 &vV, float fW)
{
	x = vV.x;
	y = vV.y;
	z = vV.z;
	w = fW;
}


//[-------------------------------------------------------]
//[ Misc                                                  ]
//[-------------------------------------------------------]
/**
*  @brief
*    Calculates a normalized projection vector
*/
Vector4 &Vector4::GetProjection(const Vector4 &vX, const Vector4 &vN)
{
	*this = vX + vN*(-vN.DotProduct(vX)/vN.DotProduct(vN));
	SetLength(1.0f);

	return *this;
}

/**
*  @brief
*    Project the vector on to the plane created by two direction vectors
*/
Vector4 &Vector4::ProjectPlane(const Vector4 &vV1, const Vector4 &vV2)
{
	Vector4 vT1 = ProjectVector(Vector4::UnitW, vV1);
	Vector4 vT2 = ProjectVector(Vector4::UnitW, vV2);
	x = vT1.x + vT2.x;
	y = vT1.y + vT2.y;
	z = vT1.z + vT2.z;
	w = vT1.w + vT2.w;

	return *this;
}

/**
*  @brief
*    To string
*/
String Vector4::ToString() const
{
	return String::Format("%g %g %g %g", x, y, z, w);
}

/**
*  @brief
*    From string
*/
bool Vector4::FromString(const String &sString)
{
	if (sString.GetLength()) {
		// Parse components
		uint32 nParsePos  = 0;
		uint32 nComponent = 0;
		static RegEx cRegEx("\\s*(\\S+)");
		while (nComponent < 4 && cRegEx.Match(sString, nParsePos)) {
			fV[nComponent++] = cRegEx.GetResult(0).GetFloat();
			nParsePos = cRegEx.GetPosition();
		}

		// Set unused componts to 0
		while (nComponent < 4)
			fV[nComponent++] = 0.0f;

		// Done
		return true;
	} else {
		// Error!
		x = y = z = w = 0.0f;
		return false;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
