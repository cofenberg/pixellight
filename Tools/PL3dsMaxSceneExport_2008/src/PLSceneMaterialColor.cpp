/*********************************************************\
 *  File: PLSceneMaterialColor.cpp                       *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLCore/Xml/Xml.h>
#include "PL3dsMaxSceneExport/PLSceneMaterialColor.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PLSceneMaterialColor::PLSceneMaterialColor(PLScene &cScene, const Color &cColor, const std::string &sName) :
	PLSceneMaterial(cScene, nullptr, nullptr, sName),
	m_cColor(cColor)
{
}

/**
*  @brief
*    Destructor
*/
PLSceneMaterialColor::~PLSceneMaterialColor()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLSceneMaterial functions             ]
//[-------------------------------------------------------]
void PLSceneMaterialColor::SaveParameters(XmlElement &cMaterialElement)
{
	// Add to material
	XmlElement *pFloat3Element = new XmlElement("Float3");
	pFloat3Element->SetAttribute("Name", "DiffuseColor");

	// Add value
	XmlText *pValue = new XmlText(String::Format("%f %f %f", m_cColor.r, m_cColor.g, m_cColor.b));
	pFloat3Element->LinkEndChild(*pValue);

	// Link float element
	cMaterialElement.LinkEndChild(*pFloat3Element);
}
