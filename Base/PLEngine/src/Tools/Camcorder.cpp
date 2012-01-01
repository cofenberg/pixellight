/*********************************************************\
 *  File: Camcorder.cpp                                  *
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
#include <PLCore/Log/Log.h>
#include <PLCore/Xml/Xml.h>
#include <PLCore/Tools/Loader.h>
#include <PLCore/Tools/LoaderImpl.h>
#include <PLRenderer/Animation/Animation.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodeModifiers/SNMPositionKeyframeAnimation.h>
#include <PLScene/Scene/SceneNodeModifiers/SNMRotationKeyframeAnimation.h>
#include "PLEngine/Application/EngineApplication.h"
#include "PLEngine/Tools/Camcorder.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
namespace PLEngine {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Camcorder)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Camcorder::Camcorder(EngineApplication &cApplication) :
	CamcorderDirectory(this),
	SlotOnAnimationStop(this),
	m_pApplication(&cApplication),
	m_bRecording(false),
	m_bPlaying(false),
	m_bPlaybackFinished(false)
{
}

/**
*  @brief
*    Destructor
*/
Camcorder::~Camcorder()
{
	// Stop the record
	StopRecord();
}

/**
*  @brief
*    Returns the owner application
*/
EngineApplication &Camcorder::GetApplication() const
{
	return *m_pApplication;
}

/**
*  @brief
*    Starts the record
*/
void Camcorder::StartRecord(const String &sName)
{
	// Stop the previous recording
	StopRecord();

	// Stop the playback
	StopPlayback();

	// Valid record name?
	if (sName.GetLength()) {
		// Get the currently used camera
		SceneNode *pCameraSceneNode = reinterpret_cast<SceneNode*>(m_pApplication->GetCamera());
		if (pCameraSceneNode) {
			// Keep a reference to this camera scene node
			m_cCameraSceneNodeHandler.SetElement(pCameraSceneNode);

			{ // Add position and rotation keyframe record modifiers to the camera scene node
				// Position
				const String sPositionChunkFilename = CamcorderDirectory.Get() + sName + "_Position.chunk";
				pCameraSceneNode->AddModifier("PLEngine::SNMPositionKeyframeRecord", "Keys=\"" + sPositionChunkFilename + "\" CoordinateSystem=\"Parent\"");	// "Parent" because we're using portals!

				// Rotation
				const String sRotationChunkFilename = CamcorderDirectory.Get() + sName + "_Rotation.chunk";
				pCameraSceneNode->AddModifier("PLEngine::SNMRotationKeyframeRecord", "Keys=\"" + sRotationChunkFilename + '\"');
			}

			// Backup the record name and some important camera information
			m_sRecordName					= sName;
			m_sCameraStartSceneContainer	= pCameraSceneNode->GetContainer()->GetAbsoluteName();
			m_sCameraStartName				= pCameraSceneNode->GetName();

			// Recording is now enabled
			m_bRecording = true;
		}
	}
}

/**
*  @brief
*    Returns whether or not recording is currently active
*/
bool Camcorder::IsRecording() const
{
	return m_bRecording;
}

/**
*  @brief
*    Stops the record
*/
void Camcorder::StopRecord()
{
	// Is recording currently enabled?
	if (m_bRecording) {
		// Recording is no longer enabled
		m_bRecording = false;

		// Get the recorded camera
		SceneNode *pCameraSceneNode = m_cCameraSceneNodeHandler.GetElement();
		if (pCameraSceneNode) {
			// Get the filename
			const String sFilename = CamcorderDirectory.Get() + m_sRecordName + ".cam";

			// Save the camcorder loadable
			SaveByFilename(sFilename);

			// Remove position and rotation keyframe record modifiers from the camera scene node
			pCameraSceneNode->RemoveModifier("PLEngine::SNMPositionKeyframeRecord");
			pCameraSceneNode->RemoveModifier("PLEngine::SNMRotationKeyframeRecord");
		}
	}
}

