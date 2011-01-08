/*********************************************************\
 *  File: PLSceneMaterial.cpp                            *
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
#include <PLGeneral/File/Url.h>
#include <PLGeneral/File/Directory.h>
#include <IGame/IGame.h>
#include <IGame/IGameFX.h>
#include <iparamb2.h>
#include <pbbitmap.h>
#include <IDxMaterial.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLTools.h"
#include "PL3dsMaxSceneExport/PLScene.h"
#include "PL3dsMaxSceneExport/PLSceneTexture.h"
#include "PL3dsMaxSceneExport/PLSceneMaterialFX.h"
#include "PL3dsMaxSceneExport/PLSceneExportOptions.h"
#include "PL3dsMaxSceneExport/PLSceneMaterialStandard.h"
#include "PL3dsMaxSceneExport/PLSceneMaterialBakeShell.h"
#include "PL3dsMaxSceneExport/PLSceneMaterialSRShaderLighting.h"
#include "PL3dsMaxSceneExport/PLSceneMaterial.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the IGame material this material comes from
*/
IGameMaterial *PLSceneMaterial::GetIGameMaterial() const
{
	return m_pIGameMaterial;
}

/**
*  @brief
*    Returns the material name
*/
const std::string &PLSceneMaterial::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Returns the reference count of this material
*/
unsigned int PLSceneMaterial::GetReferenceCount() const
{
	return m_nReferenceCount;
}

