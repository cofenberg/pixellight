/*********************************************************\
 *  File: PLSceneMaterialBakeShell.cpp                   *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Xml/Xml.h>
#include <IGame/IGame.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLScene.h"
#include "PL3dsMaxSceneExport/PLSceneMaterialBakeShell.h"


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
PLSceneMaterialBakeShell::PLSceneMaterialBakeShell(PLScene &cScene, IGameMaterial *pParentIGameMaterial, IGameMaterial &cIGameMaterial, const String &sName) :
	PLSceneMaterial(cScene, pParentIGameMaterial, &cIGameMaterial, sName)
{
}

/**
*  @brief
*    Destructor
*/
PLSceneMaterialBakeShell::~PLSceneMaterialBakeShell()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLSceneMaterial functions             ]
//[-------------------------------------------------------]
void PLSceneMaterialBakeShell::SaveParameters(XmlElement &cMaterialElement)
{
	// Get the 'backed' material
	IGameMaterial *pBackedIGameMaterial = m_pIGameMaterial->GetSubMaterial(1);
	if (pBackedIGameMaterial) {
		// Get the 3ds Max material... I don't use IGame for this because I didn't get it working using it...
		Mtl *pMaxMaterial = pBackedIGameMaterial->GetMaxMaterial();
		if (pMaxMaterial) {
			// See if it's a standard material
			StdMat *pMaxStandardMat = (pMaxMaterial->ClassID() == Class_ID(DMTL_CLASS_ID, 0)) ? static_cast<StdMat*>(pMaxMaterial) : nullptr;

			// Textures, do only take "Self-Illumination" into account...
			for (int nSlot=0; nSlot<pMaxMaterial->NumSubTexmaps(); nSlot++) {
				// If this is a standard material, is the map enabled?
				if (!pMaxStandardMat || pMaxStandardMat->MapEnabled(nSlot)) {
					// Get the texture
					Texmap *pTexMap = pMaxMaterial->GetSubTexmap(nSlot);
					if (pTexMap && pTexMap->ClassID() == Class_ID(BMTEX_CLASS_ID, 0)) {
						BitmapTex *pBitmapTex = static_cast<BitmapTex*>(pTexMap);
						const String sSlotName = pMaxMaterial->GetSubTexmapSlotName(nSlot);
						if (sSlotName.CompareNoCase("Self-Illumination")) {
							SaveTexture(cMaterialElement, pBitmapTex->GetMapName(), static_cast<const char*>(sSlotName));
							break;
						}
					}
				}
			}
		}
	} else {
		g_pLog->LogFLine(PLLog::Error, "Material '%s': Backed material is missing!", m_sName.GetASCII());
	}

	// Get the 'original' material
	IGameMaterial *pOriginalIGameMaterial = m_pIGameMaterial->GetSubMaterial(0);
	if (pOriginalIGameMaterial) {
		// Export the 'original' material
		PLSceneMaterial *pOriginalMaterial = m_pScene->AddMaterial(m_pParentIGameMaterial, *pOriginalIGameMaterial);
		if (pOriginalMaterial) {
			// Add the 'original' material to the written material
			XmlElement *pMaterialElement = new XmlElement("Material");

			// Add value
			XmlText *pValue = new XmlText(pOriginalMaterial->GetName());
			pMaterialElement->LinkEndChild(*pValue);

			// Link material element
			cMaterialElement.LinkEndChild(*pMaterialElement);
		}
	} else {
		g_pLog->LogFLine(PLLog::Error, "Material '%s': Original material is missing!", m_sName.GetASCII());
	}
}
