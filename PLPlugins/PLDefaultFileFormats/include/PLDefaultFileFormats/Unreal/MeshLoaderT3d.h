/*********************************************************\
 *  File: MeshLoaderT3d.h                                *
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


#ifndef __PLDEFAULTFILEFORMATS_UNREAL_MESHLOADER_T3D_H__
#define __PLDEFAULTFILEFORMATS_UNREAL_MESHLOADER_T3D_H__
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
*    Mesh loader implementation for t3d (Unreal text file)
*
*  @note
*    - Only polygons are used
*
*  @see
*    - http://unreal.jall.org/tutorials/t3d.html or google around :)
*/
class MeshLoaderT3d : public PLMesh::MeshLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, MeshLoaderT3d, "PLDefaultFileFormats", PLMesh::MeshLoader, "Mesh loader implementation for t3d (Unreal text file)")
		pl_properties
			pl_property("Formats",	"t3d,T3D")
			pl_property("Load",		"1")
			pl_property("Save",		"0")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_2(Load, bool, PLMesh::Mesh&, PLGeneral::File&, "Load method. The loaded mesh is static.", "")
		pl_method_3(LoadParams, bool, PLMesh::Mesh&, PLGeneral::File&, bool, "Load method. Parameters: First 'bool' parameter determines whether or not the mesh is static.", "")
		pl_method_2(Save, bool, PLMesh::Mesh&, PLGeneral::File&, "Save method", "")
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
		MeshLoaderT3d();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~MeshLoaderT3d();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Recursive section skip
		*
		*  @param[in] cTokenizer
		*    Tokenizer to use
		*/
		void SkipSectionRec(PLGeneral::Tokenizer &cTokenizer) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats


#endif // __PLDEFAULTFILEFORMATS_UNREAL_MESHLOADER_T3D_H__
