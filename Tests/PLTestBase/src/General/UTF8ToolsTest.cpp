/*********************************************************\
 *  File: UTF8ToolsTest.cpp                              *
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
#ifdef LINUX
	#include <wchar.h>
	#include <PLCore/PLCoreLinuxWrapper.h>
#endif
#include <PLCore/String/UTF8Tools.h>
#include "PLTestBase/General/UTF8ToolsTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *UTF8ToolsTest::GetName() const
{
	return "UTF8Tools";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void UTF8ToolsTest::Test()
{
	// Some test data
	const char    *pszASCIIString1    = "\\u65e5\\u672c\\u8a9e";
	const wchar_t *pszWCharString1    = L"\u65e5\u672c\u8a9e";
	const char    *pszUTF8String1     = "日本語";
	wchar_t        nWideCharacter1    = 26085; // 3 characters => 日
	wchar_t        nWideCharacter2    = 26412; // 3 characters => 本
	wchar_t        nWideCharacter3    = 35486; // 3 characters => 語
	const char    *pszASCIICharacter1 = "\\u65e5";
	const char    *pszUTF8Character1  = "日";

	// Variables
	wchar_t szWCharTemp[256];
	const char *pszUTF8Temp;
	char szASCIITemp[256];
	char szUTF8Temp[256];
	bool bResult = true;
	wchar_t nWCharTemp;
	uint32 nTemp;

	// IsOctalDigit(char nCharacter)
	StartTask("IsOctalDigit(char nCharacter)");
	if (!UTF8Tools::IsOctalDigit('0') || !UTF8Tools::IsOctalDigit('2') || !UTF8Tools::IsOctalDigit('7')) bResult = false;
	if ( UTF8Tools::IsOctalDigit('-') ||  UTF8Tools::IsOctalDigit('F') ||  UTF8Tools::IsOctalDigit('8')) bResult = false;
	EndTask(bResult);

	// IsHexDigit(char nCharacter)
	StartTask("IsHexDigit(char nCharacter)");
	if (!UTF8Tools::IsHexDigit('0') || !UTF8Tools::IsHexDigit('2') || !UTF8Tools::IsHexDigit('9')) bResult = false;
	if (!UTF8Tools::IsHexDigit('A') || !UTF8Tools::IsHexDigit('C') || !UTF8Tools::IsHexDigit('F')) bResult = false;
	if (!UTF8Tools::IsHexDigit('a') || !UTF8Tools::IsHexDigit('c') || !UTF8Tools::IsHexDigit('f')) bResult = false;
	if ( UTF8Tools::IsHexDigit('-') ||  UTF8Tools::IsHexDigit('G') ||  UTF8Tools::IsHexDigit('g')) bResult = false;
	EndTask(bResult);

	// IsSequenceStart(char nCharacter)
	StartTask("IsSequenceStart(char nCharacter)");
	if (!UTF8Tools::IsSequenceStart('0') || !UTF8Tools::IsSequenceStart('A') || !UTF8Tools::IsSequenceStart('+')) bResult = false;
	EndTask(bResult);

	// GetNumOfCharacterBytes(char nCharacter)
	StartTask("GetNumOfCharacterBytes(char nCharacter)");
	if (UTF8Tools::GetNumOfCharacterBytes('0') != 1) bResult = false;
	if (UTF8Tools::GetNumOfCharacterBytes('A') != 1) bResult = false;
	if (UTF8Tools::GetNumOfCharacterBytes('+') != 1) bResult = false;
	if (UTF8Tools::GetNumOfCharacterBytes(*pszUTF8Character1) != 3) bResult = false;
	EndTask(bResult);

	// GetNumOfCharacterBytes(wchar_t nWideCharacter)
	StartTask("GetNumOfCharacterBytes(wchar_t nWideCharacter");
	if (UTF8Tools::GetNumOfCharacterBytes(L'0') != 1) bResult = false;
	if (UTF8Tools::GetNumOfCharacterBytes(L'A') != 1) bResult = false;
	if (UTF8Tools::GetNumOfCharacterBytes(L'+') != 1) bResult = false;
	if (UTF8Tools::GetNumOfCharacterBytes(nWideCharacter1) != 3) bResult = false;
	EndTask(bResult);

	// GetWideCharacter(const char nCharacter[])
	StartTask("GetWideCharacter(const char nCharacter[])");
	if (UTF8Tools::GetWideCharacter("0") != '0') bResult = false;
	if (UTF8Tools::GetWideCharacter("A") != 'A') bResult = false;
	if (UTF8Tools::GetWideCharacter("+") != '+') bResult = false;
	if (UTF8Tools::GetWideCharacter(pszUTF8Character1) != nWideCharacter1) bResult = false;
	EndTask(bResult);

	// GetNextWideCharacter(const char **ppszString)
	StartTask("GetNextWideCharacter(const char **ppszString)");
	pszUTF8Temp = "0";
	if (UTF8Tools::GetNextWideCharacter(&pszUTF8Temp) != '0') bResult = false;
	pszUTF8Temp = "A";
	if (UTF8Tools::GetNextWideCharacter(&pszUTF8Temp) != 'A') bResult = false;
	pszUTF8Temp = "+";
	if (UTF8Tools::GetNextWideCharacter(&pszUTF8Temp) != '+') bResult = false;
	// Read first character
	pszUTF8Temp = pszUTF8String1;
	if (UTF8Tools::GetNextWideCharacter(&pszUTF8Temp) != nWideCharacter1 ||
		pszUTF8Temp != pszUTF8String1+3) bResult = false;
	// Read second character
	if (UTF8Tools::GetNextWideCharacter(&pszUTF8Temp) != nWideCharacter2 ||
		pszUTF8Temp != pszUTF8String1+6) bResult = false;
	// Read third character
	if (UTF8Tools::GetNextWideCharacter(&pszUTF8Temp) != nWideCharacter3 ||
		pszUTF8Temp != pszUTF8String1+9) bResult = false;
	// Read fourth and fifth character ;-)
	if (UTF8Tools::GetNextWideCharacter(&pszUTF8Temp) != 0 ||
		pszUTF8Temp != pszUTF8String1+9) bResult = false;
	if (UTF8Tools::GetNextWideCharacter(&pszUTF8Temp) != 0 ||
		pszUTF8Temp != pszUTF8String1+9) bResult = false;
	EndTask(bResult);

	// MoveToNextCharacter(const char **ppszString)
	StartTask("MoveToNextCharacter(const char **ppszString)");
	// Move to second character
	pszUTF8Temp = pszUTF8String1;
	if (UTF8Tools::MoveToNextCharacter(&pszUTF8Temp) != 3 ||
		pszUTF8Temp != pszUTF8String1+3) bResult = false;
	// Move to third character
	if (UTF8Tools::MoveToNextCharacter(&pszUTF8Temp) != 3 ||
		pszUTF8Temp != pszUTF8String1+6) bResult = false;
	// Move to fourth and fifth character ;-)
	if (UTF8Tools::MoveToNextCharacter(&pszUTF8Temp) != 3 ||
		pszUTF8Temp != pszUTF8String1+9) bResult = false;
	if (UTF8Tools::MoveToNextCharacter(&pszUTF8Temp) != 0 ||
		pszUTF8Temp != pszUTF8String1+9) bResult = false;
	EndTask(bResult);

	// MoveToPreviousCharacter(const char **ppszString)
	StartTask("MoveToPreviousCharacter(const char **ppszString)");
	// Move to third character
	pszUTF8Temp = pszUTF8String1+9;
	if (UTF8Tools::MoveToPreviousCharacter(&pszUTF8Temp) != 3 ||
		pszUTF8Temp != pszUTF8String1+6) bResult = false;
	// Move to second character
	if (UTF8Tools::MoveToPreviousCharacter(&pszUTF8Temp) != 3 ||
		pszUTF8Temp != pszUTF8String1+3) bResult = false;
	// Move to second first
	if (UTF8Tools::MoveToPreviousCharacter(&pszUTF8Temp) != 3 ||
		pszUTF8Temp != pszUTF8String1) bResult = false;
	EndTask(bResult);

	// CharacterIndexToByteOffset(const char szString[], uint32 nCharacterIndex)
	StartTask("CharacterIndexToByteOffset(const char szString[], uint32 nCharacterIndex)");
	bResult = true;
	if (UTF8Tools::CharacterIndexToByteOffset(pszUTF8String1, 0) != 0) bResult = false;
	if (UTF8Tools::CharacterIndexToByteOffset(pszUTF8String1, 1) != 3) bResult = false;
	if (UTF8Tools::CharacterIndexToByteOffset(pszUTF8String1, 2) != 6) bResult = false;
	if (UTF8Tools::CharacterIndexToByteOffset(pszUTF8String1, 3) != 9) bResult = false;
	EndTask(bResult);

	// ByteOffsetToCharacterIndex(const char szString[], uint32 nOffset)
	StartTask("ByteOffsetToCharacterIndex(const char szString[], uint32 nOffset)");
	bResult = true;
	if (UTF8Tools::ByteOffsetToCharacterIndex(pszUTF8String1, 0) != 0) bResult = false;
	if (UTF8Tools::ByteOffsetToCharacterIndex(pszUTF8String1, 3) != 1) bResult = false;
	if (UTF8Tools::ByteOffsetToCharacterIndex(pszUTF8String1, 6) != 2) bResult = false;
	if (UTF8Tools::ByteOffsetToCharacterIndex(pszUTF8String1, 8) != 3) bResult = false;
	EndTask(bResult);

	// GetNumOfStringBytes(const char szString[])
	StartTask("GetNumOfStringBytes(const char szString[])");
	bResult = true;
	if (UTF8Tools::GetNumOfStringBytes(pszUTF8String1) != strlen(pszUTF8String1)) bResult = false;
	EndTask(bResult);

	// GetNumOfCharacters(const char szString[])
	StartTask("GetNumOfCharacters(const char szString[])");
	bResult = true;
	if (UTF8Tools::GetNumOfCharacters(pszUTF8Character1) != 1) bResult = false;
	if (UTF8Tools::GetNumOfCharacters(pszUTF8String1) != 3) bResult = false;
	EndTask(bResult);

	// GetNumOfCharacters(const char szString[], uint32 nNumOfBytes)
	StartTask("GetNumOfCharacters(const char szString[], uint32 nNumOfBytes)");
	bResult = true;
	if (UTF8Tools::GetNumOfCharacters(pszUTF8Character1, 3) != 1) bResult = false;
	if (UTF8Tools::GetNumOfCharacters(pszUTF8Character1, 2) != 1) bResult = false;
	if (UTF8Tools::GetNumOfCharacters(pszUTF8String1, 9) != 3) bResult = false;
	if (UTF8Tools::GetNumOfCharacters(pszUTF8String1, 6) != 2) bResult = false;
	if (UTF8Tools::GetNumOfCharacters(pszUTF8String1, 5) != 2) bResult = false;
	EndTask(bResult);

	// GetNumOfCharactersAndBytes(const char szString[], uint32 &nNumOfBytes)
	StartTask("GetNumOfCharactersAndBytes(const char szString[], uint32 &nNumOfBytes)");
	bResult = true;
	if (UTF8Tools::GetNumOfCharactersAndBytes(pszUTF8Character1, nTemp) != 1 || nTemp != 3) bResult = false;
	if (UTF8Tools::GetNumOfCharactersAndBytes(pszUTF8String1, nTemp) != 3 || nTemp != 9) bResult = false;
	EndTask(bResult);

	// FindCharacter(const char szString[], wchar_t nWideCharacter, uint32 *pnCharacterIndex)
	StartTask("FindCharacter(const char szString[], wchar_t nWideCharacter, uint32 *pnCharacterIndex)");
	bResult = true;
	if (UTF8Tools::FindCharacter(pszUTF8String1, nWideCharacter1, &nTemp) != pszUTF8String1   || nTemp != 0) bResult = false;
	if (UTF8Tools::FindCharacter(pszUTF8String1, nWideCharacter2, &nTemp) != pszUTF8String1+3 || nTemp != 1) bResult = false;
	if (UTF8Tools::FindCharacter(pszUTF8String1, nWideCharacter3, &nTemp) != pszUTF8String1+6 || nTemp != 2) bResult = false;
	if (UTF8Tools::FindCharacter(pszUTF8String1, 55,			  &nTemp) != nullptr		  || nTemp != 0) bResult = false;
	EndTask(bResult);

	// FindCharacter(const char szString[], uint32 nNumOfBytes, wchar_t nWideCharacter, uint32 *pnCharacterIndex)
	StartTask("FindCharacter(const char szString[], uint32 nNumOfBytes, wchar_t nWideCharacter, uint32 *pnCharacterIndex)");
	bResult = true;
	if (UTF8Tools::FindCharacter(pszUTF8String1, static_cast<uint32>(strlen(pszUTF8String1)), nWideCharacter1, &nTemp) != pszUTF8String1   || nTemp != 0) bResult = false;
	if (UTF8Tools::FindCharacter(pszUTF8String1, static_cast<uint32>(strlen(pszUTF8String1)), nWideCharacter2, &nTemp) != pszUTF8String1+3 || nTemp != 1) bResult = false;
	if (UTF8Tools::FindCharacter(pszUTF8String1, static_cast<uint32>(strlen(pszUTF8String1)), nWideCharacter3, &nTemp) != pszUTF8String1+6 || nTemp != 2) bResult = false;
	if (UTF8Tools::FindCharacter(pszUTF8String1, static_cast<uint32>(strlen(pszUTF8String1)), 55,			   &nTemp) != nullptr		   || nTemp != 0) bResult = false;
	if (UTF8Tools::FindCharacter(pszUTF8String1, 3,								 			  nWideCharacter2, &nTemp) != nullptr		   || nTemp != 0) bResult = false;
	EndTask(bResult);

	// FromWideCharacter(char szDestination[], wchar_t nWideCharacter)
	StartTask("FromWideCharacter(char szDestination[], wchar_t nWideCharacter)");
	bResult = true;
	if (UTF8Tools::FromWideCharacter(szUTF8Temp, nWideCharacter1) == 3) {
		// Is the result correct?
		if (strncmp(szUTF8Temp, pszUTF8String1, 3)) bResult = false;
	} else bResult = false;
	EndTask(bResult);

	// FromWideCharacterString(char *pszDestination, uint32 nNumOfBytes, wchar_t szSource[], uint32 nSourceLength)
	StartTask("FromWideCharacterString(char *pszDestination, uint32 nNumOfBytes, wchar_t szSource[], uint32 nSourceLength)");
	bResult = true;
	if (UTF8Tools::FromWideCharacterString(nullptr, 0, pszWCharString1, 0) != 9) bResult = false;
	if (UTF8Tools::FromWideCharacterString(szUTF8Temp, 256, pszWCharString1, 0) == 9) {
		// Is the result correct?
		if (strncmp(szUTF8Temp, pszUTF8String1, 3)) bResult = false;
	} else bResult = false;
	EndTask(bResult);

	// ToWideCharacterString(wchar_t szDestination[], uint32 nLength, char szSource[], int nSourceNumOfBytes)
	StartTask("ToWideCharacterString(wchar_t szDestination[], uint32 nLength, char szSource[], int nSourceNumOfBytes)");
	bResult = true;
	if (UTF8Tools::ToWideCharacterString(szWCharTemp, 256, pszUTF8String1, 0) == 3) {
		// Is the result correct?
		if (wcsncmp(szWCharTemp, pszWCharString1, 3)) bResult = false;
	} else bResult = false;
	EndTask(bResult);

	// EscapeWideCharacter(char *pszDestination, uint32 nNumOfBytes, wchar_t nWideCharacter)
	StartTask("EscapeWideCharacter(char *pszDestination, uint32 nNumOfBytes, wchar_t nWideCharacter)");
	bResult = true;
	if (UTF8Tools::EscapeWideCharacter(nullptr, 0, nWideCharacter1) != strlen(pszASCIICharacter1)) bResult = false;
	if (UTF8Tools::EscapeWideCharacter(szASCIITemp, 256, nWideCharacter1) == strlen(pszASCIICharacter1)) {
		// Is the result correct? (not case sensitive...)
		if (_stricmp(szASCIITemp, pszASCIICharacter1))
			bResult = false;
	} else bResult = false;
	EndTask(bResult);

	// Escape(char *pszDestination, uint32 nNumOfBytes, const char szSource[], bool bEscapeQuotes)
	StartTask("Escape(char *pszDestination, uint32 nNumOfBytes, const char szSource[], bool bEscapeQuotes)");
	bResult = true;
	if (UTF8Tools::Escape(nullptr, 0, pszUTF8String1, true) != strlen(pszASCIIString1)) bResult = false;
	if (UTF8Tools::Escape(szASCIITemp, 256, pszUTF8String1, true) == strlen(pszASCIIString1)) {
		// Is the result correct? (not case sensitive...)
		if (_stricmp(szASCIITemp, pszASCIIString1)) bResult = false;
	} else bResult = false;
	EndTask(bResult);

	// ReadEscapeSequence(wchar_t nDestination, const char szSource[])
	StartTask("ReadEscapeSequence(wchar_t nDestination, const char szSource[])");
	bResult = true;
	if (UTF8Tools::ReadEscapeSequence(nWCharTemp, pszASCIICharacter1+1) != strlen(pszASCIICharacter1)-1 ||
		nWCharTemp != nWideCharacter1) bResult = false;
	EndTask(bResult);

	// Unescape(char *pszDestination, uint32 nNumOfBytes, const char szSource[])
	StartTask("Unescape(char *pszDestination, uint32 nNumOfBytes, const char szSource[])");
	bResult = true;
	if (UTF8Tools::Unescape(nullptr, 0, pszASCIIString1) != strlen(pszUTF8String1)) bResult = false;
	if (UTF8Tools::Unescape(szUTF8Temp, 256, pszASCIIString1) == strlen(pszUTF8String1)) {
		// Is the result correct?
		if (strcmp(szUTF8Temp, pszUTF8String1)) bResult = false;
	} else bResult = false;
	EndTask(bResult);

	// Compare(const char szFirst[], const char szSecond[], uint32 nCount)
	StartTask("Compare(const char szFirst[], const char szSecond[], uint32 nCount)");
	bResult = true;
	if (UTF8Tools::Compare("",			"")		  !=  0)	bResult = false;
	if (UTF8Tools::Compare("",			"a")	  >  -1)	bResult = false;
	if (UTF8Tools::Compare("a",			"")		  <   1)	bResult = false;
	if (UTF8Tools::Compare("a",			"b")	  >  -1)	bResult = false;
	if (UTF8Tools::Compare("b",			"a")	  <   1)	bResult = false;
	if (UTF8Tools::Compare("1234",		"4321")	  >  -1)	bResult = false;
	if (UTF8Tools::Compare("ABBA",		"ABBA")	  !=  0)	bResult = false;
	if (UTF8Tools::Compare("ABBA",		"abbaba") >  -1)	bResult = false;
	if (UTF8Tools::Compare("abbaba",	"ABBA")	  <   1)	bResult = false;
	if (UTF8Tools::Compare("ABBA",		"BAAB")	  >  -1)	bResult = false;
	EndTask(bResult);

	// FindSubstring(const char szSource[], const char szSubstring[])
	StartTask("FindSubstring(const char szSource[], const char szSubstring[])");
	bResult = true;
	if (UTF8Tools::FindSubstring("", "")) bResult = false;
	if (UTF8Tools::FindSubstring("a", "")) bResult = false;
	if (_stricmp(UTF8Tools::FindSubstring("a", "a"), "a")) bResult = false;
	if (_stricmp(UTF8Tools::FindSubstring("abba", "a"), "abba")) bResult = false;
	if (_stricmp(UTF8Tools::FindSubstring("abba", "ab"), "abba")) bResult = false;
	if (_stricmp(UTF8Tools::FindSubstring("abba", "abba"), "abba")) bResult = false;
	if (!UTF8Tools::FindSubstring("abba", "abbab")) bResult = false;
	if (_stricmp(UTF8Tools::FindSubstring("abba", "bba"), "bba")) bResult = false;
	EndTask(bResult);

	// Copy(char szDestination[], const char szSource[], uint32 nCount)
	StartTask("Copy(char szDestination[], const char szSource[], uint32 nCount)");
	bResult = true;
	if (strcmp(UTF8Tools::Copy(szUTF8Temp, ""),		   ""))     bResult = false;
	if (strcmp(UTF8Tools::Copy(szUTF8Temp, "", 0),	   ""))     bResult = false;
	if (strcmp(UTF8Tools::Copy(szUTF8Temp, "a"),	   "a"))    bResult = false;
	if (strcmp(UTF8Tools::Copy(szUTF8Temp, "abba"),	   "abba")) bResult = false;
	if (strcmp(UTF8Tools::Copy(szUTF8Temp, "baab", 2), "baba")) bResult = false;
	if (strcmp(UTF8Tools::Copy(szUTF8Temp, "abba", 8), "abba")) bResult = false;
	if (strcmp(UTF8Tools::Copy(szUTF8Temp, "aa"),	   "aa"))   bResult = false;
	EndTask(bResult);
}
