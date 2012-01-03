/*********************************************************\
 *  File: Log.inl                                        *
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
#include "PLCore/Log/LogFormatter.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get verbose mode (write log entries to console)
*/
inline bool Log::IsVerbose() const
{
	return m_bVerbose;
}

/**
*  @brief
*    Set verbose mode (write log entries to console)
*/
inline void Log::SetVerbose(bool bVerbose, bool bVerboseLogLevelPrefix)
{
	m_bVerbose				 = bVerbose;
	m_bVerboseLogLevelPrefix = bVerboseLogLevelPrefix;
}

/**
*  @brief
*    Get log filename
*/
inline String Log::GetFilename() const
{
	// Return filename
	return m_sFilename;
}

/**
*  @brief
*    Write a string into the log
*/
inline bool Log::Output(uint8 nLogLevel, const String &sText)
{
	// Check log level
	return (nLogLevel > Quiet && nLogLevel <= m_nLogLevel && Write(nLogLevel, sText));
}

/**
*  @brief
*    Get current log level
*/
inline uint8 Log::GetLogLevel() const
{
	return m_nLogLevel;
}

/**
*  @brief
*    Set current log level
*/
inline void Log::SetLogLevel(uint8 nLogLevel)
{
	// Is this log level already set?
	if (m_nLogLevel != nLogLevel) {
		// Set log level
		m_nLogLevel = nLogLevel;

		// Write log message
		Write(Debug, "[Enter log level \"" + LogLevelToString(nLogLevel) + "\"]");
	}
}

/**
*  @brief
*    Get log level for automatic flush
*/
inline uint8 Log::GetFlushLogLevel() const
{
	return m_nFlushLogLevel;
}

/**
*  @brief
*    Set log level for automatic flush
*/
inline void Log::SetFlushLogLevel(uint8 nFlushLogLevel)
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
inline bool Log::Flush()
{
	// Is there anything to flush?
	if (m_nFlushMessages && m_pLogFormatter) {
		// Flush on disc
		m_nFlushMessages = 0;
		return m_pLogFormatter->Flush();
	} else {
		// No need to flush anything
		return false;
	}
}

/**
*  @brief
*    Get current amount of buffered log messages
*/
inline uint32 Log::GetBufferCount() const
{
	return m_nBufferedMessages;
}

/**
*  @brief
*    Get a copy of the queue which holds the last log messages
*/
inline const Queue<String> &Log::GetLastMessages() const
{
	return m_qLastMessages;
}

/**
*  @brief
*    Get current log formatter
*/
inline LogFormatter *Log::GetLogFormatter() const
{
	return m_pLogFormatter;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
