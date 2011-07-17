/*********************************************************\
 *  File: Math.h                                         *
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


#ifndef __PLMATH_MATH_H__
#define __PLMATH_MATH_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneral.h>
#include "PLMath/PLMath.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static class with some useful math constants and functions
*/
class Math {


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		PLMATH_API static const double Pi;			/**< 3.14159265358979323846 */
		PLMATH_API static const double Pi2;			/**< 6.28318530717958623200 (Pi*2) */
		PLMATH_API static const double PiHalf;		/**< 1.57079632679489655800 (Pi/2) */
		PLMATH_API static const double DegToRad;	/**< 0.01745329251994329576 (Pi/180) */
		PLMATH_API static const double RadToDeg;	/**< 57.2957795130823208768 (180/Pi) */
		PLMATH_API static const double Epsilon;		/**< 1.192092896e-07F */
		PLMATH_API static const double Log2Const;	/**< 0.693147180559945309417 */
		PLMATH_API static const int    RandMax;		/**< Maximum random value (0x7fff) */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ Floating point                                        ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Checks whether the given float-precision floating-point value is not a number (NAN)
		*
		*  @return
		*    'true' if the value is not a number, else 'false'
		*/
		PLMATH_API static bool IsNotANumber(float fValue);

		/**
		*  @brief
		*    Checks whether the given double-precision floating-point value is not a number (NAN)
		*
		*  @return
		*    'true' if the value is not a number, else 'false'
		*/
		PLMATH_API static bool IsNotANumber(double dValue);

		/**
		*  @brief
		*    Checks whether the given float-precision floating-point value is finite
		*
		*  @return
		*    'true' if the value is finite, (–INF < fValue < +INF) else 'false' (infinite or not a number)
		*/
		PLMATH_API static bool IsFinite(float fValue);

		/**
		*  @brief
		*    Checks whether the given double-precision floating-point value is finite
		*
		*  @return
		*    'true' if the value is finite, (–INF < dValue < +INF) else 'false' (infinite or not a number)
		*/
		PLMATH_API static bool IsFinite(double dValue);

		//[-------------------------------------------------------]
		//[ Nearest power of two                                  ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Check's whether the given the number is a power of 2
		*
		*  @param[in] nNumber
		*    Number to check
		*
		*  @return
		*    'true' if the number is a power of 2, else 'false'
		*/
		inline static bool IsPowerOfTwo(int nNumber);

		/**
		*  @brief
		*    Returns the nearest power of 2
		*
		*  @param[in] nNumber
		*    Number to check
		*  @param[in] bLower
		*    'true' take the lower nearest number, else 'false' takes the higher one
		*
		*  @return
		*    The nearest power of 2, if it couldn't be found 'nNumber'
		*/
		PLMATH_API static int GetNearestPowerOfTwo(int nNumber, bool bLower = true);

		//[-------------------------------------------------------]
		//[ Random                                                ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns a positive random number
		*
		*  @return
		*    A positive random number
		*/
		PLMATH_API static PLGeneral::uint32 GetRand();

		/**
		*  @brief
		*    Returns a positive or negative random number
		*
		*  @return
		*    A positive or negative random number
		*/
		inline static int GetRandNeg();

		/**
		*  @brief
		*    Returns a positive float random number between 0..1
		*
		*  @return
		*    A positive float random number between 0..1
		*/
		PLMATH_API static float GetRandFloat();

		/**
		*  @brief
		*    Returns a positive or negative float random number between -1..1
		*
		*  @return
		*    A positive or negative float random number between -1..1
		*/
		inline static float GetRandNegFloat();

		/**
		*  @brief
		*    Returns a float random number between the given minimum/maximum
		*
		*  @param[in] fMin
		*    Minimum (inclusive), must be <= maximum
		*  @param[in] fMax
		*    Maximum (inclusive), must be >= minimum
		*
		*  @return
		*    A float random number between the given minimum/maximum
		*/
		inline static float GetRandMinMaxFloat(float fMin, float fMax);

		//[-------------------------------------------------------]
		//[ Misc                                                  ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns a whether to given numbers are equal or not
		*
		*  @param[in] f1
		*    First number
		*  @param[in] f2
		*    Second number
		*  @param[in] fEpsilon
		*    Error tolerance
		*
		*  @return
		*    'true' if the given numbers are equal, else 'false'
		*/
		inline static bool AreEqual(float f1, float f2, float fEpsilon = Math::Epsilon);

		/**
		*  @brief
		*    Returns a whether to given numbers are equal or not
		*
		*  @param[in] d1
		*    First number
		*  @param[in] d2
		*    Second number
		*  @param[in] dEpsilon
		*    Error tolerance
		*
		*  @return
		*    'true' if the given numbers are equal, else 'false'
		*/
		inline static bool AreEqual(double d1, double d2, double dEpsilon = Math::Epsilon);

