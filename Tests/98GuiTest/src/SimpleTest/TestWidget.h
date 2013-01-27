/*********************************************************\
 *  File: TestWidget.h                                   *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
	//[ Public virtual PLGui::Widget functions                ]
	//[-------------------------------------------------------]
	public:
		virtual void OnClose() override;
		virtual void OnMouseButtonDown(PLCore::uint32 nButton, const PLMath::Vector2i &vPos) override;
		virtual void OnGetFocus() override;
		virtual void OnLooseFocus() override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool				m_bExit;	/**< Exit application on right-click or ALT+F4? */
		PLGraphics::Color4	m_cColor;	/**< Default color */


};


#endif // __PLSAMPLE98_TESTWIDGET_H__
