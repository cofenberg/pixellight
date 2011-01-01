/*********************************************************\
 *  File: MemoryManager.cpp                              *
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
// <<nostepinto>> PLGeneral::MemoryManager::.*
// <<nostepinto>> operator delete.*
// <<nostepinto>> operator new.*


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <malloc.h>
#include <memory.h>
#include "PLGeneral/Core/MemoryManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copies memory
*/
void MemoryManager::Copy(void *pDestination, const void *pSource, uint32 nNumOfBytes)
{
	memcpy(pDestination, pSource, nNumOfBytes);
}

/**
*  @brief
*    Sets memory to a specified character
*/
void MemoryManager::Set(void *pDestination, int nCharacter, uint32 nNumOfBytes)
{
	memset(pDestination, nCharacter, nNumOfBytes);
}

/**
*  @brief
*    Compares memory
*/
int MemoryManager::Compare(const void *pFirstBuffer, const void *pSecondBuffer, uint32 nNumOfBytes)
{
	return memcmp(pFirstBuffer, pSecondBuffer, nNumOfBytes);
}

/**
*  @brief
*    Reallocates memory
*/
void *MemoryManager::Reallocator(void *pAddress, size_t nNumOfBytes, EType nType, const char *pszSourceFile, int nSourceLine)
{
	return realloc(pAddress, nNumOfBytes);
}

/**
*  @brief
*    Allocates new memory
*/
void *MemoryManager::Allocator(EType nType, size_t nNumOfBytes, const char *pszSourceFile, int nSourceLine)
{
	return malloc(nNumOfBytes);
}

/**
*  @brief
*    Frees memory
*/
void MemoryManager::Deallocator(EType nType, void *pAddress, const char *pszSourceFile, int nSourceLine)
{
	free(pAddress);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
