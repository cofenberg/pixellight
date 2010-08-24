/*********************************************************\
 *  File: XmlComment.cpp                                 *
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
#include "PLGeneral/Xml/XmlComment.h"


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
XmlComment::XmlComment() :
	XmlNode(new TiXmlComment())
{
}

/**
*  @brief
*    Copy constructor
*/
XmlComment::XmlComment(const XmlComment &cSource) :
	XmlNode(new TiXmlComment(*(TiXmlComment*)cSource.m_pData))
{
}

/**
*  @brief
*    Destructor
*/
XmlComment::~XmlComment()
{
}

/**
*  @brief
*    Copy operator
*/
XmlComment &XmlComment::operator =(const XmlComment &cSource)
{
	*((TiXmlComment*)m_pData) = (const TiXmlComment&)*((TiXmlComment*)cSource.m_pData);
	return *this;
}


//[-------------------------------------------------------]
//[ Public virtual XmlBase functions                      ]
//[-------------------------------------------------------]
bool XmlComment::Save(File &cFile, uint32 nDepth)
{
	// Get the number of empty spaces
	const XmlDocument *pDocument = GetDocument();
	uint32 nNumOfSpaces = (pDocument ? pDocument->GetTabSize() : 4) * nDepth;

	// Print empty spaces
	for (uint32 i=0; i<nNumOfSpaces; i++)
		cFile.PutC(' ');

	// Write value
	cFile.Print("<!--" + GetValue() + "-->");

	// Done
	return true;
}

String XmlComment::ToString(uint32 nDepth)
{
	// Get the number of empty spaces
	const XmlDocument *pDocument = GetDocument();
	uint32 nNumOfSpaces = (pDocument ? pDocument->GetTabSize() : 4) * nDepth;

	// Print empty spaces
	String sXml;
	for (uint32 i=0; i<nNumOfSpaces; i++)
		sXml += ' ';

	// Write value
	sXml += "<!--" + GetValue() + "-->";

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
XmlComment::XmlComment(void *pNode, int nDummy) :
	XmlNode(pNode)
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
