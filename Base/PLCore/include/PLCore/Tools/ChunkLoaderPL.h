/*********************************************************\
 *  File: ChunkLoaderPL.h                                *
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


#ifndef __PLCORE_CHUNKLOADER_PL_H__
#define __PLCORE_CHUNKLOADER_PL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Tools/ChunkLoader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Chunk loader implementation for the PixelLight binary (Little-Endian) chunk file format
*
*  @remarks
*    PixelLight mesh format description:
*    - uint32: Magic number
*    - uint32: Version
*      - uint32: The total size of the following chunk (header + data) in bytes
*      - uint32: Semantic
*      - uint32: Element type
*      - uint32: Components per element
*      - uint32: Number of elements
*      -         Data
*/
class ChunkLoaderPL : public ChunkLoader {


	//[-------------------------------------------------------]
	//[ Public constants                                      ]
	//[-------------------------------------------------------]
	public:
		static PLCORE_API const uint32 MAGIC;	/**< Magic number of the file format */
		static PLCORE_API const uint32 VERSION;	/**< File format version */


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCORE_RTTI_EXPORT, ChunkLoaderPL, "PLCore", PLCore::ChunkLoader, "Chunk loader implementation for the PixelLight binary (Little-Endian) chunk file format")
		// Properties
		pl_properties
			pl_property("Formats",	"chunk,CHUNK")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_2(Load,	pl_ret_type(bool),	Chunk&,			File&,	"Load method",	"")
		pl_method_2(Save,	pl_ret_type(bool),	const Chunk&,	File&,	"Save method",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		PLCORE_API bool Load(Chunk &cChunk, File &cFile);
		PLCORE_API bool Save(const Chunk &cChunk, File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCORE_API ChunkLoaderPL();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~ChunkLoaderPL();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Loader implementation for format version 1
		*
		*  @param[in] cChunk
		*    Chunk to load into
		*  @param[in] cFile
		*    Chunk file to read the data from
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadV1(Chunk &cChunk, File &cFile) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CHUNKLOADER_PL_H__
