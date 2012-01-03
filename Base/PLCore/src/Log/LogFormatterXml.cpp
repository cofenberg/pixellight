/*********************************************************\
 *  File: LogFormatterXml.cpp                            *
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/File/File.h"
#include "PLCore/Log/Log.h"
#include "PLCore/Log/LogFormatterXml.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
LogFormatterXml::LogFormatterXml()
{
}

/**
*  @brief
*    Destructor
*/
LogFormatterXml::~LogFormatterXml()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
LogFormatterXml::LogFormatterXml(const LogFormatterXml &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
LogFormatterXml &LogFormatterXml::operator =(const LogFormatterXml &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Returns the XML formated text the given log level
*/
String LogFormatterXml::GetXmlFormatedText(uint8 nLogLevel, const String &sText) const
{
	String sTags     = "\t<a>|</a>";
	String sLogLevel = Log::GetInstance()->LogLevelToString(nLogLevel);

	if (sLogLevel.GetLength() > 0) {
		// Replace the 'a' with the text representation of the log level
		sTags.Replace('a', sLogLevel);
	} else {
		// Replace the 'a' with intern (because used log level is == 0 => internal log message)
		sTags.Replace("a", "Intern");
	}

	// Replace the '|' with the text in sText
	sTags.Replace('|', sText);

	return sTags;
}


//[-------------------------------------------------------]
//[ Private virtual LogFormatter functions                ]
//[-------------------------------------------------------]
bool LogFormatterXml::Open(const String &sFilename)
{
	// Open the log file via the helper function of the base class, use UTF8 string encoding format so one can also put cryptic none English characters into the log
	m_pFile = OpenFile(sFilename, String::UTF8);

	// Error?
	if (m_pFile) {
		// Write the start tags
		if (m_pFile->PrintLn("<?xml version=\"1.0\" ?>\n<Log>"))
			return true; // Done
	}

	// Error!
	return false;
}

bool LogFormatterXml::Close()
{
	// Is the file open?
	if (m_pFile) {
		// Write the end tag
		if (m_pFile->PrintLn("</Log>"))
			return true; // Done

		// Close file
		m_pFile->Close();

		// Reset data
		delete m_pFile;
		m_pFile = nullptr;

		// Done
		return true;
	}

	// Error, the log was not even open!
	return false;
}

bool LogFormatterXml::Output(uint8 nLogLevel, const String &sText)
{
	if (m_pFile) {
		// Write the text and a newline
		if (m_pFile->PrintLn(GetXmlFormatedText(nLogLevel, sText)))
			return true; // Done
	}

	// Error!
	return false;
}

bool LogFormatterXml::Flush()
{
	return m_pFile && m_pFile->Flush();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
