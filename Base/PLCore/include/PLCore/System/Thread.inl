/*********************************************************\
 *  File: Thread.inl                                     *
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
#include "PLCore/System/ThreadImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the name of the thread
*/
inline String Thread::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Sets the name of the thread
*/
inline void Thread::SetName(const String &sName)
{
	m_sName = sName;
}

/**
*  @brief
*    Returns the unique system ID of the thread
*/
inline handle Thread::GetID() const
{
	// Call system implementation
	return m_pThreadImpl->GetID();
}

/**
*  @brief
*    Returns whether the thread is active
*/
inline bool Thread::IsActive() const
{
	// Call system implementation
	return m_pThreadImpl->IsActive();
}

/**
*  @brief
*    Starts the execution of the thread
*/
inline bool Thread::Start()
{
	// Call system implementation
	return m_pThreadImpl->Start();
}

/**
*  @brief
*    Stops the execution of the thread
*/
inline bool Thread::Terminate()
{
	// Call system implementation
	return m_pThreadImpl->Terminate();
}

/**
*  @brief
*    Waits until the thread has been stopped
*/
inline bool Thread::Join()
{
	// Call system implementation
	return m_pThreadImpl->Join();
}

/**
*  @brief
*    Waits until the thread has been stopped
*/
inline bool Thread::Join(uint64 nTimeout)
{
	// Call system implementation
	return m_pThreadImpl->Join(nTimeout);
}

/**
*  @brief
*    Returns the priority class the thread is in
*/
inline Thread::EPriorityClass Thread::GetPriorityClass() const
{
	// Call system implementation
	return static_cast<Thread::EPriorityClass>(m_pThreadImpl->GetPriorityClass());
}

/**
*  @brief
*    Sets the priority class the thread is in
*/
inline bool Thread::SetPriorityClass(EPriorityClass nPriorityClass)
{
	// Call system implementation
	return m_pThreadImpl->SetPriorityClass(nPriorityClass);
}

/**
*  @brief
*    Returns the thread priority within the priority class it is in
*/
inline Thread::EPriority Thread::GetPriority() const
{
	// Call system implementation
	return static_cast<Thread::EPriority>(m_pThreadImpl->GetPriority());
}

/**
*  @brief
*    Sets the thread priority within the priority class it is in
*/
inline bool Thread::SetPriority(EPriority nPriority)
{
	// Call system implementation
	return m_pThreadImpl->SetPriority(nPriority);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
