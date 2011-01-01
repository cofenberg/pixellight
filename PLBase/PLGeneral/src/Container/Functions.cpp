/*********************************************************\
 *  File: Functions.cpp                                  *
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <string.h>
#include "PLGeneral/String/String.h"
#include "PLGeneral/Container/Functions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public static HashFunction functions                  ]
//[-------------------------------------------------------]
uint32 HashFunction::Hash(const int32 &nKey)
{
	return (uint32)nKey;
}

uint32 HashFunction::Hash(const uint32 &nKey)
{
	return nKey;
}

uint32 HashFunction::Hash(const int64 &nKey)
{
	return (uint32)nKey;
}

uint32 HashFunction::Hash(const uint64 &nKey)
{
	return (uint32)nKey;
}

uint32 HashFunction::Hash(const char *pszKey)
{
	// Check the given pointer for NULL
	if (pszKey) {
		uint32 h = 0;

		while (*pszKey) {
			h = (h << 4) + *pszKey++;
			uint32 g = h & 0xF0000000;
			if (g)
				h ^= g >> 24;
			h &= ~g;
		}

		return h;
	} else {
		// Error!
		return 0;
	}
}

uint32 HashFunction::Hash(const String &sKey)
{
	// Hash depending on the internal string format
	switch (sKey.GetFormat()) {
		case String::ASCII:
		{
			const char *pszKey = sKey.GetASCII();
			uint32 h = 0;

			while (*pszKey) {
				h = (h << 4) + *pszKey++;
				uint32 g = h & 0xF0000000;
				if (g)
					h ^= g >> 24;
				h &= ~g;
			}

			return h;
		}

		case String::Unicode:
		{
			const wchar_t *pszKey = sKey.GetUnicode();
			uint32 h = 0;

			while (*pszKey) {
				h = (h << 4) + *pszKey++;
				uint32 g = h & 0xF0000000;
				if (g)
					h ^= g >> 24;
				h &= ~g;
			}

			return h;
		}

		default:
			return 0; // Error!
	}
}


//[-------------------------------------------------------]
//[ Public static CompareFunction functions               ]
//[-------------------------------------------------------]
// int32
bool CompareFunction::AreEqual(const int32 &nKey1, const int32 &nKey2)
{
	return (nKey1 == nKey2);
}

bool CompareFunction::IsGreater(const int32 &nKey1, const int32 &nKey2)
{
	return (nKey1 > nKey2);
}

// uint32
bool CompareFunction::AreEqual(const uint32 &nKey1, const uint32 &nKey2)
{
	return (nKey1 == nKey2);
}

bool CompareFunction::IsGreater(const uint32 &nKey1, const uint32 &nKey2)
{
	return (nKey1 > nKey2);
}

// int64
bool CompareFunction::AreEqual(const int64 &nKey1, const int64 &nKey2)
{
	return (nKey1 == nKey2);
}

bool CompareFunction::IsGreater(const int64 &nKey1, const int64 &nKey2)
{
	return (nKey1 > nKey2);
}

// uint64
bool CompareFunction::AreEqual(const uint64 &nKey1, const uint64 &nKey2)
{
	return (nKey1 == nKey2);
}

bool CompareFunction::IsGreater(const uint64 &nKey1, const uint64 &nKey2)
{
	return (nKey1 > nKey2);
}

// float
bool CompareFunction::AreEqual(const float &fKey1, const float &fKey2)
{
	return (fKey1 == fKey2);
}

bool CompareFunction::IsGreater(const float &fKey1, const float &fKey2)
{
	return (fKey1 > fKey2);
}

// const char *
bool CompareFunction::AreEqual(const char *pszKey1, const char *pszKey2)
{
	return (pszKey1 && pszKey2 && !strcmp(pszKey1, pszKey2));
}

bool CompareFunction::IsGreater(const char *pszKey1, const char *pszKey2)
{
	return (pszKey1 && pszKey2 && strcmp(pszKey1, pszKey2) > 0);
}

// String
bool CompareFunction::AreEqual(const String &sKey1, const String &sKey2)
{
	return (sKey1 == sKey2);
}

bool CompareFunction::IsGreater(const String &sKey1, const String &sKey2)
{
	return (sKey1 > sKey2);
}


//[-------------------------------------------------------]
//[ Public static GrowFunction functions                  ]
//[-------------------------------------------------------]
uint32 GrowFunction::GetNewSize(uint32 nCurrentSize, uint32 nFreeSlots)
{
	uint32 nNewSize = nCurrentSize;
	while (nFreeSlots <= (nNewSize/10)) {
		// Get a prime number greater than the current size - to keep things simple and
		// fast we will do this by hand for some prime numbers :)
		if (nNewSize < 1297) {
			if (nNewSize < 199) {
				if (nNewSize < 109) {
					nNewSize = (nNewSize < 41) ? 41 : 109;
				} else {
					nNewSize = 199;
				}
			} else {
				if (nNewSize < 797) {
					nNewSize = (nNewSize < 397) ? 397 : 797;
				} else {
					nNewSize = 1297;
				}
			}
		} else {
			if (nNewSize < 3467) {
				if (nNewSize < 2467) {
					nNewSize = (nNewSize < 1699) ? 1699 : 2467;
				} else {
					nNewSize = 3467;
				}
			} else {
				if (nNewSize < 7559) {
					nNewSize = (nNewSize < 5231) ? 5231 : 7559;
				} else {
					nNewSize = (nNewSize < 9923) ? 9923 : nNewSize*2; // Fallback
				}
			}
		}

		// Because the array grows, more slots will be available now
		nFreeSlots = nFreeSlots + (nNewSize-nCurrentSize);
	}
	return nNewSize;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
}
