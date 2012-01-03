/*********************************************************\
 *  File: ThreadLinux.h                                  *
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


#ifndef __PLCORE_THREAD_LINUX_H__
#define __PLCORE_THREAD_LINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <pthread.h>
#include "PLCore/System/ThreadImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


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
		*    If 'bThreadID == true' and 'nThreadID == NULL_HANDLE', the current thread
		*    ID will be used. If called from the main thread, this is the
		*    main thread ID.
		*/
		ThreadLinux(Thread &cThread, bool bThreadID, handle nThreadID);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ThreadLinux();


	//[-------------------------------------------------------]
	//[ Private virtual ThreadImpl functions                  ]
	//[-------------------------------------------------------]
	private:
		virtual handle GetID() const override;
		virtual bool IsActive() const override;
		virtual bool Start() override;
		virtual bool Terminate() override;
		virtual bool Join() override;
		virtual bool Join(uint64 nTimeout) override;
		virtual uint32 GetPriorityClass() const override;
		virtual bool SetPriorityClass(uint32 nPriorityClass) override;
		virtual uint32 GetPriority() const override;
		virtual bool SetPriority(uint32 nPriority) override;


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
		pthread_t	 m_nThreadID;		/**< PThread thread ID */
		Mutex		*m_pMutex;			/**< Mutex used to detect running state of the thread */
		uint32		 m_nPriorityClass;	/**< Priority class the thread is in (type: Thread::EPriorityClass) */
		uint32		 m_nPriority;		/**< Thread priority within the priority class it is in (type: Thread::EPriority) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_THREAD_LINUX_H__
