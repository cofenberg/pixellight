/*********************************************************\
 *  File: MaterialManager.cpp                            *
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
#include "PLRenderer/RendererContext.h"
#include "PLRenderer/Texture/TextureManager.h"
#include "PLRenderer/Material/MaterialManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the owner renderer context of this manager
*/
RendererContext &MaterialManager::GetRendererContext() const
{
	return *m_pRendererContext;
}

/**
*  @brief
*    Reloads all materials
*/
bool MaterialManager::ReloadMaterials()
{
	bool bResult = true; // No error by default

	for (uint32 i=0; i<m_lstResources.GetNumOfElements(); i++) {
		Material *pMaterial = m_lstResources[i];
		if (!pMaterial->Reload())
			bResult = false; // Error!
	}

	// Done
	return bResult;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MaterialManager::MaterialManager(RendererContext &cRendererContext) :
	m_pRendererContext(&cRendererContext)
{
	PL_LOG(Debug, "Create material manager")

	// Set manager name
	SetManagerName("Material manager");

	// Unload unused resources, please
	SetUnloadUnused(true);

	// Load the standard material
	const TextureManager &cTM = cRendererContext.GetTextureManager();
	Material *pMaterial = LoadResource(cTM.GetStandard() ? cTM.GetStandard()->GetFilename() : TextureManager::Default);
	if (!pMaterial)
		pMaterial = CreateResource("StandardMaterial");
	if (pMaterial) {
		pMaterial->SetProtected(true);
		SetStandard(pMaterial);
	}
}

/**
*  @brief
*    Destructor
*/
MaterialManager::~MaterialManager()
{
	PL_LOG(Debug, "Destroy material manager")
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ResourceManager functions     ]
//[-------------------------------------------------------]
Material *MaterialManager::CreateResource(const String &sName)
{
	return new Material(*this, sName);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
