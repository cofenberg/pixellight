/*********************************************************\
 *  File: SceneRenderer.cpp                              *
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
#include <PLGeneral/Log/Log.h>
#include <PLRenderer/Renderer/Renderer.h>

// [TODO] Remove this!
//#include "PLScene/Compositing/General/SRPLightEffects.h"

// [TODO] Remove this!
//#include "PLScene/Compositing/General/SRPPostProcessing.h"

#include "PLScene/Compositing/SceneRendererManager.h"
#include "PLScene/Compositing/SceneRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the scene renderer manager this scene renderer is in
*/
SceneRendererManager &SceneRenderer::GetSceneRendererManager() const
{
	// There MUST always be a manager!
	return (SceneRendererManager&)*m_pManager;
}

/**
*  @brief
*    Creates a new scene node
*/
SceneRendererPass *SceneRenderer::Create(const String &sClass, const String &sName, const String &sParameters)
{
	// Check parameter
	if (sClass.GetLength()) {
		// To keep things as fast as possible we store a pointer to the base class
		// (no hash map operation + quite efficent internal string comparison)
		static const Class *pBaseClass = ClassManager::GetInstance()->GetClass("PLScene::SceneRendererPass");

		// Get scene node plugin
		if (pBaseClass) {
			const Class *pClass = ClassManager::GetInstance()->GetClass(sClass);
			if (pClass && pClass->IsDerivedFrom(*pBaseClass)) {
				PL_LOG(Debug, "Create scene renderer pass '" + sName + "' of type '" + sClass + "'")
				SceneRendererPass *pPass = (SceneRendererPass*)pClass->Create();
				if (pPass) {
					if (sParameters.GetLength())
						pPass->SetValues(sParameters);
					pPass->SetName(sName);
					Add(*pPass);
				}

				// Return the created scene renderer pass
				return pPass;
			} else { // Plugin not found
				PL_LOG(Error, "Unknown scene renderer pass type: " + sClass)
			}
		}
	}

	// Error
	return NULL;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SceneRenderer::SceneRenderer(SceneRendererManager &cManager, const String &sName) : PLCore::Resource<SceneRenderer>(sName, &cManager)
{
}

/**
*  @brief
*    Destructor
*/
SceneRenderer::~SceneRenderer()
{
}

/**
*  @brief
*    Draws a scene renderer pass
*/
void SceneRenderer::DrawPass(Renderer &cRenderer, const SQCull &cCullQuery, SceneRendererPass &cPass)
{
	cPass.Draw(cRenderer, cCullQuery);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets another render target if required
*/
bool SceneRenderer::SetRenderTarget(Renderer &cRenderer)
{
	// [TODO] Remove this!
//	SRPPostProcessing *pSRPPostProcessing = (SRPPostProcessing*)Get("PostProcessing");
//	return (pSRPPostProcessing && pSRPPostProcessing->IsActive() && pSRPPostProcessing->IsInstanceOf("PLCompositing::SRPPostProcessing")) ? pSRPPostProcessing->SetRenderTarget(cRenderer) : true;
	return true;
}

/**
*  @brief
*    Draws the scene using this scene renderer
*/
void SceneRenderer::DrawScene(Renderer &cRenderer, const SQCull &cCullQuery)
{
	/*
	// [TODO] Remove this!
	// [TODO] Solve this within another, universal way!
	// Get 'light effects' scene render pass
	SceneRendererPass *pSRPSolidFunctions = NULL;
	SRPLightEffects   *pSRPLightEffects   = (SRPLightEffects*)Get("LightEffects");
	if (pSRPLightEffects && pSRPLightEffects->IsInstanceOf("PLCompositing::SRPLightEffects") && pSRPLightEffects->IsActive())
		pSRPSolidFunctions = Get("FunctionsSolid");
	else
		pSRPLightEffects = NULL;
*/

	// Draw all scene renderer passes
	for (uint32 i=0; i<GetNumOfElements(); i++) {
		// Get the current pass
		SceneRendererPass *pPass = Get(i);

		// [TODO] Remove this!
		// Can we now prepare the light effects scene render pass?
//		if (pPass == pSRPSolidFunctions && pSRPLightEffects)
//			pSRPLightEffects->Prepare(cRenderer, cCullQuery);

		// Do ONLY take it into account if it's valid and active
		if (pPass && pPass->IsActive())
			DrawPass(cRenderer, cCullQuery, *pPass);
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Loadable functions             ]
//[-------------------------------------------------------]
bool SceneRenderer::Unload()
{
	// Cleanup
	Clear();

	// Call base implementation
	return PLCore::Resource<SceneRenderer>::Unload();
}

String SceneRenderer::GetLoadableTypeName() const
{
	static const String sString = "SceneRenderer";
	return sString;
}


//[-------------------------------------------------------]
//[ Private virtual PLGeneral::ElementManager functions   ]
//[-------------------------------------------------------]
SceneRendererPass *SceneRenderer::CreateElement(const String &sName)
{
	return Create(sName, "");
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
