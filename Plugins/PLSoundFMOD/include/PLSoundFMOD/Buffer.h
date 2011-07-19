/*********************************************************\
 *  File: Buffer.h                                       *
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


#ifndef __PLSOUNDFMOD_BUFFER_H__
#define __PLSOUNDFMOD_BUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLSound/Buffer.h>
#include "PLSoundFMOD/PLSoundFMOD.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLSoundFMOD {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    FMOD sound buffer resource
*/
class Buffer : public PLSound::Buffer {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Source;
	friend class SoundManager;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Buffer();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSoundManager
		*    Owner sound manager
		*  @param[in] sName
		*    Resource name to set
		*  @param[in] bStream
		*    Stream the file?
		*/
		Buffer(PLSound::SoundManager &cSoundManager, const PLCore::String &sName = "", bool bStream = false);

		/**
		*  @brief
		*    Plays the buffer
		*
		*  @return
		*    The channel where the buffer is played, < 0 on error
		*/
		int Play();

		/**
		*  @brief
		*    Checks whether the buffer is currently playing or not
		*
		*  @param[in] nChannel
		*    Sound channel
		*
		*  @return
		*    'true' if the buffer is playing at the moment, else 'false'
		*
		*  @note
		*    - In some chases (e.g. mods) no channels are used (< 0)
		*/
		bool IsPlaying(int nChannel) const;

		/**
		*  @brief
		*    Stops the buffer playback
		*
		*  @param[in] nChannel
		*    Sound channel
		*
		*  @see
		*    - IsPlaying()
		*/
		void Stop(int nChannel);

		/**
		*  @brief
		*    Sets the volume
		*
		*  @param[in] nChannel
		*    Sound channel
		*  @param[in] fVolume
		*    Volume (value from 0.0-1.0 -> 0.0 = silence, 1.0 = full volume)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @see
		*    - IsPlaying()
		*/
		bool SetVolume(int nChannel, float fVolume = 1.0f);

		/**
		*  @brief
		*    Sets whether the sound is looping or not
		*
		*  @param[in] nChannel
		*    Sound channel
		*  @param[in] bLooping
		*    If 'true' the sound is looping, else 'false'
		*
		*  @see
		*    - IsPlaying()
		*/
		void SetLooping(int nChannel, bool bLooping = false);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		FMUSIC_MODULE *m_pMod;		/**< Mod pointer, can be a null pointer */
		FSOUND_SAMPLE *m_pSample;	/**< Sample pointer, can be a null pointer */
		FSOUND_STREAM *m_pStream;	/**< Stream pointer, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Public virtual PLSound::Buffer functions              ]
	//[-------------------------------------------------------]
	public:
		virtual bool LoadBuffer(const PLCore::String &sFilename, bool bStream);
		virtual bool LoadBuffer(const PLCore::uint8 nData[], PLCore::uint32 nSize, bool bStream = false);
		virtual bool IsLoaded() const;
		virtual bool IsStreamed() const;


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Resource functions             ]
	//[-------------------------------------------------------]
	public:
		virtual bool Load(const PLCore::String &sName);
		virtual bool Unload();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundFMOD


#endif // __PLSOUNDFMOD_BUFFER_H__
