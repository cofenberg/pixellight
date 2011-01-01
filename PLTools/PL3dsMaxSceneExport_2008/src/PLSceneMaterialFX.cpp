/*********************************************************\
 *  File: PLSceneMaterialFX.cpp                          *
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
#include <IGame/IGame.h>
#include <IGame/IGameFX.h>
#include <iparamb2.h>
#include <pbbitmap.h>
#include <IDxMaterial.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLScene.h"
#include "PL3dsMaxSceneExport/PLSceneMaterialFX.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PLSceneMaterialFX::PLSceneMaterialFX(PLScene &cScene, IGameMaterial *pParentIGameMaterial, IGameMaterial &cIGameMaterial, const std::string &sName) :
	PLSceneMaterial(cScene, pParentIGameMaterial, &cIGameMaterial, sName)
{
}

/**
*  @brief
*    Destructor
*/
PLSceneMaterialFX::~PLSceneMaterialFX()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLSceneMaterial functions             ]
//[-------------------------------------------------------]
void PLSceneMaterialFX::SaveParameters(XmlElement &cMaterialElement)
{
	// Get the 3ds Max material... I don't use IGame for this because I didn't get it working using it...
	Mtl *pMaxMaterial = m_pIGameMaterial->GetMaxMaterial();
	if (pMaxMaterial) {
		// DxMaterial or extend?
		IDxMaterial2 *pFXMaterial = (IDxMaterial2*)m_pIGameMaterial->GetMaxMaterial()->GetInterface(IDXMATERIAL2_INTERFACE);
		if (!pFXMaterial && m_pParentIGameMaterial)
			pFXMaterial = (IDxMaterial2*)m_pParentIGameMaterial->GetMaxMaterial()->GetInterface(IDXMATERIAL2_INTERFACE);
		if (pFXMaterial) { // Get information from the DirectX Shader material
			// Get number of bitmaps used
			int nNumOfBitmaps = pFXMaterial->GetNumberOfEffectBitmaps();

			// Write textures/bitmaps
			for (int i=0; i<nNumOfBitmaps; i++) {
				PBBitmap *pBitmap = pFXMaterial->GetEffectBitmap(i);
				if (pBitmap) {
					BitmapInfo &cBInfo = pBitmap->bi;
					const char *pszName = (const char*)cBInfo.Name();
					if (pszName && _stricmp(pszName, "None")) {
						std::string sSemantic;
						switch (pFXMaterial->GetBitmapUsage(i)) {
							case IDxMaterial2::UNKNOWN_MAP:
								sSemantic = "EmissiveMap";
								break;

							case IDxMaterial2::DIFFUSE_MAP:
								sSemantic = "DiffuseMap";
								break;

							case IDxMaterial2::BUMP_MAP:
								sSemantic = "HeightMap";
								break;

							case IDxMaterial2::SPECULAR_MAP:
								sSemantic = "SpecularMap";
								break;

							case IDxMaterial2::DISPLACEMENT_MAP:
								sSemantic = "DetailNormalMap";
								break;

							case IDxMaterial2::LIGHTMAP_MAP:
								sSemantic = "LightMap";
								break;

							case IDxMaterial2::NORMAL_MAP:
								sSemantic = "NormalMap";
								break;

							case IDxMaterial2::REFLECTION_MAP:
								sSemantic = "ReflectionMap";
								break;
						}
						if (sSemantic.length())
							SaveTexture(cMaterialElement, pszName, sSemantic);
					}
				}
			}
		}
	}
}
