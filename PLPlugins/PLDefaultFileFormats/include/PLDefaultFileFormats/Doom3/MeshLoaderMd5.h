/*********************************************************\
 *  File: MeshLoaderMd5.h                                *
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


#ifndef __PLDEFAULTFILEFORMATS_DOOM3_MESHLOADER_MD5_H__
#define __PLDEFAULTFILEFORMATS_DOOM3_MESHLOADER_MD5_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMesh/Loader/MeshLoader.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class Tokenizer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mesh loader implementation for Md5 (Doom3) version 6 and 10
*
*  @remarks
*    You can create own md5 models for instance with Blender (a free 3d
*    application, http://www.blender.org) and the blender2md5 export script
*    (http://www.doom3world.org/phpbb2/viewtopic.php?t=1711).
*/
class MeshLoaderMd5 : public PLMesh::MeshLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, MeshLoaderMd5, "PLDefaultFileFormats", PLMesh::MeshLoader, "Mesh loader implementation for Md5 (Doom3) version 6 and 10")
		// Properties
		pl_properties
			pl_property("Formats",	"md5mesh,MD5MESH")
			pl_property("Load",		"1")
			pl_property("Save",		"0")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_2(Load,		bool,	PLMesh::Mesh&,	PLGeneral::File&,			"Load method. The loaded mesh is static.",															"")
		pl_method_3(LoadParams,	bool,	PLMesh::Mesh&,	PLGeneral::File&,	bool,	"Load method. Parameters: First 'bool' parameter determines whether or not the mesh is static.",	"")
		pl_method_2(Save,		bool,	PLMesh::Mesh&,	PLGeneral::File&,			"Save method",																						"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool Load(PLMesh::Mesh &cMesh, PLGeneral::File &cFile);
		bool LoadParams(PLMesh::Mesh &cMesh, PLGeneral::File &cFile, bool bStatic);
		bool Save(PLMesh::Mesh &cMesh, PLGeneral::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		MeshLoaderMd5();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~MeshLoaderMd5();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Md5 version 6 loader
		*
		*  @param[in] cMesh
		*    Mesh object
		*  @param[in] cTokenizer
		*    Tokenizer with the data to read
		*  @param[in] bStatic
		*    Static mesh? (better performance!)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadV6(PLMesh::Mesh &cMesh, PLGeneral::Tokenizer &cTokenizer, bool bStatic = false) const;

		/**
		*  @brief
		*    Md5 version 10 loader
		*
		*  @param[in] cMesh
		*    Mesh object
		*  @param[in] cTokenizer
		*    Tokenizer with the data to read
		*  @param[in] bStatic
		*    Static mesh? (better performance!)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadV10(PLMesh::Mesh &cMesh, PLGeneral::Tokenizer &cTokenizer, bool bStatic = false) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats


#endif // __PLDEFAULTFILEFORMATS_DOOM3_MESHLOADER_MD5_H__
