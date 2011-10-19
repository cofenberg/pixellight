/*********************************************************\
 *  File: LogFormatterText.cpp                           *
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
#include "PLCore/File/File.h"
#include "PLCore/Log/Log.h"
#include "PLCore/Log/LogFormatterText.h"


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
LogFormatterText::LogFormatterText()
{
}

/**
*  @brief
*    Destructor
*/
LogFormatterText::~LogFormatterText()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
LogFormatterText::LogFormatterText(const LogFormatterText &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
LogFormatterText &LogFormatterText::operator =(const LogFormatterText &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Private virtual LogFormatter functions                ]
//[-------------------------------------------------------]
bool LogFormatterText::Open(const String &sFilename)
{
	// Open the log file via the helper function of the base-class, use UTF8 string encoding format so one can also put cryptic none English characters into the log
	m_pFile = OpenFile(sFilename, String::UTF8);

	// Error?
	return (m_pFile != nullptr);
}

bool LogFormatterText::Close()
{
	// Is the file open?
	if (m_pFile) {
		// Close file
		m_pFile->Close();

		// Reset data
		delete m_pFile;
		m_pFile = nullptr;

		// Done
		return true;
	}

	// Log was not even open
	return false; // Error!
}

bool LogFormatterText::Output(uint8 nLogLevel, const String &sText)
{
	if (m_pFile) {
		// Prepare log message
		String sLogMessage;
		if (nLogLevel >= Log::Quiet && m_bShowLogLevelPrefix) {
			sLogMessage  = "[";
			sLogMessage += Log::GetInstance()->LogLevelToString(nLogLevel);
			sLogMessage += "]: ";
		}
		sLogMessage += sText;

		// Write the text and a newline
		if (m_pFile->PrintLn(sLogMessage))
			return true; // Done
	}

	// Error!
	return false;
}

bool LogFormatterText::Flush()
{
	return m_pFile && m_pFile->Flush();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
