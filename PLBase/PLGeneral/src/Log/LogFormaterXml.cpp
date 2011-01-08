/*********************************************************\
 *  File: LogFormaterXml.cpp                             *
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
#include "PLGeneral/File/File.h"
#include "PLGeneral/Log/Log.h"
#include "PLGeneral/Log/LogFormaterXml.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
LogFormaterXml::LogFormaterXml()
{
}

/**
*  @brief
*    Destructor
*/
LogFormaterXml::~LogFormaterXml()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
LogFormaterXml::LogFormaterXml(const LogFormaterXml &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
LogFormaterXml &LogFormaterXml::operator =(const LogFormaterXml &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Returns the XML formated text the given log level
*/
String LogFormaterXml::GetXmlFormatedText(uint8 nLogLevel, const String &sText) const
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
//[ Private virtual LogFormater functions                 ]
//[-------------------------------------------------------]
bool LogFormaterXml::Open(const String &sFilename)
{
	// Open the log file via the helper function of the base class
	m_pFile = OpenFile(sFilename);

	// Error?
	if (m_pFile) {
		// Write the start tags
		if (m_pFile->PrintLn("<?xml version=\"1.0\" ?>\n<Log>"))
			return true; // Done
	}

	// Error!
	return false;
}

bool LogFormaterXml::Close()
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

bool LogFormaterXml::Output(uint8 nLogLevel, const String &sText)
{
	if (m_pFile) {
		// Write the text and a newline
		if (m_pFile->PrintLn(GetXmlFormatedText(nLogLevel, sText)))
			return true; // Done
	}

	// Error!
	return false;
}

bool LogFormaterXml::Flush()
{
	return m_pFile && m_pFile->Flush();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
