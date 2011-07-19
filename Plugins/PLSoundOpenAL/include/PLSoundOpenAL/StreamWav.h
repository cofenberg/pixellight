/*********************************************************\
 *  File: StreamWav.h                                    *
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


#ifndef __PLSOUNDOPENAL_STREAMWAV_H__
#define __PLSOUNDOPENAL_STREAMWAV_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLSoundOpenAL/Stream.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class File;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLSoundOpenAL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Wav stream
*/
class StreamWav : public Stream {


	//[-------------------------------------------------------]
	//[ Public structures                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Header of the 'wav' file format
		*/
		typedef struct {
			ALubyte		riff[4];
			ALsizei		riffSize;
			ALubyte		wave[4];
			ALubyte		fmt[4];
			ALuint		fmtSize;
			ALushort	Format;
			ALushort	Channels;
			ALuint		SamplesPerSec;
			ALuint		BytesPerSec;
			ALushort	BlockAlign;
			ALushort	BitsPerSample;
			ALubyte		data[4];
			ALuint		dataSize;
		} Header;


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
		StreamWav(ALuint nSource, const Buffer &cBuffer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~StreamWav();


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
		PLCore::File	    *m_pFile;		/**< Used on file streaming, can be a null pointer */
		const PLCore::uint8 *m_pnData;		/**< Used on memory streaming, can be a null pointer */
		ALuint				 m_nStreamSize;	/**< Stream size */
		ALuint				 m_nStreamPos;	/**< Current stream position */
		ALenum				 m_nFormat;		/**< Format */
		ALuint				 m_nFrequency;	/**< Frequency */
		ALuint				 m_nBuffers[2];	/**< Back and front buffer */
		PLCore::uint32		 m_nSwapSize;	/**< Swap buffer size in bytes */
		PLCore::uint8	    *m_pnSwap;		/**< Buffer used within FillBuffer(), can be a null pointer */


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


#endif // __PLSOUNDOPENAL_STREAMWAV_H__
