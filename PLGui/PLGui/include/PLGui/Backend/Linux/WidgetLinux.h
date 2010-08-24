/*********************************************************\
 *  File: WidgetLinux.h                                  *
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


#ifndef __PLGUI_WIDGETLINUX_H__
#define __PLGUI_WIDGETLINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include "PLGui/Backend/WidgetImpl.h"
#include "PLGui/PLGuiLinuxIncludes.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class GuiLinux;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linux widget implementation
*/
class WidgetLinux : public WidgetImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class GuiLinux;
	friend class TrayIconWidgetLinux;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cWidget
		*    Reference to platform independent widget
		*/
		PLGUI_API WidgetLinux(Widget &cWidget);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~WidgetLinux();


	//[-------------------------------------------------------]
	//[ Public virtual WidgetImpl functions                   ]
	//[-------------------------------------------------------]
	public:
		virtual void CreateWidget();
		virtual void CreateWrapperWidget(PLGeneral::handle nWindowHandle);
		virtual bool IsDestroyed() const;
		virtual void Destroy();
		virtual PLGeneral::handle GetWindowHandle() const;
		virtual void SetParent(WidgetImpl *pParent);
		virtual bool IsShowInTaskbar() const;
		virtual void SetShowInTaskbar(bool bShowInTaskbar);
		virtual void MoveToScreen(Screen &cScreen);
		virtual PLMath::Vector2i GetPos() const;
		virtual void SetPos(const PLMath::Vector2i &vPos);
		virtual PLMath::Vector2i GetSize() const;
		virtual void SetSize(const PLMath::Vector2i &vSize);
		virtual void SetZPos(EZPos nZPos, Widget *pWidget);
		virtual bool IsTopmost() const;
		virtual void SetTopmost(bool bTopmost);
		virtual EWindowState GetWindowState() const;
		virtual void SetWindowState(EWindowState nWindowState);
		virtual void SetTransparency(ETransparency nTransparency, const PLGraphics::Color4 &cColor);
		virtual bool IsVisible() const;
		virtual void SetVisible(bool bVisible);
		virtual bool IsEnabled() const;
		virtual void SetEnabled(bool bEnabled);
		virtual void Activate();
		virtual void SetFocus();
		virtual void Redraw();
		virtual void SetCaptureMouse(bool bCapture);
		virtual void SetTrapMouse(bool bTrap);
		virtual void SetTitle(const PLGeneral::String &sTitle);
		virtual void SetIcon(const Image &cIcon);
		virtual PLGeneral::uint32 RegisterHotkey(PLGeneral::uint32 nModKey, PLGeneral::uint32 nKey);
		virtual void UnregisterHotkey(PLGeneral::uint32 nID);
		virtual void SetCursor(const Cursor &cCursor);
		virtual bool GetMousePos(PLMath::Vector2i &vPos);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		void AddWMState(::Atom sAtom1, ::Atom sAtom2 = 0);
		void RemoveWMState(::Atom sAtom1, ::Atom sAtom2 = 0);
		void UpdateWMStates();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Display		*m_pDisplay;		/**< X display */
		int			 m_nScreen;			/**< X screen */
		::Window	 m_nWindow;			/**< X window handle */
		bool		 m_bWrapper;		/**< 'true' if this is a wrapper for a system window */
		bool		 m_bDestroyed;		/**< 'true' if the window has already been destroyed */
		bool		 m_bVisible;		/**< 'true' if the window is visible */
		bool		 m_bEnabled;		/**< 'true' if the window is enabled */
		bool		 m_bTopmost;		/**< 'true' if the window is on top of all other windows */
		bool		 m_bShowInTaskbar;	/**< 'true' if a toplevel window is to be shown in the taskbar */
		int			 m_nX;				/**< X position */
		int			 m_nY;				/**< Y position */
		int			 m_nWidth;			/**< Width */
		int			 m_nHeight;			/**< Height */
		bool		 m_bFullscreen;		/**< Fullscreen mode? */
		bool		 m_bMaximized;		/**< Maximized? */
		bool		 m_bMinimized;		/**< Minimized? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_WIDGETLINUX_H__
