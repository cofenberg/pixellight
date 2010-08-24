/*********************************************************\
 *  File: StringBufferUTF8.cpp                           *
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
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#ifdef LINUX
	#include <wchar.h>
	#include "PLGeneral/PLGeneralLinuxWrapper.h"
#endif
#include "PLGeneral/Core/MemoryManager.h"
#include "PLGeneral/String/UTF8Tools.h"
#include "PLGeneral/String/StringBufferASCII.h"
#include "PLGeneral/String/StringBufferUnicode.h"
#include "PLGeneral/String/StringBufferUTF8.h"


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
StringBufferUTF8::StringBufferUTF8(char szString[], uint32 nLength) : StringBuffer(nLength, String::UTF8),
	m_pszString(NULL),
	m_nNumOfBytes(0),
	m_pASCII(NULL),
	m_pUnicode(NULL)
{
	// Get the number of bytes the UTF8 string requires
	m_nNumOfBytes = UTF8Tools::Unescape(NULL, 0, szString);

	// Get the UTF8 string
	m_pszString = new utf8[m_nNumOfBytes + 1];
	UTF8Tools::Unescape(m_pszString, m_nNumOfBytes + 1, szString);
}

/**
*  @brief
*    Constructor
*/
StringBufferUTF8::StringBufferUTF8(const wchar_t szString[], uint32 nLength) : StringBuffer(nLength, String::UTF8),
	m_pszString(NULL),
	m_nNumOfBytes(0),
	m_pASCII(NULL),
	m_pUnicode(NULL)
{
	// Get the number of bytes the UTF8 string requires
	m_nNumOfBytes = UTF8Tools::FromWideCharacterString(NULL, 0, szString, 0);

	// Get the UTF8 string
	m_pszString = new utf8[m_nNumOfBytes + 1];
	UTF8Tools::FromWideCharacterString(m_pszString, m_nNumOfBytes + 1, szString, 0);
}

/**
*  @brief
*    Constructor
*/
StringBufferUTF8::StringBufferUTF8(utf8 szString[], uint32 nLength, uint32 nNumOfBytes) : StringBuffer(nLength, String::UTF8),
	m_pszString(szString),
	m_nNumOfBytes(nNumOfBytes),
	m_pASCII(NULL),
	m_pUnicode(NULL)
{
}

/**
*  @brief
*    Destructor
*/
StringBufferUTF8::~StringBufferUTF8()
{
	if (m_pASCII) m_pASCII->Release();
	if (m_pUnicode) m_pUnicode->Release();
	delete [] m_pszString; // (there MUST by such a string :)
}

/**
*  @brief
*    Sets the string
*/
bool StringBufferUTF8::SetString(utf8 szString[], uint32 nLength, uint32 nNumOfBytes)
{
	// The ASCII version is now dirty
	if (m_pASCII) {
		m_pASCII->Release();
		m_pASCII = NULL;
	}

	// The Unicode version is now dirty
	if (m_pUnicode) {
		m_pUnicode->Release();
		m_pUnicode = NULL;
	}

	// Kill the old string (there MUST by such a string :)
	delete [] m_pszString;

	// Set new string
	m_pszString   = szString;
	m_nLength     = nLength;
	m_nNumOfBytes = nNumOfBytes;

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Public virtual StringBuffer functions                 ]
//[-------------------------------------------------------]
String::EFormat StringBufferUTF8::GetFormat() const
{
	return String::UTF8;
}

StringBufferASCII *StringBufferUTF8::GetASCII()
{
	// Is there already a current ASCII version?
	if (!m_pASCII) {
		// Nope, let's create one
		m_pASCII = new StringBufferASCII(m_pszString, m_nLength, m_nNumOfBytes);
		m_pASCII->AddReference();
	}

	// Return it
	return m_pASCII;
}

StringBufferUnicode *StringBufferUTF8::GetUnicode()
{
	// Is there already a current Unicode version?
	if (!m_pUnicode) {
		// Nope, let's create one
		m_pUnicode = new StringBufferUnicode(m_pszString, m_nLength, m_nNumOfBytes);
		m_pUnicode->AddReference();
	}

	// Return it
	return m_pUnicode;
}

StringBufferUTF8 *StringBufferUTF8::GetUTF8()
{
	return this;
}

uint32 StringBufferUTF8::GetNumOfBytes() const
{
	return m_nNumOfBytes;
}

