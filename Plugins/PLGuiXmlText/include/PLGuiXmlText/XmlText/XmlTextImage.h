/*********************************************************\
 *  File: XmlTextImage.h                                 *
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


#ifndef __PLGUIXMLTEXT_IMAGE_H__
#define __PLGUIXMLTEXT_IMAGE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>
#include <PLMath/Vector2i.h>
#include "PLGuiXmlText/PLGuiXmlText.h"
#include "PLGuiXmlText/XmlText/XmlTextElement.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGui {
	class Image;
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
*    Element displaying an image
*/
class XmlTextImage : public XmlTextElement {


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
		PLGUIXMLTEXT_API XmlTextImage(XmlTextElement *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUIXMLTEXT_API virtual ~XmlTextImage();


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
		// Image data
		PLCore::String	  m_sFilename;	/**< Image filename */
		PLMath::Vector2i  m_vSize;		/**< Image size */
		PLGui::Image	 *m_pImage;		/**< Image, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGuiXmlText


#endif // __PLGUIXMLTEXT_IMAGE_H__
