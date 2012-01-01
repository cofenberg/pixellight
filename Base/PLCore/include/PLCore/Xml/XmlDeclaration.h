/*********************************************************\
 *  File: XmlDeclaration.h                               *
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


#ifndef __PLCORE_XML_DECLARATION_H__
#define __PLCORE_XML_DECLARATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Xml/XmlNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    XML declaration node
*
*  @remarks
*    In correct XML the declaration is the first entry in the file.
*    @verbatim
*    <?xml version="1.0" standalone="yes"?>
*    @endverbatim
*
*    The parser will happily read or write files without a declaration,
*    however. There are 3 possible attributes to the declaration:
*    version, encoding, and standalone.
*
*  @note
*    - In this version of the code, the attributes are handled as special cases, not
*      generic attributes, simply because there can only be at most 3 and they are
*      always the same.
*/
class XmlDeclaration : public XmlNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XmlNode;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCORE_API XmlDeclaration();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLCORE_API XmlDeclaration(const XmlDeclaration &cSource);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sVersion
		*    Version
		*  @param[in] sEncoding
		*    Encoding
		*  @param[in] sStandalone
		*    Standalone
		*/
		PLCORE_API XmlDeclaration(const String &sVersion, const String &sEncoding, const String &sStandalone);

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~XmlDeclaration();

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
		PLCORE_API XmlDeclaration &operator =(const XmlDeclaration &cSource);

		/**
		*  @brief
		*    Version - will return an empty string if none was found
		*
		*  @return
		*    Version - will return an empty string if none was found
		*/
		inline String GetVersion() const;

		/**
		*  @brief
		*    Encoding - will return an empty string if none was found
		*
		*  @return
		*    Encoding - will return an empty string if none was found
		*/
		inline String GetEncoding() const;

		/**
		*  @brief
		*    Standalone - will return an empty string if none was found
		*
		*  @return
		*    Standalone - will return an empty string if none was found
		*/
		inline String GetStandalone() const;


	//[-------------------------------------------------------]
	//[ Public virtual XmlBase functions                      ]
	//[-------------------------------------------------------]
	public:
		PLCORE_API virtual bool Save(File &cFile, uint32 nDepth = 0) override;
		PLCORE_API virtual String ToString(uint32 nDepth = 0) const override;
		PLCORE_API virtual const char *Parse(const char *pszData, XmlParsingData *pData = nullptr, EEncoding nEncoding = EncodingUnknown) override;


	//[-------------------------------------------------------]
	//[ Public virtual XmlNode functions                      ]
	//[-------------------------------------------------------]
	public:
		PLCORE_API virtual XmlNode *Clone() const override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		String m_sVersion;		/**< Version */
		String m_sEncoding;		/**< Encoding */
		String m_sStandalone;	/**< Standalone */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Xml/XmlDeclaration.inl"


#endif // __PLCORE_XML_DECLARATION_H__
