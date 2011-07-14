/*********************************************************\
 *  File: MaterialLoaderPL.cpp                           *
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
#include <PLGeneral/Xml/Xml.h>
#include <PLGeneral/Log/Log.h>
#include "PLRenderer/RendererContext.h"
#include "PLRenderer/Effect/EffectManager.h"
#include "PLRenderer/Material/MaterialManager.h"
#include "PLRenderer/Material/ParameterManager.h"
#include "PLRenderer/Material/MaterialLoaderPL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(MaterialLoaderPL)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool MaterialLoaderPL::Load(Material &cMaterial, File &cFile)
{
	// Load XML document
	XmlDocument cDocument;
	if (cDocument.Load(cFile)) {
		// Get material element
		const XmlElement *pMaterialElement = cDocument.GetFirstChildElement("Material");
		if (pMaterialElement) {
			// Get the format version
			const int nVersion = pMaterialElement->GetAttribute("Version").GetInt();

			// Unkown
			if (nVersion > 1) {
				PL_LOG(Error, cDocument.GetValue() + ": " + UnknownFormatVersion)

			// 1 (current)
			} else if (nVersion == 1) {
				return LoadV1(cMaterial, *pMaterialElement);

			// ""/0 (same format as 1)
			} else if (nVersion == 0) {
				// [DEPRECATED]
				PL_LOG(Warning, cDocument.GetValue() + ": " + DeprecatedFormatVersion)
				return LoadV1(cMaterial, *pMaterialElement);

			// No longer supported format version
			} else if (nVersion >= 0) {
				PL_LOG(Warning, cDocument.GetValue() + ": " + NoLongerSupportedFormatVersion)

			// Invalid format version (negative!)
			} else {
				PL_LOG(Error, cDocument.GetValue() + ": " + InvalidFormatVersion)
			}
		} else {
			PL_LOG(Error, "Can't find 'Material' element")
		}
	} else {
		PL_LOG(Error, cDocument.GetValue() + ": " + cDocument.GetErrorDesc())
	}

	// Error!
	return false;
}

bool MaterialLoaderPL::Save(const Material &cMaterial, File &cFile)
{
	// Create XML document
	XmlDocument cDocument;

	// Add declaration
	XmlDeclaration *pDeclaration = new XmlDeclaration("1.0", "", "");
	cDocument.LinkEndChild(*pDeclaration);

	// Add material
	XmlElement *pMaterialElement = new XmlElement("Material");
	pMaterialElement->SetAttribute("Version", "1");

	// Save parameters
	if (cMaterial.GetParameterManager().GetNumOfParameters())
		cMaterial.GetParameterManager().AddParametersToXMLElement(*pMaterialElement);

	// Save materials
	for (uint32 i=0; i<cMaterial.GetNumOfMaterials(); i++) {
		Material *pMaterial = cMaterial.GetMaterial(i);
		if (pMaterial) {
			XmlElement *pElement = new XmlElement("Material");

			// Add value
			XmlText *pValue = new XmlText(pMaterial->GetFilename());
			pElement->LinkEndChild(*pValue);

			// Link effect element
			pMaterialElement->LinkEndChild(*pElement);
		}
	}

	// Add effect
	const Effect *pFX = cMaterial.GetEffect();
	if (pFX) {
		XmlElement *pFXElement = new XmlElement("Effect");

		// Add value
		XmlText *pValue = new XmlText(pFX->GetName());
		pFXElement->LinkEndChild(*pValue);

		// Link effect element
		pMaterialElement->LinkEndChild(*pFXElement);
	}

	// Link material element
	cDocument.LinkEndChild(*pMaterialElement);

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
MaterialLoaderPL::MaterialLoaderPL()
{
}

/**
*  @brief
*    Destructor
*/
MaterialLoaderPL::~MaterialLoaderPL()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loader implementation for format version 1
*/
bool MaterialLoaderPL::LoadV1(Material &cMaterial, const XmlElement &cMaterialElement) const
{
	// Iterate through all elements
	const XmlElement *pElement = cMaterialElement.GetFirstChildElement();
	while (pElement) {
		// Is it a parameter?
		if (!cMaterial.GetParameterManager().AddParameterFromXMLElement(*pElement)) {
			String sValue = pElement->GetValue();

			// Is it a material?
			if (sValue == "Material") {
				// Get value, if there's one
				const XmlNode *pValue = pElement->GetFirstChild();
				if (pValue && pValue->GetType() == XmlNode::Text) {
					sValue = pValue->GetValue();
					if (sValue.GetLength()) {
						Material *pMaterial = cMaterial.GetMaterialManager().LoadResource(sValue);
						if (pMaterial)
							cMaterial.AddMaterial(*pMaterial);
					}
				}

			// Is it an effect?
			} else if (sValue == "Effect") {
				// Is there already an effect?
				const Effect *pFX = cMaterial.GetEffect();
				if (!pFX) {
					// Get value, if there's one
					const XmlNode *pValue = pElement->GetFirstChild();
					if (pValue && pValue->GetType() == XmlNode::Text) {
						sValue = pValue->GetValue();
						if (sValue.GetLength())
							cMaterial.SetEffect(cMaterial.GetMaterialManager().GetRendererContext().GetEffectManager().LoadResource(sValue));
					}
				}
			}
		}

		// Next element, please
		pElement = pElement->GetNextSiblingElement();
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
