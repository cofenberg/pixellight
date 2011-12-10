/*********************************************************\
 *  File: MemoryManager.inl                              *
 *      Memory manager inline implementation
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
//[ Debugging options for Microsoft Visual Studio         ]
//[-------------------------------------------------------]
// <<nostepinto>> PLCore::MemoryManager::.*
// <<nostepinto>> operator delete.*
// <<nostepinto>> operator new.*


// For performance reasons we include so called "standard headers" in here even if they are not standardized across all platforms.
// Usually the used headers don't introduce definition conflicts across the platforms, so, this should be fine... but it's still
// highly recommended to use this "MemoryManager" helper class in case there are issues on a new platform. Changing this one header
// is easier than changing all source codes of all projects.


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <stdlib.h>	// For "realloc()", "malloc()" and "free()"
#include <string.h>	// For "memcpy()", "memset()" and "memcmp()"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copies memory
*/
inline void MemoryManager::Copy(void *pDestination, const void *pSource, uint32 nNumOfBytes)
{
	memcpy(pDestination, pSource, nNumOfBytes);
}

/**
*  @brief
*    Sets memory to a specified character
*/
inline void MemoryManager::Set(void *pDestination, int nCharacter, uint32 nNumOfBytes)
{
	memset(pDestination, nCharacter, nNumOfBytes);
}

/**
*  @brief
*    Compares memory
*/
inline int MemoryManager::Compare(const void *pFirstBuffer, const void *pSecondBuffer, uint32 nNumOfBytes)
{
	return memcmp(pFirstBuffer, pSecondBuffer, nNumOfBytes);
}

/**
*  @brief
*    Reallocates memory
*/
inline void *MemoryManager::Reallocator(void *pAddress, size_t nNumOfBytes, EType nType, const char *pszSourceFile, int nSourceLine)
{
	return realloc(pAddress, nNumOfBytes);
}

/**
*  @brief
*    Allocates new memory
*/
inline void *MemoryManager::Allocator(EType nType, size_t nNumOfBytes, const char *pszSourceFile, int nSourceLine)
{
	return malloc(nNumOfBytes);
}

/**
*  @brief
*    Frees memory
*/
inline void MemoryManager::Deallocator(EType nType, void *pAddress, const char *pszSourceFile, int nSourceLine)
{
	free(pAddress);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
