/*********************************************************\
 *  File: Joint.h                                        *
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


#ifndef __PLMESH_JOINT_H__
#define __PLMESH_JOINT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Base/Element.h>
#include "PLMesh/JointState.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Skeleton joint element
*/
class Joint : public PLGeneral::Element<Joint>, public JointState {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Skeleton;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sName
		*    Element name to set
		*  @param[in] pManager
		*    Element manager using this element, can be NULL
		*/
		PLMESH_API Joint(const PLGeneral::String &sName = "", PLGeneral::ElementManager<Joint> *pManager = NULL);

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~Joint();

		/**
		*  @brief
		*    Get the ID of this joint
		*
		*  @return
		*    ID of this joint, < 0 normally means this is an unsed ID
		*/
		PLMESH_API int GetID() const;

		/**
		*  @brief
		*    Set the ID this joint
		*
		*  @param[in] nID
		*    ID of this joint
		*/
		PLMESH_API void SetID(int nID = -1);

		/**
		*  @brief
		*    Get the parent joint number of this joint
		*
		*  @return
		*    Number of the parent joint number, if < 0 no parent
		*/
		PLMESH_API int GetParent() const;

		/**
		*  @brief
		*    Set the parent joint number of this joint
		*
		*  @param[in] nParent
		*    Number of the parent joint number, if < 0 no parent
		*/
		PLMESH_API void SetParent(int nParent = -1);

		/**
		*  @brief
		*    Gets an array with the child joints
		*
		*  @return
		*    Child joints array
		*
		*  @note
		*    - Call Skeleton::UpdateJointInformation() after changing parent/child joints!
		*/
		PLMESH_API const PLGeneral::Array<PLGeneral::uint32> &GetChildren() const;

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    This joint
		*/
		PLMESH_API Joint &operator =(const Joint &cSource);

		/**
		*  @brief
		*    Compares two joints
		*
		*  @param[in] cJoint
		*    Joint to compare with
		*
		*  @return
		*    'true' if both joints are equal, else 'false'
		*/
		PLMESH_API bool operator ==(const Joint &cJoint) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		int									m_nID;			/**< Joint ID */
		int									m_nParent;		/**< Number of the parent joint */
		PLGeneral::Array<PLGeneral::uint32>	m_lstChildren;	/**< Array of child joints */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_JOINT_H__
