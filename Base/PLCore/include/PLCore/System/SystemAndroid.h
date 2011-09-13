/*********************************************************\
 *  File: SystemAndroid.h                                *
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


#ifndef __PLCORE_SYSTEM_ANDROID_H__
#define __PLCORE_SYSTEM_ANDROID_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/System/SystemLinux.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
struct AAssetManager;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Android 'System' implementation
*/
class SystemAndroid : public SystemLinux {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class System;


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the Android asset manager
		*
		*  @return
		*    The Android asset manager, can be a null pointer, do not delete the returned instance
		*/
		static PLCORE_API AAssetManager *GetAssetManager();

		/**
		*  @brief
		*    Sets the Android asset manager
		*
		*  @param[in] pAAssetManager
		*    Android asset manager, can be a null pointer, the given instance is just shared and not destroyed by this class
		*/
		static PLCORE_API void SetAssetManager(AAssetManager *pAAssetManager);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		SystemAndroid();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SystemAndroid();


	//[-------------------------------------------------------]
	//[ Private virtual SystemImpl functions                  ]
	//[-------------------------------------------------------]
	private:
		virtual String GetPlatform() const override;
		virtual String GetOS() const override;
		virtual void UrgentMessage(const String &sMessage) const override;


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		static AAssetManager *g_pAAssetManager = nullptr;	/**< Android asset manager, can be a null pointer, the given instance is just shared and not destroyed by this class */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_SYSTEM_ANDROID_H__