StringBuffer *StringBufferUTF8::Clone() const
{
	utf8 *pszClone = new utf8[m_nNumOfBytes];
	MemoryManager::Copy(pszClone, m_pszString, m_nNumOfBytes);
	return new StringBufferUTF8(pszClone, m_nLength, m_nNumOfBytes);
}

StringBuffer *StringBufferUTF8::Duplicate()
{
	// Do we need to clone this string buffer?
	if (GetRefCount() > 1) return Clone();
	else {
		// The ASCII version is now dirty
		if (m_pASCII) {
			m_pASCII->Release();
			m_pASCII = NULL;
		}

		// The Unicode version is now dirty
		if (m_pUnicode) {
			m_pUnicode->Release();
			m_pUnicode = NULL;
		}

		// Just return this string buffer
		return (StringBuffer*)this;
	}
}

bool StringBufferUTF8::IsLessThan(const char szString[], uint32 nLength) const
{
	return (UTF8Tools::Compare(m_pszString, (utf8*)szString, nLength) < 0);
}

bool StringBufferUTF8::IsLessThan(const wchar_t szString[], uint32 nLength) const
{
	if (m_nLength < nLength ) return true;
	if (m_nLength > nLength ) return false;
	
	// We need to convert this UTF8 string into an Unicode one :(
	wchar_t *pUnicode = new wchar_t[m_nLength + 1];
	UTF8Tools::ToWideCharacterString(pUnicode, m_nLength + 1, m_pszString, m_nNumOfBytes);
	bool bResult = wcscmp(pUnicode, szString) < 0;
	delete [] pUnicode;
	return bResult;
}

bool StringBufferUTF8::IsGreaterThan(const char szString[], uint32 nLength) const
{
	
	return (UTF8Tools::Compare(m_pszString, (const utf8*)szString, nLength) > 0);
}

bool StringBufferUTF8::IsGreaterThan(const wchar_t szString[], uint32 nLength) const
{
	if (m_nLength < nLength ) return false;
	if (m_nLength > nLength ) return true;
	
	// We need to convert this UTF8 string into an Unicode one :(
	wchar_t *pUnicode = new wchar_t[m_nLength + 1];
	UTF8Tools::ToWideCharacterString(pUnicode, m_nLength + 1, m_pszString, m_nNumOfBytes);
	bool bResult = wcscmp(pUnicode, szString) > 0;
	delete [] pUnicode;
	return bResult;
}

bool StringBufferUTF8::Compare(const char szString[], uint32 nLength, uint32 nPos, uint32 nCount) const
{
	if (!nPos && !nCount) {
		// Compare hole strings
		if (nLength != m_nLength) return false; // THAT was pretty easy, the length of the strings is not equal :)
		else					  return !UTF8Tools::Compare(m_pszString, (const utf8*)szString);

	} else {
		// Check start position
		if (nPos >= m_nLength) return false; // Strings are not equal

		// Compare strings (count can be > maximum string length)
		if (nCount)	return !UTF8Tools::Compare(&m_pszString[nPos], (const utf8*)szString, nCount);
		else		return !UTF8Tools::Compare(&m_pszString[nPos], (const utf8*)szString);
	}
	
}

bool StringBufferUTF8::Compare(const wchar_t szString[], uint32 nLength, uint32 nPos, uint32 nCount) const
{
	if (!nPos && !nCount) {
		// Compare hole strings
		if (nLength != m_nLength) return false; // THAT was pretty easy, the length of the strings is not equal :)
		else {
			// We need to convert this UTF8 string into an Unicode one :(
			wchar_t *pUnicode = new wchar_t[m_nLength + 1];
			UTF8Tools::ToWideCharacterString(pUnicode, m_nLength + 1, m_pszString, m_nNumOfBytes);
			bool bResult = !wcscmp(pUnicode, szString);
			delete [] pUnicode;
			return bResult;
		}

	} else {
		// Check start position
		if (nPos >= m_nLength) return false; // Strings are not equal

		// We need to convert this UTF8 string into an Unicode one :(
		wchar_t *pUnicode = new wchar_t[m_nLength + 1];
		UTF8Tools::ToWideCharacterString(pUnicode, m_nLength + 1, m_pszString, m_nNumOfBytes);

		// Compare strings (count can be > maximum string length)
		bool bResult;
		if (nCount)	bResult = !wcsncmp(&pUnicode[nPos], szString, nCount);
		else		bResult = !wcscmp (&pUnicode[nPos], szString);
		delete [] pUnicode;
		return bResult;
	}
}

