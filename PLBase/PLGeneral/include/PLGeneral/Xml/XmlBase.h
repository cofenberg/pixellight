/*********************************************************\
 *  File: XmlBase.h                                      *
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


#ifndef __PLGENERAL_XML_BASE_H__
#define __PLGENERAL_XML_BASE_H__
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
class File;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract XML base class
*
*  @remarks
*    'XmlBase' is a base class for every class of the XML parser.
*    It does little except to establish that parser classes can be printed and provide
*    some utility functions. In XML, the document and elements can contain other
*    elements and other types of nodes.
*
*    @verbatim
*    A document can contain: Element (container or leaf)
*                            Comment (leaf)
*                            Unknown (leaf)
*                            Declaration (leaf)
*
*    An element can contain: Element (container or leaf)
*                            Text (leaf)
*                            Attributes (not on tree)
*                            Comment (leaf)
*                            Unknown (leaf)
*
*    A declaration contains: Attributes (not on tree)
*    @endverbatim
*/
class XmlBase {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Error codes
		*/
		enum {
			NoError,						/**< No error */
			Error,							/**< Error */
			ErrorOpeningFile,				/**< Error opening file */
			ErrorOutOfMemory,				/**< Error out of memory */
			ErrorParsingElement,			/**< Error parsing element */
			ErrorFailedToReadElementName,	/**< Error failed to read element name */
			ErrorReadingElementValue,		/**< Error reading element value */
			ErrorReadingAttributes,			/**< Error reading attributes */
			ErrorParsingEmpty,				/**< Error parsing empty */
			ErrorReadingEndTag,				/**< Error reading end tag */
			ErrorParsingUnknown,			/**< Error parsing unknown */
			ErrorParsingComment,			/**< Error parsing comment */
			ErrorParsingDeclaration,		/**< Error parsing declaration */
			ErrorDocumentEmpty,				/**< Error document empty */
			ErrorEmbeddedNull,				/**< Error embedded null */
			ErrorStringCount				/**< Error string count */
		};

		/**
		*  @brief
		*    Only used by 'Attribute::Query'-functions
		*/
		enum EQueryResult {
			Success,		/**< All went fine */
			NoAttribute,	/**< Attribut does not exist */
			WrongType		/**< Invalid attribute type */
		};


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Return the current white space setting
		*
		*  @return
		*    'true' if white space condensed is set, else 'false'
		*
		*  @remarks
		*    The world does not agree on whether white space should be kept or
		*    not. In order to make everyone happy, these global, static functions
		*    are provided to set whether or not the parser will condense all white space
		*    into a single space or not. The default is to condense. Note changing this
		*    values is not thread safe.
		*/
		PLGENERAL_API static bool IsWhiteSpaceCondensed();

		/**
		*  @brief
		*    Set white space handling
		*
		*  @param[in] bCondense
		*    'true' if white space condensed is set, else 'false'
		*
		*  @see
		*    - IsWhiteSpaceCondensed()
		*/
		PLGENERAL_API static void SetCondenseWhiteSpace(bool bCondense);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API virtual ~XmlBase();

		/**
		*  @brief
		*    Return the row position, in the original source file, of this node or attribute
		*
		*  @return
		*    Row position
		*
		*  @remarks
		*    The row and column are 1-based. (That is the first row and first column is
		*    1, 1). If the returns values are 0 or less, then the parser does not have
		*    a row and column value.
		*    Generally, the row and column value will be set when the 'XmlDocument::Load()',
		*    'XmlDocument::Load()', or any 'XmlNode::Parse()' is called. It will NOT be set
		*    when the DOM was created from operator '>>'.
		*    The values reflect the initial load. Once the DOM is modified programmatically
		*    (by adding or changing nodes and attributes) the new values will NOT update to
		*    reflect changes in the document.
		*    There is a minor performance cost to computing the row and column. Computation
		*    can be disabled if 'XmlDocument::SetTabSize()' is called with 0 as the value.
		*
		*  @see
		*    - XmlDocument::SetTabSize()
		*/
		PLGENERAL_API int GetRow() const;

		/**
		*  @brief
		*    Return the column position, in the original source file, of this node or attribute
		*
		*  @return
		*    Column position
		*
		*  @see
		*    - GetRow()
		*/
		PLGENERAL_API int GetColumn() const;

		/**
		*  @brief
		*    Returns the user data
		*
		*  @return
		*    User data, can be NULL
		*
		*  @note
		*    - The user data is not used internally, it's really user only :)
		*/
		PLGENERAL_API void *GetUserData() const;

		/**
		*  @brief
		*    Sets the user data
		*
		*  @param[in] pUser
		*    User data, can be NULL
		*
		*  @see
		*    - GetUserData()
		*/
		PLGENERAL_API void SetUserData(void *pUser);

		/**
		*  @brief
		*    Returns the internal data
		*
		*  @return
		*    Internal data (always valid!)
		*
		*  @note
		*    - For internal usage only!
		*/
		void *GetData() const;

		/**
		*  @brief
		*    Sets the internal data
		*
		*  @param[in] pData
		*    New internal data (must be always valid!)
		*
		*  @note
		*    - For internal usage only!
		*/
		void SetData(void *pData);


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Save function
		*
		*  @param[out] cFile
		*    File to write in, must be opened and writable
		*  @param[in]  nDepth
		*    Current depth
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Save(File &cFile, uint32 nDepth = 0) = 0;

		/**
		*  @brief
		*    Output as string function
		*
		*  @param[in] nDepth
		*    Current depth
		*
		*  @return
		*    String containing the XML
		*/
		virtual PLGeneral::String ToString(uint32 nDepth = 0) = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pData
		*    Pointer to the concrete data (always valid!)
		*/
		XmlBase(void *pData);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		void *m_pData;	/**< Pointer to the concrete data (always valid, set within the derived classes) */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
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
		XmlBase &operator =(const XmlBase &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		void *m_pUserData;	/**< User data, can be NULL */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_XML_BASE_H__
