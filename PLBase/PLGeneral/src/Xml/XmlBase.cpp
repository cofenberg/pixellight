/*********************************************************\
 *  File: XmlBase.cpp                                    *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <tinyxml.h>
#include "PLGeneral/Xml/XmlBase.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Global TinyXML callback function                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Internal TinyXML destroy callback
*/
void F_CALLBACKAPI DestroyCallback(TiXmlBase *pBase)
{
	// Check if this TinyXML node has a PL XML node, if so, delete this too
	if (pBase && pBase->GetUserData()) {
		XmlBase *pPLBase = (XmlBase*)pBase->GetUserData();
		pPLBase->SetData(NULL);
		delete pPLBase;
	}
}


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Return the current white space setting
*/
bool XmlBase::IsWhiteSpaceCondensed()
{
	return TiXmlBase::IsWhiteSpaceCondensed();
}

/**
*  @brief
*    Set white space handling
*/
void XmlBase::SetCondenseWhiteSpace(bool bCondense)
{
	TiXmlBase::SetCondenseWhiteSpace(bCondense);
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
XmlBase::~XmlBase()
{
	// Check for NULL (worst case :)
	if (m_pData) {
		((TiXmlBase*)m_pData)->SetUserData(NULL);
		delete (TiXmlNode*)m_pData;
	}
}

/**
*  @brief
*    Return the row position, in the original source file, of this node or attribute
*/
int XmlBase::GetRow() const
{
	return ((TiXmlBase*)m_pData)->Row();
}

/**
*  @brief
*    Return the column position, in the original source file, of this node or attribute
*/
int XmlBase::GetColumn() const
{
	return ((TiXmlBase*)m_pData)->Column();
}

/**
*  @brief
*    Returns the user data
*/
void *XmlBase::GetUserData() const
{
	return m_pUserData;
}

/**
*  @brief
*    Sets the user data
*/
void XmlBase::SetUserData(void *pUser)
{
	m_pUserData = pUser;
}

/**
*  @brief
*    Returns the internal data
*/
void *XmlBase::GetData() const
{
	return m_pData;
}

/**
*  @brief
*    Sets the internal data
*/
void XmlBase::SetData(void *pData)
{
	m_pData = pData;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XmlBase::XmlBase(void *pData) :
	m_pData(pData),
	m_pUserData(NULL)
{
	// Set TinyXML object user data
	((TiXmlBase*)m_pData)->SetUserData(this);

	// Set general destroy callback function
	TiXmlBase::TiXmlDestroyCallback = DestroyCallback;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy operator
*/
XmlBase &XmlBase::operator =(const XmlBase &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
