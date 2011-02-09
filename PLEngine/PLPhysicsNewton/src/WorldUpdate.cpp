/*********************************************************\
 *  File: WorldUpdate.cpp                                *
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
#include <PLGeneral/System/System.h>
#include "PLPhysicsNewton/World.h"
#include "PLPhysicsNewton/WorldUpdate.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLPhysicsNewton {


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
WorldUpdate::WorldUpdate(World &cWorld) :
	m_pWorld(&cWorld),
	m_nTotalNumOfSteps(0),
	m_nLastTime(System::GetInstance()->GetMilliseconds()),
	m_fTimeElapsed(0.0f)
{
}


//[-------------------------------------------------------]
//[ Protected virtual functions                           ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
WorldUpdate::~WorldUpdate()
{
}

/**
*  @brief
*    Returns whether or not the implementation is using a thread
*/
bool WorldUpdate::IsThread()
{
	return false;
}

/**
*  @brief
*    Locks the updated
*/
bool WorldUpdate::Lock()
{
	// Nothing to do in here

	// Done
	return true;
}

/**
*  @brief
*    Updates the physics
*/
bool WorldUpdate::Update(float fTimeScaleFactor, float fMaxTimeDifference, float fSimulationSpeed, float fFrameRate)
{
	// Get the current time
	const uint32 nTime = System::GetInstance()->GetMilliseconds();

	// Get the number of milliseconds past since the last slice
	const int32 nMilliseconds = nTime - m_nLastTime;

	// Get the number of seconds past since the last slice
	float fSeconds = static_cast<float>(nMilliseconds)/1000.0f*fTimeScaleFactor;
	if (fSeconds > fMaxTimeDifference)
		fSeconds = fMaxTimeDifference;
	m_fTimeElapsed += fSeconds;

	// If the time scale factor is smaller than 1, multiply the step size with this factor for smooth movement
	const float fFrequency = 1.0f/fFrameRate;
	const float fStepSize = (fTimeScaleFactor < 1.0f) ? fFrequency*fTimeScaleFactor*fSimulationSpeed : fFrequency*fSimulationSpeed;

	// Perform physics simulation
	while (m_fTimeElapsed > fStepSize) {
		// Physical world step
		Newton::NewtonUpdate(static_cast<World*>(m_pWorld)->GetNewtonWorld(), fStepSize);

		// Decrease elapsed time
		m_fTimeElapsed -= fStepSize;
	}

	// Update counter
	m_nLastTime = nTime;
	m_nTotalNumOfSteps++;

	// Done
	return true;
}

/**
*  @brief
*    Unlocks the updated
*/
bool WorldUpdate::Unlock()
{
	// Nothing to do in here

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton
