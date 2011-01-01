/*********************************************************\
 *  File: WidgetPL.h                                     *
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


#ifndef __PLSCENE_SCENENODE_GUI_WIDGET_H__
#define __PLSCENE_SCENENODE_GUI_WIDGET_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Tools/QuickSort.h>
#include <PLGraphics/Color/Color4.h>
#include <PLGui/Backend/WidgetImpl.h>
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGui {
	class GuiPL;
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
*    PixelLight ingame GUI widget implementation
*/
class WidgetPL : public PLGui::WidgetImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class GuiPL;


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
		PLS_API WidgetPL(PLGui::Widget &cWidget);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~WidgetPL();


	//[-------------------------------------------------------]
	//[ Public virtual PLGui::WidgetImpl functions            ]
	//[-------------------------------------------------------]
	public:
		virtual void CreateWidget();
		virtual void CreateWrapperWidget(PLGeneral::handle nWindowHandle);
		virtual bool IsDestroyed() const;
		virtual void Destroy();
		virtual PLGeneral::handle GetWindowHandle() const;
		virtual void SetParent(PLGui::WidgetImpl *pParent);
		virtual bool IsShowInTaskbar() const;
		virtual void SetShowInTaskbar(bool bShowInTaskbar);
		virtual void MoveToScreen(PLGui::Screen &cScreen);
		virtual PLMath::Vector2i GetPos() const;
		virtual void SetPos(const PLMath::Vector2i &vPos);
		virtual PLMath::Vector2i GetSize() const;
		virtual void SetSize(const PLMath::Vector2i &vSize);
		virtual void SetZPos(PLGui::EZPos nZPos, PLGui::Widget *pWidget);
		virtual bool IsTopmost() const;
		virtual void SetTopmost(bool bTopmost);
		virtual PLGui::EWindowState GetWindowState() const;
		virtual void SetWindowState(PLGui::EWindowState nWindowState);
		virtual void SetTransparency(PLGui::ETransparency nTransparency, const PLGraphics::Color4 &cColor);
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
		virtual void SetIcon(const PLGui::Image &cIcon);
		virtual PLGeneral::uint32 RegisterHotkey(PLGeneral::uint32 nModKey, PLGeneral::uint32 nKey);
		virtual void UnregisterHotkey(PLGeneral::uint32 nID);
		virtual void SetCursor(const PLGui::Cursor &cCursor);
		virtual bool GetMousePos(PLMath::Vector2i &vPos);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Set Z position
		*
		*  @param[in, out] lstChildren
		*    List of z position sorted child widgets, smaller number for widgets below other with higher numbers
		*  @param[in]      nZPos
		*    Z position (see EZPos)
		*  @param[in]      pWidget
		*    Other widget used to align relative to (only matters for 'ZAbove' or 'ZBehind')
		*/
		void SetZPos(PLGeneral::Array<PLGui::Widget*> &lstChildren, PLGui::EZPos nZPos, PLGui::Widget *pWidget = NULL);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGui::Widget					   *m_pWidget;				/**< Reference to platform independent widget, always valid! */
		bool								m_bWrapper;				/**< 'true' if this is a wrapper for a system window */
		bool								m_bDestroyed;			/**< 'true' if the widget has already been destroyed */
		PLGui::EWindowState					m_nWindowState;			/**< Current window state */
		PLMath::Vector2i					m_vPos;					/**< Widget position */
		PLMath::Vector2i					m_vSize;				/**< Widget size */
		bool								m_bTopmost;				/**< Is this widget topmost */
		bool								m_bFullscreen;			/**< Fullscreen mode */
		PLGui::ETransparency				m_nTransparency;		/**< Widget transparency type */
		PLGraphics::Color4					m_cTransparencyColor;	/**< Widget color */
		bool								m_bVisible;				/**< Is the widget visible? */
		bool								m_bEnabled;				/**< Is the widget enabled? */
		bool								m_bCaptureMouse;		/**< Capture mouse? */
		PLGeneral::Array<PLGui::Widget*>	m_lstTopmostChildren;	/**< List of z position sorted topmost child widgets, smaller number for widgets below other with higher numbers */
		PLGeneral::Array<PLGui::Widget*>	m_lstChildren;			/**< List of z position sorted child widgets (including topmost), smaller number for widgets below other with higher numbers */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_GUI_WIDGET_H__
