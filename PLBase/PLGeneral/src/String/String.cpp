/*********************************************************\
 *  File: String.cpp                                     *
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
// <<nostepinto>> PLGeneral::String::.*


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#ifdef LINUX
	#include <inttypes.h>
	#include <wchar.h>
	#include "PLGeneral/PLGeneralLinuxWrapper.h"
#endif
#include "PLGeneral/Core/MemoryManager.h"
#include "PLGeneral/String/UTF8Tools.h"
#include "PLGeneral/String/StringBufferUTF8.h"
#include "PLGeneral/String/StringBufferASCII.h"
#include "PLGeneral/String/StringBufferUnicode.h"
#include "PLGeneral/String/String.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4996) // "'strdup': The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: _strdup. See online help for details."


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ String Implementation                                 ]
//[-------------------------------------------------------]
/**
*  @brief
*    Creates a new formatted string (like sprintf)
*/
String String::Format(const char *pszFormat, ...)
{
	String sString;

	// Check format string
	if (pszFormat && pszFormat[0] != '\0') {
		// We REALLY need to set the locale to a known setting... else we may get floats like "1,123" instead of "1.123"!
		char *pSaveLocale = strdup(setlocale(LC_ALL, nullptr));	// Get the current set locale, we REALLY need to backup the locale because it "may" be changed by "setlocale"
		setlocale(LC_ALL, "C");

		// Get the required buffer length, does not include the terminating zero character
		va_list vaList;
		va_start(vaList, pszFormat);
		const int nLength = _vscprintf(pszFormat, vaList);
		va_end(vaList);

		// Check length
		if (nLength > 0) {
			// Request an ASCII string buffer from the string buffer manager
			sString.m_pStringBuffer = StringBuffer::Manager.GetStringBufferASCII(nLength);
			if (sString.m_pStringBuffer) {
				sString.m_pStringBuffer->AddReference();

				// In here, because we KNOW what we're doing, we access the internal string buffer data directly
				StringBufferASCII *pStringBufferASCII = static_cast<StringBufferASCII*>(sString.m_pStringBuffer);

				// Print the formatted string
				va_start(vaList, pszFormat);
				vsprintf(pStringBufferASCII->m_pszString, pszFormat, vaList);
				va_end(vaList);

				// Set the correct string length
				pStringBufferASCII->m_nLength = nLength;
			}
		}

		// Be polite and restore the previously set locale
		setlocale(LC_ALL, pSaveLocale);
		free(pSaveLocale);	// ... and don't forget to free the memory of our locale backup...
	}

	// Return new string
	return sString;
}

String String::Format(const wchar_t *pszFormat, ...)
{
	String sString;

	// Check format string
	if (pszFormat && pszFormat[0] != L'\0') {
		// We REALLY need to set the locale to a known setting... else we may get floats like "1,123" instead of "1.123"!
		char *pSaveLocale = strdup(setlocale(LC_ALL, nullptr));	// Get the current set locale, we REALLY need to backup the locale because it "may" be changed by "setlocale"
		setlocale(LC_ALL, "C");

		// Get the required buffer length, does not include the terminating zero character
		va_list vaList;
		va_start(vaList, pszFormat);
		const int nLength = _vscwprintf(pszFormat, vaList);
		va_end(vaList);

		// Check length
		if (nLength > 0) {
			// Request an unicode string buffer from the string buffer manager
			sString.m_pStringBuffer = StringBuffer::Manager.GetStringBufferUnicode(nLength);
			if (sString.m_pStringBuffer) {
				sString.m_pStringBuffer->AddReference();

				// In here, because we KNOW what we're doing, we access the internal string buffer data directly
				StringBufferUnicode *pStringBufferUnicode = static_cast<StringBufferUnicode*>(sString.m_pStringBuffer);

				// Print the formatted string
				va_start(vaList, pszFormat);
				vswprintf(pStringBufferUnicode->m_pszString, nLength + 1, pszFormat, vaList);
				va_end(vaList);

				// Set the correct string length
				pStringBufferUnicode->m_nLength = nLength;
			}
		}

		// Be polite and restore the previously set locale
		setlocale(LC_ALL, pSaveLocale);
		free(pSaveLocale);	// ... and don't forget to free the memory of our locale backup...
	}

	// Return new string
	return sString;
}

/**
*  @brief
*    Sets the character string as UTF8
*/
String String::FromUTF8(const char *pszUTF8, int nLength, uint32 nNumOfBytes)
{
	// Valid string?
	if (pszUTF8) {
		// Get the number of characters and number of bytes of the given string
		if (nLength > 0) {
			if (!nNumOfBytes)
				UTF8Tools::GetNumOfCharactersAndBytes(pszUTF8, nNumOfBytes);
		} else {
			if (nNumOfBytes)
				nLength = UTF8Tools::GetNumOfCharacters(pszUTF8, nNumOfBytes);
			else
				nLength = UTF8Tools::GetNumOfCharactersAndBytes(pszUTF8, nNumOfBytes);
		}

		// Valid string?
		if (nLength && nNumOfBytes) {
			// Allocate the wide character string (+1 for the terminating zero)
			wchar_t *pszWideCharacterString = new wchar_t[nLength + 1];

			// Get the wide character string (+1 for the terminating zero)
			UTF8Tools::ToWideCharacterString(pszWideCharacterString, nLength + 1, pszUTF8, nNumOfBytes);

			// Create a new string buffer and take over the control of the given memory
			return String(pszWideCharacterString, false, nLength);
		}
	}

	// Just return an empty string...
	return "";
}

/**
*  @brief
*    Default constructor
*/
String::String() :
	m_pStringBuffer(nullptr)
{
}

/**
*  @brief
*    Character constructor
*/
String::String(char nValue)
{
	// Terminating zero?
	if (nValue != '\0') {
		// Request an ASCII string buffer from the string buffer manager
		m_pStringBuffer = StringBuffer::Manager.GetStringBufferASCII(1);
		if (m_pStringBuffer) {
			m_pStringBuffer->AddReference();
			m_pStringBuffer->Append(&nValue, 1);
		}
	} else {
		// Empty string
		m_pStringBuffer = nullptr;
	}
}

String::String(wchar_t nValue)
{
	// Terminating zero?
	if (nValue != L'\0') {
		// Request an unicode string buffer from the string buffer manager
		m_pStringBuffer = StringBuffer::Manager.GetStringBufferUnicode(1);
		if (m_pStringBuffer) {
			m_pStringBuffer->AddReference();
			m_pStringBuffer->Append(&nValue, 1);
		}
	} else {
		// Empty string
		m_pStringBuffer = nullptr;
	}
}

/**
*  @brief
*    Constructor
*/
String::String(const char *pszString, bool bCopy, int nLength)
{
	// Is pszString a null pointer?
	if (pszString) {
		// Get the length of the given string?
		if (nLength < 0) {
			// Get the length of the given string (excluding the terminating zero)
			nLength = pszString ? static_cast<uint32>(strlen(pszString)) : 0;
		}
	} else {
		// A null pointer string = length of 0!
		nLength = 0;
	}

	// Set string
	if (nLength) {
		// Copy string?
		if (bCopy) {
			// Request an ASCII string buffer from the string buffer manager
			m_pStringBuffer = StringBuffer::Manager.GetStringBufferASCII(nLength);
			if (m_pStringBuffer) {
				m_pStringBuffer->AddReference();
				m_pStringBuffer->Append(pszString, nLength);
			}
		} else {
			// Create a new string buffer and take over the control of the given memory
			m_pStringBuffer = new StringBufferASCII(const_cast<char*>(pszString), nLength, nLength);
			m_pStringBuffer->AddReference();
		}
	} else {
		// Empty string
		m_pStringBuffer = nullptr;

		// Lookout, the length may be 0, but it's still possible that the pszString pointer is valid -
		// and now we really have to fullfill the duties described within the method documentation!
		if (pszString && !bCopy)
			delete [] pszString;
	}
}

String::String(const wchar_t *pszString, bool bCopy, int nLength)
{
	// Is pszString a null pointer?
	if (pszString) {
		// Get the length of the given string?
		if (nLength < 0) {
			// Get the length of the given string (excluding the terminating zero)
			nLength = pszString ? static_cast<uint32>(wcslen(pszString)) : 0;
		}
	} else {
		// A null pointer string = length of 0!
		nLength = 0;
	}

	// Set string
	if (nLength) {
		// Copy string
		if (bCopy) {
			// Request an unicode string buffer from the string buffer manager
			m_pStringBuffer = StringBuffer::Manager.GetStringBufferUnicode(nLength);
			if (m_pStringBuffer) {
				m_pStringBuffer->AddReference();
				m_pStringBuffer->Append(pszString, nLength);
			}
		} else {
			// Create a new string buffer and take over the control of the given memory
			m_pStringBuffer = new StringBufferUnicode(const_cast<wchar_t*>(pszString), nLength, nLength);
			m_pStringBuffer->AddReference();
		}
	} else {
		// Empty string
		m_pStringBuffer = nullptr;

		// Lookout, the length may be 0, but it's still possible that the pszString pointer is valid -
		// and now we really have to fullfill the duties described within the method documentation!
		if (pszString && !bCopy)
			delete [] pszString;
	}
}

/**
*  @brief
*    Copy constructor
*/
String::String(const String &sString)
{
	// Copy source string by assigning to it's string buffer
	if (sString.m_pStringBuffer) {
		m_pStringBuffer = sString.m_pStringBuffer;
		m_pStringBuffer->AddReference();
	} else {
		// Empty string
		m_pStringBuffer = nullptr;
	}
}

/**
*  @brief
*    Number constructor
*/
String::String(bool bValue) :
	m_pStringBuffer(nullptr)
{
	*this = bValue;
}

String::String(int nValue)
{
	// Sadly, the useful "itoa" is a non-standard extension to the standard C
	#ifdef WIN32
		// Request an ASCII string buffer from the string buffer manager
		// -> According to the "itoa"-documentation, this buffer should be 33 bytes long
		m_pStringBuffer = StringBuffer::Manager.GetStringBufferASCII(33);
		if (m_pStringBuffer) {
			m_pStringBuffer->AddReference();

			// And there the magic happens, number -> string :D
			_itoa(nValue, static_cast<StringBufferASCII*>(m_pStringBuffer)->m_pszString, 10);

			// Hm, _itoa doesn't tell us how many characters were actually written...
			m_pStringBuffer->m_nLength = strlen(static_cast<StringBufferASCII*>(m_pStringBuffer)->m_pszString);
		}
	#else
		// [TODO] Check itoa under Linux
		// Use the "portable", but less efficient way
		m_pStringBuffer = nullptr;
		*this = Format("%d", nValue);
	#endif
}

String::String(uint8 nValue) :
	m_pStringBuffer(nullptr)
{
	*this = nValue;
}

String::String(uint16 nValue) :
	m_pStringBuffer(nullptr)
{
	*this = nValue;
}

