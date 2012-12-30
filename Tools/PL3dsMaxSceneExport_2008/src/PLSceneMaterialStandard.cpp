/*********************************************************\
 *  File: PLSceneMaterialStandard.cpp                    *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <NormalBump/normalrender.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLScene.h"
#include "PL3dsMaxSceneExport/PLSceneMaterialStandard.h"


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
PLSceneMaterialStandard::PLSceneMaterialStandard(PLScene &cScene, IGameMaterial *pParentIGameMaterial, IGameMaterial &cIGameMaterial, const String &sName) :
	PLSceneMaterial(cScene, pParentIGameMaterial, &cIGameMaterial, sName)
{
}

/**
*  @brief
*    Destructor
*/
PLSceneMaterialStandard::~PLSceneMaterialStandard()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLSceneMaterial functions             ]
//[-------------------------------------------------------]
void PLSceneMaterialStandard::SaveParameters(XmlElement &cMaterialElement)
{
	// Get the 3ds Max material... I don't use IGame for this because I didn't get it working using it...
	Mtl *pMaxMaterial = m_pIGameMaterial->GetMaxMaterial();
	if (pMaxMaterial) {
		// Variables
		float fReflectionColor = 1.0f;

		// See if it's a standard material
		StdMat *pMaxStandardMat = (pMaxMaterial->ClassID() == Class_ID(DMTL_CLASS_ID, 0)) ? static_cast<StdMat*>(pMaxMaterial) : nullptr;

		// Textures
		for (int nSlot=0; nSlot<pMaxMaterial->NumSubTexmaps(); nSlot++) {
			// If this is a standard material, is the map enabled?
			if (!pMaxStandardMat || pMaxStandardMat->MapEnabled(nSlot)) {
				// Get the texture map
				Texmap *pTexMap = pMaxMaterial->GetSubTexmap(nSlot);
				if (pTexMap) {
					// Is this a "Bitmap" texture map?
					if (pTexMap->ClassID() == Class_ID(BMTEX_CLASS_ID, 0)) {
						const String sSlotName = pMaxMaterial->GetSubTexmapSlotName(nSlot);
						BitmapTex *pBitmapTex = static_cast<BitmapTex*>(pTexMap);
						if (sSlotName.GetLength())
							g_pLog->LogFLine(PLLog::Warning, "Material '%s': Slot '%d' (value: '%s') has no name!", m_sName.GetASCII(), nSlot, pBitmapTex->GetMapName());

						// Save the texture
						SaveTexture(cMaterialElement, pBitmapTex->GetMapName(), sSlotName);

						// Is this a reflection map?
						if (pMaxStandardMat && sSlotName.CompareNoCase("Reflection", 0, 10))
							fReflectionColor = pMaxStandardMat->GetTexmapAmt(nSlot, m_pScene->GetMaxInterface().GetTime());

					// Is this a "Normal Bump" texture map?
					} else if (pTexMap->ClassID() == GNORMAL_CLASS_ID) {
						Gnormal *pGnormal = static_cast<Gnormal*>(pTexMap);

						// [TODO] Write a warning into the log if 'Gnormal::method' is not 'TANGENTUV_SPACE'

						// [TODO] Only export if enabled
						// Get the 'Normal' bitmap
						Texmap *pNormalMap = pGnormal->GetSubTexmap(0);
						if (pNormalMap && pNormalMap->ClassID() == Class_ID(BMTEX_CLASS_ID, 0)) {
							// Save the texture
							SaveTexture(cMaterialElement, static_cast<BitmapTex*>(pNormalMap)->GetMapName(), "NormalMap");
						}

						// [TODO] Only export if enabled
						// Get the 'Bump' bitmap
						Texmap *pBumpMap = pGnormal->GetSubTexmap(1);
						if (pBumpMap && pBumpMap->ClassID() == Class_ID(BMTEX_CLASS_ID, 0)) {
							// Save the texture
							SaveTexture(cMaterialElement, static_cast<BitmapTex*>(pBumpMap)->GetMapName(), "HeightMap");

							// [TODO] Save 'weight' as 'parallax'
						}
					}
				}
			}
		}

		// See if it's a standard material
		if (pMaxStandardMat) {
			// Save two sided?
			bool bTwoSided = (pMaxStandardMat->GetTwoSided() != 0);
			if (bTwoSided || !g_SEOptions.bSmartMaterialParameters) {
				// Add to material
				XmlElement *pFloatElement = new XmlElement("Float");
				pFloatElement->SetAttribute("Name", "TwoSided");

				// Add value
				XmlText *pValue = new XmlText("1.0");
				pFloatElement->LinkEndChild(*pValue);

				// Link float element
				cMaterialElement.LinkEndChild(*pFloatElement);
			}

			// Save opacity?
			float fOpacity = pMaxStandardMat->GetOpacity(m_pScene->GetMaxInterface().GetTime());
			if (fOpacity != 1.0f || !g_SEOptions.bSmartMaterialParameters) {
				// Add to material
				XmlElement *pFloatElement = new XmlElement("Float");
				pFloatElement->SetAttribute("Name", "Opacity");

				{ // Add value
					XmlText *pValue = new XmlText(String::Format("%f", fOpacity));
					pFloatElement->LinkEndChild(*pValue);
				}

				// Link float element
				cMaterialElement.LinkEndChild(*pFloatElement);

				// Subtractive transparency?
				if (pMaxStandardMat->GetTransparencyType() == TRANSP_SUBTRACTIVE) {
					{ // SrcBlendFunc
						// Add to material
						XmlElement *pStringElement = new XmlElement("String");
						pStringElement->SetAttribute("Name", "SrcBlendFunc");

						// Add value
						XmlText *pValue = new XmlText("SrcAlpha");
						pStringElement->LinkEndChild(*pValue);

						// Link float element
						cMaterialElement.LinkEndChild(*pStringElement);
					}
					{ // DstBlendFunc
						// Add to material
						XmlElement *pStringElement = new XmlElement("String");
						pStringElement->SetAttribute("Name", "DstBlendFunc");

						// Add value
						XmlText *pValue = new XmlText("InvSrcAlpha");
						pStringElement->LinkEndChild(*pValue);

						// Link float element
						cMaterialElement.LinkEndChild(*pStringElement);
					}
				}
			}

			// Save diffuse color?
			Color cDiffuseColor = pMaxStandardMat->GetDiffuse(m_pScene->GetMaxInterface().GetTime());
			if (!g_SEOptions.bSmartMaterialParameters || cDiffuseColor.r != 1.0f || cDiffuseColor.g != 1.0f || cDiffuseColor.b != 1.0f) {
				// Add to material
				XmlElement *pFloat3Element = new XmlElement("Float3");
				pFloat3Element->SetAttribute("Name", "DiffuseColor");

				// Add value
				XmlText *pValue = new XmlText(String::Format("%f %f %f", cDiffuseColor.r, cDiffuseColor.g, cDiffuseColor.b));
				pFloat3Element->LinkEndChild(*pValue);

				// Link float element
				cMaterialElement.LinkEndChild(*pFloat3Element);
			}

			// Save specular exponent?
			float fSpecularExponent = pMaxStandardMat->GetShininess(m_pScene->GetMaxInterface().GetTime())*100;
			if (fSpecularExponent != 45.0f || !g_SEOptions.bSmartMaterialParameters) {
				// Add to material
				XmlElement *pFloatElement = new XmlElement("Float");
				pFloatElement->SetAttribute("Name", "SpecularExponent");

				// Add value
				XmlText *pValue = new XmlText(String::Format("%f", fSpecularExponent));
				pFloatElement->LinkEndChild(*pValue);

				// Link float element
				cMaterialElement.LinkEndChild(*pFloatElement);
			}

			// Save specular color?
			Color cSpecularColor = pMaxStandardMat->GetSpecular(m_pScene->GetMaxInterface().GetTime());
			cSpecularColor *= pMaxStandardMat->GetShinStr(m_pScene->GetMaxInterface().GetTime());
			if (!g_SEOptions.bSmartMaterialParameters || cSpecularColor.r != 1.0f || cSpecularColor.g != 1.0f || cSpecularColor.b != 1.0f) {
				// Add to material
				XmlElement *pFloat3Element = new XmlElement("Float3");
				pFloat3Element->SetAttribute("Name", "SpecularColor");

				// Add value
				XmlText *pValue = new XmlText(String::Format("%f %f %f", cSpecularColor.r, cSpecularColor.g, cSpecularColor.b));
				pFloat3Element->LinkEndChild(*pValue);

				// Link float element
				cMaterialElement.LinkEndChild(*pFloat3Element);
			}

			// Save index of refraction
			const float fIndexOfRefraction = pMaxStandardMat->GetIOR(m_pScene->GetMaxInterface().GetTime());
			if (fIndexOfRefraction || !g_SEOptions.bSmartMaterialParameters) {
				// Add to material
				XmlElement *pFloatElement = new XmlElement("Float");
				pFloatElement->SetAttribute("Name", "IndexOfRefraction");

				// Add value
				XmlText *pValue = new XmlText(String::Format("%f", fIndexOfRefraction));
				pFloatElement->LinkEndChild(*pValue);

				// Link float element
				cMaterialElement.LinkEndChild(*pFloatElement);
			}
		}

		// Save reflection color?
		if (fReflectionColor != 1.0f || !g_SEOptions.bSmartMaterialParameters) {
			// Add to material
			XmlElement *pFloat3Element = new XmlElement("Float3");
			pFloat3Element->SetAttribute("Name", "fReflectionColor");

			// Add value
			XmlText *pValue = new XmlText(String::Format("%f %f %f", fReflectionColor, fReflectionColor, fReflectionColor));
			pFloat3Element->LinkEndChild(*pValue);

			// Link float element
			cMaterialElement.LinkEndChild(*pFloat3Element);
		}
	}
}
