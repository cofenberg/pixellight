/*********************************************************\
 *  File: World.h                                        *
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


#ifndef __PLPHYSICSODE_WORLD_H__
#define __PLPHYSICSODE_WORLD_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLPhysics/World.h>
#include "PLPhysicsODE/PLPhysicsODE.h"


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
namespace PLPhysicsODE {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    ODE physics world base class
*/
class World : public PLPhysics::World {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPHYSICSODE_RTTI_EXPORT, World, "PLPhysicsODE", PLPhysics::World, "ODE physics world base class")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLPHYSICSODE_API World();

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICSODE_API virtual ~World();

		/**
		*  @brief
		*    Returns the ODE physics world
		*
		*  @return
		*    The ODE physics world, a null pointer on error (of that's the case, something went totally wrong :)
		*/
		PLPHYSICSODE_API dWorldID GetODEWorld() const;

		/**
		*  @brief
		*    Returns the ODE space
		*
		*  @return
		*    The ODE space, a null pointer on error (of that's the case, something went totally wrong :)
		*/
		PLPHYSICSODE_API dSpaceID GetODESpace() const;

		/**
		*  @brief
		*    Returns the ODE contact group
		*
		*  @return
		*    The ODE contact group, a null pointer on error (of that's the case, something went totally wrong :)
		*/
		PLPHYSICSODE_API dJointGroupID GetODEContactGroup() const;

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
	//[ Private virtual World functions                       ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Is called when two non-space ODE geometries colliding
		*
		*  @param[in] pGeomID1
		*    Colliding geometry 1
		*  @param[in] pGeomID2
		*    Colliding geometry 2
		*
		*  @note
		*    - In this functions you have to create the contact points
		*/
		virtual void OnCollision(dGeomID pGeomID1, dGeomID pGeomID2);


	//[-------------------------------------------------------]
	//[ Private ODE callback functions                        ]
	//[-------------------------------------------------------]
	private:
		static void *AllocationFunction(size_t nSize);
		static void *ReallocationFunction(void *pAddress, size_t nOldSize, size_t nNewSize);
		static void DeallocationFunction(void *pAddress, size_t nSize);
		static void ErrorHandler(int nErrNum, const char *pszMSG, va_list ap);
		static void NearCallback(void *pData, dGeomID pGeomID1, dGeomID pGeomID2);


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal body pair
		*/
		struct BodyPair {
			const PLPhysics::Body *pBody1;	/**< The first body (always valid!) */
			const PLPhysics::Body *pBody2;	/**< The second body (always valid!) */
		};


	//[-------------------------------------------------------]
	//[ Private classes                                       ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal hash function
		*/
		class MyHashFunction {
			public:
				static PLCore::uint32 Hash(const BodyPair &sKey);
		};

		/**
		*  @brief
		*    Internal compare function
		*/
		class MyCompareFunction {
			public:
				static bool AreEqual(const BodyPair &sKey1, const BodyPair &sKey2);
				static bool IsGreater(const BodyPair &sKey1, const BodyPair &sKey2);
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMath::Vector3 m_vWorldSizeMin;			/**< ODE no not need this */
		PLMath::Vector3 m_vWorldSizeMax;			/**< ODE no not need this */
		float		    m_fFrameRate;
		bool		    m_bSimulationActive;
		float		    m_fSimulationSpeed;
		float		    m_fSimulationQuality;
		PLCore::uint32  m_nGroupCollision[32];	/**< Group collision active states */
		bool		    m_bBuoyancyActive;		// [TODO] Implement buoyancy within the ODE backend
		float		    m_fBuoyancyPlaneY;		// [TODO] Implement buoyancy within the ODE backend

		static PLCore::uint32 m_nODEInstanceCounter;	/**< ODE instance counter */
		dWorldID				 m_pODEWorld;			/**< ODE physics world, can be a null pointer */
		dSpaceID				 m_pODESpaceID;			/**< ODE world space, can be a null pointer */
		dJointGroupID			 m_pODEContactGroup;	/**< ODE contact joint group, can be a null pointer */
		float					 m_fTimeElapsed;		/**< Elapsed time since last update */

		// Body pair flags
		PLCore::HashMap<BodyPair, PLCore::uint8, MyHashFunction, MyCompareFunction> m_mapBodyPairs;


	//[-------------------------------------------------------]
	//[ Public virtual PLPhysics::World functions             ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ Physics body creation                                 ]
		//[-------------------------------------------------------]
		PLPHYSICSODE_API virtual PLPhysics::Body *CreateBodyBox(const PLMath::Vector3 &vDimension, bool bStatic = false) override;
		PLPHYSICSODE_API virtual PLPhysics::Body *CreateBodySphere(float fRadius, bool bStatic = false) override;
		PLPHYSICSODE_API virtual PLPhysics::Body *CreateBodyEllipsoid(const PLMath::Vector3 &vRadius, bool bStatic = false) override;
		PLPHYSICSODE_API virtual PLPhysics::Body *CreateBodyConvexHull(PLMesh::MeshManager &cMeshManager, const PLCore::String &sMesh, const PLMath::Vector3 &vMeshScale = PLMath::Vector3::One, bool bStatic = false) override;
		PLPHYSICSODE_API virtual PLPhysics::Body *CreateBodyMesh(PLMesh::MeshManager &cMeshManager, const PLCore::String &sMesh, const PLMath::Vector3 &vMeshScale = PLMath::Vector3::One, bool bOptimize = false) override;
		PLPHYSICSODE_API virtual PLPhysics::Body *CreateBodyTerrain(PLCore::uint32 nWidth, PLCore::uint32 nHeight, const float fTerrain[], const PLMath::Vector3 &vBoxMin, const PLMath::Vector3 &vBoxMax, const PLMath::Vector3 &vScale) override;
		PLPHYSICSODE_API virtual PLPhysics::Body *CreateBodyCylinder(float fRadius, float fHeight, bool bStatic = false) override;
		PLPHYSICSODE_API virtual PLPhysics::Body *CreateBodyCone(float fRadius, float fHeight, bool bStatic = false) override;
		PLPHYSICSODE_API virtual PLPhysics::Body *CreateBodyCapsule(float fRadius, float fHeight, bool bStatic = false) override;
		PLPHYSICSODE_API virtual PLPhysics::Body *CreateBodyChamferCylinder(float fRadius, float fHeight, bool bStatic = false) override;

		//[-------------------------------------------------------]
		//[ Physics joint creation                                ]
		//[-------------------------------------------------------]
		PLPHYSICSODE_API virtual PLPhysics::Joint *CreateJointBall(PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody, const PLMath::Vector3 &vPivotPoint, const PLMath::Vector3 &vPinDir) override;
		PLPHYSICSODE_API virtual PLPhysics::Joint *CreateJointSlider(PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody, const PLMath::Vector3 &vPivotPoint, const PLMath::Vector3 &vPinDir) override;
		PLPHYSICSODE_API virtual PLPhysics::Joint *CreateJointHinge(PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody, const PLMath::Vector3 &vPivotPoint, const PLMath::Vector3 &vPinDir) override;
		PLPHYSICSODE_API virtual PLPhysics::Joint *CreateJointUniversal(PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody, const PLMath::Vector3 &vPivotPoint, const PLMath::Vector3 &vPinDir1, const PLMath::Vector3 &vPinDir2) override;
		PLPHYSICSODE_API virtual PLPhysics::Joint *CreateJointCorkscrew(PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody, const PLMath::Vector3 &vPivotPoint, const PLMath::Vector3 &vPinDir) override;
		PLPHYSICSODE_API virtual PLPhysics::Joint *CreateJointUpVector(PLPhysics::Body &cParentBody, const PLMath::Vector3 &vPinDir) override;

		//[-------------------------------------------------------]
		//[ Physics sensor creation                               ]
		//[-------------------------------------------------------]
		PLPHYSICSODE_API virtual PLPhysics::Sensor *CreateSensorRaycast(const PLMath::Vector3 &vStart = PLMath::Vector3::Zero, const PLMath::Vector3 &vEnd = PLMath::Vector3::Zero, PLCore::uint32 nFlags = 0) override;
		PLPHYSICSODE_API virtual PLPhysics::Sensor *CreateSensorAABoundingBox(const PLMath::Vector3 &vMin = PLMath::Vector3::Zero, const PLMath::Vector3 &vMax = PLMath::Vector3::Zero, PLCore::uint32 nFlags = 0) override;

		//[-------------------------------------------------------]
		//[ Misc                                                  ]
		//[-------------------------------------------------------]
		PLPHYSICSODE_API virtual void GetWorldSize(PLMath::Vector3 &vMin, PLMath::Vector3 &vMax) const override;
		PLPHYSICSODE_API virtual void SetWorldSize(const PLMath::Vector3 &vMin = PLMath::Vector3(-10000.0f, -10000.0f, -10000.0f), const PLMath::Vector3 &vMax = PLMath::Vector3( 10000.0f,  10000.0f,  10000.0f)) override;
		PLPHYSICSODE_API virtual bool IsSimulationActive() const override;
		PLPHYSICSODE_API virtual void SetSimulationActive(bool bActive = true) override;
		PLPHYSICSODE_API virtual float GetSimulationSpeed() const override;
		PLPHYSICSODE_API virtual bool SetSimulationSpeed(float fSpeed = 1.0f) override;
		PLPHYSICSODE_API virtual float GetSimulationQuality() const override;
		PLPHYSICSODE_API virtual bool SetSimulationQuality(float fQuality = 1.0f) override;
		PLPHYSICSODE_API virtual float GetFrameRate() const override;
		PLPHYSICSODE_API virtual bool SetFrameRate(float fFrameRate = 60.0f) override;
		PLPHYSICSODE_API virtual void GetGravity(PLMath::Vector3 &vGravity) const override;
		PLPHYSICSODE_API virtual void SetGravity(const PLMath::Vector3 &vGravity = PLMath::Vector3(0.0f, -9.81f, 0.0f)) override;
		PLPHYSICSODE_API virtual bool GetGroupCollision(PLCore::uint8 nGroup1, PLCore::uint8 nGroup2) const override;
		PLPHYSICSODE_API virtual void SetGroupCollision(PLCore::uint8 nGroup1, PLCore::uint8 nGroup2, bool bActive = true) override;
		PLPHYSICSODE_API virtual PLCore::uint8 GetBodyPairFlags(const PLPhysics::Body &cBody1, const PLPhysics::Body &cBody2) const override;
		PLPHYSICSODE_API virtual void SetBodyPairFlags(const PLPhysics::Body &cBody1, const PLPhysics::Body &cBody2, PLCore::uint8 nFlags = 0) override;
		PLPHYSICSODE_API virtual bool IsBuoyancyActive() const override;
		PLPHYSICSODE_API virtual void SetBuoyancyActive(bool bActive = false) override;
		PLPHYSICSODE_API virtual float GetBuoyancyPlaneY() const override;
		PLPHYSICSODE_API virtual void SetBuoyancyPlaneY(float fY = 0.0f) override;
		PLPHYSICSODE_API virtual void UpdateSimulation() override;
		PLPHYSICSODE_API virtual bool IsAlwaysStatic() const override;


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ElementManager functions      ]
	//[-------------------------------------------------------]
	private:
		virtual PLPhysics::Element *CreateElement(const PLCore::String &sName) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsODE


#endif // __PLPHYSICSODE_WORLD_H__
