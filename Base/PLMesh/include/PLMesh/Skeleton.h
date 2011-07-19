/*********************************************************\
 *  File: Skeleton.h                                     *
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


#ifndef __PLMESH_SKELETON_H__
#define __PLMESH_SKELETON_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/List.h>
#include <PLCore/Container/Element.h>
#include <PLCore/Container/ElementManager.h>
#include <PLCore/Container/Resource.h>
#include <PLCore/Container/ResourceHandler.h>
#include <PLCore/Container/ResourceManager.h>
#include "PLMesh/JointAni.h"
#include "PLMesh/Joint.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Hierarchical skeleton class
*/
class Skeleton : public PLCore::Resource<Skeleton>, public PLCore::ElementManager<Joint>, public JointAni {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SkeletonManager;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~Skeleton();

		//[-------------------------------------------------------]
		//[ Joints                                                ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the skeleton root joint indices
		*
		*  @return
		*    Skeleton root joint indices
		*
		*  @note
		*    Must be called after joint parent/child manipulation
		*/
		PLMESH_API const PLCore::Array<PLCore::uint32> &GetRootJoints() const;

		/**
		*  @brief
		*    Updates the joint information
		*
		*  @see
		*    - GetRootJoints()
		*/
		PLMESH_API void UpdateJointInformation();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cManager
		*    Skeleton manager using this resource
		*  @param[in] sName
		*    Resource name to set
		*/
		Skeleton(PLCore::ResourceManager<Skeleton> &cManager, const PLCore::String &sName);

		/**
		*  @brief
		*    Recursive joint state calculations
		*
		*  @param[in] cJoint
		*    Current joint to process
		*  @param[in] pParentJoint
		*    Current parent joint to process, can be a null pointer
		*/
		void RecCalculateStates(Joint &cJoint, Joint *pParentJoint = nullptr) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::Array<PLCore::uint32> m_lstRootJoints;	/**< Array of root joint indices */


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ElementManager functions      ]
	//[-------------------------------------------------------]
	private:
		virtual Joint *CreateElement(const PLCore::String &sName);


	//[-------------------------------------------------------]
	//[ Public virtual AnimationInfo functions                ]
	//[-------------------------------------------------------]
	public:
		PLMESH_API Skeleton &operator =(const Skeleton &cSource);
		PLMESH_API virtual PLCore::String GetSourceName() const;


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Loadable functions             ]
	//[-------------------------------------------------------]
	public:
		PLMESH_API virtual bool Unload();
		PLMESH_API virtual PLCore::String GetLoadableTypeName() const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_SKELETON_H__
