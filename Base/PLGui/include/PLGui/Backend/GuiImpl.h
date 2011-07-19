/*********************************************************\
 *  File: GuiImpl.h                                      *
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


#ifndef __PLGUI_GUIIMPL_H__
#define __PLGUI_GUIIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include <PLMath/Vector2i.h>
#include "PLGui/Gui/Resources/FontInfo.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Gui;
class GuiMessage;
class Screen;
class Widget;
class WidgetImpl;
class Graphics;
class GraphicsImpl;
class Image;
class ImageImpl;
class Font;
class FontImpl;
class Cursor;
class CursorImpl;
class TrayIcon;
class TrayIconImpl;
class ClipBoard;
class ClipBoardImpl;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Gui implementation backend
*
*  @remarks
*    This class is the base class for platform specific GUI implementations
*
*  @note
*    - Implementation of the bridge design pattern, this class is the implementor of the 'Gui' abstraction
*/
class GuiImpl : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, GuiImpl, "PLGui", PLCore::Object, "Gui implementation backend")
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
		*
		*  @remarks
		*    To create a GUI implementation using the RTTI, it is necessary to have
		*    a default constructor, so the GUI pointer will be a null pointer. Whenever this
		*    is used, the GUI rederence must be set immediatly after creating the instance!
		*/
		PLGUI_API GuiImpl(Gui *pGui);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~GuiImpl();


	//[-------------------------------------------------------]
	//[ Public virtual GuiImpl functions                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Check if there are system messages waiting
		*
		*  @return
		*    'true' if there are messages in the queue
		*/
		virtual bool HasPendingMessages() = 0;

		/**
		*  @brief
		*    Process GUI message
		*
		*  @note
		*    - This function shall process exactly one GUI message
		*    - If no message is in the queue, the function shall block until there is one
		*/
		virtual void ProcessMessage() = 0;

		/**
		*  @brief
		*    Post message to the message queue
		*
		*  @param[in] cMessage
		*    Message to be posted
		*/
		virtual void PostMessage(const GuiMessage &cMessage) = 0;

		/**
		*  @brief
		*    Get list of display screens (monitors)
		*
		*  @param[out]
		*    List of screens
		*
		*  @note
		*    - The given list is not cleared, new entries are just added
		*    - If you no longer need the list entries, you are responsible for destroying them
		*/
		virtual void EnumerateScreens(PLCore::List<Screen*> &lstScreens) = 0;

		/**
		*  @brief
		*    Get screen size
		*
		*  @return
		*    Size of screen (width, height)
		*/
		virtual PLMath::Vector2i GetScreenSize() const = 0;

		/**
		*  @brief
		*    Check if the GUI has a taskbar
		*
		*  @return
		*    'true', if the system has a taskbar, else 'false'
		*/
		virtual bool HasTaskbar() = 0;

		/**
		*  @brief
		*    Set mouse cursor visibility
		*
		*  @param[in] bVisible
		*    Shall the mouse cursor be visible?
		*/
		virtual void SetMouseVisible(bool bVisible) = 0;

		/**
		*  @brief
		*    List all available font
		*
		*  @param[out] lstFonts
		*    List that will receive the fonts
		*/
		virtual void ListFonts(PLCore::List<FontInfo> &lstFonts) const = 0;

		/**
		*  @brief
		*    Create a widget implementation
		*
		*  @param[in] cWidget
		*    Widget
		*
		*  @return
		*    Platform specific widget implementation
		*/
		virtual WidgetImpl *CreateWidgetImpl(Widget &cWidget) const = 0;

		/**
		*  @brief
		*    Create a graphics implementation
		*
		*  @param[in] cGraphics
		*    Graphics object
		*
		*  @return
		*    Platform specific graphics implementation
		*/
		virtual GraphicsImpl *CreateGraphicsImpl(Graphics &cGraphics) const = 0;

		/**
		*  @brief
		*    Create an image implementation
		*
		*  @param[in] cImage
		*    Image object
		*
		*  @return
		*    Platform specific image implementation
		*/
		virtual ImageImpl *CreateImageImpl(Image &cImage) const = 0;

		/**
		*  @brief
		*    Create a font implementation
		*
		*  @param[in] cFont
		*    Font object
		*
		*  @return
		*    Platform specific font implementation
		*/
		virtual FontImpl *CreateFontImpl(Font &cFont) const = 0;

		/**
		*  @brief
		*    Create a cursor implementation
		*
		*  @param[in] cCursor
		*    Cursor object
		*
		*  @return
		*    Platform specific cursor implementation
		*/
		virtual CursorImpl *CreateCursorImpl(Cursor &cCursor) const = 0;

		/**
		*  @brief
		*    Create a tray-icon implementation
		*
		*  @param[in] cTrayIcon
		*    TrayIcon object
		*
		*  @return
		*    Platform specific tray-icon implementation
		*/
		virtual TrayIconImpl *CreateTrayIconImpl(TrayIcon &cTrayIcon) const = 0;

		/**
		*  @brief
		*    Create a clipboard implementation
		*
		*  @param[in] cClipBoard
		*    ClipBoard object
		*
		*  @return
		*    Platform specific clipboard implementation
		*/
		virtual ClipBoardImpl *CreateClipBoardImpl(ClipBoard &cClipBoard) const = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Gui *m_pGui;	/**< Pointer to the platform independent GUI object */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_GUIIMPL_H__
