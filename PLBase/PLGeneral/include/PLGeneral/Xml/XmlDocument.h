/*********************************************************\
 *  File: XmlDocument.h                                  *
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


#ifndef __PLGENERAL_XML_DOCUMENT_H__
#define __PLGENERAL_XML_DOCUMENT_H__
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
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class XmlParsingData;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    XML (Extensible Markup Language) document node
*
*  @remarks
*    Always the top level node. A document binds together all the
*    XML pieces. It can be saved, loaded, and printed to the screen.
*    The 'value' of a document node is the XML filename.
*
*    The XML DOM parser is basing on TinyXML (http://www.sourceforge.net/projects/tinyxml).
*/
class XmlDocument : public XmlNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XmlText;
	friend class XmlNode;
	friend class XmlUnknown;
	friend class XmlElement;
	friend class XmlComment;
	friend class XmlAttribute;
	friend class XmlDeclaration;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLGENERAL_API XmlDocument();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sName
		*    Document name. The name of the document is also the filename of the XML.
		*/
		PLGENERAL_API XmlDocument(const String &sName);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLGENERAL_API XmlDocument(const XmlDocument &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API virtual ~XmlDocument();

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
		PLGENERAL_API XmlDocument &operator =(const XmlDocument &cSource);

		/**
		*  @brief
		*    Load a file using the current document value
		*
		*  @param[in] nEncoding
		*    Encoding
		*
		*  @return
		*    Returns 'true' if successful, else 'false'
		*
		*  @note
		*    - Will delete any existing document data before loading
		*/
		PLGENERAL_API bool Load(EEncoding nEncoding = EncodingUnknown);

		/**
		*  @brief
		*    Load a file using the given filename
		*
		*  @param[in] sFilename
		*    Filename
		*  @param[in] nEncoding
		*    Encoding
		*
		*  @return
		*    Returns 'true' if successful, else 'false'
		*
		*  @note
		*    - The document value is set to 'sFilename'
		*/
		PLGENERAL_API bool Load(const String &sFilename, EEncoding nEncoding = EncodingUnknown);

		/**
		*  @brief
		*    Loads from a given file
		*
		*  @param[in] cFile
		*    File to read from, must be opened and readable
		*  @param[in] nEncoding
		*    Encoding
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLGENERAL_API virtual bool Load(File &cFile, EEncoding nEncoding = EncodingUnknown);

		/**
		*  @brief
		*    Save a file using the current document value
		*
		*  @return
		*    Returns 'true' if successful, else 'false'
		*/
		PLGENERAL_API bool Save();

		/**
		*  @brief
		*    Save a file using the given filename
		*
		*  @param[in] sFilename
		*    Filename
		*
		*  @return
		*    Returns 'true' if successful, else 'false'
		*
		*  @note
		*    - The document value is set to 'sFilename'
		*/
		PLGENERAL_API bool Save(const String &sFilename);

		/**
		*  @brief
		*    Get the root element -- the only top level element -- of the document
		*
		*  @return
		*    The root element, a null pointer on error
		*
		*  @note
		*    - In well formed XML, there should only be one. This parser is tolerant of
		*      multiple elements at the document level
		*/
		PLGENERAL_API XmlElement *GetRootElement();
		PLGENERAL_API const XmlElement *GetRootElement() const;

		/**
		*  @brief
		*    If an error occurs, error will be set to true
		*
		*  @return
		*    'true' if an error occurs, else 'false'
		*
		*  @note
		*    - 'GetErrorID()' will contain the integer identifier of the error (not generally useful)
		*    - 'GetErrorDesc()' will return the name of the error. (very useful)
		*    - 'GetErrorRow()' and 'GetErrorColumn()' will return the location of the error (if known)
		*/
		PLGENERAL_API bool Error() const;

		/**
		*  @brief
		*    Contains a textual (english) description of the error if one occurs
		*
		*  @param[in] bLocation
		*    Do also add the location (if known) of the error?
		*
		*  @return
		*    Error description
		*/
		PLGENERAL_API String GetErrorDesc(bool bLocation = true) const;

		/**
		*  @brief
		*    Generally, you probably want the error string ('GetErrorDesc()') - but if you
		*    prefer the error ID, this function will fetch it
		*
		*  @return
		*    Error ID
		*/
		PLGENERAL_API int GetErrorID() const;

		/**
		*  @brief
		*    Returns the location (if known) of the error
		*
		*  @remarks
		*    The first column is column 1, and the first row is row 1. A value of 0 means
		*    the row and column wasn't applicable (memory errors, for example, have no
		*    row/column) or the parser lost the error. (An error in the error reporting,
		*    in that case.)
		*
		*  @return
		*    Row the error occurred
		*
		*  @see
		*    - SetTabSize(), GetRow() and GetColumn()
		*/
		PLGENERAL_API int GetErrorRow() const;

		/**
		*  @brief
		*    The column where the error occured
		*
		*  @return
		*    Column the error occurred
		*
		*  @see
		*    - GetErrorRow()
		*/
		PLGENERAL_API int GetErrorColumn() const;

		/**
		*  @brief
		*    Returns the tab size
		*
		*  @return
		*    Tab size
		*/
		PLGENERAL_API uint32 GetTabSize() const;

		/**
		*  @brief
		*    Sets the tab size
		*
		*  @param[in] nTabSize
		*    New tab size
		*
		*  @remarks
		*    By calling this method, with a tab size greater than 0, the row and column
		*    of each node and attribute is stored when the file is loaded. Very useful
		*    for tracking the DOM back in to the source file.
		*    The tab size is required for calculating the location of nodes. If not
		*    set, the default of 4 is used. The tabsize is set per document. Setting
		*    the tabsize to 0 disables row/column tracking.
		*    Note that row and column tracking is not supported when using operator '>>'
		*    The tab size needs to be enabled before the parse or load. Correct usage:
		*    @verbatim
		*    XmlDocument cDocument;
		*    cDocument.SetTabSize(8);
		*    cDocument.Load("myfile.xml");
		*    @endverbatim
		*
		*    @see
		*      - GetRow() and GetColumn()
		*/
		PLGENERAL_API void SetTabSize(uint32 nTabSize = 4);

		/**
		*  @brief
		*    If you have handled the error, it can be reset with this call
		*
		*  @note
		*    - The error state is automatically cleared if you parse a new XML block
		*/
		PLGENERAL_API void ClearError();


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
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		static const String sErrorString[ErrorStringCount];	/**< Human readable error messages */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Sets an error
		*
		*  @param[in] nError
		*    Error code
		*  @param[in] pszErrorLocation
		*    Error location
		*  @param[in] pData
		*    Data
		*  @param[in] nEncoding
		*    Encoding
		*/
		void SetError(int nError, const char *pszErrorLocation, XmlParsingData *pData, EEncoding nEncoding);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool   m_bError;			/**< Error detected? */
		int    m_nErrorID;			/**< Error ID */
		String m_sErrorDescription;	/**< Human readable error description */
		Cursor m_cErrorCursor;		/**< Error cursor */
		int    m_nTabSize;			/**< Tab size */
		bool   m_bUseMicrosoftBOM;	/**< The UTF-8 BOM were found when read. Note this, and try to write. */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_XML_DOCUMENT_H__
