/*********************************************************\
 *  File: SNMRotationKeyframeRecord.cpp                  *
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
#include <PLScene/Scene/SceneNode.h>
#include <PLScene/Scene/SceneContext.h>
#include "PLEngine/Tools/SNMRotationKeyframeRecord.h"


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
pl_implement_class(SNMRotationKeyframeRecord)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMRotationKeyframeRecord::SNMRotationKeyframeRecord(SceneNode &cSceneNode) : SNMTransform(cSceneNode),
	FramesPerSecond(this),
	Keys(this),
	SlotOnUpdate(this),
	m_bRecording(false),
	m_fFrame(0.0f),
	m_nFrame(0),
	m_pChunk(new Chunk())
{
	// Set chunk semantic
	m_pChunk->SetSemantic(Chunk::Rotation);
}

/**
*  @brief
*    Destructor
*/
SNMRotationKeyframeRecord::~SNMRotationKeyframeRecord()
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
Chunk &SNMRotationKeyframeRecord::GetChunk()
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
void SNMRotationKeyframeRecord::OnUpdate()
{
	// Update the current frame
	m_fFrame += float(FramesPerSecond)*Timing::GetInstance()->GetTimeDifference();

	// Is it time to record the next key?
	if (m_nFrame != int(m_fFrame)) {
		// Record the current rotation of the owner scene node
		m_lstData.Add(GetSceneNode().GetTransform().GetRotation());

		// Backup the current frame as integer
		m_nFrame = int(m_fFrame);
	}
}

/**
*  @brief
*    Starts the record
*/
void SNMRotationKeyframeRecord::StartRecord()
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
void SNMRotationKeyframeRecord::StopRecord()
{
	// Is recording currently enabled?
	if (m_bRecording) {
		// Recording is no longer enabled
		m_bRecording = false;

		// Fill the chunk with the recorded data
		m_pChunk->Allocate(PLCore::Chunk::Float, 4, m_lstData.GetNumOfElements());
		if (m_lstData.GetNumOfElements()) {
			// Get a direct pointer to the chunk data
			float *pfChunkData = (float*)m_pChunk->GetData();

			// Loop through the recorded data
			Iterator<Quaternion> cIterator = m_lstData.GetIterator();
			while (cIterator.HasNext()) {
				// Get the recorded rotation
				const Quaternion &qRotation = cIterator.Next();

				// w
				*pfChunkData = qRotation.w;
				pfChunkData++;

				// x
				*pfChunkData = qRotation.x;
				pfChunkData++;

				// y
				*pfChunkData = qRotation.y;
				pfChunkData++;

				// z
				*pfChunkData = qRotation.z;
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
void SNMRotationKeyframeRecord::OnActivate(bool bActivate)
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
