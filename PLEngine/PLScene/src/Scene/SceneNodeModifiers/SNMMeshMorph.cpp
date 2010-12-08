/*********************************************************\
 *  File: SNMMeshMorph.cpp                               *
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
#include <PLMesh/MeshHandler.h>
#include "PLScene/Scene/SceneNode.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMMeshMorph.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
using namespace PLMesh;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMMeshMorph)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String SNMMeshMorph::GetName() const
{
	return m_sName;
}

void SNMMeshMorph::SetName(const String &sValue)
{
	if (m_sName != sValue) {
		// Set new value
		m_sName = sValue;

		// Update morph target
		UpdateMorphTarget();
	}
}

float SNMMeshMorph::GetWeight() const
{
	return m_fWeight;
}

void SNMMeshMorph::SetWeight(float fValue)
{
	if (m_fWeight != fValue) {
		// Clamp the weight
		if (fValue < m_fMinWeight)
			fValue = m_fMinWeight;
		if (fValue > m_fMaxWeight)
			fValue = m_fMaxWeight;

		// Set new value
		m_fWeight = fValue;

		// Update morph target
		UpdateMorphTarget();
	}
}

float SNMMeshMorph::GetMinWeight() const
{
	return m_fMinWeight;
}

void SNMMeshMorph::SetMinWeight(float fValue)
{
	if (m_fMinWeight != fValue) {
		// Set new value
		m_fMinWeight = fValue;

		// Check minimum/maximum
		if (m_fMinWeight > m_fMaxWeight)
			m_fMinWeight = m_fMaxWeight;

		// Update weight
		SetWeight(GetWeight());
	}
}

float SNMMeshMorph::GetMaxWeight() const
{
	return m_fMaxWeight;
}

void SNMMeshMorph::SetMaxWeight(float fValue)
{
	if (m_fMaxWeight != fValue) {
		// Set new value
		m_fMaxWeight = fValue;

		// Check minimum/maximum
		if (m_fMaxWeight < m_fMinWeight)
			m_fMaxWeight = m_fMinWeight;

		// Update weight
		SetWeight(GetWeight());
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMMeshMorph::SNMMeshMorph(SceneNode &cSceneNode) : SNMMesh(cSceneNode),
	Name(this),
	Weight(this),
	MinWeight(this),
	MaxWeight(this),
	m_fWeight(0.0f),
	m_fMinWeight(0.0f),
	m_fMaxWeight(1.0f)
{
}

/**
*  @brief
*    Destructor
*/
SNMMeshMorph::~SNMMeshMorph()
{
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
void SNMMeshMorph::OnActivate(bool bActivate)
{
	if (bActivate)
		UpdateMorphTarget();
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Updates the morph target
*/
void SNMMeshMorph::UpdateMorphTarget()
{
	// Is this modifier active?
	if (IsActive()) {
		// Is there a mesh handler?
		MeshHandler *pMeshHandler = GetSceneNode().GetMeshHandler();
		if (pMeshHandler) {
			// Get the used mesh
			const Mesh *pMesh = pMeshHandler->GetResource();
			if (pMesh) {
				// Get the morph target index
				const int nIndex = pMesh->GetMorphTargetIndex(m_sName);
				if (nIndex >= 0) {
					// State change? We use the 'const'-version for this to avoid forcing a mesh update...
					const Array<float> &lstBaseMorphTargetWeights = ((const MeshHandler*)pMeshHandler)->GetBaseMorphTargetWeights();
					if (lstBaseMorphTargetWeights[nIndex] != m_fWeight) {
						// Get/create the mesh animation manager
						if (!pMeshHandler->GetMeshAnimationManager())
							pMeshHandler->CreateMeshAnimationManager();

						// Update the morph target weight
						pMeshHandler->GetBaseMorphTargetWeights()[nIndex] = m_fWeight;

						// Ensure that there's a "PLScene::SNMMeshUpdate" instance within the owner scene node which takes care of the frequent mesh update
						if (m_fWeight)
							GetSNMMeshUpdate();
					}
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
