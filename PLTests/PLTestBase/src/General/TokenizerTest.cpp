/*********************************************************\
 *  File: TokenizerTest.cpp                              *
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
#include <PLGeneral/File/File.h>
#include <PLGeneral/String/Tokenizer.h>
#include "PLTestBase/General/TokenizerTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *TokenizerTest::GetName() const
{
	return "Tokenizer";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void TokenizerTest::Test()
{
	// Open file
	StartTask("Open file 'tokenizer.txt'");
		File cFile("tokenizer.txt");
		bool bOpen = cFile.Open(File::FileRead);
	EndTask(bOpen);

	if (!bOpen) return;

	// Start tokenizer
	StartTask("Start tokenizer on file");
		Tokenizer tok;
		tok.SetSingleChars("{}()[]<>+-*/=,;\"");
		tok.Start(cFile);
	EndTask(true);

	// Parse token 'first'
	StartTask("Parse token 'first'");
		String s = tok.GetNextToken();
	EndTask(s == "first");

	// Expect token 'second'
	StartTask("Expect token 'second'");
	EndTask(tok.ExpectToken("second"));

	// Read through garbage
	StartTask("Read through garbage");
	EndTask(tok.ExpectToken("third"));

	// Read 11 tokens
	StartTask("Read 11 tokens");
		Print("\n");
		bool bResult = true;

		for (int i=0; i<11; i++) {
			s = tok.GetNextToken();
			Print("    %s\n", s.GetASCII());
			if (i ==  0 && s != "zero")  bResult = false;
			if (i ==  1 && s != "one")	 bResult = false;
			if (i ==  2 && s != "two")	 bResult = false;
			if (i ==  3 && s != "three") bResult = false;
			if (i ==  4 && s != "four")	 bResult = false;
			if (i ==  5 && s != "five")	 bResult = false;
			if (i ==  6 && s != "six")	 bResult = false;
			if (i ==  7 && s != "seven") bResult = false;
			if (i ==  8 && s != "eight") bResult = false;
			if (i ==  9 && s != "nine")	 bResult = false;
			if (i == 10 && s != "ten")	 bResult = false;
		}
	EndTask(bResult);

	// Read simple line of text
	StartTask("Read simple line of text");
		Print("\n");
		bResult = true;

		s = tok.GetNextToken(); Print("    %s\n", s.GetASCII());
		if (s != "A")		bResult = false;
		s = tok.GetNextToken(); Print("    %s\n", s.GetASCII());
		if (s != "simple")	bResult = false;
		s = tok.GetNextToken(); Print("    %s\n", s.GetASCII());
		if (s != "line")	bResult = false;
		s = tok.GetNextToken(); Print("    %s\n", s.GetASCII());
		if (s != "of")		bResult = false;
		s = tok.GetNextToken(); Print("    %s\n", s.GetASCII());
		if (s != "text")	bResult = false;
	EndTask(bResult);

	// Read quoted line
	StartTask("Read quoted line");
		Print("\n");
		bResult = true;

		s = tok.GetNextToken(); Print("    %s\n", s.GetASCII());
		if (s != "\"")					 bResult = false;
		s = tok.GetNextToken(); Print("    %s\n", s.GetASCII());
		if (s != "Another line of text") bResult = false;
		s = tok.GetNextToken(); Print("    %s\n", s.GetASCII());
		if (s != "\"")					 bResult = false;
	EndTask(bResult);

	// Read quotes within quotes
	StartTask("Read quotes within quotes");
		Print("\n");
		bResult = true;

		s = tok.GetNextToken(); Print("    %s\n", s.GetASCII());
		if (s != "\"")					 bResult = false;
		s = tok.GetNextToken(); Print("    %s\n", s.GetASCII());
		if (s != "Quotes within 'quotes'") bResult = false;
		s = tok.GetNextToken(); Print("    %s\n", s.GetASCII());
		if (s != "\"")					 bResult = false;

		s = tok.GetNextToken(); Print("    %s\n", s.GetASCII());
		if (s != "'")					 bResult = false;
		s = tok.GetNextToken(); Print("    %s\n", s.GetASCII());
		if (s != "other \"way\" round")  bResult = false;
		s = tok.GetNextToken(); Print("    %s\n", s.GetASCII());
		if (s != "'")					 bResult = false;
	EndTask(bResult);

	// Read C code
	StartTask("Read C code");
		Print("\n");
		bResult = true;

		// Parse 'void'
		s = tok.GetNextToken(); Print("    %s\n", s.GetASCII());
		if (s != "void") bResult = false;

		// Parse code (should be exactly 32 tokens)
		s = tok.GetNextToken();
		int nCount = 0;
		while (s.GetLength() && s != "EOF") {
			Print("    %s\n", s.GetASCII());
			s = tok.GetNextToken();
			nCount++;
		}
		if (nCount != 32) bResult = false;

		// Parse 'EOF'
		Print("    %s\n", s.GetASCII());
		if (s != "EOF") bResult = false;
	EndTask(bResult);

	// Parse vector of floats
	StartTask("Parse vector of floats");
		Print("\n");
		bResult = true;

		// Parse 'vector'
		if (!tok.ExpectToken("vector")) bResult = false;

		// Parse vector of floats
		Array<float> cVector;
		tok.ParseVector(cVector, "(", ")", "");
		for (uint32 i=0; i<cVector.GetNumOfElements(); i++) {
			Print("    %g\n", cVector[i]);
		}
		if (cVector.GetNumOfElements() != 3) bResult = false;
		if (cVector[0] != 123.0f) bResult = false;
		if (cVector[1] != 25.43f) bResult = false;
		if (cVector[2] != 16.4f)  bResult = false;
	EndTask(bResult);

	// Parse vector of strings
	StartTask("Parse vector of strings");
		Print("\n");
		bResult = true;

		// Parse 'vector'
		if (!tok.ExpectToken("vector")) bResult = false;

		// Parse vector of floats
		Array<String> cVector2;
		tok.ParseVector(cVector2, "[", "]", ",");
		for (uint32 i=0; i<cVector2.GetNumOfElements(); i++) {
			Print("    %s\n", cVector2[i].GetASCII());
		}
		if (cVector2.GetNumOfElements() != 3) bResult = false;
		if (cVector2[0] != "one")   bResult = false;
		if (cVector2[1] != "two")   bResult = false;
		if (cVector2[2] != "three") bResult = false;
	EndTask(bResult);

	// Parse equation (string)
	StartTask("Parse equations");
		Print("\n");
		bResult = true;

		String sName, sValue;
		if (!tok.ParseEquation(sName, sValue)) bResult = false;
		Print("    %s -> %s\n", sName.GetASCII(), sValue.GetASCII());
		if (sValue != "test") bResult = false;

		int nValue;
		if (!tok.ParseEquation(sName, nValue)) bResult = false;
		Print("    %s -> %d\n", sName.GetASCII(), nValue);
		if (nValue != 123) bResult = false;

		float fValue;
		if (!tok.ParseEquation(sName, fValue)) bResult = false;
		Print("    %s -> %g\n", sName.GetASCII(), fValue);
		if (fValue != 12.5f) bResult = false;
	EndTask(bResult);

	// Stop tokenizer
	StartTask("Stop tokenizer");
		tok.Stop();
	EndTask(true);
}
