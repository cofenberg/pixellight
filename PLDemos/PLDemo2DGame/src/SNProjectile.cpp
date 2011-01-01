/*********************************************************\
 *  File: SNProjectile.cpp                               *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneQueries/SQAABoundingBox.h>
#include "SNProjectile.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLScene;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNProjectile)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNProjectile::SNProjectile() :
	Direction(this),
	EventHandlerUpdate(&SNProjectile::NotifyUpdate, this),
	EventHandlerSceneNode(&SNProjectile::NotifySceneNode, this)
{
	// Set the bounding box
	SetAABoundingBox(AABoundingBox(-3.0f, -3.0f, -1.0f, 3.0f, 3.0f, 1.0f));
}

/**
*  @brief
*    Destructorja
*/
SNProjectile::~SNProjectile()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNProjectile::NotifyUpdate()
{
	// Get time difference
	const float fTimeDiff = Timing::GetInstance()->GetTimeDifference();

	// Update the bomb timer
	GetTransform().SetPosition(GetTransform().GetPosition() + Vector3(Direction.Get().x, Direction.Get().y, 0.0f)*fTimeDiff*100);

	// Has the projectile left the screen?
	if (GetTransform().GetPosition().x < -3  || GetTransform().GetPosition().y < -3 || GetTransform().GetPosition().x > 323 || GetTransform().GetPosition().y > 203) {
		Delete(); // Destroy the projectile

	// Collision detection
	} else {
		// Create a new scene query we can use to check which scene nodes are within a given axis aligned bounding box
		SQAABoundingBox *pSceneQuery = (SQAABoundingBox*)GetContainer()->CreateQuery("PLScene::SQAABoundingBox");
		if (pSceneQuery) {
			// Connect event handler
			pSceneQuery->EventSceneNode.Connect(&EventHandlerSceneNode);

			// Setup axis aligned bounding box
			pSceneQuery->GetAABoundingBox() = GetContainerAABoundingBox();

			// Let's perform the query...
			pSceneQuery->PerformQuery();

			// ... and clean up if we are done, we don't use 'GetContainer()' in here because this node
			// can be destroyed inside our query
			pSceneQuery->GetSceneContainer().DestroyQuery(*pSceneQuery);
		}
	}
}

/**
*  @brief
*    Called when a scene node was found
*/
void SNProjectile::NotifySceneNode(SceneQuery &cQuery, SceneNode &cSceneNode)
{
	// Is this projectile still active?
	if (IsActive()) {
		// Is this a bomb?
		if (cSceneNode.IsInstanceOf("SNBomb")) {
			// Is the bomb still alive?
			if (!cSceneNode.GetAttribute("Killed")->GetBool()) {
				// Jap, kill the bomb right now
				cSceneNode.SetAttribute("Killed", "1");

				// Destroy this projectile
				Delete();

				// Done, do NOT continue the query!
				cQuery.Stop();
			}

		// Is this the UFO? (can not be killed :)
		} else if (cSceneNode.IsInstanceOf("SNUFO")) {
			// Jap, destroy this projectile
			Delete();

			// Done, do NOT continue the query!
			cQuery.Stop();
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void SNProjectile::OnActivate(bool bActivate)
{
	// Call the base implementation
	SceneNode::OnActivate(bActivate);

	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate)
			pSceneContext->EventUpdate.Connect(&EventHandlerUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(&EventHandlerUpdate);
	}
}

