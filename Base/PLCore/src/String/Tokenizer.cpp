/*********************************************************\
 *  File: Tokenizer.cpp                                  *
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


// [TODO]
// - BufferedReader is not ideal - too many strings are allocated, this should
//   not be necessary in case of string buffers.
//   Also BufferedReaderFile should work on stream rather than files - but this is
//   only possible if a general stream interface has been created :-)


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/BufferedReaderFile.h"
#include "PLCore/String/BufferedReaderString.h"
#include "PLCore/String/Tokenizer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
const String Tokenizer::EndOfLine = '\n';


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Tokenizer::Tokenizer() :
	m_sDelimiters(" \t\r\n"),
	m_sSingleChars("{}()[]<*>/=,;\""),
	m_sQuotes("\"\'"),
	m_sCommentStartTag("/*"),
	m_sCommentEndTag("*/"),
	m_sSingleLineComment("//"),
	m_bCaseSensitive(false),
	m_pStream(nullptr),
	m_nPosition(0),
	m_nLine(0),
	m_nParseMode(eEatGarbage)
{
}

/**
*  @brief
*    Destructor
*/
Tokenizer::~Tokenizer()
{
	// Stop tokenizer
	Stop();
}

/**
*  @brief
*    Get delimiters (characters that a treated as whitespace)
*/
String Tokenizer::GetDelimiters() const
{
	return m_sDelimiters;
}

/**
*  @brief
*    Set delimiters (characters that a treated as whitespace)
*/
void Tokenizer::SetDelimiters(const String &sDelimiters)
{
	m_sDelimiters = sDelimiters;
}

/**
*  @brief
*    Get single characters
*/
String Tokenizer::GetSingleChars() const
{
	return m_sSingleChars;
}

/**
*  @brief
*    Set single characters
*/
void Tokenizer::SetSingleChars(const String &sSingleChars)
{
	m_sSingleChars = sSingleChars;
}

/**
*  @brief
*    Get characters that are used for quotes
*/
String Tokenizer::GetQuotes() const
{
	return m_sQuotes;
}

/**
*  @brief
*    Set characters that are used for quotes
*/
void Tokenizer::SetQuotes(const String &sQuotes)
{
	m_sQuotes = sQuotes;
}

/**
*  @brief
*    Get the string that starts a multi-line comment
*/
String Tokenizer::GetCommentStartTag() const
{
	return m_sCommentStartTag;
}

/**
*  @brief
*    Set the string that starts a multi-line comment
*/
void Tokenizer::SetCommentStartTag(const String &sCommentStartTag)
{
	m_sCommentStartTag = sCommentStartTag;
}

/**
*  @brief
*    Get the string that ends a multi-line comment
*/
String Tokenizer::GetCommentEndTag() const
{
	return m_sCommentEndTag;
}

/**
*  @brief
*    Set the string that ends a multi-line comment
*/
void Tokenizer::SetCommentEndTag(const String &sCommentEndTag)
{
	m_sCommentEndTag = sCommentEndTag;
}

/**
*  @brief
*    Get the string that starts a single-line comment
*/
String Tokenizer::GetSingleLineComment() const
{
	return m_sSingleLineComment;
}

/**
*  @brief
*    Set the string that starts a single-line comment
*/
void Tokenizer::SetSingleLineComment(const String &sSingleLineComment)
{
	m_sSingleLineComment = sSingleLineComment;
}

/**
*  @brief
*    Get case sensitivity flag
*/
bool Tokenizer::IsCaseSensitive() const
{
	return m_bCaseSensitive;
}

/**
*  @brief
*    Set case sensitivity flag
*/
void Tokenizer::SetCaseSensitive(bool bCaseSensitive)
{
	m_bCaseSensitive = bCaseSensitive;
}

/**
*  @brief
*    Starts the tokenizer on a string
*/
void Tokenizer::Start(const String &sBuffer)
{
	// Start tokenizer
	Stop();
	m_pStream = new BufferedReaderString(sBuffer);
}