bool StringBufferUTF8::CompareNoCase(const char szString[], uint32 nLength, uint32 nPos, uint32 nCount) const
{
	// [TODO]
	return false;
/*	if (!nPos && !nCount) {
		// Compare hole strings
		if (nLength != m_nLength) return false; // THAT was pretty easy, the length of the strings is not equal :)
		else					  return !stricmp(m_pszString, szString);

	} else {
		// Check start position
		if (nPos >= m_nLength) return false; // Strings are not equal

		// Compare strings (count can be > maximum string length)
		if (nCount)	return !strnicmp(&m_pszString[nPos], szString, nCount);
		else		return !stricmp (&m_pszString[nPos], szString);
	}
	*/
}

bool StringBufferUTF8::CompareNoCase(const wchar_t szString[], uint32 nLength, uint32 nPos, uint32 nCount) const
{
	if (!nPos && !nCount) {
		// Compare hole strings
		if (nLength != m_nLength) return false; // THAT was pretty easy, the length of the strings is not equal :)
		else {
			// We need to convert this UTF8 string into an Unicode one :(
			wchar_t *pUnicode = new wchar_t[m_nLength + 1];
			UTF8Tools::ToWideCharacterString(pUnicode, m_nLength + 1, m_pszString, m_nNumOfBytes);
			bool bResult = !_wcsicmp(pUnicode, szString);
			delete [] pUnicode;
			return bResult;
		}

	} else {
		// Check start position
		if (nPos >= m_nLength) return false; // Strings are not equal

		// We need to convert this UTF8 string into an Unicode one :(
		wchar_t *pUnicode = new wchar_t[m_nLength + 1];
		UTF8Tools::ToWideCharacterString(pUnicode, m_nLength + 1, m_pszString, m_nNumOfBytes);

		// Compare strings (count can be > maximum string length)
		bool bResult;
		if (nCount)	bResult = !_wcsnicmp(&pUnicode[nPos], szString, nCount);
		else		bResult = !_wcsicmp (&pUnicode[nPos], szString);
		delete [] pUnicode;
		return bResult;
	}
}

bool StringBufferUTF8::IsAlphabetic() const
{
/*	const char *pszString    = m_pszString;
	const char *pszStringEnd = pszString + m_nLength;
	for (; pszString<pszStringEnd; pszString++)
		if (!isalpha((unsigned char)*pszString)) return false; // The string is not alphabetic
*/
	// The string is alphabetic
	return true;
}

bool StringBufferUTF8::IsAlphaNumeric() const
{
/*	const char *pszString    = m_pszString;
	const char *pszStringEnd = pszString + m_nLength;
	for (; pszString<pszStringEnd; pszString++)
		if (!isalpha((unsigned char)*pszString) && !isdigit((unsigned char)*pszString)) return false; // The string is not alpha-numeric
*/
	// The string is alpha-numeric
	return true;
}

bool StringBufferUTF8::IsNumeric() const
{
/*	const char *pszString    = m_pszString;
	const char *pszStringEnd = pszString + m_nLength;
	for (; pszString<pszStringEnd; pszString++)
		if (!isdigit((unsigned char)*pszString)) return false; // The string is not numeric
*/
	// The string is numeric
	return true;
}

bool StringBufferUTF8::IsSubstring(const char szString[], uint32 nLength) const
{
	// [TODO]
	return false;
// return strstr(m_pszString, szString) != NULL;
}

bool StringBufferUTF8::IsSubstring(const wchar_t szString[], uint32 nLength) const
{
	// We need to convert this UTF8 string into an Unicode one :(
	wchar_t *pUnicode = new wchar_t[m_nLength + 1];
	UTF8Tools::ToWideCharacterString(pUnicode, m_nLength + 1, m_pszString, m_nNumOfBytes);
	bool bResult = wcsstr(pUnicode, szString) != NULL;
	delete [] pUnicode;
	return bResult;
}

int StringBufferUTF8::IndexOf(const char szString[], uint32 nPos, uint32 nLength) const
{
	// [TODO]
/*	const char *pszPos = strstr(&m_pszString[nPos], szString);
	return pszPos ? int(pszPos - m_pszString) : -1;
	*/
	return -1;
}

