/*********************************************************\
 *  File: SCPhysicsWorld.h                               *
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


#ifndef __PLPHYSICS_SCENENODES_PHYSICSWORLD_H__
#define __PLPHYSICS_SCENENODES_PHYSICSWORLD_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneContainer.h>
#include "PLPhysics/PLPhysics.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class World;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Physics world scene node container
*
*  @note
*    - If 'CacheDirectory' is set, the implementation tries to cache for instance 'physics meshes'. This
*      can speed up loading times, but may create 'up to date' problems during development when data
*      was changed, but the cache is still using the old one. So, be careful when using this feature.
*    - 'ThreadPriorityClass' and 'ThreadPriority' are only used if the physics API implementation
*      is using an own thread and allows the manipulation of this settings
*/
class SCPhysicsWorld : public PLScene::SceneContainer {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPHYSICS_RTTI_EXPORT, SCPhysicsWorld, "PLPhysics", PLScene::SceneContainer, "Physics world scene node container")
		// Attributes
		pl_attribute(PhysicsAPI,			PLGeneral::String,	"PLPhysicsNewton::World",				ReadWrite,	DirectValue,	"Name of the physics API this world is using",																			"")
		pl_attribute(SimulationActive,		bool,				true,									ReadWrite,	GetSet,			"Is the physics simulation currently active?",																			"")
		pl_attribute(SimulationSpeed,		float,				1.0f,									ReadWrite,	GetSet,			"Physics simulation speed. A speed of <= 0 is NOT allowed! Do NOT make the factor 'too' (for example > 4) extreme.",	"Min='0.0001'")
		pl_attribute(SimulationQuality,		float,				1.0f,									ReadWrite,	GetSet,			"Physics simulation quality. 1 means best realistic behavior, 0 for the fastest possible configuration.",				"Min='0.0' Max='1.0'")
		pl_attribute(FrameRate,				float,				60.0f,									ReadWrite,	GetSet,			"Frame frate the simulation runs on: smaller=more performance, larger=more accurate simulation",						"Min='60.0' Max='1000.0'")
		pl_attribute(CacheDirectory,		PLGeneral::String,	"",										ReadWrite,	DirectValue,	"Physics cache directory, if empty, no caching is used (best to avoid cache problems during development)",				"")

		// [TODO] New RTTI usage
	//	DEFINE_VAR(PL_VAR_ENUM,		m_nThreadPriorityClass,	"",	"",							,							"Idle=0 BelowNormal=1 Normal=2 AboveNormal=3 High=4 Realtime=5 None=6")
	//	DEFINE_VAR(PL_VAR_ENUM,		m_nThreadPriority,		"",		"",						,							"Idle=0 Lowest=1 BelowNormal=2 Normal=3 AboveNormal=4 Highest=5 TimeCritical=6")
	//	pl_attribute(ThreadPriorityClass,	pl_enum_type(),		None,									ReadWrite,	GetSet,			"Physics thread priority class (use realtime priority class ONLY if you REALLY need it, 'None' = do not use a thread)",	"")
	//	pl_attribute(ThreadPriority,		pl_enum_type(),		Normal,									ReadWrite,	GetSet,			"Physics thread priority within the priority class it is in",															"")

		pl_attribute(Gravity,				PLMath::Vector3,	PLMath::Vector3(0.0f, -9.81f, 0.0f),	ReadWrite,	GetSet,			"Gravity vector",																										"")
		pl_attribute(BuoyancyActive,		bool,				false,									ReadWrite,	GetSet,			"Is buoyancy force active?",																							"")
		pl_attribute(BuoyancyPlaneY,		float,				0.0f,									ReadWrite,	GetSet,			"Buoyancy plane y position",																							"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICS_API bool GetSimulationActive() const;
		PLPHYSICS_API void SetSimulationActive(bool bValue);
		PLPHYSICS_API float GetSimulationSpeed() const;
		PLPHYSICS_API void SetSimulationSpeed(float fValue);
		PLPHYSICS_API float GetSimulationQuality() const;
		PLPHYSICS_API void SetSimulationQuality(float fValue);
		PLPHYSICS_API float GetFrameRate() const;
		PLPHYSICS_API void SetFrameRate(float fValue);
		PLPHYSICS_API const PLMath::Vector3 &GetGravity() const;
		PLPHYSICS_API void SetGravity(const PLMath::Vector3 &vValue);
		PLPHYSICS_API bool GetBuoyancyActive() const;
		PLPHYSICS_API void SetBuoyancyActive(bool bValue);
		PLPHYSICS_API float GetBuoyancyPlaneY() const;
		PLPHYSICS_API void SetBuoyancyPlaneY(float fValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLPHYSICS_API SCPhysicsWorld();

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~SCPhysicsWorld();

		/**
		*  @brief
		*    Returns the PL physics world
		*
		*  @return
		*    The PL physics world, a null pointer on error (if that's the case, something went totally wrong :)
		*/
		PLPHYSICS_API World *GetWorld() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void NotifyUpdate();

		/**
		*  @brief
		*    Called when the scene node axis aligned bounding box changed
		*/
		void NotifyAABoundingBox();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerUpdate;
		PLCore::EventHandler<> EventHandlerAABoundingBox;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool			   m_bSimulationActive;		/**< Is the physics simulation currently active? */
		float			   m_fSimulationSpeed;		/**< Physics simulation speed. A speed of <= 0 is NOT allowed! Do NOT make the factor 'too' (for example > 4) extreme. */
		float			   m_fSimulationQuality;	/**< Physics simulation quality. 1 means best realistic behavior, 0 for the fastest possible configuration. */
		float			   m_fFrameRate;			/**< Frame frate the simulation runs on: smaller=more performance, larger=more accurate simulation */
		PLGeneral::uint32  m_nThreadPriorityClass;	/**< Physics thread priority class (use realtime priority class ONLY if you REALLY need it, 'None' = do not use a thread) */
		PLGeneral::uint32  m_nThreadPriority;		/**< Physics thread priority within the priority class it is in */
		PLMath::Vector3    m_vGravity;				/**< Gravity vector */
		bool			   m_bBuoyancyActive;		/**< Is buoyancy force active? */
		float			   m_fBuoyancyPlaneY;		/**< Buoyancy plane y position */
		World			  *m_pWorld;				/**< The PL physics world, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Protected virtual PLScene::SceneNode functions        ]
	//[-------------------------------------------------------]
	protected:
		PLPHYSICS_API virtual void InitFunction();
		PLPHYSICS_API virtual void DeInitFunction();
		PLPHYSICS_API virtual void OnActivate(bool bActivate);


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Loadable functions             ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICS_API virtual bool Load(const PLGeneral::String &sFilename, const PLGeneral::String &sParams = "", const PLGeneral::String &sMethod = "");
		PLPHYSICS_API virtual bool Load(PLGeneral::File &cFile, const PLGeneral::String &sParams = "", const PLGeneral::String &sMethod = "");


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SCENENODES_PHYSICSWORLD_H__