/**
*  @brief
*    Starts the tokenizer on a file
*/
void Tokenizer::Start(File &cFile)
{
	// Start tokenizer
	Stop();
	m_pStream = new BufferedReaderFile(cFile);
}

/**
*  @brief
*    Stops the tokenizer
*/
void Tokenizer::Stop()
{
	// Stop tokenizer
	if (m_pStream) {
		delete m_pStream;
		m_pStream = nullptr;
	}
	m_sToken     = "";
	m_nPosition  = 0;
	m_nLine      = 0;
	m_nParseMode = eEatGarbage;
	m_sEndTag    = "";
	m_cStateStack.Clear();
}

/**
*  @brief
*    Reads all tokens until the end of the stream
*/
Array<String> Tokenizer::GetTokens()
{
	// Read tokens
	Array<String> cTokens;
	String sToken = GetNextToken();
	while (sToken.GetLength()) {
		// Add token
		cTokens.Add(sToken);

		// Next token
		sToken = GetNextToken();
	}

	// Return array of tokens
	return cTokens;
}

/**
*  @brief
*    Reads the next token from the stream
*/
String Tokenizer::GetNextToken()
{
	// Read input
	m_sToken = "";
	while (m_pStream && !m_pStream->IsEof()) {
		// Get character
		const char cChar = m_pStream->GetChar();

		// Do the work
		switch (m_nParseMode) {
			// Eat garbage until the first character of a word has been found
			case eEatGarbage:
				if (m_sCommentStartTag.GetLength() && StreamIsString(m_sCommentStartTag)) {
					// The beginning of a comment has been found
					StreamRead(m_sCommentStartTag.GetLength());
					m_sEndTag	 = m_sCommentEndTag;
					m_nParseMode = eSkipComment;
				} else if (m_sSingleLineComment.GetLength() && StreamIsString(m_sSingleLineComment)) {
					// The beginning of a comment has been found
					StreamRead(m_sSingleLineComment.GetLength());
					m_sEndTag	 = EndOfLine;
					m_nParseMode = eSkipComment;
				} else if (StreamIsChar(m_sQuotes)) {
					// The beginning of a quote has been found
					StreamRead(1);
					m_sEndTag	 = cChar;
					m_nParseMode = eReadQuote;
				} else if (StreamIsChar(m_sDelimiters)) {
					// Only more garbage found
					StreamRead(1);
				} else if (StreamIsChar(m_sSingleChars)) {
					// A single character word has been found
					m_nParseMode = eSingleChar;
				} else {
					// The beginning of a word has been found
					m_nParseMode = eReadWord;
				}
				break;

			// Read a word until a delimiter has been found
			case eReadWord:
				if (m_sCommentStartTag.GetLength() && StreamIsString(m_sCommentStartTag)) {
					// The beginning of a comment has been found
					StreamRead(m_sCommentStartTag.GetLength());
					m_sEndTag	 = m_sCommentEndTag;
					m_nParseMode = eSkipComment;
				} else if (m_sSingleLineComment.GetLength() && StreamIsString(m_sSingleLineComment)) {
					// The beginning of a comment has been found
					StreamRead(m_sSingleLineComment.GetLength());
					m_sEndTag	 = EndOfLine;
					m_nParseMode = eSkipComment;
				} else if (StreamIsChar(m_sQuotes)) {
					// The beginning of a quote has been found
					StreamRead(1);
					m_sEndTag	 = cChar;
					m_nParseMode = eReadQuote;
				} else if (StreamIsChar(m_sDelimiters)) {
					// A delimiter has been found
					StreamRead(1);
					m_nParseMode = eEatGarbage;
				} else if (StreamIsChar(m_sSingleChars)) {
					// A single character word has been found
					m_nParseMode = eSingleChar;
				} else {
					// Read word
					m_sToken += cChar;
					StreamRead(1);
				}

				// Return word if one has been found
				if (m_nParseMode != eReadWord && m_sToken.GetLength()) {
					return m_sToken;
				}
				break;

			// Read a single character word
			case eSingleChar:
				// Return the single character word
				StreamRead(1);
				m_nParseMode = eEatGarbage;
				m_sToken	 = cChar;
				return m_sToken;

			// Read the beginning of a quote
			case eReadQuote:
				m_nParseMode = eReadQuoteInside;
				m_sToken	 = m_sEndTag;
				return m_sEndTag;

			// Read until the end quote has been found
			case eReadQuoteInside:
				if (StreamIsString(m_sEndTag)) {
					// Return string inside the quote
					m_nParseMode = eReadQuoteEnd;
					if (m_sToken.GetLength()) return m_sToken;
				} else {
					m_sToken += cChar;
					StreamRead(1);
				}
				break;

			// Read the end of a quote
			case eReadQuoteEnd:
				StreamRead(m_sEndTag.GetLength());
				m_nParseMode = eEatGarbage;
				m_sToken	 = m_sEndTag;
				return m_sEndTag;

			// Skip a comment until the comment end-tag has been found
			case eSkipComment:
				if (StreamIsString(m_sEndTag)) {
					StreamRead(m_sEndTag.GetLength());
					m_nParseMode = eEatGarbage;
				} else {
					StreamRead(1);
				}
				break;
		}
	}

	// Return token
	return m_sToken;
}

