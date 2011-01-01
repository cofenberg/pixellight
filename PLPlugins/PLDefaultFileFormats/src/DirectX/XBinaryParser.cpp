/*********************************************************\
 *  File: XBinaryParser.cpp                              *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/File/File.h>
#include "PLDefaultFileFormats/DirectX/XBinaryParser.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ XToken implementation                                 ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the token type
*/
XToken::EType XToken::GetType() const
{
	return m_nType;
}

/**
*  @brief
*    Returns the first child token
*/
XToken *XToken::GetFirstChildToken() const
{
	return m_pChildToken;
}

/**
*  @brief
*    Returns the next token
*/
XToken *XToken::GetNextToken() const
{
	return m_pNextToken;
}

//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XToken::XToken(EType nType) :
	m_nType(nType),
	m_pChildToken(NULL),
	m_pNextToken(NULL)
{
}

/**
*  @brief
*    Destructor
*/
XToken::~XToken()
{
	if (m_pChildToken) delete m_pChildToken;
	if (m_pNextToken)  delete m_pNextToken;
}

/**
*  @brief
*    Reads all tokens inside a block
*/
void XToken::ReadTokens(File &cFile, XToken &cParentToken)
{
	XToken *pCurrentToken = NULL;

	// Read the first token type
	uint16 nTokenType;
	int nNumOfReadBytes = (int)cFile.Read(&nTokenType, sizeof(nTokenType), 1);
	while (nNumOfReadBytes) {
		XToken *pNewToken = NULL;

		// Process the token
		switch (nTokenType) {
			case TOKEN_NAME:			pNewToken = new XTokenName(cFile);		break;
			case TOKEN_STRING:			pNewToken = new XTokenString(cFile);	break;
			case TOKEN_INTEGER:			pNewToken = new XTokenInt(cFile);		break;
			case TOKEN_GUID:			pNewToken = new XTokenGUID(cFile);		break;
			case TOKEN_INTEGER_LIST:	pNewToken = new XTokenIntList(cFile);	break;
			case TOKEN_FLOAT_LIST:		pNewToken = new XTokenFloatList(cFile);	break;

			case TOKEN_OBRACE:
				// '{' found, go 'inside'
				if (pCurrentToken) {
					ReadTokens(cFile, *pCurrentToken);
					break;
				} else return; // Error!

			case TOKEN_CBRACE:
				// '}' found, return to the parent
				return;

			case TOKEN_TEMPLATE:		pNewToken = new XTokenTemplate(cFile);	break;

			default:
				// Once we reach an unknown type we'll just add the token
				pNewToken = new XToken((EType)nTokenType);
				break;
		}

		// Link the new token (if there's one :)
		if (pNewToken) {
			if (pCurrentToken) {
				pCurrentToken->m_pNextToken = pNewToken;
			} else {
				// This is the first child token
				cParentToken.m_pChildToken = pNewToken;
			}
			pCurrentToken = pNewToken;
		}

		// Read the next token type
		nNumOfReadBytes = (int)cFile.Read(&nTokenType, sizeof(nTokenType), 1);
	}
}


//[-------------------------------------------------------]
//[ XTokenRoot implementation                             ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XTokenRoot::XTokenRoot(File &cFile) : XToken(TOKEN_ROOT)
{
	ReadTokens(cFile, *this);
}

/**
*  @brief
*    Destructor
*/
XTokenRoot::~XTokenRoot()
{
}


//[-------------------------------------------------------]
//[ XTokenName implementation                             ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the length of the name, in bytes
*/
uint32 XTokenName::GetLength() const
{
	return m_nLength;
}

/**
*  @brief
*    Returns the ASCII name
*/
char *XTokenName::GetName() const
{
	return m_pszName;
}

/**
*  @brief
*    Someone took over the control of the name (and therefore is responsible for cleanup)
*/
void XTokenName::ControlTaken()
{
	m_nLength = 0;
	m_pszName = NULL;
}

//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XTokenName::XTokenName(File &cFile) : XToken(TOKEN_NAME),
	m_pszName(NULL)
{
	// Read the name
	cFile.Read(&m_nLength, sizeof(uint32), 1);
	if (m_nLength) {
		// Size doesn't include the null terminator!
		m_pszName = new char[m_nLength+1];
		cFile.Read(m_pszName, sizeof(char), m_nLength);
		m_pszName[m_nLength] = '\0';
	}
}

/**
*  @brief
*    Destructor
*/
XTokenName::~XTokenName()
{
	if (m_pszName) delete m_pszName;
}


