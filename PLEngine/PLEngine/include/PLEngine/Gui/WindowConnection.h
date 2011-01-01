/*********************************************************\
 *  File: WindowConnection.h                             *
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


#ifndef __PLENGINE_WINDOWCONNECTION_H__
#define __PLENGINE_WINDOWCONNECTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/Event.h>
#include <PLRenderer/Renderer/Types.h>
#include <PLRenderer/Renderer/SurfaceWindowHandler.h>
#include "PLEngine/PLEngine.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Window and renderer surface connection class
*
*  @note
*    - Use EventDisplayMode and EventFullscreenMode to keep track of the window connection state,
*      this events are also generated on initialization
*/
class WindowConnection : public PLRenderer::SurfaceWindowHandler {


	//[-------------------------------------------------------]
	//[ Events                                                ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<> EventDisplayMode;		/**< Display mode changed event */
		PLCore::Event<> EventFullscreenMode;	/**< Fullscreen mode changed event */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*  @param[in] cWidget
		*    Widget to render into
		*  @param[in] pEventWidget
		*    Optional event widget, if not given, the events from cWidget are used
		*
		*  @note
		*    - Don't forget to call Initialize() to initialize the connection
		*/
		PL_API WindowConnection(PLRenderer::Renderer &cRenderer, PLGui::Widget &cWidget, PLGui::Widget *pEventWidget = NULL);

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~WindowConnection();

		/**
		*  @brief
		*    Initializes the window connection
		*
		*  @param[in] pDisplayMode
		*    Display mode information, can be NULL
		*  @param[in] bFullscreen
		*    Initial in fullscreen mode?
		*
		*  @note
		*    - If 'pDisplayMode' is not given, default settings are used
		*    - If no fullscreen mode, just the size from 'pDisplayMode' are used
		*/
		PL_API void Initialize(const PLRenderer::DisplayMode *pDisplayMode = NULL, bool bFullscreen = false);

		/**
		*  @brief
		*    Returns information about the used display mode
		*
		*  @return
		*    Information about the used display mode
		*/
		PL_API const PLRenderer::DisplayMode &GetDisplayMode() const;

		/**
		*  @brief
		*    Sets a new display mode
		*
		*  @param[in] sDisplayMode
		*    New display mode
		*/
		PL_API void SetDisplayMode(const PLRenderer::DisplayMode &sDisplayMode);

		/**
		*  @brief
		*    Gets whether it's allowed to toggle the fullscreen mode using hotkeys
		*
		*  @return
		*    'true' if it's possible to toggle the fullscreen mode using hotkeys, else 'false'
		*/
		PL_API bool GetToggleFullscreenMode() const;

		/**
		*  @brief
		*    Sets whether it's allowed to toggle the fullscreen mode using hotkeys
		*
		*  @param[in] bToggleFullscreenMode
		*    Is it allowed to toggle the fullscreen mode using hotkeys?
		*
		*  @note
		*    - Alt-Return is registered at the given GUI widget as hotkey
		*    - AltGr-Return is registered at the given GUI widget as hotkey
		*    - By default, it's not allowed to switch widgets into fullscreen mode using Alt-Return or AltGr-Return
		*/
		PL_API void SetToggleFullscreenMode(bool bToggleFullscreenMode);

		/**
		*  @brief
		*    Gets whether it's allowed to use Alt-Tab if fullscreen mode is used
		*
		*  @return
		*    'true' if it's possible to use Alt-Tab if fullscreen mode is used, else 'false'
		*
		*  @note
		*    - Widgets only
		*/
		PL_API bool GetFullscreenAltTab() const;

		/**
		*  @brief
		*    Sets whether it's allowed to use Alt-Tab if fullscreen mode is used
		*
		*  @param[in] bAllowed
		*    Is it allowed to use Alt-Tab within fullscreen mode?
		*
		*  @note
		*    - By default, it's not allowed to use Alt-Tab
		*
		*  @see
		*    - GetFullscreenAltTab()
		*/
		PL_API void SetFullscreenAltTab(bool bAllowed);

		/**
		*  @brief
		*    Returns whether the window is in fullscreen mode or not
		*
		*  @return
		*    'true' if the window is in fullscreen mode, else 'false'
		*/
		PL_API bool IsFullscreen() const;

		/**
		*  @brief
		*    Sets the window's fullscreen mode
		*
		*  @param[in] bFullscreen
		*    'true' if the window should be in fullscreen mode, else 'false'
		*/
		PL_API void SetFullscreen(bool bFullscreen);


	//[-------------------------------------------------------]
	//[ Protected virtual WindowConnection functions          ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Function that is called when the display mode was changed
		*
		*  @note
		*    - The default implementation emits the EventDisplayMode event
		*/
		PL_API virtual void OnDisplayMode();

		/**
		*  @brief
		*    Function that is called when the fullscreen mode was changed
		*
		*  @note
		*    - The default implementation emits the EventFullscreenMode event
		*/
		PL_API virtual void OnFullscreenMode();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		WindowConnection(const WindowConnection &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		WindowConnection &operator =(const WindowConnection &cSource);

		/**
		*  @brief
		*    Initializes the render widget
		*
		*  @param[in] bFullscreen
		*    Fullscreen mode?
		*/
		void InitWidget(bool bFullscreen);

		/**
		*  @brief
		*    Function that is called when the GUI widget is destroyed
		*/
		void NotifyDestroy();

		/**
		*  @brief
		*    Function that is called when the GUI widget is shown
		*/
		void NotifyShow();

		/**
		*  @brief
		*    Function that is called when the GUI widget is hidden
		*/
		void NotifyHide();

		/**
		*  @brief
		*    Called when a key is pressed down
		*
		*  @param[in] nKey
		*    Pressed key
		*  @param[in] nModifiers
		*    Modifier keys pressed
		*/
		void NotifyKeyDown(PLGeneral::uint32 nKey, PLGeneral::uint32 nModifiers);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<>									   EventHandlerDestroy;
		PLCore::EventHandler<>									   EventHandlerShow;
		PLCore::EventHandler<>									   EventHandlerHide;
		PLCore::EventHandler<PLGeneral::uint32, PLGeneral::uint32> EventHandlerKeyDown;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::Renderer	*m_pRenderer;				/**< Owner renderer, always valid! */
		PLGui::Widget			*m_pWidget;					/**< The GUI widget we're rendering in, always valid! */
		PLRenderer::DisplayMode	 m_sDisplayMode;			/**< Display mode information */
		bool					 m_bFullscreenMode;			/**< Is the widget in fullscreen mode? */
		bool					 m_bToggleFullscreenMode;	/**< Is it allowed to toggle the fullscreen mode using alt-return? */
		bool					 m_bFullscreenAltTab;		/**< Is it allowed to use hotkeys within fullscreen mode? */
		bool					 m_bFullscreenAltTabKey;	/**< Is there an hotkeys key? */
		PLGeneral::uint32		 m_nHotkeyIDAltTab;			/**< Alt-tab hotkey ID */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_WINDOWCONNECTION_H__
