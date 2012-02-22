/*********************************************************\
 *  File: SceneCreator.cpp                               *
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
#include <PLCore/Base/Class.h>
#include <PLScene/Scene/SceneContainer.h>
#include "PLEngine/SceneCreator/SceneCreator.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLScene;
namespace PLEngine {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SceneCreator)


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Configures a generic scene
*/
SNCamera *SceneCreator::ConfigureGenericScene(SceneContainer &cSceneContainer, SceneNode *pPrimarySceneNode)
{
	// Add a directional light source scene node named "Light"
	cSceneContainer.Create("PLScene::SNDirectionalLight", "Light", "Rotation=\"45 0 0\"");

	// Add a free camera scene node named "Camera"
	SceneNode *pFreeCamera = cSceneContainer.Create("PLScene::SNCamera", "Camera");
	if (pFreeCamera) {
		// Add a controller modifier so we can look around the camera by using a default control
		pFreeCamera->AddModifier("PLEngine::SNMEgoLookController");

		// Add a controller modifier so we can move around the camera by using a default control
		pFreeCamera->AddModifier("PLEngine::SNMMoveController");
	}

	// If primary scene node given, add an orbiter camera scene node named "OrbiterCamera"
	SceneNode *pOrbitingCamera = pPrimarySceneNode ? cSceneContainer.Create("PLScene::SNCamera", "OrbiterCamera") : nullptr;
	if (pOrbitingCamera) {
		// Get the axis align bounding box (in 'scene container space') from the primary scene node
		const AABoundingBox &cAABoundingBox = pPrimarySceneNode->GetContainerAABoundingBox();

		// Get orbiting distance, use the axis align bounding box (in 'scene container space') from the primary scene node as hint
		const float fDistance = cAABoundingBox.GetLongestAxisLength()*2;

		// Calculate the orbiting offset, use the axis align bounding box (in 'scene container space') from the primary scene node as hint
		const Vector3 vOffset = cAABoundingBox.GetCenter();

		// Add a controller modifier so we can orbiting around the camera by using a default control
		pOrbitingCamera->AddModifier("PLEngine::SNMEgoOrbitingController", "Target=\"" + pPrimarySceneNode->GetAbsoluteName() + "\" Distance=\"" + fDistance + "\" Offset=\"" + vOffset.ToString() + '\"');

		// Give the free camera the same position and rotation as used for the orbiting camera
		if (pFreeCamera)
			pFreeCamera->GetTransform() = pOrbitingCamera->GetTransform();
	}

	// Return the preferred camera scene node
	return reinterpret_cast<SNCamera*>(pOrbitingCamera ? pOrbitingCamera : pFreeCamera);
}

/**
*  @brief
*    Configures a scene
*/
SNCamera *SceneCreator::ConfigureScene(SceneContainer &cSceneContainer, const String &sClass, const String &sParameters)
{
	// Check parameter
	if (sClass.GetLength()) {
		// To keep things as fast as possible we store a pointer to the base class
		// (no hash map operation + quite efficient internal string comparison)
		static const Class *pBaseClass = ClassManager::GetInstance()->GetClass("PLEngine::SceneCreator");
		if (pBaseClass) {
			const Class *pClass = ClassManager::GetInstance()->GetClass(sClass);
			if (pClass && pClass->IsDerivedFrom(*pBaseClass)) {
				// Create the scene creator instance
				SceneCreator *pSceneCreator = static_cast<SceneCreator*>(pClass->Create());
				if (pSceneCreator) {
					// In case parameters are provided, set them
					if (sParameters.GetLength())
						pSceneCreator->SetValues(sParameters);

					// Configure the scene
					SNCamera *pSNCamera = pSceneCreator->Create(cSceneContainer);

					// Destroy the scene creator instance
					delete pSceneCreator;

					// Return the preferred camera scene node
					return pSNCamera;
				}
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
*    Default constructor
*/
SceneCreator::SceneCreator()
{
}

/**
*  @brief
*    Destructor
*/
SceneCreator::~SceneCreator()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
