/*********************************************************\
 *  File: FocusWidget.h                                  *
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


#ifndef __PLSAMPLE98_FOCUSWIDGET_H__
#define __PLSAMPLE98_FOCUSWIDGET_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Widgets/Widget.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Test widget for focus events
*/
class FocusWidget : public PLGui::Widget {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, FocusWidget, "", PLGui::Widget, "Test widget for focus events")
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
		FocusWidget(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~FocusWidget();


	//[-------------------------------------------------------]
	//[ Public virtual Widget functions                       ]
	//[-------------------------------------------------------]
	public:
		virtual void OnDraw(PLGui::Graphics &cGraphics);
		virtual void OnGetFocus();
		virtual void OnLooseFocus();
		virtual void OnActivate(bool bActivate);


};


#endif // __PLSAMPLE98_FOCUSWIDGET_H__
