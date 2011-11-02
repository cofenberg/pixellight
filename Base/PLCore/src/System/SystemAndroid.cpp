/*********************************************************\
 *  File: SystemAndroid.cpp                              *
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
#include <android/log.h>
#include "PLCore/System/SystemAndroid.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public static events                                  ]
//[-------------------------------------------------------]
Event<const struct AInputEvent&> SystemAndroid::EventInputEvent;	/**< Android input event, input event to be processed as first parameter */


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
AAssetManager *SystemAndroid::g_pAAssetManager      = nullptr;	/**< Android asset manager, can be a null pointer, the given instance is just shared and not destroyed by this class */
bool		   SystemAndroid::g_bConsoleToKernelLog = false;	/**< 'true' if console messages are also written into the Android in-kernel log buffer, else 'false', default is 'false' */


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the Android asset manager
*/
AAssetManager *SystemAndroid::GetAssetManager()
{
	return g_pAAssetManager;
}

/**
*  @brief
*    Sets the Android asset manager
*/
void SystemAndroid::SetAssetManager(AAssetManager *pAAssetManager)
{
	g_pAAssetManager = pAAssetManager;
}

/**
*  @brief
*    Emit Android input event
*/
void SystemAndroid::EmitInputEvent(const struct AInputEvent &sAInputEvent)
{
	EventInputEvent(sAInputEvent);
}

/**
*  @brief
*    Returns whether or not console messages are also written into the Android in-kernel log buffer (use Androids "logcat" utility to access this system log)
*/
bool SystemAndroid::GetConsoleToKernelLog()
{
	return g_bConsoleToKernelLog;
}

/**
*  @brief
*    Sets whether or not console messages are also written into the Android in-kernel log buffer (use Androids "logcat" utility to access this system log)
*/
void SystemAndroid::SetConsoleToKernelLog(bool bConsoleToKernelLog)
{
	g_bConsoleToKernelLog = bConsoleToKernelLog;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SystemAndroid::SystemAndroid()
{
}

/**
*  @brief
*    Destructor
*/
SystemAndroid::~SystemAndroid()
{
}


//[-------------------------------------------------------]
//[ Private virtual SystemImpl functions                  ]
//[-------------------------------------------------------]
String SystemAndroid::GetPlatform() const
{
	static const String sString = "Android";
	return sString;
}

const Console &SystemAndroid::GetConsole() const
{
	return g_bConsoleToKernelLog ? m_cConsole : SystemLinux::m_cConsole;
}

void SystemAndroid::UrgentMessage(const String &sMessage) const
{
	// Write into the Android kernel log buffer (use Androids "logcat" utility to access this system log)
	__android_log_write(ANDROID_LOG_FATAL, "PixelLight", (sMessage.GetFormat() == String::ASCII) ? sMessage.GetASCII() : sMessage.GetUTF8());
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
