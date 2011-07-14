/*********************************************************\
 *  File: TimerThread.cpp                                *
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
#include <PLGeneral/System/Mutex.h>
#include "PLGui/Gui/Base/GuiMessage.h"
#include "PLGui/Gui/Resources/Timer.h"
#include "PLGui/Gui/Resources/TimerThread.h"
#include "PLGui/Gui/Gui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TimerThread::TimerThread(Timer &cTimer, uint64 nTimeout, bool bOnce) :
	m_cTimer(cTimer),
	m_pMutex(new Mutex()),
	m_nTimeout(nTimeout),
	m_bOnce(bOnce),
	m_bShutdown(false)
{
}

/**
*  @brief
*    Destructor
*/
TimerThread::~TimerThread()
{
	// Delete mutex
	delete m_pMutex;
}

/**
*  @brief
*    Stop timer thread
*/
void TimerThread::StopTimer()
{
	// Deactivate timer
	m_pMutex->Lock();
	m_bShutdown = true;
	m_pMutex->Unlock();

	// Wait for thread to exit
	if (!Join(200)) {
		Terminate();
		m_pMutex->Unlock();
	}
}

/**
*  @brief
*    Fire timer
*/
void TimerThread::Fire()
{
	// Send timer message
	m_cTimer.GetGui()->PostMessage(GuiMessage::OnTimer(&m_cTimer));
}


//[-------------------------------------------------------]
//[ Private virtual ThreadFunction functions              ]
//[-------------------------------------------------------]
int TimerThread::Run()
{
	// Start timer loop
	bool bRunning = true;
	do {
		// Wait for timeout
		System::GetInstance()->Sleep(m_nTimeout);

		// Timer fired
		Fire();

		// Check if timer is still active
		m_pMutex->Lock();
		if (m_bOnce)	 bRunning = false;
		if (m_bShutdown) bRunning = false;
		m_pMutex->Unlock();
	} while (bRunning);

	// Timer is no longer active
	m_cTimer.m_bActive = false;

	// Done
	return 0;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