String::String(uint32 nValue) :
	m_pStringBuffer(nullptr)
{
	*this = nValue;
}

String::String(uint64 nValue) :
	m_pStringBuffer(nullptr)
{
	*this = nValue;
}

String::String(long nValue) :
	m_pStringBuffer(nullptr)
{
	*this = nValue;
}

String::String(float fValue) :
	m_pStringBuffer(nullptr)
{
	*this = fValue;
}

String::String(double fValue) :
	m_pStringBuffer(nullptr)
{
	*this = fValue;
}

/**
*  @brief
*    Internal copy constructor
*/
String::String(StringBuffer *pStringBuffer)
{
	// Copy source string by assigning to it's string buffer
	if (pStringBuffer) {
		m_pStringBuffer = pStringBuffer;
		m_pStringBuffer->AddReference();
	} else {
		// Empty string
		m_pStringBuffer = nullptr;
	}
}

/**
*  @brief
*    Destructor
*/
String::~String()
{
	// Release string buffer
	if (m_pStringBuffer)
		StringBuffer::Manager.ReleaseStringBuffer(*m_pStringBuffer);
}

/**
*  @brief
*    Returns the length of the string
*/
uint32 String::GetLength() const
{
	return m_pStringBuffer ? m_pStringBuffer->GetLength() : 0;
}

/**
*  @brief
*    Returns the internal string format
*/
String::EFormat String::GetFormat() const
{
	return m_pStringBuffer ? m_pStringBuffer->GetFormat() : ASCII;
}

/**
*  @brief
*    Returns the number of bytes the string is using
*/
uint32 String::GetNumOfBytes() const
{
	return m_pStringBuffer ? m_pStringBuffer->GetNumOfBytes() : 0;
}

/**
*  @brief
*    Get a ASCII character of the string
*/
char String::operator [](uint32 nIndex) const
{
	// Terminating \0 by default...
	return (nIndex < GetLength()) ? GetASCII()[nIndex] : '\0';
}

/**
*  @brief
*    Returns the character string as ASCII
*/
const char *String::GetASCII() const
{
	return m_pStringBuffer ? m_pStringBuffer->GetASCII()->m_pszString : "";
}

/**
*  @brief
*    Returns the ASCII character string
*/
String::operator const char *() const
{
	return m_pStringBuffer ? m_pStringBuffer->GetASCII()->m_pszString : "";
}

/**
*  @brief
*    Returns the character string as Unicode
*/
const wchar_t *String::GetUnicode() const
{
	return m_pStringBuffer ? m_pStringBuffer->GetUnicode()->m_pszString : L"";
}

/**
*  @brief
*    Returns the Unicode character string
*/
String::operator const wchar_t *() const
{
	return m_pStringBuffer ? m_pStringBuffer->GetUnicode()->m_pszString : L"";
}

/**
*  @brief
*    Copy operator
*/
String &String::operator =(const String &sString)
{
	// Assign new string buffer (all security check are done within this function... :)
	SetStringBuffer(sString.m_pStringBuffer);

	// Return a reference to this instance
	return *this;
}

/**
*  @brief
*    Copy operator
*/
String &String::operator =(const char *pszString)
{
	// Get the length of the given string (excluding the terminating zero)
	const uint32 nLength = pszString ? static_cast<uint32>(strlen(pszString)) : 0;

	// Set new string
	if (nLength) {
		// Release old string buffer
		if (m_pStringBuffer)
			StringBuffer::Manager.ReleaseStringBuffer(*m_pStringBuffer);

		// Request an ASCII string buffer from the string buffer manager
		m_pStringBuffer = StringBuffer::Manager.GetStringBufferASCII(nLength);
		if (m_pStringBuffer) {
			m_pStringBuffer->AddReference();
			m_pStringBuffer->Append(pszString, nLength);
		}

	// Empty string
	} else {
		ReleaseStringBuffer();
	}

	// Return a reference to this instance
	return *this;
}

String &String::operator =(const wchar_t *pszString)
{
	// Get the length of the given string (excluding the terminating zero)
	const uint32 nLength = pszString ? static_cast<uint32>(wcslen(pszString)) : 0;

	// Set new string
	if (nLength) {
		// Release old string buffer
		if (m_pStringBuffer)
			StringBuffer::Manager.ReleaseStringBuffer(*m_pStringBuffer);

		// Request an unicode string buffer from the string buffer manager
		m_pStringBuffer = StringBuffer::Manager.GetStringBufferUnicode(nLength);
		if (m_pStringBuffer) {
			m_pStringBuffer->AddReference();
			m_pStringBuffer->Append(pszString, nLength);
		}

	// Empty string
	} else {
		ReleaseStringBuffer();
	}

	// Return a reference to this instance
	return *this;
}

/**
*  @brief
*    Concatenates strings
*/
String String::operator +(const String &sString) const
{
	// Check whether this string is empty
	if (!m_pStringBuffer)
		return sString; // Just return the other string

	// Check whether the other string is empty
	if (!sString.m_pStringBuffer)
		return *this; // Just return this string

	// Create concatenated string
	String sResult = *this;
	sResult.Insert(sString, m_pStringBuffer->GetLength(), sString.GetLength());
	return sResult;
}

/**
*  @brief
*    Concatenates strings
*/
String String::operator +(const char *pszString) const
{
	// Check whether this string is empty
	if (!m_pStringBuffer)
		return pszString; // Just return the other string

	// Check whether the other string is empty
	if (pszString) {
		// Get the length of the given string (excluding the terminating zero)
		const uint32 nLength = static_cast<uint32>(strlen(pszString));
		if (nLength) {
			// Compose new string
			String sResult = *this;
			sResult.SetStringBuffer(sResult.m_pStringBuffer->Append(pszString, nLength));
			return sResult;
		}
	}

	// Just return this string
	return *this;
}

String String::operator +(const wchar_t *pszString) const
{
	// Check whether this string is empty
	if (!m_pStringBuffer)
		return pszString; // Just return the other string

	// Check whether the other string is empty
	if (pszString) {
		// Get the length of the given string (excluding the terminating zero)
		const uint32 nLength = static_cast<uint32>(wcslen(pszString));
		if (nLength) {
			// Compose new string
			String sResult = *this;
			sResult.SetStringBuffer(sResult.m_pStringBuffer->Append(pszString, nLength));
			return sResult;
		}
	}

	// Just return this string
	return *this;
}

/**
*  @brief
*    Concatenate strings
*/
String operator +(const char *pszString, const String &sString)
{
	// Is the second string empty?
	if (!sString.GetLength())
		return pszString; // Just return the first string

	// Check whether the first string is empty
	if (pszString) {
		// Get the length of the given string (excluding the terminating zero)
		const uint32 nLength = static_cast<uint32>(strlen(pszString));
		if (nLength) {
			// Compose new string
			String sResult = pszString;
			sResult += sString;
			return sResult;
		}
	}

	// Just return the second string
	return sString;
}

String operator +(const wchar_t *pszString, const String &sString)
{
	// Is the second string empty?
	if (!sString.GetLength())
		return pszString; // Just return the first string

	// Check whether the first string is empty
	if (pszString) {
		// Get the length of the given string (excluding the terminating zero)
		const uint32 nLength = static_cast<uint32>(wcslen(pszString));
		if (nLength) {
			// Compose new string
			String sResult = pszString;
			sResult += sString;
			return sResult;
		}
	}

	// Just return the second string
	return sString;
}

/**
*  @brief
*    Concatenates strings
*/
String &String::operator +=(const String &sString)
{
	// Check whether this string is empty
	if (m_pStringBuffer) {
		// Check whether the other string is valid
		if (sString.m_pStringBuffer) {
			// Combine the two strings
			Insert(sString, m_pStringBuffer->GetLength(), sString.GetLength());
		}
	} else {
		// Check whether the other string is valid
		if (sString.m_pStringBuffer) {
			sString.m_pStringBuffer->AddReference();
			m_pStringBuffer = sString.m_pStringBuffer;
		}
	}

	// Done
	return *this;
}

/**
*  @brief
*    Concatenates strings
*/
String &String::operator +=(const char *pszString)
{
	// Get the length of the given string
	if (pszString) {
		// Get the length of the given string (excluding the terminating zero)
		const uint32 nLength = static_cast<uint32>(strlen(pszString));
		if (nLength) {
			// Check whether this string is empty
			if (m_pStringBuffer) {
				// Combine the two strings
				SetStringBuffer(m_pStringBuffer->Append(pszString, nLength));
			} else {
				// Request an ASCII string buffer from the string buffer manager
				m_pStringBuffer = StringBuffer::Manager.GetStringBufferASCII(nLength);
				if (m_pStringBuffer) {
					m_pStringBuffer->AddReference();
					m_pStringBuffer->Append(pszString, nLength);
				}
			}
		}
	}

	// Done
	return *this;
}

String &String::operator +=(const wchar_t *pszString)
{
	// Get the length of the given string
	if (pszString) {
		// Get the length of the given string (excluding the terminating zero)
		const uint32 nLength = static_cast<uint32>(wcslen(pszString));
		if (nLength) {
			// Check whether this string is empty
			if (m_pStringBuffer) {
				// Combine the two strings
				SetStringBuffer(m_pStringBuffer->Append(pszString, nLength));
			} else {
				// Request an unicode string buffer from the string buffer manager
				m_pStringBuffer = StringBuffer::Manager.GetStringBufferUnicode(nLength);
				if (m_pStringBuffer) {
					m_pStringBuffer->AddReference();
					m_pStringBuffer->Append(pszString, nLength);
				}
			}
		}
	}

	// Done
	return *this;
}

/**
*  @brief
*    Compares this string and the given one lexicographically
*/
bool String::operator <(const String &sString) const
{
	// Check whether this string is empty
	if (m_pStringBuffer) {
		// Check whether the other string is valid
		if (!sString.m_pStringBuffer)
			return false; // The other string is empty while the this one is not, empty is less :)

		// Compare
		switch (m_pStringBuffer->GetFormat()) {
			case ASCII:
				switch (sString.GetFormat()) {
					case ASCII:
						return m_pStringBuffer->IsLessThan(static_cast<StringBufferASCII*>(sString.m_pStringBuffer)->m_pszString, sString.m_pStringBuffer->GetLength()); // Same format

					case Unicode:
						return sString.m_pStringBuffer->IsGreaterThan(GetUnicode(), m_pStringBuffer->GetLength());
				}
				break; // We should NEVER get in here!

			case Unicode:
				switch (sString.GetFormat()) {
					case ASCII:
						return m_pStringBuffer->IsLessThan(sString.GetUnicode(), sString.m_pStringBuffer->GetLength());

					case Unicode:
						return m_pStringBuffer->IsLessThan(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, sString.m_pStringBuffer->GetLength()); // Same format
				}
				break; // We should NEVER get in here!
		}

		// We should NEVER get in here!
		return false;
	} else {
		// Check whether the other string is empty, too
		if (sString.m_pStringBuffer)
			return true;  // This string is empty while the other is not, empty is less :)
		else
			return false; // Both strings are empty, so they are equal
	}
}