/**
*  @brief
*    Expects the next token to be equal to a given string
*/
bool Tokenizer::ExpectToken(const String &sExpected)
{
	PushState();
	String sToken = GetNextToken();
	if (!sToken.GetLength() || !CompareToken(sExpected)) {
		PopState();

		// The next token is not equal to the string
		return false;
	} else {
		DropState();

		// The next token is equal to the string
		return true;
	}
}

/**
*  @brief
*    Finds a given token in the stream
*/
bool Tokenizer::FindToken(const String &sExpected)
{
	// Check expected string
	if (sExpected.GetLength()) {
		// Read first token
		PushState();
		String sToken = GetNextToken();

		// Read tokens
		while (sToken.GetLength()) {
			// Token found?
			if (CompareToken(sExpected)) {
				PopState();
				return true;
			}

			// Next token
			DropState();
			PushState();
			sToken = GetNextToken();
		}
		DropState();
	}

	// Not found
	return false;
}

/**
*  @brief
*    Returns the current token
*/
String Tokenizer::GetToken() const
{
	// Return current token
	return m_sToken;
}

/**
*  @brief
*    Compares the current token with a given string
*/
bool Tokenizer::CompareToken(const String &sExpected)
{
	return m_bCaseSensitive ? m_sToken.Compare(sExpected) : m_sToken.CompareNoCase(sExpected);
}

/**
*  @brief
*    Returns the current position in the stream
*/
uint32 Tokenizer::GetPosition() const
{
	// Return current position
	return m_nPosition;
}

/**
*  @brief
*    Returns the current line (counted by '\n' occurences)
*/
uint32 Tokenizer::GetLine() const
{
	// Return current line
	return m_nLine;
}

/**
*  @brief
*    Saves the current state of the tokenizer on a state stack
*/
void Tokenizer::PushState()
{
	// Push current state onto the stack
	STokenizerState sState;
	sState.m_sToken		= m_sToken;
	sState.m_nPosition	= m_nPosition;
	sState.m_nLine		= m_nLine;
	sState.m_nParseMode	= m_nParseMode;
	sState.m_sEndTag	= m_sEndTag;
	m_cStateStack.Push(sState);
}

