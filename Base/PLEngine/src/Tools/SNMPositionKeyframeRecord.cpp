/*********************************************************\
 *  File: SNMPositionKeyframeRecord.cpp                  *
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
#include <PLCore/Tools/Chunk.h>
#include <PLCore/Tools/Timing.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SceneContainer.h>
#include "PLEngine/Tools/SNMPositionKeyframeRecord.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLScene;
namespace PLEngine {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPositionKeyframeRecord)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPositionKeyframeRecord::SNMPositionKeyframeRecord(SceneNode &cSceneNode) : SNMTransform(cSceneNode),
	FramesPerSecond(this),
	Keys(this),
	CoordinateSystem(this),
	SlotOnUpdate(this),
	m_bRecording(false),
	m_fFrame(0.0f),
	m_nFrame(0),
	m_pChunk(new Chunk())
{
	// Set chunk semantic
	m_pChunk->SetSemantic(Chunk::Position);
}

/**
*  @brief
*    Destructor
*/
SNMPositionKeyframeRecord::~SNMPositionKeyframeRecord()
{
	// Stop the record
	StopRecord();

	// Destroy the chunk
	delete m_pChunk;
}

/**
*  @brief
*    Returns the chunk holding the keyframe data
*/
Chunk &SNMPositionKeyframeRecord::GetChunk()
{
	return *m_pChunk;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNMPositionKeyframeRecord::OnUpdate()
{
	// Update the current frame
	m_fFrame += float(FramesPerSecond)*Timing::GetInstance()->GetTimeDifference();

	// Is it time to record the next key?
	if (m_nFrame != int(m_fFrame)) {
		// Get the current position of the owner scene node
		Vector3 vPosition = GetSceneNode().GetTransform().GetPosition();

		// Transform the position into the requested scene container space?
		if (CoordinateSystem.Get().GetLength()) {
			// Get the scene container the position keys should be in
			SceneNode *pTargetSceneNode = GetSceneNode().GetContainer()->GetByName(CoordinateSystem);
			if (pTargetSceneNode && pTargetSceneNode->IsContainer()) {
				// Get the transform matrix that transform from "this scene container" into "the other scene container"
				Matrix3x4 mTransform;
				GetSceneNode().GetContainer()->GetTransformMatrixTo((SceneContainer&)*pTargetSceneNode, mTransform);

				// Transform the position into the requested coordinate system
				vPosition *= mTransform;
			}
		}

		// Record the current position of the owner scene node
		m_lstData.Add(vPosition);

		// Backup the current frame as integer
		m_nFrame = int(m_fFrame);
	}
}

/**
*  @brief
*    Starts the record
*/
void SNMPositionKeyframeRecord::StartRecord()
{
	// Stop the previous recording
	StopRecord();

	// Clear the previous chunk data
	m_pChunk->Clear();

	// Recording is now enabled
	m_bRecording = true;

	// Set initial frame
	m_fFrame = 0.0f;
	m_nFrame = -1;	// -1 so force to generate a new key at once
}

/**
*  @brief
*    Stops the record
*/
void SNMPositionKeyframeRecord::StopRecord()
{
	// Is recording currently enabled?
	if (m_bRecording) {
		// Recording is no longer enabled
		m_bRecording = false;

		// Fill the chunk with the recorded data
		m_pChunk->Allocate(PLCore::Chunk::Float, 3, m_lstData.GetNumOfElements());
		if (m_lstData.GetNumOfElements()) {
			// Get a direct pointer to the chunk data
			float *pfChunkData = (float*)m_pChunk->GetData();

			// Loop through the recorded data
			Iterator<Vector3> cIterator = m_lstData.GetIterator();
			while (cIterator.HasNext()) {
				// Get the recorded position
				const Vector3 &vPosition = cIterator.Next();

				// x
				*pfChunkData = vPosition.x;
				pfChunkData++;

				// y
				*pfChunkData = vPosition.y;
				pfChunkData++;

				// z
				*pfChunkData = vPosition.z;
				pfChunkData++;
			}
		}

		// Clear the recorded data (it's not within the chunk!)
		m_lstData.Clear();

		// If a chunk filename is given, save the chunk right now
		if (Keys.Get().GetLength())
			m_pChunk->SaveByFilename(Keys);
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNodeModifier functions  ]
//[-------------------------------------------------------]
void SNMPositionKeyframeRecord::OnActivate(bool bActivate)
{
	// Connect/disconnect event handler and start/stop the record
	if (bActivate) {
		// Start the record
		StartRecord();

		// Connect event handler
		SceneContext *pSceneContext = GetSceneContext();
		if (pSceneContext)
			pSceneContext->EventUpdate.Connect(SlotOnUpdate);
	} else {
		// Stop the record
		StopRecord();

		// Disconnect event handler
		SceneContext *pSceneContext = GetSceneContext();
		if (pSceneContext)
			pSceneContext->EventUpdate.Disconnect(SlotOnUpdate);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
