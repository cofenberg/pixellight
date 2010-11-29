/*********************************************************\
 *  File: XmlBase.cpp                                    *
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
#include <ctype.h>
#include <string.h>
#include "PLGeneral/Xml/XmlParsingData.h"
#include "PLGeneral/Xml/XmlBase.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const int XmlBase::utf8ByteTable[256] =
{
	//	0	1	2	3	4	5	6	7	8	9	a	b	c	d	e	f
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x00
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x10
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x20
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x30
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x40
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x50
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x60
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x70	End of ASCII range
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x80 0x80 to 0xc1 invalid
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x90 
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0xa0 
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0xb0 
		1,	1,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	// 0xc0 0xc2 to 0xdf 2 byte
		2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	// 0xd0
		3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	// 0xe0 0xe0 to 0xef 3 byte
		4,	4,	4,	4,	4,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1	// 0xf0 0xf0 to 0xf4 4 byte, 0xf5 and higher invalid
};


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
// Note tha "PutString" hardcodes the same list. This
// is less flexible than it appears. Changing the entries
// or order will break putstring.
XmlBase::Entity XmlBase::sEntity[NumOfEntities] =
{
	{ "&amp;",  '&' },
	{ "&lt;",   '<' },
	{ "&gt;",   '>' },
	{ "&quot;", '\"' },
	{ "&apos;", '\'' }
};
bool XmlBase::bCondenseWhiteSpace = true;


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Return the current white space setting
*/
bool XmlBase::IsWhiteSpaceCondensed()
{
	return bCondenseWhiteSpace;
}

