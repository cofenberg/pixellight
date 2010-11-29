/*********************************************************\
 *  File: StringBufferManager.cpp                        *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Core/MemoryManager.h"
#include "PLGeneral/String/StringBufferASCII.h"
#include "PLGeneral/String/StringBufferUnicode.h"
#include "PLGeneral/String/StringBufferManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
StringBufferManager::StringBufferManager() :
	m_pStringBufferASCII(NULL),
	m_pStringBufferUnicode(NULL)
{
}

/**
*  @brief
*    Destructor
*/
StringBufferManager::~StringBufferManager()
{
	// Destroy all buffered ASCII string buffers
	if (m_pStringBufferASCII) {
		for (uint32 i=0; i<MaxStringReuseLength; i++) {
			for (uint32 j=0; j<MaxStringsPerReuseLength; j++) {
				StringBufferASCII *pStringBufferASCII = m_pStringBufferASCII[i*MaxStringsPerReuseLength + j];
				if (pStringBufferASCII)
					delete pStringBufferASCII;
			}
		}
		delete [] m_pStringBufferASCII;
		m_pStringBufferASCII = NULL;
	}

	// Destroy all buffered unicode string buffers
	if (m_pStringBufferUnicode) {
		for (uint32 i=0; i<MaxStringReuseLength; i++) {
			for (uint32 j=0; j<MaxStringsPerReuseLength; j++) {
				StringBufferUnicode *pStringBufferUnicode = m_pStringBufferUnicode[i*MaxStringsPerReuseLength + j];
				if (pStringBufferUnicode)
					delete pStringBufferUnicode;
			}
		}
		delete [] m_pStringBufferUnicode;
		m_pStringBufferUnicode = NULL;
	}
}

/**
*  @brief
*    Returns an instance of a ASCII string buffer
*/
StringBufferASCII *StringBufferManager::GetStringBufferASCII(uint32 nLength)
{
	StringBufferASCII *pStringBufferASCII = NULL;

	// Calculate the maximum available length of the string (excluding the terminating zero)
	const uint32 nMaxLength = nLength + NumOfReservedCharacters;

	// Can be reuse a previous string buffer?
	if (nMaxLength < MaxStringReuseLength && m_pStringBufferASCII) {
		// Try to find a used slot
		for (int j=MaxStringsPerReuseLength-1; j>=0; j--) {
			// Is this slot used?
			const uint32 nIndex = nMaxLength*MaxStringsPerReuseLength + j;
			if (m_pStringBufferASCII[nIndex]) {
				// Jap, revive this string buffer!
				pStringBufferASCII = m_pStringBufferASCII[nIndex];
				m_pStringBufferASCII[nIndex] = NULL;

				// Get us out of the loop
				j = -1;
			}
		}
	}

	// Do we need to create a new string buffer?
	if (!pStringBufferASCII) {
		// Create the string
		char *pszString = new char[nMaxLength + 1];
		pszString[0] = '\0';

		// Create the ASCII string buffer instance
		pStringBufferASCII = new StringBufferASCII(pszString, 0, nMaxLength);
	}

	// Done
	return pStringBufferASCII;
}

/**
*  @brief
*    Returns an instance of a unicode string buffer
*/
StringBufferUnicode *StringBufferManager::GetStringBufferUnicode(uint32 nLength)
{
	StringBufferUnicode *pStringBufferUnicode = NULL;

	// Calculate the maximum available length of the string (excluding the terminating zero)
	const uint32 nMaxLength = nLength + NumOfReservedCharacters;

	// Can be reuse a previous string buffer?
	if (nMaxLength < MaxStringReuseLength && m_pStringBufferUnicode) {
		// Try to find a used slot
		for (int j=MaxStringsPerReuseLength-1; j>=0; j--) {
			// Is this slot used?
			const uint32 nIndex = nMaxLength*MaxStringsPerReuseLength + j;
			if (m_pStringBufferUnicode[nIndex]) {
				// Jap, revive this string buffer!
				pStringBufferUnicode = m_pStringBufferUnicode[nIndex];
				m_pStringBufferUnicode[nIndex] = NULL;

				// Get us out of the loop
				j = -1;
			}
		}
	}

	// Do we need to create a new string buffer?
	if (!pStringBufferUnicode) {
		// Create the string
		wchar_t *pszString = new wchar_t[nMaxLength + 1];
		pszString[0] = L'\0';

		// Create the unicode string buffer instance
		pStringBufferUnicode = new StringBufferUnicode(pszString, 0, nMaxLength);
	}

	// Done
	return pStringBufferUnicode;
}