/**
*  @brief
*    Compares this string and the given one lexicographically
*/
bool String::operator <(const char *pszString) const
{
	// Check whether this string is empty
	if (m_pStringBuffer) {
		// Check whether the other string is valid
		if (pszString) {
			// Get the length of the given string (excluding the terminating zero)
			const uint32 nLength = static_cast<uint32>(strlen(pszString));
			if (nLength) {
				// Compare
				return m_pStringBuffer->IsLessThan(pszString, nLength);
			}
		}

		// The other string is empty while the this one is not, empty is less :)
		return false;
	} else {
		// Check whether the other string is empty, too
		if (pszString && pszString[0] != '\0')
			return true;  // This string is empty while the other is not, empty is less :)
		else
			return false; // Both strings are empty, so they are equal
	}
}

bool String::operator <(const wchar_t *pszString) const
{
	// Check whether this string is empty
	if (m_pStringBuffer) {
		// Check whether the other string is valid
		if (pszString) {
			// Get the length of the given string (excluding the terminating zero)
			const uint32 nLength = static_cast<uint32>(wcslen(pszString));
			if (nLength) {
				// Compare
				return m_pStringBuffer->IsLessThan(pszString, nLength);
			}
		}

		// The other string is empty while the this one is not, empty is less :)
		return false;
	} else {
		// Check whether the other string is empty, too
		if (pszString && pszString[0] != L'\0')
			return true;  // This string is empty while the other is not, empty is less :)
		else
			return false; // Both strings are empty, so they are equal
	}
}

/**
*  @brief
*    Compares this string and the given one lexicographically
*/
bool String::operator >(const String &sString) const
{
	// Check whether this string is empty
	if (m_pStringBuffer) {
		// Check whether the other string is valid
		if (!sString.m_pStringBuffer)
			return true; // The other string is empty while the this one is not, empty is less :)

		// Compare
		switch (m_pStringBuffer->GetFormat()) {
			case ASCII:
				switch (sString.GetFormat()) {
					case ASCII:
						return m_pStringBuffer->IsGreaterThan(static_cast<StringBufferASCII*>(sString.m_pStringBuffer)->m_pszString, sString.m_pStringBuffer->GetLength()); // Same format

					case Unicode:
						return sString.m_pStringBuffer->IsLessThan(GetUnicode(), m_pStringBuffer->GetLength());
				}
				break; // We should NEVER get in here!

			case Unicode:
				switch (sString.GetFormat()) {
					case ASCII:
						return m_pStringBuffer->IsGreaterThan(sString.GetUnicode(), sString.m_pStringBuffer->GetLength());

					case Unicode:
						return m_pStringBuffer->IsGreaterThan(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, sString.m_pStringBuffer->GetLength()); // Same format
				}
				break; // We should NEVER get in here!
		}

		// We should NEVER get in here!
		return false;
	} else {
		// Because this string is empty the other one is ALWAYS greater or equal
		return false;
	}
}

/**
*  @brief
*    Compares this string and the given one lexicographically
*/
bool String::operator >(const char *pszString) const
{
	// Check whether this string is empty
	if (m_pStringBuffer) {
		// Check whether the other string is valid
		if (pszString) {
			// Get the length of the given string (excluding the terminating zero)
			const uint32 nLength = static_cast<uint32>(strlen(pszString));
			if (nLength) {
				// Compare
				return m_pStringBuffer->IsGreaterThan(pszString, nLength);
			}
		}

		// The other string is empty while the this one is not, empty is less :)
		return true;
	} else {
		// Because this string is empty the other one is ALWAYS greater or equal
		return false;
	}
}

bool String::operator >(const wchar_t *pszString) const
{
	// Check whether this string is empty
	if (m_pStringBuffer) {
		// Check whether the other string is valid
		if (pszString) {
			// Get the length of the given string (excluding the terminating zero)
			const uint32 nLength = static_cast<uint32>(wcslen(pszString));
			if (nLength) {
				// Compare
				return m_pStringBuffer->IsGreaterThan(pszString, nLength);
			}
		}

		// The other string is empty while the this one is not, empty is less :)
		return true;
	} else {
		// Because this string is empty the other one is ALWAYS greater or equal
		return false;
	}
}

/**
*  @brief
*    Compare operator (case sensitive)
*/
bool String::operator ==(const String &sString) const
{
	return Compare(sString);
}

/**
*  @brief
*    Compare operator (case sensitive)
*/
bool String::operator ==(const char *pszString) const
{
	return Compare(pszString);
}

bool String::operator ==(const wchar_t *pszString) const
{
	return Compare(pszString);
}

/**
*  @brief
*    Compare operator (case sensitive)
*/
bool String::operator !=(const String &sString) const
{
	return !Compare(sString);
}

/**
*  @brief
*    Compare operator (case sensitive)
*/
bool String::operator !=(const char *pszString) const
{
	return !Compare(pszString);
}

bool String::operator !=(const wchar_t *pszString) const
{
	return !Compare(pszString);
}

/**
*  @brief
*    Compare function (case sensitive)
*/
bool String::Compare(const String &sString, uint32 nPos, int nCount) const
{
	// Check the count
	if (nCount) {
		// Check whether this string is empty
		if (m_pStringBuffer) {
			// Check whether the other string is valid
			if (!sString.m_pStringBuffer)
				return false; // Strings are not equal

			// Check whether both use the same buffer
			if (!nPos && m_pStringBuffer == sString.m_pStringBuffer)
				return true; // Strings MUST be equal :)

			// Compare
			switch (m_pStringBuffer->GetFormat()) {
				case ASCII:
					switch (sString.GetFormat()) {
						case ASCII:
							return m_pStringBuffer->Compare(static_cast<StringBufferASCII*>(sString.m_pStringBuffer)->m_pszString, sString.GetLength(), nPos, (nCount < 0) ? 0 : static_cast<uint32>(nCount));

						case Unicode:
							return m_pStringBuffer->Compare(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, sString.GetLength(), nPos, (nCount < 0) ? 0 : static_cast<uint32>(nCount));
					}
					break; // We should NEVER get in here!

				case Unicode:
					switch (sString.GetFormat()) {
						case ASCII:
							return m_pStringBuffer->Compare(sString.GetUnicode(), sString.GetLength(), nPos, (nCount < 0) ? 0 : static_cast<uint32>(nCount));

						case Unicode:
							return m_pStringBuffer->Compare(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, sString.GetLength(), nPos, (nCount < 0) ? 0 : static_cast<uint32>(nCount));
					}
					break; // We should NEVER get in here!
			}

			// We should NEVER get in here!
			return false;
		} else {
			// Check whether the other string is empty, too
			if (sString.m_pStringBuffer)
				return false; // Strings are not equal
			else
				return true;  // Both strings are empty, so they are equal
		}
	} else {
		// Return "strings are equal"
		return true;
	}
}

/**
*  @brief
*    Compare function (case sensitive)
*/
bool String::Compare(const char *pszString, uint32 nPos, int nCount) const
{
	// Check the count
	if (nCount) {
		// Check whether this string is empty
		if (m_pStringBuffer) {
			// Check whether the other string is valid
			if (pszString) {
				// Get the length of the given string (excluding the terminating zero)
				const uint32 nLength = static_cast<uint32>(strlen(pszString));
				if (nLength)
					return m_pStringBuffer->Compare(pszString, nLength, nPos, (nCount < 0) ? 0 : static_cast<uint32>(nCount));
			}

			// Strings are not equal
			return false;
		} else {
			// Check whether the other string is empty, too
			if (pszString && pszString[0] != '\0')
				return false; // Strings are not equal
			else
				return true;  // Both strings are empty, so they are equal
		}
	} else {
		// Return "strings are equal"
		return true;
	}
}

bool String::Compare(const wchar_t *pszString, uint32 nPos, int nCount) const
{
	// Check the count
	if (nCount) {
		// Check whether this string is empty
		if (m_pStringBuffer) {
			// Check whether the other string is valid
			if (pszString) {
				// Get the length of the given string (excluding the terminating zero)
				const uint32 nLength = static_cast<uint32>(wcslen(pszString));
				if (nLength)
					return m_pStringBuffer->Compare(pszString, nLength, nPos, (nCount < 0) ? 0 : static_cast<uint32>(nCount));
			}

			// Strings are not equal
			return false;
		} else {
			// Check whether the other string is empty, too
			if (pszString && pszString[0] != L'\0')
				return false; // Strings are not equal
			else
				return true;  // Both strings are empty, so they are equal
		}
	} else {
		// Return "strings are equal"
		return true;
	}
}

/**
*  @brief
*    Compare function (case insensitive)
*/
bool String::CompareNoCase(const String &sString, uint32 nPos, int nCount) const
{
	// Check the count
	if (nCount) {
		// Check whether this string is empty
		if (m_pStringBuffer) {
			// Check whether the other string is valid
			if (!sString.m_pStringBuffer)
				return false; // Strings are not equal

			// Check whether both use the same buffer
			if (!nPos && m_pStringBuffer == sString.m_pStringBuffer)
				return true; // Strings MUST be equal :)

			// Compare
			switch (m_pStringBuffer->GetFormat()) {
				case ASCII:
					switch (sString.GetFormat()) {
						case ASCII:
							return m_pStringBuffer->CompareNoCase(static_cast<StringBufferASCII*>(sString.m_pStringBuffer)->m_pszString, sString.GetLength(), nPos, (nCount < 0) ? 0 : static_cast<uint32>(nCount));

						case Unicode:
							return m_pStringBuffer->CompareNoCase(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, sString.GetLength(), nPos, (nCount < 0) ? 0 : static_cast<uint32>(nCount));
					}
					break; // We should NEVER get in here!

				case Unicode:
					switch (sString.GetFormat()) {
						case ASCII:
							return m_pStringBuffer->CompareNoCase(sString.GetUnicode(), sString.GetLength(), nPos, (nCount < 0) ? 0 : static_cast<uint32>(nCount));

						case Unicode:
							return m_pStringBuffer->CompareNoCase(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, sString.GetLength(), nPos, (nCount < 0) ? 0 : static_cast<uint32>(nCount));
					}
					break; // We should NEVER get in here!
			}

			// We should NEVER get in here!
			return false;
		} else {
			// Check whether the other string is empty, too
			if (sString.m_pStringBuffer)
				return false; // Strings are not equal
			else
				return true;  // Both strings are empty, so they are equal
		}
	} else {
		// Return "strings are equal"
		return true;
	}
}