//[-------------------------------------------------------]
//[ XTokenString implementation                           ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the length of the string, in bytes
*/
uint32 XTokenString::GetLength() const
{
	return m_nLength;
}

/**
*  @brief
*    Returns the ASCII string
*/
char *XTokenString::GetString() const
{
	return m_pszString;
}

/**
*  @brief
*    Someone took over the control of the string (and therefore is responsible for cleanup)
*/
void XTokenString::ControlTaken()
{
	m_nLength   = 0;
	m_pszString = NULL;
}

//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XTokenString::XTokenString(File &cFile) : XToken(TOKEN_STRING),
	m_pszString(NULL)
{
	// Read the string
	cFile.Read(&m_nLength, sizeof(uint32), 1);
	if (m_nLength) {
		// Size doesn't include the null terminator!
		m_pszString = new char[m_nLength+1];
		cFile.Read(m_pszString, sizeof(char), m_nLength);
		m_pszString[m_nLength] = '\0';
	}

	// Read the terminator
	cFile.Read(&m_nTerminator, sizeof(uint16), 1);
}

/**
*  @brief
*    Destructor
*/
XTokenString::~XTokenString()
{
	if (m_pszString) delete m_pszString;
}


//[-------------------------------------------------------]
//[ XTokenInt implementation                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XTokenInt::XTokenInt(File &cFile) : XToken(TOKEN_INTEGER)
{
	cFile.Read(&m_value, sizeof(uint32), 1);
}


//[-------------------------------------------------------]
//[ XTokenGUID implementation                             ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XTokenGUID::XTokenGUID(File &cFile) : XToken(TOKEN_GUID)
{
	cFile.Read(&m_Data1, sizeof(uint32), 1);
	cFile.Read(&m_Data2, sizeof(uint16), 1);
	cFile.Read(&m_Data3, sizeof(uint16), 1);
	for (uint8 i=0; i<8; i++)
		cFile.Read(&m_Data4[i], sizeof(uint8), 1);
}


//[-------------------------------------------------------]
//[ XTokenIntList implementation                          ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XTokenIntList::XTokenIntList(File &cFile) : XToken(TOKEN_INTEGER_LIST),
	m_list(NULL)
{
	cFile.Read(&m_nLength, sizeof(uint32), 1);
	if (m_nLength) {
		m_list = new uint32[m_nLength];
		cFile.Read(m_list, sizeof(uint32), m_nLength);
	}
}

/**
*  @brief
*    Destructor
*/
XTokenIntList::~XTokenIntList()
{
	if (m_list) delete m_list;
}


//[-------------------------------------------------------]
//[ XTokenFloatList implementation                        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XTokenFloatList::XTokenFloatList(File &cFile) : XToken(TOKEN_FLOAT_LIST),
	m_list(NULL)
{
	cFile.Read(&m_nLength, sizeof(uint32), 1);
	if (m_nLength) {
		m_list = new float[m_nLength];
		cFile.Read(m_list, sizeof(float), m_nLength);
	}
}

/**
*  @brief
*    Destructor
*/
XTokenFloatList::~XTokenFloatList()
{
	if (m_list) delete m_list;
}


//[-------------------------------------------------------]
//[ XTokenTemplate implementation                         ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XTokenTemplate::XTokenTemplate(File &cFile) : XToken(TOKEN_TEMPLATE),
	pszName(NULL),
	pGUID(NULL)
{
	// Template name
	uint16 nTokenType;
	cFile.Read(&nTokenType, sizeof(nTokenType), 1);
//	if (nTokenType != TOKEN_NAME)
//		dprintf("ERROR - Token Template Unknown syntax (expected TOKEN_NAME)\n");
	pszName = new XTokenName(cFile);

	// '{'
	cFile.Read(&nTokenType, sizeof(nTokenType), 1);
//	if (nTokenType != TOKEN_OBRACE)
//		dprintf("ERROR - Token Template Unknown syntax (expected TOKEN_OBRACE\n");

	// GUID
	cFile.Read(&nTokenType, sizeof(nTokenType), 1);
//	if (nTokenType != TOKEN_GUID)
//		dprintf("ERROR - Token Template Unknown syntax (expected TOKEN_GUID\n");
	pGUID = new XTokenGUID(cFile);

	// Read all tokens within the block
	ReadTokens(cFile, *this);
}

/**
*  @brief
*    Destructor
*/
XTokenTemplate::~XTokenTemplate()
{
	if (pszName) delete pszName;
	if (pGUID)   delete pGUID;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
