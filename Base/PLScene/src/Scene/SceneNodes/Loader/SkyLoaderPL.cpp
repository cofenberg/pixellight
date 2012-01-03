/*********************************************************\
 *  File: SkyLoaderPL.cpp                                *
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
#include <PLCore/Log/Log.h>
#include <PLRenderer/Material/Material.h>
#include <PLMesh/MeshHandler.h>
#include "PLScene/Scene/SceneNodes/SNSky.h"
#include "PLScene/Scene/SceneNodes/Loader/SkyLoaderPL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SkyLoaderPL)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool SkyLoaderPL::Load(SNSky &cSky, File &cFile)
{
	// Load XML document
	XmlDocument cDocument;
	if (cDocument.Load(cFile)) {
		// Get sky element
		const XmlElement *pSkyElement = cDocument.GetFirstChildElement("Sky");
		if (pSkyElement) {
			// Get the format version
			const int nVersion = pSkyElement->GetAttribute("Version").GetInt();

			// Unknown
			if (nVersion > 1) {
				PL_LOG(Error, cDocument.GetValue() + ": " + UnknownFormatVersion)

			// 1 (current)
			} else if (nVersion == 1) {
				return LoadV1(cSky, *pSkyElement);

			// ""/0 (same format as 1)
			} else if (nVersion == 0) {
				// [DEPRECATED]
				PL_LOG(Warning, cDocument.GetValue() + ": " + DeprecatedFormatVersion)
				return LoadV1(cSky, *pSkyElement);

			// No longer supported format version
			} else if (nVersion >= 0) {
				PL_LOG(Warning, cDocument.GetValue() + ": " + NoLongerSupportedFormatVersion)

			// Invalid format version (negative!)
			} else {
				PL_LOG(Error, cDocument.GetValue() + ": " + InvalidFormatVersion)
			}
		} else {
			PL_LOG(Error, "Can't find 'Sky' element")
		}
	} else {
		PL_LOG(Error, cDocument.GetValue() + ": " + cDocument.GetErrorDesc())
	}

	// Error!
	return false;
}

bool SkyLoaderPL::Save(SNSky &cSky, File &cFile)
{
	// Create XML document
	XmlDocument cDocument;

	// Add declaration
	XmlDeclaration *pDeclaration = new XmlDeclaration("1.0", "", "");
	cDocument.LinkEndChild(*pDeclaration);

	// Add sky
	XmlElement *pSkyElement = new XmlElement("Sky");
	pSkyElement->SetAttribute("Version", "1");

	// Loop through all layers
	for (uint32 nLayer=0; nLayer<cSky.GetNumOfElements(); nLayer++) {
		// Get the layer
		const SkyLayer *pSkyLayer = cSky.GetByIndex(nLayer);
		if (pSkyLayer) {
			// Create the layer element
			XmlElement *pLayerElement = new XmlElement("Layer");

			// Populate the XML parameters element
			pSkyLayer->GetValuesXml(*pLayerElement);

			// Loop through all materials of the layer
			const PLMesh::MeshHandler *pMeshHandler = pSkyLayer->GetMeshHandler();
			if (pMeshHandler) {
				for (uint32 nMaterial=0; nMaterial<pMeshHandler->GetNumOfMaterials(); nMaterial++) {
					// Get the material
					const PLRenderer::Material *pMaterial = pMeshHandler->GetMaterial(nMaterial);
					if (pMaterial) {
						// Create the material element
						XmlElement *pMaterialElement = new XmlElement("Material");

						// Set the attributes
						pMaterialElement->SetAttribute("ID",   String::Format("%d", nMaterial));
						pMaterialElement->SetAttribute("Name", pMaterial->GetName());

						// Link material element
						pLayerElement->LinkEndChild(*pMaterialElement);
					}
				}
			}

			// Link layer element
			pSkyElement->LinkEndChild(*pLayerElement);
		}
	}

	// Link sky element
	cDocument.LinkEndChild(*pSkyElement);

	// Save settings
	cDocument.Save(cFile);

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SkyLoaderPL::SkyLoaderPL()
{
}

/**
*  @brief
*    Destructor
*/
SkyLoaderPL::~SkyLoaderPL()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loader implementation for format version 1
*/
bool SkyLoaderPL::LoadV1(SNSky &cSky, const XmlElement &cSkyElement) const
{
	// Iterate through all layers
	const XmlElement *pLayerElement = cSkyElement.GetFirstChildElement("Layer");
	while (pLayerElement) {
		// Get optional sky layer name
		const String sLayerName = pLayerElement->GetAttribute("Name");

		// Create the sky layer
		SkyLayer *pSkyLayer = cSky.Create(sLayerName);
		if (pSkyLayer) {
			// Set variables
			pSkyLayer->SetValuesXml(*pLayerElement);

			// Iterate through all materials
			const XmlElement *pMaterialElement = pLayerElement->GetFirstChildElement("Material");
			while (pMaterialElement) {
				// Get optional material ID
				const int nID = pMaterialElement->GetAttribute("ID").GetInt();

				// Get and load material
				const String sMaterialName = pMaterialElement->GetAttribute("Name");
				if (sMaterialName.GetLength())
					pSkyLayer->LoadMaterial(sMaterialName, nID);

				// Next element, please
				pMaterialElement = pMaterialElement->GetNextSiblingElement("Material");
			}
		}

		// Next element, please
		pLayerElement = pLayerElement->GetNextSiblingElement("Layer");
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
