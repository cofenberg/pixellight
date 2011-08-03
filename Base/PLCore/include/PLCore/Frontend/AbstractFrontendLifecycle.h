/*********************************************************\
 *  File: AbstractFrontendLifecycle.h                    *
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


#ifndef __PLCORE_ABSTRACTFRONTENDLIFECYCLE_H__
#define __PLCORE_ABSTRACTFRONTENDLIFECYCLE_H__
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
*    Abstract frontend lifecycle class
*
*  @remarks
*    The "Frontend Lifecycle" is:
*      "OnCreate()"         - Called directly after the frontend has been created
*        ("OnRestart()")    - Called directly before a stopped frontend is going to start again (always followed by "OnStart()")
*        "OnStart()"        - Called when the frontend becoming visible to the user
*          "OnResume()"     - Called when the frontend has the focus (keep the implementation lightweight)
*          "OnPause()"      - Called when the frontend has no longer the focus (keep the implementation lightweight)
*        "OnStop()"         - Called when the frontend is no longer visible to the user
*      "OnDestroy()"        - Called before the frontend is going to be finally destroyed
*    This lifecycle has the same interface as the "Android Activity Lifecycle"
*    (http://developer.android.com/reference/android/app/Activity.html#ActivityLifecycle)
*    because this interface looks just the right way to go for this purpose... also there
*    are nice diagrams and documentations explaining the interface so it shouldn't be to
*    hard to understand it.
*/
class AbstractFrontendLifecycle {


	//[-------------------------------------------------------]
	//[ Public virtual AbstractFrontendLifecycle functions    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Called directly after the frontend has been created
		*/
		virtual void OnCreate() = 0;

		/**
		*  @brief
		*    Called directly before a stopped frontend is going to start again (always followed by "OnStart()")
		*/
		virtual void OnRestart() = 0;

		/**
		*  @brief
		*    Called when the frontend becoming visible to the user
		*/
		virtual void OnStart() = 0;

		/**
		*  @brief
		*    Called when the frontend has the focus (keep the implementation lightweight)
		*/
		virtual void OnResume() = 0;

		/**
		*  @brief
		*    Called when the frontend has no longer the focus (keep the implementation lightweight)
		*/
		virtual void OnPause() = 0;

		/**
		*  @brief
		*    Called when the frontend is no longer visible to the user
		*/
		virtual void OnStop() = 0;

		/**
		*  @brief
		*    Called before the frontend is going to be finally destroyed
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
		AbstractFrontendLifecycle();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~AbstractFrontendLifecycle();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_ABSTRACTFRONTENDLIFECYCLE_H__