int StringBufferUTF8::IndexOf(const wchar_t szString[], uint32 nPos, uint32 nLength) const
{
	// We need to convert this UTF8 string into an Unicode one :(
	wchar_t *pUnicode = new wchar_t[m_nLength + 1];
	UTF8Tools::ToWideCharacterString(pUnicode, m_nLength + 1, m_pszString, m_nNumOfBytes);
	const wchar_t *pszPos = wcsstr(&pUnicode[nPos], szString);
	int nResult = pszPos ? int(pszPos - pUnicode) : -1;
	delete [] pUnicode;
	return nResult;
}

int StringBufferUTF8::LastIndexOf(const char szString[], int nPos, uint32 nLength) const
{
	// We need to convert the given ASCII string into an Unicode one :(
	wchar_t *pUnicodeGiven = new wchar_t[nLength + 1];
	mbstowcs(pUnicodeGiven, szString, nLength + 1);

	// We need to convert this UTF8 string into an Unicode one :(
	wchar_t *pUnicodeThis = new wchar_t[m_nLength + 1];
	UTF8Tools::ToWideCharacterString(pUnicodeThis, m_nLength + 1, m_pszString, m_nNumOfBytes);

	// Find substring
	const wchar_t *pszStringStart = pUnicodeThis;
	const wchar_t *pszStringT     = pszStringStart + nPos;
	for (; pszStringT>=pszStringStart; pszStringT--) {
		if (!wcsncmp(pszStringT, pUnicodeGiven, nLength)) {
			int nResult = int(pszStringT - pszStringStart);
			delete [] pUnicodeGiven;
			delete [] pUnicodeThis;
			return nResult; // We have found something
		}
	}
	delete [] pUnicodeGiven;
	delete [] pUnicodeThis;

	// No substring
	return -1;
}

int StringBufferUTF8::LastIndexOf(const wchar_t szString[], int nPos, uint32 nLength) const
{
	// [TODO]
	// We need to convert this UTF8 string into an Unicode one :(
	wchar_t *pUnicode = new wchar_t[m_nLength + 1];
	UTF8Tools::ToWideCharacterString(pUnicode, m_nLength + 1, m_pszString, m_nNumOfBytes);

	// Find substring
	const wchar_t *pszStringStart = pUnicode;
	const wchar_t *pszStringT     = pszStringStart + nPos;
	for (; pszStringT>=pszStringStart; pszStringT--) {
		if (!wcsncmp(pszStringT, szString, nLength)) {
			int nResult = int(pszStringT - pszStringStart);
			delete [] pUnicode;
			return nResult; // We have found something
		}
	}
	delete [] pUnicode;

	// No substring
	return -1;
}

StringBuffer *StringBufferUTF8::GetSubstring(uint32 nPos, uint32 nCount) const
{
	// Character index => byte offset
	const uint32 nByteOffset = UTF8Tools::CharacterIndexToByteOffset(m_pszString, nPos);

	// Get the source pointer
	const utf8 *pszSource = &m_pszString[nByteOffset];

	// Get the number of bytes a given string requires (excluding the terminating zero)
	const uint32 nNumOfBytes = UTF8Tools::GetNumOfStringBytes(pszSource, nCount);

	// Allocate memory (+1 for the terminating zero)
	utf8 *pszNewString = new utf8[nNumOfBytes + 1];

	// Copy the given UTF8 source string into the destination string
	UTF8Tools::Copy(pszNewString, pszSource, nCount);

	// Set terminating zero at the end
	pszNewString[nNumOfBytes] = '\0';

	// Create the new string buffer and return it
	return new StringBufferUTF8(pszNewString, nCount, nNumOfBytes);
}

StringBuffer *StringBufferUTF8::ToLower()
{
	// [TODO]
	return NULL;
/*	// Look for the first character that is NOT lower case
	const char *pszString    = m_pszString;
	const char *pszStringEnd = pszString + m_nLength;
	for (; pszString<pszStringEnd; pszString++) {
		// Is this already a lower character?
		if (!islower(*pszString)) {
			// Nope, now we have to clone the string buffer :(
			StringBufferUTF8 *pClone = (StringBufferUTF8*)Duplicate();

			// Start with an offset - we KNOW the characters before will not be changed!
			strlwr(pClone->m_pszString + (pszString - m_pszString));

			// Return the new, lower case string buffer
			return pClone;
		}
	}

	// If we are here, nothing was changed and we can just return this string buffer
	return this;
	*/
}