/**
*  @brief
*    Set white space handling
*/
void XmlBase::SetCondenseWhiteSpace(bool bCondense)
{
	bCondenseWhiteSpace = bCondense;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
XmlBase::~XmlBase()
{
}

/**
*  @brief
*    Return the row position, in the original source file, of this node or attribute
*/
int XmlBase::GetRow() const
{
	return m_cCursor.nRow + 1;
}

/**
*  @brief
*    Return the column position, in the original source file, of this node or attribute
*/
int XmlBase::GetColumn() const
{
	return m_cCursor.nColumn + 1;
}

/**
*  @brief
*    Returns the user data
*/
void *XmlBase::GetUserData() const
{
	return m_pUserData;
}

/**
*  @brief
*    Sets the user data
*/
void XmlBase::SetUserData(void *pUser)
{
	m_pUserData = pUser;
}


//[-------------------------------------------------------]
//[ Protected static functions                            ]
//[-------------------------------------------------------]
const char *XmlBase::SkipWhiteSpace(const char *pszData, EEncoding nEncoding)
{
	if (!pszData || !*pszData)
		return NULL;	// Error!
	if (nEncoding == EncodingUTF8) {
		while (*pszData) {
			const unsigned char *pU = (const unsigned char*)pszData;

			// Skip the stupid Microsoft UTF-8 Byte order marks
			if (	*(pU+0)==UTF_LEAD_0
				 && *(pU+1)==UTF_LEAD_1 
				 && *(pU+2)==UTF_LEAD_2 ) {
				pszData += 3;
				continue;
			} else if( *(pU+0)==UTF_LEAD_0
					&& *(pU+1)==0xbfU
					&& *(pU+2)==0xbeU ) {
				pszData += 3;
				continue;
			} else if( *(pU+0)==UTF_LEAD_0
					&& *(pU+1)==0xbfU
					&& *(pU+2)==0xbfU ) {
				pszData += 3;
				continue;
			}

			if (IsWhiteSpace(*pszData))		// Still using old rules for white space
				++pszData;
			else
				break;
		}
	} else {
		while (*pszData && IsWhiteSpace(*pszData))
			++pszData;
	}

	// Done
	return pszData;
}

bool XmlBase::IsWhiteSpace(char c)
{
	return (isspace((unsigned char)c) || c == '\n' || c == '\r');
}

bool XmlBase::IsWhiteSpace(int c)
{
	return (c < 256) ? IsWhiteSpace((char)c) : false;	// Again, only truly correct for English/Latin... but usually works
}

/**
*  @brief
*    Reads an XML name into the string provided
*/
const char *XmlBase::ReadName(const char *pszData, String &sName, EEncoding nEncoding)
{
	sName = "";

	// Names start with letters or underscores.
	// Of course, in unicode, the parser has no idea what a letter *is*. The algorithm is generous.
	//
	// After that, they can be letters, underscores, numbers,
	// hyphens, or colons. (Colons are valid ony for namespaces,
	// but the parser can't tell namespaces from names.)
	if (pszData && *pszData && (IsAlpha((unsigned char)*pszData) || *pszData == '_')) {
		const char *pszStart = pszData;
		while (pszData && *pszData && (IsAlphaNum((unsigned char)*pszData) || *pszData == '_' || *pszData == '-' || *pszData == '.' || *pszData == ':'))
			++pszData;
		if (pszData-pszStart > 0)
			sName.Copy(pszStart, pszData-pszStart);
		return pszData;
	}
	return NULL;
}

/**
*  @brief
*    Reads text
*/
const char *XmlBase::ReadText(const char *pszData, String &sText, bool bTrimWhiteSpace, const char *pszEndTag, bool bCaseInsensitive, EEncoding nEncoding)
{
	sText = "";
	if (    !bTrimWhiteSpace			// Certain tags always keep whitespace
		 || !bCondenseWhiteSpace ) {	// If true, whitespace is always kept
		// Keep all the white space
		while (pszData && *pszData && !StringEqual(pszData, pszEndTag, bCaseInsensitive, nEncoding)) {
			int nLength;
			char szCharacters[4] = { 0, 0, 0, 0 };
			pszData = GetChar(pszData, szCharacters, nLength, nEncoding);
			if (nLength == 1)
				sText += szCharacters[0];	// More efficient because we already know that we just add a single character
			else
				sText.Insert(szCharacters, sText.GetLength(), nLength);
		}
	} else {
		bool bWhitespace = false;

		// Remove leading white space
		pszData = SkipWhiteSpace( pszData, nEncoding );
		while (pszData && *pszData && !StringEqual( pszData, pszEndTag, bCaseInsensitive, nEncoding)) {
			if (*pszData == '\r' || *pszData == '\n') {
				bWhitespace = true;
				++pszData;
			} else if (IsWhiteSpace(*pszData)) {
				bWhitespace = true;
				++pszData;
			} else {
				// If we've found whitespace, add it before the new character. Any whitespace just becomes a space.
				if (bWhitespace) {
					sText += ' ';
					bWhitespace = false;
				}
				int nLength;
				char szCharacters[4] = { 0, 0, 0, 0 };
				pszData = GetChar(pszData, szCharacters, nLength, nEncoding);
				if (nLength == 1)
					sText += szCharacters[0];	// More efficient because we already know that we just add a single character
				else
					sText.Insert(szCharacters, sText.GetLength(), nLength);
			}
		}
	}
	if (pszData && *pszData)
		pszData += strlen(pszEndTag);
	return pszData;
}

const char *XmlBase::GetEntity(const char *pszData, char *pszValue, int &nLength, EEncoding nEncoding)
{
	// Presume an entity, and pull it out
	nLength = 0;

	if (*(pszData+1) && *(pszData+1) == '#' && *(pszData+2)) {
		unsigned long ucs = 0;
		ptrdiff_t pDeltaAddress = 0;

		if (*(pszData+2) == 'x') {
			// Hexadecimal
			if (!*(pszData+3))
				return NULL;

			const char *pszCurrentData = pszData + 3;
			pszCurrentData = strchr(pszCurrentData, ';');
			if (!pszCurrentData || !*pszCurrentData)
				return NULL;

			pDeltaAddress = pszCurrentData - pszData;
			--pszCurrentData;

			unsigned int nMult = 1;
			while (*pszCurrentData != 'x') {
				if (*pszCurrentData >= '0' && *pszCurrentData <= '9')
					ucs += nMult * (*pszCurrentData - '0');
				else if (*pszCurrentData >= 'a' && *pszCurrentData <= 'f')
					ucs += nMult * (*pszCurrentData - 'a' + 10);
				else if (*pszCurrentData >= 'A' && *pszCurrentData <= 'F')
					ucs += nMult * (*pszCurrentData - 'A' + 10);
				else
					return NULL;
				nMult *= 16;
				--pszCurrentData;
			}
		} else {
			// Decimal
			if (!*(pszData+2))
				return NULL;

			const char *pszCurrentData = pszData + 2;
			pszCurrentData = strchr(pszCurrentData, ';');
			if (!pszCurrentData || !*pszCurrentData)
				return NULL;

			pDeltaAddress = pszCurrentData - pszData;
			--pszCurrentData;

			unsigned int nMult = 1;
			while (*pszCurrentData != '#') {
				if (*pszCurrentData >= '0' && *pszCurrentData <= '9')
					ucs += nMult * (*pszCurrentData - '0');
				else
					return NULL;
				nMult *= 10;
				--pszCurrentData;
			}
		}
		if (nEncoding == EncodingUTF8) {
			// Convert the UCS to UTF-8
			ConvertUTF32ToUTF8(ucs, pszValue, nLength);
		} else {
			*pszValue = (char)ucs;
			nLength = 1;
		}
		return pszData + pDeltaAddress + 1;
	}

	// Now try to match it
	for (int i=0; i<NumOfEntities; ++i) {
		if (sEntity[i].sString.Compare(pszData, 0, sEntity[i].sString.GetLength())) {
			*pszValue = sEntity[i].nCharacter;
			nLength = 1;
			return (pszData + sEntity[i].sString.GetLength());
		}
	}

	// So it wasn't an entity, its unrecognized, or something like that
	*pszValue = *pszData;	// Don't put back the last one, since we return it!
	//nLength = 1;	// Leave unrecognized entities - this doesn't really work.
					// Just writes strange XML.
	return pszData+1;
}

const char *XmlBase::GetChar(const char *pszData, char *pszValue, int &nLength, EEncoding nEncoding)
{
	nLength = (nEncoding == EncodingUTF8) ? utf8ByteTable[*((const unsigned char*)pszData)] : 1;
	if (nLength == 1) {
		if (*pszData == '&')
			return GetEntity(pszData, pszValue, nLength, nEncoding);
		*pszValue = *pszData;
		return pszData + 1;
	} else if (nLength) {
		for (int i=0; pszData[i] && i<nLength; ++i)
			pszValue[i] = pszData[i];
		return pszData + nLength;
	} else {
		// Not valid text
		return NULL;
	}
}

bool XmlBase::StringEqual(const char *pszData, const char *pszTag, bool bIgnoreCase, EEncoding nEncoding)
{
	if (!pszData || !*pszData)
		return false;
	const char *pszCurrentData = pszData;
	if (bIgnoreCase) {
		while (*pszCurrentData && *pszTag && ToLower(*pszCurrentData, nEncoding) == ToLower(*pszTag, nEncoding)) {
			++pszCurrentData;
			++pszTag;
		}

		if (*pszTag == 0)
			return true;
	} else {
		while (*pszCurrentData && *pszTag && *pszCurrentData == *pszTag) {
			++pszCurrentData;
			++pszTag;
		}

		if (*pszTag == 0)	// Have we found the end of the tag, and everything equal?
			return true;
	}
	return false;
}

int XmlBase::IsAlpha(unsigned char nByte)
{
	// This will only work for low-ascii, everything else is assumed to be a valid
	// letter. I'm not sure this is the best approach, but it is quite tricky trying
	// to figure out alhabetical vs. not across encoding. So take a very conservative approach.
	return (nByte < 127) ? isalpha(nByte) : 1;	// What else to do? The unicode set is huge... get the english ones right.
}

int XmlBase::IsAlphaNum(unsigned char nByte)
{
	// This will only work for low-ascii, everything else is assumed to be a valid
	// letter. I'm not sure this is the best approach, but it is quite tricky trying
	// to figure out alhabetical vs. not across nEncoding. So take a very conservative approach.
	return (nByte < 127) ? isalnum(nByte) : 1;	// What else to do? The unicode set is huge... get the english ones right.
}

int XmlBase::ToLower(int nValue, EEncoding nEncoding)
{
	if (nEncoding == EncodingUTF8)
		return (nValue < 128) ? tolower(nValue) : nValue;
	else
		return tolower(nValue);
}

void XmlBase::ConvertUTF32ToUTF8(unsigned long nInput, char *pszOutput, int &nLength)
{
	const unsigned long BYTE_MASK = 0xBF;
	const unsigned long BYTE_MARK = 0x80;
	const unsigned long FIRST_BYTE_MARK[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

	if (nInput < 0x80)
		nLength = 1;
	else if (nInput < 0x800)
		nLength = 2;
	else if (nInput < 0x10000)
		nLength = 3;
	else if (nInput < 0x200000)
		nLength = 4;
	else {
		// This code won't covert this correctly anyway
		nLength = 0;
		return;
	}

	pszOutput += nLength;

	// Scary scary fall throughs
	switch (nLength) {
		case 4:
			--pszOutput;
			*pszOutput = (char)((nInput | BYTE_MARK) & BYTE_MASK);
			nInput >>= 6;

		case 3:
			--pszOutput;
			*pszOutput = (char)((nInput | BYTE_MARK) & BYTE_MASK);
			nInput >>= 6;

		case 2:
			--pszOutput;
			*pszOutput = (char)((nInput | BYTE_MARK) & BYTE_MASK);
			nInput >>= 6;

		case 1:
			--pszOutput;
			*pszOutput = (char)(nInput | FIRST_BYTE_MARK[nLength]);
	}
}

void XmlBase::EncodeString(const String &sInString, String &sOutString)
{
	uint32 i = 0;
	while (i<(int)sInString.GetLength()) {
		unsigned char c = (unsigned char)sInString[i];

		if (c == '&'  && (int)i < ((int)sInString.GetLength() - 2) && sInString[i+1] == '#' && sInString[i+2] == 'x') {
			// Hexadecimal character reference.
			// Pass through unchanged.
			// &#xA9;	-- copyright symbol, for example.
			//
			// The -1 keeps an overflow from happening if there is no ';'.
			// There are actually 2 ways to exit this loop -
			// while fails (error case) and break (semicolon found).
			// However, there is no mechanism (currently) for
			// this function to return an error.
			while ((int)i<(int)sInString.GetLength()-1) {
				sOutString += sInString[i];
				++i;
				if (sInString[i] == ';')
					break;
			}
		} else if (c == '&') {
			sOutString += sEntity[0].sString;
			++i;
		} else if (c == '<') {
			sOutString += sEntity[1].sString;
			++i;
		} else if (c == '>') {
			sOutString += sEntity[2].sString;
			++i;
		} else if (c == '\"') {
			sOutString += sEntity[3].sString;
			++i;
		} else if (c == '\'') {
			sOutString += sEntity[4].sString;
			++i;
		} else if (c < 32) {
			// Easy pass at non-alpha/numeric/symbol
			// Below 32 is symbolic
			sOutString += String::Format("&#x%02X;", (unsigned)(c & 0xff));
			++i;
		} else {
			sOutString += (char)c;
			++i;
		}
	}
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
XmlBase::XmlBase() :
	m_pUserData(NULL)
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
XmlBase::XmlBase(const XmlBase &cSource) :
	m_pUserData(NULL)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
XmlBase &XmlBase::operator =(const XmlBase &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
