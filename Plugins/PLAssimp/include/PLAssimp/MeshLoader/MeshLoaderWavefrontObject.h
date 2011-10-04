/*********************************************************\
 *  File: MeshLoaderWavefrontObject.h                    *
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


#ifndef __PLASSIMP_MESHLOADER_WAVEFRONTOBJECT_H__
#define __PLASSIMP_MESHLOADER_WAVEFRONTOBJECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLAssimp/MeshLoader/MeshLoader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLAssimp {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mesh loader implementation for obj (Wavefront Object) using Assimp
*/
class MeshLoaderWavefrontObject : public MeshLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, MeshLoaderWavefrontObject, "PLAssimp", PLAssimp::MeshLoader, "Mesh loader implementation for obj (Wavefront Object) using Assimp")
		// Properties
		pl_properties
			pl_property("Formats",	"obj,OBJ")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_3(LoadParams,	pl_ret_type(bool),	PLMesh::Mesh&,	PLCore::File&,	bool,	"Load method. Parameters: First 'bool' parameter determines whether or not the mesh is static.",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool LoadParams(PLMesh::Mesh &cMesh, PLCore::File &cFile, bool bStatic);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		MeshLoaderWavefrontObject();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~MeshLoaderWavefrontObject();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLAssimp


#endif // __PLASSIMP_MESHLOADER_WAVEFRONTOBJECT_H__
