/*********************************************************\
 *  File: Camcorder.h                                    *
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


#ifndef __PLENGINE_TOOLS_CAMCORDER_H__
#define __PLENGINE_TOOLS_CAMCORDER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneNodeHandler.h>
#include "PLEngine/PLEngine.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class EngineApplication;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Camcorder interaction component
*
*  @note
*    - Do not perform playback if the current camera is using physics...
*/
class Camcorder : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, Camcorder, "PLEngine", PLCore::Object, "Camcorder interaction component")
		// Attributes
		pl_attribute(CamcorderDirectory,	PLCore::String,	"../Data/Camcorder/",	ReadWrite,	DirectValue,	"Default directory for the camcorder files",	"")
		#ifdef PLENGINE_EXPORTS	// The following is only required when compiling PLEngine
			// Methods
			pl_method_1(StartRecord,	pl_ret_type(void),	const PLCore::String&,	"Starts the record, record name as first parameter (if empty string, no recording can be started). The currently used application camera will be recorded. If playback is currently enabled, the playback will be stopped at once.",	"")
			pl_method_0(IsRecording,	pl_ret_type(bool),							"Returns whether or not recording is currently active. Returns 'true' if recording is currently active, else 'false'.",																													"")
			pl_method_0(StopRecord,		pl_ret_type(void),							"Stops the record",																																																						"")
			pl_method_1(StartPlayback,	pl_ret_type(void),	const PLCore::String&,	"Starts the playback, record name as first parameter (must be valid). The currently used application camera will be feed with the recorded data. If recording is currently enabled, the recording will be stopped at once.",			"")
			pl_method_0(IsPlaying,		pl_ret_type(bool),							"Returns whether or not playback is currently active. Returns 'true' if playback is currently active, else 'false'.",																													"")
			pl_method_0(StopPlayback,	pl_ret_type(void),							"Stops the playback",																																																					"")
			pl_method_0(Update,			pl_ret_type(void),							"Updates the camcorder component",																																																		"")
		#endif
		// Signals
		pl_signal_0(SignalPlaybackFinished,	"Playback has been finished",	"")
		// Slots
		pl_slot_0(OnAnimationStop,	"Called when one of the keyframe animations has been stopped",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cApplication
		*    Owner application
		*/
		PL_API Camcorder(EngineApplication &cApplication);

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~Camcorder();

		/**
		*  @brief
		*    Returns the owner application
		*
		*  @return
		*    The owner application
		*/
		PL_API EngineApplication &GetApplication() const;

		/**
		*  @brief
		*    Starts the record
		*
		*  @param[in] sName
		*    Record name, if empty string, no recording can be started
		*
		*  @note
		*    - The currently used application camera will be recorded
		*    - If playback is currently enabled, the playback will be stopped at once
		*/
		PL_API void StartRecord(const PLCore::String &sName);

		/**
		*  @brief
		*    Returns whether or not recording is currently active
		*
		*  @return
		*    'true' if recording is currently active, else 'false'
		*/
		PL_API bool IsRecording() const;

		/**
		*  @brief
		*    Stops the record
		*/
		PL_API void StopRecord();

		/**
		*  @brief
		*    Starts the playback
		*
		*  @param[in] sName
		*    Record name, must be valid
		*
		*  @note
		*    - The currently used application camera will be feed with the recorded data
		*    - If recording is currently enabled, the recording will be stopped at once
		*/
		PL_API void StartPlayback(const PLCore::String &sName);

		/**
		*  @brief
		*    Returns whether or not playback is currently active
		*
		*  @return
		*    'true' if playback is currently active, else 'false'
		*/
		PL_API bool IsPlaying() const;

		/**
		*  @brief
		*    Stops the playback
		*/
		PL_API void StopPlayback();

		/**
		*  @brief
		*    Updates the camcorder component
		*/
		PL_API void Update();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Activates/deactivates certain scene node modifiers of the given scene node
		*
		*  @param[in] cSceneNode
		*    Scene node
		*  @param[in] bActive
		*    New scene node modifier active state
		*/
		void SetupSceneNodeModifiers(PLScene::SceneNode &cSceneNode, bool bActive);

		/**
		*  @brief
		*    Called when one of the keyframe animations has been stopped
		*/
		void OnAnimationStop();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		EngineApplication	 	  *m_pApplication;					/**< Owner application, always valid! */
		bool					   m_bRecording;					/**< Is recording currently enabled? */
		bool					   m_bPlaying;						/**< Is playback currently enabled? */
		bool					   m_bPlaybackFinished;				/**< Playback finished? */
		PLCore::String			   m_sRecordName;					/**< Current record name */
		PLScene::SceneNodeHandler  m_cCameraSceneNodeHandler;		/**< Recorded camera scene node handler */
		PLCore::String			   m_sCameraStartSceneContainer;	/**< Camera start scene container */
		PLCore::String			   m_sCameraStartName;				/**< Camera start name */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_TOOLS_CAMCORDER_H__
