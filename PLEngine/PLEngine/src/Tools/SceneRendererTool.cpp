/*********************************************************\
 *  File: SceneRendererTool.cpp                          *
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
#include <PLRenderer/Renderer/SurfacePainter.h>
#include <PLScene/Compositing/SceneRenderer.h>
#include <PLScene/Scene/SPScene.h>
#include "PLEngine/Tools/SceneRendererTool.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLRenderer;
using namespace PLScene;
namespace PLEngine {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SceneRendererTool::SceneRendererTool(SurfacePainter *pSurfacePainter) :
	m_pSurfacePainter(pSurfacePainter)
{
}

/**
*  @brief
*    Destructor
*/
SceneRendererTool::~SceneRendererTool()
{
}

/**
*  @brief
*    Get surface painter
*/
SurfacePainter *SceneRendererTool::GetPainter() const
{
	// Return surface painter
	return m_pSurfacePainter;
}

/**
*  @brief
*    Set surface painter
*/
void SceneRendererTool::SetPainter(SurfacePainter *pSurfacePainter)
{
	// Set surface painter
	m_pSurfacePainter = pSurfacePainter;
}

/**
*  @brief
*    Returns the used scene renderer instance
*/
SceneRenderer *SceneRendererTool::GetSceneRenderer() const
{
	// Get the painter
	if (m_pSurfacePainter && m_pSurfacePainter->IsInstanceOf("PLScene::SPScene")) {
		// Return the default scene renderer
		return ((SPScene*)m_pSurfacePainter)->GetDefaultSceneRenderer();
	}

	// Error!
	return NULL;
}

/**
*  @brief
*    Gets a scene renderer pass
*/
SceneRendererPass *SceneRendererTool::GetPass(const String &sName) const
{
	// Get the scene renderer
	SceneRenderer *pSceneRenderer = GetSceneRenderer();
	if (pSceneRenderer) {
		// Return the requested scene renderer pass
		return pSceneRenderer->Get(sName);
	}

	// Error!
	return NULL;
}

/**
*  @brief
*    Gets a scene renderer pass attribute
*/
DynVar *SceneRendererTool::GetPassAttribute(const String &sSceneRendererPassName, const String &sAttributeName) const
{
	// Get the scene renderer pass
	SceneRendererPass *pSceneRendererPass = GetPass(sSceneRendererPassName);
	if (pSceneRendererPass) {
		// Get the attribute
		return pSceneRendererPass->GetAttribute(sAttributeName);
	}

	// Error!
	return NULL;
}

/**
*  @brief
*    Sets a scene renderer pass attribute value using a string
*/
bool SceneRendererTool::SetPassAttribute(const String &sSceneRendererPassName, const String &sAttributeName, const String &sValue) const
{
	// Get the scene renderer pass
	SceneRendererPass *pSceneRendererPass = GetPass(sSceneRendererPassName);
	if (pSceneRendererPass) {
		// Get the attribute
		DynVar *pDynVar = pSceneRendererPass->GetAttribute(sAttributeName);
		if (pDynVar) {
			// Set the value of the attribute using a string
			pDynVar->SetString(sValue);

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

/**
*  @brief
*    Sets scene renderer pass attribute values using a string
*/
uint32 SceneRendererTool::SetAttribute(const String &sAttributeName, const String &sValue) const
{
	uint32 nNumOfSetAttributes = 0;

	// Get the scene renderer
	SceneRenderer *pSceneRenderer = GetSceneRenderer();
	if (pSceneRenderer) {
		// Loop through all scene renderer passes
		for (uint32 nPass=0; nPass<pSceneRenderer->GetNumOfElements(); nPass++) {
			// Get the current scene renderer pass
			SceneRendererPass *pSceneRendererPass = pSceneRenderer->Get(nPass);
			if (pSceneRendererPass) {
				// Get the attribute
				DynVar *pDynVar = pSceneRendererPass->GetAttribute(sAttributeName);
				if (pDynVar) {
					// Set the value of the attribute using a string
					pDynVar->SetString(sValue);

					// Update the number of set attributes
					nNumOfSetAttributes++;
				}
			}
		}
	}

	// Done
	return nNumOfSetAttributes;
}

/**
*  @brief
*    Sets scene renderer pass attribute values using a string
*/
void SceneRendererTool::SetValues(const String &sValues) const
{
	// Get the scene renderer
	SceneRenderer *pSceneRenderer = GetSceneRenderer();
	if (pSceneRenderer) {
		// Loop through all scene renderer passes
		for (uint32 nPass=0; nPass<pSceneRenderer->GetNumOfElements(); nPass++) {
			// Get the current scene renderer pass
			SceneRendererPass *pSceneRendererPass = pSceneRenderer->Get(nPass);
			if (pSceneRendererPass) {
				// Set the values
				pSceneRendererPass->SetValues(sValues);
			}
		}
	}
}

/**
*  @brief
*    Sets all scene renderer pass attribute values to their default value
*/
void SceneRendererTool::SetDefaultValues() const
{
	// Get the scene renderer
	SceneRenderer *pSceneRenderer = GetSceneRenderer();
	if (pSceneRenderer) {
		// Loop through all scene renderer passes
		for (uint32 nPass=0; nPass<pSceneRenderer->GetNumOfElements(); nPass++) {
			// Get the current scene renderer pass
			SceneRendererPass *pSceneRendererPass = pSceneRenderer->Get(nPass);
			if (pSceneRendererPass) {
				// Set the values
				pSceneRendererPass->SetDefaultValues();
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
