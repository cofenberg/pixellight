/*********************************************************\
 *  File: ConsoleAndroid.cpp                             *
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
#include <android/log.h>
#include "PLCore/String/String.h"
#include "PLCore/System/ConsoleAndroid.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public virtual Console functions                      ]
//[-------------------------------------------------------]
void ConsoleAndroid::Print(const String &sString) const
{
	// Write into the Android in-kernel log buffer (use Androids "logcat" utility to access this system log)
	const String sLogMessage = "[Console] " + sString;
	__android_log_write(ANDROID_LOG_INFO, "PixelLight", (sLogMessage.GetFormat() == String::ASCII) ? sLogMessage.GetASCII() : sLogMessage.GetUTF8());

	// Do also do the normal console output
	ConsoleLinux::Print(sString);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ConsoleAndroid::ConsoleAndroid()
{
}

/**
*  @brief
*    Destructor
*/
ConsoleAndroid::~ConsoleAndroid()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
