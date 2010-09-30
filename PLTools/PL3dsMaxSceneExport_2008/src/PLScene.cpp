/*********************************************************\
 *  File: PLScene.cpp                                    *
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
#include <PLGeneral/File/Url.h>
#include <IGame/IGame.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLSceneNode.h"
#include "PL3dsMaxSceneExport/PLSceneTexture.h"
#include "PL3dsMaxSceneExport/PLSceneMaterial.h"
#include "PL3dsMaxSceneExport/PLSceneMaterialColor.h"
#include "PL3dsMaxSceneExport/PLScene.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PLScene::PLScene(Interface &cMaxInterface, IGameScene &cIGame, int nProgressMin, int nProgressMax, const char szApplicationDrive[], const char szApplicationDir[]) :
	PLSceneContainer(NULL, g_SEOptions.sFilenameOnly, TypeScene),
	m_pMaxInterface(&cMaxInterface),
	m_pIGame(&cIGame),
	m_nTotalNumOfMaxNodes(cIGame.GetTotalNodeCount()),
	m_nNumOfMaxNodes(0),
	m_nProgressMin(nProgressMin),
	m_nProgressMax(nProgressMax),
	m_nProgress(0),
	m_sApplicationDrive(szApplicationDrive),
	m_sApplicationDir(szApplicationDir),
	m_nTotalNumOfNodes(0),
	m_nMaxMeshVertices(4096),
	m_pMeshVertices(new PLSceneMesh::Vertex[m_nMaxMeshVertices]),
	m_pVHTable(new PLSceneMesh::VertexHashTable(15000)),
	m_bVHTableUsed(false),
	m_nMaxMeshTriangles(4096),
	m_pMeshTriangles(new PLSceneMesh::Triangle[m_nMaxMeshTriangles]),
	m_nMaxMeshGeometries(32),
	m_pMeshGeometries(new PLSceneMesh::Geometry[m_nMaxMeshGeometries])
{
	// Initialize the scene statistics
	memset(&m_sSceneStatistics, 0, sizeof(SStatistics));

	// Initialize the mesh statistics
	memset(&m_sMeshStatistics, 0, sizeof(SMeshStatistics));

	// Loop through all top level nodes
	g_pLog->LogFLine(PLLog::Scene, "Scene root created");
	m_pMaxInterface->ProgressUpdate(5, 0, "Process scene...");
	for (int nNode=0; nNode<m_pIGame->GetTopLevelNodeCount(); nNode++) {
		IGameNode *pIGameNode = m_pIGame->GetTopLevelNode(nNode);
		if (pIGameNode) {
			g_pLog->LogFLine(PLLog::Scene, "Found top level 3ds Max node: %s", pIGameNode->GetName());
			AddIGameNode(*pIGameNode);
		}
	}
}

/**
*  @brief
*    Destructor
*/
PLScene::~PLScene()
{
	// Destroy all meshes
	for (std::vector<PLScenePLMesh*>::size_type i=0; i<m_lstMeshes.size(); i++) {
		PLScenePLMesh *pMesh = m_lstMeshes[i];
		if (pMesh)
			delete pMesh;
	}

	// For PLSceneMesh
	delete [] m_pMeshVertices;
	delete m_pVHTable;
	delete [] m_pMeshTriangles;
	delete [] m_pMeshGeometries;

	// Destroy all textures
	for (std::vector<PLSceneTexture*>::size_type i=0; i<m_lstTextures.size(); i++) {
		PLSceneTexture *pTexture = m_lstTextures[i];
		if (pTexture)
			delete pTexture;
	}

	// Destroy all materials
	for (std::vector<PLSceneMaterial*>::size_type i=0; i<m_lstMaterials.size(); i++) {
		PLSceneMaterial *pMaterial = m_lstMaterials[i];
		if (pMaterial)
			delete pMaterial;
	}
}

/**
*  @brief
*    Returns the 3ds Max interface
*/
Interface &PLScene::GetMaxInterface() const
{
	return *m_pMaxInterface;
}

/**
*  @brief
*    Returns the IGame interface
*/
IGameScene &PLScene::GetIGameInterface() const
{
	return *m_pIGame;
}

/**
*  @brief
*    Returns the total number of 3ds Max nodes
*/
int PLScene::GetTotalNumOfMaxNodes() const
{
	return m_nTotalNumOfMaxNodes;
}

/**
*  @brief
*    Returns the current number of 3ds Max nodes
*/
int PLScene::GetNumOfMaxNodes() const
{
	return m_nNumOfMaxNodes;
}

/**
*  @brief
*    Returns the a pointer to the PL scene node of a given 3ds Max node
*/
PLSceneNode *PLScene::GetPLSceneNode(INode &cMaxNode)
{
	// Bah, std::string is horror. Here I use a hack to use the good old sprintf to convert a pointer address into a string...
	std::string sKey = "XXXXXXXXXXXXXXXXXXXX";
	sprintf((char*)sKey.c_str(), "%19p", &cMaxNode);
	std::map<std::string, PLSceneNode*>::iterator pIterator = m_mapMaxToPLNodes.find(sKey);
	return pIterator == m_mapMaxToPLNodes.end() ? NULL : pIterator->second;
}

