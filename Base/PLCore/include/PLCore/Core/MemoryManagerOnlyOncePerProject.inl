/*********************************************************\
 *  File: MemoryManagerOnlyOncePerProject.inl            *
 *      Memory manager inline implementation. This header can ONLY be includes once per project!
 *      (normally automatically included within 'PLCore/ModuleMain.h')
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Core/MemoryManager.h"


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
inline void *operator new(size_t nNumOfBytes)
{
	// ANSI says: allocation requests of 0 bytes will still return a valid value
	if (!nNumOfBytes)
		nNumOfBytes = 1;

	// ANSI says: loop continuously because the error handler could possibly free up some memory
	for (;;) {
		// Try the allocation
		void *pAddress = PLCore::MemoryManager::Allocator(PLCore::MemoryManager::New, nNumOfBytes, "?", 0);
		if (pAddress)
			return pAddress;
	}
}

inline void *operator new[](size_t nNumOfBytes)
{
	// The ANSI standard says that allocation requests of 0 bytes will still return a valid value
	if (!nNumOfBytes)
		nNumOfBytes = 1;

	// ANSI says: loop continuously because the error handler could possibly free up some memory
	for (;;) {
		// Try the allocation
		void *pAddress = PLCore::MemoryManager::Allocator(PLCore::MemoryManager::NewArray, nNumOfBytes, "?", 0);
		if (pAddress)
			return pAddress;
	}
}

inline void operator delete(void *pAddress)
{
	// ANSI says: delete & delete[] allow null pointers (they do nothing)
	if (pAddress)
		PLCore::MemoryManager::Deallocator(PLCore::MemoryManager::Delete, pAddress, "?", 0);
}

inline void operator delete[](void *pAddress)
{
	// ANSI says: delete & delete[] allow null pointers (they do nothing)
	if (pAddress)
		PLCore::MemoryManager::Deallocator(PLCore::MemoryManager::DeleteArray, pAddress, "?", 0);
}

inline void *operator new(size_t nNumOfBytes, const char *pszSourceFile, int nSourceLine)
{
	// ANSI says: allocation requests of 0 bytes will still return a valid value
	if (!nNumOfBytes)
		nNumOfBytes = 1;

	// ANSI says: loop continuously because the error handler could possibly free up some memory
	for (;;) {
		// Try the allocation
		void *pAddress = PLCore::MemoryManager::Allocator(PLCore::MemoryManager::New, nNumOfBytes, pszSourceFile, nSourceLine);
		if (pAddress)
			return pAddress;
	}
}

inline void *operator new[](size_t nNumOfBytes, const char *pszSourceFile, int nSourceLine)
{
	// ANSI says: allocation requests of 0 bytes will still return a valid value
	if (!nNumOfBytes)
		nNumOfBytes = 1;

	// ANSI says: loop continuously because the error handler could possibly free up some memory
	for (;;) {
		// Try the allocation
		void *pAddress = PLCore::MemoryManager::Allocator(PLCore::MemoryManager::New, nNumOfBytes, pszSourceFile, nSourceLine);
		if (pAddress)
			return pAddress;
	}
}

inline void operator delete(void *pAddress, const char *pszSourceFile, int nSourceLine)
{
	// ANSI says: delete & delete[] allow null pointers (they do nothing)
	if (pAddress)
		PLCore::MemoryManager::Deallocator(PLCore::MemoryManager::Delete, pAddress, pszSourceFile, nSourceLine);
}

inline void operator delete[](void *pAddress, const char *pszSourceFile, int nSourceLine)
{
	// ANSI says: delete & delete[] allow null pointers (they do nothing)
	if (pAddress)
		PLCore::MemoryManager::Deallocator(PLCore::MemoryManager::Delete, pAddress, pszSourceFile, nSourceLine);
}
