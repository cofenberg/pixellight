/*********************************************************\
 *  File: XmlTextElement.h                               *
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


#ifndef __PLXMLTEXT_ELEMENT_H__
#define __PLXMLTEXT_ELEMENT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/List.h>
#include <PLGui/Gui/Resources/Image.h>
#include "PLXmlText/PLXmlText.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class XmlNode;
}
namespace PLGraphics {
	class Color4;
}
namespace PLGui {
	class Gui;
}
namespace PLXmlText {
	class XmlTextView;
	class XmlTextRenderer;
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
*    Base class for XmlText elements
*/
class XmlTextElement {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XmlTextView;


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
		PLXMLTEXT_API XmlTextElement(XmlTextElement *pParent = NULL);

		/**
		*  @brief
		*    Destructor
		*/
		PLXMLTEXT_API virtual ~XmlTextElement();

		/**
		*  @brief
		*    Load XML file
		*
		*  @param[in] sFilename
		*    Filename of XML file
		*/
		PLXMLTEXT_API void Load(const PLGeneral::String &sFilename);

		/**
		*  @brief
		*    Draw element and all children to screen
		*
		*  @param[in] cRenderer
		*    XmlText renderer
		*/
		PLXMLTEXT_API void Draw(XmlTextRenderer &cRenderer);

		/**
		*  @brief
		*    Get size of XMLText content (looks for the first section)
		*/
		PLXMLTEXT_API PLMath::Vector2i GetSize() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Clear element and all children
		*/
		PLXMLTEXT_API void Clear();

		/**
		*  @brief
		*    Parse XML node
		*
		*  @param[in] cXmlNode
		*    XML node to be parsed
		*/
		PLXMLTEXT_API void Parse(PLGeneral::XmlNode &cXmlNode);

		/**
		*  @brief
		*    Draw all children
		*
		*  @param[in] cRenderer
		*    XmlText renderer
		*/
		PLXMLTEXT_API void DrawChildren(XmlTextRenderer &cRenderer);

		/**
		*  @brief
		*    Parse HTML compatible color value
		*
		*  @param[in] sColor
		*    Color value or name
		*
		*  @return
		*    Color
		*/
		PLXMLTEXT_API PLGraphics::Color4 GetColor(const PLGeneral::String &sColor);

		/**
		*  @brief
		*    Load image file
		*
		*  @param[in] cGui
		*    Gui to which the image belongs
		*  @param[in] sFilename
		*    Image file name
		*
		*  @return
		*    Image instance
		*/
		PLXMLTEXT_API PLGui::Image LoadImage(PLGui::Gui &cGui, const PLGeneral::String &sFilename);


	//[-------------------------------------------------------]
	//[ Protected virtual XmlTextElement functions            ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Parse XML node
		*
		*  @param[in] cXmlNode
		*    XML node to be parsed
		*/
		PLXMLTEXT_API virtual void OnParse(PLGeneral::XmlNode &cXmlNode);

		/**
		*  @brief
		*    Draw element
		*
		*  @param[in] cRenderer
		*    XmlText renderer
		*/
		PLXMLTEXT_API virtual void OnDraw(XmlTextRenderer &cRenderer);

		/**
		*  @brief
		*    Get element size
		*
		*  @return
		*    Size of element
		*/
		PLXMLTEXT_API virtual PLMath::Vector2i OnGetSize() const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Element tree
		XmlTextView							*m_pXmlText;		/**< XmlView control */
		XmlTextElement						*m_pParent;			/**< Parent element */
		PLGeneral::List<XmlTextElement*>	 m_lstChildren;		/**< Child elements */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLXmlText


#endif // __PLXMLTEXT_ELEMENT_H__
