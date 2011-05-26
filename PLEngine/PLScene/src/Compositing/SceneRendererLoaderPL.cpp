/*********************************************************\
 *  File: SceneRendererLoaderPL.cpp                      *
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
#include <PLCore/Base/Class.h>
#include "PLScene/Compositing/SceneRenderer.h"
#include "PLScene/Compositing/SceneRendererLoaderPL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SceneRendererLoaderPL)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool SceneRendererLoaderPL::Load(SceneRenderer &cSceneRenderer, File &cFile)
{
	// Load XML document
	XmlDocument cDocument;
	if (cDocument.Load(cFile)) {
		// Get scene renderer element
		const XmlElement *pSceneRendererElement = cDocument.GetFirstChildElement("SceneRenderer");
		if (pSceneRendererElement) {
			// Get the format version
			const int nVersion = pSceneRendererElement->GetAttribute("Version").GetInt();

			// Unkown
			if (nVersion > 1) {
				PL_LOG(Error, cDocument.GetValue() + ": " + UnknownFormatVersion)

			// 1 (current)
			} else if (nVersion == 1) {
				return LoadV1(cSceneRenderer, *pSceneRendererElement);

			// ""/0 (same format as 1)
			} else if (nVersion == 0) {
				// [DEPRECATED]
				PL_LOG(Warning, cDocument.GetValue() + ": " + DeprecatedFormatVersion)
				return LoadV1(cSceneRenderer, *pSceneRendererElement);

			// No longer supported format version
			} else if (nVersion >= 0) {
				PL_LOG(Warning, cDocument.GetValue() + ": " + NoLongerSupportedFormatVersion)

			// Invalid format version (negative!)
			} else {
				PL_LOG(Error, cDocument.GetValue() + ": " + InvalidFormatVersion)
			}
		} else {
			PL_LOG(Error, "Can't find 'SceneRenderer' element")
		}
	} else {
		PL_LOG(Error, cDocument.GetValue() + ": " + cDocument.GetErrorDesc())
	}

	// Error!
	return false;
}

bool SceneRendererLoaderPL::Save(SceneRenderer &cSceneRenderer, File &cFile)
{
	return SaveParams(cSceneRenderer, cFile, true);
}

bool SceneRendererLoaderPL::SaveParams(SceneRenderer &cSceneRenderer, File &cFile, bool bNoDefault)
{
	// Create XML document
	XmlDocument cDocument;

	// Add declaration
	XmlDeclaration *pDeclaration = new XmlDeclaration("1.0", "", "");
	cDocument.LinkEndChild(*pDeclaration);

	// Add scene renderer pass
	XmlElement *pSceneRendererElement = new XmlElement("SceneRenderer");
	pSceneRendererElement->SetAttribute("Version", "1");

	// Add all scene renderer passes
	for (uint32 i=0; i<cSceneRenderer.GetNumOfElements(); i++) {
		const SceneRendererPass *pSceneRendererPass = cSceneRenderer.Get(i);
		if (pSceneRendererPass) {
			XmlElement *pPassElement = new XmlElement("Pass");

			// Add class and parameters
			pPassElement->SetAttribute("Class", pSceneRendererPass->GetClass()->GetClassName());
			pSceneRendererPass->GetValuesXml(*pPassElement, bNoDefault ? NoDefault : WithDefault);

			// Link to pass element
			pSceneRendererElement->LinkEndChild(*pPassElement);
		}
	}

	// Link scene renderer element
	cDocument.LinkEndChild(*pSceneRendererElement);
	
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
SceneRendererLoaderPL::SceneRendererLoaderPL() :
	MethodLoad(this),
	MethodSave(this),
	MethodSaveParams(this)
{
}

/**
*  @brief
*    Destructor
*/
SceneRendererLoaderPL::~SceneRendererLoaderPL()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loader implementation for format version 1
*/
bool SceneRendererLoaderPL::LoadV1(SceneRenderer &cSceneRenderer, const XmlElement &cSceneRendererElement) const
{
	// Iterate through all passes
	const XmlElement *pPassElement = cSceneRendererElement.GetFirstChildElement("Pass");
	while (pPassElement) {
		// Get scene renderer pass class name
		const String sClass = pPassElement->GetAttribute("Class");
		if (sClass.GetLength()) {
			// Setup variables
			String sParameters, sName;
			const XmlAttribute *pAttribute = pPassElement->GetFirstAttribute();
			while (pAttribute) {
				// Is this the name?
				if (pAttribute->GetName() == "Name")
					sName = pAttribute->GetValue();

				// Add parameter
				sParameters += pAttribute->GetName();
				sParameters += "=\"";
				sParameters += pAttribute->GetValue();
				sParameters += "\" ";

				// Get the next attribute
				pAttribute = pAttribute->GetNext();
			}

			// Create scene renderer pass
			if (!cSceneRenderer.Create(sClass, sName, sParameters))
				PL_LOG(Error, pPassElement->GetValue() + ": Pass at row " + pPassElement->GetRow() + " column " + pPassElement->GetColumn() + " creation failed!")
		} else {
			PL_LOG(Error, pPassElement->GetValue() + ": Pass at row " + pPassElement->GetRow() + " column " + pPassElement->GetColumn() + " has no class name!")
		}

		// Next pass, please
		pPassElement = pPassElement->GetNextSiblingElement();
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
