/*********************************************************\
 *  File: Half.h                                         *
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


#ifndef __PLMATH_HALF_H__
#define __PLMATH_HALF_H__
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
		PLMATH_API static const PLGeneral::uint16 Zero;				/**< Representation of 0.0 */
		PLMATH_API static const PLGeneral::uint16 One;				/**< Representation of 1.0 */

		// Important values
		PLMATH_API static const float SmallestPositive;				/**< Smallest positive half (5.96046448e-08f) */
		PLMATH_API static const float SmallestPositiveNormalized;	/**< Smallest positive normalized half (6.10351562e-05f) */
		PLMATH_API static const float LargestPositive;				/**< Largest positive half (65504.0f) */
		PLMATH_API static const float Epsilon;						/**< Smallest positive epsilon for which 1+e!=1 (0.00097656f) */


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
		inline static bool IsZero(PLGeneral::uint16 nHalf);

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
		inline static bool IsNegative(PLGeneral::uint16 nHalf);

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
		inline static bool IsNotANumber(PLGeneral::uint16 nHalf);

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
		inline static bool IsFinite(PLGeneral::uint16 nHalf);

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
		inline static bool IsInfinity(PLGeneral::uint16 nHalf);

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
		inline static bool IsNormalized(PLGeneral::uint16 nHalf);

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
		inline static bool IsDenormalized(PLGeneral::uint16 nHalf);

		/**
		*  @brief
		*    Convertes a given half value into a float value
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
		inline static float ToFloat(PLGeneral::uint16 nHalf);

		/**
		*  @brief
		*    Convertes a given float value into a half value
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
		inline static PLGeneral::uint16 FromFloat(float fFloat);


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
