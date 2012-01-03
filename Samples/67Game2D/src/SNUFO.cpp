/*********************************************************\
 *  File: SNUFO.cpp                                      *
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
#include <PLCore/Tools/Timing.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLSound/Source.h>
#include "SNUFO.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLScene;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNUFO)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNUFO::SNUFO() :
	Sound(this),
	SlotOnUpdate(this),
	m_fTimer(0.0f),
	m_fBombTimer(0.0f)
{
	// Overwritten PLSound::SNSound variables
	m_sSound = "Data/Sounds/UFO.ogg";

	// Overwrite the default setting of the flags
	SetFlags(GetFlags()|No3D);

	// Set the bounding box
	SetAABoundingBox(AABoundingBox(-25.0f, -10.0f, -1.0f, 25.0f, 10.0f, 1.0f));
}

/**
*  @brief
*    Destructor
*/
SNUFO::~SNUFO()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNUFO::OnUpdate()
{
	// Get time difference
	const float fTimeDiff = Timing::GetInstance()->GetTimeDifference();

	// Update timer
	m_fTimer += fTimeDiff/2;

	// Update position
	GetTransform().SetPosition(Vector3(160 + Math::Sin(m_fTimer)*130, 20.0f + Math::Cos(m_fTimer*10)*5, 0.0f));

	// Update the bomb timer
	m_fBombTimer += fTimeDiff*2;
	if (m_fBombTimer >= 1.0f) {
		m_fBombTimer = 0.0f;
		// Drop a bomb?
		if (!(Math::GetRand() % 3))
			GetContainer()->Create("SNBomb", "", String::Format("Position=\"%g %g\"", GetTransform().GetPosition().x+18, GetTransform().GetPosition().y+10));
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void SNUFO::OnActivate(bool bActivate)
{
	// Call the base implementation
	SNSound::OnActivate(bActivate);

	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate) {
			pSceneContext->EventUpdate.Connect(SlotOnUpdate);

			// Make a first update to ensure everything is up-to-date when we're going active (synchronization and logic update)
			OnUpdate();
		} else {
			pSceneContext->EventUpdate.Disconnect(SlotOnUpdate);
		}
	}
}