/**
*  @brief
*    Saves the material
*/
bool PLSceneMaterial::Save(const std::string &sApplicationDrive, const std::string &sApplicationDir)
{
	// Create XML document
	XmlDocument cDocument;

	// Add declaration
	XmlDeclaration *pDeclaration = new XmlDeclaration("1.0", "ISO-8859-1", "");
	cDocument.LinkEndChild(*pDeclaration);

	// Add material
	XmlElement *pMaterialElement = new XmlElement("Material");
	pMaterialElement->SetAttribute("Version", "1");

	// Save the parameters
	SaveParameters(*pMaterialElement);

	// Link material element
	cDocument.LinkEndChild(*pMaterialElement);

	// Get the absolute material filename
	std::string sFilename;
	if (g_SEOptions.bPLDirectories)
		sFilename = sApplicationDrive + sApplicationDir + "Data\\Materials\\" + m_sName;
	else
		sFilename = sApplicationDrive + sApplicationDir + m_sName;

	{ // Before we safe, we need to ensure that the target directory is there, else 'Save()' will fail!
		Url cUrl = sFilename.c_str();
		Directory cDirectory(cUrl.CutFilename());
		cDirectory.CreateRecursive();
	}

	// Save settings
	cDocument.Save(sFilename.c_str());

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PLSceneMaterial::PLSceneMaterial(PLScene &cScene, IGameMaterial *pParentIGameMaterial, IGameMaterial *pIGameMaterial, const std::string &sName) :
	m_pScene(&cScene),
	m_pParentIGameMaterial(pParentIGameMaterial),
	m_pIGameMaterial(pIGameMaterial),
	m_sName(sName),
	m_nReferenceCount(0)
{
}

/**
*  @brief
*    Destructor
*/
PLSceneMaterial::~PLSceneMaterial()
{
}

/**
*  @brief
*    Saves a texture
*/
void PLSceneMaterial::SaveTexture(XmlElement &cMaterialElement, const std::string &sFilename, const std::string &sSemantic, bool bNormalMap_xGxR)
{
	// Get known semantic
	String sPLSemantic = sSemantic.c_str();
	if (sPLSemantic.CompareNoCase("Ambient Color", 0, 13) || sPLSemantic.CompareNoCase("EmissiveMap", 0, 11))
		sPLSemantic = "EmissiveMap";
	else if (sPLSemantic.CompareNoCase("Diffuse Color", 0, 13) || sPLSemantic.CompareNoCase("DiffuseMap", 0, 10))
		sPLSemantic = "DiffuseMap";
	else if (sPLSemantic.CompareNoCase("Specular Color", 0, 14) || sPLSemantic.CompareNoCase("SpecularMap", 0, 11))
		sPLSemantic = "SpecularMap";
	else if (sPLSemantic.CompareNoCase("Self-Illumination", 0, 17) || sPLSemantic.CompareNoCase("LightMap", 0, 8))
		sPLSemantic = "LightMap";
	else if (sPLSemantic.CompareNoCase("Filter Color", 0, 12) || sPLSemantic.CompareNoCase("DetailNormalMap", 0, 15))
		sPLSemantic = "DetailNormalMap";
	else if (sPLSemantic.CompareNoCase("Bump", 0, 4) || sPLSemantic.CompareNoCase("NormalMap", 0, 9))
		sPLSemantic = "NormalMap";
	else if (sPLSemantic.CompareNoCase("Reflection", 0, 10) || sPLSemantic.CompareNoCase("ReflectionMap", 0, 13))
		sPLSemantic = "ReflectionMap";
	else if (sPLSemantic.CompareNoCase("Refraction", 0, 10) || sPLSemantic.CompareNoCase("ReflectivityMap", 0, 15))
		sPLSemantic = "ReflectivityMap";
	else if (sPLSemantic.CompareNoCase("Displacement", 0, 13) ||sPLSemantic.CompareNoCase("HeightMap", 0, 9))
		sPLSemantic = "HeightMap";
	else {
		// Unknown to the exporter - just export it anyway so we don't loose important information
	}

	// Copy texture if there's a known semantic
	if (sPLSemantic.GetLength()) {
		PLSceneTexture *pTexture = m_pScene->CopyTexture(sFilename, bNormalMap_xGxR);
		if (pTexture) {
			// Add to material
			XmlElement *pTextureElement = new XmlElement("Texture");
			pTextureElement->SetAttribute("Name", sPLSemantic);

			// Add value
			XmlText *pValue = new XmlText(pTexture->GetName().c_str());
			pTextureElement->LinkEndChild(*pValue);

			// Link texture element
			cMaterialElement.LinkEndChild(*pTextureElement);
		}
	}
}


//[-------------------------------------------------------]
//[ Private static functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Creates a material
*/
PLSceneMaterial *PLSceneMaterial::Create(PLScene &cScene, IGameMaterial *pParentIGameMaterial, IGameMaterial &cIGameMaterial, const std::string &sName)
{
	// Get the 3ds Max material... I don't use IGame for this because I didn't get it working using it...
	Mtl *pMaxMaterial = cIGameMaterial.GetMaxMaterial();
	if (pMaxMaterial) {
		// DxMaterial or extend?
		IDxMaterial2 *pFXMaterial = (IDxMaterial2*)pMaxMaterial->GetInterface(IDXMATERIAL2_INTERFACE);
		if (!pFXMaterial && pParentIGameMaterial)
			pFXMaterial = (IDxMaterial2*)pParentIGameMaterial->GetMaxMaterial()->GetInterface(IDXMATERIAL2_INTERFACE);
		if (pFXMaterial) { // Get information from the DirectX Shader material
			// Get effect filename
		#if MAX_RELEASE >= 12000	// For R12 release
			Url cUrl = pFXMaterial->GetEffectFile().GetFullFilePath().data();
		#else
			Url cUrl = pFXMaterial->GetEffectFilename();
		#endif
			std::string sEffectFilenameName = cUrl.GetFilename();

			// Our effect?
			if (sEffectFilenameName == "PixelLight_SRShaderLighting.fx")
				return new PLSceneMaterialSRShaderLighting(cScene, pParentIGameMaterial, cIGameMaterial, sName);
			else
				return new PLSceneMaterialFX(cScene, pParentIGameMaterial, cIGameMaterial, sName);
		} else {
			// Is this a shell material used for 'backed texture'?
			if (pMaxMaterial->ClassID() == Class_ID(BAKE_SHELL_CLASS_ID, 0))
				return new PLSceneMaterialBakeShell(cScene, pParentIGameMaterial, cIGameMaterial, sName);
			else
				return new PLSceneMaterialStandard(cScene, pParentIGameMaterial, cIGameMaterial, sName);
		}
	}

	// Error!
	return nullptr;
}
