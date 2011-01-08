/*********************************************************\
 *  File: Vector2.cpp                                    *
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
#include <PLGeneral/String/RegEx.h>
#include "PLMath/Matrix3x3.h"
#include "PLMath/Matrix3x4.h"
#include "PLMath/Matrix4x4.h"
#include "PLMath/Vector2.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLMath {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const Vector2 Vector2::Zero			( 0.0f,  0.0f);
const Vector2 Vector2::One			( 1.0f,  1.0f);
const Vector2 Vector2::NegativeOne	(-1.0f, -1.0f);
const Vector2 Vector2::UnitX		( 1.0f,  0.0f);
const Vector2 Vector2::UnitY		( 0.0f,  1.0f);
const Vector2 Vector2::NegativeUnitX(-1.0f,  0.0f);
const Vector2 Vector2::NegativeUnitY( 0.0f, -1.0f);


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Constructors                                          ]
//[-------------------------------------------------------]
Vector2::Vector2(const Vector3 &vV) :
	x(vV.x),
	y(vV.y)
{
}

Vector2::Vector2(const Vector4 &vV) :
	x(vV.x),
	y(vV.y)
{
}


//[-------------------------------------------------------]
//[ Assignment operators                                  ]
//[-------------------------------------------------------]
Vector2 &Vector2::operator =(const Vector3 &vV)
{
	x = vV.x;
	y = vV.y;
	return *this;
}

Vector2 &Vector2::operator =(const Vector4 &vV)
{
	x = vV.x;
	y = vV.y;
	return *this;
}

/**
*  @brief
*    Rotates the vector
*/
Vector2 &Vector2::operator *=(const Matrix3x3 &mRot)
{
	float xt = x, yt = y;
	x = mRot.xx*xt + mRot.xy*yt;
	y = mRot.yx*xt + mRot.yy*yt;
	return *this;
}

/**
*  @brief
*    Transforms the vector
*/
Vector2 &Vector2::operator *=(const Matrix3x4 &mRot)
{
	float xt = x, yt = y;
	x = mRot.xx*xt + mRot.xy*yt + mRot.xw;
	y = mRot.yx*xt + mRot.yy*yt + mRot.yw;
	return *this;
}

/**
*  @brief
*    Transforms the vector
*/
Vector2 &Vector2::operator *=(const Matrix4x4 &mTrans)
{
	float xt = x, yt = y;
	float fInvW = 1.0f/(mTrans.wx*xt + mTrans.wy*yt + mTrans.ww);
	x = (mTrans.xx*xt + mTrans.xy*yt + mTrans.xw)*fInvW;
	y = (mTrans.yx*xt + mTrans.yy*yt + mTrans.yw)*fInvW;
	return *this;
}

/**
*  @brief
*    To string
*/
String Vector2::ToString() const
{
	return String::Format("%g %g", x, y);
}

/**
*  @brief
*    From string
*/
bool Vector2::FromString(const String &sString)
{
	if (sString.GetLength()) {
		// Parse components
		uint32 nParsePos  = 0;
		uint32 nComponent = 0;
		static RegEx cRegEx("\\s*(\\S+)");
		while (nComponent < 2 && cRegEx.Match(sString, nParsePos)) {
			fV[nComponent++] = cRegEx.GetResult(0).GetFloat();
			nParsePos = cRegEx.GetPosition();
		}

		// Set unused componts to 0
		while (nComponent < 2)
			fV[nComponent++] = 0.0f;

		// Done
		return true;
	} else {
		// Error!
		x = y = 0.0f;
		return false;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
