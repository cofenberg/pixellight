/*********************************************************\
 *  File: XBinaryParser.h                                *
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


#ifndef __PLDEFAULTFILEFORMATS_DIRECTX_SCENELOADER_X_H__
#define __PLDEFAULTFILEFORMATS_DIRECTX_XBINARYPARSER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneral.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class File;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Token base class
*/
class XToken {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Type of the token
		*/
		enum EType {
			// Record-bearing
			TOKEN_NAME			= 1,
			TOKEN_STRING		= 2,
			TOKEN_INTEGER		= 3,
			TOKEN_GUID			= 5,
			TOKEN_INTEGER_LIST	= 6,
			TOKEN_FLOAT_LIST	= 7,
			// Stand-alone
			TOKEN_OBRACE		= 10,
			TOKEN_CBRACE		= 11,
			TOKEN_OPAREN		= 12,
			TOKEN_CPAREN		= 13,
			TOKEN_OBRACKET		= 14,
			TOKEN_CBRACKET		= 15,
			TOKEN_OANGLE		= 16,
			TOKEN_CANGLE		= 17,
			TOKEN_DOT			= 18,
			TOKEN_COMMA			= 19,
			TOKEN_SEMICOLON		= 20,
			TOKEN_TEMPLATE		= 31,
			TOKEN_WORD			= 40,
			TOKEN_DWORD			= 41,
			TOKEN_FLOAT			= 42,
			TOKEN_DOUBLE		= 43,
			TOKEN_CHAR			= 44,
			TOKEN_UCHAR			= 45,
			TOKEN_SWORD			= 46,
			TOKEN_SDWORD		= 47,
			TOKEN_VOID			= 48,
			TOKEN_LPSTR			= 49,
			TOKEN_UNICODE		= 50,
			TOKEN_CSTRING		= 51,
			TOKEN_ARRAY			= 52,
			TOKEN_ROOT			= 9999999
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the token type
		*
		*  @return
		*    The token type
		*/
		EType GetType() const;

		/**
		*  @brief
		*    Returns the first child token
		*
		*  @return
		*    The first child token, NULL if there's no first child token
		*/
		XToken *GetFirstChildToken() const;

		/**
		*  @brief
		*    Returns the next token
		*
		*  @return
		*    The next token, NULL if there's no next token
		*/
		XToken *GetNextToken() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nType
		*    Token type
		*/
		XToken(EType nType);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XToken();

		/**
		*  @brief
		*    Reads all tokens inside a block
		*
		*  @param[in] cFile
		*    File to use
		*  @param[in] cParentToken
		*    Parent token
		*/
		void ReadTokens(PLGeneral::File &cFile, XToken &cParentToken);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		EType   m_nType;		/**< Token type */
		XToken *m_pChildToken;	/**< First child token, can be NULL */
		XToken *m_pNextToken;	/**< Next token, can be NULL */


};

/**
*  @brief
*    Root token
*
*  @remarks
*    Processes a binary x file to receive a hierarchical token representation of the data.
*/
class XTokenRoot : public XToken {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFile
		*    File to use
		*/
		XTokenRoot(PLGeneral::File &cFile);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XTokenRoot();


};

/**
*  @brief
*    Name token
*/
class XTokenName : public XToken {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XToken;
	friend class XTokenTemplate;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the length of the name, in bytes
		*
		*  @return
		*    The length of the name, in bytes
		*/
		PLGeneral::uint32 GetLength() const;

		/**
		*  @brief
		*    Returns the ASCII name
		*
		*  @return
		*    The ASCII name, NULL on error
		*/
		char *GetName() const;

		/**
		*  @brief
		*    Someone took over the control of the name (and therefore is responsible for cleanup)
		*/
		void ControlTaken();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFile
		*    File to use
		*/
		XTokenName(PLGeneral::File &cFile);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XTokenName();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::uint32  m_nLength;	/**< Length of name field, in bytes */
		char			  *m_pszName;	/**< Array count ASCII name, can be NULL */


};

/**
*  @brief
*    String token
*/
class XTokenString : public XToken {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XToken;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the length of the string, in bytes
		*
		*  @return
		*    The length of the string, in bytes (excluding the terminating zero)
		*/
		PLGeneral::uint32 GetLength() const;

		/**
		*  @brief
		*    Returns the ASCII string
		*
		*  @return
		*    The ASCII string, NULL on error
		*/
		char *GetString() const;

		/**
		*  @brief
		*    Someone took over the control of the string (and therefore is responsible for cleanup)
		*/
		void ControlTaken();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFile
		*    File to use
		*/
		XTokenString(PLGeneral::File &cFile);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XTokenString();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::uint32	m_nLength;		/**< DWORD 4 length of string field in bytes (excluding the terminating zero) */
		char			   *m_pszString;	/**< BYTE array count ASCII string, can be NULL */
		PLGeneral::uint16	m_nTerminator;	/**< DWORD 4 TOKEN_SEMICOLON or TOKEN_COMMA */


};

/**
*  @brief
*    Integer token
*/
class XTokenInt : public XToken {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XToken;


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		PLGeneral::uint32 m_value;	/**< DWORD 4 single integer */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFile
		*    File to use
		*/
		XTokenInt(PLGeneral::File &cFile);


};

/**
*  @brief
*    GUID token
*/
class XTokenGUID : public XToken {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XToken;
	friend class XTokenTemplate;


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		PLGeneral::uint32 m_Data1;		/**< DWORD 4 GUID data field 1 */
		PLGeneral::uint16 m_Data2;		/**< WORD 2 GUID data field 2 */
		PLGeneral::uint16 m_Data3;		/**< WORD 2 GUID data field 3 */
		PLGeneral::uint8  m_Data4[8];	/**< BYTE array 8 GUID data field 4 */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFile
		*    File to use
		*/
		XTokenGUID(PLGeneral::File &cFile);


};

/**
*  @brief
*    Integer list token
*/
class XTokenIntList : public XToken {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XToken;


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		PLGeneral::uint32  m_nLength;	/**< DWORD 4 number of integers in list field */
		PLGeneral::uint32 *m_list;		/**< DWORD 4 x count integer list, can be NULL */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFile
		*    File to use
		*/
		XTokenIntList(PLGeneral::File &cFile);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XTokenIntList();


};

/**
*  @brief
*    Float list token
*/
class XTokenFloatList : public XToken {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XToken;


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		PLGeneral::uint32  m_nLength;	/**< DWORD 4 number of floats or doubles in list field */
		float			  *m_list;		/**< float/double array 4 or 8 x count float or double list
											 determined from the header accuracy, can be NULL */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFile
		*    File to use
		*/
		XTokenFloatList(PLGeneral::File &cFile);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XTokenFloatList();


};

/**
*  @brief
*    Template token
*/
class XTokenTemplate : public XToken {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XToken;


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		XTokenName *pszName;	/**< TOKEN_NAME, can be NULL */
		XTokenGUID *pGUID;		/**< TOKEN_GUID, can be NULL */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFile
		*    File to use
		*/
		XTokenTemplate(PLGeneral::File &cFile);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XTokenTemplate();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats


#endif // __PLDEFAULTFILEFORMATS_DIRECTX_XBINARYPARSER_H__
