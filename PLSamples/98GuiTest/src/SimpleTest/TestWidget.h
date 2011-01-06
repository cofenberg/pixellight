/*********************************************************\
 *  File: TestWidget.h                                   *
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


#ifndef __PLSAMPLE98_TESTWIDGET_H__
#define __PLSAMPLE98_TESTWIDGET_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color4.h>
#include <PLGui/Widgets/Widget.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Very simple test widget
*/
class TestWidget : public PLGui::Widget {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, TestWidget, "", PLGui::Widget, "Very simple test widget")
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
		*    Pointer to parent widget
		*/
		TestWidget(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~TestWidget();

		/**
		*  @brief
		*    Set if this window can exit the application
		*
		*  @param[in] bExit
		*    if 'true', exit on right mouse-button or ALT+F4
		*/
		void SetExit(bool bExit);

		/**
		*  @brief
		*    Set default color (visible if no focus is set to the window)
		*
		*  @param[in] cColor
		*    Color
		*/
		void SetColor(const PLGraphics::Color4 &cColor);


	//[-------------------------------------------------------]
	//[ Public virtual Widget functions                       ]
	//[-------------------------------------------------------]
	public:
		virtual void OnClose();
		virtual void OnMouseButtonDown(PLGeneral::uint32 nButton, const PLMath::Vector2i &vPos);
		virtual void OnGetFocus();
		virtual void OnLooseFocus();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool				m_bExit;		/**< Exit application on right-click or ALT+F4? */
		PLGraphics::Color4	m_cColor;		/**< Default color */


};


#endif // __PLSAMPLE98_TESTWIDGET_H__
