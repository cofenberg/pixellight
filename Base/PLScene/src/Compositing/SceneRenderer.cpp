/*********************************************************\
 *  File: SceneRenderer.cpp                              *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLCore/Base/Class.h>
#include "PLScene/Compositing/SceneRendererManager.h"
#include "PLScene/Compositing/SceneRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
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
	return static_cast<SceneRendererManager&>(*m_pManager);
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
		// (no hash map operation + quite efficient internal string comparison)
		static const Class *pBaseClass = ClassManager::GetInstance()->GetClass("PLScene::SceneRendererPass");

		// Get scene node plugin
		if (pBaseClass) {
			const Class *pClass = ClassManager::GetInstance()->GetClass(sClass);
			if (pClass && pClass->IsDerivedFrom(*pBaseClass)) {
				PL_LOG(Debug, "Create scene renderer pass '" + sName + "' of type '" + sClass + '\'')
				SceneRendererPass *pPass = static_cast<SceneRendererPass*>(pClass->Create());
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
	return nullptr;
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
	// Emit scene renderer destroyed event
	EventDestroyed();
}


//[-------------------------------------------------------]
//[ Private virtual SceneRenderer functions               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Draws the scene using this scene renderer
*/
void SceneRenderer::DrawScene(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Draw all scene renderer passes
	for (uint32 i=0; i<GetNumOfElements(); i++) {
		// Get the current pass
		SceneRendererPass *pPass = GetByIndex(i);

		// Do ONLY take it into account if it's valid and active
		if (pPass && pPass->IsActive())
			pPass->Draw(cRenderer, cCullQuery);
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
//[ Private virtual PLCore::ElementManager functions      ]
//[-------------------------------------------------------]
SceneRendererPass *SceneRenderer::CreateElement(const String &sName)
{
	return Create(sName, "");
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
