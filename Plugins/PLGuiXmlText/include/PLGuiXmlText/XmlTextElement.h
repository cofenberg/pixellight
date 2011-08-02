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


#ifndef __PLGUIXMLTEXT_ELEMENT_H__
#define __PLGUIXMLTEXT_ELEMENT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/List.h>
#include <PLGui/Gui/Resources/Image.h>
#include "PLGuiXmlText/PLGuiXmlText.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class XmlNode;
}
namespace PLGraphics {
	class Color4;
}
namespace PLGui {
	class Gui;
}
namespace PLGuiXmlText {
	class XmlTextView;
	class XmlTextRenderer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGuiXmlText {


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
		*    Parent object, can be a null pointer
		*/
		PLGUIXMLTEXT_API XmlTextElement(XmlTextElement *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUIXMLTEXT_API virtual ~XmlTextElement();

		/**
		*  @brief
		*    Load XML file
		*
		*  @param[in] sFilename
		*    Filename of XML file
		*/
		PLGUIXMLTEXT_API void Load(const PLCore::String &sFilename);

		/**
		*  @brief
		*    Draw element and all children to screen
		*
		*  @param[in] cRenderer
		*    XmlText renderer
		*/
		PLGUIXMLTEXT_API void Draw(XmlTextRenderer &cRenderer);

		/**
		*  @brief
		*    Get size of XMLText content (looks for the first section)
		*/
		PLGUIXMLTEXT_API PLMath::Vector2i GetSize() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Clear element and all children
		*/
		PLGUIXMLTEXT_API void Clear();

		/**
		*  @brief
		*    Parse XML node
		*
		*  @param[in] cXmlNode
		*    XML node to be parsed
		*/
		PLGUIXMLTEXT_API void Parse(PLCore::XmlNode &cXmlNode);

		/**
		*  @brief
		*    Draw all children
		*
		*  @param[in] cRenderer
		*    XmlText renderer
		*/
		PLGUIXMLTEXT_API void DrawChildren(XmlTextRenderer &cRenderer);

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
		PLGUIXMLTEXT_API PLGraphics::Color4 GetColor(const PLCore::String &sColor);

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
		PLGUIXMLTEXT_API PLGui::Image LoadImage(PLGui::Gui &cGui, const PLCore::String &sFilename);


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
		PLGUIXMLTEXT_API virtual void OnParse(PLCore::XmlNode &cXmlNode);

		/**
		*  @brief
		*    Draw element
		*
		*  @param[in] cRenderer
		*    XmlText renderer
		*/
		PLGUIXMLTEXT_API virtual void OnDraw(XmlTextRenderer &cRenderer);

		/**
		*  @brief
		*    Get element size
		*
		*  @return
		*    Size of element
		*/
		PLGUIXMLTEXT_API virtual PLMath::Vector2i OnGetSize() const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Element tree
		XmlTextView						*m_pXmlText;		/**< XmlView control */
		XmlTextElement					*m_pParent;			/**< Parent element */
		PLCore::List<XmlTextElement*>	 m_lstChildren;		/**< Child elements */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGuiXmlText


#endif // __PLGUIXMLTEXT_ELEMENT_H__
