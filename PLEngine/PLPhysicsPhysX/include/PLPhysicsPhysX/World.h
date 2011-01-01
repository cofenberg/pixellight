/*********************************************************\
 *  File: World.h                                        *
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


#ifndef __PLPHYSICSPHYSX_WORLD_H__
#define __PLPHYSICSPHYSX_WORLD_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLPhysics/World.h>
#include "PLPhysicsPhysX/PLPhysicsPhysX.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLPhysics {
	class BodyImpl;
	class JointImpl;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsPhysX {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PhysX physics world base class
*/
class World : public PLPhysics::World, public NxUserContactModify {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class BodyImpl;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPHYSICSPHYSX_RTTI_EXPORT, World, "PLPhysicsPhysX", PLPhysics::World, "PhysX physics world base class")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLPHYSICSPHYSX_API World();

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICSPHYSX_API virtual ~World();

		/**
		*  @brief
		*    Returns the PhysX physics SDK
		*
		*  @return
		*    The PhysX physics SDK, NULL on error (if that's the case, something went totally wrong :)
		*/
		PLPHYSICSPHYSX_API NxPhysicsSDK *GetPhysXPhysicsSDK() const;

		/**
		*  @brief
		*    Returns the PhysX physics scene
		*
		*  @return
		*    The PhysX physics scene, NULL on error (if that's the case, something went totally wrong :)
		*/
		PLPHYSICSPHYSX_API NxScene *GetPhysXScene() const;

		/**
		*  @brief
		*    Creates a physics body implementation
		*
		*  @return
		*    The created physics body implementation
		*/
		PLPhysics::BodyImpl &CreateBodyImpl() const;

		/**
		*  @brief
		*    Creates a physics joint implementation
		*
		*  @return
		*    The created physics joint implementation
		*/
		PLPhysics::JointImpl &CreateJointImpl() const;


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		static NxPhysicsSDK		 *m_pPhysXPhysicsSDK;		/**< PhysX physics SDK instance, can be NULL */
		static PLGeneral::uint32  m_nPhysXInstanceCounter;	/**< PhysX instance counter */


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMath::Vector3 m_vWorldSizeMin;		/**< PhysX no not need this */
		PLMath::Vector3 m_vWorldSizeMax;		/**< PhysX no not need this */
		float			m_fFrameRate;
		bool			m_bSimulationActive;
		float			m_fSimulationSpeed;
		float			m_fSimulationQuality;
		bool			m_bBuoyancyActive;		// [TODO] Implement buoyancy within the PhysX backend
		float			m_fBuoyancyPlaneY;		// [TODO] Implement buoyancy within the PhysX backend

		PLGeneral::Pool<PLPhysics::Body*> m_lstChangedByUser;
		NxScene *m_pPhysXScene;	/**< PhysX physics scene, can be NULL */


	//[-------------------------------------------------------]
	//[ Public virtual PLPhysics::World functions             ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ Physics body creation                                 ]
		//[-------------------------------------------------------]
		PLPHYSICSPHYSX_API virtual PLPhysics::Body *CreateBodyBox(const PLMath::Vector3 &vDimension, bool bStatic = false);
		PLPHYSICSPHYSX_API virtual PLPhysics::Body *CreateBodySphere(float fRadius, bool bStatic = false);
		PLPHYSICSPHYSX_API virtual PLPhysics::Body *CreateBodyEllipsoid(const PLMath::Vector3 &vRadius, bool bStatic = false);
		PLPHYSICSPHYSX_API virtual PLPhysics::Body *CreateBodyConvexHull(PLMesh::MeshManager &cMeshManager, const PLGeneral::String &sMesh, const PLMath::Vector3 &vMeshScale = PLMath::Vector3::One, bool bStatic = false);
		PLPHYSICSPHYSX_API virtual PLPhysics::Body *CreateBodyMesh(PLMesh::MeshManager &cMeshManager, const PLGeneral::String &sMesh, const PLMath::Vector3 &vMeshScale = PLMath::Vector3::One, bool bOptimize = false);
		PLPHYSICSPHYSX_API virtual PLPhysics::Body *CreateBodyTerrain(PLGeneral::uint32 nWidth, PLGeneral::uint32 nHeight, const float fTerrain[],
																		const PLMath::Vector3 &vBoxMin, const PLMath::Vector3 &vBoxMax, const PLMath::Vector3 &vScale);
		PLPHYSICSPHYSX_API virtual PLPhysics::Body *CreateBodyCylinder(float fRadius, float fHeight, bool bStatic = false);
		PLPHYSICSPHYSX_API virtual PLPhysics::Body *CreateBodyCone(float fRadius, float fHeight, bool bStatic = false);
		PLPHYSICSPHYSX_API virtual PLPhysics::Body *CreateBodyCapsule(float fRadius, float fHeight, bool bStatic = false);
		PLPHYSICSPHYSX_API virtual PLPhysics::Body *CreateBodyChamferCylinder(float fRadius, float fHeight, bool bStatic = false);

		//[-------------------------------------------------------]
		//[ Physics joint creation                                ]
		//[-------------------------------------------------------]
		PLPHYSICSPHYSX_API virtual PLPhysics::Joint *CreateJointBall(PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody, const PLMath::Vector3 &vPivotPoint,
																	   const PLMath::Vector3 &vPinDir);
		PLPHYSICSPHYSX_API virtual PLPhysics::Joint *CreateJointSlider(PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody, const PLMath::Vector3 &vPivotPoint,
																	     const PLMath::Vector3 &vPinDir);
		PLPHYSICSPHYSX_API virtual PLPhysics::Joint *CreateJointHinge(PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody, const PLMath::Vector3 &vPivotPoint,
																	    const PLMath::Vector3 &vPinDir);
		PLPHYSICSPHYSX_API virtual PLPhysics::Joint *CreateJointUniversal(PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody, const PLMath::Vector3 &vPivotPoint,
																    		const PLMath::Vector3 &vPinDir1, const PLMath::Vector3 &vPinDir2);
		PLPHYSICSPHYSX_API virtual PLPhysics::Joint *CreateJointCorkscrew(PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody, const PLMath::Vector3 &vPivotPoint,
																			const PLMath::Vector3 &vPinDir);
		PLPHYSICSPHYSX_API virtual PLPhysics::Joint *CreateJointUpVector(PLPhysics::Body &cParentBody, const PLMath::Vector3 &vPinDir);

		//[-------------------------------------------------------]
		//[ Physics sensor creation                               ]
		//[-------------------------------------------------------]
		PLPHYSICSPHYSX_API virtual PLPhysics::Sensor *CreateSensorRaycast(const PLMath::Vector3 &vStart = PLMath::Vector3::Zero, const PLMath::Vector3 &vEnd = PLMath::Vector3::Zero, PLGeneral::uint32 nFlags = 0);
		PLPHYSICSPHYSX_API virtual PLPhysics::Sensor *CreateSensorAABoundingBox(const PLMath::Vector3 &vMin = PLMath::Vector3::Zero, const PLMath::Vector3 &vMax = PLMath::Vector3::Zero, PLGeneral::uint32 nFlags = 0);

		//[-------------------------------------------------------]
		//[ Misc                                                  ]
		//[-------------------------------------------------------]
		PLPHYSICSPHYSX_API virtual void GetWorldSize(PLMath::Vector3 &vMin, PLMath::Vector3 &vMax) const;
		PLPHYSICSPHYSX_API virtual void SetWorldSize(const PLMath::Vector3 &vMin = PLMath::Vector3(-10000.0f, -10000.0f, -10000.0f),
													   const PLMath::Vector3 &vMax = PLMath::Vector3( 10000.0f,  10000.0f,  10000.0f));
		PLPHYSICSPHYSX_API virtual bool IsSimulationActive() const;
		PLPHYSICSPHYSX_API virtual void SetSimulationActive(bool bActive = true);
		PLPHYSICSPHYSX_API virtual float GetSimulationSpeed() const;
		PLPHYSICSPHYSX_API virtual bool SetSimulationSpeed(float fSpeed = 1.0f);
		PLPHYSICSPHYSX_API virtual float GetSimulationQuality() const;
		PLPHYSICSPHYSX_API virtual bool SetSimulationQuality(float fQuality = 1.0f);
		PLPHYSICSPHYSX_API virtual float GetFrameRate() const;
		PLPHYSICSPHYSX_API virtual bool SetFrameRate(float fFrameRate = 60.0f);
		PLPHYSICSPHYSX_API virtual void GetGravity(PLMath::Vector3 &vGravity) const;
		PLPHYSICSPHYSX_API virtual void SetGravity(const PLMath::Vector3 &vGravity = PLMath::Vector3(0.0f, -9.81f, 0.0f));
		PLPHYSICSPHYSX_API virtual bool GetGroupCollision(PLGeneral::uint8 nGroup1, PLGeneral::uint8 nGroup2) const;
		PLPHYSICSPHYSX_API virtual void SetGroupCollision(PLGeneral::uint8 nGroup1, PLGeneral::uint8 nGroup2, bool bActive = true);
		PLPHYSICSPHYSX_API virtual PLGeneral::uint8 GetBodyPairFlags(const PLPhysics::Body &cBody1, const PLPhysics::Body &cBody2) const;
		PLPHYSICSPHYSX_API virtual void SetBodyPairFlags(const PLPhysics::Body &cBody1, const PLPhysics::Body &cBody2, PLGeneral::uint8 nFlags = 0);
		PLPHYSICSPHYSX_API virtual bool IsBuoyancyActive() const;
		PLPHYSICSPHYSX_API virtual void SetBuoyancyActive(bool bActive = false);
		PLPHYSICSPHYSX_API virtual float GetBuoyancyPlaneY() const;
		PLPHYSICSPHYSX_API virtual void SetBuoyancyPlaneY(float fY = 0.0f);
		PLPHYSICSPHYSX_API virtual void UpdateSimulation();
		PLPHYSICSPHYSX_API virtual bool IsAlwaysStatic() const;


	//[-------------------------------------------------------]
	//[ Private virtual PLGeneral::ElementManager functions   ]
	//[-------------------------------------------------------]
	private:
		virtual PLPhysics::Element *CreateElement(const PLGeneral::String &sName);


	//[-------------------------------------------------------]
	//[ Public virtual NxUserContactModify functions          ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICSPHYSX_API bool onContactConstraint(NxU32 &nChangeFlags, const NxShape *pShape0,
													const NxShape *pShape1, const NxU32 nFeatureIndex0,
													const NxU32 nFeatureIndex1, NxContactCallbackData &sData);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsPhysX


#endif // __PLPHYSICSPHYSX_WORLD_H__
