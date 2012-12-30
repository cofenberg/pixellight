/*********************************************************\
 *  File: SNSystem.cpp                                   *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/Timing.h>
#include <PLMath/Math.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Visibility/VisNode.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4530) // "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	#include <SPK.h>
PL_WARNING_POP
#include "SPARK_PL/PLSceneNodes/SNSystem.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLScene;
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNSystem)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNSystem::SNSystem() :
	Flags(this),
	EventHandlerUpdate(&SNSystem::NotifyUpdate, this),
	m_pParticleSystem(nullptr),
	m_bUpdate(false)
{
	// Set draw function flags
	SetDrawFunctionFlags(uint8(GetDrawFunctionFlags() | UseDrawTransparent));
}

/**
*  @brief
*    Destructor
*/
SNSystem::~SNSystem()
{
	// Cleanup
	if (m_pParticleSystem)
		delete m_pParticleSystem;
}


//[-------------------------------------------------------]
//[ Public virtual PLScene::SceneNode functions           ]
//[-------------------------------------------------------]
void SNSystem::DrawTransparent(Renderer &cRenderer, const VisNode *pVisNode)
{
	if (m_pParticleSystem) {
		// Get the fixed functions interface
		FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
		if (pFixedFunctions) {
			cRenderer.GetRendererContext().GetEffectManager().Use();

			// Set the current world matrix
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, pVisNode->GetWorldMatrix());

			// Draw the SPARK particle system
			m_pParticleSystem->render();
		}
	}
}


//[-------------------------------------------------------]
//[ Protected virtual SNSystem functions                  ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called just before the particle system is updated
*/
void SNSystem::Update()
{
	// The default implementation is empty
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void SNSystem::OnActivate(bool bActivate)
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

void SNSystem::UpdateAABoundingBox()
{
	// Is the computation of the axis aligned bounding box enabled?
	if (m_pParticleSystem && m_pParticleSystem->isAABBComputingEnabled() && !(GetFlags() & NoAutomaticAABB)) {
		// Get the minimum/maximum of the axis aligned bounding box (in 'scene node space')
		const SPK::Vector3D &vAABBMin = m_pParticleSystem->getAABBMin();
		const SPK::Vector3D &vAABBMax = m_pParticleSystem->getAABBMax();

		// Set the new axis aligned bounding box
		SetAABoundingBox(AABoundingBox(vAABBMin.x, vAABBMin.y, vAABBMin.z, vAABBMax.x, vAABBMax.y, vAABBMax.z));
	}
}

void SNSystem::OnAddedToVisibilityTree(VisNode &cVisNode)
{
	m_bUpdate = true;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNSystem::NotifyUpdate()
{
	// If this scene node wasn't drawn at the last frame, we can skip some update stuff
	if (m_pParticleSystem && ((GetFlags() & UpdateInvisible) || m_bUpdate)) {
		m_bUpdate = false;

		// Give the derived systems an update change
		Update();

		// Get the current time difference
		const float fTimeDiff = Timing::GetInstance()->GetTimeDifference();

		// Update the SPARK particle system
		m_pParticleSystem->update(fTimeDiff);

		// We have to recalculate the current axis align bounding box in 'scene node space'
		if (m_pParticleSystem->isAABBComputingEnabled() && !(GetFlags() & NoAutomaticAABB))
			DirtyAABoundingBox();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL
