/*********************************************************\
 *  File: GuiWindows.h                                   *
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


#ifndef __PLGUI_GUIWINDOWS_H__
#define __PLGUI_GUIWINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneralWindowsIncludes.h>
#include <PLGeneral/Container/List.h>
#include <PLGeneral/Container/HashMap.h>
#include "PLGui/Backend/GuiImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Screen;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Windows GUI implementation
*/
class GuiWindows : public GuiImpl {


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
		PLGUI_API GuiWindows(Gui *pGui);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~GuiWindows();


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
		*    Static window callback function
		*/
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

		/**
		*  @brief
		*    Static monitor enumeration callback function
		*/
		static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);

		/**
		*  @brief
		*    Static font enumeration callback function (enumerating font names only)
		*/
		static int CALLBACK FontEnumProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, DWORD FontType, LPARAM lParam);

		/**
		*  @brief
		*    Static font enumeration callback function (enumerating all weights and styles of a font)
		*/
		static int CALLBACK FontEnumProc2(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, DWORD FontType, LPARAM lParam);

		/**
		*  @brief
		*    Windows timer callback
		*/
		static void CALLBACK TimerFunction(HWND hWnd, UINT nMsg, UINT_PTR nTimerID, DWORD nTime);

		/**
		*  @brief
		*    Process a tray icon message
		*
		*  @param[in] nID
		*    Tray icon ID
		*  @param[in] nMessage
		*    Notify message
		*/
		static void ProcessTrayIconMessage(TrayIcon *pTrayIcon, PLGeneral::uint32 nID, PLGeneral::uint32 nMessage);

		/**
		*  @brief
		*    Get PLGui widget that belongs to a certain window handle
		*
		*  @param[in] hWnd
		*    Window handle
		*
		*  @return
		*    Widget, can be NULL if hWnd is NULL or the window is not a PLGui widget
		*/
		static Widget *GetPLGuiWidget(HWND hWnd);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// System handles
		HINSTANCE				  m_hInstance;			/**< Main process handle */
		DWORD					  m_nThreadID;			/**< Main thread ID */
		WNDCLASS				  m_WndClass;			/**< Window class */

		// Screens
		PLGeneral::List<Screen*>  m_lstScreens;			/**< List of available screens (monitors) */

		// Widgets
		Widget					 *m_pMouseOver;			/**< Widget that the mouse has currently entered */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_GUIWINDOWS_H__