StringBuffer *StringBufferUTF8::ToUpper()
{
	// [TODO]
	return NULL;
	/*
	// Look for the first character that is NOT upper case
	const char *pszString    = m_pszString;
	const char *pszStringEnd = pszString + m_nLength;
	for (; pszString<pszStringEnd; pszString++) {
		// Is this already a upper character?
		if (!isupper(*pszString)) {
			// Nope, now we have to clone the string buffer :(
			StringBufferUTF8 *pClone = (StringBufferUTF8*)Duplicate();

			// Start with an offset - we KNOW the characters before will not be changed!
			_strupr(pClone->m_pszString + (pszString - m_pszString));

			// Return the new, upper case string buffer
			return pClone;
		}
	}

	// If we are here, nothing was changed and we can just return this string buffer
	return this;*/
}

StringBuffer *StringBufferUTF8::Delete(uint32 nPos, uint32 nCount)
{
	// [TODO]
	return NULL;
/*	// Characters are deleted by moving up the data following the region to delete
	uint32 nNewLength = m_nLength - nCount;
	char *pszNewString = new char[nNewLength + 1];
	if (nPos) strncpy(pszNewString, m_pszString, nPos);
	strncpy(&pszNewString[nPos], m_pszString + nPos + nCount, nNewLength - nPos);
	pszNewString[nNewLength] = '\0';

	// Return the new string buffer
	if (GetRefCount() > 1) return new StringBufferUTF8(pszNewString, nNewLength);
	else {
		// Just modify and return this string buffer
		SetString(pszNewString, nNewLength);
		return this;
	}*/
}

StringBuffer *StringBufferUTF8::Insert(const char szString[], uint32 nPos, uint32 nCount)
{
	// [TODO]
	return NULL;
/*	// Compose the new string
	uint32 nNewLength = m_nLength + nCount;
	char *pszNewString = new char[nNewLength + 1];
	if (nPos) strncpy(pszNewString, m_pszString, nPos);
	strncpy(&pszNewString[nPos], szString, nCount);
	strncpy(&pszNewString[nPos + nCount], &m_pszString[nPos], m_nLength - nPos);
	pszNewString[nNewLength] = '\0';

	// Return the new string buffer
	if (GetRefCount() > 1) return new StringBufferUTF8(pszNewString, nNewLength);
	else {
		// Just modify and return this string buffer
		SetString(pszNewString, nNewLength);
		return this;
	}
	*/
}

StringBuffer *StringBufferUTF8::Insert(const wchar_t szString[], uint32 nPos, uint32 nCount)
{
	// [TODO]
	return NULL;
/*	// Compose the new string (we need to convert this UTF8 string into an Unicode one)
	uint32 nNewLength = m_nLength + nCount;
	wchar_t *pszNewString = new wchar_t[nNewLength + 1];
	if (nPos) mbstowcs(pszNewString, m_pszString, nPos);
	wcsncpy(&pszNewString[nPos], szString, nCount);
	mbstowcs(&pszNewString[nPos + nCount], &m_pszString[nPos], m_nLength - nPos);
	pszNewString[nNewLength] = L'\0';

	// Return the new Unicode string buffer
	return new StringBufferUnicode(pszNewString, nNewLength);
	*/
}

StringBuffer *StringBufferUTF8::Replace(char nOld, char nNew, uint32 &nReplaced)
{
	// [TODO]
	return NULL;
/*	char *pszString    = m_pszString;
	char *pszStringEnd = m_pszString + m_nLength;

	// Search for the first character which should be replaced
	nReplaced = 0;
	for (; pszString<pszStringEnd; pszString++) {
		if (*pszString == nOld) {
			// Fork string buffer when the first character has been found
			StringBufferUTF8 *pClone = (StringBufferUTF8*)Duplicate();

			// Set pointers to new location
			pszString    = pClone->m_pszString + (pszString - m_pszString);
			pszStringEnd = pClone->m_pszString + m_nLength;

			// Replace characters
			for (; pszString<pszStringEnd; pszString++) {
				if (*pszString == nOld) {
					*pszString = nNew;
					nReplaced++;
				}
			}

			// Return the new string buffer
			return pClone;
		}
	}

	// If we are here, nothing was changed and we can just return this string buffer
	return this;
	*/
}

