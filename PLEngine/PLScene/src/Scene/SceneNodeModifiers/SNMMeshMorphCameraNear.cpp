/*********************************************************\
 *  File: SNMMeshMorphCameraNear.cpp                     *
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
#include "PLScene/Scene/SNCamera.h"
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNodes/SNMesh.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMMeshMorphCameraNear.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMMeshMorphCameraNear)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMMeshMorphCameraNear::SNMMeshMorphCameraNear(SceneNode &cSceneNode) : SNMMeshMorph(cSceneNode),
	Joint(this),
	Distance(this),
	InSpeed(this),
	OutSpeed(this),
	EventHandlerUpdate(&SNMMeshMorphCameraNear::OnUpdate, this)
{
}

/**
*  @brief
*    Destructor
*/
SNMMeshMorphCameraNear::~SNMMeshMorphCameraNear()
{
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
void SNMMeshMorphCameraNear::OnActivate(bool bActivate)
{
	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate)
			pSceneContext->EventUpdate.Connect(EventHandlerUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(EventHandlerUpdate);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node modifier needs to be updated
*/
void SNMMeshMorphCameraNear::OnUpdate()
{
	// Get camera
	const SNCamera *pCamera = SNCamera::GetCamera();
	if (pCamera) {
		// Get joint position in world space
		Vector3 vPosition;
		if (!Joint.Get().GetLength() || !static_cast<SNMesh&>(GetSceneNode()).GetSkeletonJointWorldPosition(Joint.Get(), vPosition))
			vPosition = GetSceneNode().GetTransform().GetPosition();

		// Update the morph target weight
		const float fDistance       = pCamera->GetTransform().GetPosition().GetDistance(vPosition);
		const float fPreviousWeight = m_fWeight;
		const float fTimeDiff       = Timing::GetInstance()->GetTimeDifference();
		if (fDistance < Distance) {
			m_fWeight += fTimeDiff*InSpeed;
			if (m_fWeight > m_fMaxWeight)
				m_fWeight = m_fMaxWeight;
		} else {
			m_fWeight -= fTimeDiff*OutSpeed;
			if (m_fWeight < m_fMinWeight)
				m_fWeight = m_fMinWeight;
		}

		// Update the morph target if required
		if (fPreviousWeight != m_fWeight)
			UpdateMorphTarget();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
