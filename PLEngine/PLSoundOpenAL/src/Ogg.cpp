/*********************************************************\
 *  File: Ogg.cpp                                        *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <vorbis/vorbisfile.h>
#include <PLGeneral/File/File.h>
#include "PLSoundOpenAL/SoundManager.h"
#include "PLSoundOpenAL/Ogg.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLSoundOpenAL {


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    This function loads a '.ogg' file into a memory buffer and returns
*    the format and frequency
*/
bool LoadOGG(File *pFile, Array<uint8> &lstBuffer, ALenum &nFormat, ALsizei &nFrequency)
{
	bool bResult = false; // Error by default
	if (pFile) {
		// Try opening the given file
		OggVorbis_File oggFile;
		ov_callbacks ovc;
		ovc.read_func  = &SoundManager::read_func;
		ovc.seek_func  = &SoundManager::seek_func;
		ovc.close_func = &SoundManager::close_func;
		ovc.tell_func  = &SoundManager::tell_func;
		if (ov_open_callbacks(pFile, &oggFile, NULL, 0, ovc) == 0) {
			// Get some information about the OGG file
			vorbis_info *pInfo = ov_info(&oggFile, -1);

			// Check the number of channels... always use 16-bit samples
			nFormat = (pInfo->channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

			// The frequency of the sampling rate
			nFrequency = pInfo->rate;

			// Set to no error
			bResult = true;

			// Keep reading until all is read
			lstBuffer.Resize(pFile->GetSize()*100, false);
			static const uint32 BufferSize = 32768;	// 32 KB buffers
			uint8 nArray[BufferSize];	// Local fixed size array
			int nEndian = 0;			// 0 for Little-Endian, 1 for Big-Endian
			int nBitStream;
			long nBytes;
			do {
				// Read up to a buffer's worth of decoded sound data
				nBytes = ov_read(&oggFile, (char*)nArray, BufferSize, nEndian, 2, 1, &nBitStream);
				if (nBytes < 0) {
					// Error!
					bResult = false;
				} else {
					// Append to end of buffer
					lstBuffer.Add(nArray, nBytes);
				}
			} while (nBytes>0);

			// Cleanup (OpenAL takes over the file reference)
			ov_clear(&oggFile);
		}
	}

	// Done
	return bResult;
}

/**
*  @brief
*    This function loads a '.ogg' file into a memory buffer and returns
*    the format and frequency
*/
bool LoadOGG(const uint8 nData[], uint32 nSize, Array<uint8> &lstBuffer, ALenum &nFormat, ALsizei &nFrequency)
{
	bool bResult = false; // Error by default

	// Set data pointers
	SoundManager::MemData sMemData;
	sMemData.pnData  = nData;
	sMemData.pnDataE = sMemData.pnData + nSize;

	// Try opening the given file
	OggVorbis_File oggFile;
	ov_callbacks ovc;
	ovc.read_func  = &SoundManager::read_func_mem;
	ovc.seek_func  = &SoundManager::seek_func_mem;
	ovc.close_func = &SoundManager::close_func_mem;
	ovc.tell_func  = &SoundManager::tell_func_mem;
	if (!ov_open_callbacks(&sMemData, &oggFile, NULL, 0, ovc)) {
		// Get some information about the OGG file
		vorbis_info *pInfo = ov_info(&oggFile, -1);

		// Check the number of channels... always use 16-bit samples
		nFormat = (pInfo->channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

		// The frequency of the sampling rate
		nFrequency = pInfo->rate;

		// Set to no error
		bResult = true;

		// Keep reading until all is read
		static const uint32 BufferSize = 32768;	// 32 KB buffers
		uint8 nArray[32768];	// Local fixed size array
		int nEndian = 0;		// 0 for Little-Endian, 1 for Big-Endian
		int nBitStream;
		long nBytes;
		do {
			// Read up to a buffer's worth of decoded sound data
			nBytes = ov_read(&oggFile, (char*)nArray, 32768, nEndian, 2, 1, &nBitStream);
			if (nBytes < 0) {
				// Error!
				bResult = false;
			} else {
				// Append to end of buffer
				lstBuffer.Add(nArray, nBytes);
			}
		} while (nBytes>0);

		// Cleanup
		ov_clear(&oggFile);
	}

	// Done
	return bResult;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundOpenAL
