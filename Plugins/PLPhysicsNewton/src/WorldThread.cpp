/*********************************************************\
 *  File: WorldThread.cpp                                *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLGeneral/System/System.h>
#include <PLGeneral/System/MutexGuard.h>
#include "PLPhysicsNewton/World.h"
#include "PLPhysicsNewton/WorldThread.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLPhysicsNewton {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
WorldThread::WorldThread(World &cWorld) : WorldUpdate(cWorld),
	m_pMutex(new Mutex()),
	m_bShutDown(false),
	m_fTimeScaleFactor(Timing::GetInstance()->GetTimeScaleFactor()),
	m_fMaxTimeDifference(Timing::GetInstance()->GetMaxTimeDifference()),
	m_fSimulationSpeed(cWorld.m_fSimulationSpeed),
	m_fFrameRate(cWorld.m_fFrameRate)
{
	// Setup priority
	SetPriorityClass(static_cast<Thread::EPriorityClass>(cWorld.m_nThreadPriorityClass));
	SetPriority(static_cast<Thread::EPriority>(cWorld.m_nThreadPriority));

	// Give the thread a neat name
	SetName("PixelLightNewtonGameDynamicsWorldUpdate");

	// Lock the thread?
	if (!cWorld.m_bSimulationActive)
		m_pMutex->Lock();

	// Let's rock and roll! ;-)
	Start();
}

/**
*  @brief
*    Destructor
*/
WorldThread::~WorldThread()
{
	// Stop the physics simulation
	m_pMutex->Lock();
		m_bShutDown = true;
	m_pMutex->Unlock();
	Join(100); // Use timeout, else this may block forever...

	// Destroy the synchronisation object
	delete m_pMutex;
}


//[-------------------------------------------------------]
//[ Private virtual WorldUpdate functions                 ]
//[-------------------------------------------------------]
bool WorldThread::IsThread()
{
	return true;
}

bool WorldThread::Lock()
{
	// Lock the synchronisation object
	return m_pMutex->Lock();
}

bool WorldThread::Update(float fTimeScaleFactor, float fMaxTimeDifference, float fSimulationSpeed, float fFrameRate)
{
	// Just update settings - the physics itself is NOT updated in here!
	m_fTimeScaleFactor   = fTimeScaleFactor;
	m_fMaxTimeDifference = fMaxTimeDifference;
	m_fSimulationSpeed   = fSimulationSpeed;
	m_fFrameRate         = fFrameRate;

	// Done
	return true;
}

bool WorldThread::Unlock()
{
	// Unlock the synchronisation object
	return m_pMutex->Unlock();
}


//[-------------------------------------------------------]
//[ Public virtual PLGeneral::Thread functions            ]
//[-------------------------------------------------------]
int WorldThread::Run()
{
	// Simulation loop
	while (!m_bShutDown) {
		// Currently paused?
		if (Timing::GetInstance()->IsPaused()) {
			m_nLastTime = System::GetInstance()->GetMilliseconds();
		} else {
			// Lock the synchronisation object
			const MutexGuard cMutexGuard(*m_pMutex);

			// Update the physics
			WorldUpdate::Update(m_fTimeScaleFactor, m_fMaxTimeDifference, m_fSimulationSpeed, m_fFrameRate);
		}

		// Sleep...
		System::GetInstance()->Sleep(static_cast<uint32>(1000.0f/m_fFrameRate));
	}

	// Done
	return 0;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton
