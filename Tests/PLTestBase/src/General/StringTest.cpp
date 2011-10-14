/*********************************************************\
 *  File: StringTest.cpp                                 *
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
#include <locale.h>
#include <string.h>
#ifdef APPLE
	#include <stdlib.h>
#else
	#include <malloc.h>
#endif
#ifdef LINUX
	#include <wchar.h>
	#include <PLCore/PLCoreLinuxWrapper.h>
#endif
#include <PLCore/String/String.h>
#include "PLTestBase/General/StringTest.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4996) // "'strdup': The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: _strdup. See online help for details."


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *StringTest::GetName() const
{
	return "String";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void StringTest::Test()
{
	String sString, sStringT;
	const wchar_t *pszTempWide;
	const char *pszTempUTF8;
	const char *pszTemp;
	bool bResult;

	// Constructors
	StartTask("Constructors");
	bResult = true;
	{
		String sTest;
		if (sTest.GetLength() || strlen(sTest.GetASCII())) bResult = false;
	}
	{
		String sTest('a');
		if (sTest.GetLength() != 1 || sTest != "a") bResult = false;
	}
	{
		String sTest('\0');
		if (sTest.GetLength()) bResult = false;
	}
	{
		String sTest(L'a');
		if (sTest.GetLength() != 1 || sTest != L"a") bResult = false;
	}
	{
		String sTest(L'\u9f8d');
		if (sTest.GetLength() != 1 || sTest != L"\u9f8d") bResult = false;
	}
	{
		String sTest(L'\0');
		if (sTest.GetLength()) bResult = false;
	}
	{
		String sTest(static_cast<const char*>(nullptr));
		if (sTest.GetLength()) bResult = false;
	}
	{
		String sTest("%");
		if (sTest.GetLength() != 1 || sTest != "%") bResult = false;
	}
	{
		String sTest("123");
		if (sTest.GetLength() != 3 || sTest != "123") bResult = false;
	}
	{
		char *pszTest = new char[4];
		strcpy(pszTest, "123");
		String sTest(pszTest, false); // Do not copy, please
		if (sTest.GetLength() != 3 || sTest != "123" || sTest.GetASCII() != pszTest) bResult = false;
	}
	{
		String sTest(static_cast<const wchar_t*>(nullptr));
		if (sTest.GetLength()) bResult = false;
	}
	{
		String sTest(L"%");
		if (sTest.GetLength() != 1 || sTest != L"%") bResult = false;
	}
	{
		String sTest(L"123");
		if (sTest.GetLength() != 3 || sTest != L"123") bResult = false;
	}
	{ // Can you read THIS? *g* (nihon = 'Japanese', http://www.gojukai.nl/karate/en/jp_kanji.html for symbols & Unicode numbers)
		String sTest(L"\u65e5\u672c\u8a9e");
		if (sTest.GetLength() != 3 || sTest != L"\u65e5\u672c\u8a9e") bResult = false;
	}
	{
		wchar_t *pszTest = new wchar_t[4];
		wcscpy(pszTest, L"\u65e5\u672c\u8a9e");
		String sTest(pszTest, false); // Do not copy, please
		if (sTest.GetLength() != 3 || sTest != L"\u65e5\u672c\u8a9e" || sTest.GetUnicode() != pszTest) bResult = false;
	}
	EndTask(bResult);

	// GetLength()
	StartTask("GetLength()");
	bResult = true;
	sString = "";
	if (sString.GetLength()) bResult = false;
	sString = "1";
	if (sString.GetLength() != 1) bResult = false;
	sString = "This 1_6";
	if (sString.GetLength() != 8) bResult = false;
	sString = static_cast<char*>(nullptr);
	if (sString.GetLength()) bResult = false;
	sString = static_cast<const char*>(nullptr);
	if (sString.GetLength()) bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (sString.GetLength() != 3) bResult = false;
	sString = "";
	if (sString.GetLength()) bResult = false;
	EndTask(bResult);

	// Format(const char *pszFormat, ...)
	StartTask("Format(const char *pszFormat, ...)");
	bResult = true;
	if (String::Format(static_cast<const char*>(nullptr)).GetLength()) bResult = false;
	if (String::Format("").GetLength()) bResult = false;
	if (String::Format("1") != "1") bResult = false;
	if (String::Format("1%s5", "__") != "1__5") bResult = false;
	if (String::Format("%g 1%s5", 5.12f, "__") != "5.12 1__5") bResult = false;
	if (String::Format(static_cast<const char*>(nullptr)).GetLength()) bResult = false;
	EndTask(bResult);

	// Format(const wchar_t *pszFormat, ...)
	StartTask("Format(const wchar_t *pszFormat, ...)");
	bResult = true;
	if (String::Format(static_cast<const wchar_t*>(nullptr)).GetLength()) bResult = false;
	if (String::Format(L"").GetLength()) bResult = false;
	if (String::Format(L"1") != L"1") bResult = false;
	if (String::Format(L"1%s5", L"__") != L"1__5") bResult = false;
	if (String::Format(L"%g 1%s5", 5.12f, L"__") != L"5.12 1__5") bResult = false;
	if (String::Format(static_cast<const wchar_t*>(nullptr)).GetLength()) bResult = false;
	if (String::Format(L"1%s5", L"_\u65e5\u672c\u8a9e_") != L"1_\u65e5\u672c\u8a9e_5") bResult = false;
	// Some special '-0' tests :)
	if (String::Format(L"%d", -0) != L"0") bResult = false;
	if (String::Format(L"%.4f", -0.0f) != L"0.0000") bResult = false;
	if (String::Format(L"%g", -0.0f) != L"0") bResult = false;
	EndTask(bResult);

	// GetFormat()
	StartTask("GetFormat()");
	bResult = true;
	sString = "";
	if (sString.GetFormat() != String::ASCII) bResult = false;
	sString = "1234";
	if (sString.GetFormat() != String::ASCII) bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (sString.GetFormat() != String::Unicode) bResult = false;
	EndTask(bResult);

	// GetNumOfBytes()
	StartTask("GetNumOfBytes()");
	bResult = true;
	sString = "";
	if (sString.GetNumOfBytes()) bResult = false;
	sString = "1234";
	if (sString.GetNumOfBytes() != 4) bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (sString.GetNumOfBytes() != 3*sizeof(wchar_t)) bResult = false;
	EndTask(bResult);

	// [](uint32 nIndex)
	StartTask("[](uint32 nIndex)");
	bResult = true;
	sString = "";
	if (sString[static_cast<uint32>(0)] != '\0') bResult = false;
	sString = "1234";
	if (sString[static_cast<uint32>(0)] != '1' || sString[static_cast<uint32>(1)] != '2' ||
		sString[static_cast<uint32>(2)] != '3' || sString[static_cast<uint32>(3)] != '4' || sString[static_cast<uint32>(5)] != '\0') bResult = false;
	EndTask(bResult);

	// GetASCII(): From ASCII
	StartTask("GetASCII(): From ASCII");
	bResult = true;
	sString = "";
	if (!sString.GetASCII() || strcmp(sString.GetASCII(), "")) bResult = false;
	sString = "abcd";
	if (!sString.GetASCII() || strcmp(sString.GetASCII(), "abcd")) bResult = false;
	pszTemp = sString.GetASCII();
	sString.ToLower();
	pszTempWide = new wchar_t[100]; // If the internal memory manager is reusing the same free address, we need THIS! :)
	if (sString.GetASCII() != pszTemp) bResult = false;
	delete [] pszTempWide;
	sString.Insert("Hi");
	pszTempWide = new wchar_t[100]; // If the internal memory manager is reusing the same free address, we need THIS! :)
	if (sString.GetASCII() == pszTemp) bResult = false;
	delete [] pszTempWide;
	EndTask(bResult);

	// GetASCII(): From Unicode
	StartTask("GetASCII(): From Unicode");
	bResult = true;
	sString = L"";
	if (!sString.GetASCII() || strcmp(sString.GetASCII(), "")) bResult = false;
	sString = L"abcd";
	if (!sString.GetASCII() || strcmp(sString.GetASCII(), "abcd")) bResult = false;
	pszTemp = sString.GetASCII();
	sString.ToLower();
	pszTempWide = new wchar_t; // If the internal memory manager is reusing the same free address, we need THIS! :)
	if (sString.GetASCII() != pszTemp) bResult = false;
	delete pszTempWide;
	sString.Insert(L"Hi");
	pszTempWide = new wchar_t[100]; // If the internal memory manager is reusing the same free address, we need THIS! :)
	if (sString.GetASCII() == pszTemp) bResult = false;
	delete [] pszTempWide;
	EndTask(bResult);

	// GetUnicode(): From ASCII
	StartTask("GetUnicode(): From ASCII");
	bResult = true;
	sString = "";
	if (!sString.GetUnicode() || wcscmp(sString.GetUnicode(), L"")) bResult = false;
	sString = "abcd";
	if (!sString.GetUnicode() || wcscmp(sString.GetUnicode(), L"abcd")) bResult = false;
	pszTempWide = sString.GetUnicode();
	sString.ToLower();
	pszTemp = new char[100]; // If the internal memory manager is reusing the same free address, we need THIS! :)
	if (sString.GetUnicode() != pszTempWide) bResult = false;
	delete [] pszTemp;
	sString.Insert("Hi");
	pszTemp = new char[100]; // If the internal memory manager is reusing the same free address, we need THIS! :)
	if (sString.GetUnicode() == pszTempWide) bResult = false;
	delete [] pszTemp;
	EndTask(bResult);

	// GetUnicode(): From Unicode
	StartTask("GetUnicode(): From Unicode");
	bResult = true;
	sString = L"";
	if (!sString.GetUnicode() || wcscmp(sString.GetUnicode(), L"")) bResult = false;
	sString = L"abcd";
	if (!sString.GetUnicode() || wcscmp(sString.GetUnicode(), L"abcd")) bResult = false;
	pszTempWide = sString.GetUnicode();
	sString.ToLower();
	pszTemp = new char[100]; // If the internal memory manager is reusing the same free address, we need THIS! :)
	if (sString.GetUnicode() != pszTempWide) bResult = false;
	delete [] pszTemp;
	sString.Insert(L"Hi");
	pszTemp = new char[100]; // If the internal memory manager is reusing the same free address, we need THIS! :)
	if (sString.GetUnicode() == pszTempWide) bResult = false;
	delete [] pszTemp;
	EndTask(bResult);

	// GetUTF8(): From ASCII
	StartTask("GetUTF8(): From ASCII");
	bResult = true;
	sString = "";
	if (!sString.GetUTF8() || strcmp(sString.GetUTF8(), "")) bResult = false;
	sString = "abcd";
	if (!sString.GetUTF8() || strcmp(sString.GetUTF8(), "abcd")) bResult = false;
	pszTempUTF8 = sString.GetUTF8();
	sString.ToLower();
	pszTemp = new char[100]; // If the internal memory manager is reusing the same free address, we need THIS! :)
	if (sString.GetUTF8() != pszTempUTF8) bResult = false;
	delete [] pszTemp;
	sString.Insert("Hi");
	pszTemp = new char[100]; // If the internal memory manager is reusing the same free address, we need THIS! :)
	if (sString.GetUTF8() == pszTempUTF8) bResult = false;
	delete [] pszTemp;
	EndTask(bResult);

	// GetUTF8(): From Unicode
	StartTask("GetUTF8(): From Unicode");
	bResult = true;
	sString = L"";
	if (!sString.GetUTF8() || strcmp(sString.GetUTF8(), "")) bResult = false;
	sString = L"abcd";
	if (!sString.GetUTF8() || strcmp(sString.GetUTF8(), "abcd")) bResult = false;
	pszTempUTF8 = sString.GetUTF8();
	sString.ToLower();
	pszTemp = new char[100]; // If the internal memory manager is reusing the same free address, we need THIS! :)
	if (sString.GetUTF8() != pszTempUTF8) bResult = false;
	delete [] pszTemp;
	sString.Insert(L"Hi");
	pszTemp = new char[100]; // If the internal memory manager is reusing the same free address, we need THIS! :)
	if (sString.GetUTF8() == pszTempUTF8) bResult = false;
	delete [] pszTemp;
	EndTask(bResult);

	// =(const String &sString)
	StartTask("=(const String &sString)");
	bResult = true;
	sStringT = "";
	sString = sStringT;
	if (sString.GetLength() != 0 || sString != sStringT) bResult = false;
	sStringT = "1234";
	sString = sStringT;
	if (sString.GetLength() != 4 || sString != sStringT) bResult = false;
	EndTask(bResult);

	// =(const char *pszString)
	StartTask("=(const char *pszString)");
	bResult = true;
	sString = static_cast<const char*>(nullptr);
	if (sString.GetLength() != 0 || sString != "") bResult = false;
	sString = "";
	if (sString.GetLength() != 0 || sString != "") bResult = false;
	sString = "1234";
	if (sString.GetLength() != 4 || sString != "1234") bResult = false;
	EndTask(bResult);

	// =(const wchar_t *pszString)
	StartTask("=(const wchar_t *pszString)");
	bResult = true;
	sString = static_cast<const wchar_t*>(nullptr);
	if (sString.GetLength() != 0 || sString != L"") bResult = false;
	sString = L"";
	if (sString.GetLength() != 0 || sString != L"") bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (sString.GetLength() != 3 || sString != L"\u65e5\u672c\u8a9e") bResult = false;
	EndTask(bResult);

	// +(const String &sString)
	StartTask("+(const String &sString)");
	bResult = true;
	sString  = "";
	sStringT = "";
	sString  = sString + sStringT;
	if (sString != "") bResult = false;
	sString  = "A";
	sStringT = "";
	sString  = sString + sStringT;
	if (sString != "A") bResult = false;
	sString  = "A12";
	sStringT = "";
	sString  = sString + sStringT;
	if (sString != "A12") bResult = false;
	sString  = "";
	sStringT = "B";
	sString  = sString + sStringT;
	if (sString != "B") bResult = false;
	sString  = "";
	sStringT = "B34";
	sString  = sString + sStringT;
	if (sString != "B34") bResult = false;
	sString  = "A";
	sStringT = "B";
	sString  = sString + sStringT;
	if (sString != "AB") bResult = false;
	sString  = "A12";
	sStringT = "B34";
	sString  = sString + sStringT;
	if (sString != "A12B34") bResult = false;
	sString  = "A";
	sStringT = "%";
	sString  = sString + sStringT;
	if (sString != "A%") bResult = false;
	// Add Unicode to an ASCII string
	sString  = "A";
	sStringT = L"%";
	sString  = sString + sStringT;
	if (sString.GetFormat() != String::Unicode || sString != L"A%") bResult = false;
	// Add ASCII to an Unicode string
	sString  = L"A";
	sStringT = "%";
	sString  = sString + sStringT;
	if (sString.GetFormat() != String::Unicode || sString != L"A%") bResult = false;
	EndTask(bResult);

	// +(const char *pszString)
	StartTask("+(const char *pszString)");
	bResult = true;
	sString = "";
	sString = sString + static_cast<const char*>(nullptr);
	if (sString != "") bResult = false;
	sString = "";
	sString = sString + "";
	if (sString != "") bResult = false;
	sString = "A";
	sString = sString + static_cast<const char*>(nullptr);
	if (sString != "A") bResult = false;
	sString = "A";
	sString = sString + "";
	if (sString != "A") bResult = false;
	sString = "A12";
	sString = sString + static_cast<const char*>(nullptr);
	if (sString != "A12") bResult = false;
	sString = "A12";
	sString = sString + "";
	if (sString != "A12") bResult = false;
	sString = "";
	sString = sString + "B";
	if (sString != "B") bResult = false;
	sString = "";
	sString = sString + "B34";
	if (sString != "B34") bResult = false;
	sString = "A";
	sString = sString + "B";
	if (sString != "AB") bResult = false;
	sString = "A12";
	sString = sString + "B34";
	if (sString != "A12B34") bResult = false;
	sString  = "A";
	sString = sString + "%";
	if (sString != "A%") bResult = false;
	// Add ASCII to an Unicode string
	sString  = L"A";
	sString = sString + "%";
	if (sString.GetFormat() != String::Unicode || sString != L"A%") bResult = false;
	EndTask(bResult);

	// +(const wchar_t *pszString)
	StartTask("+(const wchar_t *pszString)");
	bResult = true;
	sString = L"";
	sString = sString + static_cast<const wchar_t*>(nullptr);
	if (sString != L"") bResult = false;
	sString = L"";
	sString = sString + L"";
	if (sString != L"") bResult = false;
	sString = L"A";
	sString = sString + static_cast<const wchar_t*>(nullptr);
	if (sString != L"A") bResult = false;
	sString = L"A";
	sString = sString + L"";
	if (sString != L"A") bResult = false;
	sString = L"A12";
	sString = sString + static_cast<const wchar_t*>(nullptr);
	if (sString != L"A12") bResult = false;
	sString = L"A12";
	sString = sString + L"";
	if (sString != L"A12") bResult = false;
	sString = L"";
	sString = sString + L"B";
	if (sString != L"B") bResult = false;
	sString = L"";
	sString = sString + L"B34";
	if (sString != L"B34") bResult = false;
	sString = L"A";
	sString = sString + L"B";
	if (sString != L"AB") bResult = false;
	sString = L"A12";
	sString = sString + L"B34";
	if (sString != L"A12B34") bResult = false;
	sString  = L"A";
	sString = sString + L"%";
	if (sString != L"A%") bResult = false;
	sString  = L"\u65e5\u672c";
	sString = sString + L"\u8a9e";
	if (sString != L"\u65e5\u672c\u8a9e") bResult = false;
	// Add Unicode to an ASCII string
	sString  = "A";
	sString = sString + L"%";
	if (sString.GetFormat() != String::Unicode || sString != L"A%") bResult = false;
	EndTask(bResult);

	// +(const char *pszString, const String &sString)
	StartTask("+(const char *pszString, const String &sString)");
	bResult = true;
	sString = "";
	sString = static_cast<const char*>(nullptr) + sString;
	if (sString != "") bResult = false;
	sString = "";
	sString = "" + sString;
	if (sString != "") bResult = false;
	sString = "";
	sString = "A" + sString;
	if (sString != "A") bResult = false;
	sString = "";
	sString = "A12" + sString;
	if (sString != "A12") bResult = false;
	sString = "B";
	sString = static_cast<const char*>(nullptr) + sString;
	if (sString != "B") bResult = false;
	sString = "B";
	sString = "" + sString;
	if (sString != "B") bResult = false;
	sString = "B34";
	sString = static_cast<const char*>(nullptr) + sString;
	if (sString != "B34") bResult = false;
	sString = "B34";
	sString = "" + sString;
	if (sString != "B34") bResult = false;
	sString = "B";
	sString = "A" + sString;
	if (sString != "AB") bResult = false;
	sString = "B34";
	sString = "A12" + sString;
	if (sString != "A12B34") bResult = false;
	sString  = "A";
	sString =  "%" + sString;
	if (sString != "%A") bResult = false;
	// Add ASCII to an Unicode string
	sString  = L"A";
	sString = "%" + sString;
	if (sString.GetFormat() != String::Unicode || sString != L"%A") bResult = false;
	EndTask(bResult);

	// +(const wchar_t *pszString, const String &sString)
	StartTask("+(const wchar_t *pszString, const String &sString)");
	bResult = true;
	sString = L"";
	sString = static_cast<const wchar_t*>(nullptr) + sString;
	if (sString != L"") bResult = false;
	sString = L"";
	sString = L"" + sString;
	if (sString != L"") bResult = false;
	sString = L"";
	sString = L"A" + sString;
	if (sString != L"A") bResult = false;
	sString = L"";
	sString = L"A12" + sString;
	if (sString != L"A12") bResult = false;
	sString = L"B";
	sString = static_cast<const wchar_t*>(nullptr) + sString;
	if (sString != L"B") bResult = false;
	sString = L"B";
	sString = L"" + sString;
	if (sString != L"B") bResult = false;
	sString = L"B34";
	sString = static_cast<const wchar_t*>(nullptr) + sString;
	if (sString != L"B34") bResult = false;
	sString = L"B34";
	sString = L"" + sString;
	if (sString != L"B34") bResult = false;
	sString = L"B";
	sString = L"A" + sString;
	if (sString != L"AB") bResult = false;
	sString = L"B34";
	sString = L"A12" + sString;
	if (sString != L"A12B34") bResult = false;
	sString  = L"A";
	sString =  L"%" + sString;
	if (sString != L"%A") bResult = false;
	sString  = L"\u672c\u8a9e";
	sString =  L"\u65e5" + sString;
	if (sString != L"\u65e5\u672c\u8a9e") bResult = false;
	// Add Unicode to an ASCII string
	sString  = "A";
	sString = L"%" + sString;
	if (sString.GetFormat() != String::Unicode || sString != L"%A") bResult = false;
	EndTask(bResult);

	// +=(const String &sString)
	StartTask("+=(const String &sString)");
	bResult = true;
	sString  = "";
	sStringT = "";
	sString  += sStringT;
	if (sString != "") bResult = false;
	sString  = "A";
	sStringT = "";
	sString  += sStringT;
	if (sString != "A") bResult = false;
	sString  = "A12";
	sStringT = "";
	sString  += sStringT;
	if (sString != "A12") bResult = false;
	sString  = "";
	sStringT = "B";
	sString  += sStringT;
	if (sString != "B") bResult = false;
	sString  = "";
	sStringT = "B34";
	sString  += sStringT;
	if (sString != "B34") bResult = false;
	sString  = "A";
	sStringT = "B";
	sString  += sStringT;
	if (sString != "AB") bResult = false;
	sString  = "A12";
	sStringT = "B34";
	sString  += sStringT;
	if (sString != "A12B34") bResult = false;
	sString  = "A";
	sStringT = "%";
	sString  += sStringT;
	if (sString != "A%") bResult = false;
	// Add Unicode to an ASCII string
	sString  = "A";
	sStringT = L"%";
	sString  += sStringT;
	if (sString.GetFormat() != String::Unicode || sString != L"A%") bResult = false;
	// Add ASCII to an Unicode string
	sString  = L"A";
	sStringT = "%";
	sString  += sStringT;
	if (sString.GetFormat() != String::Unicode || sString != L"A%") bResult = false;
	EndTask(bResult);

	// +=(const char *pszString)
	StartTask("+=(const char *pszString)");
	bResult = true;
	sString = "";
	sString += static_cast<const char*>(nullptr);
	if (sString != "") bResult = false;
	sString = "";
	sString += "";
	if (sString != "") bResult = false;	
	sString = "A";
	sString += static_cast<const char*>(nullptr);
	if (sString != "A") bResult = false;
	sString = "A";
	sString += "";
	if (sString != "A") bResult = false;
	sString = "A12";
	sString += static_cast<const char*>(nullptr);
	if (sString != "A12") bResult = false;
	sString = "A12";
	sString += "";
	if (sString != "A12") bResult = false;
	sString = "";
	sString += "B";
	if (sString != "B") bResult = false;
	sString = "";
	sString += "B34";
	if (sString != "B34") bResult = false;
	sString = "A";
	sString += "B";
	if (sString != "AB") bResult = false;
	sString = "A12";
	sString += "B34";
	if (sString != "A12B34") bResult = false;
	sString = "A";
	sString += "%";
	if (sString != "A%") bResult = false;
	// Add ASCII to an Unicode string
	sString = L"A";
	sString += "%";
	if (sString.GetFormat() != String::Unicode || sString != L"A%") bResult = false;
	EndTask(bResult);

	// +=(const wchar_t *pszString)
	StartTask("+=(const wchar_t *pszString)");
	bResult = true;
	sString = L"";
	sString += static_cast<const wchar_t*>(nullptr);
	if (sString != L"") bResult = false;
	sString = L"";
	sString += L"";
	if (sString != L"") bResult = false;	
	sString = L"A";
	sString += static_cast<const wchar_t*>(nullptr);
	if (sString != L"A") bResult = false;
	sString = L"A";
	sString += L"";
	if (sString != L"A") bResult = false;
	sString = L"A12";
	sString += static_cast<const wchar_t*>(nullptr);
	if (sString != L"A12") bResult = false;
	sString = L"A12";
	sString += L"";
	if (sString != L"A12") bResult = false;
	sString = L"";
	sString += L"B";
	if (sString != L"B") bResult = false;
	sString = L"";
	sString += L"B34";
	if (sString != L"B34") bResult = false;
	sString = L"A";
	sString += L"B";
	if (sString != L"AB") bResult = false;
	sString = L"A12";
	sString += L"B34";
	if (sString != L"A12B34") bResult = false;
	sString = L"A";
	sString += L"%";
	if (sString != L"A%") bResult = false;
	sString = L"\u65e5\u672c";
	sString += L"\u8a9e";
	if (sString != L"\u65e5\u672c\u8a9e") bResult = false;
	// Add Unicode to an ASCII string
	sString = "A";
	sString += L"%";
	if (sString.GetFormat() != String::Unicode || sString != L"A%") bResult = false;
	EndTask(bResult);

	// <(const String &sString)
	StartTask("<(const String &sString)");
	bResult = true;
	sString = "";
	sStringT = "";
	if (sString < sStringT) bResult = false;
	sString = "A";
	sStringT = "";
	if (sString < sStringT) bResult = false;
	sString = "";
	sStringT = "A";
	if (!(sString < sStringT)) bResult = false;
	sString = "A";
	sStringT = "A";
	if (sString < sStringT) bResult = false;
	sString = "AB";
	sStringT = "A";
	if (sString < sStringT) bResult = false;
	// Compare ASCII with an Unicode string
	sString  = "AB";
	sStringT = L"A";
	if (sString < sStringT) bResult = false;
	// Compare Unicode with an ASCII string
	sString  = L"AB";
	sStringT = "A";
	if (sString < sStringT) bResult = false;
	EndTask(bResult);

	// <(const char *pszString)
	StartTask("<(const char *pszString)");
	bResult = true;
	sString = "";
	if (sString < static_cast<const char*>(nullptr)) bResult = false;
	if (sString < "") bResult = false;
	sString = "A";
	if (sString < "") bResult = false;
	sString = "";
	if (!(sString < "A")) bResult = false;
	sString = "A";
	if (sString < "A") bResult = false;
	sString = "AB";
	if (sString < "A") bResult = false;
	// Compare Unicode with an ASCII string
	sString = L"AB";
	if (sString < "A") bResult = false;
	EndTask(bResult);

	// <(const wchar_t *pszString)
	StartTask("<(const wchar_t *pszString)");
	bResult = true;
	sString = L"";
	if (sString < static_cast<const wchar_t*>(nullptr)) bResult = false;
	if (sString < L"") bResult = false;
	sString = L"A";
	if (sString < L"") bResult = false;
	sString = L"";
	if (!(sString < L"A")) bResult = false;
	sString = L"A";
	if (sString < L"A") bResult = false;
	sString = L"AB";
	if (sString < L"A") bResult = false;
	sString = L"\u8a9e";
	if (sString < L"\u65e5\u672c") bResult = false;
	// Compare ASCII with an Unicode string
	sString = "AB";
	if (sString < L"A") bResult = false;
	EndTask(bResult);

	// >(const String &sString)
	StartTask(">(const String &sString)");
	bResult = true;
	sString = "";
	sStringT = "";
	if (sString > sStringT) bResult = false;
	sString = "";
	sStringT = "A";
	if (sString > sStringT) bResult = false;
	sString = "A";
	sStringT = "";
	if (!(sString > sStringT)) bResult = false;
	sString = "A";
	sStringT = "A";
	if (sString > sStringT) bResult = false;
	sString = "A";
	sStringT = "AB";
	if (sString > sStringT) bResult = false;
	// Compare ASCII with an Unicode string
	sString  = "A";
	sStringT = L"AB";
	if (sString > sStringT) bResult = false;
	// Compare Unicode with an ASCII string
	sString  = L"A";
	sStringT = "AB";
	if (sString > sStringT) bResult = false;
	EndTask(bResult);

	// >(const char *pszString)
	StartTask(">(const char *pszString)");
	bResult = true;
	sString = "";
	if (sString > static_cast<const char*>(nullptr)) bResult = false;
	if (sString > "") bResult = false;
	sString = "A";
	if (!(sString > "")) bResult = false;
	sString = "";
	if (sString > "A") bResult = false;
	sString = "A";
	if (sString > "A") bResult = false;
	sString = "AB";
	if (!(sString > "A")) bResult = false;
	// Compare Unicode with an ASCII string
	sString = L"A";
	if (sString > "AB") bResult = false;
	EndTask(bResult);

	// >(const wchar_t *pszString)
	StartTask(">(const wchar_t *pszString)");
	bResult = true;
	sString = L"";
	if (sString > static_cast<const wchar_t*>(nullptr)) bResult = false;
	if (sString > L"") bResult = false;
	sString = L"A";
	if (!(sString > L"")) bResult = false;
	sString = L"";
	if (sString > L"A") bResult = false;
	sString = L"A";
	if (sString > L"A") bResult = false;
	sString = L"AB";
	if (!(sString > L"A")) bResult = false;
	sString = L"\u8a9e";
	if (!(sString > L"\u65e5\u672c")) bResult = false;
	// Compare ASCII with an Unicode string
	sString = "AB";
	if (!(sString > L"A")) bResult = false;
	EndTask(bResult);

	// ==(const String &sString)
	StartTask("==(const String &sString)");
	bResult = true;
	sString = "";
	sStringT = "";
	if (!(sString == sStringT)) bResult = false;
	sString = "A";
	sStringT = "";
	if (sString == sStringT) bResult = false;
	sString = "A12";
	sStringT = "";
	if (sString == sStringT) bResult = false;
	sString = "";
	sStringT = "B";
	if (sString == sStringT) bResult = false;
	sString = "";
	sStringT = "B34";
	if (sString == sStringT) bResult = false;
	sString = "A";
	sStringT = "B";
	if (sString == sStringT) bResult = false;
	sString = "A12";
	sStringT = "B";
	if (sString == sStringT) bResult = false;
	sString = "A";
	sStringT = "B34";
	if (sString == sStringT) bResult = false;
	sString = "A12";
	sStringT = "B34";
	if (sString == sStringT) bResult = false;
	sString = "A";
	sStringT = "A";
	if (!(sString == sStringT)) bResult = false;
	sString = "A12";
	sStringT = "A12";
	if (!(sString == sStringT)) bResult = false;
	sString = "A12";
	sStringT = sString;
	if (!(sString == sStringT)) bResult = false;
	// Compare ASCII with an Unicode string
	sString  = "A123";
	sStringT = L"A12";
	if (sString == sStringT) bResult = false;
	sString  = "A13";
	sStringT = L"A12";
	if (sString == sStringT) bResult = false;
	sString  = "A12";
	sStringT = L"A12";
	if (!(sString == sStringT)) bResult = false;
	// Compare Unicode with an ASCII string
	sString  = L"A123";
	sStringT = "A12";
	if (sString == sStringT) bResult = false;
	sString  = L"A13";
	sStringT = "A12";
	if (sString == sStringT) bResult = false;
	sString  = L"A12";
	sStringT = "A12";
	if (!(sString == sStringT)) bResult = false;
	EndTask(bResult);

	// ==(const char *pszString)
	StartTask("==(const char *pszString)");
	bResult = true;
	sString = "";
	if (!(sString == static_cast<const char*>(nullptr))) bResult = false;
	sString = "";
	if (!(sString == "")) bResult = false;
	sString = "A";
	if (sString == static_cast<const char*>(nullptr)) bResult = false;
	sString = "A";
	if (sString == "") bResult = false;
	sString = "A12";
	if (sString == static_cast<const char*>(nullptr)) bResult = false;
	sString = "A12";
	if (sString == "") bResult = false;
	sString = "";
	if (sString == "B") bResult = false;
	sString = "";
	if (sString == "B34") bResult = false;
	sString = "A";
	if (sString == "B") bResult = false;
	sString = "A12";
	if (sString == "B") bResult = false;
	sString = "A";
	if (sString == "B34") bResult = false;
	sString = "A12";
	if (sString == "B34") bResult = false;
	sString = "A";
	if (!(sString == "A")) bResult = false;
	sString = "A12";
	if (!(sString == "A12")) bResult = false;
	// Compare Unicode with an ASCII string
	sString  = L"A123";
	if (sString == "A12") bResult = false;
	sString  = L"A13";
	if (sString == "A12") bResult = false;
	sString  = L"A12";
	if (!(sString == "A12")) bResult = false;
	EndTask(bResult);

	// ==(const wchar_t *pszString)
	StartTask("==(const wchar_t *pszString)");
	bResult = true;
	sString = L"";
	if (!(sString == static_cast<const wchar_t*>(nullptr))) bResult = false;
	sString = L"";
	if (!(sString == L"")) bResult = false;
	sString = L"A";
	if (sString == static_cast<const wchar_t*>(nullptr)) bResult = false;
	sString = L"A";
	if (sString == L"") bResult = false;
	sString = L"A12";
	if (sString == static_cast<const wchar_t*>(nullptr)) bResult = false;
	sString = L"A12";
	if (sString == L"") bResult = false;
	sString = L"";
	if (sString == L"B") bResult = false;
	sString = L"";
	if (sString == L"B34") bResult = false;
	sString = L"A";
	if (sString == L"B") bResult = false;
	sString = L"A12";
	if (sString == L"B") bResult = false;
	sString = L"A";
	if (sString == L"B34") bResult = false;
	sString = L"A12";
	if (sString == L"B34") bResult = false;
	sString = L"A";
	if (!(sString == L"A")) bResult = false;
	sString = L"A12";
	if (!(sString == L"A12")) bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (!(sString == L"\u65e5\u672c\u8a9e")) bResult = false;
	sString = L"\u65e5\u672c";
	if (sString == L"\u672c\u8a9e") bResult = false;
	// Compare Unicode with an ASCII string
	sString  = L"A123";
	if (sString == "A12") bResult = false;
	sString  = L"A13";
	if (sString == "A12") bResult = false;
	sString  = L"A12";
	if (!(sString == "A12")) bResult = false;
	EndTask(bResult);

	// !=(const String &sString)
	StartTask("!=(const String &sString)");
	bResult = true;
	sString = "";
	sStringT = "";
	if (sString != sStringT) bResult = false;
	sString = "A";
	sStringT = "";
	if (!(sString != sStringT)) bResult = false;
	sString = "A12";
	sStringT = "";
	if (!(sString != sStringT)) bResult = false;
	sString = "";
	sStringT = "B";
	if (!(sString != sStringT)) bResult = false;
	sString = "";
	sStringT = "B34";
	if (!(sString != sStringT)) bResult = false;
	sString = "A";
	sStringT = "B";
	if (!(sString != sStringT)) bResult = false;
	sString = "A12";
	sStringT = "B";
	if (!(sString != sStringT)) bResult = false;
	sString = "A";
	sStringT = "B34";
	if (!(sString != sStringT)) bResult = false;
	sString = "A12";
	sStringT = "B34";
	if (!(sString != sStringT)) bResult = false;
	sString = "A";
	sStringT = "A";
	if (sString != sStringT) bResult = false;
	sString = "A12";
	sStringT = "A12";
	if (sString != sStringT) bResult = false;
	sString = "A12";
	sStringT = sString;
	if (sString != sStringT) bResult = false;
	// Compare ASCII with an Unicode string
	sString  = "A123";
	sStringT = L"A12";
	if (!(sString != sStringT)) bResult = false;
	sString  = "A13";
	sStringT = L"A12";
	if (!(sString != sStringT)) bResult = false;
	sString  = "A12";
	sStringT = L"A12";
	if (sString != sStringT) bResult = false;
	// Compare Unicode with an ASCII string
	sString  = L"A123";
	sStringT = "A12";
	if (!(sString != sStringT)) bResult = false;
	sString  = L"A13";
	sStringT = "A12";
	if (!(sString != sStringT)) bResult = false;
	sString  = L"A12";
	sStringT = "A12";
	if (sString != sStringT) bResult = false;
	EndTask(bResult);

	// !=(const char *pszString)
	StartTask("!=(const char *pszString)");
	bResult = true;
	sString = "";
	if (sString != static_cast<const char*>(nullptr)) bResult = false;
	sString = "";
	if (sString != "") bResult = false;
	sString = "A";
	if (!(sString != static_cast<const char*>(nullptr))) bResult = false;
	sString = "A";
	if (!(sString != "")) bResult = false;
	sString = "A12";
	if (!(sString != static_cast<const char*>(nullptr))) bResult = false;
	sString = "A12";
	if (!(sString != "")) bResult = false;
	sString = "";
	if (!(sString != "B")) bResult = false;
	sString = "";
	if (!(sString != "B34")) bResult = false;
	sString = "A";
	if (!(sString != "B")) bResult = false;
	sString = "A12";
	if (!(sString != "B34")) bResult = false;
	sString = "A";
	if (sString != "A") bResult = false;
	sString = "A12";
	if (sString != "A12") bResult = false;
	// Compare Unicode with an ASCII string
	sString  = L"A123";
	if (!(sString != "A12")) bResult = false;
	sString  = L"A13";
	if (!(sString != "A12")) bResult = false;
	sString  = L"A12";
	if (sString != "A12") bResult = false;
	EndTask(bResult);

	// !=(const wchar_t *pszString)
	StartTask("!=(const wchar_t *pszString)");
	bResult = true;
	sString = L"";
	if (sString != static_cast<const wchar_t*>(nullptr)) bResult = false;
	sString = L"";
	if (sString != L"") bResult = false;
	sString = L"A";
	if (!(sString != static_cast<const wchar_t*>(nullptr))) bResult = false;
	sString = L"A";
	if (!(sString != L"")) bResult = false;
	sString = L"A12";
	if (!(sString != static_cast<const wchar_t*>(nullptr))) bResult = false;
	sString = L"A12";
	if (!(sString != L"")) bResult = false;
	sString = L"";
	if (!(sString != L"B")) bResult = false;
	sString = L"";
	if (!(sString != L"B34")) bResult = false;
	sString = L"A";
	if (!(sString != L"B")) bResult = false;
	sString = L"A12";
	if (!(sString != L"B34")) bResult = false;
	sString = L"A";
	if (sString != L"A") bResult = false;
	sString = L"A12";
	if (sString != L"A12") bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (sString != L"\u65e5\u672c\u8a9e") bResult = false;
	sString = L"\u65e5\u672c";
	if (!(sString != L"\u672c\u8a9e")) bResult = false;
	// Compare Unicode with an ASCII string
	sString  = L"A123";
	if (!(sString != "A12")) bResult = false;
	sString  = L"A13";
	if (!(sString != "A12")) bResult = false;
	sString  = L"A12";
	if (sString != "A12") bResult = false;
	EndTask(bResult);

	// Compare(const String &sString, uint32 nPos, uint32 nCount)
	StartTask("Compare(const String &sString, uint32 nPos, uint32 nCount)");
	bResult = true;
	sString = "";
	sStringT = "";
	if (!sString.Compare(sStringT)) bResult = false;
	sString = "Test";
	sStringT = "";
	if (sString.Compare(sStringT)) bResult = false;
	sString = "";
	sStringT = "Test";
	if (sString.Compare(sStringT)) bResult = false;
	sString = "Test";
	sStringT = "Test";
	if (!sString.Compare(sStringT)) bResult = false;
	if (sString.Compare(sStringT, 1, 10)) bResult = false;
	if (!sString.Compare(sStringT, 0, 10)) bResult = false;
	sString = "Test";
	sStringT = "TEst";
	if (sString.Compare(sStringT)) bResult = false;
	sString = "Test";
	sStringT = sString;
	if (!sString.Compare(sStringT)) bResult = false;
	sString = "Test";
	sStringT = "Tests";
	if (sString.Compare(sStringT)) bResult = false;
	sString = "Test";
	sStringT = "Tests";
	if (!sString.Compare(sStringT, 0, 4)) bResult = false;
	sString = "sTests";
	sStringT = "Test";
	if (!sString.Compare(sStringT, 1, 4)) bResult = false;
	sString = "sTests";
	sStringT = "Test";
	if (sString.Compare(sStringT, 1, 5)) bResult = false;
	if (sString.Compare(sStringT, 10)) bResult = false;
	if (sString.Compare(sStringT, 10, 5)) bResult = false;
	if (sString.Compare(sStringT, 1, 10)) bResult = false;
	if (sString.Compare(sStringT, 0, 10)) bResult = false;
	// Compare ASCII with an Unicode string
	sString = "sTests";
	sStringT = L"Test";
	if (sString.Compare(sStringT, 1, 5)) bResult = false;
	if (sString.Compare(sStringT, 10)) bResult = false;
	if (sString.Compare(sStringT, 10, 5)) bResult = false;
	if (sString.Compare(sStringT, 1, 10)) bResult = false;
	if (sString.Compare(sStringT, 0, 10)) bResult = false;
	// Compare Unicode with an ASCII string
	sString = L"sTests";
	sStringT = "Test";
	if (sString.Compare(sStringT, 1, 5)) bResult = false;
	if (sString.Compare(sStringT, 10)) bResult = false;
	if (sString.Compare(sStringT, 10, 5)) bResult = false;
	if (sString.Compare(sStringT, 1, 10)) bResult = false;
	if (sString.Compare(sStringT, 0, 10)) bResult = false;
	EndTask(bResult);

	// Compare(const char *pszString, uint32 nPos, uint32 nCount)
	StartTask("Compare(const char *pszString, uint32 nPos, uint32 nCount)");
	bResult = true;
	sString = "";
	if (!sString.Compare(static_cast<const char*>(nullptr))) bResult = false;
	sString = "";
	if (!sString.Compare("")) bResult = false;
	sString = "Test";
	if (sString.Compare(static_cast<const char*>(nullptr))) bResult = false;
	sString = "Test";
	if (sString.Compare("")) bResult = false;
	sString = "";
	if (sString.Compare("Test")) bResult = false;
	sString = "Test";
	if (!sString.Compare("Test")) bResult = false;
	if (sString.Compare("Test", 1, 10)) bResult = false;
	if (!sString.Compare("Test", 0, 10)) bResult = false;
	sString = "Test";
	if (sString.Compare("TEst")) bResult = false;
	sString = "Tests";
	if (sString.Compare("Test")) bResult = false;
	sString = "Tests";
	if (!sString.Compare("Test", 0, 4)) bResult = false;
	sString = "sTests";
	if (!sString.Compare("Test", 1, 4)) bResult = false;
	sString = "sTests";
	if (sString.Compare("Test", 1, 5)) bResult = false;
	if (sString.Compare("Test", 10)) bResult = false;
	if (sString.Compare("Test", 10, 5)) bResult = false;
	if (sString.Compare("Test", 1, 10)) bResult = false;
	if (sString.Compare("Test", 0, 10)) bResult = false;
	// Compare Unicode with an ASCII string
	sString = L"sTests";
	if (sString.Compare("Test", 1, 5)) bResult = false;
	if (sString.Compare("Test", 10)) bResult = false;
	if (sString.Compare("Test", 10, 5)) bResult = false;
	if (sString.Compare("Test", 1, 10)) bResult = false;
	if (sString.Compare("Test", 0, 10)) bResult = false;
	EndTask(bResult);

	// Compare(const wchar_t *pszString, uint32 nPos, uint32 nCount)
	StartTask("Compare(const wchar_t *pszString, uint32 nPos, uint32 nCount)");
	bResult = true;
	sString = L"";
	if (!sString.Compare(static_cast<const wchar_t*>(nullptr))) bResult = false;
	sString = L"";
	if (!sString.Compare(L"")) bResult = false;
	sString = L"Test";
	if (sString.Compare(static_cast<const wchar_t*>(nullptr))) bResult = false;
	sString = L"Test";
	if (sString.Compare(L"")) bResult = false;
	sString = L"";
	if (sString.Compare(L"Test")) bResult = false;
	sString = L"Test";
	if (!sString.Compare(L"Test")) bResult = false;
	if (sString.Compare(L"Test", 1, 10)) bResult = false;
	if (!sString.Compare(L"Test", 0, 10)) bResult = false;
	sString = L"Test";
	if (sString.Compare(L"TEst")) bResult = false;
	sString = L"Tests";
	if (sString.Compare(L"Test")) bResult = false;
	sString = L"Tests";
	if (!sString.Compare(L"Test", 0, 4)) bResult = false;
	sString = L"sTests";
	if (!sString.Compare(L"Test", 1, 4)) bResult = false;
	sString = L"sTests";
	if (sString.Compare(L"Test", 1, 5)) bResult = false;
	if (sString.Compare(L"Test", 10)) bResult = false;
	if (sString.Compare(L"Test", 10, 5)) bResult = false;
	if (sString.Compare(L"Test", 1, 10)) bResult = false;
	if (sString.Compare(L"Test", 0, 10)) bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (sString.Compare(L"\u65e5\u672c\u8a9e", 1, 4)) bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (!sString.Compare(L"\u672c\u8a9e", 1, 4)) bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (!sString.Compare(L"\u65e5\u672c\u8a9e", 0, 4)) bResult = false;
	// Compare ASCII with an Unicode string
	sString = "sTests";
	if (sString.Compare(L"Test", 1, 5)) bResult = false;
	if (sString.Compare(L"Test", 10)) bResult = false;
	if (sString.Compare(L"Test", 10, 5)) bResult = false;
	if (sString.Compare(L"Test", 1, 10)) bResult = false;
	if (sString.Compare(L"Test", 0, 10)) bResult = false;
	EndTask(bResult);

	// CompareNoCase(const String &sString, uint32 nPos, uint32 nCount)
	StartTask("CompareNoCase(const String &sString, uint32 nPos, uint32 nCount)");
	bResult = true;
	sString = "";
	sStringT = "";
	if (!sString.CompareNoCase(sStringT)) bResult = false;
	sString = "Test";
	sStringT = "";
	if (sString.CompareNoCase(sStringT)) bResult = false;
	sString = "";
	sStringT = "Test";
	if (sString.CompareNoCase(sStringT)) bResult = false;
	sString = "Test";
	sStringT = "Test";
	if (!sString.CompareNoCase(sStringT)) bResult = false;
	if (sString.CompareNoCase(sStringT, 1, 10)) bResult = false;
	if (!sString.CompareNoCase(sStringT, 0, 10)) bResult = false;
	sString = "Test";
	sStringT = "TEst";
	if (!sString.CompareNoCase(sStringT)) bResult = false;
	sString = "Test";
	sStringT = sString;
	if (!sString.CompareNoCase(sStringT)) bResult = false;
	sString = "Test";
	sStringT = "Tests";
	if (sString.CompareNoCase(sStringT)) bResult = false;
	sString = "Tests";
	sStringT = "Test";
	if (!sString.CompareNoCase(sStringT, 0, 4)) bResult = false;
	sString = "sTests";
	sStringT = "Test";
	if (!sString.CompareNoCase(sStringT, 1, 4)) bResult = false;
	sString = "sTests";
	sStringT = "Test";
	if (sString.CompareNoCase(sStringT, 1, 5)) bResult = false;
	if (sString.CompareNoCase(sStringT, 10)) bResult = false;
	if (sString.CompareNoCase(sStringT, 10, 5)) bResult = false;
	if (sString.CompareNoCase(sStringT, 1, 10)) bResult = false;
	if (sString.CompareNoCase(sStringT, 0, 10)) bResult = false;
	// Compare ASCII with an Unicode string
	sString = "sTests";
	sStringT = L"Test";
	if (sString.CompareNoCase(sStringT, 1, 5)) bResult = false;
	if (sString.CompareNoCase(sStringT, 10)) bResult = false;
	if (sString.CompareNoCase(sStringT, 10, 5)) bResult = false;
	if (sString.CompareNoCase(sStringT, 1, 10)) bResult = false;
	if (sString.CompareNoCase(sStringT, 0, 10)) bResult = false;
	// Compare Unicode with an ASCII string
	sString = L"sTests";
	sStringT = "Test";
	if (sString.CompareNoCase(sStringT, 1, 5)) bResult = false;
	if (sString.CompareNoCase(sStringT, 10)) bResult = false;
	if (sString.CompareNoCase(sStringT, 10, 5)) bResult = false;
	if (sString.CompareNoCase(sStringT, 1, 10)) bResult = false;
	if (sString.CompareNoCase(sStringT, 0, 10)) bResult = false;
	EndTask(bResult);

	// CompareNoCase(const char *pszString, uint32 nPos, uint32 nCount)
	StartTask("CompareNoCase(const char *pszString, uint32 nPos, uint32 nCount)");
	bResult = true;
	sString = "";
	if (!sString.CompareNoCase(static_cast<const char*>(nullptr))) bResult = false;
	sString = "";
	if (!sString.CompareNoCase("")) bResult = false;
	sString = "Test";
	if (sString.CompareNoCase(static_cast<const char*>(nullptr))) bResult = false;
	sString = "Test";
	if (sString.CompareNoCase("")) bResult = false;
	sString = "";
	if (sString.CompareNoCase("Test")) bResult = false;
	sString = "Test";
	if (!sString.CompareNoCase("Test")) bResult = false;
	if (sString.CompareNoCase("Test", 1, 10)) bResult = false;
	if (!sString.CompareNoCase("Test", 0, 10)) bResult = false;
	sString = "Test";
	if (!sString.CompareNoCase("TEst")) bResult = false;
	sString = "Test";
	if (sString.CompareNoCase("Tests")) bResult = false;
	sString = "Tests";
	if (!sString.CompareNoCase("Test", 0, 4)) bResult = false;
	sString = "sTests";
	if (!sString.CompareNoCase("Test", 1, 4)) bResult = false;
	sString = "sTests";
	if (sString.CompareNoCase("Test", 1, 5)) bResult = false;
	if (sString.CompareNoCase("Test", 10)) bResult = false;
	if (sString.CompareNoCase("Test", 10, 5)) bResult = false;
	if (sString.CompareNoCase("Test", 1, 10)) bResult = false;
	if (sString.CompareNoCase("Test", 0, 10)) bResult = false;
	// Compare Unicode with an ASCII string
	sString = L"sTests";
	if (sString.CompareNoCase("Test", 1, 5)) bResult = false;
	if (sString.CompareNoCase("Test", 10)) bResult = false;
	if (sString.CompareNoCase("Test", 10, 5)) bResult = false;
	if (sString.CompareNoCase("Test", 1, 10)) bResult = false;
	if (sString.CompareNoCase("Test", 0, 10)) bResult = false;
	EndTask(bResult);

	// CompareNoCase(const wchar_t *pszString, uint32 nPos, uint32 nCount)
	StartTask("CompareNoCase(const wchar_t *pszString, uint32 nPos, uint32 nCount)");
	bResult = true;
	sString = L"";
	if (!sString.CompareNoCase(static_cast<const wchar_t*>(nullptr))) bResult = false;
	sString = L"";
	if (!sString.CompareNoCase(L"")) bResult = false;
	sString = L"Test";
	if (sString.CompareNoCase(static_cast<const wchar_t*>(nullptr))) bResult = false;
	sString = L"Test";
	if (sString.CompareNoCase(L"")) bResult = false;
	sString = L"";
	if (sString.CompareNoCase(L"Test")) bResult = false;
	sString = L"Test";
	if (!sString.CompareNoCase(L"Test")) bResult = false;
	if (sString.CompareNoCase(L"Test", 1, 10)) bResult = false;
	if (!sString.CompareNoCase(L"Test", 0, 10)) bResult = false;
	sString = L"Test";
	if (!sString.CompareNoCase(L"TEst")) bResult = false;
	sString = L"Test";
	if (sString.CompareNoCase(L"Tests")) bResult = false;
	sString = L"Tests";
	if (!sString.CompareNoCase(L"Test", 0, 4)) bResult = false;
	sString = L"sTests";
	if (!sString.CompareNoCase(L"Test", 1, 4)) bResult = false;
	sString = L"sTests";
	if (sString.CompareNoCase(L"Test", 1, 5)) bResult = false;
	if (sString.CompareNoCase(L"Test", 10)) bResult = false;
	if (sString.CompareNoCase(L"Test", 10, 5)) bResult = false;
	if (sString.CompareNoCase(L"Test", 1, 10)) bResult = false;
	if (sString.CompareNoCase(L"Test", 0, 10)) bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (sString.CompareNoCase(L"\u65e5\u672c\u8a9e", 1, 4)) bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (!sString.CompareNoCase(L"\u672c\u8a9e", 1, 4)) bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (!sString.CompareNoCase(L"\u65e5\u672c\u8a9e", 0, 4)) bResult = false;
	// Compare ASCII with an Unicode string
	sString = "sTests";
	if (sString.CompareNoCase(L"Test", 1, 5)) bResult = false;
	if (sString.CompareNoCase(L"Test", 10)) bResult = false;
	if (sString.CompareNoCase(L"Test", 10, 5)) bResult = false;
	if (sString.CompareNoCase(L"Test", 1, 10)) bResult = false;
	if (sString.CompareNoCase(L"Test", 0, 10)) bResult = false;
	EndTask(bResult);

	// IsAlphabetic(): ASCII
	StartTask("IsAlphabetic(): ASCII");
	bResult = true;
	sString = "";
	if (sString.IsAlphabetic()) bResult = false;
	sString = ".";
	if (sString.IsAlphabetic()) bResult = false;
	sString = "46";
	if (sString.IsAlphabetic()) bResult = false;
	sString = "46.23";
	if (sString.IsAlphabetic()) bResult = false;
	sString = "46.23.7";
	if (sString.IsAlphabetic()) bResult = false;
	sString = "AbC";
	if (!sString.IsAlphabetic()) bResult = false;
	sString = "Ab-C";
	if (sString.IsAlphabetic()) bResult = false;
	sString = "Ab5C";
	if (sString.IsAlphabetic()) bResult = false;
	EndTask(bResult);

	// IsAlphabetic(): Unicode
	StartTask("IsAlphabetic(): Unicode");
	bResult = true;
	sString = L"";
	if (sString.IsAlphabetic()) bResult = false;
	sString = L".";
	if (sString.IsAlphabetic()) bResult = false;
	sString = L"46";
	if (sString.IsAlphabetic()) bResult = false;
	sString = L"46.23";
	if (sString.IsAlphabetic()) bResult = false;
	sString = L"46.23.7";
	if (sString.IsAlphabetic()) bResult = false;
	sString = L"AbC";
	if (!sString.IsAlphabetic()) bResult = false;
	sString = L"Ab-C";
	if (sString.IsAlphabetic()) bResult = false;
	sString = L"Ab5C";
	if (sString.IsAlphabetic()) bResult = false;
	sString = L"\u65e5\u672c";
	if (!sString.IsAlphabetic()) bResult = false;
	sString = L"\u65e51\u672c";
	if (sString.IsAlphabetic()) bResult = false;
	sString = L"\u65e5\u4E00\u672c";
	if (!sString.IsAlphabetic()) bResult = false;
	EndTask(bResult);

	// IsAlphaNumeric(): ASCII
	StartTask("IsAlphaNumeric(): ASCII");
	bResult = true;
	sString = "";
	if (sString.IsAlphaNumeric()) bResult = false;
	sString = ".";
	if (sString.IsAlphaNumeric()) bResult = false;
	sString = "46";
	if (!sString.IsAlphaNumeric()) bResult = false;
	sString = "46.23";
	if (sString.IsAlphaNumeric()) bResult = false;
	sString = "46.23.7";
	if (sString.IsAlphaNumeric()) bResult = false;
	sString = "AbC";
	if (!sString.IsAlphaNumeric()) bResult = false;
	sString = "Ab-C";
	if (sString.IsAlphaNumeric()) bResult = false;
	sString = "Ab5C";
	if (!sString.IsAlphaNumeric()) bResult = false;
	EndTask(bResult);

	// IsAlphaNumeric(): Unicode
	StartTask("IsAlphaNumeric(): Unicode");
	bResult = true;
	sString = L"";
	if (sString.IsAlphaNumeric()) bResult = false;
	sString = L".";
	if (sString.IsAlphaNumeric()) bResult = false;
	sString = L"46";
	if (!sString.IsAlphaNumeric()) bResult = false;
	sString = L"46.23";
	if (sString.IsAlphaNumeric()) bResult = false;
	sString = L"46.23.7";
	if (sString.IsAlphaNumeric()) bResult = false;
	sString = L"AbC";
	if (!sString.IsAlphaNumeric()) bResult = false;
	sString = L"Ab-C";
	if (sString.IsAlphaNumeric()) bResult = false;
	sString = L"Ab5C";
	if (!sString.IsAlphaNumeric()) bResult = false;
	sString = L"\u65e5\u672c";
	if (!sString.IsAlphaNumeric()) bResult = false;
	sString = L"\u65e51\u672c";
	if (!sString.IsAlphaNumeric()) bResult = false;
	sString = L"\u65e5\u4E00\u672c";
	if (!sString.IsAlphaNumeric()) bResult = false;
	EndTask(bResult);

	// IsNumeric(): ASCII
	StartTask("IsNumeric(): ASCII");
	bResult = true;
	sString = "";
	if (sString.IsNumeric()) bResult = false;
	sString = ".";
	if (sString.IsNumeric()) bResult = false;
	sString = "46";
	if (!sString.IsNumeric()) bResult = false;
	sString = "46.23";
	if (sString.IsNumeric()) bResult = false;
	sString = "46.23.7";
	if (sString.IsNumeric()) bResult = false;
	sString = "AbC";
	if (sString.IsNumeric()) bResult = false;
	sString = "Ab5C";
	if (sString.IsNumeric()) bResult = false;
	EndTask(bResult);

	// IsNumeric(): Unicode
	StartTask("IsNumeric(): Unicode");
	bResult = true;
	sString = L"";
	if (sString.IsNumeric()) bResult = false;
	sString = L".";
	if (sString.IsNumeric()) bResult = false;
	sString = L"46";
	if (!sString.IsNumeric()) bResult = false;
	sString = L"46.23";
	if (sString.IsNumeric()) bResult = false;
	sString = L"46.23.7";
	if (sString.IsNumeric()) bResult = false;
	sString = L"AbC";
	if (sString.IsNumeric()) bResult = false;
	sString = L"Ab5C";
	if (sString.IsNumeric()) bResult = false;
	sString = L"\u65e5\u672c";
	if (sString.IsNumeric()) bResult = false;
	sString = L"\u65e51\u672c";
	if (sString.IsNumeric()) bResult = false;
	sString = L"\u65e5\u4E00\u672c";
	if (sString.IsNumeric()) bResult = false;
	sString = L"1";
	if (!sString.IsNumeric()) bResult = false;
	sString = L"\u4E00";
	if (sString.IsNumeric()) bResult = false;
	EndTask(bResult);

	// IsSubstring(const String &sString)
	StartTask("IsSubstring(const String &sString)");
	sString = "";
	if (!sString.IsSubstring(String("")) || sString.IsSubstring(String("12"))) EndTask(false);
	else {
		bResult = true;
		sString = "1234";
		if (!sString.IsSubstring(String("12")))   bResult = false;
		if (!sString.IsSubstring(String("1234"))) bResult = false;
		if (!sString.IsSubstring(String("34")))   bResult = false;
		if (!sString.IsSubstring(String("")))     bResult = false;
		if (sString.IsSubstring(String("A")) || sString.IsSubstring(String("12345"))) bResult = false;
		// Compare ASCII with an Unicode string
		sString = "1234";
		if (!sString.IsSubstring(String(L"12")))   bResult = false;
		if (!sString.IsSubstring(String(L"1234"))) bResult = false;
		if (!sString.IsSubstring(String(L"34")))   bResult = false;
		if (!sString.IsSubstring(String(L"")))     bResult = false;
		// Compare Unicode with an ASCII string
		sString = L"1234";
		if (!sString.IsSubstring(String("12")))   bResult = false;
		if (!sString.IsSubstring(String("1234"))) bResult = false;
		if (!sString.IsSubstring(String("34")))   bResult = false;
		if (!sString.IsSubstring(String("")))     bResult = false;
		EndTask(bResult);
	}

	// IsSubstring(const char *pszString)
	StartTask("IsSubstring(const char *pszString)");
	sString = "";
	if (!sString.IsSubstring("") || sString.IsSubstring("12")) EndTask(false);
	else {
		bResult = true;
		sString = "1234";
		if (!sString.IsSubstring("12"))   bResult = false;
		if (!sString.IsSubstring("1234")) bResult = false;
		if (!sString.IsSubstring("34"))   bResult = false;
		if (!sString.IsSubstring(""))     bResult = false;
		if (sString.IsSubstring("A") || sString.IsSubstring("12345")) bResult = false;
		// Compare Unicode with an ASCII string
		sString = L"1234";
		if (!sString.IsSubstring("12"))   bResult = false;
		if (!sString.IsSubstring("1234")) bResult = false;
		if (!sString.IsSubstring("34"))   bResult = false;
		if (!sString.IsSubstring(""))     bResult = false;
		if (sString.IsSubstring("A") || sString.IsSubstring("12345")) bResult = false;
		EndTask(bResult);
	}

	// IsSubstring(const wchar_t *pszString)
	StartTask("IsSubstring(const wchar_t *pszString)");
	sString = L"";
	if (!sString.IsSubstring(L"") || sString.IsSubstring(L"12")) EndTask(false);
	else {
		bResult = true;
		sString = L"1234";
		if (!sString.IsSubstring(L"12"))   bResult = false;
		if (!sString.IsSubstring(L"1234")) bResult = false;
		if (!sString.IsSubstring(L"34"))   bResult = false;
		if (!sString.IsSubstring(L""))     bResult = false;
		if (sString.IsSubstring(L"A") || sString.IsSubstring(L"12345")) bResult = false;
		if (sString.IsSubstring(L"\u4E00"))    bResult = false;
		sString = L"\u65e5\u672c\u8a9e";
		if (!sString.IsSubstring(L"\u65e5\u672c\u8a9e")) bResult = false;
		if (!sString.IsSubstring(L"\u8a9e"))             bResult = false;
		if (!sString.IsSubstring(L"\u672c\u8a9e"))       bResult = false;
		if (sString.IsSubstring(L"\u65e5\u8a9e"))        bResult = false;
		// Index of ASCII with an Unicode string
		sString = "1234";
		if (!sString.IsSubstring(L"12"))   bResult = false;
		if (!sString.IsSubstring(L"1234")) bResult = false;
		if (!sString.IsSubstring(L"34"))   bResult = false;
		if (!sString.IsSubstring(L""))     bResult = false;
		EndTask(bResult);
	}

	// Check for character: ASCII
	StartTask("Check for character using GetLength() and IsSubstring(): ASCII");
	bResult = true;
	sString = "";
	if (sString.GetLength() == 1 && String("").IsSubstring(sString)) bResult = false;
	sString = "12";
	if (sString.GetLength() == 1 && String("5").IsSubstring(sString)) bResult = false;
	sString = "1";
	if (!(sString.GetLength() == 1 && String("1").IsSubstring(sString))) bResult = false;
	sString = "1";
	if (!(sString.GetLength() == 1 && String("d]16").IsSubstring(sString))) bResult = false;
	sString = "1";
	if (sString.GetLength() == 1 && String("d]6").IsSubstring(sString)) bResult = false;
	sString = "1";
	if (sString.GetLength() == 1 && String("").IsSubstring(sString)) bResult = false;
	EndTask(bResult);

	// Check for character: Unicode
	StartTask("Check for character using GetLength() and IsSubstring(): Unicode");
	bResult = true;
	sString = L"";
	if (sString.GetLength() == 1 && String(L"").IsSubstring(sString)) bResult = false;
	sString = L"12";
	if (sString.GetLength() == 1 && String(L"5").IsSubstring(sString)) bResult = false;
	sString = L"1";
	if (!(sString.GetLength() == 1 && String(L"1").IsSubstring(sString))) bResult = false;
	sString = L"1";
	if (!(sString.GetLength() == 1 && String(L"d]16").IsSubstring(sString))) bResult = false;
	sString = L"1";
	if (sString.GetLength() == 1 && String(L"d]6").IsSubstring(sString)) bResult = false;
	sString = L"1";
	if (sString.GetLength() == 1 && String(L"").IsSubstring(sString)) bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (!String(L"\u65e5\u672c\u8a9e").IsSubstring(sString)) bResult = false;
	if (!String(L"\u672c\u65e5\u672c\u8a9e\u672c").IsSubstring(sString)) bResult = false;
	if (String(L"\u672c\u8a9e\u672c").IsSubstring(sString)) bResult = false;
	if (String(L"").IsSubstring(sString)) bResult = false;
	if (String(L"\u8a9e").IsSubstring(sString)) bResult = false;
	sString = L"";
	if (!String(L"\u65e5\u672c\u8a9e").IsSubstring(sString)) bResult = false;
	EndTask(bResult);

	// IndexOf(const String &sString)
	StartTask("IndexOf(const String &sString)");
	sString = "";
	if (sString.IndexOf(String("")) >= 0 || sString.IndexOf(String("12")) >= 0) EndTask(false);
	else {
		bResult = true;
		sString = "12345634";
		if (sString.IndexOf(String("12"))    != 0) bResult = false;
		if (sString.IndexOf(String("12"), 2) >= 0) bResult = false;
		if (sString.IndexOf(String("1234"))  != 0) bResult = false;
		if (sString.IndexOf(String("34"))    != 2) bResult = false;
		if (sString.IndexOf(String("34"), 4) != 6) bResult = false;
		if (sString.IndexOf(String("34"), 8) >= 0) bResult = false;
		if (sString.IndexOf(String(""))      >= 0) bResult = false;
		if (sString.IndexOf(String("A")) >= 0 || sString.IndexOf(String("12346")) >= 0) bResult = false;
		// Index of ASCII with an Unicode string
		sString = "12345634";
		if (sString.IndexOf(String(L"12"))    != 0) bResult = false;
		if (sString.IndexOf(String(L"12"), 2) >= 0) bResult = false;
		if (sString.IndexOf(String(L"1234"))  != 0) bResult = false;
		if (sString.IndexOf(String(L"34"))    != 2) bResult = false;
		if (sString.IndexOf(String(L"34"), 4) != 6) bResult = false;
		if (sString.IndexOf(String(L"34"), 8) >= 0) bResult = false;
		if (sString.IndexOf(String(L""))      >= 0) bResult = false;
		// Index of Unicode with an ASCII string
		sString = L"12345634";
		if (sString.IndexOf(String("12"))    != 0) bResult = false;
		if (sString.IndexOf(String("12"), 2) >= 0) bResult = false;
		if (sString.IndexOf(String("1234"))  != 0) bResult = false;
		if (sString.IndexOf(String("34"))    != 2) bResult = false;
		if (sString.IndexOf(String("34"), 4) != 6) bResult = false;
		if (sString.IndexOf(String("34"), 8) >= 0) bResult = false;
		if (sString.IndexOf(String(""))      >= 0) bResult = false;
		EndTask(bResult);
	}

	// IndexOf(const char *pszString)
	StartTask("IndexOf(const char *pszString)");
	sString = "";
	if (sString.IndexOf("") >= 0 || sString.IndexOf("12") >= 0) EndTask(false);
	else {
		bResult = true;
		sString = "12345634";
		if (sString.IndexOf("12")    != 0) bResult = false;
		if (sString.IndexOf("12", 2) >= 0) bResult = false;
		if (sString.IndexOf("1234")  != 0) bResult = false;
		if (sString.IndexOf("34")    != 2) bResult = false;
		if (sString.IndexOf("34", 4) != 6) bResult = false;
		if (sString.IndexOf("34", 8) >= 0) bResult = false;
		if (sString.IndexOf(static_cast<const char*>(nullptr)) >= 0) bResult = false;
		if (sString.IndexOf("")      >= 0) bResult = false;
		if (sString.IndexOf("A") >= 0 || sString.IndexOf("12346") >= 0) bResult = false;
		// Index of Unicode with an ASCII string
		sString = L"12345634";
		if (sString.IndexOf("12")    != 0) bResult = false;
		if (sString.IndexOf("12", 2) >= 0) bResult = false;
		if (sString.IndexOf("1234")  != 0) bResult = false;
		if (sString.IndexOf("34")    != 2) bResult = false;
		if (sString.IndexOf("34", 4) != 6) bResult = false;
		if (sString.IndexOf("34", 8) >= 0) bResult = false;
		if (sString.IndexOf(static_cast<const char*>(nullptr)) >= 0) bResult = false;
		if (sString.IndexOf("")      >= 0) bResult = false;
		EndTask(bResult);
	}

	// IndexOf(const wchar_t *pszString)
	StartTask("IndexOf(const wchar_t *pszString)");
	sString = L"";
	if (sString.IndexOf(L"") >= 0 || sString.IndexOf(L"12") >= 0) EndTask(false);
	else {
		bResult = true;
		sString = L"12345634";
		if (sString.IndexOf(L"12")    != 0) bResult = false;
		if (sString.IndexOf(L"12", 2) >= 0) bResult = false;
		if (sString.IndexOf(L"1234")  != 0) bResult = false;
		if (sString.IndexOf(L"34")    != 2) bResult = false;
		if (sString.IndexOf(L"34", 4) != 6) bResult = false;
		if (sString.IndexOf(L"34", 8) >= 0) bResult = false;
		if (sString.IndexOf(static_cast<const wchar_t*>(nullptr)) >= 0) bResult = false;
		if (sString.IndexOf(L"")      >= 0) bResult = false;
		if (sString.IndexOf(L"A") >= 0 || sString.IndexOf(L"12346") >= 0) bResult = false;
		if (sString.IndexOf(L"\u65e5")    >= 0) bResult = false;
		sString = L"\u65e5\u672c\u8a9e";
		if (sString.IndexOf(L"\u65e5\u672c\u8a9e") != 0) bResult = false;
		if (sString.IndexOf(L"\u8a9e") != 2) bResult = false;
		if (sString.IndexOf(L"") >= 0)		 bResult = false;
		// Index of ASCII with an Unicode string
		sString = "12345634";
		if (sString.IndexOf(L"12")    != 0) bResult = false;
		if (sString.IndexOf(L"12", 2) >= 0) bResult = false;
		if (sString.IndexOf(L"1234")  != 0) bResult = false;
		if (sString.IndexOf(L"34")    != 2) bResult = false;
		if (sString.IndexOf(L"34", 4) != 6) bResult = false;
		if (sString.IndexOf(L"34", 8) >= 0) bResult = false;
		if (sString.IndexOf(static_cast<const wchar_t*>(nullptr)) >= 0) bResult = false;
		if (sString.IndexOf(L"")      >= 0) bResult = false;
		EndTask(bResult);
	}

	// LastIndexOf(const String &sString)
	StartTask("LastIndexOf(const String &sString)");
	sString = "";
	if (sString.LastIndexOf(String("")) >= 0 || sString.LastIndexOf(String("12")) >= 0) EndTask(false);
	else {
		bResult = true;
		sString = "1234563412";
		if (sString.LastIndexOf(String("12"))    != 8) bResult = false;
		if (sString.LastIndexOf(String("12"), 4) != 0) bResult = false;
		if (sString.LastIndexOf(String("1234"))  != 0) bResult = false;
		if (sString.LastIndexOf(String("34"))    != 6) bResult = false;
		if (sString.LastIndexOf(String("34"), 4) != 2) bResult = false;
		if (sString.LastIndexOf(String("34"), 1) >= 0) bResult = false;
		if (sString.LastIndexOf(String(""))      >= 0) bResult = false;
		if (sString.LastIndexOf(String("A")) >= 0 || sString.LastIndexOf(String("12346")) >= 0) bResult = false;
		// Index of ASCII with an Unicode string
		sString = "1234563412";
		if (sString.LastIndexOf(String(L"12"))    != 8) bResult = false;
		if (sString.LastIndexOf(String(L"12"), 4) != 0) bResult = false;
		if (sString.LastIndexOf(String(L"1234"))  != 0) bResult = false;
		if (sString.LastIndexOf(String(L"34"))    != 6) bResult = false;
		if (sString.LastIndexOf(String(L"34"), 4) != 2) bResult = false;
		if (sString.LastIndexOf(String(L"34"), 1) >= 0) bResult = false;
		if (sString.LastIndexOf(String(L""))      >= 0) bResult = false;
		// Index of Unicode with an ASCII string
		sString = L"1234563412";
		if (sString.LastIndexOf(String("12"))    != 8) bResult = false;
		if (sString.LastIndexOf(String("12"), 4) != 0) bResult = false;
		if (sString.LastIndexOf(String("1234"))  != 0) bResult = false;
		if (sString.LastIndexOf(String("34"))    != 6) bResult = false;
		if (sString.LastIndexOf(String("34"), 4) != 2) bResult = false;
		if (sString.LastIndexOf(String("34"), 1) >= 0) bResult = false;
		if (sString.LastIndexOf(String(""))      >= 0) bResult = false;
		EndTask(bResult);
	}

	// LastIndexOf(const char *pszString)
	StartTask("LastIndexOf(const char *pszString)");
	sString = "";
	if (sString.LastIndexOf("") >= 0 || sString.LastIndexOf("12") >= 0) EndTask(false);
	else {
		bResult = true;
		sString = "1234563412";
		if (sString.LastIndexOf("12")    != 8) bResult = false;
		if (sString.LastIndexOf("12", 4) != 0) bResult = false;
		if (sString.LastIndexOf("1234")  != 0) bResult = false;
		if (sString.LastIndexOf("34")    != 6) bResult = false;
		if (sString.LastIndexOf("34", 4) != 2) bResult = false;
		if (sString.LastIndexOf("34", 1) >= 0) bResult = false;
		if (sString.LastIndexOf(static_cast<const char*>(nullptr)) >= 0) bResult = false;
		if (sString.LastIndexOf("")      >= 0) bResult = false;
		if (sString.LastIndexOf("A") >= 0 || sString.LastIndexOf("12346") >= 0) bResult = false;
		// Index of Unicode with an ASCII string
		sString = L"1234563412";
		if (sString.LastIndexOf("12")    != 8) bResult = false;
		if (sString.LastIndexOf("12", 4) != 0) bResult = false;
		if (sString.LastIndexOf("1234")  != 0) bResult = false;
		if (sString.LastIndexOf("34")    != 6) bResult = false;
		if (sString.LastIndexOf("34", 4) != 2) bResult = false;
		if (sString.LastIndexOf("34", 1) >= 0) bResult = false;
		if (sString.LastIndexOf(static_cast<const char*>(nullptr)) >= 0) bResult = false;
		if (sString.LastIndexOf("")      >= 0) bResult = false;
		EndTask(bResult);
	}

	// LastIndexOf(const wchar_t *pszString)
	StartTask("LastIndexOf(const wchar_t *pszString)");
	sString = L"";
	if (sString.LastIndexOf(L"") >= 0 || sString.LastIndexOf(L"12") >= 0) EndTask(false);
	else {
		bResult = true;
		sString = L"1234563412";
		if (sString.LastIndexOf(L"12")    != 8) bResult = false;
		if (sString.LastIndexOf(L"12", 4) != 0) bResult = false;
		if (sString.LastIndexOf(L"1234")  != 0) bResult = false;
		if (sString.LastIndexOf(L"34")    != 6) bResult = false;
		if (sString.LastIndexOf(L"34", 4) != 2) bResult = false;
		if (sString.LastIndexOf(L"34", 1) >= 0) bResult = false;
		if (sString.LastIndexOf(static_cast<const wchar_t*>(nullptr)) >= 0) bResult = false;
		if (sString.LastIndexOf(L"")      >= 0) bResult = false;
		if (sString.LastIndexOf(L"A") >= 0 || sString.LastIndexOf(L"12346") >= 0) bResult = false;
		if (sString.LastIndexOf(L"\u65e5")    >= 0) bResult = false;
		sString = L"\u65e5\u672c\u8a9e";
		if (sString.LastIndexOf(L"\u65e5\u672c\u8a9e") != 0) bResult = false;
		if (sString.LastIndexOf(L"\u8a9e") != 2) bResult = false;
		if (sString.LastIndexOf(L"") >= 0)		 bResult = false;
		// Index of ASCII with an Unicode string
		sString = "1234563412";
		if (sString.LastIndexOf(L"12")    != 8) bResult = false;
		if (sString.LastIndexOf(L"12", 4) != 0) bResult = false;
		if (sString.LastIndexOf(L"1234")  != 0) bResult = false;
		if (sString.LastIndexOf(L"34")    != 6) bResult = false;
		if (sString.LastIndexOf(L"34", 4) != 2) bResult = false;
		if (sString.LastIndexOf(L"34", 1) >= 0) bResult = false;
		if (sString.LastIndexOf(static_cast<const wchar_t*>(nullptr)) >= 0) bResult = false;
		if (sString.LastIndexOf(L"")      >= 0) bResult = false;
		EndTask(bResult);
	}

	// GetSubstring(): ASCII
	StartTask("GetSubstring(): ASCII");
	sString = "";
	if (sString.GetSubstring(0).GetLength() || sString.GetSubstring(5, 5).GetLength()) EndTask(false);
	else {
		bResult = true;
		sString = "1234";
		pszTemp = sString.GetSubstring(0, 2);
		if (!pszTemp || _strnicmp(pszTemp, "12",   2)) bResult = false;
		pszTemp = sString.GetSubstring(0);
		if (!pszTemp || _strnicmp(pszTemp, "1234", 4)) bResult = false;
		pszTemp = sString.GetSubstring(2);
		if (!pszTemp || _strnicmp(pszTemp, "34",   2)) bResult = false;
		pszTemp = sString.GetSubstring(2, 4);
		if (!pszTemp || _strnicmp(pszTemp, "34",   2)) bResult = false;
		if (sString.GetSubstring(5).GetLength()) bResult = false;
		EndTask(bResult);
	}

	// GetSubstring(): Unicode
	StartTask("GetSubstring(): Unicode");
	sString = L"";
	if (sString.GetSubstring(0).GetLength() || sString.GetSubstring(5, 5).GetLength()) EndTask(false);
	else {
		bResult = true;
		sString = L"1234";
		pszTempWide = sString.GetSubstring(0, 2);
		if (!pszTempWide || _wcsnicmp(pszTempWide, L"12",   2)) bResult = false;
		pszTempWide = sString.GetSubstring(0);
		if (!pszTempWide || _wcsnicmp(pszTempWide, L"1234", 4)) bResult = false;
		pszTempWide = sString.GetSubstring(2);
		if (!pszTempWide || _wcsnicmp(pszTempWide, L"34",   2)) bResult = false;
		pszTempWide = sString.GetSubstring(2, 4);
		if (!pszTempWide || _wcsnicmp(pszTempWide, L"34",   2)) bResult = false;
		if (sString.GetSubstring(5).GetLength()) bResult = false;
		sString = L"\u65e5\u672c\u8a9e";
		pszTempWide = sString.GetSubstring(0, 2);
		if (!pszTempWide || _wcsnicmp(pszTempWide, L"\u65e5\u672c", 2)) bResult = false;
		pszTempWide = sString.GetSubstring(1, 2);
		if (!pszTempWide || _wcsnicmp(pszTempWide, L"\u672c\u8a9e", 2)) bResult = false;
		pszTempWide = sString.GetSubstring(1, 1);
		if (!pszTempWide || _wcsnicmp(pszTempWide, L"\u672c",       1)) bResult = false;
		EndTask(bResult);
	}

	// ToLower(): ASCII
	StartTask("ToLower(): ASCII");
	bResult = true;
	sString = "";
	if (sString.ToLower().GetLength()) bResult = false;
	sString = "56";
	if (sString.ToLower() != "56") bResult = false;
	sString = "AbcDE";
	if (sString.ToLower() != "abcde") bResult = false;
	sString = "Ab23cD!E";
	if (sString.ToLower() != "ab23cd!e") bResult = false;
	EndTask(bResult);

	// ToLower(): Unicode
	StartTask("ToLower(): Unicode");
	bResult = true;
	sString = L"";
	if (sString.ToLower().GetLength()) bResult = false;
	sString = L"56";
	if (sString.ToLower() != L"56") bResult = false;
	sString = L"AbcDE";
	if (sString.ToLower() != L"abcde") bResult = false;
	sString = L"Ab23cD!E";
	if (sString.ToLower() != L"ab23cd!e") bResult = false;
	sString = L"\u65e5";
	if (sString.ToLower() != L"\u65e5") bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (sString.ToLower() != L"\u65e5\u672c\u8a9e") bResult = false;
	EndTask(bResult);

	// ToUpper(): ASCII
	StartTask("ToUpper(): ASCII");
	bResult = true;
	sString = "";
	if (sString.ToUpper().GetLength()) bResult = false;
	sString = "56";
	if (sString.ToUpper() != "56") bResult = false;
	sString = "AbcDE";
	if (sString.ToUpper() != "ABCDE") bResult = false;
	sString = "Ab23cD!E";
	if (sString.ToUpper() != "AB23CD!E") bResult = false;
	EndTask(bResult);

	// ToUpper(): Unicode
	StartTask("ToUpper(): Unicode");
	bResult = true;
	sString = L"";
	if (sString.ToUpper().GetLength()) bResult = false;
	sString = L"56";
	if (sString.ToUpper() != L"56") bResult = false;
	sString = L"AbcDE";
	if (sString.ToUpper() != L"ABCDE") bResult = false;
	sString = L"Ab23cD!E";
	if (sString.ToUpper() != L"AB23CD!E") bResult = false;
	sString = L"\u65e5";
	if (sString.ToUpper() != L"\u65e5") bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (sString.ToUpper() != L"\u65e5\u672c\u8a9e") bResult = false;
	EndTask(bResult);

	// Delete(uint32 nPos, uint32 nCount): ASCII
	StartTask("Delete(uint32 nPos, uint32 nCount): ASCII");
	bResult = true;
	sString = "";
	if (sString.Delete().GetLength()) bResult = false;
	if (sString.Delete(5, 5).GetLength()) bResult = false;
	sString = "1";
	if (sString.Delete().GetLength()) bResult = false;
	sString = "123";
	if (sString.Delete(1, 1) != "13") bResult = false;
	if (sString.Delete(0, 1) != "3") bResult = false;
	sString = "1234";
	if (sString.Delete(0, 2) != "34") bResult = false;
	sString = "12345";
	if (sString.Delete(0, 2) != "345") bResult = false;
	sString = "1234";
	if (sString.Delete(5, 1) != "1234") bResult = false;
	if (sString.Delete(sString.GetLength()-1, 1) != "123") bResult = false;
	if (sString.Delete(0, 10).GetLength()) bResult = false;
	EndTask(bResult);

	// Delete(uint32 nPos, uint32 nCount): Unicode
	StartTask("Delete(uint32 nPos, uint32 nCount): Unicode");
	bResult = true;
	sString = L"";
	if (sString.Delete().GetLength()) bResult = false;
	if (sString.Delete(5, 5).GetLength()) bResult = false;
	sString = L"1";
	if (sString.Delete().GetLength()) bResult = false;
	sString = L"123";
	if (sString.Delete(1, 1) != L"13") bResult = false;
	if (sString.Delete(0, 1) != L"3") bResult = false;
	sString = L"1234";
	if (sString.Delete(0, 2) != L"34") bResult = false;
	sString = L"12345";
	if (sString.Delete(0, 2) != L"345") bResult = false;
	sString = L"1234";
	if (sString.Delete(5, 1) != L"1234") bResult = false;
	if (sString.Delete(sString.GetLength()-1, 1) != L"123") bResult = false;
	if (sString.Delete(0, 10).GetLength()) bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (sString.Delete(0, 2) != L"\u8a9e") bResult = false;
	sString = L"\u8a9e";
	if (sString.Delete(0) != L"") bResult = false;
	sString = L"\u65e5\u672c\u8a9e";
	if (sString.Delete(2, 2) != L"\u65e5\u672c") bResult = false;
	EndTask(bResult);

	// Insert(const String &sString, uint32 nPos, uint32 nCount)
	StartTask("Insert(const String &sString, uint32 nPos, uint32 nCount)");
	bResult = true;
	sString = "";
	if (sString.Insert(String("")).GetLength()) bResult = false;
	if (sString.Insert(String("12"), 5).GetLength()) bResult = false;
	if (sString.Insert(String("12"), 0, 5) != "12") bResult = false;
	if (sString.Insert(String("0 ")) != "0 12") bResult = false;
	if (sString.Insert(String("34"), sString.GetLength()) != "0 1234") bResult = false;
	if (sString.Insert(String(""), 2, 10) != "0 1234") bResult = false;
	if (sString.Insert(String(" 2.5 "), 4) != "0 12 2.5 34") bResult = false;
	sString = "";
	if (sString.Insert(String("Data/"), 0, 4).GetLength() != 4 || sString != "Data") bResult = false;
	// Insert Unicode into an ASCII string
	sString = "";
	if (sString.Insert(String(L"")).GetLength()) bResult = false;
	if (sString.Insert(String(L"12"), 5).GetLength()) bResult = false;
	if (sString.Insert(String(L"12"), 0, 5) != "12") bResult = false;
	if (sString.Insert(String(L"0 ")) != "0 12") bResult = false;
	if (sString.Insert(String(L"34"), sString.GetLength()) != "0 1234") bResult = false;
	if (sString.Insert(String(L""), 2, 10) != "0 1234") bResult = false;
	if (sString.Insert(String(L" 2.5 "), 4) != "0 12 2.5 34") bResult = false;
	if (sString.GetFormat() != String::Unicode) bResult = false;
	// Insert ASCII into an Unicode string
	sString = L"";
	if (sString.Insert(String("")).GetLength()) bResult = false;
	if (sString.Insert(String("12"), 5).GetLength()) bResult = false;
	if (sString.Insert(String("12"), 0, 5) != "12") bResult = false;
	if (sString.Insert(String("0 ")) != "0 12") bResult = false;
	if (sString.Insert(String("34"), sString.GetLength()) != "0 1234") bResult = false;
	if (sString.Insert(String(""), 2, 10) != "0 1234") bResult = false;
	if (sString.Insert(String(" 2.5 "), 4) != "0 12 2.5 34") bResult = false;
	if (sString.GetFormat() != String::ASCII) bResult = false;
	sString = L"12";
	if (sString.Insert(String("Hi")).GetLength() != 4) bResult = false;
	if (sString.GetFormat() != String::Unicode) bResult = false;
	EndTask(bResult);

	// Insert(const char *pszString, uint32 nPos, uint32 nCount)
	StartTask("Insert(const char *pszString, uint32 nPos, uint32 nCount)");
	bResult = true;
	sString = "";
	if (sString.Insert(static_cast<const char*>(nullptr)).GetLength()) bResult = false;
	if (sString.Insert("").GetLength()) bResult = false;
	if (sString.Insert("12", 5).GetLength()) bResult = false;
	if (sString.Insert("12", 0, 5) != "12") bResult = false;
	if (sString.Insert("0 ") != "0 12") bResult = false;
	if (sString.Insert("34", sString.GetLength()) != "0 1234") bResult = false;
	if (sString.Insert("", 2, 10) != "0 1234") bResult = false;
	if (sString.Insert(" 2.5 ", 4) != "0 12 2.5 34") bResult = false;
	// Insert ASCII into an Unicode string
	sString = L"";
	if (sString.Insert(static_cast<const char*>(nullptr)).GetLength()) bResult = false;
	if (sString.Insert("").GetLength()) bResult = false;
	if (sString.Insert("12", 5).GetLength()) bResult = false;
	if (sString.Insert("12", 0, 5) != "12") bResult = false;
	if (sString.Insert("0 ") != "0 12") bResult = false;
	if (sString.Insert("34", sString.GetLength()) != "0 1234") bResult = false;
	if (sString.Insert("", 2, 10) != "0 1234") bResult = false;
	if (sString.Insert(" 2.5 ", 4) != "0 12 2.5 34") bResult = false;
	if (sString.GetFormat() != String::ASCII) bResult = false;
	sString = L"12";
	if (sString.Insert("Hi").GetLength() != 4) bResult = false;
	if (sString.GetFormat() != String::Unicode) bResult = false;
	EndTask(bResult);

	// Insert(const wchar_t *pszString, uint32 nPos, uint32 nCount)
	StartTask("Insert(const wchar_t *pszString, uint32 nPos, uint32 nCount)");
	bResult = true;
	sString = L"";
	if (sString.Insert(static_cast<const wchar_t*>(nullptr)).GetLength()) bResult = false;
	if (sString.Insert(L"").GetLength()) bResult = false;
	if (sString.Insert(L"12", 5).GetLength()) bResult = false;
	if (sString.Insert(L"12", 0, 5) != L"12") bResult = false;
	if (sString.Insert(L"0 ") != L"0 12") bResult = false;
	if (sString.Insert(L"34", sString.GetLength()) != L"0 1234") bResult = false;
	if (sString.Insert(L"", 2, 10) != L"0 1234") bResult = false;
	if (sString.Insert(L" 2.5 ", 4) != L"0 12 2.5 34") bResult = false;
	sString = L"";
	if (sString.Insert(L"\u65e5\u672c\u8a9e") != L"\u65e5\u672c\u8a9e") bResult = false;
	if (sString.Insert(L"\u65e5\u672c\u8a9e") != L"\u65e5\u672c\u8a9e\u65e5\u672c\u8a9e") bResult = false;
	// Insert Unicode into an ASCII string
	sString = "";
	if (sString.Insert(static_cast<const wchar_t*>(nullptr)).GetLength()) bResult = false;
	if (sString.Insert(L"").GetLength()) bResult = false;
	if (sString.Insert(L"12", 5).GetLength()) bResult = false;
	if (sString.Insert(L"12", 0, 5) != L"12") bResult = false;
	if (sString.Insert(L"0 ") != L"0 12") bResult = false;
	if (sString.Insert(L"34", sString.GetLength()) != L"0 1234") bResult = false;
	if (sString.Insert(L"", 2, 10) != L"0 1234") bResult = false;
	if (sString.Insert(L" 2.5 ", 4) != L"0 12 2.5 34") bResult = false;
	if (sString.GetFormat() != String::Unicode) bResult = false;
	EndTask(bResult);

	// Copy(const char *pszString, uint32 nCount)
	StartTask("Copy(const char *pszString, uint32 nCount)");
	bResult = true;
	pszTemp = " Ab_1 2 ";
	sString.Copy(static_cast<const char*>(nullptr));
	if (sString.GetLength()) bResult = false;
	sString.Copy(pszTemp);
	if (sString != pszTemp) bResult = false;
	sString.Copy(pszTemp, 3);
	if (sString != " Ab") bResult = false;
	sString.Copy(pszTemp+3, 3);
	if (sString != "_1 ") bResult = false;
	EndTask(bResult);

	// Copy(const wchar_t *pszString, uint32 nCount)
	StartTask("Copy(const wchar_t *pszString, uint32 nCount)");
	bResult = true;
	pszTempWide = L" Ab_1 2 ";
	sString.Copy(static_cast<const wchar_t*>(nullptr));
	if (sString.GetLength()) bResult = false;
	sString.Copy(pszTempWide);
	if (sString != pszTempWide) bResult = false;
	sString.Copy(pszTempWide, 3);
	if (sString != L" Ab") bResult = false;
	sString.Copy(pszTempWide+3, 3);
	if (sString != L"_1 ") bResult = false;
	EndTask(bResult);

	// Replace(char nOld, char nNew)
	StartTask("Replace(char nOld, char nNew)");
	bResult = true;
	sString = "";
	if (sString.Replace(' ', ' ') || sString != "") bResult = false;
	sString = "1234";
	if (sString.Replace(' ', '5') || sString != "1234") bResult = false;
	sString = "123141";
	if (sString.Replace('1', '1') != 0 || sString != "123141") bResult = false;
	sString = "123141";
	if (sString.Replace('1', '_') != 3 || sString != "_23_4_") bResult = false;
	sString = "__123141";
	if (sString.Replace('1', '_') != 3 || sString != "___23_4_") bResult = false;
	sString = "|";
	if (sString.Replace('|', '+') != 1 || sString != "+") bResult = false;
	sString = "|<>";
	if (sString.Replace('|', '+') != 1 || sString != "+<>") bResult = false;
	sString = "<>|";
	if (sString.Replace('|', '+') != 1 || sString != "<>+") bResult = false;
	sString = "<>||";
	if (sString.Replace('|', '+') != 2 || sString != "<>++") bResult = false;
	sString = "<|>||";
	if (sString.Replace('|', '+') != 3 || sString != "<+>++") bResult = false;
	sString = "<>|<>";
	if (sString.Replace('|', '+') != 1 || sString != "<>+<>") bResult = false;
	sString = "<>|<>|<>";
	if (sString.Replace('|', '+') != 2 || sString != "<>+<>+<>") bResult = false;
	// Replace ASCII within an Unicode string
	sString = L"";
	if (sString.Replace(' ', ' ') || sString.GetFormat() != String::ASCII || sString != L"") bResult = false;
	sString = L"1234";
	if (sString.Replace(' ', '5') || sString.GetFormat() != String::Unicode || sString != L"1234") bResult = false;
	sString = L"123141";
	if (sString.Replace('1', '1') != 0 || sString.GetFormat() != String::Unicode || sString != L"123141") bResult = false;
	sString = L"123141";
	if (sString.Replace('1', '_') != 3 || sString.GetFormat() != String::Unicode || sString != L"_23_4_") bResult = false;
	sString = L"__123141";
	if (sString.Replace('1', '_') != 3 || sString.GetFormat() != String::Unicode || sString != L"___23_4_") bResult = false;
	sString = L"|";
	if (sString.Replace('|', '+') != 1 || sString.GetFormat() != String::Unicode || sString != L"+") bResult = false;
	sString = L"|<>";
	if (sString.Replace('|', '+') != 1 || sString.GetFormat() != String::Unicode || sString != L"+<>") bResult = false;
	sString = L"<>|";
	if (sString.Replace('|', '+') != 1 || sString.GetFormat() != String::Unicode || sString != L"<>+") bResult = false;
	sString = L"<>||";
	if (sString.Replace('|', '+') != 2 || sString.GetFormat() != String::Unicode || sString != L"<>++") bResult = false;
	sString = L"<|>||";
	if (sString.Replace('|', '+') != 3 || sString.GetFormat() != String::Unicode || sString != L"<+>++") bResult = false;
	sString = L"<>|<>";
	if (sString.Replace('|', '+') != 1 || sString.GetFormat() != String::Unicode || sString != L"<>+<>") bResult = false;
	sString = L"<>|<>|<>";
	if (sString.Replace('|', '+') != 2 || sString.GetFormat() != String::Unicode || sString != L"<>+<>+<>") bResult = false;
	EndTask(bResult);

	// Replace(wchar_t nOld, wchar_t nNew)
	StartTask("Replace(wchar_t nOld, wchar_t nNew)");
	bResult = true;
	sString = L"";
	if (sString.Replace(L' ', L' ') || sString != L"") bResult = false;
	sString = L"1234";
	if (sString.Replace(L' ', L'5') || sString != L"1234") bResult = false;
	sString = L"123141";
	if (sString.Replace(L'1', L'1') != 0 || sString != L"123141") bResult = false;
	sString = L"123141";
	if (sString.Replace(L'1', L'_') != 3 || sString != L"_23_4_") bResult = false;
	sString = L"__123141";
	if (sString.Replace(L'1', L'_') != 3 || sString != L"___23_4_") bResult = false;
	sString = L"|";
	if (sString.Replace(L'|', L'+') != 1 || sString != L"+") bResult = false;
	sString = L"|<>";
	if (sString.Replace(L'|', L'+') != 1 || sString != L"+<>") bResult = false;
	sString = L"<>|";
	if (sString.Replace(L'|', L'+') != 1 || sString != L"<>+") bResult = false;
	sString = L"<>||";
	if (sString.Replace(L'|', L'+') != 2 || sString != L"<>++") bResult = false;
	sString = L"<|>||";
	if (sString.Replace(L'|', L'+') != 3 || sString != L"<+>++") bResult = false;
	sString = L"<>|<>";
	if (sString.Replace(L'|', L'+') != 1 || sString != L"<>+<>") bResult = false;
	sString = L"<>|<>|<>";
	if (sString.Replace(L'|', L'+') != 2 || sString != L"<>+<>+<>") bResult = false;
	sString = L"<>|<>|<>";
	if (sString.Replace(L'|', L'\u672c') != 2 || sString != L"<>\u672c<>\u672c<>") bResult = false;
	// Replace Unicode within an ASCII string
	sString = "";
	if (sString.Replace(L' ', L' ') || sString.GetFormat() != String::ASCII || sString != L"") bResult = false;
	sString = "1234";
	if (sString.Replace(L' ', L'5') || sString.GetFormat() != String::ASCII || sString != L"1234") bResult = false;
	sString = "123141";
	if (sString.Replace(L'1', L'1') != 0 || sString.GetFormat() != String::ASCII || sString != L"123141") bResult = false;
	sString = "123141";
	if (sString.Replace(L'1', L'_') != 3 || sString.GetFormat() != String::Unicode || sString != L"_23_4_") bResult = false;
	sString = "__123141";
	if (sString.Replace(L'1', L'_') != 3 || sString.GetFormat() != String::Unicode || sString != L"___23_4_") bResult = false;
	sString = "|";
	if (sString.Replace(L'|', L'+') != 1 || sString.GetFormat() != String::Unicode || sString != L"+") bResult = false;
	sString = "|<>";
	if (sString.Replace(L'|', L'+') != 1 || sString.GetFormat() != String::Unicode || sString != L"+<>") bResult = false;
	sString = "<>|";
	if (sString.Replace(L'|', L'+') != 1 || sString.GetFormat() != String::Unicode || sString != L"<>+") bResult = false;
	sString = "<>||";
	if (sString.Replace(L'|', L'+') != 2 || sString.GetFormat() != String::Unicode || sString != L"<>++") bResult = false;
	sString = "<|>||";
	if (sString.Replace(L'|', L'+') != 3 || sString.GetFormat() != String::Unicode || sString != L"<+>++") bResult = false;
	sString = "<>|<>";
	if (sString.Replace(L'|', L'+') != 1 || sString.GetFormat() != String::Unicode || sString != L"<>+<>") bResult = false;
	sString = "<>|<>|<>";
	if (sString.Replace(L'|', L'+') != 2 || sString.GetFormat() != String::Unicode || sString != L"<>+<>+<>") bResult = false;
	EndTask(bResult);

	// Replace(const String &sOld, const String &sNew)
	StartTask("Replace(const String &sOld, const String &sNew)");
	bResult = true;
	sString = "";
	if (sString.Replace(String(' '), String(' ')) || sString != "") bResult = false;
	sString = "1234";
	if (sString.Replace(String(' '), String('5')) || sString != "1234") bResult = false;
	sString = "123141";
	if (sString.Replace(String('1'), String('1')) != 0 || sString != "123141") bResult = false;
	sString = "123141";
	if (sString.Replace(String('1'), String('_')) != 3 || sString != "_23_4_") bResult = false;
	sString = "__123141";
	if (sString.Replace(String('1'), String('_')) != 3 || sString != "___23_4_") bResult = false;
	sString = "123412";
	if (sString.Replace(String("12"), String("12")) != 0 || sString != "123412") bResult = false;
	sString = "123412";
	if (sString.Replace(String("12"), String("1")) != 2 || sString != "1341") bResult = false;
	sString = "51123412";
	if (sString.Replace(String("12"), String("1_2")) != 2 || sString != "511_2341_2") bResult = false;
	sString = "123412";
	if (sString.Replace(String("123412"), String("")) != 1 || sString != "") bResult = false;
	sString = "Test 123412 This";
	if (sString.Replace(String("ahoioi"), String("nope")) != 0 || sString != "Test 123412 This") bResult = false;
	sString = "<>|<>";
	if (sString.Replace(String("|"), String("Hi")) != 1 || sString != "<>Hi<>") bResult = false;
	sString = "<>|<>|<>";
	if (sString.Replace(String("|"), String("Hi")) != 2 || sString != "<>Hi<>Hi<>") bResult = false;
	sString = "<++++>";
	if (sString.Replace(String("++"), String("+")) != 2 || sString != "<++>") bResult = false;
	// Replace ASCII within an Unicode string
	sString = L"";
	if (sString.Replace(String(' '), String(' ')) || sString.GetFormat() != String::ASCII || sString != "") bResult = false;
	sString = L"1234";
	if (sString.Replace(String(' '), String('5')) || sString.GetFormat() != String::Unicode || sString != "1234") bResult = false;
	sString = L"123141";
	if (sString.Replace(String('1'), String('1')) != 0 || sString.GetFormat() != String::Unicode || sString != "123141") bResult = false;
	sString = L"123141";
	if (sString.Replace(String('1'), String('_')) != 3 || sString.GetFormat() != String::Unicode || sString != "_23_4_") bResult = false;
	sString = L"__123141";
	if (sString.Replace(String('1'), String('_')) != 3 || sString.GetFormat() != String::Unicode || sString != "___23_4_") bResult = false;
	sString = L"123412";
	if (sString.Replace(String("12"), String("12")) != 0 || sString.GetFormat() != String::Unicode || sString != "123412") bResult = false;
	sString = L"123412";
	if (sString.Replace(String("12"), String("1")) != 2 || sString.GetFormat() != String::Unicode || sString != "1341") bResult = false;
	sString = L"51123412";
	if (sString.Replace(String("12"), String("1_2")) != 2 || sString.GetFormat() != String::Unicode || sString != "511_2341_2") bResult = false;
	sString = L"123412";
	if (sString.Replace(String("123412"), String("")) != 1 || sString.GetFormat() != String::ASCII || sString != "") bResult = false;
	sString = L"Test 123412 This";
	if (sString.Replace(String("ahoioi"), String("nope")) != 0 || sString.GetFormat() != String::Unicode || sString != "Test 123412 This") bResult = false;
	sString = L"<>|<>";
	if (sString.Replace(String("|"), String("Hi")) != 1 || sString.GetFormat() != String::Unicode || sString != "<>Hi<>") bResult = false;
	sString = L"<>|<>|<>";
	if (sString.Replace(String("|"), String("Hi")) != 2 || sString.GetFormat() != String::Unicode || sString != "<>Hi<>Hi<>") bResult = false;
	sString = L"<++++>";
	if (sString.Replace(String("++"), String("+")) != 2 || sString.GetFormat() != String::Unicode || sString != "<++>") bResult = false;
	// Replace Unicode within an ASCII string
	sString = "";
	if (sString.Replace(String(L' '), String(L' ')) || sString.GetFormat() != String::ASCII || sString != "") bResult = false;
	sString = "1234";
	if (sString.Replace(String(' '), String(L'5')) || sString.GetFormat() != String::ASCII || sString != "1234") bResult = false;
	sString = "123141";
	if (sString.Replace(String(L'1'), String(L'1')) != 0 || sString.GetFormat() != String::ASCII || sString != L"123141") bResult = false;
	sString = "123141";
	if (sString.Replace(String(L'1'), String('_')) != 3 || sString.GetFormat() != String::Unicode || sString != L"_23_4_") bResult = false;
	sString = "__123141";
	if (sString.Replace(String(L'1'), String(L'_')) != 3 || sString.GetFormat() != String::Unicode || sString != L"___23_4_") bResult = false;
	sString = "123412";
	if (sString.Replace(String(L"12"), String(L"12")) != 0 || sString.GetFormat() != String::ASCII || sString != L"123412") bResult = false;
	sString = "123412";
	if (sString.Replace(String("12"), String(L"1")) != 2 || sString.GetFormat() != String::Unicode || sString != L"1341") bResult = false;
	sString = "51123412";
	if (sString.Replace(String(L"12"), String(L"1_2")) != 2 || sString.GetFormat() != String::Unicode || sString != L"511_2341_2") bResult = false;
	sString = "123412";
	if (sString.Replace(String(L"123412"), String("")) != 1 || sString.GetFormat() != String::ASCII || sString != "") bResult = false;
	sString = "Test 123412 This";
	if (sString.Replace(String("ahoioi"), String(L"nope")) != 0 || sString.GetFormat() != String::ASCII || sString != "Test 123412 This") bResult = false;
	sString = "<>|<>";
	if (sString.Replace(String(L"|"), String("Hi")) != 1 || sString.GetFormat() != String::Unicode || sString != L"<>Hi<>") bResult = false;
	sString = "<>|<>|<>";
	if (sString.Replace(String("|"), String(L"Hi")) != 2 || sString.GetFormat() != String::Unicode || sString != L"<>Hi<>Hi<>") bResult = false;
	sString = "<++++>";
	if (sString.Replace(String(L"++"), String(L"+")) != 2 || sString.GetFormat() != String::Unicode || sString != L"<++>") bResult = false;
	EndTask(bResult);

	// Replace(const char *pszOld, const char *pszNew)
	StartTask("Replace(const char *pszOld, const char *pszNew)");
	bResult = true;
	sString = "";
	if (sString.Replace(static_cast<const char*>(nullptr), nullptr) || sString != "") bResult = false;
	sString = "";
	if (sString.Replace(" ", static_cast<const char*>(nullptr)) || sString != "") bResult = false;
	sString = "";
	if (sString.Replace(static_cast<const char*>(nullptr), " ") || sString != "") bResult = false;
	sString = "";
	if (sString.Replace(" ", " ") || sString != "") bResult = false;
	sString = "1234";
	if (sString.Replace(" ", "5") || sString != "1234") bResult = false;
	sString = "123141";
	if (sString.Replace("1", "1") != 0 || sString != "123141") bResult = false;
	sString = "123141";
	if (sString.Replace(static_cast<const char*>(nullptr), "_") || sString != "123141") bResult = false;
	sString = "123141";
	if (sString.Replace("1", static_cast<const char*>(nullptr)) != 3 || sString != "234") bResult = false;
	sString = "123141";
	if (sString.Replace("1", "_") != 3 || sString != "_23_4_") bResult = false;
	sString = "__123141";
	if (sString.Replace("1", "_") != 3 || sString != "___23_4_") bResult = false;
	sString = "123412";
	if (sString.Replace("12", "12") != 0 || sString != "123412") bResult = false;
	sString = "123412";
	if (sString.Replace("12", "1") != 2 || sString != "1341") bResult = false;
	sString = "51123412";
	if (sString.Replace("12", "1_2") != 2 || sString != "511_2341_2") bResult = false;
	sString = "123412";
	if (sString.Replace("123412", "") != 1 || sString != "") bResult = false;
	sString = "Test 123412 This";
	if (sString.Replace("ahoioi", "nope") != 0 || sString != "Test 123412 This") bResult = false;
	sString = "<>|<>";
	if (sString.Replace("|", "Hi") != 1 || sString != "<>Hi<>") bResult = false;
	sString = "<>|<>|<>";
	if (sString.Replace("|", "Hi") != 2 || sString != "<>Hi<>Hi<>") bResult = false;
	sString = "<++++>";
	if (sString.Replace("++", "+") != 2 || sString != "<++>") bResult = false;
	// Replace ASCII within an Unicode string
	sString = L"";
	if (sString.Replace(static_cast<const char*>(nullptr), nullptr) || sString.GetFormat() != String::ASCII || sString != "") bResult = false;
	sString = L"";
	if (sString.Replace(" ", static_cast<const char*>(nullptr)) || sString.GetFormat() != String::ASCII || sString != "") bResult = false;
	sString = L"";
	if (sString.Replace(static_cast<const char*>(nullptr), " ") || sString.GetFormat() != String::ASCII || sString != "") bResult = false;
	sString = L"";
	if (sString.Replace(" ", " ") || sString.GetFormat() != String::ASCII || sString != "") bResult = false;
	sString = L"1234";
	if (sString.Replace(" ", "5") || sString.GetFormat() != String::Unicode || sString != "1234") bResult = false;
	sString = L"123141";
	if (sString.Replace("1", "1") != 0 || sString.GetFormat() != String::Unicode || sString != "123141") bResult = false;
	sString = L"123141";
	if (sString.Replace(static_cast<const char*>(nullptr), "_") || sString.GetFormat() != String::Unicode || sString != "123141") bResult = false;
	sString = L"123141";
	if (sString.Replace("1", static_cast<const char*>(nullptr)) != 3 || sString.GetFormat() != String::Unicode || sString != L"234") bResult = false;
	sString = L"123141";
	if (sString.Replace("1", "_") != 3 || sString.GetFormat() != String::Unicode || sString != L"_23_4_") bResult = false;
	sString = L"__123141";
	if (sString.Replace("1", "_") != 3 || sString.GetFormat() != String::Unicode || sString != L"___23_4_") bResult = false;
	sString = L"123412";
	if (sString.Replace("12", "12") != 0 || sString.GetFormat() != String::Unicode || sString != "123412") bResult = false;
	sString = L"123412";
	if (sString.Replace("12", "1") != 2 || sString.GetFormat() != String::Unicode || sString != L"1341") bResult = false;
	sString = L"51123412";
	if (sString.Replace("12", "1_2") != 2 || sString.GetFormat() != String::Unicode || sString != L"511_2341_2") bResult = false;
	sString = L"123412";
	if (sString.Replace("123412", "") != 1 || sString.GetFormat() != String::ASCII || sString != "") bResult = false;
	sString = L"Test 123412 This";
	if (sString.Replace("ahoioi", "nope") != 0 || sString.GetFormat() != String::Unicode || sString != "Test 123412 This") bResult = false;
	sString = L"<>|<>";
	if (sString.Replace("|", "Hi") != 1 || sString.GetFormat() != String::Unicode || sString != L"<>Hi<>") bResult = false;
	sString = L"<>|<>|<>";
	if (sString.Replace("|", "Hi") != 2 || sString.GetFormat() != String::Unicode || sString != L"<>Hi<>Hi<>") bResult = false;
	sString = L"<++++>";
	if (sString.Replace("++", "+") != 2 || sString.GetFormat() != String::Unicode || sString != L"<++>") bResult = false;
	EndTask(bResult);

	// Replace(const wchar_t *pszOld, const wchar_t *pszNew)
	StartTask("Replace(const wchar_t *pszOld, const wchar_t *pszNew)");
	bResult = true;
	sString = L"";
	if (sString.Replace(static_cast<const wchar_t*>(nullptr), nullptr) || sString != L"") bResult = false;
	sString = L"";
	if (sString.Replace(L" ", static_cast<const wchar_t*>(nullptr)) || sString != L"") bResult = false;
	sString = L"";
	if (sString.Replace(static_cast<const wchar_t*>(nullptr), L" ") || sString != L"") bResult = false;
	sString = L"";
	if (sString.Replace(L" ", L" ") || sString != L"") bResult = false;
	sString = L"1234";
	if (sString.Replace(L" ", L"5") || sString != L"1234") bResult = false;
	sString = L"123141";
	if (sString.Replace(L"1", L"1") != 0 || sString != L"123141") bResult = false;
	sString = L"123141";
	if (sString.Replace(static_cast<const wchar_t*>(nullptr), L"_") || sString != L"123141") bResult = false;
	sString = L"123141";
	if (sString.Replace(L"1", static_cast<const wchar_t*>(nullptr)) != 3 || sString != L"234") bResult = false;
	sString = L"123141";
	if (sString.Replace(L"1", L"_") != 3 || sString != L"_23_4_") bResult = false;
	sString = L"__123141";
	if (sString.Replace(L"1", L"_") != 3 || sString != L"___23_4_") bResult = false;
	sString = L"123412";
	if (sString.Replace(L"12", L"12") != 0 || sString != L"123412") bResult = false;
	sString = L"123412";
	if (sString.Replace(L"12", L"1") != 2 || sString != L"1341") bResult = false;
	sString = L"51123412";
	if (sString.Replace(L"12", L"1_2") != 2 || sString != L"511_2341_2") bResult = false;
	sString = L"123412";
	if (sString.Replace(L"123412", L"") != 1 || sString != L"") bResult = false;
	sString = L"Test 123412 This";
	if (sString.Replace(L"ahoioi", L"nope") != 0 || sString != L"Test 123412 This") bResult = false;
	sString = L"<>|<>";
	if (sString.Replace(L"|", L"Hi") != 1 || sString != L"<>Hi<>") bResult = false;
	sString = L"<>|<>|<>";
	if (sString.Replace(L"|", L"Hi") != 2 || sString != L"<>Hi<>Hi<>") bResult = false;
	sString = L"<++++>";
	if (sString.Replace(L"++", L"+") != 2 || sString != L"<++>") bResult = false;
	sString = L"<++++>";
	if (sString.Replace(L"++", L"\u672c") != 2 || sString != L"<\u672c\u672c>") bResult = false;
	// Replace Unicode within an ASCII string
	sString = "";
	if (sString.Replace(static_cast<const wchar_t*>(nullptr), nullptr) || sString.GetFormat() != String::ASCII || sString != L"") bResult = false;
	sString = "";
	if (sString.Replace(L" ", static_cast<const wchar_t*>(nullptr)) || sString.GetFormat() != String::ASCII || sString != L"") bResult = false;
	sString = "";
	if (sString.Replace(static_cast<const wchar_t*>(nullptr), L" ") || sString.GetFormat() != String::ASCII || sString != L"") bResult = false;
	sString = "";
	if (sString.Replace(L" ", L" ") || sString.GetFormat() != String::ASCII || sString != L"") bResult = false;
	sString = "1234";
	if (sString.Replace(L" ", L"5") || sString.GetFormat() != String::ASCII || sString != L"1234") bResult = false;
	sString = "123141";
	if (sString.Replace(L"1", L"1") != 0 || sString.GetFormat() != String::ASCII || sString != L"123141") bResult = false;
	sString = "123141";
	if (sString.Replace(static_cast<const wchar_t*>(nullptr), L"_") || sString.GetFormat() != String::ASCII || sString != L"123141") bResult = false;
	sString = "123141";
	if (sString.Replace(L"1", static_cast<const wchar_t*>(nullptr)) != 3 || sString.GetFormat() != String::Unicode || sString != L"234") bResult = false;
	sString = "123141";
	if (sString.Replace(L"1", L"_") != 3 || sString.GetFormat() != String::Unicode || sString != L"_23_4_") bResult = false;
	sString = "__123141";
	if (sString.Replace(L"1", L"_") != 3 || sString.GetFormat() != String::Unicode || sString != L"___23_4_") bResult = false;
	sString = "123412";
	if (sString.Replace(L"12", L"12") != 0 || sString.GetFormat() != String::ASCII || sString != L"123412") bResult = false;
	sString = "123412";
	if (sString.Replace(L"12", L"1") != 2 || sString.GetFormat() != String::Unicode || sString != L"1341") bResult = false;
	sString = "51123412";
	if (sString.Replace(L"12", L"1_2") != 2 || sString.GetFormat() != String::Unicode || sString != L"511_2341_2") bResult = false;
	sString = "123412";
	if (sString.Replace(L"123412", L"") != 1 || sString.GetFormat() != String::ASCII || sString != L"") bResult = false;
	sString = "Test 123412 This";
	if (sString.Replace(L"ahoioi", L"nope") != 0 || sString.GetFormat() != String::ASCII || sString != L"Test 123412 This") bResult = false;
	sString = "<>|<>";
	if (sString.Replace(L"|", L"Hi") != 1 || sString.GetFormat() != String::Unicode || sString != L"<>Hi<>") bResult = false;
	sString = "<>|<>|<>";
	if (sString.Replace(L"|", L"Hi") != 2 || sString.GetFormat() != String::Unicode || sString != L"<>Hi<>Hi<>") bResult = false;
	sString = "<++++>";
	if (sString.Replace(L"++", L"+") != 2 || sString.GetFormat() != String::Unicode || sString != L"<++>") bResult = false;
	sString = "<++++>";
	EndTask(bResult);

	// SetCharacter(uint32 nIndex, char nCharacter)
	StartTask("SetCharacter(uint32 nIndex, char nCharacter)");
	bResult = true;
	sString = "";
	if (sString.SetCharacter(0, 'a') || sString.SetCharacter(1, 'a') || sString.GetLength()) bResult = false;
	sString = "b";
	if (!sString.SetCharacter(0, 'a') || sString.SetCharacter(1, 'a') || sString.GetLength() != 1 ||
		sString != "a") bResult = false;
	sString = "bb";
	if (!sString.SetCharacter(0, 'a') || !sString.SetCharacter(1, '+') || sString.GetLength() != 2 ||
		sString != "a+") bResult = false;
	// Set ASCII character within an Unicode string
	sString = L"";
	if (sString.SetCharacter(0, 'a') || sString.SetCharacter(1, 'a') || sString.GetLength() || sString.GetFormat() != String::ASCII) bResult = false;
	sString = L"b";
	if (!sString.SetCharacter(0, 'a') || sString.SetCharacter(1, 'a') || sString.GetLength() != 1 ||
		sString != "a" || sString.GetFormat() != String::Unicode) bResult = false;
	sString = L"bb";
	if (!sString.SetCharacter(0, 'a') || !sString.SetCharacter(1, '+') || sString.GetLength() != 2 ||
		sString != "a+" || sString.GetFormat() != String::Unicode) bResult = false;
	EndTask(bResult);

	// SetCharacter(uint32 nIndex, wchar_t nCharacter)
	StartTask("SetCharacter(uint32 nIndex, wchar_t nCharacter)");
	bResult = true;
	sString = L"";
	if (sString.SetCharacter(0, L'a') || sString.SetCharacter(1, L'a') || sString.GetLength()) bResult = false;
	sString = L"b";
	if (!sString.SetCharacter(0, L'a') || sString.SetCharacter(1, L'a') || sString.GetLength() != 1 ||
		sString != L"a") bResult = false;
	sString = L"bb";
	if (!sString.SetCharacter(0, L'a') || !sString.SetCharacter(1, L'+') || sString.GetLength() != 2 ||
		sString != L"a+") bResult = false;
	sString = L"\u672cb";
	if (!sString.SetCharacter(0, L'\u672c') || !sString.SetCharacter(1, L'\u672c') || sString.GetLength() != 2 ||
		sString != L"\u672c\u672c") bResult = false;
	// Set Unicode character within an ASCII string
	sString = "";
	if (sString.SetCharacter(0, L'a') || sString.SetCharacter(1, L'a') || sString.GetLength() || sString.GetFormat() != String::ASCII) bResult = false;
	sString = "b";
	if (!sString.SetCharacter(0, L'a') || sString.SetCharacter(1, L'a') || sString.GetLength() != 1 ||
		sString != L"a" || sString.GetFormat() != String::Unicode) bResult = false;
	sString = "bb";
	if (!sString.SetCharacter(0, L'a') || !sString.SetCharacter(1, L'+') || sString.GetLength() != 2 ||
		sString != L"a+" || sString.GetFormat() != String::Unicode) bResult = false;
	EndTask(bResult);

	// TrimLeading(): ASCII
	StartTask("TrimLeading(): ASCII");
	bResult = true;
	sString = "";
	if (sString.TrimLeading().GetLength()) bResult = false;
	sString = "123";
	if (sString.TrimLeading() != "123") bResult = false;
	sString = "123  ";
	if (sString.TrimLeading() != "123  ") bResult = false;
	sString = "  123";
	if (sString.TrimLeading() != "123") bResult = false;
	sString = "  123  ";
	if (sString.TrimLeading() != "123  ") bResult = false;
	sString = "  ";
	if (sString.TrimLeading().GetLength()) bResult = false;
	EndTask(bResult);

	// TrimLeading(): Unicode
	StartTask("TrimLeading(): Unicode");
	bResult = true;
	sString = L"";
	if (sString.TrimLeading().GetLength()) bResult = false;
	sString = L"123";
	if (sString.TrimLeading() != L"123") bResult = false;
	sString = L"123  ";
	if (sString.TrimLeading() != L"123  ") bResult = false;
	sString = L"  123";
	if (sString.TrimLeading() != L"123") bResult = false;
	sString = L"  123  ";
	if (sString.TrimLeading() != L"123  ") bResult = false;
	sString = L"  ";
	if (sString.TrimLeading().GetLength()) bResult = false;
	sString = L"  \u65e5\u672c \u8a9e  ";
	if (sString.TrimLeading() != L"\u65e5\u672c \u8a9e  ") bResult = false;
	EndTask(bResult);

	// TrimTrailing(): ASCII
	StartTask("TrimTrailing(): ASCII");
	bResult = true;
	sString = "";
	if (sString.TrimTrailing().GetLength()) bResult = false;
	sString = "123";
	if (sString.TrimTrailing() != "123") bResult = false;
	sString = "  123";
	if (sString.TrimTrailing() != "  123") bResult = false;
	sString = "123  ";
	if (sString.TrimTrailing() != "123") bResult = false;
	sString = "  123  ";
	if (sString.TrimTrailing() != "  123") bResult = false;
	sString = "  ";
	if (sString.TrimTrailing().GetLength()) bResult = false;
	EndTask(bResult);

	// TrimTrailing(): Unicode
	StartTask("TrimTrailing(): Unicode");
	bResult = true;
	sString = L"";
	if (sString.TrimTrailing().GetLength()) bResult = false;
	sString = L"123";
	if (sString.TrimTrailing() != L"123") bResult = false;
	sString = L"  123";
	if (sString.TrimTrailing() != L"  123") bResult = false;
	sString = L"123  ";
	if (sString.TrimTrailing() != L"123") bResult = false;
	sString = L"  123  ";
	if (sString.TrimTrailing() != L"  123") bResult = false;
	sString = L"  ";
	if (sString.TrimTrailing().GetLength()) bResult = false;
	sString = L"  \u65e5\u672c \u8a9e  ";
	if (sString.TrimTrailing() != L"  \u65e5\u672c \u8a9e") bResult = false;
	EndTask(bResult);

	// Trim(): ASCII
	StartTask("Trim(): ASCII");
	bResult = true;
	sString = "";
	if (sString.Trim().GetLength()) bResult = false;
	sString = "123";
	if (sString.Trim() != "123") bResult = false;
	sString = "  123";
	if (sString.Trim() != "123") bResult = false;
	sString = "123  ";
	if (sString.Trim() != "123") bResult = false;
	sString = "  123  ";
	if (sString.Trim() != "123") bResult = false;
	sString = "  ";
	if (sString.Trim().GetLength()) bResult = false;
	EndTask(bResult);

	// Trim(): Unicode
	StartTask("Trim(): Unicode");
	bResult = true;
	sString = L"";
	if (sString.Trim().GetLength()) bResult = false;
	sString = L"123";
	if (sString.Trim() != L"123") bResult = false;
	sString = L"  123";
	if (sString.Trim() != L"123") bResult = false;
	sString = L"123  ";
	if (sString.Trim() != L"123") bResult = false;
	sString = L"  123  ";
	if (sString.Trim() != L"123") bResult = false;
	sString = L"  ";
	if (sString.Trim().GetLength()) bResult = false;
	sString = L"  \u65e5\u672c \u8a9e  ";
	if (sString.Trim() != L"\u65e5\u672c \u8a9e") bResult = false;
	EndTask(bResult);


// Is valid tests
	// IsValidInteger()
	StartTask("IsValidInteger()");
	bResult = true;
	sString = "";
	if (sString.IsValidInteger()) bResult = false;
	sString = "0";
	if (!sString.IsValidInteger()) bResult = false;
	sString = "false";
	if (sString.IsValidInteger()) bResult = false;
	sString = "Timmy!";
	if (sString.IsValidInteger()) bResult = false;
	sString = "1365";
	if (!sString.IsValidInteger()) bResult = false;
	sString = "024";
	if (!sString.IsValidInteger()) bResult = false;
	sString = "-0242";
	if (!sString.IsValidInteger()) bResult = false;
	sString = "-0242-";
	if (sString.IsValidInteger()) bResult = false;
	sString = "+0242-";
	if (sString.IsValidInteger()) bResult = false;
	sString = "+0242";
	if (!sString.IsValidInteger()) bResult = false;
	EndTask(bResult);

	// IsValidFloat()
	StartTask("IsValidFloat()");
	bResult = true;
	sString = "";
	if (sString.IsValidFloat()) bResult = false;
	sString = "0";
	if (!sString.IsValidFloat()) bResult = false;
	sString = "false";
	if (sString.IsValidFloat()) bResult = false;
	sString = "Timmy!";
	if (sString.IsValidFloat()) bResult = false;
	sString = "1365";
	if (!sString.IsValidFloat()) bResult = false;
	sString = "024";
	if (!sString.IsValidFloat()) bResult = false;
	sString = "-0242";
	if (!sString.IsValidFloat()) bResult = false;
	sString = "-0242-";
	if (sString.IsValidFloat()) bResult = false;
	sString = "+0242-";
	if (sString.IsValidFloat()) bResult = false;
	sString = "+0242";
	if (!sString.IsValidFloat()) bResult = false;
	sString = "0.";
	if (!sString.IsValidFloat()) bResult = false;
	sString = ".0";
	if (!sString.IsValidFloat()) bResult = false;
	sString = "1.0";
	if (!sString.IsValidFloat()) bResult = false;
	sString = "1.0.2";
	if (sString.IsValidFloat()) bResult = false;
	sString = "-1.0";
	if (!sString.IsValidFloat()) bResult = false;
	sString = "1.0e24";
	if (!sString.IsValidFloat()) bResult = false;
	sString = "1.0e-24";
	if (!sString.IsValidFloat()) bResult = false;
	sString = "1.e0e-24";
	if (sString.IsValidFloat()) bResult = false;
	EndTask(bResult);


// Convert from string
	// GetBool(): ASCII
	StartTask("GetBool(): ASCII");
	bResult = true;
	sString = "";
	if (sString.GetBool()) bResult = false;
	sString = "0";
	if (sString.GetBool()) bResult = false;
	sString = "false";
	if (sString.GetBool()) bResult = false;
	sString = "False";
	if (sString.GetBool()) bResult = false;
	sString = "1";
	if (!sString.GetBool()) bResult = false;
	sString = "true";
	if (!sString.GetBool()) bResult = false;
	sString = "True";
	if (!sString.GetBool()) bResult = false;
	EndTask(bResult);

	// GetBool(): Unicode
	StartTask("GetBool(): Unicode");
	bResult = true;
	sString = L"";
	if (sString.GetBool()) bResult = false;
	sString = L"0";
	if (sString.GetBool()) bResult = false;
	sString = L"false";
	if (sString.GetBool()) bResult = false;
	sString = L"False";
	if (sString.GetBool()) bResult = false;
	sString = L"1";
	if (!sString.GetBool()) bResult = false;
	sString = L"true";
	if (!sString.GetBool()) bResult = false;
	sString = L"True";
	if (!sString.GetBool()) bResult = false;
	sString = L"\u672c";
	if (sString.GetBool()) bResult = false;
	EndTask(bResult);

	// GetChar()
	StartTask("GetChar()");
	bResult = true;
	sString = "";
	if (sString.GetChar() != '\0') bResult = false;
	sString = "a";
	if (sString.GetChar() != '\0') bResult = false;
	sString = "65";
	if (sString.GetChar() != 'A') bResult = false;
	EndTask(bResult);

	// GetCharWide()
	StartTask("GetCharWide()");
	bResult = true;
	sString = L"";
	if (sString.GetChar() != L'\0') bResult = false;
	sString = L"a";
	if (sString.GetChar() != L'\0') bResult = false;
	EndTask(bResult);

	// GetInt(): ASCII
	StartTask("GetInt(): ASCII");
	bResult = true;
	sString = "";
	if (sString.GetInt()) bResult = false;
	sString = "0";
	if (sString.GetInt()) bResult = false;
	sString = "5";
	if (sString.GetInt() != 5) bResult = false;
	EndTask(bResult);

	// GetInt(): Unicode
	StartTask("GetInt(): Unicode");
	bResult = true;
	sString = L"";
	if (sString.GetInt()) bResult = false;
	sString = L"0";
	if (sString.GetInt()) bResult = false;
	sString = L"5";
	if (sString.GetInt() != 5) bResult = false;
	sString = L"\u672c";
	if (sString.GetInt() != 0) bResult = false;
	EndTask(bResult);

	// GetFloat(): ASCII
	StartTask("GetFloat(): ASCII");
	bResult = true;
	sString = "";
	if (sString.GetFloat()) bResult = false;
	sString = "0";
	if (sString.GetFloat()) bResult = false;
	sString = "5";
	if (sString.GetFloat() != 5.0f) bResult = false;
	sString = "5.0";
	if (sString.GetFloat() != 5.0f) bResult = false;
	sString = "5.5";
	if (sString.GetFloat() != 5.5f) bResult = false;
	EndTask(bResult);

	// GetFloat(): Unicode
	StartTask("GetFloat(): Unicode");
	bResult = true;
	sString = L"";
	if (sString.GetFloat()) bResult = false;
	sString = L"0";
	if (sString.GetFloat()) bResult = false;
	sString = L"5";
	if (sString.GetFloat() != 5.0f) bResult = false;
	sString = L"5.0";
	if (sString.GetFloat() != 5.0f) bResult = false;
	sString = L"5.5";
	if (sString.GetFloat() != 5.5f) bResult = false;
	sString = L"\u672c";
	if (sString.GetFloat() != 0.0f) bResult = false;
	EndTask(bResult);

	// GetDouble(): ASCII
	StartTask("GetDouble(): ASCII");
	bResult = true;
	sString = "";
	if (sString.GetDouble()) bResult = false;
	sString = "0";
	if (sString.GetDouble()) bResult = false;
	sString = "5";
	if (sString.GetDouble() != 5.0) bResult = false;
	sString = "5.0";
	if (sString.GetDouble() != 5.0) bResult = false;
	sString = "5.5";
	if (sString.GetDouble() != 5.5) bResult = false;
	EndTask(bResult);

	// GetDouble(): Unicode
	StartTask("GetDouble(): Unicode");
	bResult = true;
	sString = L"";
	if (sString.GetDouble()) bResult = false;
	sString = L"0";
	if (sString.GetDouble()) bResult = false;
	sString = L"5";
	if (sString.GetDouble() != 5.0) bResult = false;
	sString = L"5.0";
	if (sString.GetDouble() != 5.0) bResult = false;
	sString = L"5.5";
	if (sString.GetDouble() != 5.5) bResult = false;
	sString = L"\u672c";
	if (sString.GetDouble() != 0.0) bResult = false;
	EndTask(bResult);


// Convert to string
	// =(bool bValue)
	StartTask("=(bool bValue)");
	bResult = true;
	sString = false;
	if (sString != "0") bResult = false;
	sString = true;
	if (sString != "1") bResult = false;
	EndTask(bResult);

	// =(char nValue)
	StartTask("=(char nValue)");
	bResult = true;
	sString = 'a';
	if (sString != "a") bResult = false;
	sString = static_cast<char>(65);
	if (sString != "A") bResult = false;
	sString = 'A';
	if (sString != "A") bResult = false;
	sString = '\0';
	if (sString != "") bResult = false;
	EndTask(bResult);

	// =(wchar_t nValue)
	StartTask("=(wchar_t nValue)");
	bResult = true;
	sString = L'a';
	if (sString != L"a") bResult = false;
	sString = static_cast<wchar_t>(65);
	if (sString != L"A") bResult = false;
	sString = L'A';
	if (sString != L"A") bResult = false;
	sString = L'\0';
	if (sString != L"") bResult = false;
	EndTask(bResult);

	// =(int nValue)
	StartTask("=(int nValue)");
	bResult = true;
	sString = 0;
	if (sString != "0") bResult = false;
	sString = -0;
	if (sString != "0") bResult = false;
	sString = 65;
	if (sString != "65") bResult = false;
	sString = -65;
	if (sString != "-65") bResult = false;
	EndTask(bResult);

	// =(float fValue)
	StartTask("=(float fValue)");
	bResult = true;
	sString = 0.0f;
	if (sString != "0") bResult = false;
	sString = -0.0f;
	if (sString != "0") bResult = false;
	sString = 65.0f;
	if (sString != "65") bResult = false;
	sString = 65.1001f;
	if (sString != "65.1001") bResult = false;
	sString = -65.0f;
	if (sString != "-65") bResult = false;
	sString = -65.1001f;
	if (sString != "-65.1001") bResult = false;
	EndTask(bResult);

	// =(double fValue)
	StartTask("=(double fValue)");
	bResult = true;
	sString = 0.0;
	if (sString != "0") bResult = false;
	sString = -0.0;
	if (sString != "0") bResult = false;
	sString = 65.0;
	if (sString != "65") bResult = false;
	sString = 65.1001;
	if (sString != "65.1001") bResult = false;
	sString = -65.0;
	if (sString != "-65") bResult = false;
	sString = -65.1001;
	if (sString != "-65.1001") bResult = false;
	EndTask(bResult);


// Concatenation
// String + <Value>
	// +(bool bValue)
	StartTask("+(bool bValue)");
	bResult = true;
	sString = "";
	sString = sString + false;
	if (sString != "0") bResult = false;
	sString = "";
	sString = sString + true;
	if (sString != "1") bResult = false;
	sString = sString + false;
	if (sString != "10") bResult = false;
	EndTask(bResult);

	// +(char nValue)
	StartTask("+(char nValue)");
	bResult = true;
	sString = "";
	sString = sString + 'a';
	if (sString != "a") bResult = false;
	sString = "";
	sString = sString + static_cast<char>(65);
	if (sString != "A") bResult = false;
	sString = "";
	sString = sString + 'A';
	if (sString != "A") bResult = false;
	sString = "";
	sString = sString + '\0';
	if (sString != "") bResult = false;
	sString = sString + 'a';
	if (sString != "a") bResult = false;
	sString = sString + 'b';
	if (sString != "ab") bResult = false;
	EndTask(bResult);

	// +(wchar_t nValue)
	StartTask("+(wchar_t nValue)");
	bResult = true;
	sString = L"";
	sString = sString + L'a';
	if (sString != L"a") bResult = false;
	sString = L"";
	sString = sString + static_cast<wchar_t>(65);
	if (sString != L"A") bResult = false;
	sString = L"";
	sString = sString + L'A';
	if (sString != L"A") bResult = false;
	sString = L"";
	sString = sString + L'\0';
	if (sString != L"") bResult = false;
	sString = sString + L'a';
	if (sString != L"a") bResult = false;
	sString = sString + L'b';
	if (sString != L"ab") bResult = false;
	EndTask(bResult);

	// +(int nValue)
	StartTask("+(int nValue)");
	bResult = true;
	sString = "";
	sString = sString + 0;
	if (sString != "0") bResult = false;
	sString = "";
	sString = sString + -0;
	if (sString != "0") bResult = false;
	sString = "";
	sString = sString + 65;
	if (sString != "65") bResult = false;
	sString = "";
	sString = sString + -65;
	if (sString != "-65") bResult = false;
	sString = sString + 1;
	if (sString != "-651") bResult = false;
	EndTask(bResult);

	// +(float fValue)
	StartTask("+(float fValue)");
	bResult = true;
	sString = "";
	sString = sString + 0.0f;
	if (sString != "0") bResult = false;
	sString = "";
	sString = sString + -0.0f;
	if (sString != "0") bResult = false;
	sString = "";
	sString = sString + 65.0f;
	if (sString != "65") bResult = false;
	sString = "";
	sString = sString + 65.1001f;
	if (sString != "65.1001") bResult = false;
	sString = "";
	sString = sString + -65.0f;
	if (sString != "-65") bResult = false;
	sString = "";
	sString = sString + -65.1001f;
	if (sString != "-65.1001") bResult = false;
	sString = sString + 9.0f;
	if (sString != "-65.10019") bResult = false;
	EndTask(bResult);

	// +(double fValue)
	StartTask("+(double fValue)");
	bResult = true;
	sString = "";
	sString = sString + 0.0;
	if (sString != "0") bResult = false;
	sString = "";
	sString = sString + -0.0;
	if (sString != "0") bResult = false;
	sString = "";
	sString = sString + 65.0;
	if (sString != "65") bResult = false;
	sString = "";
	sString = sString + 65.1001;
	if (sString != "65.1001") bResult = false;
	sString = "";
	sString = sString + -65.0;
	if (sString != "-65") bResult = false;
	sString = "";
	sString = sString + -65.1001;
	if (sString != "-65.1001") bResult = false;
	sString = sString + 9.0;
	if (sString != "-65.10019") bResult = false;
	EndTask(bResult);

// <Value> + String
	// +(bool bValue, const String &sString)
	StartTask("+(bool bValue, const String &sString)");
	bResult = true;
	sString = "";
	sString = false + sString;
	if (sString != "0") bResult = false;
	sString = "";
	sString = true + sString;
	if (sString != "1") bResult = false;
	sString = false + sString;
	if (sString != "01") bResult = false;
	EndTask(bResult);

	// +(char nValue, const String &sString)
	StartTask("+(char nValue, const String &sString)");
	bResult = true;
	sString = "";
	sString = 'a' + sString;
	if (sString != "a") bResult = false;
	sString = "";
	sString = static_cast<char>(65) + sString;
	if (sString != "A") bResult = false;
	sString = "";
	sString = 'A' + sString;
	if (sString != "A") bResult = false;
	sString = "";
	sString = '\0' + sString;
	if (sString != "") bResult = false;
	sString = 'a' + sString;
	if (sString != "a") bResult = false;
	sString = 'b' + sString;
	if (sString != "ba") bResult = false;
	EndTask(bResult);

	// +(wchar_t nValue, const String &sString)
	StartTask("+(wchar_t nValue, const String &sString)");
	bResult = true;
	sString = L"";
	sString = L'a' + sString;
	if (sString != L"a") bResult = false;
	sString = L"";
	sString = static_cast<wchar_t>(65) + sString;
	if (sString != L"A") bResult = false;
	sString = L"";
	sString = L'A' + sString;
	if (sString != L"A") bResult = false;
	sString = L"";
	sString = L'\0' + sString;
	if (sString != L"") bResult = false;
	sString = L'a' + sString;
	if (sString != L"a") bResult = false;
	sString = L'b' + sString;
	if (sString != L"ba") bResult = false;
	EndTask(bResult);

	// +(int nValue, const String &sString)
	StartTask("+(int nValue, const String &sString)");
	bResult = true;
	sString = "";
	sString = 0 + sString;
	if (sString != "0") bResult = false;
	sString = "";
	sString = -0 + sString;
	if (sString != "0") bResult = false;
	sString = "";
	sString = 65 + sString;
	if (sString != "65") bResult = false;
	sString = "";
	sString = -65 + sString;
	if (sString != "-65") bResult = false;
	sString = 1 + sString;
	if (sString != "1-65") bResult = false;
	EndTask(bResult);

	// +(float fValue, const String &sString)
	StartTask("+(float fValue, const String &sString)");
	bResult = true;
	sString = "";
	sString = 0.0f + sString;
	if (sString != "0") bResult = false;
	sString = "";
	sString = -0.0f + sString;
	if (sString != "0") bResult = false;
	sString = "";
	sString = 65.0f + sString;
	if (sString != "65") bResult = false;
	sString = "";
	sString = 65.1001f + sString;
	if (sString != "65.1001") bResult = false;
	sString = "";
	sString = -65.0f + sString;
	if (sString != "-65") bResult = false;
	sString = "";
	sString = -65.1001f + sString;
	if (sString != "-65.1001") bResult = false;
	sString = 9.0f + sString;
	if (sString != "9-65.1001") bResult = false;
	EndTask(bResult);

	// +(double fValue, const String &sString)
	StartTask("+(double fValue, const String &sString)");
	bResult = true;
	sString = "";
	sString = 0.0 + sString;
	if (sString != "0") bResult = false;
	sString = "";
	sString = -0.0 + sString;
	if (sString != "0") bResult = false;
	sString = "";
	sString = 65.0 + sString;
	if (sString != "65") bResult = false;
	sString = "";
	sString = 65.1001 + sString;
	if (sString != "65.1001") bResult = false;
	sString = "";
	sString = -65.0 + sString;
	if (sString != "-65") bResult = false;
	sString = "";
	sString = -65.1001 + sString;
	if (sString != "-65.1001") bResult = false;
	sString = 9.0 + sString;
	if (sString != "9-65.1001") bResult = false;
	EndTask(bResult);

// String += <Value>
	// +=(bool bValue)
	StartTask("+=(bool bValue)");
	bResult = true;
	sString = "";
	sString += false;
	if (sString != "0") bResult = false;
	sString = "";
	sString += true;
	if (sString != "1") bResult = false;
	sString += false;
	if (sString != "10") bResult = false;
	EndTask(bResult);

	// +=(char nValue)
	StartTask("+=(char nValue)");
	bResult = true;
	sString = "";
	sString += 'a';
	if (sString != "a") bResult = false;
	sString = "";
	sString += static_cast<char>(65);
	if (sString != "A") bResult = false;
	sString = "";
	sString += 'A';
	if (sString != "A") bResult = false;
	sString = "";
	sString += '\0';
	if (sString != "") bResult = false;
	sString += 'a';
	if (sString != "a") bResult = false;
	sString += 'b';
	if (sString != "ab") bResult = false;
	EndTask(bResult);

	// +=(wchar_t nValue)
	StartTask("+=(wchar_t nValue)");
	bResult = true;
	sString = L"";
	sString += L'a';
	if (sString != L"a") bResult = false;
	sString = L"";
	sString += static_cast<wchar_t>(65);
	if (sString != L"A") bResult = false;
	sString = L"";
	sString += L'A';
	if (sString != L"A") bResult = false;
	sString = L"";
	sString += L'\0';
	if (sString != L"") bResult = false;
	sString += L'a';
	if (sString != L"a") bResult = false;
	sString += L'b';
	if (sString != L"ab") bResult = false;
	EndTask(bResult);

	// +=(int nValue)
	StartTask("+=(int nValue)");
	bResult = true;
	sString = "";
	sString += 0;
	if (sString != "0") bResult = false;
	sString = "";
	sString += -0;
	if (sString != "0") bResult = false;
	sString = "";
	sString += 65;
	if (sString != "65") bResult = false;
	sString = "";
	sString += -65;
	if (sString != "-65") bResult = false;
	sString += 1;
	if (sString != "-651") bResult = false;
	EndTask(bResult);

	// +=(float fValue)
	StartTask("+=(float fValue)");
	bResult = true;
	sString = "";
	sString += 0.0f;
	if (sString != "0") bResult = false;
	sString = "";
	sString += -0.0f;
	if (sString != "0") bResult = false;
	sString = "";
	sString += 65.0f;
	if (sString != "65") bResult = false;
	sString = "";
	sString += 65.1001f;
	if (sString != "65.1001") bResult = false;
	sString = "";
	sString += -65.0f;
	if (sString != "-65") bResult = false;
	sString = "";
	sString += -65.1001f;
	if (sString != "-65.1001") bResult = false;
	sString += 9.0f;
	if (sString != "-65.10019") bResult = false;
	EndTask(bResult);

	// +=(double fValue)
	StartTask("+=(double fValue)");
	bResult = true;
	sString = "";
	sString += 0.0;
	if (sString != "0") bResult = false;
	sString = "";
	sString += -0.0;
	if (sString != "0") bResult = false;
	sString = "";
	sString += 65.0;
	if (sString != "65") bResult = false;
	sString = "";
	sString += 65.1001;
	if (sString != "65.1001") bResult = false;
	sString = "";
	sString += -65.0;
	if (sString != "-65") bResult = false;
	sString = "";
	sString += -65.1001;
	if (sString != "-65.1001") bResult = false;
	sString += 9.0;
	if (sString != "-65.10019") bResult = false;
	EndTask(bResult);


// Composed
	// sString = 5 + sString + '_' + true + "HeHo" + 55.9
	StartTask("sString = 5 + sString + '_' + true + \"HeHo\" + 55.9");
	bResult = true;
	sString = "MyString";
	sString = 5 + sString + '_' + true + "HeHo" + 55.9;
	EndTask(sString == "5MyString_1HeHo55.9");


// Some special tests
	// Format("%g", 5.12f)
	StartTask("Format(\"%g\", 5.12f)");
	bResult = true;
	if (String::Format("%g", 5.12f) != "5.12") bResult = false;
	// Now, change the local...
	char *pLocalSave = strdup(setlocale(LC_ALL, nullptr));	// Get the current set locale, we REALLY need to backup the locale because it "may" be changed by "setlocale"
	setlocale(LC_ALL, "German"); // Set another local, now normally a ',' instead of '.'
								 // is used by printf and so on... (but our string class ignores that :)
	if (String::Format("%g", 5.12f) != "5.12") bResult = false;
	setlocale(LC_ALL, pLocalSave); // Reset the local
	free(pLocalSave);
	EndTask(bResult);

	// String("5.12").GetFloat()
	StartTask("String(\"5.12\").GetFloat()");
	float fValue = String("5.12").GetFloat();
	EndTask(fValue > 5.11999 && fValue < 5.12001);
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP

