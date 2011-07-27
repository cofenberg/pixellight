/*********************************************************\
 *  File: LogFormaterXml.h                               *
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


#ifndef __PLCORE_LOGFORMATER_XML_H__
#define __PLCORE_LOGFORMATER_XML_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Log/LogFormater.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    XML log formater
*
*  @note
*    - Implementation of the strategy design pattern, this class a concrete strategy of the strategy "LogFormater" of the context "Log"
*/
class LogFormaterXml : public LogFormater {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCORE_API LogFormaterXml();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~LogFormaterXml();


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
		LogFormaterXml(const LogFormaterXml &cSource);

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
		LogFormaterXml &operator =(const LogFormaterXml &cSource);

		/**
		*  @brief
		*    Returns the XML formated text the given log level
		*
		*  @param[in] nLogLevel
		*    Log level for which formated text should be returned
		*
		*  @param[in] sText
		*    The log text which should be surrounded with the XML format-tags
		*
		*  @return
		*    XML formated text
		*/
		String GetXmlFormatedText(uint8 nLogLevel, const String &sText) const;


	//[-------------------------------------------------------]
	//[ Private virtual LogFormater functions                 ]
	//[-------------------------------------------------------]
	private:
		virtual bool Open(const String &sFilename) override;
		virtual bool Close() override;
		virtual bool Output(uint8 nLogLevel, const String &sText) override;
		virtual bool Flush() override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_LOGFORMATER_XML_H__
