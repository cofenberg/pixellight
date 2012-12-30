/*********************************************************\
 *  File: PLSceneObject.cpp                              *
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
#include <morpher/wm3.h>
#include <IGame/IGame.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLScene.h"
#include "PL3dsMaxSceneExport/PLSceneMesh.h"
#include "PL3dsMaxSceneExport/PLSceneMaterial.h"
#include "PL3dsMaxSceneExport/PLSceneObject.h"


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
PLSceneObject::PLSceneObject(PLSceneContainer &cContainer, IGameNode &cIGameNode, const String &sName, PLSceneMesh *pMesh) :
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
void PLSceneObject::WriteToFile(XmlElement &cSceneElement, const String &sApplicationDrive, const String &sApplicationDir)
{
	// Add scene node
	XmlElement *pNodeElement = new XmlElement("Node");
	pNodeElement->SetAttribute("Class", GetClassName());
	pNodeElement->SetAttribute("Name",  GetName());

	// Mesh filename
	if (m_pMesh)
		pNodeElement->SetAttribute("Mesh", PLTools::GetResourceFilename(PLTools::ResourceMesh, m_pMesh->GetName() + ".mesh"));

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
							// Get PixelLight material corresponding to the mesh material
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
										pSubMaterialElement->SetAttribute("Name", PLTools::GetResourceFilename(PLTools::ResourceMaterial, pMeshSubMaterial->GetName()));

										// Add value
										XmlText *pValue = new XmlText(PLTools::GetResourceFilename(PLTools::ResourceMaterial, pSubMaterial->GetName()));
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

					// Save settings
					const String sSkinFilename    = PLTools::GetResourceFilename(PLTools::ResourceSkin, String(pMaterial->GetIGameMaterial()->GetMaterialName()) + String(".skin"));
					const String sAbsSkinFilename = sApplicationDrive + sApplicationDir + sSkinFilename;
					if (cDocument.Save(sAbsSkinFilename))
						g_pLog->LogFLine(PLLog::Hint, "Created '%s'", sAbsSkinFilename.GetASCII());
					else
						g_pLog->LogFLine(PLLog::Error, "Can't create '%s'!", sAbsSkinFilename.GetASCII());

					// Add a 'skin'
					pNodeElement->SetAttribute("Skin", sSkinFilename);
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
				pNodeElement->SetAttribute("Skin", PLTools::GetResourceFilename(PLTools::ResourceMaterial, pMaterial->GetName()));
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
