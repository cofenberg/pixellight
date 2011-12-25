/*********************************************************\
 *  File: Half.h                                         *
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


#ifndef __PLMATH_HALF_H__
#define __PLMATH_HALF_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
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
*    Static helper class for the half data type (16 bit floating point)
*
*  @note
*    - This class is using information from "Fast Half Float Conversions" (http://www.fox-toolkit.org/ftp/fasthalffloatconversion.pdf)
*      written by Jeroen van der Zijp, November 2008
*/
class Half {


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		// Some half numbers
		static PLMATH_API const PLCore::uint16 Zero;				/**< Representation of 0.0 */
		static PLMATH_API const PLCore::uint16 One;					/**< Representation of 1.0 */

		// Important values
		static PLMATH_API const float SmallestPositive;				/**< Smallest positive half (5.96046448e-08f) */
		static PLMATH_API const float SmallestPositiveNormalized;	/**< Smallest positive normalized half (6.10351562e-05f) */
		static PLMATH_API const float LargestPositive;				/**< Largest positive half (65504.0f) */
		static PLMATH_API const float Epsilon;						/**< Smallest positive epsilon for which 1+e!=1 (0.00097656f) */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns whether or not the given half value is zero
		*
		*  @param[in] nHalf
		*    Half value to check
		*
		*  @return
		*    'true' if the given half value is zero, else 'false'
		*/
		inline static bool IsZero(PLCore::uint16 nHalf);

		/**
		*  @brief
		*    Returns whether or not the given half value is negative
		*
		*  @param[in] nHalf
		*    Half value to check
		*
		*  @return
		*    'true' if the given half value is negative, else 'false'
		*/
		inline static bool IsNegative(PLCore::uint16 nHalf);

		/**
		*  @brief
		*    Returns whether or not the given half value is not a number (NAN)
		*
		*  @param[in] nHalf
		*    Half value to check
		*
		*  @return
		*    'true' if the given half value is not a number, else 'false'
		*/
		inline static bool IsNotANumber(PLCore::uint16 nHalf);

		/**
		*  @brief
		*    Returns whether or not the given half value is finite
		*
		*  @param[in] nHalf
		*    Half value to check
		*
		*  @return
		*    'true' if the given half value is finite, else 'false'
		*/
		inline static bool IsFinite(PLCore::uint16 nHalf);

		/**
		*  @brief
		*    Returns whether or not the given half value is infinity
		*
		*  @param[in] nHalf
		*    Half value to check
		*
		*  @return
		*    'true' if the given half value is infinity, else 'false'
		*/
		inline static bool IsInfinity(PLCore::uint16 nHalf);

		/**
		*  @brief
		*    Returns whether or not the given half value is normalized
		*
		*  @param[in] nHalf
		*    Half value to check
		*
		*  @return
		*    'true' if the given half value is normalized, else 'false'
		*/
		inline static bool IsNormalized(PLCore::uint16 nHalf);

		/**
		*  @brief
		*    Returns whether or not the given half value is de-normalized
		*
		*  @param[in] nHalf
		*    Half value to check
		*
		*  @return
		*    'true' if the given half value is de-normalized, else 'false'
		*/
		inline static bool IsDenormalized(PLCore::uint16 nHalf);

		/**
		*  @brief
		*    Converts a given half value into a float value
		*
		*  @param[in] nHalf
		*    Half value to convert
		*
		*  @return
		*    The given half value as float
		*
		*  [TODO]
		*    - Implement
		*/
		inline static float ToFloat(PLCore::uint16 nHalf);

		/**
		*  @brief
		*    Converts a given float value into a half value
		*
		*  @param[in] fFloat
		*    Float value to convert
		*
		*  @return
		*    The given float value as half
		*
		*  [TODO]
		*    - Implement
		*/
		inline static PLCore::uint16 FromFloat(float fFloat);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLMath/Half.inl"


#endif // __PLMATH_HALF_H__
