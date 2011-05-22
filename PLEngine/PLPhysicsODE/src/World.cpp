/*********************************************************\
 *  File: World.cpp                                      *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <limits.h>
#ifdef LINUX
	// Under Linux, we need this for '_vscprintf' :(
	#include <PLGeneral/PLGeneralLinuxWrapper.h>
#endif
#include <PLGeneral/Tools/Timing.h>
#include <PLGeneral/Core/MemoryManager.h>
#include <PLGeneral/Log/Log.h>
#include <PLPhysics/ContactInformation.h>
#include "PLPhysicsODE/BodyImpl.h"
#include "PLPhysicsODE/BodyBox.h"
#include "PLPhysicsODE/BodySphere.h"
#include "PLPhysicsODE/BodyMesh.h"
#include "PLPhysicsODE/JointImpl.h"
#include "PLPhysicsODE/JointBall.h"
#include "PLPhysicsODE/JointSlider.h"
#include "PLPhysicsODE/JointHinge.h"
#include "PLPhysicsODE/JointUniversal.h"
#include "PLPhysicsODE/World.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLPhysicsODE {


//[-------------------------------------------------------]
//[ Static variables                                      ]
//[-------------------------------------------------------]
PLGeneral::uint32 World::m_nODEInstanceCounter = 0;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(World)


//[-------------------------------------------------------]
//[ Private MyHashFunction class implementation           ]
//[-------------------------------------------------------]
PLGeneral::uint32 World::MyHashFunction::Hash(const BodyPair &sKey)
{
	return static_cast<uint32>(((sKey.pBody2 - sKey.pBody1) % UINT_MAX + (sKey.pBody1-sKey.pBody2) % UINT_MAX) % UINT_MAX);
}


//[-------------------------------------------------------]
//[ Private MyCompareFunction class implementation        ]
//[-------------------------------------------------------]
bool World::MyCompareFunction::AreEqual(const BodyPair &sKey1, const BodyPair &sKey2)
{
	return (sKey1.pBody1 == sKey2.pBody1 && sKey1.pBody2 == sKey2.pBody2 ||
		    sKey1.pBody1 == sKey2.pBody2 && sKey1.pBody2 == sKey2.pBody1);
}

bool World::MyCompareFunction::IsGreater(const BodyPair &sKey1, const BodyPair &sKey2)
{
	// Not implemented
	return false;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
World::World() :
	m_vWorldSizeMin(-10000.0f, -10000.0f, -10000.0f),
	m_vWorldSizeMax( 10000.0f,  10000.0f,  10000.0f),
	m_fFrameRate(60.0f),
	m_bSimulationActive(true),
	m_fSimulationSpeed(1.0f),
	m_fSimulationQuality(1.0f),
	m_bBuoyancyActive(false),
	m_fBuoyancyPlaneY(0.0f),
	m_fTimeElapsed(0.0f)
{
	// Initialize group collision active states
	PLGeneral::MemoryManager::Set(m_nGroupCollision, UINT_MAX, sizeof(PLGeneral::uint32)*32);

	// By default, collision between objects within the same group is disabled - except for the first group
	for (uint8 i=1; i<32; i++)
		SetGroupCollision(i, i, false);

	// Set error handler
	if (!m_nODEInstanceCounter) {
		// Set new memory management functions
		dSetAllocHandler  (AllocationFunction);
		dSetReallocHandler(ReallocationFunction);
		dSetFreeHandler   (DeallocationFunction);

		// Set new error functions
		dSetErrorHandler  (ErrorHandler);
		dSetDebugHandler  (ErrorHandler);
		dSetMessageHandler(ErrorHandler);

		// Initialize ODE (obligatory, but we are bravely and do it :)
	// [TODO] Use an actual version of ODE under Linux
	#ifdef WIN32
		dInitODE();
	#endif
	}

	// Create the ODE world
	m_pODEWorld		   = dWorldCreate();
	m_pODESpaceID	   = dHashSpaceCreate(0);
	m_pODEContactGroup = dJointGroupCreate(0);
	PL_LOG(Info, "Created ODE world")

	// Setup world
	dWorldSetGravity(m_pODEWorld, 0.0f, -9.81f, 0.0f);
	dWorldSetAutoDisableFlag(m_pODEWorld, 1);

	// Increase the ODE instance counter
	m_nODEInstanceCounter++;

	// Set simulation quality
	SetSimulationQuality(m_fSimulationQuality);
}

/**
*  @brief
*    Destructor
*/
World::~World()
{
	// Destroy the ODE world
	if (m_pODEWorld) {
		dWorldDestroy(m_pODEWorld);
		m_pODEWorld = nullptr;
	}
	if (m_pODESpaceID) {
		dSpaceDestroy(m_pODESpaceID);
		m_pODESpaceID = nullptr;
	}
	if (m_pODEContactGroup) {
		dJointGroupDestroy(m_pODEContactGroup);
		m_pODEContactGroup = nullptr;
	}
	PL_LOG(Info, "Destroyed ODE world")

	// Decrease the ODE instance counter
	m_nODEInstanceCounter--;

	// De-initialize ODE if there are no further ODE instances
	if (!m_nODEInstanceCounter)
		dCloseODE();
}