/**
*  @brief
*    Adds a mesh to the scene
*/
PLScenePLMesh *PLScene::AddMesh(IGameNode &cIGameNode, const std::string &sMeshName)
{
	// Is there a valid mesh name? If yes, instancing is quite simple. :)
	std::string sNewMeshName;
	if (!sMeshName.empty()) {
		// First at all, IS there already a mesh with this name?
		std::string sMeshNameLower = PLTools::ToLower(sMeshName); // Do ONLY use lower case, else the hashing will NOT return the same values!
		std::map<std::string, PLScenePLMesh*>::iterator pIterator = m_mapMeshes.find(sMeshNameLower);
		if (pIterator != m_mapMeshes.end() && pIterator->second) {
			// Update the total mesh statistics
			UpdateTotalMeshStatistics(*pIterator->second);

			// Return the mesh
			return pIterator->second;
		}
	}

	// Still here? Ok, maybe we are in luck and can use a 3ds Max instance...
	INode *pMaxNode = cIGameNode.GetMaxNode();
	if (pMaxNode) {
		Object *pMaxObject = pMaxNode->GetObjectRef();
		if (pMaxObject) {
			// Loop through all meshes
			for (std::vector<PLScenePLMesh*>::size_type i=0; i<m_lstMeshes.size(); i++) {
				// Get the exported mesh at the current index and check for instance. In here we do NOT go
				// over IGameObject because this would slow down the export dramatically!
				PLScenePLMesh *pMesh = m_lstMeshes.at(i);
				if (pMesh && pMaxObject == pMesh->Get3dsMaxObject()) {
					// Update the total mesh statistics
					UpdateTotalMeshStatistics(*pMesh);

					// Yeah, we found a 3ds Max instance!
					return pMesh;
				}
			}
		}
	}

	// Set mesh name
	sNewMeshName = sMeshName;

	// Nope, let's create a mesh with this name
	g_pLog->LogFLine(PLLog::Scene, "Mesh '%s' is created by the 3ds Max node '%s'", sNewMeshName.c_str(), cIGameNode.GetName());
	PLScenePLMesh *pMesh = new PLScenePLMesh(*this, cIGameNode, sNewMeshName);

	// Register the new mesh
	m_lstMeshes.push_back(pMesh);
	std::string sNewMeshNameLower = PLTools::ToLower(sNewMeshName); // Do ONLY use lower case, else the hashing will NOT return the same values!
	m_mapMeshes.insert(make_pair(sNewMeshNameLower, pMesh));

	// Update the mesh statistics
	m_sMeshStatistics.nNumOfMeshes++;
	m_sMeshStatistics.nNumOfMeshVertices   += pMesh->m_nNumOfVertices;
	m_sMeshStatistics.nNumOfMeshIndices    += pMesh->m_nNumOfTriangles*3;
	m_sMeshStatistics.nNumOfMeshTriangles  += pMesh->m_nNumOfTriangles;
	m_sMeshStatistics.nNumOfMeshGeometries += pMesh->m_nNumOfGeometries;
	UpdateTotalMeshStatistics(*pMesh);

	// Save the mesh
	if (g_SEOptions.bExportMeshes)
		pMesh->Save(m_sApplicationDrive, m_sApplicationDir);

	// Return the created mesh
	return pMesh;
}

/**
*  @brief
*    Copies a texture
*/
PLSceneTexture *PLScene::CopyTexture(const std::string &sFilename, bool bNormalMap_xGxR)
{
	// Get the map name
	std::string sMapName = sFilename;

	// Is there already a texture with this name?
	std::string sMapNameLower = PLTools::ToLower(sMapName);
	for (std::vector<PLSceneTexture*>::size_type i=0; i<m_lstTextures.size(); i++) {
		PLSceneTexture *pTexture = m_lstTextures[i];
		if (pTexture) {
			std::string sNameLower = PLTools::ToLower(pTexture->GetName());
			if (sNameLower == sMapNameLower) {
				// Jap, do not copy again
				m_sMeshStatistics.nNumOfTextureReferences++;
				pTexture->m_nReferenceCount++;
				return pTexture;
			}
		}
	}

	// Create the texture
	PLSceneTexture *pTexture = new PLSceneTexture(*this, sMapName, bNormalMap_xGxR);
	m_sMeshStatistics.nNumOfTextureReferences++;
	pTexture->m_nReferenceCount++;
	m_lstTextures.push_back(pTexture);
	return pTexture;
}

