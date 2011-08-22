/*********************************************************\
 *  File: Wrapper.h                                      *
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


#ifndef __PLCORE_WRAPPER_H__
#define __PLCORE_WRAPPER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/PLCore.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static class with some few simple wrappers you can use to avoid for instance nasty standard
*    header includes were they are undesired
*/
class Wrapper {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the number of characters of a c-string excluding the terminating zero
		*
		*  @param[in] szString
		*    C-string to check
		*
		*  @return
		*    The number of characters of the given c-string excluding the terminating zero
		*
		*  @note
		*    - 'strlen'-wrapper
		*/
		PLCORE_API static uint32 GetStringLength(const char szString[]);

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
		PLCORE_API static float Ceil(float fValue);

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
		PLCORE_API static float Log(float x);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_WRAPPER_H__
