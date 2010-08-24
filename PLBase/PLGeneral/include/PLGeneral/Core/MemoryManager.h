/*********************************************************\
 *  File: MemoryManager.h                                *
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


#ifndef __PLGENERAL_MEMORYMANAGER_H__
#define __PLGENERAL_MEMORYMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/PLGeneral.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static memory manager class
*
*  @remarks
*    By using this memory manager together with the overwritten variations of global 'new' and
*    'delete' operators we avoid some nasty memory problems when using for instance multiple
*    dynamic libraries. ALL memory allocation/deallocation happens inside the PLGeneral module and
*    goes 'through' this memory manager, so we can also create statistics, perform security checks
*    and so on.
*    When using the PixelLight way dealing with for instance application entry points (PLMain) or
*    modules (pl_module) by including 'PLCore/ModuleMain.h' or 'PLGeneral/Main.h' this
*    memory manager is 'activated' automatically. If not (why didn't you use this comfortable way? :)
*    you need to include 'PLGeneral/Core/MemoryManager.inl' once per project.
*    There are multiple allocation/deallocation types supported - also some legacy types that are only
*    supported for optimal compatibility.
*
*  @note
*    - The __FUNCTION__ information is not used, because some systems don't support it and we may
*      get some conflicts with the overloaded new-operators of 'Microsoft's memory tracker'
*    - There are some simple wrapper functions you can use to avoid for instance nasty
*      standard header includes when they are undesired
*    - We intentionally do NOT offer memory makros (like an overwritten 'malloc') because experience
*      shows that they are making more troubles than adding advantages!
*    - Try to avoid the allocation/deallocation legacy types (Malloc, Calloc, Realloc, Free) to avoid
*      possible memory problems!
*    - Do NOT mix allocation/deallocation types like using 'delete []' to deallocate memory allocated
*      'with (none array) 'new'!
*    - To get information about for instance the current free physical memory have a look at the 'System'-class
*/
class MemoryManager {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Allocation/deallocation types
		*/
		enum EType {
			Unknown,		/**< ? */
			New,			/**< new <type name> */
			NewArray,		/**< new [<number of elements>] <type name> */
			Delete,			/**< delete <pointer> */
			DeleteArray,	/**< delete [] <pointer> */
			// The following legacy types are only supported for optimal compatibility, try to avoid them!
			Malloc,			/**< malloc(<bytes to allocate>), legacy type */
			Calloc,			/**< calloc(<number of elements>, <bytes per element>), legacy type */
			Realloc,		/**< realloc(<pointer to previously memory>, <new size in bytes>), legacy type */
			Free			/**< free(<pointer>), legacy type */
		};


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Copies memory
		*
		*  @param[in] pDestination
		*    Destination buffer (MUST be valid!)
		*  @param[in] pSource
		*    Source buffer (MUST be valid!)
		*  @param[in] nNumOfBytes
		*    Number of bytes to copy
		*
		*  @note
		*    - 'memcpy'-wrapper
		*/
		PLGENERAL_API static void Copy(void *pDestination, const void *pSource, uint32 nNumOfBytes);

		/**
		*  @brief
		*    Sets memory to a specified character
		*
		*  @param[in] pDestination
		*    Destination buffer (MUST be valid!)
		*  @param[in] nCharacter
		*    Character to set
		*  @param[in] nNumOfBytes
		*    Number of bytes to set
		*
		*  @note
		*    - 'memset'-wrapper
		*/
		PLGENERAL_API static void Set(void *pDestination, int nCharacter, uint32 nNumOfBytes);

		/**
		*  @brief
		*    Compares memory
		*
		*  @param[in] pFirstBuffer
		*    First buffer (MUST be valid!)
		*  @param[in] pSecondBuffer
		*    Second buffer (MUST be valid!)
		*  @param[in] nNumOfBytes
		*    Number of bytes to compare
		*
		*  @return
		*    < 0 = First buffer is less than second buffer
		*      0 = First buffer identical to second buffer
		*    > 0 = First buffer is greater than second buffer
		*
		*  @note
		*    - 'memcmp'-wrapper
		*/
		PLGENERAL_API static int Compare(const void *pFirstBuffer, const void *pSecondBuffer, uint32 nNumOfBytes);

		/**
		*  @brief
		*    Reallocates memory
		*
		*  @param[in] pAddress
		*    Previous memory, can be NULL (if not NULL, it MUST be valid!)
		*  @param[in] nNumOfBytes
		*    Number of bytes to allocate
		*  @param[in] nType
		*    Allocator type
		*  @param[in] pszSourceFile
		*    Source file, can be NULL
		*  @param[in] nSourceLine
		*    Source line
		*
		*  @return
		*    The new allocated memory, NULL on error
		*/
		PLGENERAL_API static void *Reallocator(void *pAddress, size_t nNumOfBytes, EType nType = NewArray, const char *pszSourceFile = NULL, int nSourceLine = -1);

		/**
		*  @brief
		*    Allocates new memory
		*
		*  @param[in] nType
		*    Allocator type
		*  @param[in] nNumOfBytes
		*    Number of bytes to allocate
		*  @param[in] pszSourceFile
		*    Source file, can be NULL
		*  @param[in] nSourceLine
		*    Source line
		*
		*  @return
		*    The new allocated memory, NULL on error
		*
		*  @note
		*    - Normally there's no reason using this function directly, use the 'new' keyword instead
		*/
		PLGENERAL_API static void *Allocator(EType nType, size_t nNumOfBytes, const char *pszSourceFile = NULL, int nSourceLine = -1);

		/**
		*  @brief
		*    Frees memory
		*
		*  @param[in] nType
		*    Allocator type
		*  @param[in] pAddress
		*    Memory to free (MUST be valid!)
		*  @param[in] pszSourceFile
		*    Source file, can be NULL
		*  @param[in] nSourceLine
		*    Source line
		*
		*  @note
		*    - Normally there's no reason using this function directly, use the 'delete' keyword instead
		*/
		PLGENERAL_API static void Deallocator(EType nType, void *pAddress, const char *pszSourceFile = NULL, int nSourceLine = -1);


};



//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Variations of global 'new' and 'delete' operators     ]
//[-------------------------------------------------------]
void *operator new(size_t nNumOfBytes);
void *operator new[](size_t nNumOfBytes);
void  operator delete(void *pAddress);
void  operator delete[](void *pAddress);
// This two special new-operators are also used by 'Microsoft's memory tracker', so there's no undesired interfering
void *operator new(size_t nNumOfBytes, const char *pszSourceFile, int nSourceLine);
void *operator new[](size_t nNumOfBytes, const char *pszSourceFile, int nSourceLine);
void  operator delete(void *pAddress, const char *pszSourceFile, int nSourceLine);
void  operator delete[](void *pAddress, const char *pszSourceFile, int nSourceLine);


#endif // __PLGENERAL_MEMORYMANAGER_H__
