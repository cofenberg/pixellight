/*********************************************************\
 *  File: Log.cpp                                        *
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
#include <stdio.h>	// For "fputs" and "stdout" inside "Log::Write()"
#include "PLGeneral/File/Url.h"
#include "PLGeneral/Log/LogFormaterText.h"
#include "PLGeneral/Log/LogFormaterXml.h"
#include "PLGeneral/Log/LogFormaterHtml.h"
#include "PLGeneral/Log/Log.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
// For fast Log::LogLevelToString()
const String g_sLogLevelToString[] = {
	"Quiet",
	"Always",
	"Critical",
	"Error",
	"Warning",
	"Info",
	"Debug"
};


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get verbose mode (write log entries to console)
*/
bool Log::IsVerbose() const
{
	return m_bVerbose;
}

/**
*  @brief
*    Set verbose mode (write log entries to console)
*/
void Log::SetVerbose(bool bVerbose, bool bVerboseLogLevelPrefix )
{
	m_bVerbose				 = bVerbose;
	m_bVerboseLogLevelPrefix = bVerboseLogLevelPrefix;
}

/**
*  @brief
*    Open the log file by using a filename
*/
bool Log::Open(const String &sFilename)
{
	// Ensure that the log is currently closed
	Close();

	// Get the filename extension
	const String sExtension = Url(sFilename).GetExtension();

	// Create log formater instance by using the filename extension
	LogFormater *pLogFormater = NULL;
	if (sExtension == "txt" || sExtension == "log")
		pLogFormater = new LogFormaterText();
	else if (sExtension == "xml")
		pLogFormater = new LogFormaterXml();
	else if (sExtension == "html")
		pLogFormater = new LogFormaterHtml();

	// Open the log if a log formater instance was successfully created
	if (pLogFormater) {
		if (Open(sFilename, *pLogFormater))
			return true; // Done
		else
			delete pLogFormater; // Cleanup
	}

	// Error!
	return false;
}

