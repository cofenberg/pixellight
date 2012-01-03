/*********************************************************\
 *  File: JointAni.cpp                                   *
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
#include "PLMesh/JointHandler.h"
#include "PLMesh/JointAni.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLMesh {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
JointAni::JointAni()
{
}

/**
*  @brief
*    Destructor
*/
JointAni::~JointAni()
{
}

/**
*  @brief
*    Returns the animation joints
*/
Array<JointAni::AniJoint> &JointAni::GetJoints()
{
	return m_lstAniJoints;
}

/**
*  @brief
*    Applies the joint states from the given joint animation frame
*    to the given joint states
*/
bool JointAni::ApplyJointStates(Array<JointHandler> &lstJointHandlers, uint32 nFrame, float fWeight) const
{
	// Check weight of this states
	if (fWeight) {
		// Are there any joints?
		if (!lstJointHandlers.GetNumOfElements())
			return false; // Error!

		// Get the frame keys
		FrameKeys &cFrameKeys = m_lstFrameKeys[nFrame];
		if (&cFrameKeys == &Array<FrameKeys>::Null)
			return false; // Error!

		// Get frame
		Array<float> &lstFrameKeys = cFrameKeys.lstFrameKeys;

		// Loop through all animation joints
		Quaternion qDelta, qDeltaFinal;
		Vector3 vDelta;
		long nKey = 0;
		for (uint32 i=0; i<lstJointHandlers.GetNumOfElements(); i++) {
			JointHandler &cJH       = lstJointHandlers[i];
			AniJoint     &cAniJoint = m_lstAniJoints[i];

			// Reset deltas
			vDelta.SetXYZ(0.0f, 0.0f, 0.0f);
			qDelta.SetWXYZ(1.0f, 0.0f, 0.0f, 0.0f);

			// Get joint state
			char nAnimatedComponents = cAniJoint.nAnimatedComponents;

			// Translation
			if (nAnimatedComponents & AX)
				vDelta.x = lstFrameKeys[nKey++];
			if (nAnimatedComponents & AY)
				vDelta.y = lstFrameKeys[nKey++];
			if (nAnimatedComponents & AZ)
				vDelta.z = lstFrameKeys[nKey++];

			// Rotation
			if (nAnimatedComponents & AYaw ||
				nAnimatedComponents & APitch ||
				nAnimatedComponents & ARoll ||
				nAnimatedComponents & AW) {
				if (nAnimatedComponents & AYaw)
					qDelta.x = lstFrameKeys[nKey++];
				if (nAnimatedComponents & APitch)
					qDelta.y = lstFrameKeys[nKey++];
				if (nAnimatedComponents & ARoll)
					qDelta.z = lstFrameKeys[nKey++];
				if (nAnimatedComponents & AW)
					qDelta.w = lstFrameKeys[nKey++];
				else {
					// Compute last component (w) of the quaternion
					float fSqw = 1.0f - qDelta.x*qDelta.x -
										qDelta.y*qDelta.y -
										qDelta.z*qDelta.z;
					qDelta.w = (fSqw > 0.0f) ? -Math::Sqrt(fSqw) : 0.0f;
				}
			}

			// Add deltas
			qDeltaFinal.Slerp(qDelta, Quaternion::Identity, fWeight);
			cJH.SetTranslation(cJH.GetTranslation()+(vDelta*fWeight));
			cJH.SetRotation(cJH.GetRotation()*qDeltaFinal);
		}
	}

	// Done
	return true;
}

