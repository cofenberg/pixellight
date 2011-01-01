/*********************************************************\
 *  File: SoundManager.h                                 *
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


#ifndef __PLSOUNDFMODEX_SOUNDMANAGER_H__
#define __PLSOUNDFMODEX_SOUNDMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLSound/SoundManager.h>
#include "PLSoundFMODEx/PLSoundFMODEx.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLSoundFMODEx {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    FMOD Ex sound backend
*/
class SoundManager : public PLSound::SoundManager {


	//[-------------------------------------------------------]
	//[ Public data types                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Output
		*/
		enum EOutput {
			AUTODETECT,
			UNKNOWN,
			NOSOUND,
			WAVWRITER,
			NOSOUND_NRT,
			WAVWRITER_NRT,
			DSOUND,
			WINMM,
			ASIO,
			OSS,
			ALSA,
			ESD,
			SOUNDMANAGER,
			COREAUDIO,
			XBOX,
			PS2,
			PS3,
			GC,
			XBOX360,
			PSP,
			WII,
			MAX
		};
		pl_enum(EOutput)
			pl_enum_value(AUTODETECT,		"")
			pl_enum_value(UNKNOWN,			"")
			pl_enum_value(NOSOUND,			"")
			pl_enum_value(WAVWRITER,		"")
			pl_enum_value(NOSOUND_NRT,		"")
			pl_enum_value(WAVWRITER_NRT,	"")
			pl_enum_value(DSOUND,			"")
			pl_enum_value(WINMM,			"")
			pl_enum_value(ASIO,				"")
			pl_enum_value(OSS,				"")
			pl_enum_value(ALSA,				"")
			pl_enum_value(ESD,				"")
			pl_enum_value(SOUNDMANAGER,		"")
			pl_enum_value(COREAUDIO,		"")
			pl_enum_value(XBOX,				"")
			pl_enum_value(PS2,				"")
			pl_enum_value(PS3,				"")
			pl_enum_value(GC,				"")
			pl_enum_value(XBOX360,			"")
			pl_enum_value(PSP,				"")
			pl_enum_value(WII,				"")
			pl_enum_value(MAX,				"")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SoundManager, "PLSoundFMODEx", PLSound::SoundManager, "FMOD Ex sound backend")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(Driver,		PLGeneral::int32,		-1,			ReadWrite,	DirectValue,	"Selects a soundcard driver. It is used when an output mode has enumerated more than one output device, and you need to select between them.",		"")
		pl_attribute(Output,		pl_enum_type(EOutput),	AUTODETECT,	ReadWrite,	DirectValue,	"This function selects the output mode for the platform. This is for selecting different OS specific API's which might have different features.",	"")
		pl_attribute(Channels,		PLGeneral::uint32,		32,			ReadWrite,	DirectValue,	"Maximum number of SOFTWARE channels available (HARDWARE channels are autodetected)",																"")
		pl_attribute(BufferLength,	PLGeneral::uint32,		1024,		ReadWrite,	DirectValue,	"The mixer engine block size in samples. Use this to adjust mixer update granularity.",																"")
		pl_attribute(NumOfBuffers,	PLGeneral::uint32,		4,			ReadWrite,	DirectValue,	"The mixer engine number of buffers used. Use this to adjust mixer latency.",																		"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Checks for an FMOD Ex error
		*
		*  @param[in] nResult
		*    FMOD Ex error code to check
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		static bool ErrorCheck(FMOD_RESULT nResult);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		SoundManager();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SoundManager();

		/**
		*  @brief
		*    Adds an active sound source to the sound manager
		*
		*  @param[in] cSource
		*    Sound source to add
		*
		*  @return
		*    'true' if all went fine and the sound source was added to the sound manager,
		*    else 'false'
		*
		*  @note
		*    - The sound source itself is only added to the sound manager's list of sources!
		*/
		bool AddActiveSource(PLSound::Source &cSource);

		/**
		*  @brief
		*    Removes an active sound source from the sound manager
		*
		*  @param[in] cSource
		*    Sound source to remove
		*
		*  @return
		*    'true' if all went fine and the sound source was removed from the
		*    sound manager, else 'false' (maybe the source isn't in the sound manager)
		*
		*  @note
		*    - The sound source itself isn't destroyed, it is just removed
		*      from the sound manager's list of sources! 
		*/
		bool RemoveActiveSource(PLSound::Source &cSource);

		/**
		*  @brief
		*    Returns the FMOD Ex system instance
		*
		*  @return
		*    The FMOD Ex system instance, NULL on error
		*/
		FMOD::System *GetSystem() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		FMOD::System					   *m_pSystem;								/**< FMOD Ex system instance, can be NULL */
		float								m_fVolume;								/**< Master volume */
		float								m_fPitch;								/**< Master pitch */
		float								m_fDopplerFactor;						/**< Doppler factor */
		PLMath::Vector3						m_vListenerAttributes[ListenerNumber];	/**< Listener attributes */
		PLGeneral::Array<PLSound::Source*>  m_lstActiveSources;						/**< Current active sound sources of this sound manager */


	//[-------------------------------------------------------]
	//[ Public virtual PLSound::SoundManager functions        ]
	//[-------------------------------------------------------]
	public:
		virtual PLGeneral::String GetDescription() const;
		virtual bool GetFormatList(PLGeneral::List<Format> &lstList) const;
		virtual float GetVolume() const;
		virtual void SetVolume(float fVolume = 1.0f);
		virtual float GetPitch() const;
		virtual void SetPitch(float fPitch = 1.0f);
		virtual float GetDopplerFactor() const;
		virtual void SetDopplerFactor(float fFactor = 1.0f);

		//[-------------------------------------------------------]
		//[ Create sound buffer/source                            ]
		//[-------------------------------------------------------]
		virtual PLSound::Buffer *CreateSoundBuffer(const PLGeneral::String &sFilename = "", bool bStream = false);
		virtual PLSound::Source *CreateSoundSource(PLSound::Buffer *pSoundBuffer = NULL);

		//[-------------------------------------------------------]
		//[ Listener                                              ]
		//[-------------------------------------------------------]
		virtual PLMath::Vector3 GetListenerAttribute(EListener nAttribute) const;
		virtual bool SetListenerAttribute(EListener nAttribute, const PLMath::Vector3 &vV);


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::ResourceManager functions      ]
	//[-------------------------------------------------------]
	public:
		virtual bool Init();
		virtual bool DeInit();
		virtual bool Update();


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ResourceManager functions     ]
	//[-------------------------------------------------------]
	private:
		virtual PLSound::Buffer *CreateResource(const PLGeneral::String &sName);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundFMODEx


#endif // __PLSOUNDFMODEX_SOUNDMANAGER_H__
