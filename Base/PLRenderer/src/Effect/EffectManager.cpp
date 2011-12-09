/*********************************************************\
 *  File: EffectManager.cpp                              *
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
#include "PLRenderer/Effect/EffectTechnique.h"
#include "PLRenderer/Effect/EffectHandler.h"
#include "PLRenderer/Effect/EffectManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const String EffectManager::Default = "Default";


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Reloads all effects
*/
bool EffectManager::ReloadEffects()
{
	bool bResult = true; // No error by default

	for (uint32 i=0; i<m_lstResources.GetNumOfElements(); i++) {
		Effect *pFX = m_lstResources[i];
		if (!pFX->Reload())
			bResult = false; // Error!
	}

	// Done
	return bResult;
}

/**
*  @brief
*    Uses a given effect
*/
bool EffectManager::Use(const String &sName)
{
	Effect *pFX = LoadResource(sName);
	if (pFX) {
		const EffectTechnique *pTechnique = pFX->GetSelectedTechnique();
		if (pTechnique)
			pTechnique->SetupPass(0);

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
EffectManager::EffectManager(RendererContext &cRendererContext) :
	m_pRendererContext(&cRendererContext),
	m_pDefault(new EffectHandler())
{
	PL_LOG(Debug, "Create effect manager")

	// Set manager name
	SetManagerName("Effect manager");

	// Unload unused resources, please
	SetUnloadUnused(true);

	// Create the standard effect
	Effect *pFX = CreateResource(Default);
	if (pFX) {
		// Create the effect
		EffectTechnique *pEffectTechnique = pFX->AddTechnique();
		if (pEffectTechnique) {
			pEffectTechnique->AddPass();
			pFX->SelectTechnique(0);
		}

		// Setup effect
		pFX->SetProtected(true);
		m_pDefault->SetResource(pFX);
		SetStandard(pFX);
	}
}

/**
*  @brief
*    Destructor
*/
EffectManager::~EffectManager()
{
	PL_LOG(Debug, "Destroy effect manager")

	// Cleanup
	delete m_pDefault;
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ResourceManager functions     ]
//[-------------------------------------------------------]
Effect *EffectManager::CreateResource(const String &sName)
{
	return new Effect(*this, sName);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