/**
*  @brief
*    Applies the blended joint states from the given joint animation frames
*    to the given joint states
*/
bool JointAni::ApplyJointStates(Array<JointHandler> &lstJointHandlers, uint32 nFrame1,
								uint32 nFrame2, float fTime, float fWeight) const
{
	// Check weight of this states
	if (fWeight) {
		// Are there any joints?
		if (!lstJointHandlers.GetNumOfElements())
			return false; // Error!

		// Get the frame keys
		FrameKeys &cFrame1Keys = m_lstFrameKeys[nFrame1];
		if (&cFrame1Keys == &Array<FrameKeys>::Null)
			return false; // Error!
		FrameKeys &cFrame2Keys = m_lstFrameKeys[nFrame2];
		if (&cFrame2Keys == &Array<FrameKeys>::Null)
			return false; // Error!

		// Get frames
		Array<float> &lstFrame1Keys = cFrame1Keys.lstFrameKeys;
		Array<float> &lstFrame2Keys = cFrame2Keys.lstFrameKeys;

		// Loop through all animation joints
		Quaternion qDelta, qDelta1, qDelta2, qDeltaFinal;
		Vector3 vDelta;
		long nKey = 0;
		for (uint32 i=0; i<lstJointHandlers.GetNumOfElements(); i++) {
			JointHandler   &cJH       = lstJointHandlers[i];
			const AniJoint &cAniJoint = m_lstAniJoints[i];

			// Reset deltas
			vDelta.SetXYZ(0.0f, 0.0f, 0.0f);
			qDelta.SetWXYZ(1.0f, 0.0f, 0.0f, 0.0f);
			qDelta1.SetWXYZ(1.0f, 0.0f, 0.0f, 0.0f);
			qDelta2.SetWXYZ(1.0f, 0.0f, 0.0f, 0.0f);

			// Get joint state
			char nAnimatedComponents = cAniJoint.nAnimatedComponents;

			// Translation
			if (nAnimatedComponents & AX) {
				vDelta.x = lstFrame1Keys[nKey]+(lstFrame2Keys[nKey]-lstFrame1Keys[nKey])*fTime;
				nKey++;
			}
			if (nAnimatedComponents & AY) {
				vDelta.y = lstFrame1Keys[nKey]+(lstFrame2Keys[nKey]-lstFrame1Keys[nKey])*fTime;
				nKey++;
			}
			if (nAnimatedComponents & AZ) {
				vDelta.z = lstFrame1Keys[nKey]+(lstFrame2Keys[nKey]-lstFrame1Keys[nKey])*fTime;
				nKey++;
			}

			// Rotation
			if (nAnimatedComponents & AYaw ||
				nAnimatedComponents & APitch ||
				nAnimatedComponents & ARoll ||
				nAnimatedComponents & AW) {
				if (nAnimatedComponents & AYaw) {
					qDelta1.x = lstFrame1Keys[nKey];
					qDelta2.x = lstFrame2Keys[nKey];
					nKey++;
				}
				if (nAnimatedComponents & APitch) {
					qDelta1.y = lstFrame1Keys[nKey];
					qDelta2.y = lstFrame2Keys[nKey];
					nKey++;
				}
				if (nAnimatedComponents & ARoll) {
					qDelta1.z = lstFrame1Keys[nKey];
					qDelta2.z = lstFrame2Keys[nKey];
					nKey++;
				}
				if (nAnimatedComponents & AW) {
					qDelta1.w = lstFrame1Keys[nKey];
					qDelta2.w = lstFrame2Keys[nKey];
					nKey++;
				} else {
					// Compute last component (w) of the quaternions
					float fSqw = 1.0f - qDelta1.x*qDelta1.x - qDelta1.y*qDelta1.y - qDelta1.z*qDelta1.z;
					qDelta1.w = (fSqw <= 0.0f) ? 0.0f : -Math::Sqrt(fSqw);
					fSqw = 1.0f - qDelta2.x*qDelta2.x - qDelta2.y*qDelta2.y - qDelta2.z*qDelta2.z;
					qDelta2.w = (fSqw <= 0.0f) ? 0.0f : -Math::Sqrt(fSqw);
				}

				// Interpolate quaternions
				qDelta.Slerp(qDelta1, qDelta2, fTime);
			}

			// Add deltas
			qDeltaFinal.Slerp(Quaternion::Identity, qDelta, fWeight);
			cJH.SetTranslation((vDelta*fWeight)+cJH.GetTranslation());
			cJH.SetRotation(qDeltaFinal*cJH.GetRotation());
		}
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Public virtual AnimationInfo functions                ]
//[-------------------------------------------------------]
JointAni &JointAni::operator =(const JointAni &cSource)
{
	// Call base function
	*static_cast<AnimationBase*>(this) = *static_cast<const AnimationBase*>(&cSource);

	// Copy data
	m_lstAniJoints = cSource.m_lstAniJoints;

	// Return pointer
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh
