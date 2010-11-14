/*********************************************************\
 *  File: ThemeDesktop.h                                 *
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


#ifndef __PLGUI_THEME_DESKTOP_H__
#define __PLGUI_THEME_DESKTOP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color4.h>
#include "PLGui/Gui/Resources/Image.h"
#include "PLGui/Themes/Theme.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PixelLight desktop theme
*/
class ThemeDesktop : public Theme {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Widget;


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, ThemeDesktop, "PLGui", PLGui::Theme, "PixelLight desktop theme")
	pl_class_end


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
		*/
		PLGUI_API ThemeDesktop(Gui &cGui);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~ThemeDesktop();


	//[-------------------------------------------------------]
	//[ Public virtual Theme functions                        ]
	//[-------------------------------------------------------]
	public:
		PLGUI_API virtual void DrawRect(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, ELineStyle nStyle, const PLGraphics::Color4 &cColor, int nWidth, int nRound = 0);
		PLGUI_API virtual void DrawBorder(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EBorderStyle nBorderStyle);
		PLGUI_API virtual void DrawFocusRect(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2);
		PLGUI_API virtual void DrawSeparator(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation);
		PLGUI_API virtual void DrawRule(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation);

		PLGUI_API virtual void DrawPanel(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EBorderStyle nBorderStyle);
		PLGUI_API virtual void DrawWindow(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, bool bBorder, PLGeneral::uint32 nWidgetState, const PLGeneral::String &sTitle, const PLGui::Image &cIcon);
		PLGUI_API virtual void DrawSystemButton(Graphics &cGraphics, const PLMath::Vector2i &vPos, ESystemCommand nSystemCommand, PLGeneral::uint32 nWidgetState);
		PLGUI_API virtual void DrawButton(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, const PLGeneral::String &sTitle, const Image &cImage, PLGeneral::uint32 nWidgetState);
		PLGUI_API virtual void DrawToggleButton(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, const PLGeneral::String &sTitle, const Image &cImage, PLGeneral::uint32 nWidgetState, ECheckState nChecked);
		PLGUI_API virtual void DrawRadioButton(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, const PLGeneral::String &sTitle, PLGeneral::uint32 nWidgetState, ECheckState nChecked);
		PLGUI_API virtual void DrawCheckBox(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, const PLGeneral::String &sTitle, PLGeneral::uint32 nWidgetState, ECheckState nChecked);
		PLGUI_API virtual void DrawTooltip(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, PLGeneral::uint32 nWidgetState);
		PLGUI_API virtual void DrawSlider(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation, PLGeneral::uint32 nWidgetState);
		PLGUI_API virtual void DrawSliderHandle(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation, PLGeneral::uint32 nWidgetState);
		PLGUI_API virtual void DrawScrollBar(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation, PLGeneral::uint32 nWidgetState);
		PLGUI_API virtual void DrawScrollBarPlusButton(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation, PLGeneral::uint32 nWidgetState);
		PLGUI_API virtual void DrawScrollBarMinusButton(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation, PLGeneral::uint32 nWidgetState);
		PLGUI_API virtual void DrawScrollBarHandle(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation, PLGeneral::uint32 nWidgetState);
		PLGUI_API virtual void DrawSplitter(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation);
		PLGUI_API virtual void DrawMenuBar(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation, PLGeneral::uint32 nWidgetState);
		PLGUI_API virtual void DrawPopupMenu(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, EOrientation nOrientation, PLGeneral::uint32 nWidgetState);
		PLGUI_API virtual void DrawMenuItem(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, const PLGeneral::String &sTitle, const Image &cImage, bool bDrawArrow, EMenuItemType nType, EOrientation nOrientation, PLGeneral::uint32 nWidgetState);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		PLGUI_API void DrawControlBorder(Graphics &cGraphics, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, const PLGraphics::Color4 &cColorBorder, const PLGraphics::Color4 &cColorHighlight);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Options
		int					m_nControlRound;					/**< Rounded edges for controls */

		// Colors
		PLGraphics::Color4	m_cColorPanelRaised;				/**< Raised border color */
		PLGraphics::Color4	m_cColorPanelSunken;				/**< Sunken border color */
		PLGraphics::Color4	m_cColorBorder;						/**< Border color */
		PLGraphics::Color4	m_cColorTitleBar;					/**< Title bar color (active) */
		PLGraphics::Color4	m_cColorTitleBarInactive;			/**< Title bar color (inactive) */
		PLGraphics::Color4	m_cColorControlBack;				/**< Controls: Background color */
		PLGraphics::Color4	m_cColorControlBackDisabled;		/**< Controls: Background color (disabled) */
		PLGraphics::Color4	m_cColorControlBackSelect;			/**< Controls: Background color (mouse-over) */
		PLGraphics::Color4	m_cColorControlBackPressed;			/**< Controls: Background color (pressed) */
		PLGraphics::Color4	m_cColorControlBorder;				/**< Controls: Border color */
		PLGraphics::Color4	m_cColorControlBorderSelect;		/**< Controls: Border color (mouse-over) */
		PLGraphics::Color4	m_cColorControlHighlightSelect;		/**< Controls: Highlight color (mouse-over) */

		// Images
		Image				m_cImageArrowLeft;					/**< Arrow left */
		Image				m_cImageArrowRight;					/**< Arrow right */
		Image				m_cImageArrowUp;					/**< Arrow up */
		Image				m_cImageArrowDown;					/**< Arrow down */
		Image				m_cImageRadioButton;				/**< Radio button */
		Image				m_cImageRadioButtonChecked;			/**< Radio button (checked) */
		Image				m_cImageCheckBox;					/**< Check box */
		Image				m_cImageCheckBoxChecked;			/**< Check box (checked) */
		Image				m_cImageCheckBoxPartially;			/**< Check box (partially checked) */
		Image				m_cImageMinimize;					/**< System button 'minimize' */
		Image				m_cImageMaximize;					/**< System button 'maximize' */
		Image				m_cImageRestore;					/**< System button 'restore' */
		Image				m_cImageClose;						/**< System button 'close' */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_THEME_DESKTOP_H__
