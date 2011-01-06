/*********************************************************\
 *  File: XmlText.h                                      *
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


#ifndef __PLGENERAL_XML_TEXT_H__
#define __PLGENERAL_XML_TEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Xml/XmlNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    XML text node - contained in an XML element
*/
class XmlText : public XmlNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XmlNode;
	friend class XmlElement;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		XmlText();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sValue
		*    Value of this text node
		*/
		PLGENERAL_API XmlText(const String &sValue);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLGENERAL_API XmlText(const XmlText &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API virtual ~XmlText();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		PLGENERAL_API XmlText &operator =(const XmlText &cSource);

		/**
		*  @brief
		*    Queries whether this represents text using a CDATA section
		*
		*  @return
		*    'true' if this is input and output as a CDATA style text element, else 'false'
		*/
		PLGENERAL_API bool IsCDATA() const;

		/**
		*  @brief
		*    Turns on or off a CDATA representation of text
		*
		*  @param[in] bCDATA
		*    'true' if this should be input and output as a CDATA style text element, else 'false'
		*/
		PLGENERAL_API void SetCDATA(bool bCDATA);


	//[-------------------------------------------------------]
	//[ Public virtual XmlBase functions                      ]
	//[-------------------------------------------------------]
	public:
		PLGENERAL_API virtual bool Save(File &cFile, uint32 nDepth = 0);
		PLGENERAL_API virtual String ToString(uint32 nDepth = 0) const;
		PLGENERAL_API const char *Parse(const char *pszData, XmlParsingData *pData = nullptr, EEncoding nEncoding = EncodingUnknown);


	//[-------------------------------------------------------]
	//[ Public virtual XmlNode functions                      ]
	//[-------------------------------------------------------]
	public:
		PLGENERAL_API virtual XmlNode *Clone() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool m_bCDATA;	/**< 'true' if this should be input and output as a CDATA style text element */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_XML_TEXT_H__
