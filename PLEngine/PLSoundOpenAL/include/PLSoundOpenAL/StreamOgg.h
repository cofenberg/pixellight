/*********************************************************\
 *  File: StreamOgg.h                                    *
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


#ifndef __PLSOUNDOPENAL_STREAMOGG_H__
#define __PLSOUNDOPENAL_STREAMOGG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <vorbis/vorbisfile.h>
#include "PLSoundOpenAL/Stream.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLSoundOpenAL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Ogg stream
*
*  @remarks
*    Ogg Vorbis (or just OGG) is an open-source audio compression format similar to MP3.
*    Actually, the file .ogg file format can contain other things, but let's just assume
*    it is audio data in here. One of the biggest advantages it has over MP3 is that it
*    is patent-free. This means you do not need to pay a license fee in order to encode
*    or decode OGG files.
*/
class StreamOgg : public Stream {


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
		StreamOgg(ALuint nSource, const Buffer &cBuffer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~StreamOgg();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Opens the stream
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool OpenStream();

		/**
		*  @brief
		*    Fill a buffer
		*
		*  @param[in] nBuffer
		*    Buffer to fill
		*
		*  @return
		*    'true' if all went fine, else 'false' (end of stream reached?)
		*/
		bool FillBuffer(ALuint nBuffer);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		OggVorbis_File     m_cOggStream;	/**< Ogg stream */
		vorbis_info		  *m_pVorbisInfo;	/**< Vorbis information, can be NULL */
		ALenum			   m_nFormat;		/**< Format */
		ALuint			   m_nBuffers[2];	/**< Back and front buffer */
		PLGeneral::uint32  m_nSwapSize;		/**< Swap buffer size in bytes */
		PLGeneral::uint8  *m_pnSwap;		/**< Buffer used within FillBuffer(), can be NULL */


	//[-------------------------------------------------------]
	//[ Public virtual Stream functions                       ]
	//[-------------------------------------------------------]
	public:
		virtual bool Init();
		virtual bool IsInitialized() const;
		virtual void DeInit();
		virtual bool Update();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundOpenAL


#endif // __PLSOUNDOPENAL_STREAMOGG_H__
