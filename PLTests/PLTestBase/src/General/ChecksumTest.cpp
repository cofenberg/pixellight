/*********************************************************\
 *  File: ChecksumTest.cpp                               *
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
#include <PLGeneral/File/File.h>
#include <PLGeneral/Tools/ChecksumMD5.h>
#include <PLGeneral/Tools/ChecksumCRC32.h>
#include <PLGeneral/Tools/ChecksumSHA1.h>
#include "PLTestBase/General/ChecksumTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *ChecksumTest::GetName() const
{
	return "Checksum";
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the checksum of a given file
*/
String ChecksumTest::CheckFile(Checksum &cChecksum, const String &sFilename)
{
	// Check the given parameter
	if (!sFilename.GetLength()) return ""; // Error!

	// Open the file
	File cFile(sFilename);

	// Fool the checksum function ;-)
/* Assertion...
	String sChecksum = Checksum::Get(sClass, pFile);
	if (sChecksum.GetLength()) {
		pFile->Release();

		// Error!
		return "";
	}
	*/

	// Open the file
	if (!cFile.Open(File::FileRead)) {
		// Error!
		return "";
	}

	// Get the checksum
	String sChecksum = cChecksum.Get(cFile);

	// Check the current file offset
	if (cFile.Tell()) sChecksum = ""; // Error!

	// Close the file
	cFile.Close();

	// Done
	return sChecksum;
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void ChecksumTest::Test()
{
	bool bResult = true;
	String sChecksum;
	ChecksumMD5 cChecksumMD5;
	ChecksumCRC32 cChecksumCRC32;
	ChecksumSHA1 cChecksumSHA1;

// ChecksumMD5
	// ChecksumMD5: Get(const uint8 nBuffer[], uint32 nNumOfBytes)
	StartTask("ChecksumMD5: Get(const uint8 nBuffer[], uint32 nNumOfBytes)");
	// Alphabet
	sChecksum = cChecksumMD5.Get((uint8*)"abcdefghijklmnopqrstuvwxyz", (uint32)strlen("abcdefghijklmnopqrstuvwxyz"));
	if (sChecksum != "c3fcd3d76192e4007dfb496cca67e13b") bResult = false;
	// Corrupted alphabet (one of the letters in the alphabet (in this case 'm') is changed to uppercase)
	sChecksum = cChecksumMD5.Get((uint8*)"abcdefghijklMnopqrstuvwxyz", (uint32)strlen("abcdefghijklMnopqrstuvwxyz"));
	if (sChecksum == "c3fcd3d76192e4007dfb496cca67e13b") bResult = false;
	// Alphabet and numbers
	sChecksum = cChecksumMD5.Get((uint8*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", (uint32)strlen("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"));
	if (sChecksum != "d174ab98d277d9f5a5611c2c9f419d9f") bResult = false;
	// Corrupted alphabet and numbers ('9' removed)
	sChecksum = cChecksumMD5.Get((uint8*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345678", (uint32)strlen("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345678"));
	if (sChecksum == "d174ab98d277d9f5a5611c2c9f419d9f") bResult = false;
	EndTask(bResult);

	// ChecksumMD5: Get(const String &sString)
	StartTask("ChecksumMD5: Get(const String &sString)");
	bResult = true;
	// Alphabet
	sChecksum = cChecksumMD5.Get("abcdefghijklmnopqrstuvwxyz");
	if (sChecksum != "c3fcd3d76192e4007dfb496cca67e13b") bResult = false;
	// Corrupted alphabet (one of the letters in the alphabet (in this case 'm') is changed to uppercase)
	sChecksum = cChecksumMD5.Get("abcdefghijklMnopqrstuvwxyz");
	if (sChecksum == "c3fcd3d76192e4007dfb496cca67e13b") bResult = false;
	// Alphabet and numbers
	sChecksum = cChecksumMD5.Get("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	if (sChecksum != "d174ab98d277d9f5a5611c2c9f419d9f") bResult = false;
	// Corrupted alphabet and numbers ('9' removed)
	sChecksum = cChecksumMD5.Get("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345678");
	if (sChecksum == "d174ab98d277d9f5a5611c2c9f419d9f") bResult = false;
	// Unicode
	sChecksum = cChecksumMD5.Get(L"\u65e5\u672c\u8a9e");
	if (sChecksum != "965f626b62b499198df91ae051f13bd2") bResult = false;
	// Alphabet and numbers - this time as Unicode
	sChecksum = cChecksumMD5.Get(L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	if (sChecksum == "d174ab98d277d9f5a5611c2c9f419d9f") bResult = false;
	EndTask(bResult);

	// ChecksumMD5: Get(File &cFile)
	StartTask("ChecksumMD5: Get(File &cFile)");
	bResult = true;
	// Check 'demotest.xml'
	sChecksum = CheckFile(cChecksumMD5, "demotest.xml");
	if (sChecksum != "caf5fe7d6c372d213627d51147c889c8") bResult = false;
	// Check 'tokenizer.txt'
	sChecksum = CheckFile(cChecksumMD5, "tokenizer.txt");
	if (sChecksum != "e8d4c6ef5f6ab8d5750f012a8633a315") bResult = false;
	// Check 'test.zip'
	sChecksum = CheckFile(cChecksumMD5, "test.zip");
	if (sChecksum != "d9bdfd82c142eccbb6237b32f90422a0") bResult = false;
	EndTask(bResult);

	// ChecksumMD5: GetFile(const String &sFilename)
	StartTask("ChecksumMD5: Get(const String &sFilename)");
	bResult = true;
	// Check 'demotest.xml'
	sChecksum = cChecksumMD5.GetFile("demotest.xml");
	if (sChecksum != "caf5fe7d6c372d213627d51147c889c8") bResult = false;
	// Check 'tokenizer.txt'
	sChecksum = cChecksumMD5.GetFile("tokenizer.txt");
	if (sChecksum != "e8d4c6ef5f6ab8d5750f012a8633a315") bResult = false;
	// Check 'test.zip'
	sChecksum = cChecksumMD5.GetFile("test.zip");
	if (sChecksum != "d9bdfd82c142eccbb6237b32f90422a0") bResult = false;
	EndTask(bResult);


// ChecksumCRC32
	bResult = true;
	// ChecksumCRC32: Get(const uint8 nBuffer[], uint32 nNumOfBytes)
	StartTask("ChecksumCRC32: Get(const uint8 nBuffer[], uint32 nNumOfBytes)");
	// Alphabet
	sChecksum = cChecksumCRC32.Get((uint8*)"abcdefghijklmnopqrstuvwxyz", (uint32)strlen("abcdefghijklmnopqrstuvwxyz"));
	if (sChecksum != "4c2750bd") bResult = false;
	// Corrupted alphabet (one of the letters in the alphabet (in this case 'm') is changed to uppercase)
	sChecksum = cChecksumCRC32.Get((uint8*)"abcdefghijklMnopqrstuvwxyz", (uint32)strlen("abcdefghijklMnopqrstuvwxyz"));
	if (sChecksum == "4c2750bd") bResult = false;
	// Alphabet and numbers
	sChecksum = cChecksumCRC32.Get((uint8*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", (uint32)strlen("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"));
	if (sChecksum != "1fc2e6d2") bResult = false;
	// Corrupted alphabet and numbers ('9' removed)
	sChecksum = cChecksumCRC32.Get((uint8*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345678", (uint32)strlen("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345678"));
	if (sChecksum == "170fccc") bResult = false;
	EndTask(bResult);

	// ChecksumCRC32: Get(const String &sString)
	StartTask("ChecksumCRC32: Get(const String &sString)");
	bResult = true;
	// Alphabet
	sChecksum = cChecksumCRC32.Get("abcdefghijklmnopqrstuvwxyz");
	if (sChecksum != "4c2750bd") bResult = false;
	// Corrupted alphabet (one of the letters in the alphabet (in this case 'm') is changed to uppercase)
	sChecksum = cChecksumCRC32.Get("abcdefghijklMnopqrstuvwxyz");
	if (sChecksum == "4c2750bd") bResult = false;
	// Alphabet and numbers
	sChecksum = cChecksumCRC32.Get("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	if (sChecksum != "1fc2e6d2") bResult = false;
	// Corrupted alphabet and numbers ('9' removed)
	sChecksum = cChecksumCRC32.Get("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345678");
	if (sChecksum == "1fc2e6d2") bResult = false;
	// Unicode
	sChecksum = cChecksumCRC32.Get(L"\u65e5\u672c\u8a9e");
	if (sChecksum != "e34ad326") bResult = false;
	// Alphabet and numbers - this time as Unicode
	sChecksum = cChecksumCRC32.Get(L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	if (sChecksum == "e34ad326") bResult = false;
	EndTask(bResult);

	// ChecksumCRC32: Get(File &cFile)
	StartTask("ChecksumCRC32: Get(File &cFile)");
	bResult = true;
	// Check 'demotest.xml'
	sChecksum = CheckFile(cChecksumCRC32, "demotest.xml");
	if (sChecksum != "879c2363") bResult = false;
	// Check 'tokenizer.txt'
	sChecksum = CheckFile(cChecksumCRC32, "tokenizer.txt");
	if (sChecksum != "fbab7f1f") bResult = false;
	// Check 'test.zip'
	sChecksum = CheckFile(cChecksumCRC32, "test.zip");
	if (sChecksum != "84ee7986") bResult = false;
	EndTask(bResult);

	// ChecksumCRC32: GetFile(const String &sFilename)
	StartTask("ChecksumCRC32: Get(const String &sFilename)");
	bResult = true;
	// Check 'demotest.xml'
	sChecksum = cChecksumCRC32.GetFile("demotest.xml");
	if (sChecksum != "879c2363") bResult = false;
	// Check 'tokenizer.txt'
	sChecksum = cChecksumCRC32.GetFile("tokenizer.txt");
	if (sChecksum != "fbab7f1f") bResult = false;
	// Check 'test.zip'
	sChecksum = cChecksumCRC32.GetFile("test.zip");
	if (sChecksum != "84ee7986") bResult = false;
	EndTask(bResult);


// ChecksumSHA1
	bResult = true;
	// ChecksumSHA1: Get(const uint8 nBuffer[], uint32 nNumOfBytes)
	StartTask("ChecksumSHA1: Get(const uint8 nBuffer[], uint32 nNumOfBytes)");
	// Alphabet
	sChecksum = cChecksumSHA1.Get((uint8*)"abcdefghijklmnopqrstuvwxyz", (uint32)strlen("abcdefghijklmnopqrstuvwxyz"));
	if (sChecksum != "32d10c7b8cf96570ca04ce37f2a19d84240d3a89") bResult = false;
	// Corrupted alphabet (one of the letters in the alphabet (in this case 'm') is changed to uppercase)
	sChecksum = cChecksumSHA1.Get((uint8*)"abcdefghijklMnopqrstuvwxyz", (uint32)strlen("abcdefghijklMnopqrstuvwxyz"));
	if (sChecksum == "32d10c7b8cf96570ca04ce37f2a19d84240d3a89") bResult = false;
	// Alphabet and numbers
	sChecksum = cChecksumSHA1.Get((uint8*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", (uint32)strlen("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"));
	if (sChecksum != "761c457bf73b14d27e9e9265c46f4b4dda11f940") bResult = false;
	// Corrupted alphabet and numbers ('9' removed)
	sChecksum = cChecksumSHA1.Get((uint8*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345678", (uint32)strlen("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345678"));
	if (sChecksum == "761c457bf73b14d27e9e9265c46f4b4dda11f940") bResult = false;
	EndTask(bResult);

	// ChecksumSHA1: Get(const String &sString)
	StartTask("ChecksumSHA1: Get(const String &sString)");
	bResult = true;
	// Alphabet
	sChecksum = cChecksumSHA1.Get("abcdefghijklmnopqrstuvwxyz");
	if (sChecksum != "32d10c7b8cf96570ca04ce37f2a19d84240d3a89") bResult = false;
	// Corrupted alphabet (one of the letters in the alphabet (in this case 'm') is changed to uppercase)
	sChecksum = cChecksumSHA1.Get("abcdefghijklMnopqrstuvwxyz");
	if (sChecksum == "32d10c7b8cf96570ca04ce37f2a19d84240d3a89") bResult = false;
	// Alphabet and numbers
	sChecksum = cChecksumSHA1.Get("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	if (sChecksum != "761c457bf73b14d27e9e9265c46f4b4dda11f940") bResult = false;
	// Corrupted alphabet and numbers ('9' removed)
	sChecksum = cChecksumSHA1.Get("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345678");
	if (sChecksum == "761c457bf73b14d27e9e9265c46f4b4dda11f940") bResult = false;
	// Unicode
	sChecksum = cChecksumSHA1.Get(L"\u65e5\u672c\u8a9e");
	if (sChecksum != "5c9941a48c296ef5cc2f267874c8dafeeb36a385") bResult = false;
	// Alphabet and numbers - this time as Unicode
	sChecksum = cChecksumSHA1.Get(L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	if (sChecksum == "5c9941a48c296ef5cc2f267874c8dafeeb36a385") bResult = false;
	EndTask(bResult);

	// ChecksumSHA1: Get(File &cFile)
	StartTask("ChecksumSHA1: Get(File &cFile)");
	bResult = true;
	// Check 'demotest.xml'
	sChecksum = CheckFile(cChecksumSHA1, "demotest.xml");
	if (sChecksum != "f3f9259f1a56e9dc2e47a89342c3cfa7c5a72a98") bResult = false;
	// Check 'tokenizer.txt'
	sChecksum = CheckFile(cChecksumSHA1, "tokenizer.txt");
	if (sChecksum != "1426466cd8518ae4a630a54acc082de634fd44ed") bResult = false;
	// Check 'test.zip'
	sChecksum = CheckFile(cChecksumSHA1, "test.zip");
	if (sChecksum != "ddc29c7c422d8ef3c0a2102b61a56f0f899367d3") bResult = false;
	EndTask(bResult);

	// ChecksumSHA1: GetFile(const String &sFilename)
	StartTask("ChecksumSHA1: Get(const String &sFilename)");
	bResult = true;
	// Check 'demotest.xml'
	sChecksum = cChecksumSHA1.GetFile("demotest.xml");
	if (sChecksum != "f3f9259f1a56e9dc2e47a89342c3cfa7c5a72a98") bResult = false;
	// Check 'tokenizer.txt'
	sChecksum = cChecksumSHA1.GetFile("tokenizer.txt");
	if (sChecksum != "1426466cd8518ae4a630a54acc082de634fd44ed") bResult = false;
	// Check 'test.zip'
	sChecksum = cChecksumSHA1.GetFile("test.zip");
	if (sChecksum != "ddc29c7c422d8ef3c0a2102b61a56f0f899367d3") bResult = false;
	EndTask(bResult);
}
