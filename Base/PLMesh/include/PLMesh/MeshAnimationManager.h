/*********************************************************\
 *  File: MeshAnimationManager.h                         *
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


#ifndef __PLMESH_MESHANIMATIONMANAGER_H__
#define __PLMESH_MESHANIMATIONMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include <PLRenderer/Animation/AnimationManager.h>
#include "PLMesh/PLMesh.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class MeshHandler;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    This is a manager for the mesh animation element
*/
class MeshAnimationManager : public PLRenderer::AnimationManager, public PLCore::Object {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLMESH_RTTI_EXPORT, MeshAnimationManager, "PLMesh", PLCore::Object, "This is a manager for the mesh animation element")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns whether the mesh animation manager will reset the current joint states
		*    within the Apply() function before the current animation states are applied
		*
		*  @return
		*    'true' if the mesh animation manager will reset the current joint states, else 'false'
		*
		*  @remarks
		*    Normally, the manager will reset the current states to the base settings
		*    before the animation states are 'added'. If this isn't done automatically,
		*    you have to do this by yourself - but this way, you can do more complex
		*    animations.
		*/
		PLMESH_API bool GetResetJointStates() const;

		/**
		*  @brief
		*    Sets whether the mesh animation manager will reset the current joint states
		*    within the Apply() function before the current animation states are applied
		*
		*  @param[in] bReset
		*    Reset states?
		*/
		PLMESH_API void SetResetJointStates(bool bReset = true);

		/**
		*  @brief
		*    Returns whether the mesh animation manager will reset the current morph weights
		*    within the Apply() function before the current animation weights are applied
		*
		*  @return
		*    'true' if the mesh animation manager will reset the current morph weights, else 'false'
		*
		*  @see
		*    - GetResetJointStates()
		*/
		PLMESH_API bool GetResetMorphWeights() const;

		/**
		*  @brief
		*    Sets whether the mesh animation manager will reset the current morph weights
		*    within the Apply() function before the current animation weights are applied
		*
		*  @param[in] bReset
		*    Reset weights?
		*/
		PLMESH_API void SetResetMorphWeights(bool bReset = true);

		/**
		*  @brief
		*    Returns whether the mesh animation manager will apply base joint states before calculating
		*    the current states
		*
		*  @return
		*    'true' if apply base joint states before calculating the current states, else 'false'
		*/
		PLMESH_API bool GetApplyBaseJointStates() const;

		/**
		*  @brief
		*    Sets whether the mesh animation manager will apply base joint states before calculating
		*    the current states
		*
		*  @param[in] bApply
		*    Apply base joint states before calculating the current states?
		*/
		PLMESH_API void SetApplyBaseJointStates(bool bApply = true);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLMESH_API MeshAnimationManager();

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~MeshAnimationManager();


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Updates the mesh animation manager
		*
		*  @param[in] fTimeDifference
		*    Past time since last frame (use e.g. PLGeneral::Timing::GetInstance()->GetTimeDifference())
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLMESH_API virtual bool Update(float fTimeDifference);

		/**
		*  @brief
		*    Applies all animations to the given mesh handler
		*
		*  @param[in] cMeshHandler
		*    Mesh handler to apply the animations on
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*    This base implementation will only calculate the current skeleton handler
		*    joint states and morph target influences. Use a derived mesh animation manager
		*    to for instance manipulate the mesh, too.
		*/
		PLMESH_API virtual bool Apply(MeshHandler &cMeshHandler) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool m_bResetJointStates;		/**< Reset joint states? */
		bool m_bResetMorphWeights;		/**< Reset morph weights? */
		bool m_bApplyBaseJointStates;	/**< Apply base joint states? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_MESHANIMATIONMANAGER_H__