/**
*  @brief
*    Compare function (case insensitive)
*/
bool String::CompareNoCase(const char *pszString, uint32 nPos, int nCount) const
{
	// Check the count
	if (nCount) {
		// Check whether this string is empty
		if (m_pStringBuffer) {
			// Check whether the other string is valid
			if (pszString) {
				// Get the length of the given string (excluding the terminating zero)
				const uint32 nLength = static_cast<uint32>(strlen(pszString));
				if (nLength)
					return m_pStringBuffer->CompareNoCase(pszString, nLength, nPos, (nCount < 0) ? 0 : static_cast<uint32>(nCount));
			}

			// Strings are not equal
			return false;
		} else {
			// Check whether the other string is empty, too
			if (pszString && pszString[0] != '\0')
				return false; // Strings are not equal
			else
				return true;  // Both strings are empty, so they are equal
		}
	} else {
		// Return "strings are equal"
		return true;
	}
}

bool String::CompareNoCase(const wchar_t *pszString, uint32 nPos, int nCount) const
{
	// Check the count
	if (nCount) {
		// Check whether this string is empty
		if (m_pStringBuffer) {
			// Check whether the other string is valid
			if (pszString) {
				// Get the length of the given string (excluding the terminating zero)
				const uint32 nLength = static_cast<uint32>(wcslen(pszString));
				if (nLength)
					return m_pStringBuffer->CompareNoCase(pszString, nLength, nPos, (nCount < 0) ? 0 : static_cast<uint32>(nCount));
			}

			// Strings are not equal
			return false;
		} else {
			// Check whether the other string is empty, too
			if (pszString && pszString[0] != L'\0')
				return false; // Strings are not equal
			else
				return true;  // Both strings are empty, so they are equal
		}
	} else {
		// Return "strings are equal"
		return true;
	}
}

/**
*  @brief
*    Determines whether the string is alphabetic or not
*/
bool String::IsAlphabetic() const
{
	// No string, no alphabetic
	return (m_pStringBuffer && m_pStringBuffer->IsAlphabetic());
}

/**
*  @brief
*    Determines whether the string is alpha-numeric or not
*/
bool String::IsAlphaNumeric() const
{
	// No string, no alpha-numeric
	return (m_pStringBuffer && m_pStringBuffer->IsAlphaNumeric());
}

/**
*  @brief
*    Determines whether the string is numeric or not
*/
bool String::IsNumeric() const
{
	// No string, no numeric
	return (m_pStringBuffer && m_pStringBuffer->IsNumeric());
}

/**
*  @brief
*    Checks whether the given string is a substring of this string or not
*/
bool String::IsSubstring(const String &sString) const
{
	// Empty strings?
	if (!sString.GetLength())
		return true; // Substring
	if (!m_pStringBuffer)
		return false; // No substring

	// Find substring
	switch (m_pStringBuffer->GetFormat()) {
		case ASCII:
			switch (sString.GetFormat()) {
				case ASCII:
					return m_pStringBuffer->IsSubstring(static_cast<StringBufferASCII*>(sString.m_pStringBuffer)->m_pszString, 0); // Same format

				case Unicode:
					return m_pStringBuffer->IsSubstring(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, sString.m_pStringBuffer->GetLength());
			}
			break; // We should NEVER get in here!

		case Unicode:
			switch (sString.GetFormat()) {
				case ASCII:
					return m_pStringBuffer->IsSubstring(sString.GetUnicode(), sString.m_pStringBuffer->GetLength());

				case Unicode:
					return m_pStringBuffer->IsSubstring(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, 0); // Same format
			}
			break; // We should NEVER get in here!
	}

	// We should NEVER get in here!
	return false;
}

/**
*  @brief
*    Checks whether the given string is a substring of this string or not
*/
bool String::IsSubstring(const char *pszString) const
{
	// Is the given string empty
	if (pszString) {
		// Get the length of the given string (excluding the terminating zero)
		const uint32 nLength = static_cast<uint32>(strlen(pszString));
		if (nLength) {
			// Is this string emtpy?
			if (m_pStringBuffer)
				return m_pStringBuffer->IsSubstring(pszString, nLength);
			else
				return false; // No substring
		}
	}

	// Substring (because the given string is empty)
	return true;
}

bool String::IsSubstring(const wchar_t *pszString) const
{
	// Is the given string empty
	if (pszString) {
		// Get the length of the given string (excluding the terminating zero)
		const uint32 nLength = static_cast<uint32>(wcslen(pszString));
		if (nLength) {
			// Is this string emtpy?
			if (m_pStringBuffer)
				return m_pStringBuffer->IsSubstring(pszString, nLength);
			else
				return false; // No substring
		}
	}

	// Substring (because the given string is empty)
	return true;
}

/**
*  @brief
*    Returns the index of the substring if contained in this string
*/
int String::IndexOf(const String &sString, uint32 nPos) const
{
	// Is this string not empty and is the given position valid and is the given string not empty?
	if (m_pStringBuffer && nPos < m_pStringBuffer->GetLength() && sString.GetLength()) {
		// Get first index
		switch (m_pStringBuffer->GetFormat()) {
			case ASCII:
				switch (sString.GetFormat()) {
					case ASCII:
						return m_pStringBuffer->IndexOf(static_cast<StringBufferASCII*>(sString.m_pStringBuffer)->m_pszString, nPos, 0); // Same format

					case Unicode:
						return m_pStringBuffer->IndexOf(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, nPos, sString.m_pStringBuffer->GetLength());
				}
				break; // We should NEVER get in here!

			case Unicode:
				switch (sString.GetFormat()) {
					case ASCII:
						return m_pStringBuffer->IndexOf(sString.GetUnicode(), nPos, sString.m_pStringBuffer->GetLength());

					case Unicode:
						return m_pStringBuffer->IndexOf(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, nPos, 0); // Same format
				}
				break; // We should NEVER get in here!
		}
	}

	// No substring
	return -1;
}

/**
*  @brief
*    Returns the index of the substring if contained in this string
*/
int String::IndexOf(const char *pszString, uint32 nPos) const
{
	// Is this string not empty and is the given position valid and is the given string not empty?
	if (m_pStringBuffer && nPos < m_pStringBuffer->GetLength() && pszString) {
		// Get the length of the given string (excluding the terminating zero)
		const uint32 nLength = static_cast<uint32>(strlen(pszString));

		// Is the given string empty?
		if (nLength) {
			// Get the index
			return m_pStringBuffer->IndexOf(pszString, nPos, nLength);
		}
	}

	// No substring
	return -1;
}

int String::IndexOf(const wchar_t *pszString, uint32 nPos) const
{
	// Is this string not empty and is the given position valid and is the given string not empty?
	if (m_pStringBuffer && nPos < m_pStringBuffer->GetLength() && pszString) {
		// Get the length of the given string (excluding the terminating zero)
		const uint32 nLength = static_cast<uint32>(wcslen(pszString));

		// Is the given string empty?
		if (nLength) {
			// Get the index
			return m_pStringBuffer->IndexOf(pszString, nPos, nLength);
		}
	}

	// No substring
	return -1;
}

/**
*  @brief
*    Searches from backwards for the index of the substring within this string
*/
int String::LastIndexOf(const String &sString, int nPos) const
{
	// Is this string not empty and is the given position valid and is the given string not empty?
	if (m_pStringBuffer && nPos < static_cast<int>(m_pStringBuffer->GetLength()) && sString.GetLength()) {
		// Start at the last character?
		if (nPos < 0)
			nPos = m_pStringBuffer->GetLength() - 1;

		// Get last index
		switch (m_pStringBuffer->GetFormat()) {
			case ASCII:
				switch (sString.GetFormat()) {
					case ASCII:
						return m_pStringBuffer->LastIndexOf(static_cast<StringBufferASCII*>(sString.m_pStringBuffer)->m_pszString, nPos, sString.GetLength());

					case Unicode:
						return m_pStringBuffer->LastIndexOf(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, nPos, sString.GetLength());
				}
				break; // We should NEVER get in here!

			case Unicode:
				switch (sString.GetFormat()) {
					case ASCII:
						return m_pStringBuffer->LastIndexOf(sString.GetUnicode(), nPos, sString.GetLength());

					case Unicode:
						return m_pStringBuffer->LastIndexOf(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, nPos, sString.GetLength());
				}
				break; // We should NEVER get in here!
		}
	}

	// No substring
	return -1;
}

/**
*  @brief
*    Searches from backwards for the index of the substring within this string
*/
int String::LastIndexOf(const char *pszString, int nPos) const
{
	// Is this string not empty and is the given position valid and is the given string not empty?
	if (m_pStringBuffer && nPos < static_cast<int>(m_pStringBuffer->GetLength()) && pszString) {
		// Get the length of the given string (excluding the terminating zero)
		const uint32 nLength = static_cast<uint32>(strlen(pszString));

		// Is the given string empty?
		if (nLength) {
			// Start at the last character?
			if (nPos < 0)
				nPos = m_pStringBuffer->GetLength() - 1;

			// Get the last index
			return m_pStringBuffer->LastIndexOf(pszString, nPos, nLength);
		}
	}

	// No substring
	return -1;
}

int String::LastIndexOf(const wchar_t *pszString, int nPos) const
{
	// Is this string not empty and is the given position valid and is the given string not empty?
	if (m_pStringBuffer && nPos < static_cast<int>(m_pStringBuffer->GetLength()) && pszString) {
		// Get the length of the given string (excluding the terminating zero)
		const uint32 nLength = static_cast<uint32>(wcslen(pszString));

		// Is the given string empty?
		if (nLength) {
			// Start at the last character?
			if (nPos < 0)
				nPos = m_pStringBuffer->GetLength() - 1;

			// Get the last index
			return m_pStringBuffer->LastIndexOf(pszString, nPos, nLength);
		}
	}

	// No substring
	return -1;
}

/**
*  @brief
*    Get a substring from the string
*/
String String::GetSubstring(uint32 nPos, int nCount) const
{
	// Is this string empty or the given count zero?
	if (m_pStringBuffer && nCount) {
		// Is the given position valid?
		const uint32 nLength = GetLength();
		if (nPos < nLength) {
			// Check count
			if (nCount < 0 || static_cast<uint32>(nCount) > nLength - nPos)
				nCount = nLength - nPos;

			// Get the substring
			return m_pStringBuffer->GetSubstring(nPos, static_cast<uint32>(nCount));
		}
	}

	// Done
	return "";
}

/**
*  @brief
*    Change all characters to lower case
*/
String &String::ToLower()
{
	// Is there a string buffer?
	if (m_pStringBuffer) {
		// Change all characters to lower case, string 'may' be changed
		SetStringBuffer(m_pStringBuffer->ToLower());
	}

	// Done
	return *this;
}

/**
*  @brief
*    Change all characters to upper case
*/
String &String::ToUpper()
{
	// Is there a string buffer?
	if (m_pStringBuffer) {
		// Change all characters to upper case, string 'may' be changed
		SetStringBuffer(m_pStringBuffer->ToUpper());
	}

	// Done
	return *this;
}

