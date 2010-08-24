/*********************************************************\
 *  File: Wav.cpp                                        *
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
#include <PLGeneral/Container/Array.h>
#include <PLGeneral/File/File.h>
#include "PLSoundOpenAL/StreamWav.h" // For StreamWav::Header
#include "PLSoundOpenAL/Wav.h"


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
*    This function loads a '.wav' file into a memory buffer and returns
*    the format and frequency
*/
bool LoadWav(File *pFile, Array<uint8> &lstBuffer, ALenum &nFormat, ALsizei &nFrequency)
{
	if (pFile) {
		// Read wav header
		StreamWav::Header sWavHeader;
		pFile->Read(&sWavHeader, sizeof(StreamWav::Header), 1);

		// Check if the wav-file has no compressed data
		if (sWavHeader.Format == 1) {
			// Check the number of channels... and bits per sample
			if (sWavHeader.Channels == 1)
				nFormat = (sWavHeader.BitsPerSample == 16) ? AL_FORMAT_MONO16   : AL_FORMAT_MONO8;
			else
				nFormat = (sWavHeader.BitsPerSample == 16) ? AL_FORMAT_STEREO16 : AL_FORMAT_STEREO8;

			// The frequency of the sampling rate
			nFrequency = sWavHeader.SamplesPerSec;

			// Keep reading until all is read
			static const uint32 BufferSize = 32768;	// 32 KB buffers
			uint8 nArray[BufferSize];				// Local fixed size array
			pFile->Seek(sizeof(StreamWav::Header));
			long nSize   = BufferSize;
			long nToRead = sWavHeader.dataSize;
			while (nToRead > 0) {
				if (pFile->IsEof()) {
					// Error!
					return false;
				}
				if (nToRead<BufferSize)
					nSize = nToRead;
				long nBytes = pFile->Read(nArray, 1, nSize);
				if (nBytes <= 0 && !pFile->IsEof()) {
					// Error!
					return false;
				}
				lstBuffer.Add(nArray, nBytes);
				nToRead -= nBytes;
			}

			// Close the file
			delete pFile;

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

/**
*  @brief
*    This function loads a '.wav' file into a memory buffer and returns
*    the format and frequency
*/
bool LoadWav(const uint8 nData[], uint32 nSize, Array<uint8> &lstBuffer, ALenum &nFormat, ALsizei &nFrequency)
{
	// Check parameter
	if (nSize) {
		// Set stream size
		uint32 nSizeToRead = nSize - sizeof(StreamWav::Header);

		// Read wav header
		StreamWav::Header sWavHeader;
		MemoryManager::Copy(&sWavHeader, nData, sizeof(StreamWav::Header));

		// Check if the wav-file has no compressed data
		if (sWavHeader.Format == 1) {
			// Check the number of channels... and bits per sample
			if (sWavHeader.Channels == 1)
				nFormat = (sWavHeader.BitsPerSample == 16) ? AL_FORMAT_MONO16   : AL_FORMAT_MONO8;
			else
				nFormat = (sWavHeader.BitsPerSample == 16) ? AL_FORMAT_STEREO16 : AL_FORMAT_STEREO8;

			// The frequency of the sampling rate
			nFrequency = sWavHeader.SamplesPerSec;

			// Copy the data to the buffer
			const uint8 *pnTemp = nData;
			lstBuffer.Add(pnTemp + sizeof(StreamWav::Header), nSizeToRead);

			// Done
			return true;
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundOpenAL
