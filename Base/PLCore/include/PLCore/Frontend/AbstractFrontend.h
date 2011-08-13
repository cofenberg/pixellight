/*********************************************************\
 *  File: AbstractFrontend.h                             *
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


#ifndef __PLCORE_ABSTRACTFRONTEND_H__
#define __PLCORE_ABSTRACTFRONTEND_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class ValueType> class Container;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract frontend class
*
*  @remarks
*    Please note that the frontend system is not designed to be a replacement for a decent GUI
*    system. In here, only primitive and commonly used GUI related feature are offered with a
*    limited feature set. For more complex stuff one has to use a real GUI system.
*/
class AbstractFrontend {


	//[-------------------------------------------------------]
	//[ Public virtual AbstractFrontend functions             ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Called when the window size has been changed
		*/
		virtual void OnSize() = 0;

		/**
		*  @brief
		*    Called when the display mode was changed
		*/
		virtual void OnDisplayMode() = 0;

		/**
		*  @brief
		*    Called when the fullscreen mode was changed
		*/
		virtual void OnFullscreenMode() = 0;

		/**
		*  @brief
		*    Called to let the frontend draw into it's window
		*/
		virtual void OnDraw() = 0;

		/**
		*  @brief
		*    Called to let the frontend update it's states
		*
		*  @remarks
		*    You can use this method to do work you have to perform on a regular basis. It's
		*    recommended to keep the work done within the implementation as compact as possible.
		*    Don't use this function to perform 'polling'-everything, use events or if required
		*    for example timers or threads instead.
		*/
		virtual void OnUpdate() = 0;

		/**
		*  @brief
		*    Called when string data has been dropped onto the frontend window
		*
		*  @param[in] lstFiles
		*    List of file names
		*/
		virtual void OnDrop(const Container<String> &lstFiles) = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		AbstractFrontend();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~AbstractFrontend();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_ABSTRACTFRONTEND_H__
