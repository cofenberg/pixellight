/*********************************************************\
 *  File: SNMRotationKeyframeRecord.h                    *
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


#ifndef __PLENGINE_TOOLS_SNMROTATIONKEYFRAMERECORD_H__
#define __PLENGINE_TOOLS_SNMROTATIONKEYFRAMERECORD_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneNodeModifiers/SNMTransform.h>
#include "PLEngine/PLEngine.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class Chunk;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Keyframe rotation record scene node modifier class
*
*  @remarks
*    If this modifier is active, it records the rotation of the scene nodes over time using keyframes.
*    When the modifier get's inactive or destroyed, the recorded keyframes are written into a chunk file.
*/
class SNMRotationKeyframeRecord : public PLScene::SNMTransform {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, SNMRotationKeyframeRecord, "PLEngine", PLScene::SNMTransform, "Keyframe rotation animation scene node modifier class")
		// Attributes
		pl_attribute(FramesPerSecond,	PLCore::uint32,	24,	ReadWrite,	DirectValue,	"Frames per second",													"")
		pl_attribute(Keys,				PLCore::String,	"",	ReadWrite,	DirectValue,	"Rotation keys (w, x, y and z quaternion components) chunk filename",	"")
		// Constructors
		pl_constructor_1(ParameterConstructor,	PLScene::SceneNode&,	"Parameter constructor",	"")
		// Slots
		pl_slot_0(OnUpdate,	"Called when the scene node needs to be updated",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		PL_API SNMRotationKeyframeRecord(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~SNMRotationKeyframeRecord();

		/**
		*  @brief
		*    Returns the chunk holding the keyframe data
		*
		*  @return
		*    The chunk holding the keyframe data (only with valid/current data after the record was stopped)
		*/
		PL_API PLCore::Chunk &GetChunk();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void OnUpdate();

		/**
		*  @brief
		*    Starts the record
		*
		*  @note
		*    - Called when the modifier gets active
		*    - The previous chunk data will be destroyed
		*/
		void StartRecord();

		/**
		*  @brief
		*    Stops the record
		*
		*  @note
		*    - Called when the modifier get's inactive or destroyed
		*    - If "Keys" is not empty, the chunk is saved
		*/
		void StopRecord();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool							  m_bRecording;	/**< Is recording currently enabled? */
		PLCore::List<PLMath::Quaternion>  m_lstData;	/**< Recorded data */
		float							  m_fFrame;		/**< Current frame as floating point */
		int								  m_nFrame;		/**< Current frame as integer */
		PLCore::Chunk					 *m_pChunk;		/**< Chunk holding the keyframe data, always valid! */


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneNodeModifier functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void OnActivate(bool bActivate) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_TOOLS_SNMROTATIONKEYFRAMERECORD_H__
