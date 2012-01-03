/*********************************************************\
 *  File: ConsoleAndroid.h                               *
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


#ifndef __PLCORE_CONSOLE_ANDROID_H__
#define __PLCORE_CONSOLE_ANDROID_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/System/ConsoleLinux.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Android 'Console' implementation
*
*  @remarks
*    Even on Android, it's possible to write into the console, meaning "stdout"... but it's somewhat
*    complicated to "see" this output when starting an apk file (meaning: not starting an native
*    application via shell). In this console implementation, messages are not only written into the console,
*    the Android in-kernel log buffer is used as well (use Androids "logcat" utility to access this system log).
*/
class ConsoleAndroid : public ConsoleLinux {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SystemAndroid;


	//[-------------------------------------------------------]
	//[ Public virtual Console functions                      ]
	//[-------------------------------------------------------]
	public:
		virtual void Print(const String &sString) const override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		ConsoleAndroid();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ConsoleAndroid();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CONSOLE_ANDROID_H__
