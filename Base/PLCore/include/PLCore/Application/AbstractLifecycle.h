/*********************************************************\
 *  File: AbstractLifecycle.h                            *
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


#ifndef __PLCORE_ABSTRACTLIFECYCLE_H__
#define __PLCORE_ABSTRACTLIFECYCLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract lifecycle class
*
*  @remarks
*  @verbatim
*    The "Lifecycle" is:
*      "OnCreate()"         - Called directly after the object has been created
*        ("OnRestart()")    - Called directly before a stopped object is going to start again (always followed by "OnStart()")
*        "OnStart()"        - Called when the object becoming visible to the user
*          "OnResume()"     - Called when the object has the focus (keep the implementation lightweight)
*          "OnPause()"      - Called when the object has no longer the focus (keep the implementation lightweight)
*        "OnStop()"         - Called when the object is no longer visible to the user
*      "OnDestroy()"        - Called before the object is going to be finally destroyed
*    This lifecycle has the same interface as the "Android Activity Lifecycle"
*    (http://developer.android.com/reference/android/app/Activity.html#ActivityLifecycle)
*    because this interface looks just the right way to go for this purpose... also there
*    are nice diagrams and documentations explaining the interface so it shouldn't be to
*    hard to understand it.
*  @endverbatim
*/
class AbstractLifecycle {


	//[-------------------------------------------------------]
	//[ Public virtual AbstractLifecycle functions            ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Called directly after the object has been created
		*/
		virtual void OnCreate() = 0;

		/**
		*  @brief
		*    Called directly before a stopped object is going to start again (always followed by "OnStart()")
		*/
		virtual void OnRestart() = 0;

		/**
		*  @brief
		*    Called when the object becoming visible to the user
		*
		*  @return
		*    'true' if all went fine, else 'false' (on failure, no "OnResume()", "OnPause()" or "OnStop()" will be called)
		*/
		virtual bool OnStart() = 0;

		/**
		*  @brief
		*    Called when the object has the focus (keep the implementation lightweight)
		*/
		virtual void OnResume() = 0;

		/**
		*  @brief
		*    Called when the object has no longer the focus (keep the implementation lightweight)
		*/
		virtual void OnPause() = 0;

		/**
		*  @brief
		*    Called when the object is no longer visible to the user
		*/
		virtual void OnStop() = 0;

		/**
		*  @brief
		*    Called before the object is going to be finally destroyed
		*/
		virtual void OnDestroy() = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		AbstractLifecycle();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~AbstractLifecycle();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_ABSTRACTLIFECYCLE_H__
