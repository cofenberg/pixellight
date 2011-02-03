/*********************************************************\
 *  File: MeshAnimationManager.cpp                       *
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
#include <PLRenderer/Animation/Animation.h>
#include "PLMesh/MeshManager.h"
#include "PLMesh/MorphTargetAni.h"
#include "PLMesh/SkeletonManager.h"
#include "PLMesh/MeshAnimationManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace PLMesh {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(MeshAnimationManager)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns whether the mesh animation manager will reset the current joint states
*    within the Apply() function before the current animation states are applied
*/
bool MeshAnimationManager::GetResetJointStates() const
{
	return m_bResetJointStates;
}

/**
*  @brief
*    Sets whether the mesh animation manager will reset the current joint states
*    within the Apply() function before the current animation states are applied
*/
void MeshAnimationManager::SetResetJointStates(bool bReset)
{
	m_bResetJointStates = bReset;
}

/**
*  @brief
*    Returns whether the mesh animation manager will reset the current morph weights
*    within the Apply() function before the current animation weights are applied
*/
bool MeshAnimationManager::GetResetMorphWeights() const
{
	return m_bResetMorphWeights;
}

/**
*  @brief
*    Sets whether the mesh animation manager will reset the current morph weights
*    within the Apply() function before the current animation weights are applied
*/
void MeshAnimationManager::SetResetMorphWeights(bool bReset)
{
	m_bResetMorphWeights = bReset;
}

/**
*  @brief
*    Returns whether the mesh animation manager will apply base joint states before calculating
*    the current states
*/
bool MeshAnimationManager::GetApplyBaseJointStates() const
{
	return m_bApplyBaseJointStates;
}

/**
*  @brief
*    Sets whether the mesh animation manager will apply base joint states before calculating
*    the current states
*/
void MeshAnimationManager::SetApplyBaseJointStates(bool bApply)
{
	m_bApplyBaseJointStates = bApply;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
MeshAnimationManager::MeshAnimationManager() :
	m_bResetJointStates(true),
	m_bResetMorphWeights(true),
	m_bApplyBaseJointStates(true)
{
	// Init data
	SetManagerName("Mesh animation manager");
}

/**
*  @brief
*    Destructor
*/
MeshAnimationManager::~MeshAnimationManager()
{
}


//[-------------------------------------------------------]
//[ Public virtual functions                              ]
//[-------------------------------------------------------]
bool MeshAnimationManager::Update(float fTimeDifference)
{
	// Update all animations
	for (uint32 i=0; i<m_lstElements.GetNumOfElements(); i++)
		m_lstElements[i]->Update(fTimeDifference);

	// Done
	return true;
}

bool MeshAnimationManager::Apply(MeshHandler &cMeshHandler) const
{
	// Get mesh
	Mesh *pMesh = cMeshHandler.GetResource();
	if (pMesh) {
		// Check if there's a skeleton handler
		SkeletonHandler *pSH = cMeshHandler.GetSkeletonHandler();

		// Reset current joint states
		if (pSH && m_bResetJointStates)
			pSH->ResetJointStates();

		// Reset current morph target weights
		if (m_bResetMorphWeights)
			cMeshHandler.GetMorphTargetWeights() = cMeshHandler.GetBaseMorphTargetWeights();

		// Get the skeleton manager
		SkeletonManager &cSkeletonManager = pMesh->GetMeshManager()->GetSkeletonManager();

		// Loop through all animations
		for (uint32 i=0; i<m_lstElements.GetNumOfElements(); i++) {
			// Get animation and check if we have to add it
			const Animation *pAnimation = m_lstElements[i];
			if (pAnimation->IsActive()) {
				// Check animation type
				switch (pAnimation->GetType()) {
					case 0: // Skeleton
						// No skeleton handler, no skeleton animation :(
						if (pSH) {
							// Get skeleton
							const Skeleton *pSkeleton;
							if (pAnimation->GetAnimation() && pAnimation->GetAnimation()->GetSourceName().GetLength())
								pSkeleton = cSkeletonManager.Get(pAnimation->GetAnimation()->GetSourceName());
							else
								pSkeleton = cSkeletonManager.Get(pAnimation->GetName());
							if (pSkeleton) {
								// Add animation
								pSkeleton->ApplyJointStates(pSH->GetJointHandlers(),
															pAnimation->GetCurrentFrame(),
															pAnimation->GetNextFrame(),
															pAnimation->GetProgress(),
															pAnimation->GetWeight());
							}
						}
						break;

					case 1: // Vertex
					{
						// Get morph target animation
						const MorphTargetAni *pMorphTargetAni;
						if (pAnimation->GetAnimation() && pAnimation->GetAnimation()->GetSourceName().GetLength())
							pMorphTargetAni = pMesh->GetMorphTargetAnimationManager().Get(pAnimation->GetAnimation()->GetSourceName());
						else
							pMorphTargetAni = pMesh->GetMorphTargetAnimationManager().Get(pAnimation->GetName());
						if (pMorphTargetAni) {
							// Add animation
							pMorphTargetAni->ApplyMorphTargetWeight(cMeshHandler.GetMorphTargetWeights(),
																	pAnimation->GetCurrentFrame(),
																	pAnimation->GetNextFrame(),
																	pAnimation->GetProgress(),
																	pAnimation->GetWeight(),
																	pMesh);
						}
						break;
					}
				}
			}
		}

		// Complete skeleton handler states
		if (pSH) {
			// Apply base joint states to get the final pose
			if (m_bApplyBaseJointStates)
				pSH->ApplyBaseJointStates();

			// Complete the current joint states
			pSH->CalculateStates();
		}

		// Done
		return true;
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh
