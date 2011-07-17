/*********************************************************\
 *  File: GuiLinux.h                                     *
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


#ifndef __PLGUI_GUILINUX_H__
#define __PLGUI_GUILINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/Array.h>
#include "PLGui/Backend/GuiImpl.h"
#include "PLGui/PLGuiLinuxIncludes.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class WidgetLinux;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linux GUI implementation
*/
class GuiLinux : public GuiImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class WidgetLinux;
	friend class GraphicsLinux;
	friend class TrayIconLinux;
	friend class TrayIconWidgetLinux;


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
		PLGUI_API GuiLinux(Gui *pGui);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~GuiLinux();

		/**
		*  @brief
		*    Get display
		*
		*  @return
		*    Display
		*/
		PLGUI_API Display *GetDisplay() const;

		/**
		*  @brief
		*    Keep track of modifier keys (shift, control and alt)
		*
		*  @param[in] nKey
		*    Key code of modifier key
		*  @param[in] bPressed
		*    'true' if key is pressed down, else 'false'
		*/
		PLGUI_API void TrackModifierKeys(int nKey, bool bPressed);

		/**
		*  @brief
		*    Get current state of modifier keys (shift, control and alt)
		*
		*  @return
		*    Bitmask of currently pressed modifier keys
		*
		*  @remarks
		*    See Keys.h for symbolic values of modifier keys
		*/
		PLGUI_API PLGeneral::uint32 GetModifierKeys();


	//[-------------------------------------------------------]
	//[ Public virtual GuiImpl functions                      ]
	//[-------------------------------------------------------]
	public:
		virtual bool HasPendingMessages();
		virtual void ProcessMessage();
		virtual void PostMessage(const GuiMessage &cMessage);
		virtual void EnumerateScreens(PLGeneral::List<Screen*> &lstScreens);
		virtual PLMath::Vector2i GetScreenSize() const;
		virtual bool HasTaskbar();
		virtual void SetMouseVisible(bool bVisible);
		virtual void ListFonts(PLGeneral::List<FontInfo> &lstFonts) const;
		virtual WidgetImpl *CreateWidgetImpl(Widget &cWidget) const;
		virtual GraphicsImpl *CreateGraphicsImpl(Graphics &cGraphics) const;
		virtual ImageImpl *CreateImageImpl(Image &cImage) const;
		virtual FontImpl *CreateFontImpl(Font &cFont) const;
		virtual CursorImpl *CreateCursorImpl(Cursor &cCursor) const;
		virtual TrayIconImpl *CreateTrayIconImpl(TrayIcon &cTrayIcon) const;
		virtual ClipBoardImpl *CreateClipBoardImpl(ClipBoard &cClipBoard) const;


	//[-------------------------------------------------------]
	//[ Private static functions                              ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    X error handler
		*
		*  @param[in] pDisplay
		*    Display
		*  @param[in] pError
		*    Error descriptor
		*
		*  @return
		*    Ignored
		*/
		static int ErrorHandler(Display *pDisplay, XErrorEvent *pError);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    X event procedure
		*
		*  @param[in] pEvent
		*    Pointer to an X-event
		*/
		PLGUI_API void ProcessXEvent(XEvent *pEvent);

		/**
		*  @brief
		*    Destroy a widget and it's child widgets
		*
		*  @param[in] pWidget
		*    Widget
		*/
		PLGUI_API void DestroyWidget(Widget *pWidget);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Used client protocols
		struct {
			::Atom Close;							/**< Message for closing the window */
			::Atom Focus;							/**< Message for taking the focus */
			::Atom Timer;							/**< Message for timer events */
			::Atom Exit;							/**< Message for quitting the GUI */
			::Atom Wakeup;							/**< Message for waking up the message loop */
			::Atom DestroyWidget;					/**< Message for destroying a widget (delayed) */
			::Atom ThemeChanged;					/**< Message for changing the theme of a widget */
		} m_sClientProtocols;

		// Other used atoms
		struct {
			::Atom UTF8_STRING;						/**< Atom for the type of a window title */
			::Atom WM_NAME;							/**< Window title (old?) */
			::Atom _NET_WM_NAME;					/**< Window title */
			::Atom _NET_WM_VISIBLE_NAME;			/**< Window title (visible title, can be different) */
			::Atom _NET_WM_STATE;					/**< Window state */
			::Atom _NET_WM_STATE_FULLSCREEN;		/**< Fullscreen mode */
			::Atom _NET_WM_STATE_MAXIMIZED_HORZ;	/**< Maximize horizontally */
			::Atom _NET_WM_STATE_MAXIMIZED_VERT;	/**< Maximize vertically */
			::Atom _NET_WM_STATE_HIDDEN;			/**< Minimize window */
			::Atom _NET_WM_STATE_SKIP_TASKBAR;		/**< Do not show window in taskbar */
			::Atom _NET_WM_STATE_ABOVE;				/**< Topmost state */
			::Atom _XEMBED;							/**< XEMBED protocol */
			::Atom _XEMBED_INFO;					/**< XEMBED information */
			::Atom _NET_SYSTEM_TRAY_OPCODE;			/**< System tray protocol */
			::Atom _NET_SYSTEM_TRAY_MESSAGE_DATA;	/**< System tray message data */
		} m_sAtoms;

		// System handles
		::Display *m_pDisplay;						/**< X display */
		::Window   m_nHiddenWindow;					/**< Hidden window for internal messages */

		// Modifier keys
		bool	   m_bModifierShift;				/**< Is the SHIFT key pressed? */
		bool	   m_bModifierCtrl;					/**< Is the CTRL key pressed? */
		bool	   m_bModifierAlt;					/**< Is the ALT key pressed? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_GUILINUX_H__