/**
*  @brief
*    Open the log file by using a filename and an explicit log formater instance
*/
bool Log::Open(const String &sFilename, LogFormater &cLogFormater)
{
	// Ensure that the log is currently closed
	Close();

	// Inform the log formater that the log should be opened
	if (cLogFormater.Open(sFilename)) {
		m_sFilename    = sFilename;
		m_pLogFormater = &cLogFormater;

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Close log
*/
bool Log::Close()
{
	// Is the file open?
	if (m_pLogFormater) {
		// Close the log formater
		bool bResult = true; // By default, all went fine
		if (m_sFilename.GetLength()) {
			// Write log message
			Write(0, "Close log");

			// Inform the log formater that the log should be closed
			bResult = m_pLogFormater->Close();
		}

		// Destroy the log formater
		delete m_pLogFormater;
		m_pLogFormater = NULL;

		// Reset data
		m_sFilename = "";

		// Done
		return bResult;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Get log filename
*/
String Log::GetFilename() const
{
	// Return filename
	return m_sFilename;
}

/**
*  @brief
*    Write a string into the log
*/
bool Log::Output(uint8 nLogLevel, const String &sText)
{
	// Check log level
	return (nLogLevel > Quiet && nLogLevel <= m_nLogLevel && Write(nLogLevel, sText));
}

/**
*  @brief
*    Get current log level
*/
uint8 Log::GetLogLevel() const
{
	return m_nLogLevel;
}

/**
*  @brief
*    Set current log level
*/
void Log::SetLogLevel(uint8 nLogLevel)
{
	// Is this log level already set?
	if (m_nLogLevel != nLogLevel) {
		// Set log level
		m_nLogLevel = nLogLevel;

		// Write log message
		Write(0, "[Enter log level \"" + LogLevelToString(nLogLevel) + "\"]");
	}
}

/**
*  @brief
*    Get log level for automatic flush
*/
uint8 Log::GetFlushLogLevel() const
{
	return m_nFlushLogLevel;
}

/**
*  @brief
*    Set log level for automatic flush
*/
void Log::SetFlushLogLevel(uint8 nFlushLogLevel)
{
	// Change only if the new flush log level is not equal to the current one
	if (nFlushLogLevel != m_nFlushLogLevel) {
		// An explicit flush is necessary when the new flush log level is lower then the old one
		if (nFlushLogLevel < m_nFlushLogLevel)
			Flush();

		// Set the new flush log level
		m_nFlushLogLevel = nFlushLogLevel;
	}
}

/**
*  @brief
*    Flush output buffer to disk
*/
bool Log::Flush()
{
	// Is there anything to flush?
	if (m_nFlushMessages && m_pLogFormater) {
		// Flush on disc
		m_nFlushMessages = 0;
		return m_pLogFormater->Flush();
	} else {
		// No need to flush anything
		return false;
	}
}

/**
*  @brief
*    Get current amount of buffered log messages
*/
uint32 Log::GetBufferCount() const
{
	return m_nBufferedMessages;
}

/**
*  @brief
*    Set how many log messages should be buffered in memory
*/
void Log::SetBufferCount(uint32 nBufferCount)
{
	// Make an explicit flush
	Flush();

	// Remove surplus log messages
	if (m_nBufferedMessages > nBufferCount) {
		uint32 nToRemove = m_nBufferedMessages-nBufferCount;
		for (uint32 i=0; i<nToRemove; i++)
			m_qLastMessages.Pop();
	}

	// Set the new number of buffered messaged
	m_nBufferedMessages = nBufferCount;
}

/**
*  @brief
*    Get a copy of the queue which holds the last log messages
*/
const Queue<String> &Log::GetLastMessages() const
{
	return m_qLastMessages;
}

/**
*  @brief
*    Get a string representation of the given log level
*/
String Log::LogLevelToString(uint8 nLogLevel) const
{
		 if (!nLogLevel)		return "";
	else if (nLogLevel > Debug)	return String::Format("Debug%d", nLogLevel-Debug);
	else						return g_sLogLevelToString[nLogLevel-1];
}

/**
*  @brief
*    Get current log formater
*/
LogFormater *Log::GetLogFormater() const
{
	return m_pLogFormater;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Log::Log() :
	m_bVerbose(false),
	m_bVerboseLogLevelPrefix(true),
	m_nLogLevel(Info),
	m_nFlushLogLevel(Error),
	m_nFlushMessages(0),
	m_nBufferedMessages(10),
	m_pLogFormater(NULL)
{
}

/**
*  @brief
*    Copy constructor
*/
Log::Log(const Log &cSource) :
	m_bVerbose(false),
	m_bVerboseLogLevelPrefix(true),
	m_nLogLevel(Info),
	m_nFlushLogLevel(Error),
	m_nFlushMessages(0),
	m_nBufferedMessages(10),
	m_pLogFormater(NULL)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Destructor
*/
Log::~Log()
{
	// Close log
	Close();
}

/**
*  @brief
*    Copy operator
*/
Log &Log::operator =(const Log &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Writes a string into the log
*/
bool Log::Write(uint8 nLogLevel, const String &sText)
{
	// Is there any text to write down?
	if (sText.GetLength()) {
		// Write into the standard OS console?
		if (m_bVerbose) {
			// Prepare log message
			String sLogMessage;
			if (nLogLevel >= Quiet && m_bVerboseLogLevelPrefix) {
				sLogMessage  = "[";
				sLogMessage += LogLevelToString(nLogLevel);
				sLogMessage += "]: ";
			}
			sLogMessage += sText;
			sLogMessage += '\n';

			// Write the text into the OS console - it would be nice if this could be done using 'File::StandardOutput.Print()',
			// but this may cause problems when de-initializing the static variables :/
			fputs(sLogMessage.GetASCII(), stdout);
		}

		// Is there a log formater?
		bool bResult = true; // By default, all went fine
		if (m_pLogFormater) {
			// Write the text
			bResult = m_pLogFormater->Output(nLogLevel, sText);
			if (bResult) {
				// Remove the latest message from the list if the limit is reached
				if (m_qLastMessages.GetNumOfElements() == m_nBufferedMessages) {
					// Make an explicit flush
					Flush();

					// Remove the oldest message
					m_qLastMessages.Pop();
				}

				// Write the message in the queue
				if (m_nBufferedMessages && nLogLevel > Quiet)
					m_qLastMessages.Push("(" + LogLevelToString(nLogLevel) + ") " + sText);

				// Should be the output buffer written to the file?
				m_nFlushMessages++;
				if (nLogLevel >= m_nFlushLogLevel || m_nFlushMessages >= m_nBufferedMessages) {
					m_nFlushMessages = 0;
					if (!m_pLogFormater->Flush())
						bResult = false; // Error!
				}
			}
		}

		// Done
		return bResult;
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
