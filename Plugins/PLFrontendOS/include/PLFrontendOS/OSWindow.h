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

		/**
		*  @brief
		*    Redraw window
		*/
		virtual void Redraw() = 0;

		/**
		*  @brief
		*    Ping window
		*
		*  @return
		*    'true' when to shut down the frontend, else 'false'
		*/
		virtual bool Ping() = 0;

		/**
		*  @brief
		*    Get window width
		*
		*  @return
		*    Width
		*/
		virtual PLCore::uint32 GetWidth() const = 0;

		/**
		*  @brief
		*    Get window height
		*
		*  @return
		*    Height
		*/
		virtual PLCore::uint32 GetHeight() const = 0;

		/**
		*  @brief
		*    Sets whether it's allowed to use Alt-Tab if fullscreen mode is used
		*
		*  @param[in] bAllowed
		*    Is it allowed to use Alt-Tab within fullscreen mode?
		*/
		virtual void SetFullscreenAltTab(bool bAllowed) = 0;

		/**
		*  @brief
		*    Sets the window's fullscreen mode
		*
		*  @param[in] bFullscreen
		*    'true' if the window should be in fullscreen mode, else 'false'
		*/
		virtual void SetFullscreen(bool bFullscreen) = 0;

		/**
		*  @brief
		*    Something related to fullscreen mode has been changed (e.g. the display resolution)
		*/
		virtual void RefreshFullscreen() = 0;

		/**
		*  @brief
		*    Check if the mouse is currently over the window
		*
		*  @return
		*    'true' if mouse-over, else 'false'
		*/
		virtual bool IsMouseOver() const = 0;

		/**
		*  @brief
		*    Get current mouse cursor X position inside the window
		*
		*  @return
		*    Current mouse cursor X position inside the window, negative value if the mouse cursor isn't currently over the frontend
		*/
		virtual int GetMousePositionX() const = 0;

		/**
		*  @brief
		*    Get current mouse cursor Y position inside the window
		*
		*  @return
		*    Current mouse cursor Y position inside the window, negative value if the mouse cursor isn't currently over the frontend
		*/
		virtual int GetMousePositionY() const = 0;

		/**
		*  @brief
		*    Check if the mouse cursor is visible
		*
		*  @return
		*    'true' if the mouse cursor is visible, else 'false'
		*
		*  @note
		*    - If the mouse cursor is visible in general, it's still possible that it's
		*      invisible over some special widgets.
		*    - If the mouse cursor is invisible in general, it will NEVER be visible!
		*/
		virtual bool IsMouseVisible() const = 0;

		/**
		*  @brief
		*    Set mouse cursor visibility
		*
		*  @param[in] bVisible
		*    Shall the mouse cursor be visible?
		*
		*  @see
		*    - IsMouseVisible()
		*/
		virtual void SetMouseVisible(bool bVisible) = 0;

		/**
		*  @brief
		*    Trap mouse inside the frontend window
		*
		*  @param[in] bTrap
		*    'true' if the mouse should be trapped inside the frontend window, else 'false'
		*/
		virtual void SetTrapMouse(bool bTrap) = 0;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendOS


#endif // __PLFRONTENDOS_OSWINDOW_H__