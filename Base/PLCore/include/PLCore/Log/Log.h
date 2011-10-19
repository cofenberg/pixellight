/*********************************************************\
 *  File: Log.h                                          *
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


#ifndef __PLCORE_LOG_H__
#define __PLCORE_LOG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Core/Singleton.h"
#include "PLCore/String/String.h"
#include "PLCore/Container/Queue.h"


//[-------------------------------------------------------]
//[ Macro definitions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Log macro
*
*  @param[in] Level
*    Log level
*  @param[in] Text
*    Text which should be written into the log
*/
#define PL_LOG(Level, Text) { \
	if (PLCore::Log::HasInstance() && PLCore::Log::GetInstance()->GetLogLevel() >= PLCore::Log::Level) { \
		PLCore::Log::LogLevel nLogLevel = PLCore::Log::Level; /* Avoid 'expression is constant' warning */ \
		if (nLogLevel >= PLCore::Log::Debug) { \
			PLCore::String sLogString = Text; \
			PLCore::Log::GetInstance()->Output(PLCore::Log::Level, sLogString + PLCore::String::Format(", %s, %d, %s", __FILE__, __LINE__, __FUNCTION__)); \
		} else PLCore::Log::GetInstance()->Output(PLCore::Log::Level, Text); \
	} \
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class LogFormatter;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Log system class
*
*  @note
*    - A configurable amount of messages is hold in a queue (the last n-messages)
*    - When the queue is full a flush is done
*    - A flush is also done if a specified log level is used in the output function (configurable)
*    - A specified log level includes also all log levels with lower values
*      e.g.: if the overall log level is set to info, log messages marked as
*      warning, error or critical are written to the log, too
*    - You can define as many debug log levels as you want
*    - Implementation of the strategy design pattern, this class is the context
*/
class Log : public Singleton<Log> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Singleton<Log>;


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Log levels
		*
		*  @remarks
		*    The log level 0 is reserved for messages which are generated from the
		*    log system itself.
		*/
		enum LogLevel {
			Quiet = 1,	/**< No log outputs */
			Always,		/**< Should be used if the message should be logged always */
			Critical,	/**< Should be used if an critical error occurs */
			Error,		/**< Should be used if an error occurs */
			Warning,	/**< Should be used for warning texts */
			Info,		/**< Should be used for info texts */
			Debug		/**< Should be used for debug level texts */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get verbose mode (write log entries to console)
		*
		*  @return
		*    'true' if the log is writing into the console, else 'false'
		*
		*  @note
		*    - In addition to using an optional log formatter, the log also writes into the console in verbose mode
		*    - The log does not need be to be opened to write into the console
		*    - Android: Messages are not written into the console, instead the Android in-kernel log buffer is used
		*              (use Androids "logcat" utility to access this system log)
		*    - By default the log does not write into the console
		*/
		PLCORE_API bool IsVerbose() const;

		/**
		*  @brief
		*    Set verbose mode (write log entries to console)
		*
		*  @param[in] bVerbose
		*    'true' if the log is writing into the console, else 'false'
		*  @param[in] bVerboseLogLevelPrefix
		*    Should the [LogLevel] prefix be shown?
		*
		*  @see
		*    - IsVerbose()
		*/
		PLCORE_API void SetVerbose(bool bVerbose, bool bVerboseLogLevelPrefix = true);

		/**
		*  @brief
		*    Open the log file by using a filename
		*
		*  @param[in] sFilename
		*    The log's filename, the log formatter is automatically created by using the filename extension
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe the log is already opened or the filename extension is not supported?)
		*
		*  @note
		*    - Supported log filename extensions: "txt" (LogFormatterText), "log" (LogFormatterText), "xml" (LogFormatterXml), "html" (LogFormatterHtml)
		*/
		PLCORE_API bool Open(const String &sFilename);

		/**
		*  @brief
		*    Open the log file by using a filename and an explicit log formatter instance
		*
		*  @param[in] sFilename
		*    The log's filename
		*  @param[in] cLogFormatter
		*    Log formatter instance to be used, if this method returns successfully, the log takes over
		*    the control and is responsible for the destruction of the given instance
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe the log is already opened?)
		*/
		PLCORE_API bool Open(const String &sFilename, LogFormatter &cLogFormatter);

		/**
		*  @brief
		*    Close log
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool Close();

		/**
		*  @brief
		*    Get log filename
		*
		*  @return
		*    The log filename
		*/
		PLCORE_API String GetFilename() const;

		/**
		*  @brief
		*    Write a string into the log
		*
		*  @param[in] nLogLevel
		*    Log level
		*  @param[in] sText
		*    Text which should be written into the log
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*    The text is written to the log only if the current
		*    log level is greater or equal to the specified value.
		*/
		PLCORE_API bool Output(uint8 nLogLevel, const String &sText);

		/**
		*  @brief
		*    Get current log level
		*
		*  @return
		*    The current log level
		*/
		PLCORE_API uint8 GetLogLevel() const;

		/**
		*  @brief
		*    Set current log level
		*
		*  @param[in] nLogLevel
		*    New current log level
		*/
		PLCORE_API void SetLogLevel(uint8 nLogLevel = Info);

		/**
		*  @brief
		*    Get log level for automatic flush
		*
		*  @return
		*    Log level for explicitly flush
		*/
		PLCORE_API uint8 GetFlushLogLevel() const;

		/**
		*  @brief
		*    Set log level for automatic flush
		*
		*  @param[in] nFlushLogLevel
		*    Log level for the explicitly flush
		*/
		PLCORE_API void SetFlushLogLevel(uint8 nFlushLogLevel = Error);

		/**
		*  @brief
		*    Flush output buffer to disk
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe there was nothing to flush?)
		*
		*  @note
		*    - Only call this function if really required!
		*/
		PLCORE_API bool Flush();

		/**
		*  @brief
		*    Get current amount of buffered log messages
		*
		*  @return
		*    Amount of buffered log messages
		*/
		PLCORE_API uint32 GetBufferCount() const;

		/**
		*  @brief
		*    Set how many log messages should be buffered in memory
		*
		*  @param[in] nBufferCount
		*    Number of messages to buffer
		*
		*  @note
		*    The nBufferCount-last log messages gets buffered
		*/
		PLCORE_API void SetBufferCount(uint32 nBufferCount = 10);

		/**
		*  @brief
		*    Get a copy of the queue which holds the last log messages
		*
		*  @return
		*    Queue of n-last log messages
		*/
		PLCORE_API const Queue<String> &GetLastMessages() const;

		/**
		*  @brief
		*    Get a string representation of the given log level
		*
		*  @param[in] nLogLevel
		*    Log level to return the string representation from
		*
		*  @return
		*    The string representation of the given log level
		*/
		PLCORE_API String LogLevelToString(uint8 nLogLevel) const;

		/**
		*  @brief
		*    Get log formatter
		*
		*  @return
		*    The current log formatter object, can be a null pointer, do NOT delete the returned instance!
		*/
		PLCORE_API LogFormatter *GetLogFormatter() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		Log();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Log(const Log &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Log();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Log &operator =(const Log &cSource);

		/**
		*  @brief
		*    Write a string into the log
		*
		*  @param[in] nLogLevel
		*    Log Level
		*  @param[in] sText
		*    Text which should be written into the log
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool Write(uint8 nLogLevel, const String &sText);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool		   m_bVerbose;					/**< Write into the standard OS console? */
		bool		   m_bVerboseLogLevelPrefix;	/**< Indicates if the [LogLevel] prefix should be shown within the standard OS console output */
		String		   m_sFilename;					/**< Filename */
		uint8		   m_nLogLevel;					/**< Current log level mode (see LogLevel) */
		uint8		   m_nFlushLogLevel;			/**< If this log level is used the the flush is explicitly done */
		uint32		   m_nFlushMessages;			/**< Holds the number of messages since the last flush */
		Queue<String>  m_qLastMessages;				/**< Holds the last log messages */
		uint32		   m_nBufferedMessages;			/**< How much messages should be buffered */
		LogFormatter  *m_pLogFormatter;				/**< Holds an instance of a log formatter class, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Template extern instance                              ]
//[-------------------------------------------------------]
#ifndef PLCORE_LOG_CPP
	PLCORE_EXTERN_TEMPLATE Singleton<Log>;
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_LOG_H__
