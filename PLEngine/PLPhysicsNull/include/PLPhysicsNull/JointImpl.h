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


#ifndef __PLPHYSICSNULL_JOINTIMPL_H__
#define __PLPHYSICSNULL_JOINTIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include <PLPhysics/JointImpl.h>
#include "PLPhysicsNull/PLPhysicsNull.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsNull {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Null physics joint implementation class
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
		*    Initializes the null physics joint
		*
		*  @param[in] cJoint
		*    PL physics joint this is the implementation from
		*/
		void InitializeNullJoint(PLPhysics::Joint &cJoint);


	//[-------------------------------------------------------]
	//[ Public virtual PLPhysics::JointImpl functions         ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICSNULL_API virtual PLPhysics::Joint *GetJoint() const;
		PLPHYSICSNULL_API virtual bool IsBreakable() const;
		PLPHYSICSNULL_API virtual void SetBreakable(bool bBreakable);
		PLPHYSICSNULL_API virtual void GetBreakForce(PLMath::Vector3 &vForce) const;
		PLPHYSICSNULL_API virtual void SetBreakForce(const PLMath::Vector3 &vForce);
		PLPHYSICSNULL_API virtual void GetBreakTorque(PLMath::Vector3 &vTorque) const;
		PLPHYSICSNULL_API virtual void SetBreakTorque(const PLMath::Vector3 &vTorque);


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
		PLPhysics::Joint *m_pJoint;			/**< PL physics joint this is the implementation from, can be NULL */
		bool			  m_bBreakable;		/**< Is this joint breakable? */
		PLMath::Vector3	  m_vBreakForce;	/**< Break force */
		PLMath::Vector3	  m_vBreakTorque;	/**< Break torque */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNull


#endif // __PLPHYSICSNULL_JOINTIMPL_H__
