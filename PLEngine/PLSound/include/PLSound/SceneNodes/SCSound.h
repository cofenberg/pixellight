/*********************************************************\
 *  File: SCSound.h                                      *
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


#ifndef __PLSOUND_SCENENODES_SCSOUND_H__
#define __PLSOUND_SCENENODES_SCSOUND_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodeHandler.h>
#include "PLSound/PLSound.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLSound {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class SoundManager;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sound scene node container
*/
class SCSound : public PLScene::SceneContainer {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLSOUND_RTTI_EXPORT, SCSound, "PLSound", PLScene::SceneContainer, "Sound scene node container")
		// Attributes
		pl_attribute(SoundAPI,	PLGeneral::String,	"PLSoundOpenAL::SoundManager",	ReadWrite,	DirectValue,	"Name of the sound API this scene container is using",						"")
		pl_attribute(Volume,	float,				1.0f,							ReadWrite,	GetSet,			"Volume (value from 0.0-1.0 -> 0.0 = silence, 1.0 = full volume)",			"Min='0.0' Max='1.0'")
		pl_attribute(Pitch,		float,				1.0f,							ReadWrite,	GetSet,			"Pitch multiplier (pitch<1.0=slower/pitch=1.0=normal/pitch>1.0=faster)",	"Min='0.0'")
		pl_attribute(Listener,	PLGeneral::String,	"",								ReadWrite,	GetSet,			"Name of the scene node used as listener",									"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Slots
		pl_slot_0(OnUpdate,	"Called when the scene node needs to be updated",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLSOUND_API float GetVolume() const;
		PLSOUND_API void SetVolume(float fValue);
		PLSOUND_API float GetPitch() const;
		PLSOUND_API void SetPitch(float fValue);
		PLSOUND_API PLGeneral::String GetListener() const;
		PLSOUND_API void SetListener(const PLGeneral::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLSOUND_API SCSound();

		/**
		*  @brief
		*    Destructor
		*/
		PLSOUND_API virtual ~SCSound();

		/**
		*  @brief
		*    Returns the PL sound manager
		*
		*  @return
		*    The PL sound manager, a null pointer on error (if that's the case, something went totally wrong :)
		*/
		PLSOUND_API SoundManager *GetSoundManager() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void OnUpdate();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float						m_fVolume;				/**< Volume (value from 0.0-1.0 -> 0.0 = silence, 1.0 = full volume) */
		float						m_fPitch;				/**< Pitch multiplier (pitch<1.0=slower/pitch=1.0=normal/pitch>1.0=faster) */
		PLGeneral::String			m_sListener;			/**< Name of the scene node used as listener */
		SoundManager			   *m_pSoundManager;		/**< The PL sound manager, can be a null pointer */
		PLScene::SceneNodeHandler   m_cListenerNodeHandler;	/**< Listener scene node handler */


	//[-------------------------------------------------------]
	//[ Protected virtual PLScene::SceneNode functions        ]
	//[-------------------------------------------------------]
	protected:
		PLSOUND_API virtual void InitFunction();
		PLSOUND_API virtual void OnActivate(bool bActivate);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSound


#endif // __PLSOUND_SCENENODES_SCSOUND_H__