StringBuffer *StringBufferUTF8::Replace(wchar_t nOld, wchar_t nNew, uint32 &nReplaced)
{
	// [TODO]
	return NULL;
	/*
	char *pszString    = m_pszString;
	char *pszStringEnd = m_pszString + m_nLength;
	wchar_t nUnicode;

	// Search for the first character which should be replaced
	nReplaced = 0;
	for (; pszString<pszStringEnd; pszString++) {
		mbtowc(&nUnicode, pszString, 1);
		if (nUnicode == nOld) {
			// Create an Unicode string buffer when the first character has been found
			StringBufferUnicode *pClone = new StringBufferUnicode(m_pszString, m_nLength);

			// Set pointers to new location
			wchar_t *pszStringUnicode    = pClone->m_pszString + (pszString - m_pszString);
			wchar_t *pszStringUnicodeEnd = pClone->m_pszString + m_nLength;

			// Replace characters
			for (; pszStringUnicode<pszStringUnicodeEnd; pszStringUnicode++) {
				if (*pszStringUnicode == nOld) {
					*pszStringUnicode = nNew;
					nReplaced++;
				}
			}

			// Return the new string buffer
			return pClone;
		}
	}

	// If we are here, nothing was changed and we can just return this string buffer
	return this;
	*/
}

StringBuffer *StringBufferUTF8::Replace(const char szOld[], uint32 nOldLength, const char szNew[], uint32 nNewLength, uint32 &nReplaced)
{
	// [TODO]
	return NULL;
/*	// Check for only character replace
	if (nOldLength == 1 && nNewLength == 1)
		return Replace(szOld[0], szNew[0], nReplaced);

	// First, get the number of substrings to replace
	nReplaced = 0;
	const char *pszString = m_pszString;
	const char *pszEnd    = m_pszString + m_nLength;
	while (pszString<pszEnd) {
		if (!strncmp(pszString, szOld, nOldLength)) {
			nReplaced++;
			pszString += nOldLength;
		} else pszString++;
	}

	// Jipi, no substrings, no further work to do :)
	if (!nReplaced) return this; // Nothing was changed and we can just return this string buffer

	// Get and check the new length
	uint32 nFinalLength = m_nLength + (nNewLength - nOldLength)*nReplaced;
	if (!nFinalLength) return NULL; // The string is now empty!

	// Create the new string
	char *pszNewString  = new char[nFinalLength + 1];
	char *pszNewStringT = pszNewString;
	uint32 nSkipped = 0;
	pszString = m_pszString;
	for (uint32 i=0; i<nReplaced; i++) {
		// Find substring
		while (strncmp(pszString, szOld, nOldLength)) {
			pszString++;
			nSkipped++;
		}

		// Copy previous none substring characters
		if (nSkipped) {
			strncpy(pszNewStringT, pszString - nSkipped, nSkipped);
			pszNewStringT += nSkipped;
		}

		// Insert new substring
		strncpy(pszNewStringT, szNew, nNewLength);
		pszNewStringT += nNewLength;
		pszString += nOldLength;
		nSkipped = 0;
	}

	// Copy the rest of the old string to the new string
	if (*pszString != '\0') {
		uint32 i = uint32(pszNewString + nFinalLength - pszNewStringT);
		strncpy(pszNewStringT, pszString, i);
		pszNewStringT += i;
	}

	// Add terminating zero
	*pszNewStringT = '\0';

	// Return the new string buffer
	if (GetRefCount() > 1) return new StringBufferUTF8(pszNewString, nFinalLength);
	else {
		// Just modify and return this string buffer
		SetString(pszNewString, nFinalLength);
		return this;
	}
	*/
}

