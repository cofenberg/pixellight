/*********************************************************\
 *  File: MeshManager.cpp                                *
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
#include <PLCore/Log/Log.h>
#include <PLCore/File/Url.h>
#include <PLCore/Base/Class.h>
#include <PLCore/String/Tokenizer.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Material/MaterialManager.h>
#include "PLMesh/Creator/MeshCreator.h"
#include "PLMesh/MeshLODLevel.h"
#include "PLMesh/SkeletonManager.h"
#include "PLMesh/MeshManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
namespace PLMesh {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MeshManager::MeshManager(Renderer &cRenderer) :
	m_pRenderer(&cRenderer),
	m_pSkeletonManager(new SkeletonManager())
{
	SetManagerName("Mesh manager");

	// Unload unused resources, please
	SetUnloadUnused(true);

	// Create the standard mesh
	Mesh *pMesh = CreateMesh("PLMesh::MeshCreatorCube", true, "Dimension=\"1.0 1.0 1.0\"");
	if (pMesh) {
		pMesh->SetName("Default");
		pMesh->SetProtected(true);
		SetStandard(pMesh);
	}
}

/**
*  @brief
*    Destructor
*/
MeshManager::~MeshManager()
{
	delete m_pSkeletonManager;
}

/**
*  @brief
*    Returns the used renderer
*/
Renderer *MeshManager::GetRenderer() const
{
	return m_pRenderer;
}

/**
*  @brief
*    Creates the mesh if a null pointer is given and adds the required LODs
*/
Mesh *MeshManager::CreateMesh()
{
	Mesh *pMesh = Create();
	pMesh->AddMorphTarget();

	// Set standard material
	pMesh->AddMaterial(GetRenderer()->GetRendererContext().GetMaterialManager().GetStandard());
	while (pMesh->GetNumOfLODLevels() <= 0) {
		MeshLODLevel *pLODLevel = pMesh->AddLODLevel();
		pLODLevel->CreateGeometries();
		pLODLevel->CreateIndexBuffer();
	}

	// Done
	return pMesh;
}

/**
*  @brief
*    Creates a new mesh resource
*/
Mesh *MeshManager::CreateMesh(const String &sName, bool bStatic)
{
	// Check whether this resource is already within the manager
	Mesh *pResource = GetByName(sName);
	if (pResource)
		return pResource;

	// Get name
	String sNameT;
	if (sName.GetLength())
		sNameT = sName;
	else {
		// Find an unused resource name
		sNameT = "0";
		for (int i=1; GetByName(sNameT); i++)
			sNameT = i;
	}

	// Create and return the new resource
	return new Mesh(m_pRenderer, *this, sNameT, bStatic);
}

/**
*  @brief
*    Creates a mesh resource using a mesh creator
*/
Mesh *MeshManager::CreateMesh(const String &sName, bool bStatic, const String &sParameters)
{
	// To keep things as fast as possible we store a pointer to the base class
	// (no hash map operation + quite efficent internal string comparison)
	static const PLCore::Class *pBaseClass = PLCore::ClassManager::GetInstance()->GetClass("PLMesh::MeshCreator");

	// Create the mesh creator
	if (pBaseClass) {
		const PLCore::Class *pClass = PLCore::ClassManager::GetInstance()->GetClass(sName);
		if (pClass && pClass->IsDerivedFrom(*pBaseClass)) {
			MeshCreator *pMC = static_cast<MeshCreator*>(pClass->Create());
			if (pMC) {
				// Set parameters
				if (sParameters.GetLength())
					pMC->SetValues(sParameters);

				// Create the mesh
				Mesh *pMesh = CreateMesh();
				if (pMesh)
					pMC->Create(*pMesh, 0, bStatic);

				// Destroy the mesh creator
				delete pMC;

				// Return the created mesh
				return pMesh;
			}
		}
	}

	// Error!
	return nullptr;
}

/**
*  @brief
*    Load mesh
*/
Mesh *MeshManager::LoadMesh(const String &sFilename, const String &sParams, const String &sMethod, bool bReloadMesh, bool bStatic)
{
	// Is the mesh already loaded?
	Mesh *pMesh = GetByName(sFilename);
	if (pMesh) {
		// Reload this mesh?
		if (bReloadMesh)
			pMesh->Reload();
	} else {
		// Create the mesh by using a mesh creator?
		if (sFilename.Compare("Create ", 0, 7)) {
			// Get mesh creator class to use
			Tokenizer cTokenizer;
			cTokenizer.Start(sFilename);
			cTokenizer.GetNextToken(); // Skip 'Create '
			String sClass = cTokenizer.GetNextToken();
			if (sClass.GetLength()) {
				// Get mesh name
				bool bUseName = false;
				String sName;
				cTokenizer.PushState();
				if (cTokenizer.FindToken("Name")) {
					// Skip '='
					cTokenizer.GetNextToken();

					// Get name
					if (cTokenizer.GetNextToken().GetLength()) {
						if (cTokenizer.GetNextToken().GetLength() == 1 && cTokenizer.GetQuotes().IsSubstring(cTokenizer.GetToken())) {
							sName = cTokenizer.GetNextToken();
							// Read "
							if (!cTokenizer.GetNextToken().GetLength() == 1 && cTokenizer.GetQuotes().IsSubstring(cTokenizer.GetToken()))
								PL_LOG(Error, "Name var closing \" is missed! (" + sFilename + ')')
						} else {
							sName = cTokenizer.GetToken();
						}
						bUseName = true;
					}
				} else {
					// There's no name! :(
					cTokenizer.PopState();
				}

				// Check whether the mesh is already within the mesh manager
				pMesh = bUseName ? GetByName(sName) : nullptr;
				if (!pMesh) {
					// Get the parameters
					String sParameters = sFilename.GetSubstring(cTokenizer.GetPosition());

					// Try to create the mesh
					pMesh = CreateMesh(sClass, bStatic, sParameters);
					if (bUseName && pMesh)
						pMesh->SetName(sName);
				}
			}
			cTokenizer.Stop();

		// Try to get/load the mesh
		} else {
			String sExtension = Url(sFilename).GetExtension();
			if (sExtension.GetLength()) {
				pMesh = Create(sFilename);
				if (pMesh) {
					if (bStatic) {
						// We do NOT need to give parameters because 'Static' is 'true' by default!
						if (!pMesh->Load(sFilename, sParams, sMethod)) {
							// Can't load mesh...
							delete pMesh;
							pMesh = nullptr;
						}
					} else {
						if (!pMesh->Load(sFilename, String("Static=") + bStatic + '\"')) {
							// Can't load mesh...
							delete pMesh;
							pMesh = nullptr;
						}
					}
				}
			}
		}
	}

	// Return the mesh
	return pMesh;
}

/**
*  @brief
*    Returns the skeleton manager
*/
SkeletonManager &MeshManager::GetSkeletonManager() const
{
	return *m_pSkeletonManager;
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ResourceManager functions     ]
//[-------------------------------------------------------]
Mesh *MeshManager::CreateResource(const String &sName)
{
	return new Mesh(m_pRenderer, *this, sName);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh
