/*********************************************************\
 *  File: XmlText.cpp                                    *
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
#include "PLGeneral/File/File.h"
#include "PLGeneral/Xml/XmlText.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XmlText::XmlText(const String &sValue) :
	XmlNode(new TiXmlText(sValue))
{
}

/**
*  @brief
*    Copy constructor
*/
XmlText::XmlText(const XmlText &cSource) :
	XmlNode(new TiXmlText(*(TiXmlText*)cSource.m_pData))
{
}

/**
*  @brief
*    Destructor
*/
XmlText::~XmlText()
{
}

/**
*  @brief
*    Copy operator
*/
XmlText &XmlText::operator =(const XmlText &cSource)
{
	*((TiXmlText*)m_pData) = (const TiXmlText&)*((TiXmlText*)cSource.m_pData);
	return *this;
}


//[-------------------------------------------------------]
//[ Public virtual XmlBase functions                      ]
//[-------------------------------------------------------]
bool XmlText::Save(File &cFile, uint32 nDepth)
{
	TIXML_STRING sBuffer;

	TiXmlBase::EncodeString(((TiXmlText*)m_pData)->ValueTStr(), &sBuffer);
	cFile.Print(sBuffer.c_str());

	// Done
	return true;
}

String XmlText::ToString(uint32 nDepth)
{
	TIXML_STRING sBuffer;
	TiXmlBase::EncodeString(((TiXmlText*)m_pData)->ValueTStr(), &sBuffer);
	return String(sBuffer.c_str());
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XmlText::XmlText(void *pNode, int nDummy) :
	XmlNode(pNode)
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
