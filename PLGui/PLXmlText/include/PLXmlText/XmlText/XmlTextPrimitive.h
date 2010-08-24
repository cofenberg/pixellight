/*********************************************************\
 *  File: XmlTextPrimitive.h                             *
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


#ifndef __PLXMLTEXT_PRIMITIVE_H__
#define __PLXMLTEXT_PRIMITIVE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLMath/Vector2i.h>
#include <PLGraphics/Color/Color4.h>
#include <PLGui/Gui/Resources/Font.h>
#include "PLXmlText/PLXmlText.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGui {
	class Image;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLXmlText {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    XmlText primitive element
*/
class XmlTextPrimitive {


	//[-------------------------------------------------------]
	//[ Public data types                                     ]
	//[-------------------------------------------------------]
	public:
		enum EPrimitiveType {
			PrimitiveText = 0,	/**< Primitive is a word */
			PrimitiveImage,		/**< Primitive is an image */
			PrimitiveBullet		/**< Primitive is a bullet in front of a list element */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		XmlTextPrimitive() :
			m_nType(PrimitiveText),
			m_cTextColor(PLGraphics::Color4::Transparent),
			m_cBgColor(PLGraphics::Color4::Transparent),
			m_pImage(NULL),
			m_nIndent(0),
			m_nHGap(0),
			m_pFont(NULL)
		{
		}

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cPrimitive
		*    Primitive to copy
		*/
		XmlTextPrimitive(const XmlTextPrimitive &cPrimitive) :
			m_nType(cPrimitive.m_nType),
			m_cTextColor(cPrimitive.m_cTextColor),
			m_cBgColor(cPrimitive.m_cBgColor),
			m_vSize(cPrimitive.m_vSize),
			m_sText(cPrimitive.m_sText),
			m_pImage(cPrimitive.m_pImage),
			m_nIndent(cPrimitive.m_nIndent),
			m_nHGap(cPrimitive.m_nHGap),
			m_pFont(cPrimitive.m_pFont ? new PLGui::Font(*cPrimitive.m_pFont) : NULL)
		{
		}

		/**
		*  @brief
		*    Destructor
		*/
		~XmlTextPrimitive()
		{
			// Destroy the font
			if (m_pFont)
				delete m_pFont;
		}

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] cPrimitive
		*    Primitive to copy
		*/
		inline XmlTextPrimitive &operator =(const XmlTextPrimitive &cPrimitive)
		{
			// Destroy the previous font
			if (m_pFont) {
				delete m_pFont;
				m_pFont = NULL;
			}

			// Copy data
			m_nType		 = cPrimitive.m_nType;
			m_cTextColor = cPrimitive.m_cTextColor;
			m_cBgColor	 = cPrimitive.m_cBgColor;
			m_vSize		 = cPrimitive.m_vSize;
			m_sText		 = cPrimitive.m_sText;
			m_pImage	 = cPrimitive.m_pImage;
			m_nIndent	 = cPrimitive.m_nIndent;
			m_nHGap		 = cPrimitive.m_nHGap;
			m_pFont		 = cPrimitive.m_pFont ? new PLGui::Font(*cPrimitive.m_pFont) : NULL;

			// Done
			return *this;
		}

		/**
		*  @brief
		*    Comparison operator
		*
		*  @param[in] cPrimitive
		*    Primitive to compare with
		*
		*  @return
		*    'true' if both primitives are equal, else 'false'
		*/
		inline bool operator ==(const XmlTextPrimitive &cPrimitive) const
		{
			// Get the font implementations
			PLGui::FontImpl *pFontImpl			= m_pFont			 ? m_pFont->GetImpl()			 : NULL;
			PLGui::FontImpl *pPrimitiveFontImpl = cPrimitive.m_pFont ? cPrimitive.m_pFont->GetImpl() : NULL;

			// Compare
			return (m_nType		 == cPrimitive.m_nType &&
					m_cTextColor == cPrimitive.m_cTextColor &&
					m_cBgColor	 == cPrimitive.m_cBgColor &&
					m_vSize		 == cPrimitive.m_vSize &&
					m_sText		 == cPrimitive.m_sText &&
					m_pImage	 == cPrimitive.m_pImage &&
					m_nIndent	 == cPrimitive.m_nIndent &&
					m_nHGap		 == cPrimitive.m_nHGap &&
					pFontImpl	 == pPrimitiveFontImpl);
		}

		/**
		*  @brief
		*    Return the font
		*
		*  @return
		*    The font, can be NULL
		*/
		PLGui::Font *GetFont() const
		{
			return m_pFont;
		}

		/**
		*  @brief
		*    Set the font
		*
		*  @param[in] pFont
		*    Font to set, can be NULL
		*/
		void SetFont(PLGui::Font *pFont)
		{
			// Destroy the previous font
			if (m_pFont) {
				delete m_pFont;
				m_pFont = NULL;
			}

			// Set the new font
			m_pFont = pFont ? new PLGui::Font(*pFont) : NULL;
		}


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		// Primitive
		EPrimitiveType		 m_nType;			/**< Type of primitive */
		PLGraphics::Color4	 m_cTextColor;		/**< Current text color */
		PLGraphics::Color4	 m_cBgColor;		/**< Current background color */
		PLMath::Vector2i	 m_vSize;			/**< Size of primitive */
		int					 m_nHGap;			/**< Horizontal gap after primitive */

		// PrimitiveText
		PLGeneral::String	 m_sText;			/**< Text to print */

		// PrimitiveImage
		const PLGui::Image	*m_pImage;			/**< Image */

		// PrimitiveBullet
		int					 m_nIndent;			/**< Indent at which to draw the bullet */


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGui::Font *m_pFont;	/**< Current font, can be NULL */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLXmlText


#endif // __PLXMLTEXT_PRIMITIVE_H__
