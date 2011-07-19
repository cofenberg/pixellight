/*********************************************************\
 *  File: Theme.h                                        *
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


#ifndef __PLGUI_THEME_H__
#define __PLGUI_THEME_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include <PLMath/Vector2i.h>
#include <PLGraphics/Color/Color4.h>
#include "PLGui/Gui/Resources/Image.h"
#include "PLGui/Gui/Resources/Font.h"
#include "PLGui/PLGuiDefinitions.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGraphics {
	class Color4;
}
namespace PLGui {
	class Gui;
	class Graphics;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Theme
*/
class Theme : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, Theme, "PLGui", PLCore::Object, "GUI theme class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Gui;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cGui
		*    Owner GUI
		*  @param[in] sName
		*    Name of modifier
		*/
		PLGUI_API Theme(Gui &cGui, const PLCore::String &sName = "");

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~Theme();

		/**
		*  @brief
		*    Get owner GUI
		*
		*  @return
		*    Pointer to GUI object (never a null pointer)
		*/
		PLGUI_API Gui *GetGui() const;

		/**
		*  @brief
		*    Get name of theme
		*
		*  @return
		*    Name of theme
		*/
		PLGUI_API PLCore::String GetName() const;

		/**
		*  @brief
		*    Get default font
		*
		*  @return
		*    Default font
		*/
		PLGUI_API const PLGui::Font &GetDefaultFont() const;

		/**
		*  @brief
		*    Get default icon
		*
		*  @return
		*    Default icon
		*/
		PLGUI_API const PLGui::Image &GetDefaultIcon() const;

		/**
		*  @brief
		*    Get window border size
		*
		*  @return
		*    Border size
		*/
		PLGUI_API int GetWindowBorderSize() const;

		/**
		*  @brief
		*    Get window title bar height
		*
		*  @return
		*    Title bar height
		*/
		PLGUI_API int GetWindowTitleBarHeight() const;

		/**
		*  @brief
		*    Get menu bar height
		*
		*  @return
		*    Menu bar height
		*/
		PLGUI_API int GetMenuBarHeight() const;

		/**
		*  @brief
		*    Get default window color
		*
		*  @return
		*    Window color
		*/
		PLGUI_API PLGraphics::Color4 GetWindowColor() const;

		/**
		*  @brief
		*    Get panel border size
		*
		*  @return
		*    Border size
		*/
		PLGUI_API int GetPanelBorderSize() const;

		/**
		*  @brief
		*    Get default panel color
		*
		*  @return
		*    Panel color
		*/
		PLGUI_API PLGraphics::Color4 GetPanelColor() const;

		/**
		*  @brief
		*    Get system button size
		*
		*  @return
		*    Size of system button (X and Y)
		*/
		PLGUI_API PLMath::Vector2i GetSysButtonSize() const;


	//[-------------------------------------------------------]
	//[ Public virtual Theme functions                        ]
	//[-------------------------------------------------------]
	public:
		// General drawing functions
		virtual void DrawRect(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, ELineStyle nStyle, const PLGraphics::Color4 &cColor, int nWidth, int nRound = 0) = 0;
		virtual void DrawBorder(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EBorderStyle nBorderStyle) = 0;
		virtual void DrawFocusRect(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2) = 0;
		virtual void DrawSeparator(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation) = 0;
		virtual void DrawRule(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation) = 0;

		// Widgets
		virtual void DrawPanel(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EBorderStyle nBorderStyle) = 0;
		virtual void DrawWindow(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, bool bBorder, PLCore::uint32 nWidgetState, const PLCore::String &sTitle, const PLGui::Image &cIcon) = 0;
		virtual void DrawSystemButton(Graphics &cGraphics, const PLMath::Vector2i &vPos, ESystemCommand nSystemCommand, PLCore::uint32 nWidgetState) = 0;
		virtual void DrawButton(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, const PLCore::String &sTitle, const Image &cImage, PLCore::uint32 nWidgetState) = 0;
		virtual void DrawToggleButton(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, const PLCore::String &sTitle, const Image &cImage, PLCore::uint32 nWidgetState, ECheckState nChecked) = 0;
		virtual void DrawRadioButton(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, const PLCore::String &sTitle, PLCore::uint32 nWidgetState, ECheckState nChecked) = 0;
		virtual void DrawCheckBox(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, const PLCore::String &sTitle, PLCore::uint32 nWidgetState, ECheckState nChecked) = 0;
		virtual void DrawTooltip(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, PLCore::uint32 nWidgetState) = 0;
		virtual void DrawSlider(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation, PLCore::uint32 nWidgetState) = 0;
		virtual void DrawSliderHandle(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation, PLCore::uint32 nWidgetState) = 0;
		virtual void DrawScrollBar(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation, PLCore::uint32 nWidgetState) = 0;
		virtual void DrawScrollBarPlusButton(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation, PLCore::uint32 nWidgetState) = 0;
		virtual void DrawScrollBarMinusButton(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation, PLCore::uint32 nWidgetState) = 0;
		virtual void DrawScrollBarHandle(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation, PLCore::uint32 nWidgetState) = 0;
		virtual void DrawSplitter(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation) = 0;
		virtual void DrawMenuBar(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation, PLCore::uint32 nWidgetState) = 0;
		virtual void DrawPopupMenu(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation, PLCore::uint32 nWidgetState) = 0;
		virtual void DrawMenuItem(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, const PLCore::String &sTitle, const Image &cImage, bool bDrawArrow, EMenuItemType nType, EOrientation nOrientation, PLCore::uint32 nWidgetState) = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Gui
		Gui					*m_pGui;					/**< Owner GUI */
		PLCore::String		 m_sName;					/**< Theme name */

		// Default resources
		PLGui::Font			 m_cDefaultFont;			/**< Default font */
		PLGui::Image		 m_cDefaultIcon;			/**< Default icon */

		// Window
		int					 m_nWindowBorderSize;		/**< Border size of a window */
		int					 m_nWindowTitleBarHeight;	/**< Title bar height of a window */
		int					 m_nMenuBarHeight;			/**< Menu bar height */
		PLGraphics::Color4	 m_cWindowColor;			/**< Default window color */

		// Panel
		int					 m_nPanelBorderSize;		/**< Border size of a panel */
		PLGraphics::Color4	 m_cPanelColor;				/**< Default panel color */

		// SystemButton
		PLMath::Vector2i	 m_vSysButtonSize;			/**< System button size */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_THEME_H__
