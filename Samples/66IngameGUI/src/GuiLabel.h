/*********************************************************\
 *  File: GuiLabel.h                                     *
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


#ifndef __PLSAMPLE_66_GUILABEL_H__
#define __PLSAMPLE_66_GUILABEL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "GuiBase.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGui {
	class Font;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Ingame Gui - Label (text item)
*/
class GuiLabel : public GuiBase {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, GuiLabel, "", GuiBase, "Ingame Gui - Label (text item)")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Text alignment
		*/
		enum ETextAlign {
			AlignLeft,
			AlignRight,
			AlignCenter,
			AlignBlock
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pParent
		*    Parent widget, can be a null pointer
		*/
		GuiLabel(PLGui::Widget *pParent);

		/**
		*  @brief
		*    Get text
		*
		*  @return
		*    Text displayed in the item
		*/
		PLCore::String GetText() const;

		/**
		*  @brief
		*    Set text
		*
		*  @param[in] sText
		*    Text displayed in the item
		*/
		void SetText(const PLCore::String &sText);

		/**
		*  @brief
		*    Get font
		*
		*  @return
		*    Used font
		*/
		PLGui::Font *GetFont() const;

		/**
		*  @brief
		*    Set font
		*
		*  @param[in] pFont
		*    Used font
		*/
		void SetFont(PLGui::Font *pFont);

		/**
		*  @brief
		*    Get text color
		*
		*  @return
		*    Text color
		*/
		PLGraphics::Color4 GetColor() const;

		/**
		*  @brief
		*    Set text color
		*
		*  @param[in] cColor
		*    Test color
		*/
		void SetColor(const PLGraphics::Color4 &cColor);

		/**
		*  @brief
		*    Get text alignment
		*
		*  @return
		*    Text alignment
		*/
		ETextAlign GetAlign() const;

		/**
		*  @brief
		*    Set text alignment
		*
		*  @param[in] nAlign
		*    Text alignment
		*/
		void SetAlign(ETextAlign nAlign);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~GuiLabel();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String		 m_sText;	/**< Displayed text */
		PLGui::Font			*m_pFont;	/**< Selected font */
		PLGraphics::Color4	 m_cColor;	/**< Text color */
		ETextAlign			 m_nAlign;	/**< Text alignment */


	//[-------------------------------------------------------]
	//[ Public virtual PLGui::Widget functions                ]
	//[-------------------------------------------------------]
	public:
		virtual void OnDraw(PLGui::Graphics &cGraphics) override;


};


#endif // __PLSAMPLE_66_GUILABEL_H__