/**
*  @brief
*    Delete a substring
*/
String &String::Delete(uint32 nPos, int nCount)
{
	// Is the given count not null?
	if (nCount) {
		// Check the length and the start position
		const uint32 nLength = GetLength();
		if (nLength && nPos < nLength) {
			// Check count
			if (nCount < 0 || static_cast<uint32>(nCount) > nLength - nPos)
				nCount = nLength - nPos;

			// Is the string empty now?
			if (nLength - nCount) {
				// If not, delete the given part
				SetStringBuffer(m_pStringBuffer->Delete(nPos, static_cast<uint32>(nCount)));
			} else {
				// The string is now empty!
				ReleaseStringBuffer();
			}
		}
	}

	// Return this
	return *this;
}

/**
*  @brief
*    Inserts a string at a given location
*/
String &String::Insert(const String &sString, uint32 nPos, int nCount)
{
	// Check if the count is not null and whether the position is valid
	if (nCount && nPos <= GetLength()) {
		// Check count
		const uint32 nStringLength = sString.GetLength();
		if (nStringLength) {
			// Check count
			if (nCount < 0 || static_cast<uint32>(nCount) > nStringLength)
				nCount = nStringLength;

			// Check if the string is empty
			if (m_pStringBuffer) {
				// Compose new string by appending?
				if (nPos == GetLength()) {
					switch (m_pStringBuffer->GetFormat()) {
						case ASCII:
							switch (sString.GetFormat()) {
								case ASCII:
									SetStringBuffer(m_pStringBuffer->Append(static_cast<StringBufferASCII*>(sString.m_pStringBuffer)->m_pszString, static_cast<uint32>(nCount)));
									break;

								case Unicode:
									SetStringBuffer(m_pStringBuffer->Append(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, static_cast<uint32>(nCount)));
									break;
							}
							break;

						case Unicode:
							switch (sString.GetFormat()) {
								case ASCII:
									SetStringBuffer(m_pStringBuffer->Append(sString.GetUnicode(), static_cast<uint32>(nCount)));
									break;

								case Unicode:
									SetStringBuffer(m_pStringBuffer->Append(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, static_cast<uint32>(nCount)));
									break;
							}
							break;
					}
				} else {
					switch (m_pStringBuffer->GetFormat()) {
						case ASCII:
							switch (sString.GetFormat()) {
								case ASCII:
									SetStringBuffer(m_pStringBuffer->Insert(static_cast<StringBufferASCII*>(sString.m_pStringBuffer)->m_pszString, nPos, static_cast<uint32>(nCount)));
									break;

								case Unicode:
									SetStringBuffer(m_pStringBuffer->Insert(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, nPos, static_cast<uint32>(nCount)));
									break;
							}
							break;

						case Unicode:
							switch (sString.GetFormat()) {
								case ASCII:
									SetStringBuffer(m_pStringBuffer->Insert(sString.GetUnicode(), nPos, static_cast<uint32>(nCount)));
									break;

								case Unicode:
									SetStringBuffer(m_pStringBuffer->Insert(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, nPos, static_cast<uint32>(nCount)));
									break;
							}
							break;
					}
				}

			// No string to insert into, create new string
			} else {
				if (static_cast<uint32>(nCount) == nStringLength) {
					m_pStringBuffer = sString.m_pStringBuffer;
					m_pStringBuffer->AddReference();
				} else {
					if (sString.GetFormat() == Unicode) {
						// Request an unicode string buffer from the string buffer manager
						m_pStringBuffer = StringBuffer::Manager.GetStringBufferUnicode(static_cast<uint32>(nCount));
						if (m_pStringBuffer) {
							m_pStringBuffer->AddReference();
							m_pStringBuffer->Append(static_cast<StringBufferUnicode*>(sString.m_pStringBuffer)->m_pszString, static_cast<uint32>(nCount));
						}
					} else {
						// Request an ASCII string buffer from the string buffer manager
						m_pStringBuffer = StringBuffer::Manager.GetStringBufferASCII(static_cast<uint32>(nCount));
						if (m_pStringBuffer) {
							m_pStringBuffer->AddReference();
							m_pStringBuffer->Append(static_cast<StringBufferASCII*>(sString.m_pStringBuffer)->m_pszString, static_cast<uint32>(nCount));
						}
					}
				}
			}
		}
	}

	// Done
	return *this;
}

/**
*  @brief
*    Inserts a string at a given location
*/
String &String::Insert(const char *pszString, uint32 nPos, int nCount)
{
	// Check if the string to insert and the position are valid
	if (pszString && nCount && nPos <= GetLength()) {
		// Get the length of the given string (excluding the terminating zero)
		const uint32 nStringLength = static_cast<uint32>(strlen(pszString));
		if (nStringLength) {
			// Check count
			if (nCount < 0 || static_cast<uint32>(nCount) > nStringLength)
				nCount = nStringLength;

			// Check if the string is empty
			if (m_pStringBuffer) {
				// Compose new string by appending?
				if (nPos == GetLength())
					SetStringBuffer(m_pStringBuffer->Append(pszString, static_cast<uint32>(nCount)));
				else
					SetStringBuffer(m_pStringBuffer->Insert(pszString, nPos, static_cast<uint32>(nCount)));
			} else {
				// Request an ASCII string buffer from the string buffer manager
				m_pStringBuffer = StringBuffer::Manager.GetStringBufferASCII(static_cast<uint32>(nCount));
				if (m_pStringBuffer) {
					m_pStringBuffer->AddReference();
					m_pStringBuffer->Append(pszString, static_cast<uint32>(nCount));
				}
			}
		}
	}

	// Done
	return *this;
}

String &String::Insert(const wchar_t *pszString, uint32 nPos, int nCount)
{
	// Check if the string to insert and the position are valid
	if (pszString && nCount && nPos <= GetLength()) {
		// Get the length of the given string (excluding the terminating zero)
		const uint32 nStringLength = static_cast<uint32>(wcslen(pszString));
		if (nStringLength) {
			if (nCount < 0 || static_cast<uint32>(nCount) > nStringLength)
				nCount = nStringLength;

			// Check if the string is empty
			if (m_pStringBuffer) {
				// Compose new string by appending?
				if (nPos == GetLength())
					SetStringBuffer(m_pStringBuffer->Append(pszString, static_cast<uint32>(nCount)));
				else
					SetStringBuffer(m_pStringBuffer->Insert(pszString, nPos, static_cast<uint32>(nCount)));
			} else {
				// Request an unicode string buffer from the string buffer manager
				m_pStringBuffer = StringBuffer::Manager.GetStringBufferUnicode(static_cast<uint32>(nCount));
				if (m_pStringBuffer) {
					m_pStringBuffer->AddReference();
					m_pStringBuffer->Append(pszString, static_cast<uint32>(nCount));
				}
			}
		}
	}

	// Done
	return *this;
}

/**
*  @brief
*    Copies a string
*/
String &String::Copy(const char *pszString, int nCount)
{
	// Get the length of the given string (excluding the terminating zero)
	const uint32 nLength = (pszString && nCount) ? static_cast<uint32>(strlen(pszString)) : 0;

	// Set new string
	if (nLength) {
		// Check count
		if (nCount > 0) {
			if (static_cast<uint32>(nCount) > nLength)
				nCount = nLength;
		} else {
			nCount = nLength;
		}

		// Release old string buffer
		if (m_pStringBuffer)
			StringBuffer::Manager.ReleaseStringBuffer(*m_pStringBuffer);

		// Request an ASCII string buffer from the string buffer manager
		m_pStringBuffer = StringBuffer::Manager.GetStringBufferASCII(static_cast<uint32>(nCount));
		if (m_pStringBuffer) {
			m_pStringBuffer->AddReference();
			m_pStringBuffer->Append(pszString, static_cast<uint32>(nCount));
		}
	} else {
		// Empty string
		ReleaseStringBuffer();
	}

	// Done
	return *this;
}

String &String::Copy(const wchar_t *pszString, int nCount)
{
	// Get the length of the given string (excluding the terminating zero)
	const uint32 nLength = (pszString && nCount) ? static_cast<uint32>(wcslen(pszString)) : 0;

	// Set new string
	if (nLength) {
		// Check count
		if (nCount) {
			if (static_cast<uint32>(nCount) > nLength)
				nCount = nLength;
		} else {
			nCount = nLength;
		}

		// Release old string buffer
		if (m_pStringBuffer)
			StringBuffer::Manager.ReleaseStringBuffer(*m_pStringBuffer);

		// Request an unicode string buffer from the string buffer manager
		m_pStringBuffer = StringBuffer::Manager.GetStringBufferUnicode(static_cast<uint32>(nCount));
		if (m_pStringBuffer) {
			m_pStringBuffer->AddReference();
			m_pStringBuffer->Append(pszString, static_cast<uint32>(nCount));
		}
	} else {
		// Empty string
		ReleaseStringBuffer();
	}

	// Done
	return *this;
}

/**
*  @brief
*    Replaces all occurences of a character by another character
*/
uint32 String::Replace(char nOld, char nNew)
{
	// Check length of string
	if (!m_pStringBuffer || nOld == nNew)
		return 0; // Nothing to do :)

	// Replace
	uint32 nReplaced;
	SetStringBuffer(m_pStringBuffer->Replace(nOld, nNew, nReplaced));

	// Return the number of replaced characters
	return nReplaced;
}

uint32 String::Replace(wchar_t nOld, wchar_t nNew)
{
	// Check length of string
	if (!m_pStringBuffer || nOld == nNew)
		return 0; // Nothing to do :)

	// Replace
	uint32 nReplaced;
	SetStringBuffer(m_pStringBuffer->Replace(nOld, nNew, nReplaced));

	// Return the number of replaced characters
	return nReplaced;
}

/**
*  @brief
*    Replaces all occurences of a substring by another string
*/
uint32 String::Replace(const String &sOld, const String &sNew)
{
	// Check the two given strings
	if (m_pStringBuffer && sOld.GetLength() && sOld.GetLength() <= m_pStringBuffer->GetLength() && sOld != sNew) {
		// Replace
		uint32 nReplaced;
		if (m_pStringBuffer->GetFormat() == ASCII && sOld.GetFormat() == ASCII && sNew.GetFormat() == ASCII)
			SetStringBuffer(m_pStringBuffer->Replace(sOld.GetASCII(), sOld.GetLength(), sNew.GetASCII(), sNew.GetLength(), nReplaced));
		else
			SetStringBuffer(m_pStringBuffer->Replace(sOld.GetUnicode(), sOld.GetLength(), sNew.GetUnicode(), sNew.GetLength(), nReplaced));

		// Return the number of replaced substrings
		return nReplaced;
	}

	// Nothing to do :)
	return 0;
}

/**
*  @brief
*    Replaces all occurences of a substring by another string
*/
uint32 String::Replace(const char *pszOld, const char *pszNew)
{
	// Is this string or the old string empty?
	if (m_pStringBuffer && pszOld) {
		// Get the length of the given old string (excluding the terminating zero)
		const uint32 nOldLength = static_cast<uint32>(strlen(pszOld));

		// Is the old string empty?
		if (nOldLength) {
			// Check the two given strings
			const uint32 nLength    = m_pStringBuffer->GetLength();
			const uint32 nNewLength = pszNew ? static_cast<uint32>(strlen(pszNew)) : 0;
			if (nOldLength <= nLength && !(nNewLength && nOldLength == nNewLength && !strcmp(pszOld, pszNew))) {
				// Replace
				uint32 nReplaced;
				SetStringBuffer(m_pStringBuffer->Replace(pszOld, nOldLength, pszNew ? pszNew : "", nNewLength, nReplaced));

				// Return the number of replaced substrings
				return nReplaced;
			}
		}
	}

	// Nothing to do :)
	return 0;
}

