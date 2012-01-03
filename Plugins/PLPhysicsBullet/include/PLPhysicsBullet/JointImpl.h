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


#ifndef __PLPHYSICSBULLET_JOINTIMPL_H__
#define __PLPHYSICSBULLET_JOINTIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include <PLPhysics/JointImpl.h>
#include "PLPhysicsBullet/PLPhysicsBullet.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsBullet {


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
		*    Returns the Bullet physics constraint
		*
		*  @return
		*    The Bullet physics constraint, a null pointer when no constraint is used (e.g. for the JointUpVector, there is no constraint needed)
		*/
		PLPHYSICSBULLET_API btTypedConstraint *GetBulletConstraint() const;

		/**
		*  @brief
		*    Initializes the Bullet physics constraint
		*
		*  @param[in] cJoint
		*    PL physics joint this is the implementation from
		*  @param[in] pBulletConstraint
		*    Bullet physics Constraint
		*/
		void InitializeBulletConstraint(PLPhysics::Joint &cJoint, btTypedConstraint *pBulletConstraint);


	//[-------------------------------------------------------]
	//[ Public virtual PLPhysics::JointImpl functions         ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICSBULLET_API virtual PLPhysics::Joint *GetJoint() const override;
		PLPHYSICSBULLET_API virtual bool IsBreakable() const override;
		PLPHYSICSBULLET_API virtual void SetBreakable(bool bBreakable) override;
		PLPHYSICSBULLET_API virtual void GetBreakForce(PLMath::Vector3 &vForce) const override;
		PLPHYSICSBULLET_API virtual void SetBreakForce(const PLMath::Vector3 &vForce) override;
		PLPHYSICSBULLET_API virtual void GetBreakTorque(PLMath::Vector3 &vTorque) const override;
		PLPHYSICSBULLET_API virtual void SetBreakTorque(const PLMath::Vector3 &vTorque) override;


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
		btTypedConstraint	*m_pBulletConstraint;	/**< Bullet physics Constraint, can be a null pointer */
		bool				 m_bBreakable;		/**< Is this joint breakable? */
		PLMath::Vector3		 m_vBreakForce;		/**< Break force */
		PLMath::Vector3		 m_vBreakTorque;	/**< Break torque */
		PLPhysics::Joint	*m_pJoint;			/**< The associated PLPhysics::Joint instance*/


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsBullet


#endif // __PLPHYSICSBULLET_JOINTIMPL_H__
