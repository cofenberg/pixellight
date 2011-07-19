/*********************************************************\
 *  File: MeshLoaderAse.h                                *
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


#ifndef __PLDEFAULTFILEFORMATS_3DSTUDIOMAX_MESHLOADER_ASE_H__
#define __PLDEFAULTFILEFORMATS_3DSTUDIOMAX_MESHLOADER_ASE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMesh/Loader/MeshLoader.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mesh loader implementation for ase (3D Studio Max ASCII Export)
*/
class MeshLoaderAse : public PLMesh::MeshLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, MeshLoaderAse, "PLDefaultFileFormats", PLMesh::MeshLoader, "Mesh loader implementation for ase (3D Studio Max ASCII Export)")
		// Properties
		pl_properties
			pl_property("Formats",	"ase,ASE")
			pl_property("Load",		"1")
			pl_property("Save",		"0")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_2(Load,		pl_ret_type(bool),	PLMesh::Mesh&,	PLCore::File&,			"Load method. The loaded mesh is static.",															"")
		pl_method_3(LoadParams,	pl_ret_type(bool),	PLMesh::Mesh&,	PLCore::File&,	bool,	"Load method. Parameters: First 'bool' parameter determines whether or not the mesh is static.",	"")
		pl_method_2(Save,		pl_ret_type(bool),	PLMesh::Mesh&,	PLCore::File&,			"Save method",																						"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool Load(PLMesh::Mesh &cMesh, PLCore::File &cFile);
		bool LoadParams(PLMesh::Mesh &cMesh, PLCore::File &cFile, bool bStatic);
		bool Save(PLMesh::Mesh &cMesh, PLCore::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		MeshLoaderAse();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~MeshLoaderAse();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats


#endif // __PLDEFAULTFILEFORMATS_3DSTUDIOMAX_MESHLOADER_ASE_H__