uint32 String::Replace(const wchar_t *pszOld, const wchar_t *pszNew)
{
	// Is this string or the old string empty?
	if (m_pStringBuffer && pszOld) {
		// Get the length of the given old string (excluding the terminating zero)
		const uint32 nOldLength = static_cast<uint32>(wcslen(pszOld));

		// Is the old string empty?
		if (nOldLength) {
			// Check the two given strings
			const uint32 nLength    = m_pStringBuffer->GetLength();
			const uint32 nNewLength = pszNew ? static_cast<uint32>(wcslen(pszNew)) : 0;
			if (nOldLength <= nLength && !(nNewLength && nOldLength == nNewLength && !wcscmp(pszOld, pszNew))) {
				// Replace
				uint32 nReplaced;
				SetStringBuffer(m_pStringBuffer->Replace(pszOld, nOldLength, pszNew ? pszNew : L"", nNewLength, nReplaced));

				// Return the number of replaced substrings
				return nReplaced;
			}
		}
	}

	// Nothing to do :)
	return 0;
}

/**
*  @brief
*    Sets a character at the given index
*/
bool String::SetCharacter(uint32 nIndex, char nCharacter)
{
	// Is this string empty?
	if (m_pStringBuffer) {
		// Check if the index is valid
		if (nIndex < GetLength()) {
			// Set the character
			SetStringBuffer(m_pStringBuffer->SetCharacter(nIndex, nCharacter));

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool String::SetCharacter(uint32 nIndex, wchar_t nCharacter)
{
	// Is this string empty?
	if (m_pStringBuffer) {
		// Check if the index is valid
		if (nIndex < GetLength()) {
			// Set the character
			SetStringBuffer(m_pStringBuffer->SetCharacter(nIndex, nCharacter));

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

/**
*  @brief
*    Removes all whitespace (tabs and spaces) at the beginning of the string
*/
String &String::TrimLeading()
{
	// Is this string empty?
	if (m_pStringBuffer) {
		// Delete whitespace at the beginning of the string
		SetStringBuffer(m_pStringBuffer->TrimLeading());
	}

	// Done
	return *this;
}

/**
*  @brief
*    Removes all whitespace (tabs and spaces) at the end of the string
*/
String &String::TrimTrailing()
{
	// Is this string empty?
	if (m_pStringBuffer) {
		// Delete whitespace at the end of the string
		SetStringBuffer(m_pStringBuffer->TrimTrailing());
	}

	// Done
	return *this;
}

/**
*  @brief
*    Removes all whitespace (tabs and spaces) at the beginning and the end of the string
*/
String &String::Trim()
{
	// Is this string empty?
	if (m_pStringBuffer) {
		// Delete whitespace at the beginning of the string
		SetStringBuffer(m_pStringBuffer->TrimLeading());

		// Is this string now empty?
		if (m_pStringBuffer) {
			// Delete whitespace at the end of the string
			SetStringBuffer(m_pStringBuffer->TrimTrailing());
		}
	}

	// Done
	return *this;
}

/**
*  @brief
*    Removes line endings ("\r" or "\n") at the end of the string
*/
String &String::RemoveLineEndings()
{
	// Is this string empty?
	if (m_pStringBuffer) {
		// Remove line endings at the end of the string
		SetStringBuffer(m_pStringBuffer->RemoveLineEndings());
	}

	// Done
	return *this;
}


//[-------------------------------------------------------]
//[ Conversion functions                                  ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the character string as UTF8
*/
const char *String::GetUTF8() const
{
	return m_pStringBuffer ? m_pStringBuffer->GetUTF8()->m_pszString : "";
}

// Is valid tests
bool String::IsValidInteger() const
{
	uint32 nLength = GetLength();

	// Check length
	if (nLength) {
		const char *pszASCII = GetASCII();

		// Skip spaces and tabs
		while (nLength > 0 && *pszASCII == ' ' || *pszASCII == '\t') {
			pszASCII++;
			nLength--;
		}

		// Check length
		if (nLength) {
			// Skip sign
			if (*pszASCII == '-' || *pszASCII == '+') {
				pszASCII++;
				nLength--;
			}

			// Check length
			if (nLength) {
				// Digits
				while (nLength > 0 && isdigit(*pszASCII)) {
					// Next character
					pszASCII++;
					nLength--;
				}

				// Check length
				if (!nLength)
					return true; // Valid integer

				// Skip spaces and tabs
				while (nLength > 0 && *pszASCII == ' ' || *pszASCII == '\t') {
					pszASCII++;
					nLength--;
				}

				if (!nLength)
					return true; // Valid integer
			}
		}
	}

	// Not a valid integer
	return false;
}

bool String::IsValidFloat() const
{
	uint32 nLength = GetLength();

	// Check length
	if (nLength) {
		const char *pszASCII = GetASCII();

		// Skip spaces and tabs
		while (nLength > 0 && *pszASCII == ' ' || *pszASCII == '\t') {
			pszASCII++;
			nLength--;
		}

		// Check length
		if (nLength) {
			// Skip sign
			if (*pszASCII == '-' || *pszASCII == '+') {
				pszASCII++;
				nLength--;
			}

			// Check length
			if (nLength) {
				// Digits
				bool bGotDot = false;
				while (nLength > 0 && (isdigit(*pszASCII) || (!bGotDot && *pszASCII == '.'))) {
					if (*pszASCII == '.')
						bGotDot = true;

					// Next character
					pszASCII++;
					nLength--;
				}

				// Check length
				if (!nLength)
					return true; // Valid float

				// Exponent
				if (*pszASCII == 'e' || *pszASCII == 'E') {
					pszASCII++;
					nLength--;

					// Check length
					if (!nLength)
						return true; // Valid float

					// Skip sign
					if (*pszASCII == '-' || *pszASCII == '+') {
						pszASCII++;
						nLength--;
					}

					// Check length
					if (nLength) {
						// Digits
						while (nLength > 0 && isdigit(*pszASCII)) {
							// Next character
							pszASCII++;
							nLength--;
						}

						// Check length
						if (!nLength)
							return true; // Valid float

						// Skip spaces and tabs
						while (nLength > 0 && *pszASCII == ' ' || *pszASCII == '\t') {
							pszASCII++;
							nLength--;
						}

						// Check length
						if (!nLength)
							return true; // Valid float
					}
				}
			}
		}
	}

	// Not a valid float
	return false;
}

// Convert from string
bool String::GetBool() const
{
	if (GetFormat() == Unicode) {
		if (CompareNoCase(L"true"))
			return true;
		else if (CompareNoCase(L"false"))
			return false;
		else
			return (GetInt() != 0);
	} else {
		if (CompareNoCase("true"))
			return true;
		else if (CompareNoCase("false"))
			return false;
		else
			return (GetInt() != 0);
	}
}

char String::GetChar() const
{
	if (m_pStringBuffer) {
		switch (m_pStringBuffer->GetFormat()) {
			case ASCII:
				return static_cast<char>(atoi(static_cast<StringBufferASCII*>(m_pStringBuffer)->m_pszString));

			case Unicode:
				return static_cast<char>(_wtoi(static_cast<StringBufferUnicode*>(m_pStringBuffer)->m_pszString));
		}
	}

	// Error!
	return 0;
}

wchar_t String::GetWideChar() const
{
	if (m_pStringBuffer) {
		switch (m_pStringBuffer->GetFormat()) {
			case ASCII:
				return static_cast<wchar_t>(atoi(static_cast<StringBufferASCII*>(m_pStringBuffer)->m_pszString));

			case Unicode:
				return static_cast<wchar_t>(_wtoi(static_cast<StringBufferUnicode*>(m_pStringBuffer)->m_pszString));
		}
	}

	// Error!
	return 0;
}

int String::GetInt() const
{
	if (m_pStringBuffer) {
		switch (m_pStringBuffer->GetFormat()) {
			case ASCII:
				return atoi(static_cast<StringBufferASCII*>(m_pStringBuffer)->m_pszString);

			case Unicode:
				return _wtoi(static_cast<StringBufferUnicode*>(m_pStringBuffer)->m_pszString);
		}
	}

	// Error!
	return 0;
}

uint8 String::GetUInt8() const
{
	if (m_pStringBuffer) {
		switch (m_pStringBuffer->GetFormat()) {
			case ASCII:
				// We don't use "return atol(((StringBufferASCII*)m_pStringBuffer)->m_pszString);"
				// because "atol" seems to have a different behaviour under Linux and Windows (uint32 values from string...)
				return static_cast<uint8>(strtoul(static_cast<StringBufferASCII*>(m_pStringBuffer)->m_pszString, nullptr, 10));

			case Unicode:
				// We don't use "return _wtol(((StringBufferUnicode*)m_pStringBuffer)->m_pszString);"
				// because "_wtol" seems to have a different behaviour under Linux and Windows (uint32 values from string...)
				return static_cast<uint8>(wcstoul(static_cast<StringBufferUnicode*>(m_pStringBuffer)->m_pszString, nullptr, 10));
		}
	}

	// Error!
	return 0;
}

uint16 String::GetUInt16() const
{
	if (m_pStringBuffer) {
		switch (m_pStringBuffer->GetFormat()) {
			case ASCII:
				// We don't use "return atol(((StringBufferASCII*)m_pStringBuffer)->m_pszString);"
				// because "atol" seems to have a different behaviour under Linux and Windows (uint32 values from string...)
				return static_cast<uint16>(strtoul(static_cast<StringBufferASCII*>(m_pStringBuffer)->m_pszString, nullptr, 10));

			case Unicode:
				// We don't use "return _wtol(((StringBufferUnicode*)m_pStringBuffer)->m_pszString);"
				// because "_wtol" seems to have a different behaviour under Linux and Windows (uint32 values from string...)
				return static_cast<uint16>(wcstoul(static_cast<StringBufferUnicode*>(m_pStringBuffer)->m_pszString, nullptr, 10));
		}
	}

	// Error!
	return 0;
}

uint32 String::GetUInt32() const
{
	if (m_pStringBuffer) {
		switch (m_pStringBuffer->GetFormat()) {
			case ASCII:
				// We don't use "return atol(((StringBufferASCII*)m_pStringBuffer)->m_pszString);"
				// because "atol" seems to have a different behaviour under Linux and Windows (uint32 values from string...)
				return strtoul(static_cast<StringBufferASCII*>(m_pStringBuffer)->m_pszString, nullptr, 10);

			case Unicode:
				// We don't use "return _wtol(((StringBufferUnicode*)m_pStringBuffer)->m_pszString);"
				// because "_wtol" seems to have a different behaviour under Linux and Windows (uint32 values from string...)
				return wcstoul(static_cast<StringBufferUnicode*>(m_pStringBuffer)->m_pszString, nullptr, 10);
		}
	}

	// Error!
	return 0;
}

uint64 String::GetUInt64() const
{
	if (m_pStringBuffer) {
		switch (m_pStringBuffer->GetFormat()) {
			case ASCII:
				return _atoi64(static_cast<StringBufferASCII*>(m_pStringBuffer)->m_pszString);

			case Unicode:
				#ifdef LINUX
					return wcstoumax(static_cast<StringBufferUnicode*>(m_pStringBuffer)->m_pszString, nullptr, 10);
				#elif defined(WIN32)
					return _wtoi64(static_cast<StringBufferUnicode*>(m_pStringBuffer)->m_pszString);
				#endif
		}
	}

	// Error!
	return 0;
}

uint_ptr String::GetUIntPtr() const
{
	#ifdef X64_ARCHITECTURE
		return GetUInt64();
	#else
		return GetUInt32();
	#endif
}

long String::GetLong() const
{
	if (m_pStringBuffer) {
		switch (m_pStringBuffer->GetFormat()) {
			case ASCII:
				return atol(static_cast<StringBufferASCII*>(m_pStringBuffer)->m_pszString);

			case Unicode:
				return _wtol(static_cast<StringBufferUnicode*>(m_pStringBuffer)->m_pszString);
		}
	}

	// Error!
	return 0;
}

float String::GetFloat() const
{
	if (m_pStringBuffer) {
		// We REALLY need to set the locale to a known setting... else we may get floats like "1,123" instead of "1.123"!
		char *pSaveLocale = strdup(setlocale(LC_ALL, nullptr));	// Get the current set locale, we REALLY need to backup the locale because it "may" be changed by "setlocale"
		setlocale(LC_ALL, "C");

		float fReturnValue;
		switch (m_pStringBuffer->GetFormat()) {
			case ASCII:
				fReturnValue = static_cast<float>(atof(static_cast<StringBufferASCII*>(m_pStringBuffer)->m_pszString));
				break;

			case Unicode:
				fReturnValue = static_cast<float>(_wtof(static_cast<StringBufferUnicode*>(m_pStringBuffer)->m_pszString));
				break;

			default:
				fReturnValue = 0.0f;
				break;
		}

		// Be polite and restore the previously set locale
		setlocale(LC_ALL, pSaveLocale);
		free(pSaveLocale);	// ... and don't forget to free the memory of our locale backup...

		return fReturnValue;
	} else {
		// No string buffer => just return zero
		return 0.0f;
	}
}

double String::GetDouble() const
{
	if (m_pStringBuffer) {
		// We REALLY need to set the locale to a known setting... else we may get floats like "1,123" instead of "1.123"!
		char *pSaveLocale = strdup(setlocale(LC_ALL, nullptr));	// Get the current set locale, we REALLY need to backup the locale because it "may" be changed by "setlocale"
		setlocale(LC_ALL, "C");

		double fReturnValue;
		switch (m_pStringBuffer->GetFormat()) {
			case ASCII:
				fReturnValue = atof(static_cast<StringBufferASCII*>(m_pStringBuffer)->m_pszString);
				break;

			case Unicode:
				fReturnValue = _wtof(static_cast<StringBufferUnicode*>(m_pStringBuffer)->m_pszString);
				break;

			default:
				fReturnValue = 0.0;
				break;
		}

		// Be polite and restore the previously set locale
		setlocale(LC_ALL, pSaveLocale);
		free(pSaveLocale);	// ... and don't forget to free the memory of our locale backup...

		return fReturnValue;
	} else {
		// No string buffer => just return zero
		return 0.0;
	}
}

// Convert to string
String &String::operator =(bool bValue)
{
	// Set data
	*this = bValue ? '1' : '0';

	// Return a reference to this instance
	return *this;
}

String &String::operator =(char nValue)
{
	// Terminating zero?
	if (nValue == '\0')
		ReleaseStringBuffer();
	else {
		// Optimization: If we have our own unique string buffer instance in the required format we 'just'
		// cut it down to use a single character
		if (m_pStringBuffer && m_pStringBuffer->GetRefCount() == 1 && m_pStringBuffer->GetFormat() == ASCII) {
			// Just set a character
			static_cast<StringBufferASCII*>(m_pStringBuffer)->SetCharacter(nValue);
		} else {
			// Release old string buffer
			if (m_pStringBuffer)
				StringBuffer::Manager.ReleaseStringBuffer(*m_pStringBuffer);

			// Request an ASCII string buffer from the string buffer manager
			m_pStringBuffer = StringBuffer::Manager.GetStringBufferASCII(1);
			if (m_pStringBuffer) {
				m_pStringBuffer->AddReference();
				m_pStringBuffer->Append(&nValue, 1);
			}
		}
	}

	// Return a reference to this instance
	return *this;
}

String &String::operator =(wchar_t nValue)
{
	// Terminating zero?
	if (nValue == L'\0')
		ReleaseStringBuffer();
	else {
		// Optimization: If we have our own unique string buffer instance in the required format we 'just'
		// cut it down to use a single character
		if (m_pStringBuffer && m_pStringBuffer->GetRefCount() == 1 && m_pStringBuffer->GetFormat() == Unicode) {
			// Just set a character
			static_cast<StringBufferUnicode*>(m_pStringBuffer)->SetCharacter(nValue);
		} else {
			// Release old string buffer
			if (m_pStringBuffer)
				StringBuffer::Manager.ReleaseStringBuffer(*m_pStringBuffer);

			// Request an unicode string buffer from the string buffer manager
			m_pStringBuffer = StringBuffer::Manager.GetStringBufferUnicode(1);
			if (m_pStringBuffer) {
				m_pStringBuffer->AddReference();
				m_pStringBuffer->Append(&nValue, 1);
			}
		}
	}

	// Return a reference to this instance
	return *this;
}

String &String::operator =(int nValue)
{
	// Sadly, the useful "itoa" is a non-standard extension to the standard C
	#ifdef WIN32
		// Release old string buffer
		if (m_pStringBuffer)
			StringBuffer::Manager.ReleaseStringBuffer(*m_pStringBuffer);

		// Request an ASCII string buffer from the string buffer manager
		// -> According to the "itoa"-documentation, this buffer should be 33 bytes long
		m_pStringBuffer = StringBuffer::Manager.GetStringBufferASCII(33);
		if (m_pStringBuffer) {
			m_pStringBuffer->AddReference();

			// And there the magic happens, number -> string :D
			_itoa(nValue, static_cast<StringBufferASCII*>(m_pStringBuffer)->m_pszString, 10);

			// Hm, _itoa doesn't tell us how many characters were actually written...
			m_pStringBuffer->m_nLength = strlen(static_cast<StringBufferASCII*>(m_pStringBuffer)->m_pszString);
		}
	#else
		// [TODO] Check itoa under Linux
		// Use the "portable", but less efficient way
		*this = Format("%d", nValue);
	#endif

	// Return a reference to this instance
	return *this;
}

String &String::operator =(uint8 nValue)
{
	// Set data
	#ifdef WIN32
		*this = Format("%I32u", static_cast<uint32>(nValue));
	#else
		// [TODO] Is this working correctly on Linux?
		*this = Format("%u", static_cast<uint32>(nValue));
	#endif

	// Return a reference to this instance
	return *this;
}

String &String::operator =(uint16 nValue)
{
	// Set data
	#ifdef WIN32
		*this = Format("%I32u", static_cast<uint32>(nValue));
	#else
		// [TODO] Is this working correctly on Linux?
		*this = Format("%u", static_cast<uint32>(nValue));
	#endif

	// Return a reference to this instance
	return *this;
}

String &String::operator =(uint32 nValue)
{
	// Set data
	#ifdef WIN32
		*this = Format("%I32u", nValue);
	#else
		// [TODO] Is this working correctly on Linux?
		*this = Format("%u", nValue);
	#endif

	// Return a reference to this instance
	return *this;
}

String &String::operator =(uint64 nValue)
{
	// Set data
	#ifdef WIN32
		*this = Format("%I64u", nValue);
	#else
		// [TODO] Is this working correctly on Linux or do we need something like
		/*
		#include <inttypes.h>
		int64_t var;
		sprintf (buf, "%" PRId64, var);
		*/
		*this = Format("%llu", nValue);
	#endif

	// Return a reference to this instance
	return *this;
}

String &String::operator =(long lValue)
{
	// Set data
	*this = Format("%ld", lValue);

	// Return a reference to this instance
	return *this;
}

String &String::operator =(float fValue)
{
	// Set data
	*this = Format("%g", fValue);

	// Return a reference to this instance
	return *this;
}

String &String::operator =(double dValue)
{
	// Set data
	*this = Format("%g", dValue);

	// Return a reference to this instance
	return *this;
}

// Concatenation
String String::operator +(bool bValue) const
{
	if (m_pStringBuffer) {
		if (m_pStringBuffer->GetFormat() == Unicode) {
			// Compose new string
			String sResult = *this;
			sResult.SetStringBuffer(sResult.m_pStringBuffer->Append(bValue ? L"1" : L"0", 1));
			return sResult;
		} else {
			// Compose new string
			String sResult = *this;
			sResult.SetStringBuffer(sResult.m_pStringBuffer->Append(bValue ? "1" : "0", 1));
			return sResult;
		}
	} else {
		return bValue ? '1' : '0';
	}
}

String String::operator +(char nValue) const
{
	// Terminating zero?
	if (nValue == '\0')
		return *this; // Ingore this, please!

	// Check if the string is empty
	if (m_pStringBuffer) {
		// Compose new string
		String sResult = *this;
		sResult.SetStringBuffer(sResult.m_pStringBuffer->Append(&nValue, 1));
		return sResult;
	} else {
		// Set just this character
		return nValue;
	}
}

String String::operator +(wchar_t nValue) const
{
	// Terminating zero?
	if (nValue == L'\0')
		return *this; // Ingore this, please!

	// Check if the string is empty
	if (m_pStringBuffer) {
		// Compose new string
		String sResult = *this;
		sResult.SetStringBuffer(sResult.m_pStringBuffer->Append(&nValue, 1));
		return sResult;
	} else {
		// Set just this character
		return nValue;
	}
}

String String::operator +(int nValue) const
{
	return *this + String(nValue);
}

String String::operator +(uint8 nValue) const
{
	#ifdef WIN32
		return (GetFormat() == Unicode) ? *this + Format(L"%I32u", static_cast<uint32>(nValue)) : *this + Format("%I32u", static_cast<uint32>(nValue));
	#else
		// [TODO] Is this working correctly on Linux?
		return (GetFormat() == Unicode) ? *this + Format(L"%u", static_cast<uint32>(nValue)) : *this + Format("%u", static_cast<uint32>(nValue));
	#endif
}

String String::operator +(uint16 nValue) const
{
	#ifdef WIN32
		return (GetFormat() == Unicode) ? *this + Format(L"%I32u", static_cast<uint32>(nValue)) : *this + Format("%I32u", static_cast<uint32>(nValue));
	#else
		// [TODO] Is this working correctly on Linux?
		return (GetFormat() == Unicode) ? *this + Format(L"%u", static_cast<uint32>(nValue)) : *this + Format("%u", static_cast<uint32>(nValue));
	#endif
}

String String::operator +(uint32 nValue) const
{
	#ifdef WIN32
		return (GetFormat() == Unicode) ? *this + Format(L"%I32u", nValue) : *this + Format("%I32u", nValue);
	#else
		// [TODO] Is this working correctly on Linux?
		return (GetFormat() == Unicode) ? *this + Format(L"%u", nValue) : *this + Format("%u", nValue);
	#endif
}

String String::operator +(uint64 nValue) const
{
	// Set data
	#ifdef WIN32
		return (GetFormat() == Unicode) ? *this + Format(L"%I64u", nValue) : *this + Format("%I64u", nValue);
	#else
		// [TODO] Is this working correctly on Linux or do we need something like
		/*
		#include <inttypes.h>
		int64_t var;
		sprintf (buf, "%" PRId64, var);
		*/
		return (GetFormat() == Unicode) ? *this + Format(L"%llu", nValue) : *this + Format("%llu", nValue);
	#endif
}

String String::operator +(float fValue) const
{
	return (GetFormat() == Unicode) ? *this + Format(L"%g", fValue) : *this + Format("%g", fValue);
}

String String::operator +(double dValue) const
{
	return (GetFormat() == Unicode) ? *this + String::Format(L"%g", dValue) : *this + String::Format("%g", dValue);
}

String operator +(bool bValue, const String &sString)
{
	if (sString.GetLength()) {
		if (sString.GetFormat() == String::Unicode) {
			return (bValue ? L'1' : L'0') + sString;
		} else {
			return (bValue ? '1' : '0') + sString;
		}
	} else {
		return bValue ? '1' : '0';
	}
}

String operator +(char nValue, const String &sString)
{
	// Terminating zero?
	if (nValue == '\0')
		return sString; // Ingore this, please!

	// Check if the string is empty
	if (sString.m_pStringBuffer)
		return String(nValue) + sString;	// Compose new string
	else
		return nValue;						// Set just this character
}

String operator +(wchar_t nValue, const String &sString)
{
	// Terminating zero?
	if (nValue == L'\0')
		return sString; // Ingore this, please!

	// Check if the string is empty
	if (sString.m_pStringBuffer)
		return String(nValue) + sString;	// Compose new string
	else
		return nValue;						// Set just this character
}

String operator +(int nValue, const String &sString)
{
	return (sString.GetFormat() == String::Unicode) ? String::Format(L"%d", nValue) + sString : String::Format("%d", nValue) + sString;
}

String operator +(uint8 nValue, const String &sString)
{
	#ifdef WIN32
		return (sString.GetFormat() == String::Unicode) ? String::Format(L"%I32u", static_cast<uint32>(nValue)) + sString : String::Format("%I32u", static_cast<uint32>(nValue)) + sString;
	#else
		// [TODO] Is this working correctly on Linux?
		return (sString.GetFormat() == String::Unicode) ? String::Format(L"%u", static_cast<uint32>(nValue)) + sString : String::Format("%u", static_cast<uint32>(nValue)) + sString;
	#endif
}

String operator +(uint16 nValue, const String &sString)
{
	#ifdef WIN32
		return (sString.GetFormat() == String::Unicode) ? String::Format(L"%I32u", static_cast<uint32>(nValue)) + sString : String::Format("%I32u", static_cast<uint32>(nValue)) + sString;
	#else
		// [TODO] Is this working correctly on Linux?
		return (sString.GetFormat() == String::Unicode) ? String::Format(L"%u", static_cast<uint32>(nValue)) + sString : String::Format("%u", static_cast<uint32>(nValue)) + sString;
	#endif
}

String operator +(uint32 nValue, const String &sString)
{
	#ifdef WIN32
		return (sString.GetFormat() == String::Unicode) ? String::Format(L"%I32u", nValue) + sString : String::Format("%I32u", nValue) + sString;
	#else
		// [TODO] Is this working correctly on Linux?
		return (sString.GetFormat() == String::Unicode) ? String::Format(L"%u", nValue) + sString : String::Format("%u", nValue) + sString;
	#endif
}

String operator +(uint64 nValue, const String &sString)
{
	#ifdef WIN32
		return (sString.GetFormat() == String::Unicode) ? String::Format(L"%I64u", nValue) + sString : String::Format("%I64u", nValue) + sString;
	#else
		// [TODO] Is this working correctly on Linux or do we need something like
		/*
		#include <inttypes.h>
		int64_t var;
		sprintf (buf, "%" PRId64, var);
		*/
		return (sString.GetFormat() == String::Unicode) ? String::Format(L"%llu", nValue) + sString : String::Format("%llu", nValue) + sString;
	#endif
}

String operator +(float fValue, const String &sString)
{
	return (sString.GetFormat() == String::Unicode) ? String::Format(L"%g", fValue) + sString : String::Format("%g", fValue) + sString;
}

String operator +(double dValue, const String &sString)
{
	return (sString.GetFormat() == String::Unicode) ? String::Format(L"%g", dValue) + sString : String::Format("%g", dValue) + sString;
}

String &String::operator +=(bool bValue)
{
	// Check if the string is empty
	if (m_pStringBuffer) {
		// Compose new string
		if (GetFormat() == Unicode)
			SetStringBuffer(m_pStringBuffer->Append(bValue ? L"1" : L"0", 1));
		else
			SetStringBuffer(m_pStringBuffer->Append(bValue ?  "1" :  "0", 1));

	// No string to insert into, create new string
	} else {
		// Request an ASCII string buffer from the string buffer manager
		m_pStringBuffer = StringBuffer::Manager.GetStringBufferASCII(1);
		if (m_pStringBuffer) {
			m_pStringBuffer->AddReference();
			m_pStringBuffer->Append(bValue ? "1" : "0", 1);
		}
	}

	// Done
	return *this;
}

String &String::operator +=(char nValue)
{
	// Terminating zero? (if so, ingore this, please!)
	if (nValue != '\0') {
		// Check if the string is empty
		if (m_pStringBuffer) {
			// Compose new string
			SetStringBuffer(m_pStringBuffer->Append(&nValue, 1));

		// No string to insert into, create new string
		} else {
			// Request an ASCII string buffer from the string buffer manager
			m_pStringBuffer = StringBuffer::Manager.GetStringBufferASCII(1);
			if (m_pStringBuffer) {
				m_pStringBuffer->AddReference();
				m_pStringBuffer->Append(&nValue, 1);
			}
		}
	}

	// Done
	return *this;
}

String &String::operator +=(wchar_t nValue)
{
	// Terminating zero? (if so, ingore this, please!)
	if (nValue != L'\0') {
		// Check if the string is empty
		if (m_pStringBuffer) {
			// Compose new string
			SetStringBuffer(m_pStringBuffer->Append(&nValue, 1));

		// No string to insert into, create new string
		} else {
			// Request an unicode string buffer from the string buffer manager
			m_pStringBuffer = StringBuffer::Manager.GetStringBufferUnicode(1);
			if (m_pStringBuffer) {
				m_pStringBuffer->AddReference();
				m_pStringBuffer->Append(&nValue, 1);
			}
		}
	}

	// Done
	return *this;
}

String &String::operator +=(int nValue)
{
	*this += String(nValue);
	return *this;
}

String &String::operator +=(uint8 nValue)
{
	#ifdef WIN32
		if (GetFormat() == Unicode)
			*this += Format(L"%I32u", static_cast<uint32>(nValue));
		else
			*this += Format("%I32u", static_cast<uint32>(nValue));
	#else
		// [TODO] Is this working correctly on Linux?
		if (GetFormat() == Unicode)
			*this += Format(L"%u", static_cast<uint32>(nValue));
		else
			*this += Format("%u", static_cast<uint32>(nValue));
	#endif
	return *this;
}

String &String::operator +=(uint16 nValue)
{
	#ifdef WIN32
		if (GetFormat() == Unicode)
			*this += Format(L"%I32u", static_cast<uint32>(nValue));
		else
			*this += Format("%I32u", static_cast<uint32>(nValue));
	#else
		// [TODO] Is this working correctly on Linux?
		if (GetFormat() == Unicode)
			*this += Format(L"%u", static_cast<uint32>(nValue));
		else
			*this += Format("%u", static_cast<uint32>(nValue));
	#endif
	return *this;
}

String &String::operator +=(uint32 nValue)
{
	#ifdef WIN32
		if (GetFormat() == Unicode)
			*this += Format(L"%I32u", nValue);
		else
			*this += Format("%I32u", nValue);
	#else
		// [TODO] Is this working correctly on Linux?
		if (GetFormat() == Unicode)
			*this += Format(L"%u", nValue);
		else
			*this += Format("%u", nValue);
	#endif
	return *this;
}

String &String::operator +=(uint64 nValue)
{
	// Set data
	#ifdef WIN32
		if (GetFormat() == Unicode)
			*this += Format(L"%I64u", nValue);
		else
			*this += Format("%I64u", nValue);
	#else
		// [TODO] Is this working correctly on Linux or do we need something like
		/*
		#include <inttypes.h>
		int64_t var;
		sprintf (buf, "%" PRId64, var);
		*/
		if (GetFormat() == Unicode)
			*this += Format(L"%llu", nValue);
		else
			*this += Format("%llu", nValue);
	#endif
	return *this;
}

String &String::operator +=(float fValue)
{
	if (GetFormat() == Unicode)
		*this += Format(L"%g", fValue);
	else
		*this += Format("%g", fValue);
	return *this;
}

String &String::operator +=(double dValue)
{
	if (GetFormat() == Unicode)
		*this += Format(L"%g", dValue);
	else
		*this += Format("%g", dValue);
	return *this;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Use a new string buffer
*/
void String::SetStringBuffer(StringBuffer *pStringBuffer)
{
	// Is this already the current used string buffer?
	if (m_pStringBuffer != pStringBuffer) {
		// Release old string buffer
		if (m_pStringBuffer)
			StringBuffer::Manager.ReleaseStringBuffer(*m_pStringBuffer);;

		// Set the a new string buffer
		m_pStringBuffer = pStringBuffer;
		if (m_pStringBuffer)
			m_pStringBuffer->AddReference();
	}
}

/**
*  @brief
*    Release string buffer
*/
void String::ReleaseStringBuffer()
{
	// Check string buffer
	if (m_pStringBuffer) {
		StringBuffer::Manager.ReleaseStringBuffer(*m_pStringBuffer);;
		m_pStringBuffer = nullptr;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP

