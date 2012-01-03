/*********************************************************\
 *  File: ChunkTest.cpp                                  *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLCore/Core/MemoryManager.h>
#include <PLCore/Tools/Chunk.h>
#include "PLTestBase/Core/ChunkTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *ChunkTest::GetName() const
{
	return "ChunkTest";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void ChunkTest::Test()
{
	Chunk cChunk;
	if (cChunk.LoadByFilename("ScaleData.chunk")) {
		uint8 *pData = new uint8[cChunk.GetTotalNumOfBytes()];
		MemoryManager::Copy(pData, cChunk.GetData(), cChunk.GetTotalNumOfBytes());
		if (cChunk.SaveByFilename("ScaleData.xchunk")) {
			if (cChunk.LoadByFilename("ScaleData.xchunk")) {
				// When using floating point data, we may have a loss in precision...
				for (uint32 i=0; i<cChunk.GetTotalNumOfBytes(); i++) {
					uint8 nByte1 = pData[i];
					uint8 nByte2 = cChunk.GetData()[i];
					if (nByte1 != nByte2) {
						int nError = 1;
						nError = 1;
					}
				}
				cChunk.SaveByFilename("ScaleData_Copy.chunk");
				cChunk.SaveByFilename("ScaleData_Copy.xchunk");
			}
		}
	}
}
