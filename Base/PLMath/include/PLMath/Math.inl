/*********************************************************\
 *  File: Math.inl                                       *
 *      Math inline implementation
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


// For performance reasons we include so called "standard headers" in here even if they are not standardized across all platforms.
// Usually the used headers don't introduce definition conflicts across the platforms, so, this should be fine... but it's still
// highly recommended to use this "Math" helper class in case there are issues on a new platform. Changing this one header
// is easier than changing all source codes of all projects.


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <math.h>
#include <float.h>
#include <stdlib.h> // For 'rand()'


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// The 'standard libraries' are not really 'standardized' over all platforms :(
#ifdef APPLE
	#define _isnan	isnan
	#define _finite	isfinite
#elif LINUX
	#define _isnan	isnan
	#define _finite	finite
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


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
*    Check's whether the given the number is a power of 2
*/
inline bool Math::IsPowerOfTwo(int nNumber)
{
	return ((nNumber & (nNumber-1)) == 0);
}

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
PLCore::uint32 Math::GetRand()
{
	return rand();
}

/**
*  @brief
*    Returns a positive or negative random number
*/
inline int Math::GetRandNeg()
{
	return (GetRand() % 2) ? GetRand() : -static_cast<int>(GetRand());
}

/**
*  @brief
*    Returns a positive float random number between 0..1
*/
float Math::GetRandFloat()
{
	return rand()/static_cast<float>(RAND_MAX);
}

/**
*  @brief
*    Returns a positive or negative float random number between -1..1
*/
inline float Math::GetRandNegFloat()
{
	return (GetRand() % 2) ? GetRandFloat() : -GetRandFloat();
}

/**
*  @brief
*    Returns a float random number between the given minimum/maximum
*/
float Math::GetRandMinMaxFloat(float fMin, float fMax)
{
	return fMin + GetRandFloat()*(fMax-fMin);
}


//[-------------------------------------------------------]
//[ Misc                                                  ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns a whether to given numbers are equal or not
*/
inline bool Math::AreEqual(float f1, float f2, float fEpsilon)
{
	return (f2 >= f1-fEpsilon && f2 <= f1+fEpsilon);
}

/**
*  @brief
*    Returns a whether to given numbers are equal or not
*/
inline bool Math::AreEqual(double d1, double d2, double dEpsilon)
{
	return (d2 >= d1-dEpsilon && d2 <= d1+dEpsilon);
}

/**
*  @brief
*    Returns the minimum of the 2 given values
*/
inline float Math::Min(float a, float b)
{
	return (a < b) ? a : b;
}

inline int Math::Min(int a, int b)
{
	return (a < b) ? a : b;
}

inline PLCore::uint32 Math::Min(PLCore::uint32 a, PLCore::uint32 b)
{
	return (a < b) ? a : b;
}

/**
*  @brief
*    Returns the maximum of the 2 given values
*/
inline float Math::Max(float a, float b)
{
	return (a > b) ? a : b;
}

inline int Math::Max(int a, int b)
{
	return (a > b) ? a : b;
}

inline PLCore::uint32 Math::Max(PLCore::uint32 a, PLCore::uint32 b)
{
	return (a > b) ? a : b;
}

/**
*  @brief
*    Returns the minimum of the 4 given values
*/
inline float Math::Min(float a, float b, float c, float d)
{
	if (a < b) {
		if (a < c) {
			if (a < d)
				return a;
			else
				return d;
		} else {
			if (c < d)
				return c;
			else
				return d;
		}
	} else {
		if (b < c) {
			if (b < d)
				return b;
			else
				return d;
		} else {
			if (c < d)
				return c;
			else
				return d;
		}
	}
}

inline int Math::Min(int a, int b, int c, int d)
{
	if (a < b) {
		if (a < c) {
			if (a < d)
				return a;
			else
				return d;
		} else {
			if (c < d)
				return c;
			else
				return d;
		}
	} else {
		if (b < c) {
			if (b < d)
				return b;
			else
				return d;
		} else {
			if (c < d)
				return c;
			else
				return d;
		}
	}
}

