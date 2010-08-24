/*********************************************************\
 *  File: XmlDeclaration.cpp                             *
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
#include "PLGeneral/Xml/XmlDeclaration.h"


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
XmlDeclaration::XmlDeclaration() :
	XmlNode(new TiXmlDeclaration())
{
}

/**
*  @brief
*    Constructor
*/
XmlDeclaration::XmlDeclaration(const String &sVersion, const String &sEncoding, const String &sStandalone) :
	XmlNode(new TiXmlDeclaration(sVersion, sEncoding, sStandalone))
{
}

/**
*  @brief
*    Copy constructor
*/
XmlDeclaration::XmlDeclaration(const XmlDeclaration &cSource) :
	XmlNode(new TiXmlDeclaration(*(TiXmlDeclaration*)cSource.m_pData))
{
}

/**
*  @brief
*    Destructor
*/
XmlDeclaration::~XmlDeclaration()
{
}

/**
*  @brief
*    Copy operator
*/
XmlDeclaration &XmlDeclaration::operator =(const XmlDeclaration &cSource)
{
	*((TiXmlDeclaration*)m_pData) = (const TiXmlDeclaration&)*((TiXmlDeclaration*)cSource.m_pData);
	return *this;
}

/**
*  @brief
*    Version - will return an empty string if none was found
*/
String XmlDeclaration::GetVersion() const
{
	return ((TiXmlDeclaration*)m_pData)->Version();
}

/**
*  @brief
*    Encoding - will return an empty string if none was found
*/
String XmlDeclaration::GetEncoding() const
{
	return ((TiXmlDeclaration*)m_pData)->Encoding();
}

/**
*  @brief
*    Standalone - will return an empty string if none was found
*/
String XmlDeclaration::GetStandalone() const
{
	return ((TiXmlDeclaration*)m_pData)->Standalone();
}


//[-------------------------------------------------------]
//[ Public virtual XmlBase functions                      ]
//[-------------------------------------------------------]
bool XmlDeclaration::Save(File &cFile, uint32 nDepth)
{
	cFile.Print("<?xml ");

	if (GetVersion().GetLength())
		cFile.Print("version=\"" + GetVersion() + "\" ");
	if (GetEncoding().GetLength())
		cFile.Print("encoding=\"" + GetEncoding() + "\" ");
	if (GetStandalone().GetLength())
		cFile.Print("standalone=\"" + GetStandalone() + "\" ");
	cFile.Print("?>");

	// Done
	return true;
}

String XmlDeclaration::ToString(uint32 nDepth)
{
	String sXml = "<?xml ";

	if (GetVersion().GetLength())
		sXml += "version=\"" + GetVersion() + "\" ";
	if (GetEncoding().GetLength())
		sXml += "encoding=\"" + GetEncoding() + "\" ";
	if (GetStandalone().GetLength())
		sXml += "standalone=\"" + GetStandalone() + "\" ";
	sXml += "?>";

	// Done
	return sXml;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XmlDeclaration::XmlDeclaration(void *pNode, int nDummy) :
	XmlNode(pNode)
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
