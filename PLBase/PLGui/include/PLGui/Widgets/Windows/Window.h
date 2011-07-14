/*********************************************************\
 *  File: Window.h                                       *
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


#ifndef __PLGUI_WINDOW_H__
#define __PLGUI_WINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Widgets/Containers/ContainerWidget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class SystemButton;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Base class for windows (widgets with a border and a title bar)
*/
class Window : public ContainerWidget {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, Window, "PLGui", PLGui::Widget, "Base class for windows (widgets with a border and a title bar)")
		// Attributes
		pl_attribute(SystemButtons,	pl_flag_type(ESystemButton),	7,							ReadWrite,	GetSet,	"System Buttons",				"")
		pl_attribute(ShowTitleBar,	bool,							true,						ReadWrite,	GetSet,	"Show title bar?",				"")
		pl_attribute(ShowBorder,	bool,							true,						ReadWrite,	GetSet,	"Show border?",					"")
		pl_attribute(Resizable,		bool,							true,						ReadWrite,	GetSet,	"Is window resizable?",			"")
		pl_attribute(MinSize,		PLMath::Vector2i,				PLMath::Vector2i(-1, -1),	ReadWrite,	GetSet,	"Minimum size for resizing",	"")
		pl_attribute(MaxSize,		PLMath::Vector2i,				PLMath::Vector2i(-1, -1),	ReadWrite,	GetSet,	"Maximum size for resizing",	"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
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
		*    Pointer to parent widget
		*/
		PLGUI_API Window(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~Window();

		/**
		*  @brief
		*    Get system buttons
		*
		*  @return
		*    Flags describing the displayed system buttons
		*/
		PLGUI_API PLGeneral::uint32 GetSystemButtons() const;

		/**
		*  @brief
		*    Set system buttons
		*
		*  @param[in] nButtons
		*    Flags describing the displayed system buttons
		*/
		PLGUI_API void SetSystemButtons(PLGeneral::uint32 nButtons);

		/**
		*  @brief
		*    Check if a title bar is displayed
		*
		*  @return
		*    'true' if title bar is visible, else 'false'
		*/
		PLGUI_API bool GetShowTitleBar() const;

		/**
		*  @brief
		*    Set if a title bar is displayed
		*
		*  @param[in] bVisible
		*    'true' if title bar is visible, else 'false'
		*/
		PLGUI_API void SetShowTitleBar(bool bVisible);

		/**
		*  @brief
		*    Check if a border is displayed
		*
		*  @return
		*    'true' if border is visible, else 'false'
		*/
		PLGUI_API bool GetShowBorder() const;

		/**
		*  @brief
		*    Set if a border is displayed
		*
		*  @param[in] bVisible
		*    'true' if border is visible, else 'false'
		*/
		PLGUI_API void SetShowBorder(bool bVisible);

		/**
		*  @brief
		*    Check if the window is resizable
		*
		*  @return
		*    'true' if window is resizable, else 'false'
		*/
		PLGUI_API bool GetResizable() const;

		/**
		*  @brief
		*    Set if the window is resizable
		*
		*  @param[in] bResizable
		*    'true' if window is resizable, else 'false'
		*/
		PLGUI_API void SetResizable(bool bResizable);

		/**
		*  @brief
		*    Get minimum size for resizing
		*
		*  @return
		*    Size
		*/
		PLGUI_API PLMath::Vector2i GetMinSize() const;

		/**
		*  @brief
		*    Set minimum size for resizing
		*
		*  @param[in] vSize
		*    Size
		*/
		PLGUI_API void SetMinSize(const PLMath::Vector2i &vSize);

		/**
		*  @brief
		*    Get maximum size for resizing
		*
		*  @return
		*    Size
		*/
		PLGUI_API PLMath::Vector2i GetMaxSize() const;

		/**
		*  @brief
		*    Set maximum size for resizing
		*
		*  @param[in] vSize
		*    Size
		*/
		PLGUI_API void SetMaxSize(const PLMath::Vector2i &vSize);


	//[-------------------------------------------------------]
	//[ Protected virtual WidgetFunctions functions           ]
	//[-------------------------------------------------------]
	protected:
		PLGUI_API virtual void OnDraw(Graphics &cGraphics);
		PLGUI_API virtual void OnAdjustContent();
		PLGUI_API virtual void OnWindowState(EWindowState nWindowState);
		PLGUI_API virtual void OnEnterFullscreen();
		PLGUI_API virtual void OnLeaveFullscreen();
		PLGUI_API virtual void OnActivate(bool bActivate);
		PLGUI_API virtual void OnMove(const PLMath::Vector2i &vPos);
		PLGUI_API virtual void OnMouseMove(const PLMath::Vector2i &vPos);
		PLGUI_API virtual void OnMousePosUpdate(const PLMath::Vector2i &vPos);
		PLGUI_API virtual void OnMouseLeave();
		PLGUI_API virtual void OnMouseButtonDown(PLGeneral::uint32 nButton, const PLMath::Vector2i &vPos);
		PLGUI_API virtual void OnMouseButtonUp(PLGeneral::uint32 nButton, const PLMath::Vector2i &vPos);
		PLGUI_API virtual void OnMouseButtonDoubleClick(PLGeneral::uint32 nButton, const PLMath::Vector2i &vPos);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Exported variables
		PLGeneral::uint32	 m_nSystemButtons;		/**< System buttons that are available in this window */
		bool				 m_bShowTitleBar;		/**< Show title of window? */
		bool				 m_bShowBorder;			/**< Show window border? */
		bool				 m_bResizable;			/**< Is window resizable? */

		// Data
		PLMath::Vector2i	 m_vMinSize;			/**< Minimum size for resizing */
		PLMath::Vector2i	 m_vMaxSize;			/**< Maximum size for resizing */

		// System buttons
		SystemButton		*m_pSysButtonMinimize;	/**< System button to minimize the window size */
		SystemButton		*m_pSysButtonMaximize;	/**< System button to maximize or restore the window size */
		SystemButton		*m_pSysButtonClose;		/**< System button to close the window */

		// Movement state
		PLMath::Vector2i	 m_vPos;				/**< Current widget position */
		PLMath::Vector2i	 m_vMousePos;			/**< Current mouse position */
		bool				 m_bMouseTitle;			/**< Is the mouse position on the title bar? */
		bool				 m_bMouseLeft;			/**< Is the mouse position on the left border? */
		bool				 m_bMouseRight;			/**< Is the mouse position on the right border? */
		bool				 m_bMouseTop;			/**< Is the mouse position on the top border? */
		bool				 m_bMouseBottom;		/**< Is the mouse position on the bottom border? */
		bool				 m_bMove;				/**< Is the window currently moved? */
		bool				 m_bSizeXLeft;			/**< Is the window currently sized (left border)? */
		bool				 m_bSizeXRight;			/**< Is the window currently sized (right border)? */
		bool				 m_bSizeYTop;			/**< Is the window currently sized (top border)? */
		bool				 m_bSizeYBottom;		/**< Is the window currently sized (bottom border)? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_WINDOW_H__