/**
*  @brief
*    Starts the playback
*/
void Camcorder::StartPlayback(const String &sName)
{
	// Stop the recording
	StopRecord();

	// Stop the previous playback
	StopPlayback();

	// Valid record name?
	if (sName.GetLength()) {
		// Get the currently used camera
		SceneNode *pCameraSceneNode = reinterpret_cast<SceneNode*>(m_pApplication->GetCamera());
		if (pCameraSceneNode) {
			// Get the filename
			const String sFilename = CamcorderDirectory.Get() + sName + ".cam";

			// Keep a reference to this camera scene node
			m_cCameraSceneNodeHandler.SetElement(pCameraSceneNode);

			// Disable certain scene node modifiers of the given scene node
			SetupSceneNodeModifiers(*pCameraSceneNode, false);

			// Backup the record name
			m_sRecordName = sName;

			// Playback is now enabled
			m_bPlaying			= true;
			m_bPlaybackFinished = false;

			// Load the camcorder loadable
			LoadByFilename(sFilename);
		}
	}
}

/**
*  @brief
*    Returns whether or not playback is currently active
*/
bool Camcorder::IsPlaying() const
{
	return m_bPlaying;
}

/**
*  @brief
*    Stops the playback
*/
void Camcorder::StopPlayback()
{
	// Is playback currently enabled?
	if (m_bPlaying) {
		// Playback is no longer enabled
		m_bPlaying			= false;
		m_bPlaybackFinished = false;

		// Get the used camera
		SceneNode *pCameraSceneNode = m_cCameraSceneNodeHandler.GetElement();
		if (pCameraSceneNode) {
			// Remove position and rotation keyframe animation modifiers from the camera scene node
			pCameraSceneNode->RemoveModifier("PLScene::SNMPositionKeyframeAnimation");
			pCameraSceneNode->RemoveModifier("PLScene::SNMRotationKeyframeAnimation");

			// Enable certain scene node modifiers of the given scene node
			SetupSceneNodeModifiers(*pCameraSceneNode, true);
		}
	}
}

/**
*  @brief
*    Updates the camcorder component
*/
void Camcorder::Update()
{
	// Playback finished?
	if (m_bPlaying && m_bPlaybackFinished) {
		// Stop the playback
		StopPlayback();

		// Emit the playback finished event
		SignalPlaybackFinished();
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Loadable functions             ]
//[-------------------------------------------------------]
bool Camcorder::Unload()
{
	// Stop the record
	StopRecord();

	// Call base implementation
	return Loadable::Unload();
}

String Camcorder::GetLoadableTypeName() const
{
	return "Camcorder";
}


//[-------------------------------------------------------]
//[ Protected virtual PLCore::Loadable functions          ]
//[-------------------------------------------------------]
bool Camcorder::CallLoadable(File &cFile, Loader &cLoader, const String &sMethod, const String &sParams)
{
	// Get the loader implementation
	LoaderImpl *pLoaderImpl = cLoader.GetImpl();
	if (pLoaderImpl) {
		// Load
		if (sParams.GetLength()) {
			pLoaderImpl->CallMethod(sMethod, "Param0=\"" + Type<Camcorder&>::ConvertToString(*this) + "\" Param1=\"" + Type<File&>::ConvertToString(cFile) + "\" " + sParams);
			return true;
		} else {
			Params<bool, Camcorder&, File&> cParams(*this, cFile);
			pLoaderImpl->CallMethod(sMethod, cParams);
			return cParams.Return;
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Activates/deactivates certain scene node modifiers of the given scene node
*/
void Camcorder::SetupSceneNodeModifiers(SceneNode &cSceneNode, bool bActive)
{
	// All modifiers influencing position and rotation
	for (uint32 i=0; i<cSceneNode.GetNumOfModifiers("PLScene::SNMTransform"); i++)
		cSceneNode.GetModifier("PLScene::SNMTransform", i)->SetActive(bActive);
}

/**
*  @brief
*    Called when one of the keyframe animations has been stopped
*/
void Camcorder::OnAnimationStop()
{
	// Job done...
	m_bPlaybackFinished = true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