		/**
		*  @brief
		*    Returns the minimum of the 2 given values
		*
		*  @param[in] a
		*    First value
		*  @param[in] b
		*    Second value
		*
		*  @return
		*    The minimum of the 2 given values
		*/
		inline static float Min(float a, float b);
		inline static int Min(int a, int b);
		inline static PLGeneral::uint32 Min(PLGeneral::uint32 a, PLGeneral::uint32 b);

		/**
		*  @brief
		*    Returns the maximum of the 2 given values
		*
		*  @param[in] a
		*    First value
		*  @param[in] b
		*    Second value
		*
		*  @return
		*    The maximum of the 2 given values
		*/
		inline static float Max(float a, float b);
		inline static int Max(int a, int b);
		inline static PLGeneral::uint32 Max(PLGeneral::uint32 a, PLGeneral::uint32 b);

		/**
		*  @brief
		*    Returns the minimum of the 4 given values
		*
		*  @param[in] a
		*    First value
		*  @param[in] b
		*    Second value
		*  @param[in] c
		*    Third value
		*  @param[in] d
		*    Fourth value
		*
		*  @return
		*    The minimum of the 4 given values
		*/
		inline static float Min(float a, float b, float c, float d);
		inline static int Min(int a, int b, int c, int d);
		inline static PLGeneral::uint32 Min(PLGeneral::uint32 a, PLGeneral::uint32 b, PLGeneral::uint32 c, PLGeneral::uint32 d);

		/**
		*  @brief
		*    Returns the maximum of the 4 given values
		*
		*  @param[in] a
		*    First value
		*  @param[in] b
		*    Second value
		*  @param[in] c
		*    Third value
		*  @param[in] d
		*    Fourth value
		*
		*  @return
		*    The maximum of the 4 given values
		*/
		inline static float Max(float a, float b, float c, float d);
		inline static int Max(int a, int b, int c, int d);
		inline static PLGeneral::uint32 Max(PLGeneral::uint32 a, PLGeneral::uint32 b, PLGeneral::uint32 c, PLGeneral::uint32 d);

		/**
		*  @brief
		*    Returns the sign of the given value
		*
		*  @param[in] x
		*    Value to check
		*
		*  @return
		*    '-1' if the given value is negative, else '1'
		*/
		inline static float Sign(float x);

		/**
		*  @brief
		*    Ensures that the given value is within the given interval [fMin, fMax] by clamping the value
		*
		*  @param[in] fValue
		*    Value to check
		*  @param[in] fMin
		*    Minimum of the interval, must be < fMax!
		*  @param[in] fMax
		*    Maximum of the interval, must be > fMin!
		*
		*  @return
		*    The value within the interval [fMin, fMax]
		*/
		PLMATH_API static float ClampToInterval(float fValue, float fMin, float fMax);

		/**
		*  @brief
		*    Ensures that the given value is within the given interval [fMin, fMax] by wrapping the value
		*
		*  @param[in] fValue
		*    Value to check
		*  @param[in] fMin
		*    Minimum of the interval, must be < fMax!
		*  @param[in] fMax
		*    Maximum of the interval, must be > fMin!
		*
		*  @return
		*    The value within the interval [fMin, fMax]
		*/
		PLMATH_API static float WrapToInterval(float fValue, float fMin, float fMax);

		/**
		*  @brief
		*    Returns the absolute value of the given value
		*
		*  @param[in] x
		*    Value to return the absolut value from
		*
		*  @return
		*    Absolute value of the given value
		*/
		inline static int Abs(int x);

		/**
		*  @brief
		*    Returns the absolute value of the given value
		*
		*  @param[in] x
		*    Value to return the absolut value from
		*
		*  @return
		*    Absolute value of the given value
		*/
		inline static float Abs(float x);

		/**
		*  @brief
		*    Returns the absolute value of the given value
		*
		*  @param[in] x
		*    Value to return the absolut value from
		*
		*  @return
		*    Absolute value of the given value
		*/
		inline static double Abs(double x);

		/**
		*  @brief
		*    Swaps two given values
		*
		*  @param[in, out] a
		*    First value
		*  @param[in, out] b
		*    Second value
		*/
		inline static void Swap(float &a, float &b);

		/**
		*  @brief
		*    Clamps the value between 0.0 and 1.0
		*
		*  @param[in] fValue
		*    Value to clamp
		*
		*  @return
		*    Clamped value
		*/
		inline static float Saturate(float fValue);

		/**
		*  @brief
		*    Returns the floor of the given value
		*
		*  @param[in] fValue
		*    Value to return the floor from
		*
		*  @return
		*    The floor of the given value
		*
		*  @remarks
		*    This function returns a floating-point value representing the largest integer value that
		*    is less than or equal to the given value.
		*/
		PLMATH_API static float Floor(float fValue);

		/**
		*  @brief
		*    Returns the ceil of the given value
		*
		*  @param[in] fValue
		*    Value to return the ceil from
		*
		*  @return
		*    The ceil of the given value
		*
		*  @remarks
		*    This function returns a floating-point value representing the smallest integer value
		*    that is greater than or equal to the given value.
		*/
		PLMATH_API static float Ceil(float fValue);

		/**
		*  @brief
		*    Returns the rounded value of the given value
		*
		*  @param[in] fValue
		*    Value to return the rounded value from
		*  @param[in] nPrecision
		*    Number of digits after the comma
		*
		*  @return
		*    The rounded value of the given value
		*/
		PLMATH_API static float Round(float fValue, PLGeneral::uint32 nPrecision = 0);

		/**
		*  @brief
		*    Returns the sine of a given angle
		*
		*  @param[in] fAngle
		*    Angle in radians
		*
		*  @return
		*    Sine of the given angle
		*
		*  @note
		*    - If the given angle is greater than or equal to 263, or less
		*      than or equal to –263, a loss of significance in the result occurs
		*    - Sine of 0 is 0
		*/
		PLMATH_API static float Sin(float fAngle);

		/**
		*  @brief
		*    Returns the sine of a given angle
		*
		*  @param[in] dAngle
		*    Angle in radians
		*
		*  @return
		*    Sine of the given angle
		*
		*  @see
		*    - Sin(float) above
		*/
		PLMATH_API static double Sin(double dAngle);

		/**
		*  @brief
		*    Returns the arcsine of a given value
		*
		*  @param[in] fValue
		*    Value between –1 and 1 whose arcsine is to be calculated
		*
		*  @return
		*    Arcsine of the given value
		*
		*  @remarks
		*    This function returns the arcsine of the given value in the range –p/2 to p/2 radians.
		*    If the given value is less than –1 or greater than 1, ASin returns an indefinite
		*    (same as a quiet NaN).
		*/
		PLMATH_API static float ASin(float fValue);

		/**
		*  @brief
		*    Returns the arcsine of a given value
		*
		*  @param[in] dValue
		*    Value between –1 and 1 whose arcsine is to be calculated
		*
		*  @return
		*    Arcsine of the given value
		*
		*  @see
		*    - ASin(float) above
		*/
		PLMATH_API static double ASin(double dValue);

		/**
		*  @brief
		*    Returns the cosine (cos) of a given angle
		*
		*  @param[in] fAngle
		*    Angle in radians
		*
		*  @return
		*    Cosine of the given angle
		*
		*  @note
		*    - If the given angle is greater than or equal to 263, or less
		*      than or equal to –263, a loss of significance in the result occurs
		*    - Cosine of 0 is 1
		*/
		PLMATH_API static float Cos(float fAngle);

		/**
		*  @brief
		*    Returns the cosine (cos) of a given angle
		*
		*  @param[in] dAngle
		*    Angle in radians
		*
		*  @return
		*    Cosine of the given angle
		*
		*  @see
		*    - Cos(float) above
		*/
		PLMATH_API static double Cos(double dAngle);

		/**
		*  @brief
		*    Returns the arccosine of a given value
		*
		*  @param[in] fValue
		*    Value between –1 and 1 whose arccosine is to be calculated
		*
		*  @return
		*    Arccosine of the given value
		*
		*  @remarks
		*    This function returns the arccosine of the given value in the range –p/2 to p/2 radians.
		*    If the given value is less than –1 or greater than 1, ACos returns an indefinite
		*    (same as a quiet NaN).
		*/
		PLMATH_API static float ACos(float fValue);

		/**
		*  @brief
		*    Returns the arccosine of a given value
		*
		*  @param[in] dValue
		*    Value between –1 and 1 whose arccosine is to be calculated
		*
		*  @return
		*    Arccosine of the given value
		*
		*  @see
		*    - ACos(float) above
		*/
		PLMATH_API static double ACos(double dValue);

		/**
		*  @brief
		*    Returns the tangent (tan) of a given angle
		*
		*  @param[in] fAngle
		*    Angle in radians
		*
		*  @return
		*    Tangent of the given angle
		*
		*  @note
		*    - If the given angle is greater than or equal to 263, or less
		*      than or equal to –263, a loss of significance in the result occurs
		*    - Tangent of 0 is 0
		*/
		PLMATH_API static float Tan(float fAngle);

		/**
		*  @brief
		*    Returns the tangent (tan) of a given angle
		*
		*  @param[in] dAngle
		*    Angle in radians
		*
		*  @return
		*    Tangent of the given angle
		*
		*  @see
		*    - Tan(float) above
		*/
		PLMATH_API static double Tan(double dAngle);

