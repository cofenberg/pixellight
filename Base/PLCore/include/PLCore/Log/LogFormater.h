/*********************************************************\
 *  File: LogFormater.h                                  *
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


#ifndef __PLCORE_LOGFORMATER_H__
#define __PLCORE_LOGFORMATER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/PLCore.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class File;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract log formater class
*
*  @remarks
*    Defines the interface for a formater of the log. With this interface you can
*    implement a formater which will format the output of the log.
*
*  @note
*    - Implementation of the strategy design pattern, this class is the strategy of the context "Log"
*/
class LogFormater {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Log;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    To activate/deactivate that the [LogLevel] prefix should be shown
		*    in the log before each log message e.g. [Info] info log level message
		*
		*  @param[in] bShow
		*    Should the prefix be shown?
		*
		*  @remarks
		*    This option can be ignored in an log formater implementation if the log formater
		*    wants that the prefix is always shown.
		*/
		PLCORE_API void ShowLogLevelPrefix(bool bShow = true);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCORE_API LogFormater();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~LogFormater();

		/**
		*  @brief
		*    Helper function to open the log as a file
		*
		*  @param[in] sFilename
		*    The log's filename
		*
		*  @return
		*    A pointer to the file object if all went fine, a null pointer on error
		*/
		PLCORE_API File *OpenFile(const String &sFilename);


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Open the log file
		*
		*  @param[in] sFilename
		*    The log's filename
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Open(const String &sFilename) = 0;

		/**
		*  @brief
		*    Close the log
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Close() = 0;

		/**
		*  @brief
		*    Writes an Formated string to the Logfile
		*
		*  @param[in] nLogLevel
		*    The log level to which the log message belongs
		*  @param[in] sText
		*    Text which should be written into the log
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Output(uint8 nLogLevel, const String &sText) = 0;

		/**
		*  @brief
		*    Flushes the output buffer to the file on disk
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Flush() = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		File *m_pFile;					/**< Pointer to the log file, can be a null pointer */
		bool  m_bShowLogLevelPrefix;	/**< Indicates if the [LogLevel] prefix should be shown */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		LogFormater(const LogFormater &cSource);

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
		LogFormater &operator =(const LogFormater &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_LOGFORMATER_H__