/**
*  @brief
*    Writes the scene into a XML document
*/
void PLScene::WriteToXMLDocument(XmlDocument &cDocument)
{
	// Add declaration
	XmlDeclaration *pDeclaration = new XmlDeclaration("1.0", "ISO-8859-1", "");
	cDocument.LinkEndChild(*pDeclaration);

	// Add scene
	XmlElement *pSceneElement = new XmlElement("Scene");

	// Setup attributes
	pSceneElement->SetAttribute("Version", "1");
	pSceneElement->SetAttribute("Name",    GetName().c_str());

	// Write position, rotation, scale, bounding box and flags
	WriteToFilePosRotScaleBoxFlags(*pSceneElement);

	// Write flexible variables
	WriteVariables(*pSceneElement);

	// Write modifiers
	// [TODO] Strings
	WriteModifiers(*pSceneElement, std::string(), std::string());

	// Get the 3ds Max version of the program currently running
	DWORD nRunning3dsMaxVersion = Get3DSMAXVersion();
	std::string sRunning3dsMaxVersion = "(" + PLTools::ToString(GET_MAX_RELEASE(   nRunning3dsMaxVersion)/1000.0f) + ").(" +
											  PLTools::ToString(GET_MAX_API_NUM(   nRunning3dsMaxVersion))		   + ").(" +
											  PLTools::ToString(GET_MAX_SDK_REV(   nRunning3dsMaxVersion))		   + ").(" +
											  PLTools::ToString(GET_MAX_SDK_NUMREV(nRunning3dsMaxVersion))		   + ")-('IGame.dll'='" +
											  PLTools::ToString(GetIGameVersion()) + ")'";

	// Get the 3ds Max version this exporter was build for
	DWORD nBuild3dsMaxVersion = VERSION_3DSMAX;
	std::string sBuild3dsMaxVersion = "(" + PLTools::ToString(GET_MAX_RELEASE(   nBuild3dsMaxVersion)/1000.0f) + ").(" +
											PLTools::ToString(GET_MAX_API_NUM(   nBuild3dsMaxVersion))		   + ").(" +
											PLTools::ToString(GET_MAX_SDK_REV(   nBuild3dsMaxVersion))		   + ").(" +
											PLTools::ToString(GET_MAX_SDK_NUMREV(nBuild3dsMaxVersion))		   + ")-('IGame.dll'='" +
											PLTools::ToString(IGAMEDLLVERSION) + ")'";

	{ // Write about information
		// Add scene container
		XmlElement *pContainerElement = new XmlElement("Container");

		// Setup attributes
		pContainerElement->SetAttribute("Class", "PLScene::SceneContainer");
		pContainerElement->SetAttribute("Name",  "AboutInformation");

		// First at all, write down some general information
		std::string sValue = "3ds Max ((<RELEASE>).(<API_NUM>).(<SDK_REV>).(<SDK_NUMREV>), running version: " + sRunning3dsMaxVersion + ", exporter build for version: " + sBuild3dsMaxVersion + ") scene exporter plugin (version 0.8.6, build: date: " + __DATE__ + "  time: " + __TIME__ + ") Copyright (C) 2002-2010 by The PixelLight Team";
		XmlElement *pNodeElement = new XmlElement("Node");
		pNodeElement->SetAttribute("Class", "PLScene::SNKeyValue");
		pNodeElement->SetAttribute("Name",  "CreatedWithKey");
		pNodeElement->SetAttribute("Key",   "CreatedWith");
		pNodeElement->SetAttribute("Value", sValue.c_str());
		pContainerElement->LinkEndChild(*pNodeElement);

		// Now the stuff from the file properties dialog
		GetSummaryPropertyValue(*pContainerElement, PROPSET_SUMMARYINFO,    PIDSI_TITLE,    "Title");
		GetSummaryPropertyValue(*pContainerElement, PROPSET_SUMMARYINFO,    PIDSI_SUBJECT,  "Subject");
		GetSummaryPropertyValue(*pContainerElement, PROPSET_SUMMARYINFO,    PIDSI_AUTHOR,   "Author");
		GetSummaryPropertyValue(*pContainerElement, PROPSET_DOCSUMMARYINFO, 0x0000000E,     "Manager");
		GetSummaryPropertyValue(*pContainerElement, PROPSET_DOCSUMMARYINFO, 0x0000000F,     "Company");
		GetSummaryPropertyValue(*pContainerElement, PROPSET_DOCSUMMARYINFO, 0x00000002,     "Category");
		GetSummaryPropertyValue(*pContainerElement, PROPSET_SUMMARYINFO,    PIDSI_KEYWORDS, "Keywords");
		GetSummaryPropertyValue(*pContainerElement, PROPSET_SUMMARYINFO,    PIDSI_COMMENTS, "Comments");

		// Link container element
		pSceneElement->LinkEndChild(*pContainerElement);
	}

	{ // Add 'SceneRenderer' key
		// Add scene node
		XmlElement *pNodeElement = new XmlElement("Node");

		// Setup attributes
		pNodeElement->SetAttribute("Class", "PLScene::SNKeyValue");
		pNodeElement->SetAttribute("Name",  "SceneRendererKey");
		pNodeElement->SetAttribute("Key",   "SceneRenderer");
		pNodeElement->SetAttribute("Value", g_SEOptions.sSceneRenderer.c_str());

		// Link node element
		pSceneElement->LinkEndChild(*pNodeElement);
	}

	{ // Add 'SceneRendererVariables' key
		// Add scene node
		XmlElement *pNodeElement = new XmlElement("Node");

		// Setup attributes
		Point3 cColor;
		if (g_SEOptions.bOverwriteAmbientColor) {
			cColor.x = g_SEOptions.fOverwrittenAmbientColor[0];
			cColor.y = g_SEOptions.fOverwrittenAmbientColor[1];
			cColor.z = g_SEOptions.fOverwrittenAmbientColor[2];
		} else {
			Interval valid = NEVER;
			cColor = m_pMaxInterface->GetAmbient(m_pMaxInterface->GetTime(), valid);
		}
		pNodeElement->SetAttribute("Class", "PLScene::SNKeyValue");
		pNodeElement->SetAttribute("Name",  "SceneRendererVariablesKey");
		pNodeElement->SetAttribute("Key",   "SceneRendererVariables");
		pNodeElement->SetAttribute("Value", String::Format("AmbientColor='%f %f %f'", cColor.x, cColor.y, cColor.z));

		// Link node element
		pSceneElement->LinkEndChild(*pNodeElement);
	}

	{// Add 'ClearColor' key
		// Add scene node
		XmlElement *pNodeElement = new XmlElement("Node");

		// Setup attributes
		Interval valid = NEVER;
		Point3 cColor = m_pMaxInterface->GetBackGround(m_pMaxInterface->GetTime(), valid);
		pNodeElement->SetAttribute("Class", "PLScene::SNKeyValue");
		pNodeElement->SetAttribute("Name",  "ClearColorKey");
		pNodeElement->SetAttribute("Key",   "ClearColor");
		pNodeElement->SetAttribute("Value", String::Format("%f %f %f", cColor.x, cColor.y, cColor.z));

		// Link node element
		pSceneElement->LinkEndChild(*pNodeElement);
	}

	// Export the 'start camera'
	ExportStartCamera(*pSceneElement);

	// Is there a given scene container?
	if (g_SEOptions.sSceneContainer.empty()) {
		// Write down all nodes
		for (std::vector<PLSceneNode*>::size_type i=0; i<m_lstSceneNodes.size(); i++) {
			PLSceneNode *pSceneNode = m_lstSceneNodes[i];
			if (pSceneNode)
				pSceneNode->WriteToFile(*pSceneElement, m_sApplicationDrive, m_sApplicationDir);
		}
	} else {
		// Add scene container
		XmlElement *pContainerElement = new XmlElement("Container");

		// Setup attributes
		pContainerElement->SetAttribute("Class", g_SEOptions.sSceneContainer.c_str());
		pContainerElement->SetAttribute("Name",  "Container");

		// [TODO] Currently the bounding boxes are not correct
/*		// Get the local bounding box of the scene container (equal to the scene bounding box!)
		if (!PLTools::IsEmpty(m_cBoundingBox)) {
			Box3 cLocalBox;
			if (m_pIGameNode) {
				GMatrix mTransform = m_pIGameNode->GetWorldTM().Inverse();
				cLocalBox.pmin = cLocalBox.pmax = m_cBoundingBox[0]*mTransform;
				for (int i=1; i<8; i++)
					cLocalBox += m_cBoundingBox[i]*mTransform;
				PLTools::ValidateMinimumMaximum(cLocalBox);
			} else {
				cLocalBox.pmin = m_cBoundingBox.pmin-m_vCenter;
				cLocalBox.pmax = m_cBoundingBox.pmax-m_vCenter;
			}

			// Write bounding box
			if (!PLTools::IsEmpty(cLocalBox)) {
				pContainerElement->SetAttribute("AABBMin", String::Format("%f %f %f", cLocalBox.pmin.x, cLocalBox.pmin.y, cLocalBox.pmin.z));
				pContainerElement->SetAttribute("AABBMax", String::Format("%f %f %f", cLocalBox.pmax.x, cLocalBox.pmax.y, cLocalBox.pmax.z));
			}
		}*/

		// Are there any flags?
		if (m_sFlags.length())
			pContainerElement->SetAttribute("Flags", m_sFlags.c_str());

		// Write down all nodes
		for (std::vector<PLSceneNode*>::size_type i=0; i<m_lstSceneNodes.size(); i++) {
			PLSceneNode *pSceneNode = m_lstSceneNodes[i];
			if (pSceneNode)
				pSceneNode->WriteToFile(*pContainerElement, m_sApplicationDrive, m_sApplicationDir);
		}

		// Link container element
		pSceneElement->LinkEndChild(*pContainerElement);
	}

	// Link material element
	cDocument.LinkEndChild(*pSceneElement);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Gets a PixelLight material
*/
PLSceneMaterial *PLScene::GetMaterial(Mtl &cMaxMaterial) const
{
	// Get the IGameMaterial material encapsulating the 3ds Max material
	IGameMaterial *pIGameMaterial = m_pIGame->GetIGameMaterial(&cMaxMaterial);
	if (pIGameMaterial) {
		// Try to find the PixelLight material encapsulating the IGameMaterial
		for (std::vector<PLSceneMaterial*>::size_type i=0; i<m_lstMaterials.size(); i++) {
			PLSceneMaterial *pMaterial = m_lstMaterials[i];
			if (pMaterial && pMaterial->GetIGameMaterial() &&
				pMaterial->GetIGameMaterial()->GetMaxMaterial() == pIGameMaterial->GetMaxMaterial())
				return pMaterial; // Yeah, we've found it!
		}
	}

	// Error!
	return NULL;
}

/**
*  @brief
*    Adds a material to the mesh
*/
PLSceneMaterial *PLScene::AddMaterial(IGameMaterial *pParentIGameMaterial, IGameMaterial &cIGameMaterial)
{
	// Is this material already within the scene material list?
	for (std::vector<PLSceneMaterial*>::size_type i=0; i<m_lstMaterials.size(); i++) {
		PLSceneMaterial *pMaterial = m_lstMaterials[i];
		if (pMaterial && pMaterial->GetIGameMaterial() &&
			pMaterial->GetIGameMaterial()->GetMaxMaterial() == cIGameMaterial.GetMaxMaterial()) {
			// Jap, return this scene material
			m_sMeshStatistics.nNumOfMaterialReferences++;
			pMaterial->m_nReferenceCount++;
			return pMaterial;
		}
	}

	// Ok, we are still here, must be a new one :)
	// Get the material name
	std::string sName;
	if (g_SEOptions.bCreateMaterials) {
		// Get material name
		const TCHAR *pszName = cIGameMaterial.GetMaterialName();
		if (pszName) {
			// Get material filename (hopefully no one gives materials a name like 'c:\Bla'!)
			Url cUrl = pszName;
			if (!cUrl.IsRelative()) {
				g_pLog->LogFLine(PLLog::Error, "Material '%s' is a dangerous name, we demand to NOT to use absolute filenames as material names!", pszName);

				// Error!
				return NULL;
			}
			sName = pszName;

			// Get name
			if (g_SEOptions.bSubDirectories)
				sName = g_SEOptions.sFilenameOnly + "\\" + sName;
		} else {
			// Material with no name found - ignore it!

			// Error!
			return NULL;
		}

		int nIndex = 0;
		std::string sNewName = sName;
		sNewName.append(".mat");
		while (1) {
			std::string sNewNameLower = PLTools::ToLower(sNewName);
			std::vector<PLSceneMaterial*>::size_type i = 0;
			for (; i<m_lstMaterials.size(); i++) {
				PLSceneMaterial *pMaterial = m_lstMaterials[i];
				if (pMaterial) {
					std::string sMatNameLower = PLTools::ToLower(pMaterial->GetName());
					if (sMatNameLower == sNewNameLower) {
						// Try to resolve the name conflict
						sNewName = sName + "_" + PLTools::ToString(nIndex);
						sNewName.append(".mat");
						nIndex++;
						break;
					}
				}
			}
			if (i >= m_lstMaterials.size())
				break; // There was no name conflict :)
		}
		sName = sNewName;
	} else {
		// [TODO] Don't use the 3ds Max material directly!
		Mtl *pMaxMat = cIGameMaterial.GetMaxMaterial();
		if (!pMaxMat)
			return NULL;

		// See if it's a standard material
		StdMat *pMaxStandardMat = (pMaxMat->ClassID() == Class_ID(DMTL_CLASS_ID, 0)) ? (StdMat*)pMaxMat : NULL;

		// Do NOT create material files, do ONLY use the first found active texture...
		BitmapTex *pBitmapTex = NULL;
		for (int nSlot=0; nSlot<pMaxMat->NumSubTexmaps(); nSlot++) {
			// If this is a standard material, is the map enabled?
			if (!pMaxStandardMat || pMaxStandardMat->MapEnabled(nSlot)) {
				// Get the texture
				Texmap *pTexMap = pMaxMat->GetSubTexmap(nSlot);
				if (pTexMap) {
					// Texture
					if (pTexMap->ClassID() == Class_ID(BMTEX_CLASS_ID, 0x00)) {
						pBitmapTex = (BitmapTex*)pTexMap;
						break;
					}
				}
			}
		}

		// Get texture name
		if (pBitmapTex) {
			// Get the texture name
			sName = pBitmapTex->GetMapName();
		} else {
			// Error!
			g_pLog->LogFLine(PLLog::Warning, "Material '%s' has no texture", pMaxMat->GetName());

			// Use the standard PixelLight texture as fallback
			sName = "Data/Textures/Default.dds";
		}

		// Is there already a material with this name?
		std::string sNameLower = PLTools::ToLower(sName);
		for (std::vector<PLSceneMaterial*>::size_type i=0; i<m_lstMaterials.size(); i++) {
			PLSceneMaterial *pMaterial = m_lstMaterials[i];
			if (pMaterial) {
				std::string sMatNameLower = PLTools::ToLower(pMaterial->GetName());
				if (sMatNameLower == sNameLower) {
					// Jap, return this scene material
					m_sMeshStatistics.nNumOfMaterialReferences++;
					pMaterial->m_nReferenceCount++;
					return pMaterial;
				}
			}
		}

		// Copy the texture if requested and possible
		if (pBitmapTex) {
			// Copy texture (do NOT use 'sName'!)
			PLSceneTexture *pTexture = CopyTexture(pBitmapTex->GetMapName());
			if (pTexture) {
				// Done
				g_pLog->LogFLine(PLLog::Scene, "  Texture: %s", sName.c_str());
			} else {
				// Error!
				g_pLog->LogFLine(PLLog::Error, "  Failed to copy texture: %s", sName.c_str());
			}
		}
	}

	// Create the material
	PLSceneMaterial *pMaterial = PLSceneMaterial::Create(*this, pParentIGameMaterial, cIGameMaterial, sName);
	if (pMaterial) {
		// Register the material
		m_sMeshStatistics.nNumOfMaterialReferences++;
		pMaterial->m_nReferenceCount++;
		m_lstMaterials.push_back(pMaterial);

		// Save the material
		if (g_SEOptions.bExportMaterials && g_SEOptions.bCreateMaterials)
			pMaterial->Save(m_sApplicationDrive, m_sApplicationDir);
	}

	// Done
	return pMaterial;
}

/**
*  @brief
*    Adds a color material to the scene
*/
PLSceneMaterial *PLScene::AddMaterial(const Color &cColor, const std::string &sName)
{
	// Create the material
	PLSceneMaterial *pMaterial = new PLSceneMaterialColor(*this, cColor, sName);
	if (pMaterial) {
		// Register the material
		m_sMeshStatistics.nNumOfMaterialReferences++;
		pMaterial->m_nReferenceCount++;
		m_lstMaterials.push_back(pMaterial);

		// Save the material
		if (g_SEOptions.bExportMaterials && g_SEOptions.bCreateMaterials)
			pMaterial->Save(m_sApplicationDrive, m_sApplicationDir);
	}

	// Done
	return pMaterial;
}

/**
*  @brief
*    Updates the total mesh statistics
*/
void PLScene::UpdateTotalMeshStatistics(const PLScenePLMesh &cMesh)
{
	m_sMeshStatistics.nTotalNumOfMeshes++;
	m_sMeshStatistics.nTotalNumOfMeshVertices   += cMesh.m_nNumOfVertices;
	m_sMeshStatistics.nTotalNumOfMeshIndices    += cMesh.m_nNumOfTriangles*3;
	m_sMeshStatistics.nTotalNumOfMeshTriangles  += cMesh.m_nNumOfTriangles;
	m_sMeshStatistics.nTotalNumOfMeshGeometries += cMesh.m_nNumOfGeometries;
}

/**
*  @brief
*    Reads the value as string of the 'summary' file properties
*/
void PLScene::GetSummaryPropertyValue(XmlElement &cSceneElement, int nSet, int nType, const TCHAR szName[]) const
{
	PROPSPEC PropSpec;

	PropSpec.ulKind = PRSPEC_PROPID;
	PropSpec.propid = nType;
	int nIndex = GetMaxInterface().FindProperty(nSet, &PropSpec);
	if (nIndex != -1) {
		const PROPVARIANT *pProp = GetMaxInterface().GetPropertyVariant(nSet, nIndex);
		if (pProp && pProp->vt == VT_LPSTR && pProp->pszVal && strlen(pProp->pszVal)) {
			// Add scene node
			XmlElement *pNodeElement = new XmlElement("Node");

			// Setup attributes
			pNodeElement->SetAttribute("Class", "PLScene::SNKeyValue");
			pNodeElement->SetAttribute("Name",  String(szName) + "Key");
			pNodeElement->SetAttribute("Key",   szName);
			pNodeElement->SetAttribute("Value", pProp->pszVal);

			// Link node element
			cSceneElement.LinkEndChild(*pNodeElement);
		}
	}
}

/**
*  @brief
*    Exports the 'start camera'
*/
void PLScene::ExportStartCamera(XmlElement &cSceneElement)
{
	// Get the 'start camera'
	ViewExp *pViewport = m_pMaxInterface->GetActiveViewport();
	if (pViewport) {
		std::string sName; // Name of the camera node

		// Is there a camera node assigned to the viewport?
		INode *pCamera = pViewport->GetViewCamera();
		if (pCamera) {
			sName = pCamera->GetName();
		} else {
			// Get the graphics window of the active viewport
			GraphicsWindow *pGraphicsWindow = pViewport->getGW();
			if (pGraphicsWindow) {
				// Set the name of the camera node
				sName = "ActiveViewportCamera";

				// Add camera scene node
				XmlElement *pNodeElement = new XmlElement("Node");
				pNodeElement->SetAttribute("Class", "PLScene::SNCamera");
				pNodeElement->SetAttribute("Name",  sName.c_str());

				// Get 3ds Max camera data
				int nPersp;
				Matrix3 mInvTM;
				float mMat[4][4];
				float fHither, fYon;
				pGraphicsWindow->getCameraMatrix(mMat, &mInvTM, &nPersp, &fHither, &fYon);

				// Get position, rotation and scale
				Point3 vPos;
				Point3 vRot;
				Point3 vScale;
				PLTools::GetPosRotScale(GMatrix(PLTools::Convert3dsMaxMatrixToOpenGLMatrix(mInvTM)), vPos, vRot, vScale, true);

				// Currently ONLY the center of the container the node is in use used to make it relative
				vPos -= GetWorldSpaceCenter();

				// Write down the position
				if (vPos.x || vPos.y || vPos.z)
					pNodeElement->SetAttribute("Position", String::Format("%f %f %f", vPos.x, vPos.y, vPos.z));

				// Write down the rotation
				if (vRot.x || vRot.y || vRot.z)
					pNodeElement->SetAttribute("Rotation", String::Format("%f %f %f", vRot.x, vRot.y, vRot.z));

				// [HACK] FOV... I multiplicate it with '0.74' so the result 'looks' similar to the one within
				// the 3ds Max viewport...
				float fFOV = RadToDeg(pViewport->GetFOV()*0.74f);
				if (fFOV != 45.0f)
					pNodeElement->SetAttribute("FOV", String::Format("%f", fFOV));

				// ZNear (ignore 0 or PL default setting)
				float fRange = fHither;
				if (fRange < 0.00001f)
					fRange = 0.00001f;
				if (fRange != 0.01f) {
					pNodeElement->SetAttribute("ZNear", String::Format("%f", fRange));

					// 'Normally' the near plane should never ever be <=0! (crazy z-fighting!)
					if (fRange <= 1.0000000e-006 && GetIGameNode())
						g_pLog->LogFLine(PLLog::Warning, "Camera (3ds Max node '%s') near plane is '%f' (really small number) but recommended is '>1.0000000e-006'!", GetIGameNode()->GetName(), fRange);
				}

				// ZFar (ignore 0 or PL default setting)
				fRange = fYon;
				if (fRange && fRange != 1000.0f)
					pNodeElement->SetAttribute("ZFar", String::Format("%f", fRange));

				// Detect "orbiting"/"walk through" mode... I do this by checking the current 'Command Mode ID'
				// agains '65585'... the 'walk through' viewport nagivation (I found no documentation, so I had
				// to figure out this by myself...)
				bool bOrbiting = true;
				CommandMode *pCommandMode = m_pMaxInterface->GetCommandMode();
				if (pCommandMode && pCommandMode->ID() == 65585)
					bOrbiting = false;
				if (bOrbiting) {
					// Get camera target name
					const std::string sTargetName = sName + std::string("Target");

					// Add scene node modifier so we can automatically orbiting
					XmlElement *pModifierElement = new XmlElement("Modifier");
					pModifierElement->SetAttribute("Class",  "PLScene::SNMMouseOrbitingController");
					pModifierElement->SetAttribute("Target", sTargetName.c_str());
					pNodeElement->LinkEndChild(*pModifierElement);

					{ // Add camera target scene node
						// Get look at point
						Point3 vCenter;
						Matrix3 mAffineTM;
						pViewport->GetAffineTM(mAffineTM);
						if (pViewport->GetViewType() == VIEW_PERSP_USER)
							vCenter = Point3(0.0f, 0.0f, -pViewport->GetFocalDist()) - mAffineTM.GetTrans();
						else
							vCenter = mAffineTM.GetTrans();

						// Currently ONLY the center of the container the node is in use used to make it relative
						vCenter -= GetWorldSpaceCenter();

						// Add the scene node
						XmlElement *pNodeElement = new XmlElement("Node");
						pNodeElement->SetAttribute("Class", "PLScene::SNHelper");
						pNodeElement->SetAttribute("Name",  sTargetName.c_str());
						if (vCenter.x || vCenter.y || vCenter.z)
							pNodeElement->SetAttribute("Position", String::Format("%f %f %f", vCenter.x, vCenter.y, vCenter.z));
						cSceneElement.LinkEndChild(*pNodeElement);
					}
				} else {
					// Add scene node modifier so we can automatically look around
					XmlElement *pModifierElement = new XmlElement("Modifier");
					pModifierElement->SetAttribute("Class", "PLScene::SNMRotationController");
					pNodeElement->LinkEndChild(*pModifierElement);

					// Add scene node modifier automatically fixing rotation
					pModifierElement = new XmlElement("Modifier");
					pModifierElement->SetAttribute("Class", "PLScene::SNMRotationFixRoll");
					pNodeElement->LinkEndChild(*pModifierElement);

					// Add scene node modifier so we can automatically move around
					pModifierElement = new XmlElement("Modifier");
					pModifierElement->SetAttribute("Class", "PLScene::SNMMoveController");
					pNodeElement->LinkEndChild(*pModifierElement);
				}

				// Link node element
				cSceneElement.LinkEndChild(*pNodeElement);

				// [TODO] We can add this 'always' - but often it's not desired... add
				// something like 'debug export'?
/*				{ // Add a camera rotation visualisation scene node
					XmlElement *pNodeElement = new XmlElement("Node");
					pNodeElement->SetAttribute("Class", "PLScene::SNCoordinateAxisRotation");
					cSceneElement.LinkEndChild(*pNodeElement);
				}
*/
				// [TODO] Add a grid visualisation scene node
/*				if (pViewport->IsGridVisible()) {
					XmlElement *pNodeElement = new XmlElement("Node");
					pNodeElement->SetAttribute("Class", "PLScene::SNLineGrid");
					cSceneElement.LinkEndChild(*pNodeElement);
					// GetGridSize()
					// GetConstructionTM()
					// Interface
					//virtual float GetGridSpacing()=0;
					//virtual int GetGridMajorLines()=0;
				}*/
			}
		}

		// Is there a '.' within the node name? If yes, replace it by '-'.
		size_t nIndex = sName.find_first_of(".");
		if (nIndex != std::string::npos) {
			char *pszName = (char*)sName.c_str() + nIndex;
			while (*pszName != '\0') {
				if (*pszName == '.')
					*pszName = '-';
				pszName++;
			}
		}
		TCHAR *pszName = (TCHAR*)sName.c_str();

		// Look for 'cell_' (cell_<cell name>_<node name>)
		std::string sSceneCellName, sSceneNodeName;
		if (!_strnicmp(pszName, "cell_", 5)) {
			// Get the name of the cell
			TCHAR *pszNameT = pszName += 5;

			// Check for '\0'
			if (*pszNameT != '\0') {
				// Read the cell name
				while (*pszNameT != '_' && *pszNameT != '\0')
					pszNameT++;
				sSceneCellName.insert(0, pszName, pszNameT-pszName);

				// Check for '_'
				if (*pszNameT == '_') {
					// Skip '_'
					pszNameT++; 

					// Get the name of the node
					pszName = pszNameT;
					while (*pszNameT != '_' && *pszNameT != '\0')
						pszNameT++;
					sSceneNodeName.insert(0, pszName, pszNameT-pszName);
				} else {
					sSceneNodeName = sName;
				}
			} else {
				sSceneNodeName = sName;
			}
		} else {
			sSceneNodeName = sName;
		}

		// Add scene node
		XmlElement *pNodeElement = new XmlElement("Node");

		// Setup attributes
		pNodeElement->SetAttribute("Class", "PLScene::SNKeyValue");
		pNodeElement->SetAttribute("Name",  "StartCameraKey");
		pNodeElement->SetAttribute("Key",   "StartCamera");

		// Is there a given scene container?
		g_pLog->PrintFLine("\nStart camera is: '%s'\n", sName.c_str());
		if (g_SEOptions.sSceneContainer.empty()) {
			if (sSceneCellName.length())
				pNodeElement->SetAttribute("Value", String::Format("%s.%s", sSceneCellName.c_str(), sSceneNodeName.c_str()));
			else
				pNodeElement->SetAttribute("Value", sSceneNodeName.c_str());
		} else {
			if (sSceneCellName.length())
				pNodeElement->SetAttribute("Value", String::Format("Container.%s.%s", sSceneCellName.c_str(), sSceneNodeName.c_str()));
			else
				pNodeElement->SetAttribute("Value", String::Format("Container.%s", sSceneNodeName.c_str()));
		}

		// Link node element
		cSceneElement.LinkEndChild(*pNodeElement);

		// Release the viewport
		m_pMaxInterface->ReleaseViewport(pViewport);
	}
}


//[-------------------------------------------------------]
//[ Protected virtual PLContainer functions               ]
//[-------------------------------------------------------]
bool PLScene::AddIGameNode(IGameNode &cIGameNode)
{
	// Update our 3ds Max node counter
	m_nNumOfMaxNodes++;

	// Update the 3ds Max progress bar
	int nProgress = m_nProgressMin+int(float(m_nProgressMax-m_nProgressMin)*float(m_nNumOfMaxNodes)/float(m_nTotalNumOfMaxNodes));
	if (nProgress != m_nProgress) {
		m_nProgress = nProgress;
		m_pMaxInterface->ProgressUpdate(m_nProgress, 0, "Collect scene data...");
	}

	// Call base implementation
	return PLSceneContainer::AddIGameNode(cIGameNode);
}

void PLScene::PostProcess()
{
	// Call base implementation
	PLSceneContainer::PostProcess();
}

void PLScene::OutputStatistics()
{
	// Get the total number of scene nodes
	m_nTotalNumOfNodes = m_sSceneStatistics.nNumOfCells+m_sSceneStatistics.nNumOfCellPortals+m_sSceneStatistics.nNumOfAntiPortals+
						 m_sSceneStatistics.nNumOfCameras+m_sSceneStatistics.nNumOfLights+m_sSceneStatistics.nNumOfObjects+
						 m_sSceneStatistics.nNumOfHelpers+m_sSceneStatistics.nNumOfUnknown;

// Start scene statistics
	g_pLog->PrintLine("\n\n>> Scene statistics <<");
	g_pLog->AddSpaces(PLLog::TabSize);

// Write texture statistics into the log
	g_pLog->PrintLine("\nTextures:");
	g_pLog->AddSpaces(PLLog::TabSize);
	g_pLog->PrintFLine("Number of texture references: %d", m_sMeshStatistics.nNumOfTextureReferences);
	g_pLog->PrintFLine("Number of textures: %d", m_lstTextures.size());
	g_pLog->AddSpaces(PLLog::TabSize);
	for (std::vector<PLSceneTexture*>::size_type i=0; i<m_lstTextures.size(); i++) {
		PLSceneTexture *pTexture = m_lstTextures[i];
		if (pTexture) {
			g_pLog->PrintFLine("%d: '%s' -> Reference count: %d (%g%%)", i, pTexture->GetName().c_str(), pTexture->GetReferenceCount(),
							   float(pTexture->GetReferenceCount())/float(m_sMeshStatistics.nNumOfTextureReferences)*100.0f);
		}
	}
	g_pLog->AddSpaces(-PLLog::TabSize*2);

// Write material statistics into the log
	if (g_SEOptions.bCreateMaterials) {
		g_pLog->PrintLine("\nMaterials:");
		g_pLog->AddSpaces(PLLog::TabSize);
		g_pLog->PrintFLine("Number of material references: %d", m_sMeshStatistics.nNumOfMaterialReferences);
		g_pLog->PrintFLine("Number of materials: %d", m_lstMaterials.size());
		g_pLog->AddSpaces(PLLog::TabSize);
		for (std::vector<PLSceneMaterial*>::size_type i=0; i<m_lstMaterials.size(); i++) {
			PLSceneMaterial *pMaterial = m_lstMaterials[i];
			if (pMaterial) {
				g_pLog->PrintFLine("%d: '%s' -> Reference count: %d (%g%%)", i, pMaterial->GetName().c_str(), pMaterial->GetReferenceCount(),
								   float(pMaterial->GetReferenceCount())/float(m_sMeshStatistics.nNumOfMaterialReferences)*100.0f);
			}
		}
		g_pLog->AddSpaces(-PLLog::TabSize*2);
	}

// Write scene statistics into the log
	g_pLog->PrintLine("\nNodes:");
	g_pLog->AddSpaces(PLLog::TabSize);
	g_pLog->PrintFLine("Total number of nodes: %d", m_nTotalNumOfNodes);
	g_pLog->PrintFLine("Cells: %d",   m_sSceneStatistics.nNumOfCells);
	g_pLog->PrintFLine("Cell-portals: %d", m_sSceneStatistics.nNumOfCellPortals);
	g_pLog->PrintFLine("Anti-portals: %d", m_sSceneStatistics.nNumOfAntiPortals);
	g_pLog->PrintFLine("Cameras: %d", m_sSceneStatistics.nNumOfCameras);
	g_pLog->PrintFLine("Lights: %d",  m_sSceneStatistics.nNumOfLights);
	g_pLog->PrintFLine("Objects: %d", m_sSceneStatistics.nNumOfObjects);
	g_pLog->PrintFLine("Helpers: %d", m_sSceneStatistics.nNumOfHelpers);
	g_pLog->PrintFLine("Unknown: %d", m_sSceneStatistics.nNumOfUnknown);
	g_pLog->AddSpaces(-PLLog::TabSize);

// Write mesh statistics into the log
	// Total meshes
	g_pLog->PrintLine("\nTotal meshes:");
	g_pLog->AddSpaces(PLLog::TabSize);
	g_pLog->PrintFLine("Meshes: %d",     m_sMeshStatistics.nTotalNumOfMeshes);
	g_pLog->PrintFLine("Vertices: %d",   m_sMeshStatistics.nTotalNumOfMeshVertices);
	g_pLog->PrintFLine("Indices: %d",    m_sMeshStatistics.nTotalNumOfMeshIndices);
	g_pLog->PrintFLine("Triangles: %d",  m_sMeshStatistics.nTotalNumOfMeshTriangles);
	g_pLog->PrintFLine("Geometries: %d", m_sMeshStatistics.nTotalNumOfMeshGeometries);
	g_pLog->AddSpaces(-PLLog::TabSize);

	// Unique meshes
	g_pLog->PrintLine("\nUnique meshes: (<percentage of total meshes)");
	g_pLog->AddSpaces(PLLog::TabSize);
	g_pLog->PrintFLine("Meshes: %d (%g%%)",     m_sMeshStatistics.nNumOfMeshes,         float(m_sMeshStatistics.nNumOfMeshes)/float(m_sMeshStatistics.nTotalNumOfMeshes)*100.0f);
	g_pLog->PrintFLine("Vertices: %d (%g%%)",   m_sMeshStatistics.nNumOfMeshVertices,   float(m_sMeshStatistics.nNumOfMeshVertices)/float(m_sMeshStatistics.nTotalNumOfMeshVertices)*100.0f);
	g_pLog->PrintFLine("Indices: %d (%g%%)",    m_sMeshStatistics.nNumOfMeshIndices,    float(m_sMeshStatistics.nNumOfMeshIndices)/float(m_sMeshStatistics.nTotalNumOfMeshIndices)*100.0f);
	g_pLog->PrintFLine("Triangles: %d (%g%%)",  m_sMeshStatistics.nNumOfMeshTriangles,  float(m_sMeshStatistics.nNumOfMeshTriangles)/float(m_sMeshStatistics.nTotalNumOfMeshTriangles)*100.0f);
	g_pLog->PrintFLine("Geometries: %d (%g%%)", m_sMeshStatistics.nNumOfMeshGeometries, float(m_sMeshStatistics.nNumOfMeshGeometries)/float(m_sMeshStatistics.nTotalNumOfMeshGeometries)*100.0f);
	g_pLog->AddSpaces(-PLLog::TabSize);

// Scene details
	g_pLog->PrintLine("\nScene details: (<percentage of total nodes>)");
	g_pLog->AddSpaces(PLLog::TabSize);
	PLSceneContainer::OutputStatistics();
	g_pLog->AddSpaces(-PLLog::TabSize);

// End scene statistics
	g_pLog->AddSpaces(-PLLog::TabSize);
	g_pLog->PrintLine("\n>> End statistics <<\n\n");
}
