/*********************************************************\
 *  File: RenderWindow.h                                 *
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


#ifndef __PLFRONTENDPLGUI_RENDERWINDOW_H__
#define __PLFRONTENDPLGUI_RENDERWINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Gui/Resources/Timer.h>
#include <PLGui/Widgets/Windows/Window.h>
#include "PLFrontendPLGui/WindowConnection.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendPLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    GUI window that implements a renderer surface
*
*  @remarks
*    Use 'RenderWindow' to create a window which automatically
*    implements a renderer surface handler and creates the window surface.
*
*  @note
*    - By default, it's allowed to switch windows into fullscreen mode using Alt-Return or AltGr-Return
*    - By default, it's allowed to use Alt-Tab
*/
class RenderWindow : public PLGui::Window, public WindowConnection {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLFRONTENDPLGUI_RTTI_EXPORT, RenderWindow, "PLFrontendPLGui", PLGui::Window, "GUI window that implements a renderer surface")
		// Slots
		pl_slot_0(OnTimer,	"Timer callback",	"");
	pl_class_end


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
		*  @param[in] pParent
		*    Parent widget, can be a null pointer
		*  @param[in] pDisplayMode
		*    Display mode information, can be a null pointer
		*  @param[in] bFullscreen
		*    Initial in fullscreen mode? If yes, 'pDisplayMode' information is required, if not given,
		*    no fullscreen is possible!
		*
		*  @note
		*    - If 'pDisplayMode' is not given, default settings are used
		*    - If no fullscreen mode, just the size from 'pDisplayMode' are used.
		*/
		PLFRONTENDPLGUI_API RenderWindow(PLRenderer::Renderer &cRenderer, PLGui::Widget *pParent = nullptr, const PLRenderer::DisplayMode *pDisplayMode = nullptr, bool bFullscreen = false);

		/**
		*  @brief
		*    Destructor
		*/
		PLFRONTENDPLGUI_API virtual ~RenderWindow();


	//[-------------------------------------------------------]
	//[ Protected virtual PLGui::WidgetFunctions functions    ]
	//[-------------------------------------------------------]
	protected:
		PLFRONTENDPLGUI_API virtual void OnDraw(PLGui::Graphics &cGraphics);


	//[-------------------------------------------------------]
	//[ Protected virtual WindowConnection functions          ]
	//[-------------------------------------------------------]
	protected:
		PLFRONTENDPLGUI_API virtual void OnDisplayMode() override;


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
		RenderWindow(const RenderWindow &cSource);

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
		RenderWindow &operator =(const RenderWindow &cSource);

		/**
		*  @brief
		*    Timer callback
		*/
		void OnTimer();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGui::Timer	 m_cTimer;		/**< Timer */
		bool			 m_bBackupAvailable;
		PLMath::Vector2i m_vBackupPos;
		PLMath::Vector2i m_vBackupSize;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendPLGui


#endif // __PLFRONTENDPLGUI_RENDERWINDOW_H__
