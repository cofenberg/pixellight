/*********************************************************\
 *  File: Border.h                                       *
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


#ifndef __PLGUI_BORDER_H__
#define __PLGUI_BORDER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color4.h>
#include "PLGui/Themes/Theme.h"
#include "PLGui/Widgets/Containers/ContainerWidget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Container widget that displays a border around it's content
*/
class Border : public ContainerWidget {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, Border, "PLGui", PLGui::ContainerWidget, "Container widget that displays a border around it's content")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute	(LineStyle,		pl_enum_type(ELineStyle),	SolidLine,					ReadWrite, GetSet,	"Line style",		"")
		pl_attribute	(BorderSize,	int,						1,							ReadWrite, GetSet,	"Border size",		"")
		pl_attribute	(BorderColor,	PLGraphics::Color4,			PLGraphics::Color4::Black,	ReadWrite, GetSet,	"Border color",		"")
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
		PLGUI_API Border(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~Border();

		/**
		*  @brief
		*    Get line style
		*
		*  @return
		*    Line style
		*/
		PLGUI_API ELineStyle GetLineStyle() const;

		/**
		*  @brief
		*    Set line style
		*
		*  @param[in] nLineStyle
		*    Line style
		*/
		PLGUI_API void SetLineStyle(ELineStyle nLineStyle);

		/**
		*  @brief
		*    Get border size
		*
		*  @return
		*    Border size
		*/
		PLGUI_API int GetBorderSize() const;

		/**
		*  @brief
		*    Set border size
		*
		*  @param[in] nSize
		*    Border size
		*/
		PLGUI_API void SetBorderSize(int nSize);

		/**
		*  @brief
		*    Get border color
		*
		*  @return
		*    Border color
		*/
		PLGUI_API const PLGraphics::Color4 &GetBorderColor() const;

		/**
		*  @brief
		*    Set border color
		*
		*  @param[in] cColor
		*    Border color
		*/
		PLGUI_API void SetBorderColor(const PLGraphics::Color4 &cColor);


	//[-------------------------------------------------------]
	//[ Public virtual Widget functions                       ]
	//[-------------------------------------------------------]
	public:
		PLGUI_API virtual void OnDraw(Graphics &cGraphics);
		PLGUI_API virtual PLMath::Vector2i OnPreferredSize(const PLMath::Vector2i &vRefSize) const;
		PLGUI_API virtual void OnAdjustContent();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	public:
		ELineStyle			m_nLineStyle;		/**< Line style */
		int					m_nBorderSize;		/**< Border size */
		PLGraphics::Color4	m_cBorderColor;		/**< Border color */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_BORDER_H__
