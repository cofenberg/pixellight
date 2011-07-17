/*********************************************************\
 *  File: HTMLParser.h                                   *
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


#ifndef __PLGENERAL_HTMLPARSER_H__
#define __PLGENERAL_HTMLPARSER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class XmlDocument;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    HTML parser
*
*  @remarks
*    This class provides a simple HTML parser. It does NOT comply with any existent HTML standard,
*    but it tries to be as flexible as possible in allowing many typical errors such as mixed HTML
*    and XML style as well as not properly closed tags. So don't expect this class to be able of parsing
*    any existing homepage out there. However, the class can be used to read in an HTML file and
*    produce an XML syntax tree as if it were an XML file. You can then use standard XML classes to
*    access the parsed document tree.
*/
class HTMLParser {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API HTMLParser();

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API ~HTMLParser();

		/**
		*  @brief
		*    Clear all data
		*/
		PLGENERAL_API void Clear();

		/**
		*  @brief
		*    Load file
		*
		*  @param[in] sFilename
		*    Filename of the HTML document to load in
		*/
		PLGENERAL_API void Load(const String &sFilename);

		/**
		*  @brief
		*    Get parsed HTML as an XML document
		*
		*  @return
		*    Pointer to XML document, a null pointer if there's currently no document
		*/
		PLGENERAL_API XmlDocument *GetXML() const;

		/**
		*  @brief
		*    Get number of errors occuring while parsing the HTML file
		*
		*  @return
		*    Number of errors
		*/
		PLGENERAL_API uint32 GetNumOfErrors() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Parse whole HTML file and generate a XML parsing tree
		*
		*  @return
		*    'true' if HTML file could be parsed, 'false' on error
		*/
		bool Parse();

		/**
		*  @brief
		*    Check if there is another token waiting
		*
		*  @return
		*    'true' if next token is available, else 'false'
		*/
		bool HasNextToken();

		/**
		*  @brief
		*    Get next token from HTML parser
		*
		*  @return
		*    Next token, or "" when there are no more tokens
		*/
		String GetNextToken();

		/**
		*  @brief
		*    Returns whether or not the given string is a single tag (no closing tag required to be well-formed!)
		*
		*  @param[in] sTag
		*    Tag to check
		*
		*  @return
		*    'true' the given string is a single tag, else 'false'
		*/
		bool IsSingleTag(const String &sTag) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		String		 m_sFilename;	/**< File name */
		String		 m_sText;		/**< Content of HTML file */
		String		 m_sTextLower;	/**< Text version in lower case */
		uint32		 m_nPos;		/**< Parsing position */
		String		 m_sToken;		/**< Currently parsed token */
		XmlDocument	*m_pXML;		/**< Parsed HTML, can be a null pointer */
		uint32		 m_nErrors;		/**< Number of errors */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_HTMLPARSER_H__
