/*********************************************************\
 *  File: SystemAndroid.inl                              *
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the native Android application
*/
inline android_app *SystemAndroid::GetAndroidApp()
{
	return g_pAndroidApp;
}

/**
*  @brief
*    Sets the native Android application
*/
inline void SystemAndroid::SetAndroidApp(android_app *pAndroidApp)
{
	g_pAndroidApp = pAndroidApp;
}

/**
*  @brief
*    Returns the Android asset manager
*/
inline AAssetManager *SystemAndroid::GetAssetManager()
{
	return g_pAAssetManager;
}

/**
*  @brief
*    Sets the Android asset manager
*/
inline void SystemAndroid::SetAssetManager(AAssetManager *pAAssetManager)
{
	g_pAAssetManager = pAAssetManager;
}

/**
*  @brief
*    Emit Android input event
*/
inline void SystemAndroid::EmitInputEvent(const struct AInputEvent &sAInputEvent)
{
	EventInputEvent(sAInputEvent);
}

/**
*  @brief
*    Returns whether or not console messages are also written into the Android in-kernel log buffer (use Androids "logcat" utility to access this system log)
*/
inline bool SystemAndroid::GetConsoleToKernelLog()
{
	return g_bConsoleToKernelLog;
}

/**
*  @brief
*    Sets whether or not console messages are also written into the Android in-kernel log buffer (use Androids "logcat" utility to access this system log)
*/
inline void SystemAndroid::SetConsoleToKernelLog(bool bConsoleToKernelLog)
{
	g_bConsoleToKernelLog = bConsoleToKernelLog;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
