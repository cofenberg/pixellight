/*********************************************************\
 *  File: JointImpl.h                                    *
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


#ifndef __PLPHYSICSODE_JOINTIMPL_H__
#define __PLPHYSICSODE_JOINTIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLPhysics/JointImpl.h>
#include "PLPhysicsODE/PLPhysicsODE.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsODE {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    ODE physics joint implementation class
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
		*    Returns the ODE physics joint
		*
		*  @return
		*    The ODE physics joint, a null pointer on error (of that's the case, something went totally wrong :)
		*
		*  @note
		*    - Do NOT change the user data of the ODE physics joínt! (using dJointSetData())
		*      This data MUST hold a pointer to the PL physics joint.
		*/
		PLPHYSICSODE_API dJointID GetODEJoint() const;

		/**
		*  @brief
		*    Initializes the ODE physics joint
		*
		*  @param[in] cJoint
		*    PL physics joint this is the implementation from
		*  @param[in] pODEJoint
		*    ODE physics joint
		*/
		void InitializeODEJoint(PLPhysics::Joint &cJoint, dJointID pODEJoint);


	//[-------------------------------------------------------]
	//[ Public virtual PLPhysics::JointImpl functions         ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICSODE_API virtual PLPhysics::Joint *GetJoint() const;
		PLPHYSICSODE_API virtual bool IsBreakable() const;
		PLPHYSICSODE_API virtual void SetBreakable(bool bBreakable);
		PLPHYSICSODE_API virtual void GetBreakForce(PLMath::Vector3 &vForce) const;
		PLPHYSICSODE_API virtual void SetBreakForce(const PLMath::Vector3 &vForce);
		PLPHYSICSODE_API virtual void GetBreakTorque(PLMath::Vector3 &vTorque) const;
		PLPHYSICSODE_API virtual void SetBreakTorque(const PLMath::Vector3 &vTorque);


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
		dJointID m_pODEJoint;	/**< ODE physics joint */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsODE


#endif // __PLPHYSICSODE_JOINTIMPL_H__
