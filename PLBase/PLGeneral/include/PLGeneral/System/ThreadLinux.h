/*********************************************************\
 *  File: ThreadLinux.h                                  *
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


#ifndef __PLGENERAL_THREAD_LINUX_H__
#define __PLGENERAL_THREAD_LINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <pthread.h>
#include "PLGeneral/System/ThreadImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Mutex;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linux 'Thread' implementation
*/
class ThreadLinux : public ThreadImpl {


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
		ThreadLinux(Thread &cThread, bool bThreadID, uint32 nThreadID);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ThreadLinux();


	//[-------------------------------------------------------]
	//[ Private virtual ThreadImpl functions                  ]
	//[-------------------------------------------------------]
	private:
		virtual uint32 GetID() const;
		virtual bool IsActive() const;
		virtual bool Start();
		virtual bool Terminate();
		virtual bool Join();
		virtual bool Join(uint32 nTimeout);
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
		*  @param[in] pParameter
		*    Parameter, can be a null pointer
		*
		*  @return
		*    Return value, can be a null pointer
		*/
		static void *RunThread(void *pParameter);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		pthread_t				 m_nThreadID;		/**< PThread thread ID */
		Mutex					*m_pMutex;			/**< Mutex used to detect running state of the thread */
		Thread::EPriorityClass	 m_nPriorityClass;	/**< Priority class the thread is in */
		Thread::EPriority		 m_nPriority;		/**< Thread priority within the priority class it is in */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_THREAD_LINUX_H__
