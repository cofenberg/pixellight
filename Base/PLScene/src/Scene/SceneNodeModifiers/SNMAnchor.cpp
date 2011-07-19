/*********************************************************\
 *  File: SNMAnchor.cpp                                  *
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
#include <PLMath/EulerAngles.h>
#include <PLMesh/Joint.h>
#include <PLMesh/Skeleton.h>
#include <PLMesh/MeshHandler.h>
#include <PLMesh/SkeletonHandler.h>
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneContainer.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMAnchor.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLMesh;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMAnchor)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String SNMAnchor::GetAttachedNode() const
{
	return m_sAttachedNode;
}

void SNMAnchor::SetAttachedNode(const String &sValue)
{
	if (m_sAttachedNode != sValue) {
		m_sAttachedNode = sValue;
		m_cAttachedNodeHandler.SetElement(GetSceneNode().GetContainer()->GetByName(m_sAttachedNode));
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMAnchor::SNMAnchor(SceneNode &cSceneNode) : SceneNodeModifier(cSceneNode),
	AttachedNode(this),
	PositionOffset(this),
	RotationOffset(this),
	SkeletonJoint(this),
	JointPositionOffset(this),
	JointRotationOffset(this),
	Flags(this),
	SlotOnContainer(this),
	SlotOnPositionRotationUpdate(this)
{
}

/**
*  @brief
*    Destructor
*/
SNMAnchor::~SNMAnchor()
{
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
void SNMAnchor::OnActivate(bool bActivate)
{
	// Connect/disconnect event handlers
	SceneNode &cSceneNode = GetSceneNode();
	if (bActivate) {
		// Connect event handlers
		cSceneNode.SignalContainer.Connect(SlotOnContainer);
		cSceneNode.GetTransform().EventPosition.Connect(SlotOnPositionRotationUpdate);
		cSceneNode.GetTransform().EventRotation.Connect(SlotOnPositionRotationUpdate);
		SceneContext *pSceneContext = GetSceneContext();
		if (pSceneContext)
			pSceneContext->EventUpdate.Connect(SlotOnPositionRotationUpdate);
	} else {
		// Disconnect event handlers
		cSceneNode.SignalContainer.Disconnect(SlotOnContainer);
		cSceneNode.GetTransform().EventPosition.Disconnect(SlotOnPositionRotationUpdate);
		cSceneNode.GetTransform().EventRotation.Disconnect(SlotOnPositionRotationUpdate);
		SceneContext *pSceneContext = GetSceneContext();
		if (pSceneContext)
			pSceneContext->EventUpdate.Disconnect(SlotOnPositionRotationUpdate);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node container changed
*/
void SNMAnchor::OnContainer()
{
	// Is it allowed to change the container the attached node is in?
	if (!(GetFlags() & NoContainerUpdate)) {
		// Get the scene node
		const SceneNode &cSceneNode = GetSceneNode();

		// Get the attached scene node
		SceneNode *pAttachedSceneNode = m_cAttachedNodeHandler.GetElement();
		if (!pAttachedSceneNode && cSceneNode.GetContainer()) {
			pAttachedSceneNode = cSceneNode.GetContainer()->GetByName(m_sAttachedNode);
			m_cAttachedNodeHandler.SetElement(pAttachedSceneNode);
		}
		if (pAttachedSceneNode && cSceneNode.GetContainer())
			pAttachedSceneNode->SetContainer(*cSceneNode.GetContainer());
	}
}

/**
*  @brief
*    Called when the scene node position or rotation changed or on update request
*/
void SNMAnchor::OnPositionRotationUpdate()
{
	// Is there anything to do in here?
	if (!(GetFlags() & NoPosition) || !(GetFlags() & NoRotation)) {
		// Get the owner scene node
		SceneNode &cOwnerSceneNode = GetSceneNode();

		// Get the attached scene node
		SceneNode *pAttachedSceneNode = m_cAttachedNodeHandler.GetElement();
		if (!pAttachedSceneNode && cOwnerSceneNode.GetContainer()) {
			pAttachedSceneNode = cOwnerSceneNode.GetContainer()->GetByName(m_sAttachedNode);
			m_cAttachedNodeHandler.SetElement(pAttachedSceneNode);
		}
		if (pAttachedSceneNode) {
			// Attached to a skeleton joint?
			Vector3 vPos;
			Quaternion qRot;
			if (SkeletonJoint.Get().GetLength()) {
				// Is there a mesh handler?
				const MeshHandler *pMeshHandler = cOwnerSceneNode.GetMeshHandler();
				if (pMeshHandler) {
					// Is there a skeleton handler?
					const SkeletonHandler *pSkeletonHandler = pMeshHandler->GetSkeletonHandler();
					if (pSkeletonHandler) {
						// Has this skeleton handler a skeleton resource?
						const Skeleton *pSkeleton = pSkeletonHandler->GetResource();
						if (pSkeleton) {
							// Is there a skeleton joint with the given name?
							const Joint *pJoint = pSkeleton->GetByName(SkeletonJoint.Get());
							if (pJoint) {
								// Get skeleton handler
								const Array<JointHandler> &lstJointHandlers = pSkeletonHandler->GetJointHandlers();
								const JointHandler &cJointHandler = lstJointHandlers[pJoint->GetID()];
								if (&cJointHandler != &Array<JointHandler>::Null) {
									// Set the position of the attached node
									if (!(GetFlags() & NoPosition))
										vPos = cJointHandler.GetTranslationAbsolute()+cJointHandler.GetRotationAbsolute().GetUnitInverted()*JointPositionOffset.Get();

									// Set the rotation of the attached node
									if (!(GetFlags() & NoRotation)) {
										Quaternion qRotOffset;
										EulerAngles::ToQuaternion(static_cast<float>(JointRotationOffset.Get().x*Math::DegToRad),
																  static_cast<float>(JointRotationOffset.Get().y*Math::DegToRad),
																  static_cast<float>(JointRotationOffset.Get().z*Math::DegToRad),
																  qRotOffset);
										qRot = cJointHandler.GetRotationAbsolute().GetUnitInverted()*qRotOffset;
									}
								}
							}
						}
					}
				}
			}

			// Transform into camera container space
			Matrix3x4 mTransform;
			cOwnerSceneNode.GetContainer()->GetTransformMatrixTo(*pAttachedSceneNode->GetContainer(), mTransform);

			// Set the position of the attached node
			if (!(GetFlags() & NoPosition))
				pAttachedSceneNode->GetTransform().SetPosition(mTransform*(cOwnerSceneNode.GetTransform().GetPosition()+cOwnerSceneNode.GetTransform().GetRotation()*(PositionOffset.Get()+vPos)*cOwnerSceneNode.GetTransform().GetScale()));

			// Set the rotation of the attached node
			if (!(GetFlags() & NoRotation)) {
				Quaternion qRotOffset;
				EulerAngles::ToQuaternion(static_cast<float>(RotationOffset.Get().x*Math::DegToRad),
										  static_cast<float>(RotationOffset.Get().y*Math::DegToRad),
										  static_cast<float>(RotationOffset.Get().z*Math::DegToRad),
										  qRotOffset);
				pAttachedSceneNode->GetTransform().SetRotation(Quaternion(mTransform)*(cOwnerSceneNode.GetTransform().GetRotation()*qRotOffset*qRot));
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
