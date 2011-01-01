/*********************************************************\
 *  File: XmlTextSection.h                               *
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


#ifndef __PLXMLTEXT_SECTION_H__
#define __PLXMLTEXT_SECTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLMath/Vector2i.h>
#include <PLGraphics/Color/Color4.h>
#include "PLXmlText/PLXmlText.h"
#include "PLXmlText/XmlText/XmlTextElement.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLXmlText {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Element describing a section
*/
class XmlTextSection : public XmlTextElement {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XmlTextElement;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pParent
		*    Parent object, can be NULL
		*/
		PLXMLTEXT_API XmlTextSection(XmlTextElement *pParent = NULL);

		/**
		*  @brief
		*    Destructor
		*/
		PLXMLTEXT_API virtual ~XmlTextSection();


	//[-------------------------------------------------------]
	//[ Protected virtual XmlTextNew functions                ]
	//[-------------------------------------------------------]
	protected:
		PLXMLTEXT_API virtual void OnParse(PLGeneral::XmlNode &cXmlNode);
		PLXMLTEXT_API virtual void OnDraw(XmlTextRenderer &cRenderer);
		PLXMLTEXT_API virtual PLMath::Vector2i OnGetSize() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Section data
		PLMath::Vector2i	m_vPos;				/**< Position */
		PLMath::Vector2i	m_vSize;			/**< Size */
		int					m_nPaddingLeft;		/**< Number of pixels between left border and content */
		int					m_nPaddingRight;	/**< Number of pixels between right border and content */
		int					m_nPaddingTop;		/**< Number of pixels between top border and content */
		int					m_nPaddingBottom;	/**< Number of pixels between bottom border and content */
		PLGraphics::Color4	m_cBgColor;			/**< Background color */
		PLGeneral::String	m_sBackground;		/**< Background image */
		float				m_fAlpha;			/**< Alpha transparency */
		int					m_nBorder;			/**< Border size */
		PLGraphics::Color4	m_cBorderColor;		/**< Background color */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLXmlText


#endif // __PLXMLTEXT_SECTION_H__
