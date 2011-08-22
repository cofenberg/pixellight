/*********************************************************\
 *  File: Math.cpp                                       *
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
#include <math.h>
#include <float.h>
#include <stdlib.h> // For 'rand()'
#include "PLMath/Math.h"


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Linux platform
#ifdef LINUX
	// The 'standard libraries' are not really 'standardized' over all platforms :(
	#define _isnan isnan
	#define _finite finite
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLMath {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const double Math::Pi        = 3.14159265358979323846;
const double Math::Pi2       = 6.28318530717958623200;
const double Math::PiHalf    = 1.57079632679489655800;
const double Math::DegToRad  = 0.01745329251994329576;
const double Math::RadToDeg  = 57.2957795130823208768;
const double Math::Epsilon   = 1.192092896e-07F;
const double Math::Log2Const = 0.693147180559945309417;
const int    Math::RandMax   = 0x7fff;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Floating point                                        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Checks whether the given float-precision floating-point value is not a number (NAN)
*/
bool Math::IsNotANumber(float fValue)
{
	return (_isnan(fValue) != 0);
}

/**
*  @brief
*    Checks whether the given double-precision floating-point value is not a number (NAN)
*/
bool Math::IsNotANumber(double dValue)
{
	return (_isnan(dValue) != 0);
}

/**
*  @brief
*    Checks whether the given float-precision floating-point value is finite
*/
bool Math::IsFinite(float fValue)
{
	return (_finite(fValue) != 0);
}

/**
*  @brief
*    Checks whether the given double-precision floating-point value is finite
*/
bool Math::IsFinite(double dValue)
{
	return (_finite(dValue) != 0);
}


//[-------------------------------------------------------]
//[ Nearest power of two                                  ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the nearest power of 2
*/
int Math::GetNearestPowerOfTwo(int nNumber, bool bLower)
{
	// Check whether this number is already a power of 2
	if (!IsPowerOfTwo(nNumber)) {
		int nLast = 1;
		for (int i=1; i<15; i++) {
			int nNumberT = static_cast<int>(powf(2.0f, static_cast<float>(i)));
			if (nNumber < nNumberT)
				return bLower ? nLast : nNumberT;
			nLast = nNumberT;
		}
	}

	// Return the found number
	return nNumber;
}


//[-------------------------------------------------------]
//[ Random                                                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns a positive random number
*/
uint32 Math::GetRand()
{
	return rand();
}

/**
*  @brief
*    Returns a positive float random number between 0..1
*/
float Math::GetRandFloat()
{
	return rand()/static_cast<float>(RAND_MAX);
}


//[-------------------------------------------------------]
//[ Misc                                                  ]
//[-------------------------------------------------------]
/**
*  @brief
*    Ensures that the given value is within the given interval [fMin, fMax] by clamping the value
*/
float Math::ClampToInterval(float fValue, float fMin, float fMax)
{
	if (fValue > fMax)
		return fMax;
	else if (fValue < fMin)
		return fMin;
	else
		return fValue;
}

/**
*  @brief
*    Ensures that the given value is within the given interval [fMin, fMax] by wrapping the value
*/
float Math::WrapToInterval(float fValue, float fMin, float fMax)
{
	const float fInterval = fMax - fMin;
	if (fInterval) {
		if (fValue > fMax)
			return fValue - floor(fValue/fInterval)*fInterval;
		else if (fValue < fMin)
			return fMax + (fValue - ceil(fValue/fInterval)*fInterval);
		else
			return fValue;
	} else {
		// Hm, an interval of 0?
		return fMin;
	}
}

/**
*  @brief
*    Returns the floor of the given value
*/
float Math::Floor(float fValue)
{
	return floor(fValue);
}

/**
*  @brief
*    Returns the ceil of the given value
*/
float Math::Ceil(float fValue)
{
	return ceil(fValue);
}

/**
*  @brief
*    Returns the rounded value of the given value
*/
float Math::Round(float fValue, uint32 nPrecision)
{
	const float fMultiplier = powf(10.0f, static_cast<float>(nPrecision));
	return floor(fValue*fMultiplier + 0.5f)/fMultiplier;
}

/**
*  @brief
*    Returns the sine of the given angle
*/
float Math::Sin(float fAngle)
{
	return sinf(fAngle);
}

/**
*  @brief
*    Returns the sine of the given angle
*/
double Math::Sin(double dAngle)
{
	return sin(dAngle);
}

/**
*  @brief
*    Returns the arcsine of a given value
*/
float Math::ASin(float fValue)
{
	return asinf(fValue);
}

/**
*  @brief
*    Returns the arcsine of a given value
*/
double Math::ASin(double dValue)
{
	return asin(dValue);
}

/**
*  @brief
*    Returns the cosine (cos) of a given angle
*/
float Math::Cos(float fAngle)
{
	return cosf(fAngle);
}

/**
*  @brief
*    Returns the cosine (cos) of a given angle
*/
double Math::Cos(double dAngle)
{
	return cos(dAngle);
}

/**
*  @brief
*    Returns the arccosine of a given value
*/
float Math::ACos(float fValue)
{
	return acosf(fValue);
}

/**
*  @brief
*    Returns the arccosine of a given value
*/
double Math::ACos(double dValue)
{
	return acos(dValue);
}

/**
*  @brief
*    Returns the tangent (tan) of a given angle
*/
float Math::Tan(float fAngle)
{
	return tanf(fAngle);
}

/**
*  @brief
*    Returns the tangent (tan) of a given angle
*/
double Math::Tan(double dAngle)
{
	return tan(dAngle);
}

/**
*  @brief
*    Returns the arctangent of a given value
*/
float Math::ATan(float fValue)
{
	return atanf(fValue);
}

/**
*  @brief
*    Returns the arctangent of a given value
*/
double Math::ATan(double dValue)
{
	return atan(dValue);
}

/**
*  @brief
*    Returns the arctangent of of y/x
*/
float Math::ATan2(float fX, float fY)
{
	return atan2f(fX, fY);
}

/**
*  @brief
*    Returns the arctangent of of y/x
*/
double Math::ATan2(double dX, double dY)
{
	return atan2(dX, dY);
}

/**
*  @brief
*    Returns the square-root of a given value
*/
float Math::Sqrt(float fValue)
{
	return sqrtf(fValue);
}

/**
*  @brief
*    Returns the square-root of a given value
*/
double Math::Sqrt(double dValue)
{
	return sqrt(dValue);
}

/**
*  @brief
*    Returns x raised to the power of y
*/
float Math::Pow(float x, float y)
{
	return powf(x, y);
}

/**
*  @brief
*    Returns x raised to the power of y
*/
double Math::Pow(double x, double y)
{
	return pow(x, y);
}

/**
*  @brief
*    Returns x raised to the power of y
*/
double Math::Pow(int x, int y)
{
	return pow(static_cast<float>(x), y);
}

/**
*  @brief
*    Returns the natural logarithm of a given number
*/
float Math::Log(float x)
{
	return log(x);
}

/**
*  @brief
*    Returns the natural logarithm of a given number
*/
double Math::Log(double x)
{
	return log(x);
}

/**
*  @brief
*    Returns the base 2 logarithm for a given number, as long as it is not negative, or zero
*/
float Math::Log2(float x)
{
	return static_cast<float>(log(x)/Log2Const);
}

/**
*  @brief
*    Returns the base 2 logarithm for a given number, as long as it is not negative, or zero
*/
double Math::Log2(double x)
{
	return log(x)/Math::Log2Const;
}

/**
*  @brief
*    Returns the e number raised to the power x
*/
float Math::Exp(float x)
{
	return exp(x);
}

/**
*  @brief
*    Returns the e number raised to the power x
*/
double Math::Exp(double x)
{
	return exp(x);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
