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


#ifndef __PLPHYSICS_JOINT_H__
#define __PLPHYSICS_JOINT_H__
#pragma once


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
#include "PLPhysics/Element.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class Vector3;
};
namespace PLPhysics {
	class Body;
	class JointImpl;
	class ElementHandler;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract PL physics joint (also called 'constraint') base class
*
*  @remarks
*    A joint will constrain the motion of the two bodies it's attached to. A joint can be
*    attached to two joints and one of this to bodies may be NULL which means that it's
*    attached to 'the world'. (static)
*/
class Joint : public Element {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~Joint();

		/**
		*  @brief
		*    Returns a reference to the physics API specific joint implementation
		*
		*  @return
		*    Reference to the physics API specific joint implementation
		*/
		PLPHYSICS_API JointImpl &GetJointImpl() const;

		/**
		*  @brief
		*    Returns a pointer to the parent rigid body
		*
		*  @return
		*    Pointer to the parent rigid body, can be NULL
		*/
		PLPHYSICS_API Body *GetParentBody() const;

		/**
		*  @brief
		*    Returns a pointer to the attached rigid body
		*
		*  @return
		*    Pointer to the attached rigid body, can be NULL
		*/
		PLPHYSICS_API Body *GetChildBody() const;


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Gets the current pivot point of the joint
		*
		*  @param[out] vPosition
		*    Will receive the current pivot point of the joint
		*/
		PLPHYSICS_API virtual void GetCurrentPivotPoint(PLMath::Vector3 &vPosition) const;

		/**
		*  @brief
		*    Returns whether the joint is breakable or not
		*
		*  @return
		*    'true' if the joint is breakable, else 'false'
		*/
		PLPHYSICS_API virtual bool IsBreakable() const;

		/**
		*  @brief
		*    Sets whether the joint is breakable or not
		*
		*  @param[in] bBreakable
		*    'true' if the joint is breakable, else 'false' (default setting)
		*
		*  @see
		*    - IsBreakable()
		*/
		PLPHYSICS_API virtual void SetBreakable(bool bBreakable);

		/**
		*  @brief
		*    Returns the break force
		*
		*  @param[out] vForce
		*    Will receive the break force
		*
		*  @see
		*    - IsBreakable()
		*/
		PLPHYSICS_API virtual void GetBreakForce(PLMath::Vector3 &vForce) const;

		/**
		*  @brief
		*    Sets the break force
		*
		*  @param[in] vForce
		*    The break force
		*
		*  @see
		*    - IsBreakable()
		*/
		PLPHYSICS_API virtual void SetBreakForce(const PLMath::Vector3 &vForce);

		/**
		*  @brief
		*    Returns the break torque
		*
		*  @param[out] vTorque
		*    Will receive the break torque
		*
		*  @see
		*    - IsBreakable()
		*/
		PLPHYSICS_API virtual void GetBreakTorque(PLMath::Vector3 &vTorque) const;

		/**
		*  @brief
		*    Sets the break torque
		*
		*  @param[in] vTorque
		*    The break torque
		*
		*  @see
		*    - IsBreakable()
		*/
		PLPHYSICS_API virtual void SetBreakTorque(const PLMath::Vector3 &vTorque);


	//[-------------------------------------------------------]
	//[ Public virtual Element functions                      ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICS_API virtual bool IsBody() const;
		PLPHYSICS_API virtual bool IsJoint() const;
		PLPHYSICS_API virtual bool IsSensor() const;


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
		*  @param[in] pParentBody
		*    Pointer to the parent rigid body, can be NULL
		*  @param[in] pChildBody
		*    Pointer to the attached rigid body, can be NULL
		*/
		PLPHYSICS_API Joint(World &cWorld, JointImpl &cJointImpl, Body *pParentBody, Body *pChildBody);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		JointImpl	   *m_pJointImpl;			/**< Pointer to the physics API specific joint implementation (always valid!) */
		ElementHandler *m_pParentBodyHandler;	/**< Parent body handler */
		ElementHandler *m_pChildBodyHandler;	/**< Child body handler */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_JOINT_H__
