/*********************************************************\
 *  File: JointImpl.h                                    *
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


#ifndef __PLPHYSICSNEWTON_JOINTIMPL_H__
#define __PLPHYSICSNEWTON_JOINTIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include <PLPhysics/JointImpl.h>
#include "PLPhysicsNewton/PLPhysicsNewton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsNewton {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Newton physics joint implementation class
*/
class JointImpl : public PLPhysics::JointImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class World;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the Newton physics joint
		*
		*  @return
		*    The Newton physics joint, NULL on error (of that's the case, something went totally wrong :)
		*
		*  @note
		*    - Do NOT change the user data of the Newton physics joínt! (using NewtonJointSetUserData())
		*      This data MUST hold a pointer to the PL physics joint.
		*/
		PLPHYSICSNEWTON_API Newton::NewtonJoint *GetNewtonJoint() const;

		/**
		*  @brief
		*    Initializes the Newton physics joint
		*
		*  @param[in] cJoint
		*    PL physics joint this is the implementation from
		*  @param[in] cNewtonJoint
		*    Newton physics joint
		*/
		void InitializeNewtonJoint(PLPhysics::Joint &cJoint, Newton::NewtonJoint &cNewtonJoint);


	//[-------------------------------------------------------]
	//[ Public virtual PLPhysics::JointImpl functions         ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICSNEWTON_API virtual PLPhysics::Joint *GetJoint() const;
		PLPHYSICSNEWTON_API virtual bool IsBreakable() const;
		PLPHYSICSNEWTON_API virtual void SetBreakable(bool bBreakable);
		PLPHYSICSNEWTON_API virtual void GetBreakForce(PLMath::Vector3 &vForce) const;
		PLPHYSICSNEWTON_API virtual void SetBreakForce(const PLMath::Vector3 &vForce);
		PLPHYSICSNEWTON_API virtual void GetBreakTorque(PLMath::Vector3 &vTorque) const;
		PLPHYSICSNEWTON_API virtual void SetBreakTorque(const PLMath::Vector3 &vTorque);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		JointImpl();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~JointImpl();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Newton::NewtonJoint *m_pNewtonJoint;	/**< Newton physics joint, can be NULL */
		bool				 m_bBreakable;		/**< Is this joint breakable? */
		PLMath::Vector3		 m_vBreakForce;		/**< Break force */
		PLMath::Vector3		 m_vBreakTorque;	/**< Break torque */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton


#endif // __PLPHYSICSNEWTON_JOINTIMPL_H__
