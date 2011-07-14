/*********************************************************\
 *  File: Timer.cpp                                      *
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
#include "PLGui/Gui/Gui.h"
#include "PLGui/Gui/Resources/Timer.h"
#include "PLGui/Gui/Resources/TimerThread.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLGui {


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
uint32 Timer::m_nNextID = 1000;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Timer::Timer(Gui &cGui) :
	m_pGui(&cGui),
	m_nID(++m_nNextID),
	m_pThread(nullptr),
	m_bActive(false),
	m_nTimeout(0)
{
	// Add timer to GUI
	m_pGui->AddTimer(this);
}

/**
*  @brief
*    Destructor
*/
Timer::~Timer()
{
	// Remove timer from GUI
	m_pGui->RemoveTimer(this);

	// Stop timer
	Stop();
}

/**
*  @brief
*    Get owner GUI
*/
Gui *Timer::GetGui() const
{
	// Return GUI
	return m_pGui;
}

/**
*  @brief
*    Get timer ID
*/
uint32 Timer::GetID() const
{
	// Return timer ID
	return m_nID;
}

/**
*  @brief
*    Set timer ID
*/
void Timer::SetID(uint32 nID)
{
	// Set timer ID
	m_nID = nID;
}

/**
*  @brief
*    Check if timer is active
*/
bool Timer::IsActive() const
{
	// Return if the timer is active
	return m_bActive;
}

/**
*  @brief
*    Check if timer fires only once
*/
bool Timer::IsOnce() const
{
	// Return if the timer is firing only once
	return m_bOnce;
}

/**
*  @brief
*    Get timeout interval
*/
uint64 Timer::GetTimeout() const
{
	// Return timeout
	return m_nTimeout;
}

/**
*  @brief
*    Start timer
*/
void Timer::Start(uint64 nTimeout)
{
	// Stop timer
	if (IsActive()) Stop();

	// Save options
	m_nTimeout	= nTimeout;
	m_bActive	= true;
	m_bOnce		= false;

	// Create timer thread
	m_pThread = new TimerThread(*this, m_nTimeout, m_bOnce);
	m_pThread->Start();

	// Emit Start-Event
	EventStart();
}

/**
*  @brief
*    Start timer only once, not periodically
*/
void Timer::StartOnce(uint64 nTimeout)
{
	// Stop timer
	if (IsActive()) Stop();

	// Save options
	m_nTimeout	= nTimeout;
	m_bActive	= true;
	m_bOnce		= true;

	// Create timer thread
	m_pThread = new TimerThread(*this, m_nTimeout, m_bOnce);
	m_pThread->Start();

	// Emit Start-Event
	EventStart();
}

/**
*  @brief
*    Stop timer
*/
void Timer::Stop()
{
	// Is timer active?
	if (IsActive()) {
		// Stop timer thread
		m_pThread->StopTimer();
		delete m_pThread;
		m_pThread = nullptr;

		// Emit Stop-Event
		EventStop();

		// Timer stopped
		m_bActive = false;
	}
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Fire timer
*/
void Timer::Fire()
{
	// Emit event
	EventFire();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