/**
*  @brief
*    Restores the last saved state from the stack
*/
void Tokenizer::PopState()
{
	// Is the stack empty?
	if (m_cStateStack.GetNumOfElements() > 0) {
		// Restore state
		STokenizerState sState;
		m_cStateStack.Pop(&sState);
		m_sToken	 = sState.m_sToken;
		m_nPosition	 = sState.m_nPosition;
		m_nLine		 = sState.m_nLine;
		m_nParseMode = sState.m_nParseMode;
		m_sEndTag	 = sState.m_sEndTag;
		if (m_pStream) m_pStream->Seek(m_nPosition);
	}
}

/**
*  @brief
*    Deletes the last saved state from the stack
*/
void Tokenizer::DropState()
{
	// Is the stack empty?
	if (m_cStateStack.GetNumOfElements() > 0) {
		// Pop saved state from stack
		m_cStateStack.Pop();
	}
}

/**
*  @brief
*    Expects the next token to be a number and returns it as an integer value
*/
bool Tokenizer::ParseNumber(int &nNumber)
{
	String sToken = GetNextToken();
	if (sToken.GetLength()) {
		nNumber = sToken.GetInt();

		// Done
		return true;
	} else return false; // Error!
}

/**
*  @brief
*    Expects the next token to be a floating point number and returns it as a float value
*/
bool Tokenizer::ParseNumber(float &fNumber)
{
	String sToken = GetNextToken();
	if (sToken.GetLength()) {
		fNumber = sToken.GetFloat();

		// Done
		return true;
	} else return false; // Error!
}

/**
*  @brief
*    Expects the next token to be a floating point number and returns it as a double value
*/
bool Tokenizer::ParseNumber(double &dNumber)
{
	String sToken = GetNextToken();
	if (sToken.GetLength()) {
		dNumber = sToken.GetDouble();

		// Done
		return true;
	} else return false; // Error!
}

/**
*  @brief
*    Expects the next tokens to be a vector and returns it as an array of strings
*/
bool Tokenizer::ParseVector(Array<String> &cVector, const String &sStart, const String &sEnd, const String &sSeparator)
{
	// Start parsing
	PushState();

	// Expect open bracket
	if (ExpectToken(sStart)) {
		// Read elements
		bool bFirst = true;
		while (!ExpectToken(sEnd)) {
			// Expect separator
			if (bFirst) bFirst = false;
			else if (sSeparator.GetLength() && !ExpectToken(sSeparator)) {
				PopState();

				// Error!
				return false;
			}

			// Expect an element
			String sElement = GetNextToken();
			if (!sElement.GetLength() || CompareToken(sSeparator) || CompareToken(sEnd)) {
				// Error!
				PopState();
				return false;
			}
			cVector.Add(sElement);
		}

		// Success
		DropState();
		return true;
	} else {
		PopState();

		// Error!
		return false;
	}
}

/**
*  @brief
*    Expects the next tokens to be a vector and returns it as an array of ints
*/
bool Tokenizer::ParseVector(Array<int> &cVector, const String &sStart, const String &sEnd, const String &sSeparator)
{
	// Parse string vector
	Array<String> cStringVector;
	if (!ParseVector(cStringVector, sStart, sEnd, sSeparator)) return false; // Error!

	// Create int vector
	for (uint32 i=0; i<cStringVector.GetNumOfElements(); i++)
		cVector.Add(cStringVector[i].GetInt());

	// Done
	return true;
}

/**
*  @brief
*    Expects the next tokens to be a vector and returns it as an array of floats
*/
bool Tokenizer::ParseVector(Array<float> &cVector, const String &sStart, const String &sEnd, const String &sSeparator)
{
	// Parse string vector
	Array<String> cStringVector;
	if (!ParseVector(cStringVector, sStart, sEnd, sSeparator)) return false; // Error!

	// Create int vector
	for (uint32 i=0; i<cStringVector.GetNumOfElements(); i++)
		cVector.Add(cStringVector[i].GetFloat());

	// Done
	return true;
}

