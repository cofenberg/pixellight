/*********************************************************\
 *  File: MeshAnimationManagerHardware.h                 *
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


#ifndef __PLMESH_MESHANIMATIONMANAGERHARDWARE_H__
#define __PLMESH_MESHANIMATIONMANAGERHARDWARE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLMesh/MeshAnimationManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    This is a hardware manager for the mesh animation element
*/
class MeshAnimationManagerHardware : public MeshAnimationManager {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLMESH_RTTI_EXPORT, MeshAnimationManagerHardware, "PLMesh", PLMesh::MeshAnimationManager, "This is a hardware manager for the mesh animation element")
		// Constructors
		pl_constructor_0(ParameterConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLMESH_API MeshAnimationManagerHardware();

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~MeshAnimationManagerHardware();


	//[-------------------------------------------------------]
	//[ Public virtual MeshAnimationManager functions         ]
	//[-------------------------------------------------------]
	public:
		PLMESH_API virtual bool Apply(MeshHandler &cMeshHandler) const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_MESHANIMATIONMANAGERHARDWARE_H__