inline PLCore::uint32 Math::Min(PLCore::uint32 a, PLCore::uint32 b, PLCore::uint32 c, PLCore::uint32 d)
{
	if (a < b) {
		if (a < c) {
			if (a < d)
				return a;
			else
				return d;
		} else {
			if (c < d)
				return c;
			else
				return d;
		}
	} else {
		if (b < c) {
			if (b < d)
				return b;
			else
				return d;
		} else {
			if (c < d)
				return c;
			else
				return d;
		}
	}
}

/**
*  @brief
*    Returns the maximum of the 4 given values
*/
inline float Math::Max(float a, float b, float c, float d)
{
	if (a > b) {
		if (a > c) {
			if (a > d)
				return a;
			else
				return d;
		} else {
			if (c > d)
				return c;
			else
				return d;
		}
	} else {
		if (b > c) {
			if (b > d)
				return b;
			else
				return d;
		} else {
			if (c > d)
				return c;
			else
				return d;
		}
	}
}

inline int Math::Max(int a, int b, int c, int d)
{
	if (a > b) {
		if (a > c) {
			if (a > d)
				return a;
			else
				return d;
		} else {
			if (c > d)
				return c;
			else
				return d;
		}
	} else {
		if (b > c) {
			if (b > d)
				return b;
			else
				return d;
		} else {
			if (c > d)
				return c;
			else
				return d;
		}
	}
}

inline PLCore::uint32 Math::Max(PLCore::uint32 a, PLCore::uint32 b, PLCore::uint32 c, PLCore::uint32 d)
{
	if (a > b) {
		if (a > c) {
			if (a > d)
				return a;
			else
				return d;
		} else {
			if (c > d)
				return c;
			else
				return d;
		}
	} else {
		if (b > c) {
			if (b > d)
				return b;
			else
				return d;
		} else {
			if (c > d)
				return c;
			else
				return d;
		}
	}
}

/**
*  @brief
*    Returns the sign of the given value
*/
inline float Math::Sign(float x)
{
	return (x < 0.0f) ? -1.0f : 1.0f;
}

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
*    Returns the absolute value of the given value
*/
inline int Math::Abs(int x)
{
	return (x > 0.0f) ? x : -x;
}

/**
*  @brief
*    Returns the absolute value of the given value
*/
inline float Math::Abs(float x)
{
	return (x > 0.0f) ? x : -x;
}

/**
*  @brief
*    Returns the absolute value of the given value
*/
inline double Math::Abs(double x)
{
	return (x > 0.0) ? x : -x;
}

/**
*  @brief
*    Swaps two given values
*/
inline void Math::Swap(float &a, float &b)
{
	const float fTemp = a;
	a = b;
	b = fTemp;
}

/**
*  @brief
*    Clamps the value between 0.0 and 1.0
*/
inline float Math::Saturate(float fValue)
{
	if (fValue < 0.0f)
		return 0.0f;
	if (fValue > 1.0f)
		return 1.0f;
	return fValue;
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
float Math::Round(float fValue, PLCore::uint32 nPrecision)
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
*    Returns the inverse square-root of a given value
*/
float Math::FastInvSqrt(float fValue)
{
	// The orignal author of the following code is unknown, in the 3D graphics community there are rumours who could be the orignal author:
	// - See Beyond3D article "Origin of Quake3's Fast InvSqrt()" at www.beyond3d.com/content/articles/8/ and http://www.beyond3d.com/content/articles/15
	// - See "Fast inverse square root" at http://en.wikipedia.org/wiki/Fast_inverse_square_root
	const float fThreeHalfs = 1.5f;
	float x2 = fValue*0.5f;
	float y  = fValue;
	long i   = *reinterpret_cast<long*>(&y);
	i        = 0x5f3759df - (i>>1);
	y        = *reinterpret_cast<float*>(&i);
	y        = y*(fThreeHalfs - (x2*y*y));
	return y;
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
