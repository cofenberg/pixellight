/*********************************************************\
 *  File: MeshCreatorPartialDisk.h                       *
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


#ifndef __PLMESH_MESHCREATOR_PARTIALDISK_H__
#define __PLMESH_MESHCREATOR_PARTIALDISK_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include "PLMesh/Creator/MeshCreator.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Partial disk mesh creator class
*/
class MeshCreatorPartialDisk : public MeshCreator {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLMESH_RTTI_EXPORT, MeshCreatorPartialDisk, "PLMesh", PLMesh::MeshCreator, "Partial disk mesh creator class")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(InnerRadius,	float,				0.0f,								ReadWrite,	DirectValue,	"Inner radius of the partial disk (can be zero)",											"")
		pl_attribute(OuterRadius,	float,				0.5f,								ReadWrite,	DirectValue,	"Outer radius of the partial disk",															"")
		pl_attribute(Slices,		PLGeneral::uint32,	20,									ReadWrite,	DirectValue,	"Number of subdivisions around the z-axis",													"")
		pl_attribute(Loops,			PLGeneral::uint32,	1,									ReadWrite,	DirectValue,	"Number of concentric rings about the origin into which the partial disk is subdivided",	"")
		pl_attribute(StartAngle,	float,				0.0f,								ReadWrite,	DirectValue,	"Starting angle, in degrees, of the disk portion",											"")
		pl_attribute(SweepAngle,	float,				280.0f,								ReadWrite,	DirectValue,	"Sweep angle, in degrees, of the disk portion",												"")
		pl_attribute(Offset,		PLMath::Vector3,	PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	DirectValue,	"Offset to center",																			"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLMESH_API MeshCreatorPartialDisk();

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~MeshCreatorPartialDisk();


	//[-------------------------------------------------------]
	//[ Private virtual MeshCreator functions                 ]
	//[-------------------------------------------------------]
	private:
		virtual Mesh *Create(Mesh &cMesh, PLGeneral::uint32 nLODLevel = 0, bool bStatic = true) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_MESHCREATOR_PARTIALDISK_H__
