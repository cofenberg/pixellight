/*********************************************************\
 *  File: SNMPostProcess.cpp                             *
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
#include <PLRenderer/Material/Material.h>
#include <PLRenderer/Material/Parameter.h>
#include <PLScene/Scene/SceneNode.h>
#include <PLScene/Scene/SceneContext.h>
#include "PLCompositing/Shaders/PostProcessing/PostProcessManager.h"
#include "PLCompositing/SceneNodeModifiers/SNMPostProcess.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPostProcess)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String SNMPostProcess::GetFilename() const
{
	return m_sFilename;
}

void SNMPostProcess::SetFilename(const String &sValue)
{
	if (m_sFilename != sValue) {
		m_sFilename = sValue;
		if (m_pPostProcessManager)
			m_pPostProcessManager->Load(m_sFilename);
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the post process manager
*/
PostProcessManager &SNMPostProcess::GetPostProcessManager()
{
	// Create the post process manager instance right now?
	if (!m_pPostProcessManager) {
		m_pPostProcessManager = new PostProcessManager(GetSceneNode().GetSceneContext()->GetRendererContext());
		if (m_sFilename.GetLength())
			m_pPostProcessManager->Load(m_sFilename);
	}

	// Return the post process manager instance
	return *m_pPostProcessManager;
}

/**
*  @brief
*    Returns a post process effect parameter
*/
Parameter *SNMPostProcess::GetParameter(const String &sName, uint32 nIndex, bool bActiveOnly)
{
	// Get post process
	const PostProcess *pPostProcess = GetPostProcessManager().GetByIndex(nIndex);
	if (pPostProcess && (!bActiveOnly || pPostProcess->IsActive())) {
		// Get material
		const Material *pMaterial = pPostProcess->GetMaterial();
		if (pMaterial)
			return pMaterial->GetParameter(sName);
	}

	// Error!
	return nullptr;
}

/**
*  @brief
*    Returns all post process effect parameters of a given parameter name
*/
bool SNMPostProcess::GetParameters(const String &sName, Array<Parameter*> &lstParameters, bool bActiveOnly)
{
	// Loop through all post processes
	PostProcessManager &cPostProcessManager = GetPostProcessManager();
	for (uint32 nPostProcess=0; nPostProcess<cPostProcessManager.GetNumOfElements(); nPostProcess++) {
		const PostProcess *pPostProcess = cPostProcessManager.GetByIndex(nPostProcess);
		if (!bActiveOnly || pPostProcess->IsActive()) {
			// Get material
			const Material *pMaterial = pPostProcess->GetMaterial();
			if (pMaterial) {
				// Get the parameter
				Parameter *pParameter = pMaterial->GetParameter(sName);
				if (pParameter)
					lstParameters.Add(pParameter);
			}
		}
	}

	// Done
	return (lstParameters.GetNumOfElements() != 0);
}


//[-------------------------------------------------------]
//[ Public virtual functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets all current parameter values as current post process settings
*/
void SNMPostProcess::SetParameters()
{
	// Set all EffectWeight to 1, except for the last effect
	PostProcessManager &cPostProcessManager = GetPostProcessManager();
	const uint32 nNumOfPostProcesses = cPostProcessManager.GetNumOfElements();
	for (uint32 nPostProcess=0; nPostProcess<nNumOfPostProcesses; nPostProcess++) {
		const PostProcess *pPostProcess = cPostProcessManager.GetByIndex(nPostProcess);

		// Get material
		const Material *pMaterial = pPostProcess->GetMaterial();
		if (pMaterial) {
			// Get the parameter
			Parameter *pParameter = pMaterial->GetParameter("EffectWeight");
			if (pParameter)
				pParameter->SetValue1f((nPostProcess == nNumOfPostProcesses-1) ? EffectWeight : 1.0f);
		}
	}
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcess::SNMPostProcess(SceneNode &cSceneNode) : SceneNodeModifier(cSceneNode),
	Filename(this),
	EffectWeight(this),
	m_pPostProcessManager(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
SNMPostProcess::~SNMPostProcess()
{
	// Destroy the post process manager instance, if there's one
	if (m_pPostProcessManager)
		delete m_pPostProcessManager;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
