/*********************************************************\
 *  File: ThreadWindows.h                                *
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


#ifndef __PLCORE_THREAD_WINDOWS_H__
#define __PLCORE_THREAD_WINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/PLCoreWindowsIncludes.h"
#include "PLCore/System/ThreadImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Windows 'Thread' implementation
*/
class ThreadWindows : public ThreadImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Thread;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cThread
		*    Reference to the owning thread
		*  @param[in] bThreadID
		*    If true, use the given thread ID
		*  @param[in] nThreadID
		*    System specific thread ID
		*
		*  @remarks
		*    If 'bThreadID == true' and 'nThreadID == 0', the current thread
		*    ID will be used. If called from the main thread, this is the
		*    main thread ID.
		*/
		ThreadWindows(Thread &cThread, bool bThreadID, uint32 nThreadID);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ThreadWindows();


	//[-------------------------------------------------------]
	//[ Private virtual ThreadImpl functions                  ]
	//[-------------------------------------------------------]
	private:
		virtual uint32 GetID() const;
		virtual bool IsActive() const;
		virtual bool Start();
		virtual bool Terminate();
		virtual bool Join();
		virtual bool Join(uint64 nTimeout);
		virtual Thread::EPriorityClass GetPriorityClass() const;
		virtual bool SetPriorityClass(Thread::EPriorityClass nPriorityClass);
		virtual Thread::EPriority GetPriority() const;
		virtual bool SetPriority(Thread::EPriority nPriority);


	//[-------------------------------------------------------]
	//[ Private static functions                              ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Static thread callback function
		*
		*  @param[in] lpParameter
		*    Parameter, can be a null pointer
		*
		*  @return
		*    Return value
		*/
		static DWORD WINAPI ThreadProc(LPVOID lpParameter);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		HANDLE m_hThread;	/**< Thread handle */
		DWORD  m_nThreadID;	/**< Thread ID */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_THREAD_WINDOWS_H__
