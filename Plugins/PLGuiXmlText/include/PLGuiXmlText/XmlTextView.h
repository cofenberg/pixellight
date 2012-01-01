/*********************************************************\
 *  File: XmlTextView.h                                  *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLGUIXMLTEXT_VIEW_H__
#define __PLGUIXMLTEXT_VIEW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Widgets/Widget.h>
#include "PLGuiXmlText/PLGuiXmlText.h"
#include "PLGuiXmlText/XmlTextRenderer.h"
#include "PLGuiXmlText/XmlTextElement.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGuiXmlText {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Control that display's a text using a XML based markup language
*/
class XmlTextView : public PLGui::Widget {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLGUIXMLTEXT_RTTI_EXPORT, XmlTextView, "PLGuiXmlText", PLGui::Widget, "Control that display's a text using a XML based markup language")
		// Attributes
		pl_attribute(Filename,	PLCore::String,	"",	ReadWrite,	GetSet,	"Filename of XmlText file",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLGUIXMLTEXT_API PLCore::String GetFilename() const;
		PLGUIXMLTEXT_API void SetFilename(const PLCore::String &sValue);


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
		PLGUIXMLTEXT_API XmlTextView(Widget *pParent = nullptr);

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
		*    Get document root
		*
		*  @return
		*    Path to document root (directory containing XmlText document)
		*/
		PLGUIXMLTEXT_API PLCore::String GetDocumentRoot() const;

		/**
		*  @brief
		*    Get size of content
		*
		*  @return
		*    Content size
		*/
		PLGUIXMLTEXT_API PLMath::Vector2i GetContentSize() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Destructor
		*/
		PLGUIXMLTEXT_API virtual ~XmlTextView();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Exported variables
		PLCore::String		m_sFilename;		/**< File name */
		PLCore::String		m_sDocumentRoot;	/**< Path containing the file */

		// XML text
		XmlTextElement		m_cXmlText;			/**< XmlText element tree */
		XmlTextRenderer		m_cRenderer;		/**< XmlText renderer */


	//[-------------------------------------------------------]
	//[ Public virtual Window functions                       ]
	//[-------------------------------------------------------]
	public:
		PLGUIXMLTEXT_API virtual void OnDraw(PLGui::Graphics &cGraphics) override;
		PLGUIXMLTEXT_API virtual void OnSize(const PLMath::Vector2i &vSize) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGuiXmlText


#endif // __PLGUIXMLTEXT_VIEW_H__
