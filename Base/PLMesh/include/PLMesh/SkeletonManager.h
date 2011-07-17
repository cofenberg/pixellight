/*********************************************************\
 *  File: SkeletonManager.h                              *
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


#ifndef __PLMESH_SKELETONMANAGER_H__
#define __PLMESH_SKELETONMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/ResourceManager.h>
#include "PLMesh/SkeletonHandler.h"
#include "PLMesh/Skeleton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Skeleton;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    This is a manager for the skeleton resource
*
*  @note
*    - Unloads unused resources automatically by default
*/
class SkeletonManager : public PLCore::ResourceManager<Skeleton> {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLMESH_API SkeletonManager();

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~SkeletonManager();


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ResourceManager functions     ]
	//[-------------------------------------------------------]
	private:
		virtual Skeleton *CreateResource(const PLGeneral::String &sName);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_SKELETONMANAGER_H__
