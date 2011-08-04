/*********************************************************\
 *  File: Camcorder.cpp                                  *
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
#include <PLCore/Log/Log.h>
#include <PLCore/Xml/Xml.h>
#include <PLRenderer/Animation/Animation.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodeModifier.h>
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
			// Create XML document
			XmlDocument cDocument;

			// Add declaration
			XmlDeclaration *pDeclaration = new XmlDeclaration("1.0", "", "");
			cDocument.LinkEndChild(*pDeclaration);

			// Add camcorder
			XmlElement *pCamcorderElement = new XmlElement("Camcorder");
			pCamcorderElement->SetAttribute("Version", "1");

			// Write camera scene container name attribute
			pCamcorderElement->SetAttribute("SceneContainer", m_sCameraStartSceneContainer);

			// Write camera scene node name attribute
			pCamcorderElement->SetAttribute("SceneNode", m_sCameraStartName);

			// Get the position keyframe record modifier from the camera scene node
			SceneNodeModifier *pSceneNodeModifier = pCameraSceneNode->GetModifier("PLEngine::SNMPositionKeyframeRecord");
			if (pSceneNodeModifier) {
				// Create the position keys element
				XmlElement *pElement = new XmlElement("PositionKeys");

				// Set coordinate system attribute
				pElement->SetAttribute("CoordinateSystem", pSceneNodeModifier->GetAttribute("CoordinateSystem")->GetString());

				// Set frames per second attribute
				pElement->SetAttribute("FramesPerSecond", pSceneNodeModifier->GetAttribute("FramesPerSecond")->GetString());

				// Add value
				XmlText *pValue = new XmlText(pSceneNodeModifier->GetAttribute("Keys")->GetString());
				pElement->LinkEndChild(*pValue);

				// Link position keys element to parent
				pCamcorderElement->LinkEndChild(*pElement);
			}

			// Get the rotation keyframe record modifier from the camera scene node
			pSceneNodeModifier = pCameraSceneNode->GetModifier("PLEngine::SNMRotationKeyframeRecord");
			if (pSceneNodeModifier) {
				// Create the rotation keys element
				XmlElement *pElement = new XmlElement("RotationKeys");

				// Set frames per second attribute
				pElement->SetAttribute("FramesPerSecond", pSceneNodeModifier->GetAttribute("FramesPerSecond")->GetString());

				// Add value
				XmlText *pValue = new XmlText(pSceneNodeModifier->GetAttribute("Keys")->GetString());
				pElement->LinkEndChild(*pValue);

				// Link rotation keys element to parent
				pCamcorderElement->LinkEndChild(*pElement);
			}

			// Link camcorder element to parent
			cDocument.LinkEndChild(*pCamcorderElement);

			// Get the filename
			const String sFilename = CamcorderDirectory.Get() + m_sRecordName + ".cam";

			// Save config
			cDocument.Save(sFilename);

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

			// Load XML document
			XmlDocument cDocument;
			if (cDocument.Load(sFilename)) {
				// Get camcorder element
				const XmlElement *pCamcorderElement = cDocument.GetFirstChildElement("Camcorder");
				if (pCamcorderElement) {
					// Get the format version - must be 1
					const int nVersion = pCamcorderElement->GetAttribute("Version").GetInt();
					if (nVersion == 1) {
						// Keep a reference to this camera scene node
						m_cCameraSceneNodeHandler.SetElement(pCameraSceneNode);

						// Disable certain scene node modifers of the given scene node
						SetupSceneNodeModifiers(*pCameraSceneNode, false);

						// Backup the record name
						m_sRecordName = sName;

						// Playback is now enabled
						m_bPlaying			= true;
						m_bPlaybackFinished = false;

						// Get the scene container the camera is in
						const String sSceneContainer = pCamcorderElement->GetAttribute("SceneContainer");

						// Set the camera into this scene container
						SceneNode *pSceneNode = pCameraSceneNode->GetContainer()->GetByName(sSceneContainer);
						if (pSceneNode && pSceneNode->IsContainer())
							pCameraSceneNode->SetContainer(*static_cast<SceneContainer*>(pSceneNode));

						// Get and set the camera start name - not really required, the scene node name is just there to be complete
						//const String sSceneNode = pCamcorderElement->GetAttribute("SceneNode");
						//pCameraSceneNode->SetName(sSceneNode);

						// Get position keys
						const XmlElement *pXmlPositionKeysElement = pCamcorderElement->GetFirstChildElement("PositionKeys");
						if (pXmlPositionKeysElement) {
							// Get the coordinate system
							const String sCoordinateSystem = pXmlPositionKeysElement->GetAttribute("CoordinateSystem");

							// Get frames per second attribute
							const String sFramesPerSecond = pXmlPositionKeysElement->GetAttribute("FramesPerSecond");

							// Get value
							const XmlNode *pNode = pXmlPositionKeysElement->GetFirstChild();
							if (pNode && pNode->GetType() == XmlNode::Text) {
								const String sValue = pNode->GetValue();
								if (sValue.GetLength()) {
									// Add position keyframe animation modifiers to the camera scene node
									SNMPositionKeyframeAnimation *pSNMPositionKeyframeAnimation = static_cast<SNMPositionKeyframeAnimation*>(pCameraSceneNode->AddModifier("PLScene::SNMPositionKeyframeAnimation", "Flags=\"PlaybackNoLoop\" Keys=\"" + sValue + "\" CoordinateSystem=\"" + sCoordinateSystem + "\" FramesPerSecond=\"" + sFramesPerSecond + '\"'));

									// Connect the event handler
									if (pSNMPositionKeyframeAnimation)
										pSNMPositionKeyframeAnimation->GetAnimation().EventStop.Connect(SlotOnAnimationStop);
								}
							}
						}

						// Get rotation keys
						const XmlElement *pXmlRotationKeysElement = pCamcorderElement->GetFirstChildElement("RotationKeys");
						if (pXmlRotationKeysElement) {
							// Get frames per second attribute
							const String sFramesPerSecond = pXmlRotationKeysElement->GetAttribute("FramesPerSecond");

							// Get value
							const XmlNode *pNode = pXmlRotationKeysElement->GetFirstChild();
							if (pNode && pNode->GetType() == XmlNode::Text) {
								const String sValue = pNode->GetValue();
								if (sValue.GetLength()) {
									// Add rotation keyframe animation modifiers to the camera scene node
									SNMRotationKeyframeAnimation *pSNMRotationKeyframeAnimation = static_cast<SNMRotationKeyframeAnimation*>(pCameraSceneNode->AddModifier("PLScene::SNMRotationKeyframeAnimation", "Flags=\"PlaybackNoLoop\" Keys=\"" + sValue +  + "\" FramesPerSecond=\"" + sFramesPerSecond + '\"'));

									// Connect the event handler
									if (pSNMRotationKeyframeAnimation)
										pSNMRotationKeyframeAnimation->GetAnimation().EventStop.Connect(SlotOnAnimationStop);
								}
							}
						}
					} else {
						PL_LOG(Error, "Invalid format version")
					}
				} else {
					PL_LOG(Error, "Can't find 'Camcorder' element")
				}
			} else {
				PL_LOG(Error, cDocument.GetValue() + ": " + cDocument.GetErrorDesc())
			}
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

			// Enable certain scene node modifers of the given scene node
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
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Activates/deactivates certain scene node modifers of the given scene node
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
