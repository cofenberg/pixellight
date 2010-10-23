/*********************************************************\
 *  File: GuiPL.h                                        *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLSCENE_SCENENODE_GUI_GUI_H__
#define __PLSCENE_SCENENODE_GUI_GUI_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/Queue.h>
#include <PLGeneral/Container/Bitset.h>
#include <PLGui/Backend/GuiImpl.h>
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class Rectangle;
}
namespace PLGui {
	class Timer;
	class Screen;
}
namespace PLRenderer {
	class Renderer;
}
namespace PLInput {
	class Keyboard;
	class VirtualController;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PixelLight ingame GUI implementation
*/
class GuiPL : public PLGui::GuiImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SNGui;
	friend class WidgetPL;


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, GuiPL, "PLScene", PLGui::GuiImpl, "PixelLight ingame GUI implementation")
		pl_constructor_1(DefaultConstructor, PLGui::Gui*, "Default constructor", "")
		pl_attribute(InputSemantic,	PLGeneral::String,	"",	ReadWrite,	DirectValue,	"Semantic of this input controller (e.g. \"Camera\")",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pGui
		*    Platform independent GUI
		*/
		PLS_API GuiPL(PLGui::Gui *pGui);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~GuiPL();

		/**
		*  @brief
		*    Set screen size
		*
		*  @param[in] vScreenSize
		*    Screen size (default is 1024x768)
		*/
		PLS_API void SetScreenSize(const PLMath::Vector2i &vScreenSize);

		/**
		*  @brief
		*    Returns the used renderer
		*
		*  @return
		*    The used renderer, NULL on error
		*/
		PLS_API PLRenderer::Renderer *GetRenderer() const;

		/**
		*  @brief
		*    Get virtual input controller
		*
		*  @return
		*    Virtual input controller (can be NULL)
		*/
		PLS_API PLInput::VirtualController *GetInputController() const;

		/**
		*  @brief
		*    Set virtual input controller
		*
		*  @param[in] pInputController
		*    Virtual input controller (can be NULL)
		*/
		PLS_API void SetInputController(PLInput::VirtualController *pInputController);

		/**
		*  @brief
		*    Renders the ingame GUI
		*/
		PLS_API void Render();

		/**
		*  @brief
		*    Updates the ingame GUI
		*
		*  @note
		*    - Generates for example keyboard and mouse GUI messages
		*/
		PLS_API void Update();


	//[-------------------------------------------------------]
	//[ Public virtual PLGui::GuiImpl functions               ]
	//[-------------------------------------------------------]
	public:
		virtual bool HasPendingMessages();
		virtual void ProcessMessage();
		virtual void PostMessage(const PLGui::GuiMessage &cMessage);
		virtual void EnumerateScreens(PLGeneral::List<PLGui::Screen*> &lstScreens);
		virtual PLMath::Vector2i GetScreenSize() const;
		virtual bool HasTaskbar();
		virtual void SetMouseVisible(bool bVisible);
		virtual void ListFonts(PLGeneral::List<PLGui::FontInfo> &lstFonts) const;
		virtual PLGui::WidgetImpl *CreateWidgetImpl(PLGui::Widget &cWidget) const;
		virtual PLGui::GraphicsImpl *CreateGraphicsImpl(PLGui::Graphics &cGraphics) const;
		virtual PLGui::ImageImpl *CreateImageImpl(PLGui::Image &cImage) const;
		virtual PLGui::FontImpl *CreateFontImpl(PLGui::Font &cFont) const;
		virtual PLGui::CursorImpl *CreateCursorImpl(PLGui::Cursor &cCursor) const;
		virtual PLGui::TrayIconImpl *CreateTrayIconImpl(PLGui::TrayIcon &cTrayIcon) const;
		virtual PLGui::ClipBoardImpl *CreateClipBoardImpl(PLGui::ClipBoard &cClipBoard) const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Add widget to z position sorted list of top-level widgets, by default below all already existing widget
		*
		*  @param[in] pWidget
		*    Widget
		*/
		void AddTopLevelWidget(PLGui::Widget *pWidget);

		/**
		*  @brief
		*    Render a widget recursive
		*
		*  @param[in] cWidget
		*    Widget to render
		*  @param[in] cParentRectangle
		*    Parent scissor rectangle to clip against
		*  @param[in] nTransparency
		*    Transparency mode (see ETransparency)
		*  @param[in] cColor
		*    If nMode is ColorKey, all pixels of the specified color will be transparent.
		*    If nMode is Alpha, only the alpha channel of the color will be used (1.0 = opaque, 0.0 = transparent)
		*/
		void RenderWidget(PLGui::Widget &cWidget, const PLMath::Rectangle &cParentRectangle, PLGui::ETransparency nTransparency, PLGraphics::Color4 cTransparencyColor);

		/**
		*  @brief
		*    Called when the timer has fired
		*/
		void NotifyTimer();

		/**
		*  @brief
		*    Get the currently pressed key modifiers
		*
		*  @param[in] cKeyboard
		*    Keyboard instance to use
		*
		*  @return
		*    The currently pressed key modifiers
		*/
		PLGeneral::uint32 GetKeyModifiers(PLInput::Keyboard &cKeyboard) const;

		/**
		*  @brief
		*    Update the ingame GUI keyboard
		*/
		void UpdateKeyboard();

		/**
		*  @brief
		*    Update the ingame GUI mouse
		*/
		void UpdateMouse();

		/**
		*  @brief
		*    Find the widget at the given absolute ingame GUI mouse cursor position
		*
		*  @param[in] vMousePos
		*    Absolute ingame GUI mouse cursor position
		*
		*  @return
		*    The found widget at the given absolute ingame GUI mouse cursor position, NULL if no widget was found
		*/
		PLGui::Widget *FindWidgetAtPos(const PLMath::Vector2i &vMousePos) const;

		/**
		*  @brief
		*    Find the widget at the given absolute ingame GUI mouse cursor position recursive
		*
		*  @param[in] vMousePos
		*    Absolute ingame GUI mouse cursor position
		*  @param[in] cParentWidget
		*    Parent widget
		*
		*  @return
		*    The found widget at the given absolute ingame GUI mouse cursor position, NULL if no widget was found
		*/
		PLGui::Widget *FindWidgetAtPos(const PLMath::Vector2i &vMousePos, PLGui::Widget &cParentWidget) const;


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		static const PLGeneral::uint32 NumOfMouseButtons = 3;	/**< Number of supported mouse buttons */


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerTimer;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGui::Gui							*m_pGui;									/**< Platform independent GUI, NULL on error */
		PLMath::Vector2i					 m_vScreenSize;								/**< Screen size */
		PLRenderer::Renderer				*m_pRenderer;								/**< Used renderer, NULL on error */
		PLGeneral::Mutex					*m_pMessageQueueMutex;						/**< GUI message queue mutex, always valid! */
		PLGeneral::Queue<PLGui::GuiMessage>  m_lstMessageQueue;							/**< GUI message queue */

		// Widgets
		PLGui::Widget						*m_pMouseOver;								/**< Widget that the mouse has currently entered */
		PLGeneral::Array<PLGui::Widget*>	 m_lstTopLevelWidgets;						/**< List of z position sorted top-level widgets, smaller number for widgets below other with higher numbers */

		// Input
		PLInput::VirtualController			*m_pInputController;						/**< Virtual input controller, can be NULL */

		// Keyboard
		PLGeneral::Bitset					 m_lstKeys;									/**< State of keys buttons */
		PLGeneral::Bitset					 m_lstRepeatKeys;							/**< Repeat state of keys buttons */
		PLGui::Timer						*m_pKeyTimer;								/**< Key autorepeat timer */

		// Mouse
		PLMath::Vector2i					 m_vSystemMousePos;							/**< System mouse position (not the position within the ingame GUI coordinate system) */
		PLMath::Vector2i					 m_vMousePos;								/**< Ingame GUI mouse position */
		bool								 m_bMouseButtonPressed[NumOfMouseButtons];	/**< Mouse button pressed */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_GUI_GUI_H__