/**
*  @brief
*    Returns the ODE physics world
*/
dWorldID World::GetODEWorld() const
{
	return m_pODEWorld;
}

/**
*  @brief
*    Returns the ODE space
*/
dSpaceID World::GetODESpace() const
{
	return m_pODESpaceID;
}

/**
*  @brief
*    Returns the ODE contact group
*/
dJointGroupID World::GetODEContactGroup() const
{
	return m_pODEContactGroup;
}

/**
*  @brief
*    Creates a physics body implementation
*/
PLPhysics::BodyImpl &World::CreateBodyImpl() const
{
	return *(new BodyImpl());
}

/**
*  @brief
*    Creates a physics joint implementation
*/
PLPhysics::JointImpl &World::CreateJointImpl() const
{
	return *(new JointImpl());
}


//[-------------------------------------------------------]
//[ Private virtual functions                             ]
//[-------------------------------------------------------]
/**
*  @brief
*    Is called when two non-space ODE geometries colliding
*/
void World::OnCollision(dGeomID pGeomID1, dGeomID pGeomID2)
{
	// Get the (active) PL physics bodies
	PLPhysics::Body *pBody1 = static_cast<PLPhysics::Body*>(dGeomGetData(pGeomID1));
	if (pBody1 && pBody1->IsActive() && pBody1->IsCollisionActive()) {
		PLPhysics::Body *pBody2 = static_cast<PLPhysics::Body*>(dGeomGetData(pGeomID2));
		if (pBody2 && pBody2->IsActive() && pBody2->IsCollisionActive()) {
			// Are the two bodies in different collision groups? If yes, is collision between this groups allowed?
			PLGeneral::uint8 nCollisionGroup1 = pBody1->GetCollisionGroup();
			PLGeneral::uint8 nCollisionGroup2 = pBody2->GetCollisionGroup();
			if ((static_cast<World&>(pBody1->GetWorld()).m_nGroupCollision[nCollisionGroup1] & (1<<nCollisionGroup2))) {
				// Get body pair flags
				nCollisionGroup1 = pBody1->GetWorld().GetBodyPairFlags(*pBody1, *pBody2);

				// Generate contacts?
				if (!(nCollisionGroup1 & Ignore)) {
					// Exit without doing anything if the two bodies are connected by a joint
					dBodyID pODEBody1 = dGeomGetBody(pGeomID1);
					dBodyID pODEBody2 = dGeomGetBody(pGeomID2);
					if (!pODEBody1 || !pODEBody2 || !dAreConnectedExcluding(pODEBody1, pODEBody2, dJointTypeContact)) {
						// Create the 'ContactInformation'-instance on the runtime-stack
						PLPhysics::ContactInformation cContactInformation(*pBody1, *pBody2);

						// Emit event
						EventContact(cContactInformation);

						// Is the contact marked to be ignored?
						if (!cContactInformation.IsContactIgnored()) {
							// [TODO] Check this
							/*
							static const PLGeneral::uint32 MaxContacts = 4;
							dContact contact[MaxContacts];   // Up to 'MaxContacts' contacts per box-box
							for (PLGeneral::uint32 i=0; i<MaxContacts; i++) {
								contact[i].surface.mode = dContactBounce | dContactSoftCFM;
								contact[i].surface.mu = dInfinity;
								contact[i].surface.mu2 = 0;
								contact[i].surface.bounce = 0.1;
								contact[i].surface.bounce_vel = 0.1;
								contact[i].surface.soft_cfm = 0.01;
							}
							if (PLGeneral::uint32 numc = dCollide (pGeomID1,pGeomID2,MaxContacts,&contact[0].geom,
										sizeof(dContact))) {
								for (PLGeneral::uint32 i=0; i<numc; i++) {
									dJointID c = dJointCreateContact (m_pODEWorld,m_pODEContactGroup,contact+i);
									dJointAttach (c,pODEBody1,pODEBody2);
								}
							}
						*/
							// Colliding two non-space geoms, so generate contact joints between
							// pGeomID1 and pGeomID2
							static const PLGeneral::uint32 MaxContactPoints = 16;
							dContactGeom cp_array[MaxContactPoints];
							PLGeneral::uint32 nNumContacts = dCollide(pGeomID1, pGeomID2, MaxContactPoints, cp_array, sizeof(dContactGeom));

							if (nNumContacts > 1)
								nNumContacts = 1;

							// Add these contact joints to the simulation
							for (PLGeneral::uint32 i=0; i<nNumContacts; i++) {
								dContact tempContact; // = new dContact;
								// tempContact.surface.mode = 0;

								// Lots of ways to set friction properties...
								tempContact.surface.mode = dContactApprox1 | dContactSlip1 | dContactSlip2 | dContactSoftCFM;
								tempContact.surface.slip1 = static_cast<dReal>(0.2);
								tempContact.surface.slip2 = static_cast<dReal>(0.1);
								// tempContact.surface.mode = dContactBounce | dContactSoftCFM;
								tempContact.surface.bounce = static_cast<dReal>(0.1);
								tempContact.surface.bounce_vel = static_cast<dReal>(0.2);
								tempContact.surface.soft_cfm = static_cast<dReal>(0.001);
								// tempContact.surface.mu = dInfinity;
								// tempContact.surface.mu2 = 0;

								// tempContact.surface.mu = 100;
								tempContact.geom = cp_array[i];

								// Add contact joint
								dJointID pJointID = dJointCreateContact(m_pODEWorld, m_pODEContactGroup, &tempContact);
								dJointAttach(pJointID, pODEBody1, pODEBody2);
							}

									/*
							// Colliding two non-space geoms, so generate contact joints between
							// pGeomID1 and pGeomID2
							static const PLGeneral::uint32 MaxContactPoints = 16;
							dContact pContacts[MaxContactPoints], pContact;
							PLGeneral::uint32 nNumContacts = dCollide(pGeomID1, pGeomID2, MaxContactPoints, &pContacts[0].geom, sizeof(dContact));

							// Add these contact joints to the simulation
							for (PLGeneral::uint32 i=0; i<nNumContacts; i++) {
								// Setup contact information
								pContact = pContacts[i];


								pContact.surface.mode = dContactBounce;
								pContact.surface.mu = 250;
								pContact.surface.bounce = 0.3f;
								pContact.surface.bounce_vel = 0.05f;

								// Add contact joint
								dJointID pJointID = dJointCreateContact(m_pODEWorld, m_pODEContactGroup, &pContact);
								dJointAttach(pJointID,
											 dGeomGetBody(pContact.geom.g1),
											 dGeomGetBody(pContact.geom.g2));
							}*/
						}
					}
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private ODE callback functions                        ]
//[-------------------------------------------------------]
// Allocation function
void *World::AllocationFunction(size_t nSize)
{
	return PLGeneral::MemoryManager::Allocator(PLGeneral::MemoryManager::NewArray, nSize);
}

// Reallocation function
void *World::ReallocationFunction(void *pAddress, size_t nOldSize, size_t nNewSize)
{
	// 'nOldSize' is not used (that's NO problem!)
	return PLGeneral::MemoryManager::Reallocator(pAddress, nNewSize);
}

// Deallocation function
void World::DeallocationFunction(void *pAddress, size_t nSize)
{
	// 'nSize' is not used (that's NO problem!)
	if (pAddress)
		PLGeneral::MemoryManager::Deallocator(PLGeneral::MemoryManager::DeleteArray, pAddress);
}

// Error callback function
void World::ErrorHandler(int nErrNum, const char *pszMSG, va_list ap)
{
	// Get the required buffer length
	int nLength = _vscprintf(pszMSG, ap);
	if (nLength > 0) {
		// Allocate memory
		char *pszBuffer = new char[nLength + 1];
		if (pszBuffer) {
			// Print the formatted string
			vsprintf(pszBuffer, pszMSG, ap);

			// Log message
			PL_LOG(Error, PLGeneral::String("ODE error ") + nErrNum + ": " + pszBuffer)

			// Cleanup
			delete [] pszBuffer;
		}
	}
}

// This is called by dSpaceCollide when two objects in space are potentially colliding
void World::NearCallback(void *pData, dGeomID pGeomID1, dGeomID pGeomID2)
{
	// Check whether at least one of the two geometries is a space
	if (dGeomIsSpace(pGeomID1) || dGeomIsSpace(pGeomID2)) {
		// Colliding a space with something
		dSpaceCollide2(pGeomID1, pGeomID2, pData, &NearCallback);

		// Collide all geoms internal to the space(s)
		if (dGeomIsSpace(pGeomID1))
			dSpaceCollide(reinterpret_cast<dSpaceID>(pGeomID1), pData, &NearCallback);
		if (dGeomIsSpace(pGeomID2))
			dSpaceCollide(reinterpret_cast<dSpaceID>(pGeomID2), pData, &NearCallback);
	} else { // Colliding two "normal" (non-space) geometries
		// Call world on collision function
		static_cast<World*>(pData)->OnCollision(pGeomID1, pGeomID2);
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLPhysics::World functions             ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Physics body creation                                 ]
//[-------------------------------------------------------]
PLPhysics::Body *World::CreateBodyBox(const Vector3 &vDimension, bool bStatic)
{
	return new BodyBox(*this, vDimension);
}

PLPhysics::Body *World::CreateBodySphere(float fRadius, bool bStatic)
{
	return new BodySphere(*this, fRadius);
}

PLPhysics::Body *World::CreateBodyEllipsoid(const Vector3 &vRadius, bool bStatic)
{
	// Not implemented
	return nullptr;
}

PLPhysics::Body *World::CreateBodyConvexHull(PLMesh::MeshManager &cMeshManager, const PLGeneral::String &sMesh, const Vector3 &vMeshScale, bool bStatic)
{
	// Not implemented
	return nullptr;
}

PLPhysics::Body *World::CreateBodyMesh(PLMesh::MeshManager &cMeshManager, const PLGeneral::String &sMesh, const Vector3 &vMeshScale, bool bOptimize)
{
	return new BodyMesh(*this, sMesh, vMeshScale, bOptimize);
}

PLPhysics::Body *World::CreateBodyTerrain(PLGeneral::uint32 nWidth, PLGeneral::uint32 nHeight, const float fTerrain[],
										  const Vector3 &vBoxMin, const Vector3 &vBoxMax, const Vector3 &vScale)
{
	// Not implemented
	return nullptr;
}

PLPhysics::Body *World::CreateBodyCylinder(float fRadius, float fHeight, bool bStatic)
{
	// Not implemented
	return nullptr;
}

PLPhysics::Body *World::CreateBodyCone(float fRadius, float fHeight, bool bStatic)
{
	// Not implemented
	return nullptr;
}

PLPhysics::Body *World::CreateBodyCapsule(float fRadius, float fHeight, bool bStatic)
{
	// Not implemented
	return nullptr;
}

PLPhysics::Body *World::CreateBodyChamferCylinder(float fRadius, float fHeight, bool bStatic)
{
	// Not implemented
	return nullptr;
}


//[-------------------------------------------------------]
//[ Physics joint creation                                ]
//[-------------------------------------------------------]
PLPhysics::Joint *World::CreateJointBall(PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody, const Vector3 &vPivotPoint, const Vector3 &vPinDir)
{
	// Check parameters
	if (pParentBody == pChildBody || !pParentBody && !pChildBody)
		return nullptr; // Error!

	// Create the physics joint
	return new JointBall(*this, pParentBody, pChildBody, vPivotPoint, vPinDir);
}

PLPhysics::Joint *World::CreateJointSlider(PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody, const Vector3 &vPivotPoint, const Vector3 &vPinDir)
{
	// Check parameters
	if (pParentBody == pChildBody || !pParentBody && !pChildBody)
		return nullptr; // Error!

	// Create the physics joint
	return new JointSlider(*this, pParentBody, pChildBody, vPivotPoint, vPinDir);
}

PLPhysics::Joint *World::CreateJointHinge(PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody, const Vector3 &vPivotPoint, const Vector3 &vPinDir)
{
	// Check parameters
	if (pParentBody == pChildBody || !pParentBody && !pChildBody)
		return nullptr; // Error!

	// Create the physics joint
	return new JointHinge(*this, pParentBody, pChildBody, vPivotPoint, vPinDir);
}

PLPhysics::Joint *World::CreateJointUniversal(PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody, const Vector3 &vPivotPoint,
											  const Vector3 &vPinDir1, const Vector3 &vPinDir2)
{
	// Check parameters
	if (pParentBody == pChildBody || !pParentBody && !pChildBody)
		return nullptr; // Error!

	// Create the physics joint
	return new JointUniversal(*this, pParentBody, pChildBody, vPivotPoint, vPinDir1, vPinDir2);
}

PLPhysics::Joint *World::CreateJointCorkscrew(PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody, const Vector3 &vPivotPoint, const Vector3 &vPinDir)
{
	// Not implemented
	return nullptr;
}

PLPhysics::Joint *World::CreateJointUpVector(PLPhysics::Body &cParentBody, const Vector3 &vPinDir)
{
	// Not implemented
	return nullptr;
}


//[-------------------------------------------------------]
//[ Physics sensor creation                               ]
//[-------------------------------------------------------]
PLPhysics::Sensor *World::CreateSensorRaycast(const Vector3 &vStart, const Vector3 &vEnd, PLGeneral::uint32 nFlags)
{
	// [TODO] Not implemented
	return nullptr;
}

PLPhysics::Sensor *World::CreateSensorAABoundingBox(const Vector3 &vMin, const Vector3 &vMax, PLGeneral::uint32 nFlags)
{
	// [TODO] Not implemented
	return nullptr;
}


//[-------------------------------------------------------]
//[ Misc                                                  ]
//[-------------------------------------------------------]
void World::GetWorldSize(Vector3 &vMin, Vector3 &vMax) const
{
	vMin = m_vWorldSizeMin;
	vMax = m_vWorldSizeMax;
}

void World::SetWorldSize(const Vector3 &vMin, const Vector3 &vMax)
{
	m_vWorldSizeMin = vMin;
	m_vWorldSizeMax = vMax;
}

bool World::IsSimulationActive() const
{
	return m_bSimulationActive;
}

void World::SetSimulationActive(bool bActive)
{
	m_bSimulationActive = bActive;
}

float World::GetSimulationSpeed() const
{
	return m_fSimulationSpeed;
}

bool World::SetSimulationSpeed(float fSpeed)
{
	if (fSpeed > 0.0f) {
		// Set the new speed
		m_fSimulationSpeed = fSpeed;

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

float World::GetSimulationQuality() const
{
	return m_fSimulationQuality;
}

bool World::SetSimulationQuality(float fQuality)
{
	// Quality range check
	if (fQuality >= 0.0f && fQuality <= 1.0f) {
		m_fSimulationQuality = fQuality;

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

float World::GetFrameRate() const
{
	return m_fFrameRate;
}

bool World::SetFrameRate(float fFrameRate)
{
	// Check parameter
	if (fFrameRate < 60.0f || fFrameRate > 1000.0f)
		return false; // Error!

	// Set the new frame rate
	m_fFrameRate = fFrameRate;

	// Done
	return true;
}

void World::GetGravity(Vector3 &vGravity) const
{
	if (m_pODEWorld)
		dWorldGetGravity(m_pODEWorld, vGravity);
}

void World::SetGravity(const Vector3 &vGravity)
{
	if (m_pODEWorld)
		dWorldSetGravity(m_pODEWorld, vGravity.x, vGravity.y, vGravity.z);
}

bool World::GetGroupCollision(PLGeneral::uint8 nGroup1, PLGeneral::uint8 nGroup2) const
{
	return (nGroup1 <= 31 && nGroup2 <= 31 && (m_nGroupCollision[nGroup1] & (1<<nGroup2)) != 0);
}

void World::SetGroupCollision(PLGeneral::uint8 nGroup1, PLGeneral::uint8 nGroup2, bool bActive)
{
	if (nGroup1 <= 31 && nGroup2 <= 31) {
		if (bActive) {
			m_nGroupCollision[nGroup1] |= 1<<nGroup2;
			m_nGroupCollision[nGroup2] |= 1<<nGroup1;
		} else {
			m_nGroupCollision[nGroup1] &= ~(1<<nGroup2);
			m_nGroupCollision[nGroup2] &= ~(1<<nGroup1);
		}
	}
}

PLGeneral::uint8 World::GetBodyPairFlags(const PLPhysics::Body &cBody1, const PLPhysics::Body &cBody2) const
{
	// Get body pair
	BodyPair sBodyPair;
	sBodyPair.pBody1 = &cBody1;
	sBodyPair.pBody2 = &cBody2;

	// Get and return the flags
	return m_mapBodyPairs.Get(sBodyPair);
}

void World::SetBodyPairFlags(const PLPhysics::Body &cBody1, const PLPhysics::Body &cBody2, PLGeneral::uint8 nFlags)
{
	// Get body pair
	BodyPair sBodyPair;
	sBodyPair.pBody1 = &cBody1;
	sBodyPair.pBody2 = &cBody2;

	// If flags are set to 0, just remove the map entry
	if (nFlags) {
		// Is this body pair already within the map?
		PLGeneral::uint8 &nFlagsRef = m_mapBodyPairs.Get(sBodyPair);
		if (&nFlagsRef != &PLGeneral::HashMap<BodyPair, PLGeneral::uint8, MyHashFunction, MyCompareFunction>::Null)
			nFlagsRef = nFlags; // Jep, just change the value :)
		else {
			// Nope, add it right now!
			m_mapBodyPairs.Add(sBodyPair, nFlags);

			// Add the bodies to each other
			static_cast<BodyImpl&>(cBody1.GetBodyImpl()).m_lstPartnerBodies.Add(&const_cast<PLPhysics::Body&>(static_cast<const PLPhysics::Body&>(cBody2)));
			static_cast<BodyImpl&>(cBody2.GetBodyImpl()).m_lstPartnerBodies.Add(&const_cast<PLPhysics::Body&>(static_cast<const PLPhysics::Body&>(cBody1)));
		}
	} else {
		// Remove from map
		m_mapBodyPairs.Remove(sBodyPair);

		// Remove the bodies from each other
		static_cast<BodyImpl&>(cBody1.GetBodyImpl()).m_lstPartnerBodies.Remove(&const_cast<PLPhysics::Body&>(static_cast<const PLPhysics::Body&>(cBody2)));
		static_cast<BodyImpl&>(cBody2.GetBodyImpl()).m_lstPartnerBodies.Remove(&const_cast<PLPhysics::Body&>(static_cast<const PLPhysics::Body&>(cBody1)));
	}
}

bool World::IsBuoyancyActive() const
{
	return m_bBuoyancyActive;
}

void World::SetBuoyancyActive(bool bActive)
{
	m_bBuoyancyActive = bActive;
}

float World::GetBuoyancyPlaneY() const
{
	return m_fBuoyancyPlaneY;
}

void World::SetBuoyancyPlaneY(float fY)
{
	m_fBuoyancyPlaneY = fY;
}

void World::UpdateSimulation()
{
	// Is the simulation currently active?
	if (m_bSimulationActive) {
		// If the time scale factor is smaller than 1, multiply the step size with this factor for smooth movement
		float fStepSize = 1.0f/m_fFrameRate*m_fSimulationSpeed;
		const float fTimeScaleFactor = PLGeneral::Timing::GetInstance()->GetTimeScaleFactor();
		if (fTimeScaleFactor < 1.0f)
			fStepSize = fStepSize*fTimeScaleFactor;

		// Perform physics simulation
		m_fTimeElapsed += PLGeneral::Timing::GetInstance()->GetTimeDifference();
		while (m_fTimeElapsed > fStepSize) {
			// Collision detection step to create all contact joints
			dSpaceCollide(m_pODESpaceID, this, &NearCallback);

			// Physical world step
			dWorldStep(m_pODEWorld, fStepSize);

			// Remove all contact joints
			dJointGroupEmpty(m_pODEContactGroup);

			// Decrease elapsed time
			m_fTimeElapsed -= fStepSize;
		}

		// Loop through all physics elements to emit the 'Transform'-event of physics bodies
		for (uint32 i=0; i<GetNumOfElements(); i++) {
			PLPhysics::Element *pElement = Get(i);
			if (pElement && pElement->IsBody()) {
				PLPhysics::Body *pBody = static_cast<PLPhysics::Body*>(pElement);
				if (pBody->IsActive() && !pBody->IsFrozen()) {
					// Emit event
					pBody->EventTransform();
				}
			}
		}
	}
}

bool World::IsAlwaysStatic() const
{
	return false;
}


//[-------------------------------------------------------]
//[ Private virtual PLGeneral::ElementManager functions   ]
//[-------------------------------------------------------]
PLPhysics::Element *World::CreateElement(const PLGeneral::String &sName)
{
	// Nothing to do here
	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsODE
