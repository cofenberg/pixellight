/*********************************************************\
 *  File: PostProcessLoaderPL.cpp                        *
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
#include <PLGeneral/Xml/Xml.h>
#include <PLGeneral/Log/Log.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Material/MaterialManager.h>
#include "PLCompositing/Shaders/PostProcessing/PostProcessManager.h"
#include "PLCompositing/Shaders/PostProcessing/PostProcessLoaderPL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(PostProcessLoaderPL)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool PostProcessLoaderPL::Load(PostProcessManager &cPostProcessManager, File &cFile)
{
	// Load XML document
	XmlDocument cDocument;
	if (cDocument.Load(cFile)) {
		// Get post process element
		const XmlElement *pPostProcessElement = cDocument.GetFirstChildElement("PostProcess");
		if (pPostProcessElement) {
			// Get the format version
			const int nVersion = pPostProcessElement->GetAttribute("Version").GetInt();

			// Unkown
			if (nVersion > 1) {
				PL_LOG(Error, cDocument.GetValue() + ": " + UnknownFormatVersion)

			// 1 (current)
			} else if (nVersion == 1) {
				return LoadV1(cPostProcessManager, *pPostProcessElement);

			// ""/0 (same format as 1)
			} else if (nVersion == 0) {
				// [DEPRECATED]
				PL_LOG(Warning, cDocument.GetValue() + ": " + DeprecatedFormatVersion)
				return LoadV1(cPostProcessManager, *pPostProcessElement);

			// No longer supported format version
			} else if (nVersion >= 0) {
				PL_LOG(Warning, cDocument.GetValue() + ": " + NoLongerSupportedFormatVersion)

			// Invalid format version (negative!)
			} else {
				PL_LOG(Error, cDocument.GetValue() + ": " + InvalidFormatVersion)
			}
		} else {
			PL_LOG(Error, "Can't find 'PostProcess' element")
		}
	} else {
		PL_LOG(Error, cDocument.GetValue() + ": " + cDocument.GetErrorDesc())
	}

	// Error!
	return false;
}

bool PostProcessLoaderPL::Save(PostProcessManager &cPostProcessManager, File &cFile)
{
	// Create XML document
	XmlDocument cDocument;

	// Add declaration
	XmlDeclaration *pDeclaration = new XmlDeclaration("1.0", "", "");
	cDocument.LinkEndChild(*pDeclaration);

	// Add post process
	XmlElement *pPostProcessElement = new XmlElement("PostProcess");
	pPostProcessElement->SetAttribute("Version", "1");

	// Add general information if required
	if (cPostProcessManager.GetTextureFormat() != TextureBuffer::R8G8B8A8) {
		XmlElement *pGeneralElement = new XmlElement("General");
		switch (cPostProcessManager.GetTextureFormat()) {
			case TextureBuffer::R8G8B8:
				pGeneralElement->SetAttribute("TextureFormat", "R8G8B8");
				break;

			case TextureBuffer::R16G16B16A16F:
				pGeneralElement->SetAttribute("TextureFormat", "R16G16B16A16F");
				break;

			case TextureBuffer::R32G32B32A32F:
				pGeneralElement->SetAttribute("TextureFormat", "R32G32B32A32F");
				break;
		}
		pPostProcessElement->LinkEndChild(*pGeneralElement);
	}

	// Add all post processes
	for (uint32 i=0; i<cPostProcessManager.GetNumOfElements(); i++) {
		const PostProcess *pPP = cPostProcessManager.Get(i);
		if (pPP) {
			XmlElement *pPassElement = new XmlElement("Pass");

			// Add material
			const Material *pMaterial = pPP->GetMaterial();
			if (pMaterial)
				pPassElement->SetAttribute("Material", pMaterial->GetName());

			// Link to pass element
			pPostProcessElement->LinkEndChild(*pPassElement);
		}
	}

	// Link post process element
	cDocument.LinkEndChild(*pPostProcessElement);
	
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
PostProcessLoaderPL::PostProcessLoaderPL() :
	MethodLoad(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
PostProcessLoaderPL::~PostProcessLoaderPL()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loader implementation for format version 1
*/
bool PostProcessLoaderPL::LoadV1(PostProcessManager &cPostProcessManager, const XmlElement &cPostProcessElement) const
{
	// Are there general settings?
	const XmlElement *pGeneralElement = cPostProcessElement.GetFirstChildElement("General");
	if (pGeneralElement) {
		// Texture buffer format
		TextureBuffer::EPixelFormat nTextureFormat = TextureBuffer::R8G8B8A8;
		String sTextureFormat = pGeneralElement->GetAttribute("TextureFormat");
		if (sTextureFormat.GetLength()) {
			if (sTextureFormat == "R8G8B8")
				nTextureFormat = TextureBuffer::R8G8B8;
			else if (sTextureFormat == "R8G8B8A8")
				nTextureFormat = TextureBuffer::R8G8B8A8;
			else if (sTextureFormat == "R16G16B16A16F")
				nTextureFormat = TextureBuffer::R16G16B16A16F;
			else if (sTextureFormat == "R32G32B32A32F")
				nTextureFormat = TextureBuffer::R32G32B32A32F;
		}
		cPostProcessManager.SetTextureFormat(nTextureFormat);
	}

	// Iterate through all passes
	const XmlElement *pPassElement = cPostProcessElement.GetFirstChildElement("Pass");
	while (pPassElement) {
		// Get optional material
		String sMaterial = pPassElement->GetAttribute("Material");

		// Create the post process
		PostProcess *pPP = new PostProcess("", cPostProcessManager);
		if (pPP) {
			pPP->SetMaterial(cPostProcessManager.GetRendererContext().GetMaterialManager().LoadResource(sMaterial));
			cPostProcessManager.Add(*pPP);
		}

		// Next element, please
		pPassElement = pPassElement->GetNextSiblingElement("Pass");
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
