/*********************************************************\
 *  File: MeshLoaderSmd.h                                *
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


#ifndef __PLDEFAULTFILEFORMATS_HALFLIFE_MESHLOADER_SMD_H__
#define __PLDEFAULTFILEFORMATS_HALFLIFE_MESHLOADER_SMD_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMesh/Loader/MeshLoader.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMesh {
	class Joint;
	class Skeleton;
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
*    Mesh loader implementation for smd version 1
*    (Valves skeletal model from Half-Life)
*/
class MeshLoaderSmd : public PLMesh::MeshLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, MeshLoaderSmd, "PLDefaultFileFormats", PLMesh::MeshLoader, "Mesh loader implementation for smd version 1")
		// Properties
		pl_properties
			pl_property("Formats",	"smd,SMD")
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
		MeshLoaderSmd();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~MeshLoaderSmd();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Recursive joint state calculations
		*
		*  @param[in] cSkeleton
		*    Skeleton
		*  @param[in] cJoint
		*    Current joint
		*  @param[in] pParentJoint
		*    Parent joint, can be a null pointer
		*/
		void RecCalculateStates(const PLMesh::Skeleton &cSkeleton, PLMesh::Joint &cJoint, PLMesh::Joint *pParentJoint) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats


#endif // __PLDEFAULTFILEFORMATS_HALFLIFE_MESHLOADER_SMD_H__
