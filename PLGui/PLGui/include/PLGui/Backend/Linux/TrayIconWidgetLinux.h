/*********************************************************\
 *  File: TrayIconWidgetLinux.h                          *
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


#ifndef __PLGUI_TRAYICONWIDGETLINUX_H__
#define __PLGUI_TRAYICONWIDGETLINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/PLGuiLinuxIncludes.h"
#include "PLGui/Widgets/Widget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class TrayIcon;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Tray icon widget class
*
*  @remarks
*    A widget that serves as an (embedded) tray icon widget
*/
class TrayIconWidgetLinux : public Widget {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, TrayIconWidgetLinux, "PLGui", PLGui::Widget, "Tray icon widget class")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pParent
		*    Pointer to the parent widget
		*
		*  @remarks
		*    If pParent == nullptr, the root widget of the system GUI is used as parent widget
		*/
		PLGUI_API TrayIconWidgetLinux(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~TrayIconWidgetLinux();

		/**
		*  @brief
		*    Set tray icon to which the window belongs
		*
		*  @param[in] pTrayIcon
		*    Tray icon
		*/
		PLGUI_API void SetTrayIcon(TrayIcon *pTrayIcon);

		/**
		*  @brief
		*    Show a notification text
		*
		*  @param[in] sTitle
		*    Title
		*  @param[in] sText
		*    Text
		*/
		PLGUI_API void ShowNotification(const PLGeneral::String &sTitle, const PLGeneral::String &sText);

		/**
		*  @brief
		*    Embed window into system tray
		*/
		PLGUI_API void EmbedIntoSysTray();

		/**
		*  @brief
		*    Window requests to get the focus
		*/
		PLGUI_API void XEmbedRequestFocus();

		/**
		*  @brief
		*    Window has reached the end of it's logical tab (tabbing forward)
		*/
		PLGUI_API void XEmbedFocusNext();

		/**
		*  @brief
		*    Window has reached the beginning of it's logical tab (tabbing backwards)
		*/
		PLGUI_API void XEmbedFocusPrev();

		/**
		*  @brief
		*    Register a key accelerator
		*
		*  @param[in] nID
		*    Acellerator ID
		*  @param[in] nKey
		*    Key code
		*  @param[in] nModifiers
		*    Modifier keys
		*/
		PLGUI_API void XEmbedRegisterAccelerator(long nID, long nKey, long nModifiers);

		/**
		*  @brief
		*    Unregister a key accelerator
		*
		*  @param[in] nID
		*    Acellerator ID
		*/
		PLGUI_API void XEmbedUnregisterAccelerator(long nID);


	//[-------------------------------------------------------]
	//[ Public virtual TrayIconWidgetLinux functions          ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Window has been embedded by a XEMBED compliant embedder
		*
		*  @param[in] nEmbedderWindow
		*    Window handle of embedder (also called 'site' or 'socket')
		*  @param[in] nProtocolVersion
		*    Protocol version
		*/
		PLGUI_API virtual void OnXEmbedEmbeddedNotify(::Window nEmbedderWindow, long nProtocolVersion);

		/**
		*  @brief
		*    Window has been activated (e.g. got the focus)
		*/
		PLGUI_API virtual void OnXEmbedWindowActivate();

		/**
		*  @brief
		*    Window has been deactivated (e.g. lost the focus)
		*/
		PLGUI_API virtual void OnXEmbedWindowDeactivate();

		/**
		*  @brief
		*    Window has got the focus
		*
		*  @param[in] nFocus
		*    Where to move the logical focus to (XEMBED_FOCUS_CURRENT, XEMBED_FOCUS_FIRST or XEMBED_FOCUS_LAST)
		*/
		PLGUI_API virtual void OnXEmbedFocusIn(long nFocus);

		/**
		*  @brief
		*    Window has lost the focus
		*/
		PLGUI_API virtual void OnXEmbedFocusOut();

		/**
		*  @brief
		*    Window becomes shadowed by a modal dialog
		*/
		PLGUI_API virtual void OnXEmbedModalityOn();

		/**
		*  @brief
		*    Window has been released from a modal dialog
		*/
		PLGUI_API virtual void OnXEmbedModalityOff();

		/**
		*  @brief
		*    An acellerator has been activated
		*
		*  @param[in] nID
		*    Acellerator ID
		*  @param[in] nFlags
		*    Flags
		*/
		PLGUI_API virtual void OnXEmbedActivateAccelerator(long nID, long nFlags);


	//[-------------------------------------------------------]
	//[ Public virtual Widget functions                       ]
	//[-------------------------------------------------------]
	public:
		PLGUI_API virtual void OnDraw(PLGui::Graphics &cGraphics);
		PLGUI_API virtual void OnMouseMove(const PLMath::Vector2i &vPos);
		PLGUI_API virtual void OnMouseButtonDown(PLGeneral::uint32 nButton, const PLMath::Vector2i &vPos);
		PLGUI_API virtual void OnMouseButtonUp(PLGeneral::uint32 nButton, const PLMath::Vector2i &vPos);
		PLGUI_API virtual void OnMouseButtonClick(PLGeneral::uint32 nButton, const PLMath::Vector2i &vPos);
		PLGUI_API virtual void OnMouseButtonDoubleClick(PLGeneral::uint32 nButton, const PLMath::Vector2i &vPos);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Send message to XEMBED embedder window
		*
		*  @param[in] nMessage
		*    Message opcode
		*  @param[in] nDetail
		*    Message detail
		*  @param[in] nData1
		*    First parameter
		*  @param[in] nData2
		*    Second parameter
		*/
		void SendXEmbedMessage(long nMessage, long nDetail, long nData1, long nData2);

		/**
		*  @brief
		*    Send system tray message to XEMBED embedder window
		*
		*  @param[in] nWindow
		*    Window
		*  @param[in] nMessage
		*    Message opcode
		*  @param[in] nDetail
		*    Message detail
		*  @param[in] nData1
		*    First parameter
		*  @param[in] nData2
		*    Second parameter
		*/
		void SendSysTrayMessage(::Window nWindow, long nMessage, long nDetail, long nData1, long nData2);

		/**
		*  @brief
		*    Send system tray data message to XEMBED embedder window
		*
		*  @param[in] nWindow
		*    Window
		*  @param[in] pszString
		*    String data
		*  @param[in] nSize
		*    Size of string data (excluding the terminating zero), max. 20!
		*/
		void SendSysTrayMessageData(::Window nWindow, const char *pszString, long nSize);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		TrayIcon *m_pTrayIcon;			/**< Tray icon instance */
		::Window  m_nEmbedderWindow;	/**< Embedder window */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_TRAYICONWIDGETLINUX_H__
