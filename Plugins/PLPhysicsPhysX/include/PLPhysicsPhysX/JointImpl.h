/*********************************************************\
 *  File: JointImpl.h                                    *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
