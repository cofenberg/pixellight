/*********************************************************\
 *  File: Stream.h                                       *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLSOUNDOPENAL_STREAM_H__
#define __PLSOUNDOPENAL_STREAM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLSoundOpenAL/PLSoundOpenAL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLSoundOpenAL {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Buffer;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract sound stream
*/
class Stream {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nSource
		*    Sound source using this stream
		*  @param[in] cBuffer
		*    Sound buffer this stream is using
		*/
		Stream(ALuint nSource, const Buffer &cBuffer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Stream();

		/**
		*  @brief
		*    Returns the sound source using this stream
		*
		*  @return
		*    The sound source using this stream
		*/
		ALuint GetSource() const;

		/**
		*  @brief
		*    Returns the sound buffer this stream is using
		*
		*  @return
		*    The sound buffer this stream is using
		*/
		const Buffer &GetBuffer() const;

		/**
		*  @brief
		*    Returns whether the stream is looping or not
		*
		*  @return
		*    'true' if stream is looping, else 'false'
		*/
		bool IsLooping() const;

		/**
		*  @brief
		*    Sets whether the stream is looping or not
		*
		*  @param[in] bLooping
		*    If 'true' the stream is looping, else 'false'
		*/
		void SetLooping(bool bLooping = false);


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Initializes the stream for playback
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Init() = 0;

		/**
		*  @brief
		*    Returns whether or not the stream is currently initialized (and therefore running)
		*
		*  @return
		*    'true' if the stream is currently initialized, else 'false'
		*/
		virtual bool IsInitialized() const = 0;

		/**
		*  @brief
		*    De-initializes the stream (playback stopped)
		*/
		virtual void DeInit() = 0;

		/**
		*  @brief
		*    Updates the stream
		*
		*  @return
		*    'true' if the stream is still active, else 'false' (maybe finished)
		*/
		virtual bool Update() = 0;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		ALuint		  m_nSource;	/**< Sound source using this stream */
		const Buffer *m_pBuffer;	/**< Sound buffer this stream is using (always valid!) */
		bool		  m_bLooping;	/**< Is the stream looping? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundOpenAL


#endif // __PLSOUNDOPENAL_STREAM_H__
