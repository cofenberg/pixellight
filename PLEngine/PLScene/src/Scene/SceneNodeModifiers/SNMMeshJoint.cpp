/*********************************************************\
 *  File: SNMMeshJoint.cpp                               *
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
#include <PLGeneral/Container/Stack.h>
#include <PLMath/EulerAngles.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/Font.h>
#include <PLRenderer/Renderer/FontManager.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLMesh/Skeleton.h>
#include <PLMesh/MeshHandler.h>
#include <PLMesh/JointHandler.h>
#include <PLMesh/SkeletonHandler.h>
#include "PLScene/Visibility/VisNode.h"
#include "PLScene/Scene/SceneContainer.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMMeshJoint.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLMesh;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMMeshJoint)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String SNMMeshJoint::GetName() const
{
	return m_sName;
}

void SNMMeshJoint::SetName(const String &sValue)
{
	if (m_sName != sValue) {
		m_sName = sValue;

		// Clamp rotation
		for (int i=0; i<3; i++) {
			if (m_vMin.fV[i] != m_vMax.fV[i]) {
				if (m_vRotation.fV[i] < m_vMin.fV[i])
					m_vRotation.x = m_vMin.fV[i];
				if (m_vRotation.fV[i] > m_vMax.fV[i])
					m_vRotation.x = m_vMax.fV[i];
			}
		}

		// Update the joint
		UpdateJoint();
	}
}

const Vector3 &SNMMeshJoint::GetRotation() const
{
	return m_vRotation;
}

void SNMMeshJoint::SetRotation(const Vector3 &vValue)
{
	if (m_vRotation != vValue) {
		m_vRotation = vValue;

		// Clamp rotation
		for (int i=0; i<3; i++) {
			if (m_vMin.fV[i] != m_vMax.fV[i]) {
				if (m_vRotation.fV[i] < m_vMin.fV[i])
					m_vRotation.x = m_vMin.fV[i];
				if (m_vRotation.fV[i] > m_vMax.fV[i])
					m_vRotation.x = m_vMax.fV[i];
			}
		}

		// Update the joint
		UpdateJoint();
	}
}

const Vector3 &SNMMeshJoint::GetMin() const
{
	return m_vMin;
}

void SNMMeshJoint::SetMin(const Vector3 &vValue)
{
	if (m_vMin != vValue) {
		m_vMin = vValue;

		// Clamp rotation
		bool bUpdate = false;
		for (int i=0; i<3; i++) {
			if (m_vMin.fV[i] != m_vMax.fV[i] && m_vRotation.fV[i] < m_vMin.fV[i]) {
				m_vRotation.x = m_vMin.fV[i];
				bUpdate = true;
			}
		}

		// Update the joint?
		if (bUpdate)
			UpdateJoint();
	}
}

const Vector3 &SNMMeshJoint::GetMax() const
{
	return m_vMax;
}

void SNMMeshJoint::SetMax(const Vector3 &vValue)
{
	if (m_vMax != vValue) {
		m_vMax = vValue;

		// Clamp rotation
		bool bUpdate = false;
		for (int i=0; i<3; i++) {
			if (m_vMin.fV[i] != m_vMax.fV[i] && m_vRotation.fV[i] > m_vMax.fV[i]) {
				m_vRotation.x = m_vMax.fV[i];
				bUpdate = true;
			}
		}

		// Update the joint?
		if (bUpdate)
			UpdateJoint();
	}
}

void SNMMeshJoint::SetFlags(uint32 nValue)
{
	// Call base implementation
	SNMMesh::SetFlags(nValue);

	// Connect/disconnect event handlers
	SceneNode &cSceneNode = GetSceneNode();
	if (IsActive()) {
		UpdateJoint();

		// Connect event handlers
		cSceneNode.EventUpdate.   Connect(&EventHandlerUpdate);
		cSceneNode.EventDrawDebug.Connect(&EventHandlerDrawDebug);
	} else {
		// Connect event handlers
		cSceneNode.EventUpdate.   Disconnect(&EventHandlerUpdate);
		cSceneNode.EventDrawDebug.Disconnect(&EventHandlerDrawDebug);
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMMeshJoint::SNMMeshJoint(SceneNode &cSceneNode) : SNMMesh(cSceneNode),
	Name(this),
	Rotation(this),
	RotationFrom(this),
	Min(this),
	Max(this),
	Speed(this),
	MaxDifference(this),
	FallbackRotation(this),
	Flags(this),
	EventHandlerUpdate	 (&SNMMeshJoint::NotifyUpdate,    this),
	EventHandlerDrawDebug(&SNMMeshJoint::NotifyDrawDebug, this)
{
	// Create the mesh animation manager
	MeshHandler *pMeshHandler = cSceneNode.GetMeshHandler();
	if (pMeshHandler) {
		MeshAnimationManager *pAniManager = pMeshHandler->GetMeshAnimationManager();
		if (!pAniManager)
			pAniManager = pMeshHandler->CreateMeshAnimationManager();
	}
}

/**
*  @brief
*    Destructor
*/
SNMMeshJoint::~SNMMeshJoint()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the target rotation within the container space of the owner node
*/
bool SNMMeshJoint::GetTargetRotation(Quaternion &qRot) const
{
	// Get the target scene node
	const SceneNode *pTarget;
	if (GetSceneNode().GetContainer())
		pTarget = GetSceneNode().GetContainer()->Get(RotationFrom.Get());
	else {
		// This must be the root :()
		pTarget = ((SceneContainer*)this)->Get(RotationFrom.Get());
	}
	if (!pTarget)
		return false; // Error - no valid target scene node, no target rotation :(

	// Set the rotation of the attached node
	qRot = pTarget->GetTransform().GetRotation();

	// Are we in luck and the target is within the same container as the owner node?
	if (GetSceneNode().GetContainer() != pTarget->GetContainer()) {
		// Nope, we have to translate the rotation into the correct space :(
		const SceneContainer *pContainer = pTarget->GetContainer();
		while (pContainer) {
			qRot *= pContainer->GetTransform().GetRotation();
			pContainer = pContainer->GetContainer();
		}

		// To container space of the owner node
		pContainer = GetSceneNode().GetContainer();
		Stack<const SceneContainer*> lstStack;
		while (pContainer) {
			lstStack.Push(pContainer);
			pContainer = pContainer->GetContainer();
		}
		while (lstStack.GetNumOfElements()) {
			pContainer = lstStack.Top();
			lstStack.Pop();
			qRot *= pContainer->GetTransform().GetRotation().GetUnitInverted();
		}
	}

	// Done
	return true;
}

