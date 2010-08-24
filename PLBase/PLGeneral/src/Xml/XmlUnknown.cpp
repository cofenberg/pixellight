/*********************************************************\
 *  File: XmlUnknown.cpp                                 *
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
#include "PLGeneral/Xml/XmlDocument.h"
#include "PLGeneral/Xml/XmlUnknown.h"


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
XmlUnknown::XmlUnknown() :
	XmlNode(new TiXmlUnknown())
{
}

/**
*  @brief
*    Copy constructor
*/
XmlUnknown::XmlUnknown(const XmlUnknown &cSource) :
	XmlNode(new TiXmlUnknown(*(TiXmlUnknown*)cSource.m_pData))
{
}

/**
*  @brief
*    Destructor
*/
XmlUnknown::~XmlUnknown()
{
}

/**
*  @brief
*    Copy operator
*/
XmlUnknown &XmlUnknown::operator =(const XmlUnknown &cSource)
{
	*((TiXmlUnknown*)m_pData) = (const TiXmlUnknown&)*((TiXmlUnknown*)cSource.m_pData);
	return *this;
}


//[-------------------------------------------------------]
//[ Public virtual XmlBase functions                      ]
//[-------------------------------------------------------]
bool XmlUnknown::Save(File &cFile, uint32 nDepth)
{
	// Get the number of empty spaces
	const XmlDocument *pDocument = GetDocument();
	uint32 nNumOfSpaces = (pDocument ? pDocument->GetTabSize() : 4) * nDepth;

	// Print empty spaces
	for (uint32 i=0; i<nNumOfSpaces; i++)
		cFile.PutC(' ');

	// Write value
	cFile.Print('<' + GetValue() + '>');

	// Done
	return true;
}

String XmlUnknown::ToString(uint32 nDepth)
{
	// Get the number of empty spaces
	const XmlDocument *pDocument = GetDocument();
	uint32 nNumOfSpaces = (pDocument ? pDocument->GetTabSize() : 4) * nDepth;

	// Print empty spaces
	String sXml;
	for (uint32 i=0; i<nNumOfSpaces; i++)
		sXml += ' ';

	// Write value
	sXml += '<' + GetValue() + '>';

	// Return the resulting string
	return sXml;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XmlUnknown::XmlUnknown(void *pNode, int nDummy) :
	XmlNode(pNode)
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
