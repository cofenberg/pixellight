/*********************************************************\
 *  File: JointUpVector.h                                *
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


#ifndef __PLPHYSICS_JOINTUPVECTOR_H__
#define __PLPHYSICS_JOINTUPVECTOR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include "PLPhysics/Joint.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract PL physics up vector joint
*
*  @remarks
*    This function creates an up vector joint. An up vector joint is a constraint that allows a body
*    to translate freely in 3d space, but it only allows the body to rotate around the pin direction
*    vector. This could be use by the application to control a character with physics and collision
*    Since the up vector joint is a unuary constraint, there is not need to have user callback or
*    user data assigned to it. The application can simple hold to the joint handle and update the pin
*    on the force callback function of the rigid body owning the joint.
*
*  @note
*    - This joint type has no parent
*/
class JointUpVector : public Joint {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~JointUpVector();

		/**
		*  @brief
		*    Returns the aligning vector in world space
		*
		*  @return
		*    The aligning vector in world space
		*/
		PLPHYSICS_API const PLMath::Vector3 &GetPinDir() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cWorld
		*    World this joint is in
		*  @param[in] cJointImpl
		*    Reference to the physics API specific joint implementation
		*  @param[in] cParentBody
		*    Reference to the parent rigid body
		*  @param[in] vPinDir
		*    The aligning vector in world space
		*/
		PLPHYSICS_API JointUpVector(World &cWorld, JointImpl &cJointImpl, Body &cParentBody, const PLMath::Vector3 &vPinDir);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLMath::Vector3 m_vPinDir;	/**< The aligning vector in world space */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_JOINTUPVECTOR_H__
