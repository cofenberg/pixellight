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


#ifndef __PLSOUNDFMOD_SOUNDMANAGER_H__
#define __PLSOUNDFMOD_SOUNDMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLSound/SoundManager.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLSoundFMOD {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    FMOD sound backend
*/
class SoundManager : public PLSound::SoundManager {


	//[-------------------------------------------------------]
	//[ Public data types                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Sound card driver
		*/
		enum ESoundcardDriver {
			AUTODETECT,
			NOSOUND,
			WINMM,
			DSOUND,
			A3D,
			OSS,
			ESD,
			ALSA,
			ASIO,
			XBOX,
			PS2,
			MAC,
			GC,
			NONREALTIME
		};
		pl_enum(ESoundcardDriver)
			pl_enum_value(AUTODETECT,	"")
			pl_enum_value(NOSOUND,		"")
			pl_enum_value(WINMM,		"")
			pl_enum_value(DSOUND,		"")
			pl_enum_value(A3D,			"")
			pl_enum_value(OSS,			"")
			pl_enum_value(ESD,			"")
			pl_enum_value(ALSA,			"")
			pl_enum_value(ASIO,			"")
			pl_enum_value(XBOX,			"")
			pl_enum_value(PS2,			"")
			pl_enum_value(MAC,			"")
			pl_enum_value(GC,			"")
			pl_enum_value(NONREALTIME,	"")
		pl_enum_end

		/**
		*  @brief
		*    Quality
		*/
		enum EQuality {
			QUALITY_AUTODETECT = 4,
			QUALITY_FPU,
			QUALITY_MMXP5,
			QUALITY_MMXP6,
			MONO,
			QUALITY_MONO
		};
		pl_enum(EQuality)
			pl_enum_value(QUALITY_AUTODETECT,	"")
			pl_enum_value(QUALITY_FPU,			"")
			pl_enum_value(QUALITY_MMXP5,		"")
			pl_enum_value(QUALITY_MMXP6,		"")
			pl_enum_value(MONO,					"")
			pl_enum_value(QUALITY_MONO,			"")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SoundManager, "PLSoundFMOD", PLSound::SoundManager, "FMOD sound backend")
		// Attributes
		pl_attribute(BufferSize,	PLCore::uint32,					200,				ReadWrite,	DirectValue,	"FMOD internal mixing buffer size (in milliseconds)",																							"")
		pl_attribute(Output,		pl_enum_type(ESoundcardDriver),	AUTODETECT,			ReadWrite,	DirectValue,	"The output system to be used",																													"")
		pl_attribute(Driver,		PLCore::uint32,					0,					ReadWrite,	DirectValue,	"Selects a sound card driver. It is used when an output mode has enumerated more than one output device, and you need to select between them.",	"")
		pl_attribute(Mixer,			pl_enum_type(EQuality),			QUALITY_AUTODETECT,	ReadWrite,	DirectValue,	"Digital mixer type",																															"")
		pl_attribute(OutputRate,	PLCore::uint32,					44100,				ReadWrite,	DirectValue,	"Output rate in Hz between 4000 and 65535",																										"")
		pl_attribute(Channels,		PLCore::uint32,					32,					ReadWrite,	DirectValue,	"Maximum number of SOFTWARE channels available (HARDWARE channels are auto detected)",															"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


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


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float						    m_fVolume;								/**< Master volume */
		float						    m_fPitch;								/**< Master pitch */
		float						    m_fDopplerFactor;						/**< Doppler factor */
		PLMath::Vector3				    m_vListenerAttributes[ListenerNumber];	/**< Listener attributes */
		PLCore::Array<PLSound::Source*> m_lstActiveSources;						/**< Current active sound sources of this sound manager */


	//[-------------------------------------------------------]
	//[ Public virtual PLSound::SoundManager functions        ]
	//[-------------------------------------------------------]
	public:
		virtual PLCore::String GetDescription() const override;
		virtual bool GetFormatList(PLCore::List<Format> &lstList) const override;
		virtual float GetVolume() const override;
		virtual void SetVolume(float fVolume = 1.0f) override;
		virtual float GetPitch() const override;
		virtual void SetPitch(float fPitch = 1.0f) override;
		virtual float GetDopplerFactor() const override;
		virtual void SetDopplerFactor(float fFactor = 1.0f) override;

		//[-------------------------------------------------------]
		//[ Create sound buffer/source                            ]
		//[-------------------------------------------------------]
		virtual PLSound::Buffer *CreateSoundBuffer(const PLCore::String &sFilename = "", bool bStream = false) override;
		virtual PLSound::Source *CreateSoundSource(PLSound::Buffer *pSoundBuffer = nullptr) override;

		//[-------------------------------------------------------]
		//[ Listener                                              ]
		//[-------------------------------------------------------]
		virtual PLMath::Vector3 GetListenerAttribute(EListener nAttribute) const override;
		virtual bool SetListenerAttribute(EListener nAttribute, const PLMath::Vector3 &vV) override;


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::ResourceManager functions      ]
	//[-------------------------------------------------------]
	public:
		virtual bool Init() override;
		virtual bool DeInit() override;
		virtual bool Update() override;


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ResourceManager functions     ]
	//[-------------------------------------------------------]
	private:
		virtual PLSound::Buffer *CreateResource(const PLCore::String &sName) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundFMOD


#endif // __PLSOUNDFMOD_SOUNDMANAGER_H__
