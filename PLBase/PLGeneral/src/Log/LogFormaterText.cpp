/*********************************************************\
 *  File: LogFormaterText.cpp                            *
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
#include "PLGeneral/Log/LogFormaterText.h"


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
LogFormaterText::LogFormaterText()
{
}

/**
*  @brief
*    Destructor
*/
LogFormaterText::~LogFormaterText()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
LogFormaterText::LogFormaterText(const LogFormaterText &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
LogFormaterText &LogFormaterText::operator =(const LogFormaterText &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Private virtual LogFormater functions                 ]
//[-------------------------------------------------------]
bool LogFormaterText::Open(const String &sFilename)
{
	// Open the log file via the helper function of the base-class
	m_pFile = OpenFile(sFilename);

	// Error?
	return m_pFile != nullptr;
}

bool LogFormaterText::Close()
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

bool LogFormaterText::Output(uint8 nLogLevel, const String &sText)
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

bool LogFormaterText::Flush()
{
	return m_pFile && m_pFile->Flush();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