StringBuffer *StringBufferUTF8::Replace(const wchar_t szOld[], uint32 nOldLength, const wchar_t szNew[], uint32 nNewLength, uint32 &nReplaced)
{
	// [TODO]
	return NULL;
	/*
	// Check for only character replace
	if (nOldLength == 1 && nNewLength == 1)
		return Replace(szOld[0], szNew[0], nReplaced);

	// We need to convert this UTF8 string into an Unicode one :(
	wchar_t *pUnicode = new wchar_t[m_nLength + 1];
	mbstowcs(pUnicode, m_pszString, m_nLength + 1);

	// First, get the number of substrings to replace
	nReplaced = 0;
	const wchar_t *pszString = pUnicode;
	const wchar_t *pszEnd    = pUnicode + m_nLength;
	while (pszString<pszEnd) {
		if (!wcsncmp(pszString, szOld, nOldLength)) {
			nReplaced++;
			pszString += nOldLength;
		} else pszString++;
	}

	// Jipi, no substrings, no further work to do :)
	if (!nReplaced) {
		delete [] pUnicode;
		return this; // Nothing was changed and we can just return this string buffer
	}

	// Get and check the new length
	uint32 nFinalLength = m_nLength + (nNewLength - nOldLength)*nReplaced;
	if (!nFinalLength) {
		delete [] pUnicode;
		return NULL; // The string is now empty!
	}

	// Create the new string
	wchar_t *pszNewString  = new wchar_t[nFinalLength + 1];
	wchar_t *pszNewStringT = pszNewString;
	uint32 nSkipped = 0;
	pszString = pUnicode;
	for (uint32 i=0; i<nReplaced; i++) {
		// Find substring
		while (wcsncmp(pszString, szOld, nOldLength)) {
			pszString++;
			nSkipped++;
		}

		// Copy previous none substring characters
		if (nSkipped) {
			wcsncpy(pszNewStringT, pszString - nSkipped, nSkipped);
			pszNewStringT += nSkipped;
		}

		// Insert new substring
		wcsncpy(pszNewStringT, szNew, nNewLength);
		pszNewStringT += nNewLength;
		pszString += nOldLength;
		nSkipped = 0;
	}

	// Copy the rest of the old string to the new string
	if (*pszString != L'\0') {
		uint32 i = uint32(pszNewString + nFinalLength - pszNewStringT);
		wcsncpy(pszNewStringT, pszString, i);
		pszNewStringT += i;
	}

	// Add terminating zero
	*pszNewStringT = L'\0';

	// Cleanup
	delete [] pUnicode;

	// Return the new Unicode string buffer
	return new StringBufferUnicode(pszNewString, nFinalLength);
	*/
}

StringBuffer *StringBufferUTF8::SetCharacter(uint32 nIndex, char nCharacter)
{
	// [TODO]
	return NULL;
	/*
	// Do we need to clone this string buffer?
	if (m_pszString[nIndex] == nCharacter) return this; // Nothing was changed
	else {
		// We have to clone the string buffer :(
		StringBufferUTF8 *pClone = (StringBufferUTF8*)Duplicate();

		// Set the new character
		pClone->m_pszString[nIndex] = nCharacter;

		// Return the new string buffer
		return pClone;
	}*/
}

StringBuffer *StringBufferUTF8::SetCharacter(uint32 nIndex, wchar_t nCharacter)
{
	// [TODO]
	return NULL;
	/*
	// Get this character as Unicode
	wchar_t nThisCharacterUnicode;
	mbtowc(&nThisCharacterUnicode, &m_pszString[nIndex], 1);

	// Do we need to clone this string buffer?
	if (nThisCharacterUnicode == nCharacter) return this; // Nothing was changed
	else {
		// Create an Unicode string buffer when the first character has been found
		StringBufferUnicode *pClone = new StringBufferUnicode(m_pszString, m_nLength);

		// Set the new character
		pClone->m_pszString[nIndex] = nCharacter;

		// Return the new string buffer
		return pClone;
	}
	*/
}

StringBuffer *StringBufferUTF8::TrimLeading()
{
	// [TODO]
	return NULL;
/*
	const char *pszString = m_pszString;
	while (*pszString == ' ' || *pszString == '\t') pszString++;
	if (pszString == m_pszString) {
		// Nothing to change
		return this;
	} else {
		// Get the number of characters to delete
		uint32 nCount = uint32(pszString - m_pszString);

		// Is the string now empty?
		if (nCount == m_nLength) return NULL;			   // The string is now empty
		else					 return Delete(0, nCount); // Return the new string buffer
	}
	*/
}

StringBuffer *StringBufferUTF8::TrimTrailing()
{
	// [TODO]
	return NULL;
	/*
	const char *pszEnd    = m_pszString + m_nLength - 1;
	const char *pszString = pszEnd;
	while (*pszString == ' ' || *pszString == '\t') pszString--;
	if (pszString == pszEnd) {
		// Nothing to change
		return this;
	} else {
		// Get the number of characters to delete
		uint32 nCount = uint32(pszEnd - pszString);

		// Is the string now empty?
		if (nCount == m_nLength) return NULL;												 // The string is now empty
		else					 return Delete(uint32(pszString - m_pszString) + 1, nCount); // Return the new string buffer
	}
	*/
}

StringBuffer *StringBufferUTF8::RemoveLineEndings()
{
	// [TODO]
	return NULL;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
