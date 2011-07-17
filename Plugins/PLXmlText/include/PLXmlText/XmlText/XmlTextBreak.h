/*********************************************************\
 *  File: XmlTextBreak.h                                   *
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


#ifndef __PLXMLTEXT_BREAK_H__
#define __PLXMLTEXT_BREAK_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
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
*    Element inserting a line break
*/
class XmlTextBreak : public XmlTextElement {


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
		PLXMLTEXT_API XmlTextBreak(XmlTextElement *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLXMLTEXT_API virtual ~XmlTextBreak();


	//[-------------------------------------------------------]
	//[ Protected virtual XmlTextElement functions            ]
	//[-------------------------------------------------------]
	protected:
		PLXMLTEXT_API virtual void OnParse(PLGeneral::XmlNode &cXmlNode);
		PLXMLTEXT_API virtual void OnDraw(XmlTextRenderer &cRenderer);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLXmlText


#endif // __PLXMLTEXT_BREAK_H__
