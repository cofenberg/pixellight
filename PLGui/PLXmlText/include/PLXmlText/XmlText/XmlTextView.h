/*********************************************************\
 *  File: XmlTextView.h                                  *
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


#ifndef __PLXMLTEXT_VIEW_H__
#define __PLXMLTEXT_VIEW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Widgets/Widget.h>
#include "PLXmlText/PLXmlText.h"
#include "PLXmlText/XmlText/XmlTextRenderer.h"
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
*    Control that display's a text using a XML based markup language
*/
class XmlTextView : public PLGui::Widget {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLXMLTEXT_RTTI_EXPORT, XmlTextView, "PLXmlText", PLGui::Widget, "Control that display's a text using a XML based markup language")
		pl_attribute(Filename,	PLGeneral::String,	"",	ReadWrite,	GetSet,	"Filename of XmlText file",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLXMLTEXT_API PLGeneral::String GetFilename() const;
		PLXMLTEXT_API void SetFilename(const PLGeneral::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pParent
		*    Parent widget, can be NULL
		*/
		PLXMLTEXT_API XmlTextView(Widget *pParent = NULL);

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
		*    Get document root
		*
		*  @return
		*    Path to document root (directory containing XmlText document)
		*/
		PLXMLTEXT_API PLGeneral::String GetDocumentRoot() const;

		/**
		*  @brief
		*    Get size of content
		*
		*  @return
		*    Content size
		*/
		PLXMLTEXT_API PLMath::Vector2i GetContentSize() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Destructor
		*/
		PLXMLTEXT_API virtual ~XmlTextView();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Exported variables
		PLGeneral::String		m_sFilename;		/**< File name */
		PLGeneral::String		m_sDocumentRoot;	/**< Path containing the file */

		// XML text
		XmlTextElement			m_cXmlText;			/**< XmlText element tree */
		XmlTextRenderer			m_cRenderer;		/**< XmlText renderer */


	//[-------------------------------------------------------]
	//[ Public virtual Window functions                       ]
	//[-------------------------------------------------------]
	public:
		PLXMLTEXT_API virtual void OnDraw(PLGui::Graphics &cGraphics);
		PLXMLTEXT_API virtual void OnSize(const PLMath::Vector2i &vSize);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLXmlText


#endif // __PLXMLTEXT_VIEW_H__