/**
*  @brief
*    Updates the joint rotation
*/
void SNMMeshJoint::UpdateJoint()
{
	// Is this modifier active?
	if (IsActive()) {
		// Get the mesh handler
		MeshHandler *pMeshHandler = GetSceneNode().GetMeshHandler();
		if (pMeshHandler) {
			// Get the base head joint handler
			JointHandler *pJointHandler = pMeshHandler->GetBaseJointHandler(m_sName);
			if (pJointHandler) {
				// Set joint rotation
				Quaternion qRot;
				EulerAngles::ToQuaternion(float(m_vRotation.x*Math::DegToRad), float(m_vRotation.y*Math::DegToRad), float(m_vRotation.z*Math::DegToRad), qRot);
				pJointHandler->SetRotation(qRot);

				// The mesh requires an update
				pMeshHandler->MeshUpdateRequired();
			}
		}
	}
}

/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNMMeshJoint::NotifyUpdate()
{
	// Rotation source given?
	if (RotationFrom.Get().GetLength()) {
		// Get the rotation of the target scene node
		Quaternion qTargetRotation;
		if (GetTargetRotation(qTargetRotation)) {
			// Transform the rotation from the other into this node
			qTargetRotation.UnitInvert();
			qTargetRotation *= GetSceneNode().GetTransform().GetRotation();

			// Get the mesh handler
			MeshHandler *pMeshHandler = GetSceneNode().GetMeshHandler();
			if (pMeshHandler) {
				// Get the base head joint handler
				JointHandler *pJointHandler = pMeshHandler->GetJointHandler(m_sName);
				if (pJointHandler) {
					// Mark this joint handler as user controlled
					pJointHandler->SetUserControlled(true);

					// Get the parent joint handler
					const JointHandler *pParentJointHandler = NULL;
					{
						const Joint *pJoint = pJointHandler->GetElement();
						if (pJoint) {
							const int nParent = pJoint->GetParent();
							if (nParent >= 0) {
								const SkeletonHandler *pSkeletonHandler = pMeshHandler->GetSkeletonHandler();
								if (pSkeletonHandler) {
									const Skeleton *pSkeleton = pSkeletonHandler->GetResource();
									if (pSkeleton) {
										const Joint *pParentJoint = pSkeleton->Get(nParent);
										if (pParentJoint)
											pParentJointHandler = pMeshHandler->GetJointHandler(pParentJoint->GetName());
									}
								}
							}
						}
					}

					// Perform rotation limitation (if there is any)
					if (pParentJointHandler) {
						const Quaternion qAbsoluteToRelative = pParentJointHandler->GetRotationAbsolute().GetUnitInverted();

						// Transform target rotation from absolute to relative
						qTargetRotation *= qAbsoluteToRelative;

						// Get target rotation as euler angles in radians
						float fTargetAngles[3];
						EulerAngles::FromQuaternion(qTargetRotation, fTargetAngles[0], fTargetAngles[1], fTargetAngles[2]);

						// Loop through all 3 rotation components and check the limits
						bool bClamp = false;
						const float fTimeDiff = Timing::GetInstance()->GetTimeDifference()*Speed;
						for (int i=0; i<3; i++) {
							// Radians to degree
							fTargetAngles[i] = float(fTargetAngles[i]*Math::RadToDeg);

							// Clamp this component to a range?
							if (m_vMin[i] != m_vMax[i]) {
								// Clamp to minimum
								if (fTargetAngles[i] < m_vMin[i]) {
									bClamp = true;
									fTargetAngles[i] = m_vMin[i];
								}

								// Clamp to maximum
								if (fTargetAngles[i] > m_vMax[i]) {
									bClamp = true;
									fTargetAngles[i] = m_vMax[i];
								}
							}
						}

						// Loop through all 3 rotation components and interpolate
						for (int i=0; i<3; i++) {
							// Use fallback rotation?
							if (bClamp && (GetFlags() & UseFallbackRotation))
								fTargetAngles[i] = FallbackRotation.Get()[i];

							// Smooth interpolate from current angles to target angles
							if (m_vRotation[i] > fTargetAngles[i]) {
								float fStep = Math::Abs(m_vRotation[i]-fTargetAngles[i]);
								if (fStep > MaxDifference)
									fStep = MaxDifference;
								m_vRotation[i] -= fStep*fTimeDiff;
								if (m_vRotation[i] < fTargetAngles[i])
									m_vRotation[i] = fTargetAngles[i];
							}
							if (m_vRotation[i] < fTargetAngles[i]) {
								float fStep = Math::Abs(m_vRotation[i]-fTargetAngles[i]);
								if (fStep > MaxDifference)
									fStep = MaxDifference;
								m_vRotation[i] += fStep*fTimeDiff;
								if (m_vRotation[i] > fTargetAngles[i])
									m_vRotation[i] = fTargetAngles[i];
							}
						}

						// Get target rotation as quaternion
						EulerAngles::ToQuaternion(float(m_vRotation[0]*Math::DegToRad),
												  float(m_vRotation[1]*Math::DegToRad),
												  float(m_vRotation[2]*Math::DegToRad),
												  qTargetRotation);

						// Transform target rotation from relative to absolute
						qTargetRotation *= pParentJointHandler->GetRotationAbsolute();
					}

					// Set the absolute rotation of the joint
					pJointHandler->SetRotationAbsolute(qTargetRotation);

					// Set the absolute translation of the joint
					if (pParentJointHandler)
						pJointHandler->SetTranslationAbsolute(pParentJointHandler->GetRotationAbsolute()*pJointHandler->GetTranslation()+pParentJointHandler->GetTranslationAbsolute());

					// The mesh requires an update
					pMeshHandler->MeshUpdateRequired();
				}
			}
		}
	}
}

/**
*  @brief
*    Called on scene node debug draw
*/
void SNMMeshJoint::NotifyDrawDebug(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Get the mesh handler
	const MeshHandler *pMeshHandler = GetSceneNode().GetMeshHandler();
	if (pMeshHandler && pVisNode) {
		// Get the base head joint handler
		const JointHandler *pJointHandler = pMeshHandler->GetJointHandler(m_sName);
		if (pJointHandler) {
			// Draw joint position
			cRenderer.GetRendererContext().GetEffectManager().Use();
			cRenderer.SetRenderState(RenderState::ZEnable, false);
			cRenderer.GetDrawHelpers().DrawPoint(Color4::Green, pJointHandler->GetTranslationAbsolute(), pVisNode->GetWorldViewProjectionMatrix(), 4.0f);

			// Draw joint name
			const Joint *pJoint = pJointHandler->GetElement();
			if (pJoint) {
				Font *pFont = (Font*)cRenderer.GetFontManager().GetDefaultFontTexture();
				if (pFont)
					cRenderer.GetDrawHelpers().DrawText(*pFont, pJoint->GetName(), Color4::Green, pJointHandler->GetTranslationAbsolute(), pVisNode->GetWorldViewProjectionMatrix(), Font::CenterText);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
