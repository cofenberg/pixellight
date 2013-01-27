/*********************************************************\
 *  File: Buffer.h                                       *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
		virtual bool LoadBuffer(const PLCore::String &sFilename, bool bStream) override;
		virtual bool LoadBuffer(const PLCore::uint8 nData[], PLCore::uint32 nSize, bool bStream = false) override;
		virtual bool IsLoaded() const override;
		virtual bool IsStreamed() const override;


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Loadable functions             ]
	//[-------------------------------------------------------]
	public:
		virtual bool LoadByFilename(const PLCore::String &sFilename, const PLCore::String &sParams = "", const PLCore::String &sMethod = "") override;
		virtual bool Unload() override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundFMOD


#endif // __PLSOUNDFMOD_BUFFER_H__
