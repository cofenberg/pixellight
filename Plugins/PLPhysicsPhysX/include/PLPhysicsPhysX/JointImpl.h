/*********************************************************\
 *  File: JointImpl.h                                    *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLPHYSICSPHYSX_JOINTIMPL_H__
#define __PLPHYSICSPHYSX_JOINTIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include <PLPhysics/JointImpl.h>
#include "PLPhysicsPhysX/PLPhysicsPhysX.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsPhysX {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PhysX physics joint implementation class
*
*  @note
*    - PhysX has for break force and torque just a simple floating point value instead
*      of a vector. So, this implementation is using the greatest component of the given
*      force/torque vector.
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
		*    Returns the PhysX physics joint
		*
		*  @return
		*    The PhysX physics joint, a null pointer on error (of that's the case, something went totally wrong :)
		*
		*  @note
		*    - Do NOT change the user data of the PhysX physics joínt! (using dJointSetData())
		*      This data MUST hold a pointer to the PL physics joint.
		*/
		PLPHYSICSPHYSX_API NxJoint *GetPhysXJoint() const;

		/**
		*  @brief
		*    Initializes the PhysX physics joint
		*
		*  @param[in] cJoint
		*    PL physics joint this is the implementation from
		*  @param[in] cPhysXJoint
		*    PhysX physics joint
		*/
		void InitializePhysXJoint(PLPhysics::Joint &cJoint, NxJoint &cPhysXJoint);


	//[-------------------------------------------------------]
	//[ Public virtual PLPhysics::JointImpl functions         ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICSPHYSX_API virtual PLPhysics::Joint *GetJoint() const override;
		PLPHYSICSPHYSX_API virtual bool IsBreakable() const override;
		PLPHYSICSPHYSX_API virtual void SetBreakable(bool bBreakable) override;
		PLPHYSICSPHYSX_API virtual void GetBreakForce(PLMath::Vector3 &vForce) const override;
		PLPHYSICSPHYSX_API virtual void SetBreakForce(const PLMath::Vector3 &vForce) override;
		PLPHYSICSPHYSX_API virtual void GetBreakTorque(PLMath::Vector3 &vTorque) const override;
		PLPHYSICSPHYSX_API virtual void SetBreakTorque(const PLMath::Vector3 &vTorque) override;


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
		NxJoint			*m_pPhysXJoint;		/**< PhysX physics joint, can be a null pointer */
		bool			 m_bBreakable;		/**< Is this joint breakable? */
		PLMath::Vector3	 m_vBreakForce;		/**< Break force */
		PLMath::Vector3	 m_vBreakTorque;	/**< Break torque */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsPhysX


#endif // __PLPHYSICSPHYSX_JOINTIMPL_H__
