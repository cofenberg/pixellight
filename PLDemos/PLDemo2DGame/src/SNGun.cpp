/*********************************************************\
 *  File: SNGun.cpp                                      *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneQueries/SQAABoundingBox.h>
#include <PLSound/Source.h>
#include "GunController.h"
#include "SNGun.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLInput;
using namespace PLSound;
using namespace PLScene;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNGun)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNGun::SNGun() :
	InputSemantic(this),
	Sound(this),
	Flags(this),
	EventHandlerOnSceneNode(&SNGun::OnSceneNode, this),
	m_pController(new GunController()),
	m_nFrame(0),
	m_fFrame(0.0f)
{
	// Overwrite the default setting of the flags
	SetFlags(GetFlags()|NoLoop|NoStartPlayback|No3D);

	// Overwritten PLSound::SNSound variables
	m_sSound = "Data/Sounds/Shot.ogg";

	// Set the bounding box
	SetAABoundingBox(AABoundingBox(-18.0f, -7.0f, -1.0f, 18.0f, 7.0f, 1.0f));
}

/**
*  @brief
*    Destructor
*/
SNGun::~SNGun()
{
	// Destroy the input controller
	delete m_pController;
}

/**
*  @brief
*    Returns the current frame
*/
char SNGun::GetFrame() const
{
	return m_nFrame;
}


//[-------------------------------------------------------]
//[ Public virtual PLScene::SceneNode functions           ]
//[-------------------------------------------------------]
Controller *SNGun::GetInputController() const
{
	return m_pController;
}


//[-------------------------------------------------------]
//[ Protected virtual PLScene::SceneNode functions        ]
//[-------------------------------------------------------]
void SNGun::InitFunction()
{
	// Call base implementation
	SNSound::InitFunction();

	// Emit the input controller found event of the scene context to tell everyone about our input controller
	GetSceneContext()->EventInputControllerFound.Emit(m_pController, InputSemantic);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when a scene node was found
*/
void SNGun::OnSceneNode(SceneQuery &cQuery, SceneNode &cSceneNode)
{
	// Is this gun still active?
	if (IsActive()) {
		// Is this a bomb?
		if (cSceneNode.IsInstanceOf("SNBomb")) {
			// Is the bomb still alive?
			if (!cSceneNode.GetAttribute("Killed")->GetBool()) {
				// Jap, kill the bomb right now
				cSceneNode.SetAttribute("Killed", "1");

				// Destroy this gun
				Delete();

				// Done, do NOT continue the query!
				cQuery.Stop();
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void SNGun::UpdateFunction()
{
	// Get time difference
	const float fTimeDiff = Timing::GetInstance()->GetTimeDifference();

	// Get X value
	float fDelta = m_pController->X.GetValue();

	// Left button pressed?
	if (m_pController->Left.IsPressed()) {
		fDelta = -6.0f;
	}

	// Right button pressed?
	if (m_pController->Right.IsPressed()) {
		fDelta = 6.0f;
	}

	// Move gun
	m_fFrame += fDelta * 3.0f * fTimeDiff;
	if (m_fFrame > 12.0f) m_fFrame = 12.0f;
	if (m_fFrame <  0.0f) m_fFrame =  0.0f;
	m_nFrame = (char)m_fFrame;

	// Create a projectile?
	if (m_pController->Fire.IsHit()) {
		// Get projectile start position in bitmap space
		Vector2 vPos;
		switch (m_nFrame) {
			case 0:  vPos.SetXY(0,  8); break;
			case 1:  vPos.SetXY(0,  6); break;
			case 2:  vPos.SetXY(0,  3); break;
			case 3:  vPos.SetXY(6,  0); break;
			case 4:  vPos.SetXY(11, 0); break;
			case 5:  vPos.SetXY(16, 0); break;
			case 6:  vPos.SetXY(18, 0); break;
			case 7:  vPos.SetXY(22, 0); break;
			case 8:  vPos.SetXY(25, 0); break;
			case 9:  vPos.SetXY(31, 0); break;
			case 10: vPos.SetXY(37, 3); break;
			case 11: vPos.SetXY(37, 6); break;
			case 12: vPos.SetXY(37, 8); break;
		}

		// Get real projective position
		vPos.x += GetTransform().GetPosition().x-18;
		vPos.y += GetTransform().GetPosition().y-6;

		// Get projective direction
		Vector2 vDir = Vector2(vPos.x-GetTransform().GetPosition().x, vPos.y-GetTransform().GetPosition().y-2).Normalize();

		// Create the projectile scene node
		GetContainer()->Create("SNProjectile", "", String::Format("Position=\"%g %g\" Direction=\"%g %g\"",
							   vPos.x, vPos.y, vDir.x, vDir.y));

		// Play sound
		Source *pSoundSource = GetSoundSource();
		if (pSoundSource)
			pSoundSource->Play(true);
	}

	// Collision detection
	// Create a new scene query we can use to check which scene nodes are within a given axis aligned bounding box
	SQAABoundingBox *pSceneQuery = (SQAABoundingBox*)GetContainer()->CreateQuery("PLScene::SQAABoundingBox");
	if (pSceneQuery) {
		// Connect event handler
		pSceneQuery->EventSceneNode.Connect(&EventHandlerOnSceneNode);

		// Setup axis aligned bounding box
		pSceneQuery->GetAABoundingBox() = GetContainerAABoundingBox();

		// Let's perform the query...
		pSceneQuery->PerformQuery();

		// ... and clean up if we are done, we don't use 'GetContainer()' in here because this node
		// can be destroyed inside our query
		pSceneQuery->GetSceneContainer().DestroyQuery(*pSceneQuery);
	}
}
