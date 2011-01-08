/*********************************************************\
 *  File: MorphTargetAni.cpp                             *
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
#include "PLMesh/Mesh.h"
#include "PLMesh/MorphTargetAni.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLMesh {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MorphTargetAni::MorphTargetAni(const String &sName, ElementManager<MorphTargetAni> *pManager) :
	Element<MorphTargetAni>(sName, pManager), AnimationBase()
{
}

/**
*  @brief
*    Destructor
*/
MorphTargetAni::~MorphTargetAni()
{
}

/**
*  @brief
*    Returns the morph target animation morph targets
*/
Array<MorphTargetAni::AniMorphTarget> &MorphTargetAni::GetMorphTargets()
{
	return m_lstAniMorphTargets;
}

/**
*  @brief
*    Applies the morph target weight from the given morph target frame
*    to the given morph target weights
*/
bool MorphTargetAni::ApplyMorphTargetWeight(Array<float> &lstMorphTargetWeights,
											uint32 nFrame, float fWeight, const Mesh *pMesh) const
{
	// Check weight of this states
	if (fWeight) {
		// Check size of the given weights list
		if (pMesh) {
			if (lstMorphTargetWeights.GetNumOfElements() < pMesh->GetNumOfMorphTargets())
				lstMorphTargetWeights.Resize(pMesh->GetNumOfMorphTargets());
		} else {
			if (lstMorphTargetWeights.GetNumOfElements() < m_lstAniMorphTargets.GetNumOfElements())
				lstMorphTargetWeights.Resize(m_lstAniMorphTargets.GetNumOfElements());
		}

		// Are there any weights?
		if (lstMorphTargetWeights.GetNumOfElements()) {
			// Get the frame keys
			const FrameKeys &cFrameKeys = m_lstFrameKeys[nFrame];
			if (&cFrameKeys == &Array<FrameKeys>::Null)
				return false; // Error!

			// Get frame
			const Array<float> &lstFrameKeysT = cFrameKeys.lstFrameKeys;

			// Loop through all morph targets and add weights
			if (pMesh) {
				for (uint32 i=0; i<m_lstAniMorphTargets.GetNumOfElements(); i++) {
					const int nIndex = pMesh->GetMorphTargetIndex(m_lstAniMorphTargets[i].sName);
					if (nIndex >= 0 && lstMorphTargetWeights[nIndex])
						lstMorphTargetWeights[nIndex] += lstFrameKeysT[i]*fWeight;
				}
			} else {
				for (uint32 i=0; i<m_lstAniMorphTargets.GetNumOfElements(); i++)
					lstMorphTargetWeights[i] += lstFrameKeysT[i]*fWeight;
			}
		}
	}

	// Done
	return true;
}

/**
*  @brief
*    Applies the blended morph target weight from the given morph target frames
*    to the given morph target weights
*/
bool MorphTargetAni::ApplyMorphTargetWeight(Array<float> &lstMorphTargetWeights,
											uint32 nFrame1, uint32 nFrame2, float fTime,
											float fWeight, const Mesh *pMesh) const
{
	// Check weight of this states
	if (fWeight) {
		// Check size of the given weights list
		if (pMesh) {
			if (lstMorphTargetWeights.GetNumOfElements() < pMesh->GetNumOfMorphTargets())
				lstMorphTargetWeights.Resize(pMesh->GetNumOfMorphTargets());
		} else {
			if (lstMorphTargetWeights.GetNumOfElements() < m_lstAniMorphTargets.GetNumOfElements())
				lstMorphTargetWeights.Resize(m_lstAniMorphTargets.GetNumOfElements());
		}

		// Are there any weights?
		if (lstMorphTargetWeights.GetNumOfElements()) {
			// Get the frame keys
			const FrameKeys &cFrame1Keys = m_lstFrameKeys[nFrame1];
			if (&cFrame1Keys == &Array<FrameKeys>::Null)
				return false; // Error!
			const FrameKeys &cFrame2Keys = m_lstFrameKeys[nFrame2];
			if (&cFrame2Keys == &Array<FrameKeys>::Null)
				return false; // Error!

			// Get frames
			const Array<float> &lstFrame1Keys = cFrame1Keys.lstFrameKeys;
			const Array<float> &lstFrame2Keys = cFrame2Keys.lstFrameKeys;

			// Loop through all morph targets and add weights
			if (pMesh) {
				for (uint32 i=0; i<m_lstAniMorphTargets.GetNumOfElements(); i++) {
					const int nIndex = pMesh->GetMorphTargetIndex(m_lstAniMorphTargets[i].sName);
					if (nIndex >= 0 && (&lstMorphTargetWeights[nIndex] != &Array<float>::Null)) {
						const float f1 = lstFrame1Keys[i];
						const float f2 = lstFrame2Keys[i];
						lstMorphTargetWeights[nIndex] += (f1+(f2-f1)*fTime)*fWeight;
					}
				}
			} else {
				for (uint32 i=0; i<m_lstAniMorphTargets.GetNumOfElements(); i++) {
					const float f1 = lstFrame1Keys[i];
					const float f2 = lstFrame2Keys[i];
					lstMorphTargetWeights[i] += (f1+(f2-f1)*fTime)*fWeight;
				}
			}
		}
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Public virtual AnimationInfo functions                ]
//[-------------------------------------------------------]
MorphTargetAni &MorphTargetAni::operator =(const MorphTargetAni &cSource)
{
	// Call base functiona
	*((Element<MorphTargetAni>*)this) = cSource;
	*((AnimationBase*)this) = *((const AnimationBase*)&cSource);

	// Copy data
	m_lstAniMorphTargets = cSource.m_lstAniMorphTargets;

	// Return pointer
	return *this;
}

/**
*  @brief
*    Get the animation source name
*/
String MorphTargetAni::GetSourceName() const
{
	// To implement in derived classes
	return GetName();
}


//[-------------------------------------------------------]
//[ MorphTargetAniManager                                 ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MorphTargetAniManager::MorphTargetAniManager()
{
}

/**
*  @brief
*    Destructor
*/
MorphTargetAniManager::~MorphTargetAniManager()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLGeneral::ElementManager functions   ]
//[-------------------------------------------------------]
MorphTargetAni *MorphTargetAniManager::CreateElement(const String &sName)
{
	return new MorphTargetAni(sName, this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh
