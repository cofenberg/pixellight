/*********************************************************\
 *  File: XmlTextText.h                                  *
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


#ifndef __PLGUIXMLTEXT_TEXT_H__
#define __PLGUIXMLTEXT_TEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>
#include <PLGraphics/Color/Color4.h>
#include "PLGuiXmlText/PLGuiXmlText.h"
#include "PLGuiXmlText/XmlText/XmlTextElement.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGuiXmlText {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Element describing a text section
*/
class XmlTextText : public XmlTextElement {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] bParagraph
		*    If 'true', create an own paragraph, otherwise just change options within paragraph
		*  @param[in] pParent
		*    Parent object, can be a null pointer
		*/
		PLGUIXMLTEXT_API XmlTextText(bool bParagraph, XmlTextElement *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUIXMLTEXT_API virtual ~XmlTextText();


	//[-------------------------------------------------------]
	//[ Protected virtual XmlTextElement functions            ]
	//[-------------------------------------------------------]
	protected:
		PLGUIXMLTEXT_API virtual void OnParse(PLCore::XmlNode &cXmlNode) override;
		PLGUIXMLTEXT_API virtual void OnDraw(XmlTextRenderer &cRenderer) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Text options
		bool					m_bParagraph;	/**< If 'true', this element defines it's own paragraph */
		PLGraphics::Color4		m_cTextColor;	/**< Text color */
		PLGraphics::Color4		m_cBgColor;		/**< Background color */
		PLCore::String			m_sFont;		/**< Font name */
		int						m_nFontSize;	/**< Font size */
		XmlTextRenderer::HAlign	m_nHAlign;		/**< Horizontal alignment */
		XmlTextRenderer::VAlign	m_nVAlign;		/**< Vertical alignment */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGuiXmlText


#endif // __PLGUIXMLTEXT_TEXT_H__
