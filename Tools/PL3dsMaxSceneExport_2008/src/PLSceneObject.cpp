/*********************************************************\
 *  File: PLSceneObject.cpp                              *
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
#include <morpher/wm3.h>
#include <IGame/IGame.h>
#include "PL3dsMaxSceneExport/PLSceneExportOptions.h"
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLScene.h"
#include "PL3dsMaxSceneExport/PLSceneMesh.h"
#include "PL3dsMaxSceneExport/PLSceneMaterial.h"
#include "PL3dsMaxSceneExport/PLSceneObject.h"


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
PLSceneObject::PLSceneObject(PLSceneContainer &cContainer, IGameNode &cIGameNode, const std::string &sName, PLSceneMesh *pMesh) :
	PLSceneNode(&cContainer, &cIGameNode, sName, TypeObject, "PLScene::SNMesh"),
	m_pMesh(pMesh)
{
	// Get the 3ds Max node - some settings like 'ReceiveShadows' can't be requested using IGame
	INode *p3dsMaxNode = cIGameNode.GetMaxNode();
	if (p3dsMaxNode) {
		// Cast shadow
		if (p3dsMaxNode->CastShadows())
			AddFlag("CastShadow");

		// Receive shadow
		if (p3dsMaxNode->RcvShadows())
			AddFlag("ReceiveShadow");
	}
}

/**
*  @brief
*    Destructor
*/
PLSceneObject::~PLSceneObject()
{
}

/**
*  @brief
*    Returns the mesh this object is using
*/
PLSceneMesh *PLSceneObject::GetMesh() const
{
	return m_pMesh;
}