/**
*  @brief
*    Expects the next tokens to be a vector and returns it as an array of doubles
*/
bool Tokenizer::ParseVector(Array<double> &cVector, const String &sStart, const String &sEnd, const String &sSeparator)
{
	// Parse string vector
	Array<String> cStringVector;
	if (!ParseVector(cStringVector, sStart, sEnd, sSeparator))
		return false; // Error!

	// Create int vector
	for (uint32 i=0; i<cStringVector.GetNumOfElements(); i++)
		cVector.Add(cStringVector[i].GetDouble());

	// Done
	return true;
}

/**
*  @brief
*    Expects the next tokens to be an equation and returns it
*/
bool Tokenizer::ParseEquation(String &sName, String &sValue, const String &sEquation)
{
	// Start parsing
	PushState();

	// Expect name
	String sToken = GetNextToken();
	if (sToken.GetLength()) {
		// Store name
		sName = sToken;

		// Expect equation
		sToken = GetNextToken();
		if (sToken.GetLength()) {
			if (!sEquation.GetLength() || CompareToken(sEquation)) {
				// Read value
				sToken = GetNextToken();
				if (sToken.GetLength()) {
					// Store value
					sValue = sToken;
					DropState();

					// Done
					return true;
				}
			}
		}
	}

	// An error has occurred
	PopState();
	return false;
}

/**
*  @brief
*    Expects the next tokens to be an equation and returns it
*/
bool Tokenizer::ParseEquation(String &sName, int &nValue, const String &sEquation)
{
	String sValue;
	if (ParseEquation(sName, sValue, sEquation)) {
		nValue = sValue.GetInt();

		// Done
		return true;
	} else return false; // Error!
}

/**
*  @brief
*    Expects the next tokens to be an equation and returns it
*/
bool Tokenizer::ParseEquation(String &sName, float &fValue, const String &sEquation)
{
	String sValue;
	if (ParseEquation(sName, sValue, sEquation)) {
		fValue = sValue.GetFloat();

		// Done
		return true;
	} else return false; // Error!
}

/**
*  @brief
*    Expects the next tokens to be an equation and returns it
*/
bool Tokenizer::ParseEquation(String &sName, double &dValue, const String &sEquation)
{
	String sValue;
	if (ParseEquation(sName, sValue, sEquation)) {
		dValue = sValue.GetDouble();

		// Done
		return true;
	} else return false; // Error!
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Tokenizer::Tokenizer(const Tokenizer &cSource) :
	m_sDelimiters(" \t\r\n"),
	m_sSingleChars("{}()[]<*>/=,;\""),
	m_sQuotes("\"\'"),
	m_sCommentStartTag("/*"),
	m_sCommentEndTag("*/"),
	m_sSingleLineComment("//"),
	m_bCaseSensitive(false),
	m_pStream(nullptr),
	m_nPosition(0),
	m_nLine(0),
	m_nParseMode(eEatGarbage)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Tokenizer &Tokenizer::operator =(const Tokenizer &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Checks if the next character in the stream is one of the given characters
*/
bool Tokenizer::StreamIsChar(const String &sCharacters)
{
	// Check next character
	return !m_pStream->IsEof() && sCharacters.IndexOf(m_pStream->GetChar()) >= 0;
}

/**
*  @brief
*    Checks if the next string in the stream equals the given one
*/
bool Tokenizer::StreamIsString(const String &sString)
{
	if (!m_pStream->IsEof())
		return m_bCaseSensitive ? m_pStream->IsString(sString) : m_pStream->IsStringNoCase(sString);
	else
		return false;
}

/**
*  @brief
*    Reads the next bytes of the stream
*/
void Tokenizer::StreamRead(uint32 nCount)
{
	// Read next character(s)
	for (uint32 i=0; i<nCount; i++) {
		if (m_pStream->ReadChar() == '\n')
			m_nLine++;
	}
	m_nPosition += nCount;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
