/*********************************************************\
 *  File: Label.h                                        *
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


#ifndef __PLGUI_LABEL_H__
#define __PLGUI_LABEL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color4.h>
#include "PLGui/Gui/Resources/Font.h"
#include "PLGui/Widgets/Widget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Widget that displays a static text
*/
class Label : public Widget {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, Label, "PLGui", PLGui::Widget, "Widget that displays a static text")
		// Attributes
		pl_attribute(Color,		PLGraphics::Color4,			PLGraphics::Color4::Black,	ReadWrite,	GetSet,	"Text color",					"")
		pl_attribute(Align,		pl_enum_type(EAlign),		AlignLeft,					ReadWrite,	GetSet,	"Text alignment (horizontal)",	"")
		pl_attribute(VAlign,	pl_enum_type(EVAlign),		AlignMiddle,				ReadWrite,	GetSet,	"Text alignment (vertical)",	"")
		pl_attribute(Wrap,		pl_enum_type(ETextWrap),	TextWrap,					ReadWrite,	GetSet,	"Text wrapping",				"")
		pl_attribute(Style,		pl_flag_type(ETextStyle),	0,							ReadWrite,	GetSet,	"Text style",					"")
		pl_attribute(Text,		PLCore::String,				"",							ReadWrite,	GetSet,	"Text label",					"")
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
		PLGUI_API Label(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~Label();

		/**
		*  @brief
		*    Get font
		*
		*  @return
		*    Font
		*/
		PLGUI_API const Font &GetFont() const;

		/**
		*  @brief
		*    Set font
		*
		*  @param[in] cFont
		*    Font
		*/
		PLGUI_API void SetFont(const Font &cFont);

		/**
		*  @brief
		*    Get color
		*
		*  @return
		*    Color
		*/
		PLGUI_API PLGraphics::Color4 GetColor() const;

		/**
		*  @brief
		*    Set color
		*
		*  @param[in] cColor
		*    Color
		*/
		PLGUI_API void SetColor(const PLGraphics::Color4 &cColor);

		/**
		*  @brief
		*    Get horizontal alignment
		*
		*  @return
		*    Alignment
		*/
		PLGUI_API EAlign GetAlign() const;

		/**
		*  @brief
		*    Set horizontal alignment
		*
		*  @param[in] nAlign
		*    Alignment
		*/
		PLGUI_API void SetAlign(EAlign nAlign);

		/**
		*  @brief
		*    Get vertical alignment
		*
		*  @return
		*    Alignment
		*/
		PLGUI_API EVAlign GetVAlign() const;

		/**
		*  @brief
		*    Set vertical alignment
		*
		*  @param[in] nAlign
		*    Alignment
		*/
		PLGUI_API void SetVAlign(EVAlign nAlign);

		/**
		*  @brief
		*    Get text wrapping
		*
		*  @return
		*    Wrapping mode
		*/
		PLGUI_API ETextWrap GetWrap() const;

		/**
		*  @brief
		*    Set text wrapping
		*
		*  @param[in] nWrap
		*    Wrapping mode
		*/
		PLGUI_API void SetWrap(ETextWrap nWrap);

		/**
		*  @brief
		*    Get text style
		*
		*  @return
		*    Text style
		*/
		PLGUI_API PLCore::uint32 GetStyle() const;

		/**
		*  @brief
		*    Set text style
		*
		*  @param[in] nStyle
		*    Text style
		*/
		PLGUI_API void SetStyle(PLCore::uint32 nStyle);

		/**
		*  @brief
		*    Get text
		*
		*  @return
		*    Text
		*/
		PLGUI_API PLCore::String GetText() const;

		/**
		*  @brief
		*    Set text
		*
		*  @param[in] sText
		*    Text
		*/
		PLGUI_API void SetText(const PLCore::String &sText);


	//[-------------------------------------------------------]
	//[ Protected virtual WidgetFunctions functions           ]
	//[-------------------------------------------------------]
	private:
		PLGUI_API virtual PLMath::Vector2i OnPreferredSize(const PLMath::Vector2i &vRefSize) const override;
		PLGUI_API virtual void OnDraw(Graphics &cGraphics) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Exported variables
		PLGraphics::Color4	m_cColor;
		EAlign				m_nAlign;
		EVAlign				m_nVAlign;
		ETextWrap			m_nWrap;
		PLCore::uint32		m_nStyle;
		PLCore::String		m_sText;

		// Private data
		Font				m_cFont;		/**< Used font */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_LABEL_H__
