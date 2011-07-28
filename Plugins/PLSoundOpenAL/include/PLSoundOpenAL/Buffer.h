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


#ifndef __PLSOUNDOPENAL_BUFFER_H__
#define __PLSOUNDOPENAL_BUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLSound/Buffer.h>
#include "PLSoundOpenAL/PLSoundOpenAL.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class File;
}
namespace PLSoundOpenAL {
	class Stream;
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
*    OpenAL sound buffer resource
*/
class Buffer : public PLSound::Buffer {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
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

		/**
		*  @brief
		*    Creates a stream
		*
		*  @param[in] nSource
		*    Sound source using this stream
		*
		*  @return
		*    The created stream, a null pointer on error (maybe buffer isn't streamed)
		*/
		Stream *CreateStream(ALuint nSource);

		/**
		*  @brief
		*    Returns the OpenAL buffer
		*
		*  @return
		*    The OpenAL buffer
		*/
		ALuint GetOpenALBuffer() const;

		/**
		*  @brief
		*    Returns the buffer filename
		*
		*  @return
		*    The buffer filename
		*
		*  @note
		*    - Only valid if this buffer is a stream
		*/
		PLCore::String GetFilename() const;

		/**
		*  @brief
		*    Opens the file the buffer is using
		*
		*  @return
		*    The file the buffer is using, a null pointer on error
		*
		*  @note
		*    - The returned file is already opened for reading, don't forget
		*      to destroy the file object if you no longer need it
		*/
		PLCore::File *OpenFile() const;

		/**
		*  @brief
		*    Returns the buffer data
		*
		*  @return
		*    The buffer data
		*
		*  @note
		*    - If the data is a null pointer, the stream was loaded using a filename
		*
		*  @see
		*    - GetFilename()
		*/
		const PLCore::uint8 *GetData() const;

		/**
		*  @brief
		*    Returns the buffer data size (in bytes)
		*
		*  @return
		*    The buffer data size (in bytes)
		*
		*  @note
		*    - If the data is a null pointer, the stream was loaded using a filename
		*
		*  @see
		*    - GetData()
		*/
		PLCore::uint32 GetDataSize() const;


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


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool				 m_bStream;		/**< Is the buffer a stream? */
		ALuint				 m_nBuffer;		/**< Sound buffer */
		// For streaming
		PLCore::String		 m_sFilename;	/**< Filename */
		const PLCore::uint8 *m_pnData;		/**< Data, can be a null pointer */
		PLCore::uint32		 m_nDataSize;	/**< Data size (in bytes) */


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
		virtual bool Load(const PLCore::String &sFilename, const PLCore::String &sParams = "", const PLCore::String &sMethod = "") override;
		virtual bool Unload() override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundOpenAL


#endif // __PLSOUNDOPENAL_BUFFER_H__
