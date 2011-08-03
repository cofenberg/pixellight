/*********************************************************\
 *  File: OSWindow.h                                     *
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


#ifndef __PLFRONTENDOS_OSWINDOW_H__
#define __PLFRONTENDOS_OSWINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendOS {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract OS window base class
*
*  @note
*    - Implementation of the bridge design pattern, this class is the abstraction
*/
class OSWindow {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Frontend;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		OSWindow();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~OSWindow();


	//[-------------------------------------------------------]
	//[ Protected virtual OSWindow functions                  ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Get native window handle
		*
		*  @return
		*    Native window handle for the frontend window, can be a null pointer
		*/
		virtual PLCore::handle GetNativeWindowHandle() const = 0;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendOS


#endif // __PLFRONTENDOS_OSWINDOW_H__
