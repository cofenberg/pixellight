/*********************************************************\
 *  File: Functions.h                                    *
 *      Different useful container functions
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


#ifndef __PLCORE_CONTAINER_FUNCTIONS_H__
#define __PLCORE_CONTAINER_FUNCTIONS_H__
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
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class String;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Different standard hash functions
*/
class HashFunction {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		PLCORE_API static uint32 Hash(const int32 &nKey);
		PLCORE_API static uint32 Hash(const uint32 &nKey);
		PLCORE_API static uint32 Hash(const int64 &nKey);
		PLCORE_API static uint32 Hash(const uint64 &nKey);
		PLCORE_API static uint32 Hash(const char *pszKey);
		PLCORE_API static uint32 Hash(const String &sKey);


};

/**
*  @brief
*    Standard compare function
*/
class CompareFunction {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		// int32
		PLCORE_API static bool AreEqual(const int32 &nKey1, const int32 &nKey2);
		PLCORE_API static bool IsGreater(const int32 &nKey1, const int32 &nKey2);

		// uint32
		PLCORE_API static bool AreEqual(const uint32 &nKey1, const uint32 &nKey2);
		PLCORE_API static bool IsGreater(const uint32 &nKey1, const uint32 &nKey2);

		// int64
		PLCORE_API static bool AreEqual(const int64 &nKey1, const int64 &nKey2);
		PLCORE_API static bool IsGreater(const int64 &nKey1, const int64 &nKey2);

		// uint64
		PLCORE_API static bool AreEqual(const uint64 &nKey1, const uint64 &nKey2);
		PLCORE_API static bool IsGreater(const uint64 &nKey1, const uint64 &nKey2);

		// float
		PLCORE_API static bool AreEqual(const float &fKey1, const float &fKey2);
		PLCORE_API static bool IsGreater(const float &fKey1, const float &fKey2);

		// const char *
		PLCORE_API static bool AreEqual(const char *pszKey1, const char *pszKey2);
		PLCORE_API static bool IsGreater(const char *pszKey1, const char *pszKey2);

		// String
		PLCORE_API static bool AreEqual(const String &sKey1, const String &sKey2);
		PLCORE_API static bool IsGreater(const String &sKey1, const String &sKey2);


};

/**
*  @brief
*    Standard grow functions
*
*  @remarks
*    The default grow function makes sure that there are at least 10% slots, if not, a new
*    size basing on prime numbers is returned.
*/
class GrowFunction {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns a new size
		*
		*  @param[in] nCurrentSize
		*    Current size
		*  @param[in] nFreeSlots
		*    Number of free slots
		*
		*  @return
		*    New size, if <= current size then no grow is required
		*/
		PLCORE_API static uint32 GetNewSize(uint32 nCurrentSize, uint32 nFreeSlots);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CONTAINER_FUNCTIONS_H__
