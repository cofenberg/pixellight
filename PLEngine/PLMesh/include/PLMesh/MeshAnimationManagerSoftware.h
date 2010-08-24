/*********************************************************\
 *  File: MeshAnimationManagerSoftware.h                 *
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


#ifndef __PLMESH_MESHANIMATIONMANAGERSOFTWARE_H__
#define __PLMESH_MESHANIMATIONMANAGERSOFTWARE_H__
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
*    This is a software manager for the mesh animation element
*/
class MeshAnimationManagerSoftware : public MeshAnimationManager {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLMESH_RTTI_EXPORT, MeshAnimationManagerSoftware, "PLMesh", PLMesh::MeshAnimationManager, "This is a software manager for the mesh animation element")
		pl_constructor_0(ParameterConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLMESH_API MeshAnimationManagerSoftware();

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~MeshAnimationManagerSoftware();


	//[-------------------------------------------------------]
	//[ Public virtual MeshAnimationManager functions         ]
	//[-------------------------------------------------------]
	public:
		PLMESH_API virtual bool Apply(MeshHandler &cMeshHandler) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_MESHANIMATIONMANAGERSOFTWARE_H__
