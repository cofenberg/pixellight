/*********************************************************\
 *  File: ParseTools.h                                   *
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


#ifndef __PLGENERAL_PARSETOOLS_H__
#define __PLGENERAL_PARSETOOLS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static class with some useful string parse tool functions
*/
class ParseTools {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Parse string containing a hex value to an integer (for example "FF" => "255")
		*
		*  @param[in] sString
		*    String containing a hex value
		*
		*  @return
		*    Integer representation of the given hex value
		*/
		PLGENERAL_API static uint32 ParseHexValue(const String &sString);

		/**
		*  @brief
		*    Parse an array of integer values
		*
		*  @param[in]  sString
		*    String containing integer numbers
		*  @param[out] pnValues
		*    Pointer to C-array which will receive the integer values, if NULL nothing happens
		*  @param[in]  nMaxNumOfElements
		*    The maximum number of elements 'nValues' can hold
		*
		*  @return
		*    The number of read values
		*
		*  @note
		*    - Example string with three values: "0 5 34"
		*/
		PLGENERAL_API static int ParseIntegerArray(const String &sString, int *pnValues, uint32 nMaxNumOfElements);

		/**
		*  @brief
		*    Parse an array of float values
		*
		*  @param[in]  sString
		*    String containing floating point numbers
		*  @param[out] pfValues
		*    Pointer to C-array which will receive the float values, if NULL nothing happens
		*  @param[in]  nMaxNumOfElements
		*    The maximum number of elements 'fValues' can hold
		*
		*  @return
		*    The number of read values
		*
		*  @note
		*    - Example string with three values: "0 0.0 34.245"
		*/
		PLGENERAL_API static int ParseFloatArray(const String &sString, float *pfValues, uint32 nMaxNumOfElements);

		/**
		*  @brief
		*    Parse an array of double values
		*
		*  @param[in]  sString
		*    String containg double precision floating point numbers
		*  @param[out] pdValues
		*    Pointer to C-array which will receive the double values, if NULL nothing happens
		*  @param[in]  nMaxNumOfElements
		*    The maximum number of elements 'dValues' can hold
		*
		*  @return
		*    The number of read values
		*
		*  @note
		*    - Example string with three values: "0 0.0 34.245"
		*/
		PLGENERAL_API static int ParseDoubleArray(const String &sString, double *pdValues, uint32 nMaxNumOfElements);

		//[-------------------------------------------------------]
		//[ Flags                                                 ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the flags from a string
		*
		*  @param[in] sFlags
		*    String containing flags
		*
		*  @return
		*    The flags from the string
		*
		*  @remarks
		*    Flags can be stored in strings too. (easy to edit :)\n
		*    Example: "1|2|4|8"
		*/
		PLGENERAL_API static uint32 GetFlagsFromString(const String &sFlags);

		/**
		*  @brief
		*    Creates a string from flags
		*
		*  @param[in] nFlags
		*    Flags value
		*
		*  @return
		*    String containing the flags in textual form
		*
		*  @see
		*    - GetFlagsFromString()
		*/
		PLGENERAL_API static String GetStringFromFlags(uint32 nFlags);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_PARSETOOLS_H__