/**
*  @brief
*    Releases an instance of a string buffer
*/
void StringBufferManager::ReleaseStringBuffer(StringBuffer &cStringBuffer)
{
	// Is the string buffer going to be destroyed if we release one more reference?
	if (cStringBuffer.GetRefCount() < 2) {
		// Ok, this is the reason why we can't use the "RefCount"-template in here - the string buffer manager may keep the string buffer
		// alive for later reuse, but the "reused" string buffer really needs a "fresh" reference counter set to 0
		bool bBackuped = false;

		// Check the internal string format
		const uint32 nStringLength = cStringBuffer.m_nMaxLength;
		switch (cStringBuffer.GetFormat()) {
			case String::ASCII:
				// We don't want to keep alive long strings for later reuse...
				if (nStringLength < MaxStringReuseLength) {
					// Initialize?
					if (!m_pStringBufferASCII) {
						const uint32 nNumOfElements = MaxStringReuseLength*MaxStringsPerReuseLength;
						m_pStringBufferASCII = new StringBufferASCII*[nNumOfElements];
						MemoryManager::Set(m_pStringBufferASCII, 0, sizeof(StringBufferASCII*)*nNumOfElements);
					}
					if (m_pStringBufferASCII) {
						// Try to find a unused slot
						for (uint32 j=0; j<MaxStringsPerReuseLength; j++) {
							// Is this slot used?
							const uint32 nIndex = nStringLength*MaxStringsPerReuseLength + j;
							if (!m_pStringBufferASCII[nIndex]) {
								// Nope, our string buffer found a new home!
								StringBufferASCII *pStringBufferASCII = (StringBufferASCII*)&cStringBuffer;
								m_pStringBufferASCII[nIndex] = pStringBufferASCII;
								bBackuped = true;

								// Reset the string buffer
								pStringBufferASCII->m_nRefCount = 0;
								pStringBufferASCII->SetNewStringLength(0);
								pStringBufferASCII->m_pszString[0] = '\0';

								// Get us out of the loop
								j = MaxStringsPerReuseLength;
							}
						}
					}
				}
				break;

			case String::Unicode:
				// We don't want to keep alive long strings for later reuse...
				if (nStringLength < MaxStringReuseLength) {
					// Initialize?
					if (!m_pStringBufferUnicode) {
						const uint32 nNumOfElements = MaxStringReuseLength*MaxStringsPerReuseLength;
						m_pStringBufferUnicode = new StringBufferUnicode*[nNumOfElements];
						MemoryManager::Set(m_pStringBufferUnicode, 0, sizeof(StringBufferUnicode*)*nNumOfElements);
					}
					if (m_pStringBufferUnicode) {
						// Try to find a unused slot
						for (uint32 j=0; j<MaxStringsPerReuseLength; j++) {
							// Is this slot used?
							const uint32 nIndex = nStringLength*MaxStringsPerReuseLength + j;
							if (!m_pStringBufferUnicode[nIndex]) {
								// Nope, our string buffer found a new home!
								StringBufferUnicode *pStringBufferUnicode = (StringBufferUnicode*)&cStringBuffer;
								m_pStringBufferUnicode[nIndex] = pStringBufferUnicode;
								bBackuped = true;

								// Reset the string buffer
								pStringBufferUnicode->m_nRefCount = 0;
								pStringBufferUnicode->SetNewStringLength(0);
								pStringBufferUnicode->m_pszString[0] = '\0';

								// Get us out of the loop
								j = MaxStringsPerReuseLength;
							}
						}
					}
				}
				break;

			case String::UTF8:
				// [TODO] Add reuse
				break;
		}

		// String buffer backuped?
		if (!bBackuped)
			cStringBuffer.Release();	// Sorry, no more backup space left!
	} else {
		// Just release the reference - after this, the string buffer will still be there because it's still referenced
		cStringBuffer.Release();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
