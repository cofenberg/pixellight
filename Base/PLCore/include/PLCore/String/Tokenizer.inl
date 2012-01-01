/*********************************************************\
 *  File: Tokenizer.inl                                  *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
inline Tokenizer::~Tokenizer()
{
	// Stop tokenizer
	Stop();
}

/**
*  @brief
*    Get delimiters (characters that a treated as whitespace)
*/
inline String Tokenizer::GetDelimiters() const
{
	return m_sDelimiters;
}

/**
*  @brief
*    Set delimiters (characters that a treated as whitespace)
*/
inline void Tokenizer::SetDelimiters(const String &sDelimiters)
{
	m_sDelimiters = sDelimiters;
}

/**
*  @brief
*    Get single characters
*/
inline String Tokenizer::GetSingleChars() const
{
	return m_sSingleChars;
}

/**
*  @brief
*    Set single characters
*/
inline void Tokenizer::SetSingleChars(const String &sSingleChars)
{
	m_sSingleChars = sSingleChars;
}

/**
*  @brief
*    Get characters that are used for quotes
*/
inline String Tokenizer::GetQuotes() const
{
	return m_sQuotes;
}

/**
*  @brief
*    Set characters that are used for quotes
*/
inline void Tokenizer::SetQuotes(const String &sQuotes)
{
	m_sQuotes = sQuotes;
}

/**
*  @brief
*    Get the string that starts a multi-line comment
*/
inline String Tokenizer::GetCommentStartTag() const
{
	return m_sCommentStartTag;
}

/**
*  @brief
*    Set the string that starts a multi-line comment
*/
inline void Tokenizer::SetCommentStartTag(const String &sCommentStartTag)
{
	m_sCommentStartTag = sCommentStartTag;
}

/**
*  @brief
*    Get the string that ends a multi-line comment
*/
inline String Tokenizer::GetCommentEndTag() const
{
	return m_sCommentEndTag;
}

/**
*  @brief
*    Set the string that ends a multi-line comment
*/
inline void Tokenizer::SetCommentEndTag(const String &sCommentEndTag)
{
	m_sCommentEndTag = sCommentEndTag;
}

/**
*  @brief
*    Get the string that starts a single-line comment
*/
inline String Tokenizer::GetSingleLineComment() const
{
	return m_sSingleLineComment;
}

/**
*  @brief
*    Set the string that starts a single-line comment
*/
inline void Tokenizer::SetSingleLineComment(const String &sSingleLineComment)
{
	m_sSingleLineComment = sSingleLineComment;
}

/**
*  @brief
*    Get case sensitivity flag
*/
inline bool Tokenizer::IsCaseSensitive() const
{
	return m_bCaseSensitive;
}

/**
*  @brief
*    Set case sensitivity flag
*/
inline void Tokenizer::SetCaseSensitive(bool bCaseSensitive)
{
	m_bCaseSensitive = bCaseSensitive;
}

/**
*  @brief
*    Returns the current token
*/
inline String Tokenizer::GetToken() const
{
	// Return current token
	return m_sToken;
}

/**
*  @brief
*    Compares the current token with a given string
*/
inline bool Tokenizer::CompareToken(const String &sExpected)
{
	return (m_bCaseSensitive ? m_sToken.Compare(sExpected) : m_sToken.CompareNoCase(sExpected));
}

/**
*  @brief
*    Returns the current position in the stream
*/
inline uint32 Tokenizer::GetPosition() const
{
	// Return current position
	return m_nPosition;
}

/**
*  @brief
*    Returns the current line (counted by '\n' occurrences)
*/
inline uint32 Tokenizer::GetLine() const
{
	// Return current line
	return m_nLine;
}

/**
*  @brief
*    Deletes the last saved state from the stack
*/
inline void Tokenizer::DropState()
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
inline bool Tokenizer::ParseNumber(int &nNumber)
{
	const String sToken = GetNextToken();
	if (sToken.GetLength()) {
		nNumber = sToken.GetInt();

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Expects the next token to be a floating point number and returns it as a float value
*/
inline bool Tokenizer::ParseNumber(float &fNumber)
{
	const String sToken = GetNextToken();
	if (sToken.GetLength()) {
		fNumber = sToken.GetFloat();

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Expects the next token to be a floating point number and returns it as a double value
*/
inline bool Tokenizer::ParseNumber(double &dNumber)
{
	const String sToken = GetNextToken();
	if (sToken.GetLength()) {
		dNumber = sToken.GetDouble();

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Expects the next tokens to be an equation and returns it
*/
inline bool Tokenizer::ParseEquation(String &sName, int &nValue, const String &sEquation)
{
	String sValue;
	if (ParseEquation(sName, sValue, sEquation)) {
		nValue = sValue.GetInt();

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Expects the next tokens to be an equation and returns it
*/
inline bool Tokenizer::ParseEquation(String &sName, float &fValue, const String &sEquation)
{
	String sValue;
	if (ParseEquation(sName, sValue, sEquation)) {
		fValue = sValue.GetFloat();

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Expects the next tokens to be an equation and returns it
*/
inline bool Tokenizer::ParseEquation(String &sName, double &dValue, const String &sEquation)
{
	String sValue;
	if (ParseEquation(sName, sValue, sEquation)) {
		dValue = sValue.GetDouble();

		// Done
		return true;
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
