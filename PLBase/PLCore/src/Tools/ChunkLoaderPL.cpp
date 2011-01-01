/*********************************************************\
 *  File: ChunkLoaderPL.cpp                              *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/File/File.h>
#include <PLGeneral/Log/Log.h>
#include "PLCore/Tools/Chunk.h"
#include "PLCore/Tools/ChunkLoaderPL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ChunkLoaderPL)


//[-------------------------------------------------------]
//[ Constants                                             ]
//[-------------------------------------------------------]
const uint32 ChunkLoaderPL::MAGIC	= 0x57754632;
const uint32 ChunkLoaderPL::VERSION	= 0;


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool ChunkLoaderPL::Load(Chunk &cChunk, File &cFile)
{
	// Read the magic number
	uint32 nMagic;
	cFile.Read(&nMagic, sizeof(uint32), 1);
	if (nMagic == MAGIC) {
		// Read the format version
		uint32 nVersion;
		cFile.Read(&nVersion, sizeof(uint32), 1);

		// Unkown
		if (nVersion > 0) {
			PL_LOG(Error, UnknownFormatVersion)

		// 0 (current)
		} else if (nVersion == 0) {
			return LoadV1(cChunk, cFile);
		}
	} else {
		PL_LOG(Error, "Invalid magic number")
	}

	// Error!
	return false;
}

bool ChunkLoaderPL::Save(const Chunk &cChunk, File &cFile)
{
	// Write the header
	cFile.Write(&MAGIC,   sizeof(uint32), 1);
	cFile.Write(&VERSION, sizeof(uint32), 1);

	// Write the total size of the following chunk (header + data) in bytes
	//                   Semantic         Data type        Components per element   Number of elements
	const uint32 nSize = sizeof(uint32) + sizeof(uint32) + sizeof(uint32) +         sizeof(uint32) +     cChunk.GetTotalNumOfBytes();
	cFile.Write(&nSize, sizeof(uint32), 1);

	// Write semantic
	const uint32 nSemantic = cChunk.GetSemantic();
	cFile.Write(&nSemantic, sizeof(uint32), 1);

	// Write element type
	const uint32 nElementType = cChunk.GetElementType();
	cFile.Write(&nElementType, sizeof(uint32), 1);

	// Write number of components per element
	const uint32 nNumOfComponentsPerElement = cChunk.GetNumOfComponentsPerElement();
	cFile.Write(&nNumOfComponentsPerElement, sizeof(uint32), 1);

	// Write number of elements
	const uint32 nNumOfElements = cChunk.GetNumOfElements();
	cFile.Write(&nNumOfElements, sizeof(uint32), 1);

	// Write chunk data
	cFile.Write(cChunk.GetData(), cChunk.GetTotalNumOfBytes(), 1);

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
ChunkLoaderPL::ChunkLoaderPL() :
	MethodLoad(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
ChunkLoaderPL::~ChunkLoaderPL()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loader implementation for format version 1
*/
bool ChunkLoaderPL::LoadV1(Chunk &cChunk, File &cFile) const
{
	// Read the total size of the following chunk (header + data) in bytes
	uint32 nSize = 0;
	cFile.Read(&nSize, sizeof(uint32), 1);

	// Read semantic
	uint32 nSemantic = 0;
	cFile.Read(&nSemantic, sizeof(uint32), 1);
	cChunk.SetSemantic((Chunk::ESemantic)nSemantic);

	// Read element type
	uint32 nElementType = 0;
	cFile.Read(&nElementType, sizeof(uint32), 1);

	// Validate the element type
	if (nElementType >= Chunk::Int8 && nElementType <= Chunk::Double) {
		// Read number of components per element
		uint32 nNumOfComponentsPerElement = 0;
		cFile.Read(&nNumOfComponentsPerElement, sizeof(uint32), 1);

		// Read number of elements
		uint32 nNumOfElements = 0;
		cFile.Read(&nNumOfElements, sizeof(uint32), 1);

		// Allocate the chunk data
		if (cChunk.Allocate((Chunk::EElementType)nElementType, nNumOfComponentsPerElement, nNumOfElements)) {
			// Get the header size
			//                                Semantic         Data type        Components per element   Number of elements
			static const uint32 nHeaderSize = sizeof(uint32) + sizeof(uint32) + sizeof(uint32) +         sizeof(uint32);

			// Validate the size of the chunk
			if ((nSize-nHeaderSize) == cChunk.GetTotalNumOfBytes()) {
				// Read chunk data
				cFile.Read(cChunk.GetData(), cChunk.GetTotalNumOfBytes(), 1);

				// Done
				return true;
			} else {
				PL_LOG(Error, "Invalid chunk size")
			}
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
