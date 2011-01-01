/*********************************************************\
 *  File: Math.inl                                       *
 *      Math inline implementation
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
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


//[-------------------------------------------------------]
//[ Random                                                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns a positive or negative random number
*/
inline int Math::GetRandNeg()
{
	return (GetRand() % 2) ? GetRand() : -int(GetRand());
}

/**
*  @brief
*    Returns a positive or negative float random number between -1..1
*/
inline float Math::GetRandNegFloat()
{
	return (GetRand() % 2) ? GetRandFloat() : -int(GetRandFloat());
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

inline PLGeneral::uint32 Math::Min(PLGeneral::uint32 a, PLGeneral::uint32 b)
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

inline PLGeneral::uint32 Math::Max(PLGeneral::uint32 a, PLGeneral::uint32 b)
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
			if (a < d) return a;
			else	   return d;
		} else {
			if (c < d) return c;
			else	   return d;
		}
	} else {
		if (b < c) {
			if (b < d) return b;
			else	   return d;
		} else {
			if (c < d) return c;
			else	   return d;
		}
	}
}

inline int Math::Min(int a, int b, int c, int d)
{
	if (a < b) {
		if (a < c) {
			if (a < d) return a;
			else	   return d;
		} else {
			if (c < d) return c;
			else	   return d;
		}
	} else {
		if (b < c) {
			if (b < d) return b;
			else	   return d;
		} else {
			if (c < d) return c;
			else	   return d;
		}
	}
}

inline PLGeneral::uint32 Math::Min(PLGeneral::uint32 a, PLGeneral::uint32 b, PLGeneral::uint32 c, PLGeneral::uint32 d)
{
	if (a < b) {
		if (a < c) {
			if (a < d) return a;
			else	   return d;
		} else {
			if (c < d) return c;
			else	   return d;
		}
	} else {
		if (b < c) {
			if (b < d) return b;
			else	   return d;
		} else {
			if (c < d) return c;
			else	   return d;
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
			if (a > d) return a;
			else	   return d;
		} else {
			if (c > d) return c;
			else	   return d;
		}
	} else {
		if (b > c) {
			if (b > d) return b;
			else	   return d;
		} else {
			if (c > d) return c;
			else	   return d;
		}
	}
}

inline int Math::Max(int a, int b, int c, int d)
{
	if (a > b) {
		if (a > c) {
			if (a > d) return a;
			else	   return d;
		} else {
			if (c > d) return c;
			else	   return d;
		}
	} else {
		if (b > c) {
			if (b > d) return b;
			else	   return d;
		} else {
			if (c > d) return c;
			else	   return d;
		}
	}
}

inline PLGeneral::uint32 Math::Max(PLGeneral::uint32 a, PLGeneral::uint32 b, PLGeneral::uint32 c, PLGeneral::uint32 d)
{
	if (a > b) {
		if (a > c) {
			if (a > d) return a;
			else	   return d;
		} else {
			if (c > d) return c;
			else	   return d;
		}
	} else {
		if (b > c) {
			if (b > d) return b;
			else	   return d;
		} else {
			if (c > d) return c;
			else	   return d;
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