		/**
		*  @brief
		*    Returns the arctangent of a given value
		*
		*  @param[in] fValue
		*    Value between –1 and 1 whose arccosine is to be calculated
		*
		*  @return
		*    Arccosine of the given value
		*/
		PLMATH_API static float ATan(float fValue);

		/**
		*  @brief
		*    Returns the arctangent of a given value
		*
		*  @param[in] dValue
		*    Value between –1 and 1 whose arccosine is to be calculated
		*
		*  @return
		*    Arccosine of the given value
		*/
		PLMATH_API static double ATan(double dValue);

		/**
		*  @brief
		*    Returns the arctangent of of y/x
		*
		*  @param[in] fX
		*    Any number
		*  @param[in] fY
		*    Any number
		*
		*  @return
		*    Arccosine of y/x
		*
		*  @remarks
		*    Returns a value in the range –p to p radians, using the signs of both parameters
		*    to determine the quadrant of the return value
		*
		*  @note
		*    - If fX is 0, this function returns 0
		*    - If both parameters are 0, the function returns 0
		*/
		PLMATH_API static float ATan2(float fX, float fY);

		/**
		*  @brief
		*    Returns the arctangent of of y/x
		*
		*  @param[in] dX
		*    Any number
		*  @param[in] dY
		*    Any number
		*
		*  @return
		*    Arccosine of y/x
		*
		*  @see
		*    - ATan2(float, float) above
		*/
		PLMATH_API static double ATan2(double dX, double dY);

		/**
		*  @brief
		*    Returns the square-root of a given value
		*
		*  @param[in] fValue
		*    Nonnegative floating-point value, If negative, this function returns an indefinite
		*    (same as a quiet NaN)
		*
		*  @return
		*    The square-root of the given value, indefinite on error
		*/
		PLMATH_API static float Sqrt(float fValue);

		/**
		*  @brief
		*    Returns the square-root of a given value
		*
		*  @param[in] dValue
		*    Nonnegative floating-point value, If negative, this function returns an indefinite
		*    (same as a quiet NaN)
		*
		*  @return
		*    The square-root of the given value, indefinite on error
		*/
		PLMATH_API static double Sqrt(double dValue);

		/**
		*  @brief
		*    Returns x raised to the power of y
		*
		*  @param[in] x
		*    Base
		*  @param[in] y
		*    Exponent 
		*
		*  @return
		*    x raised to the power of y
		*/
		PLMATH_API static float Pow(float x, float y);

		/**
		*  @brief
		*    Returns x raised to the power of y
		*
		*  @param[in] x
		*    Base
		*  @param[in] y
		*    Exponent
		*
		*  @return
		*    x raised to the power of y
		*/
		PLMATH_API static double Pow(double x, double y);

		/**
		*  @brief
		*    Returns x raised to the power of y
		*
		*  @param[in] x
		*    Base
		*  @param[in] y
		*    Exponent
		*
		*  @return
		*    x raised to the power of y
		*/
		PLMATH_API static double Pow(int x, int y);

		/**
		*  @brief
		*    Returns the natural logarithm of a given number
		*
		*  @param[in] x
		*    Given number
		*
		*  @return
		*    The natural logarithm of the given number
		*/
		PLMATH_API static float Log(float x);

		/**
		*  @brief
		*    Returns the natural logarithm of a given number
		*
		*  @param[in] x
		*    Given number
		*
		*  @return
		*    The natural logarithm of the given number
		*/
		PLMATH_API static double Log(double x);

		/**
		*  @brief
		*    Returns the base 2 logarithm for a given number, as long as it is not negative, or zero
		*
		*  @param[in] x
		*    Given number
		*
		*  @return
		*    The base 2 logarithm for the given number, as long as it is not negative, or zero
		*
		*  @remarks
		*    Log(x)/Log(2)
		*/
		PLMATH_API static float Log2(float x);

		/**
		*  @brief
		*    Returns the base 2 logarithm for a given number, as long as it is not negative, or zero
		*
		*  @param[in] x
		*    Given number
		*
		*  @return
		*    The base 2 logarithm for the given number, as long as it is not negative, or zero
		*
		*  @remarks
		*    Log(x)/Log(2)
		*/
		PLMATH_API static double Log2(double x);

		/**
		*  @brief
		*    Returns the e number raised to the power x
		*
		*  @param[in] x
		*    Given number
		*
		*  @return
		*    The e number raised to the power x
		*/
		PLMATH_API static float Exp(float x);

		/**
		*  @brief
		*    Returns the e number raised to the power x
		*
		*  @param[in] x
		*    Given number
		*
		*  @return
		*    The e number raised to the power x
		*/
		PLMATH_API static double Exp(double x);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLMath/Math.inl"


#endif // __PLMATH_MATH_H__