//[-------------------------------------------------------]
//[ Private virtual PLSceneNode functions                 ]
//[-------------------------------------------------------]
void PLSceneObject::WriteToFile(XmlElement &cSceneElement, const std::string &sApplicationDrive, const std::string &sApplicationDir)
{
	// Add scene node
	XmlElement *pNodeElement = new XmlElement("Node");
	pNodeElement->SetAttribute("Class", GetClassName().c_str());
	pNodeElement->SetAttribute("Name",  GetName().c_str());

	// Mesh filename
	if (m_pMesh) {
		if (g_SEOptions.bPLDirectories && g_SEOptions.bSubDirectories)
			pNodeElement->SetAttribute("Mesh", String::Format("Data\\Meshes\\%s\\%s.mesh", g_SEOptions.sFilenameOnly.c_str(), m_pMesh->GetName().c_str()));
		else
			pNodeElement->SetAttribute("Mesh", String::Format("Data\\Meshes\\%s.mesh", m_pMesh->GetName().c_str()));
	}

	// Write position, rotation, scale, bounding box and flags
	WriteToFilePosRotScaleBoxFlags(*pNodeElement);

	// Write flexible variables
	WriteVariables(*pNodeElement);

	// Is this an instance using another material? (if so, we need to map materials using a 'skin'-file)
	if (m_pMesh && (&m_pMesh->GetIGameNode() != GetIGameNode() && GetIGameNode()->GetNodeMaterial()) &&
		m_pMesh->GetIGameNode().GetNodeMaterial() != GetIGameNode()->GetNodeMaterial()) {
		// Get the IGameMaterial of the current node
		IGameMaterial *pIGameMaterial = GetIGameNode()->GetNodeMaterial();
		if (pIGameMaterial->IsMultiType() && pIGameMaterial->GetMaxMaterial() &&
			m_pMesh->GetIGameNode().GetNodeMaterial()->GetMaxMaterial()) {
			// Get the 3ds Max materials from the mesh and the current node
			Mtl *pMaxMeshMaterial = m_pMesh->GetIGameNode().GetNodeMaterial()->GetMaxMaterial();
			Mtl *pMaxNodeMaterial = pIGameMaterial->GetMaxMaterial();

			// We need a skin 'mapping' multiple materials from the mesh to the current node

			// 'Usually' both materials must have the same number of sub-materials
			if (pMaxMeshMaterial->NumSubMtls() != pMaxNodeMaterial->NumSubMtls()) {
				// [TODO] Handle this situation!?
				int i = 0;
			} else {
				// Add the multimaterial to get no name conflicts
				PLSceneMaterial *pMaterial = GetScene().AddMaterial(nullptr, *pIGameMaterial);
				if (pMaterial && pMaterial->GetIGameMaterial() && pMaterial->GetIGameMaterial()->GetMaterialName()) {
					// Create XML document
					XmlDocument cDocument;

					// Add declaration
					XmlDeclaration *pDeclaration = new XmlDeclaration("1.0", "ISO-8859-1", "");
					cDocument.LinkEndChild(*pDeclaration);

					// Add skin
					XmlElement *pSkinElement = new XmlElement("Skin");

					// Setup attributes
					pSkinElement->SetAttribute("Version", "1");

					// Loop through all sub-materials
					for (int nSubMaterial=0; nSubMaterial<pMaxMeshMaterial->NumSubMtls(); nSubMaterial++) {
						// Get 3ds Max materials
						Mtl *pMaxMeshSubMaterial = pMaxMeshMaterial->GetSubMtl(nSubMaterial);
						Mtl *pMaxNodeSubMaterial = pMaxNodeMaterial->GetSubMtl(nSubMaterial);
						if (pMaxMeshSubMaterial && pMaxNodeSubMaterial) {
							// Get PixelLight material coresponding to the mesh material
							PLSceneMaterial *pMeshSubMaterial = GetScene().GetMaterial(*pMaxMeshSubMaterial);
							if (pMeshSubMaterial) {
								// Get the IGameMaterial material encapsulating the current 3ds Max node material
								IGameMaterial *pIGameNodeMaterial = GetScene().GetIGameInterface().GetIGameMaterial(pMaxNodeSubMaterial);
								if (pIGameNodeMaterial) {
									// Add the material
									PLSceneMaterial *pSubMaterial = GetScene().AddMaterial(nullptr, *pIGameNodeMaterial);
									if (pSubMaterial) {
										// Add material
										XmlElement *pSubMaterialElement = new XmlElement("Material");
										pSubMaterialElement->SetAttribute("Name", (std::string("Data\\Materials\\") + pMeshSubMaterial->GetName()).c_str());

										// Add value
										std::string sMaterialFilename(pSubMaterial->GetName());
										if (sMaterialFilename.find(".mat") != std::string::npos)
											sMaterialFilename = "Data\\Materials\\" + sMaterialFilename;
										XmlText *pValue = new XmlText(sMaterialFilename.c_str());
										pSubMaterialElement->LinkEndChild(*pValue);

										// Link general element
										pSkinElement->LinkEndChild(*pSubMaterialElement);
									} else {
										// [TODO] Handle this situation!?
										int i = 0;
									}
								}
							} else {
								// [TODO] Handle this situation!?
								int i = 0;
							}
						} else {
							// [TODO] Handle this situation!?
							int i = 0;
						}
					}

					// Link material element
					cDocument.LinkEndChild(*pSkinElement);

					// Create paths directory...
					std::string sSkinFilename = std::string(pMaterial->GetIGameMaterial()->GetMaterialName()) + std::string(".skin");
					std::string sAbsSkinFilename = sApplicationDrive + sApplicationDir + std::string("Data\\Misc\\");
					if (g_SEOptions.bPLDirectories) {
						// Misc
						CreateDirectory(sAbsSkinFilename.c_str(), nullptr);
						if (g_SEOptions.bSubDirectories) {
							sAbsSkinFilename.append(g_SEOptions.sFilenameOnly);
							sAbsSkinFilename.append("\\");
							CreateDirectory(sAbsSkinFilename.c_str(), nullptr);
						}
					}
					sAbsSkinFilename.append(sSkinFilename);

					// Update the skin filename
					if (g_SEOptions.bPLDirectories && g_SEOptions.bSubDirectories)
						sSkinFilename = std::string("Data\\Misc\\") + g_SEOptions.sFilenameOnly + "\\" + sSkinFilename;
					else
						sSkinFilename = std::string("Data\\Misc\\") + sSkinFilename;

					// Save settings
					if (cDocument.Save(sAbsSkinFilename.c_str()))
						g_pLog->LogFLine(PLLog::Hint, "Created '%s'", sAbsSkinFilename.c_str());
					else
						g_pLog->LogFLine(PLLog::Error, "Can't create '%s'!", sAbsSkinFilename.c_str());

					// Add a 'skin'
					pNodeElement->SetAttribute("Skin", sSkinFilename.c_str());
				} else {
					// [TODO] Handle this situation!?
					int i = 0;
				}
			}
		} else {
			// Yeah, no multimaterial - that's quite primitive... just add the material and set it as 'skin'-file :D
			PLSceneMaterial *pMaterial = GetScene().AddMaterial(nullptr, *pIGameMaterial);
			if (pMaterial) {
				// Add a 'skin'
				std::string sMaterialFilename(pMaterial->GetName());
				if (sMaterialFilename.find(".mat") != std::string::npos)
					sMaterialFilename = "Data\\Materials\\" + sMaterialFilename;
				pNodeElement->SetAttribute("Skin", sMaterialFilename.c_str());
			}
		}
	}

	// Get a list of all morph channels of the mesh
	const Array<morphChannel*> *plstMorphChannels = nullptr;
	if (m_pMesh)
		plstMorphChannels = &m_pMesh->GetMorphChannels();

	// Get the animation list of the mesh
	const Array<PLSceneMesh::Animation*> *plstAnimations = m_pMesh ? &m_pMesh->GetAnimations() : nullptr;

	// Write modifiers
	WriteModifiers(*pNodeElement, sApplicationDrive, sApplicationDir);

	// Are there any morph channels?
	if (plstMorphChannels || (plstAnimations && plstAnimations->GetNumOfElements())) {
		// Write modifiers for morph channels
		if (plstMorphChannels) {
			// Loop through all morph channels
			for (uint32 nChannel=0; nChannel<plstMorphChannels->GetNumOfElements(); nChannel++) {
				// Get the current morph channel
				const morphChannel *pMorphChannel = (*plstMorphChannels)[nChannel];

				// Add scene node modifier
				XmlElement *pModifierElement = new XmlElement("Modifier");

				// Setup attributes
				pModifierElement->SetAttribute("Class",     "PLScene::SNMMeshMorph");
				pModifierElement->SetAttribute("Name",      pMorphChannel->mName.data());
				pModifierElement->SetAttribute("Weight",    "0");	// [TODO] Write down the current weight -> pMorphChannel->mTargetPercent/100.0f
				pModifierElement->SetAttribute("MinWeight", String::Format("%f", pMorphChannel->mSpinmin/100.0f));
				pModifierElement->SetAttribute("MaxWeight", String::Format("%f", pMorphChannel->mSpinmax/100.0f));

				// Link node element
				pNodeElement->LinkEndChild(*pModifierElement);
			}
		}

		// Write modifiers for animations
		if (plstAnimations && plstAnimations->GetNumOfElements()) {
			// Loop through all animations
			bool bFirst = true;
			ConstIterator<PLSceneMesh::Animation*> cIterator = plstAnimations->GetConstIterator();
			while (cIterator.HasNext()) {
				// Get the animation
				const PLSceneMesh::Animation *pAnimation = cIterator.Next();

				// Add scene node modifier
				XmlElement *pModifierElement = new XmlElement("Modifier");

				// Setup attributes
				pModifierElement->SetAttribute("Class", "PLScene::SNMMeshAnimation");
				pModifierElement->SetAttribute("Name",  pAnimation->sAnimation.szName);

				// Set speed to 1 only for the first found animation
				if (bFirst) {
					pModifierElement->SetAttribute("Speed", "1.0");
					bFirst = false;
				} else {
					pModifierElement->SetAttribute("Speed", "0.0");
				}

				// Link node element
				pNodeElement->LinkEndChild(*pModifierElement);
			}
		}
	}

	// Link node element
	cSceneElement.LinkEndChild(*pNodeElement);
}
