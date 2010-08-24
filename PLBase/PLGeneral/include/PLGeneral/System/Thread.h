/*********************************************************\
 *  File: Thread.h                                       *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLGENERAL_THREAD_H__
#define __PLGENERAL_THREAD_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/String.h"
#include "PLGeneral/System/ThreadFunction.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class ThreadImpl;


//[-------------------------------------------------------]
//[ Data types                                            ]
//[-------------------------------------------------------]
typedef int (*THREADFUNCTION)(void*);	/**< Static thread function */


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Thread class
*/
class Thread : public ThreadFunction {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class System;
	friend class ThreadLinux;


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Thread priority class
		*/
		enum EPriorityClass {
			IdlePriorityClass,			/**< Idle priority class */
			BelowNormalPriorityClass,	/**< Below normal priority class */
			NormalPriorityClass,		/**< Normal priority class (default) */
			AboveNormalPriorityClass,	/**< Above normal priority class */
			HighPriorityClass,			/**< High priority class */
			RealtimePriorityClass		/**< Realtime priority class (ONLY use this if you REALLY need it!) */
		};

		/**
		*  @brief
		*    Thread priority within the priority class it is in
		*/
		enum EPriority {
			IdlePriority,			/**< Idle priority */
			LowestPriority,			/**< Lowest priority */
			BelowNormalPriority,	/**< Below normal priority */
			NormalPriority,			/**< Normal priority (default) */
			AboveNormalPriority,	/**< Above normal priority */
			HighestPriority,		/**< Highest priority */
			TimeCriticalPriority	/**< Time critical priority */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API Thread();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pThreadFunction
		*    Pointer to the thread function, can be NULL
		*/
		PLGENERAL_API Thread(ThreadFunction *pThreadFunction);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pThreadFunction
		*    Pointer to a static thread function, can be NULL
		*  @param[in] pData
		*    Data to be passed to the thread function, can be NULL
		*/
		PLGENERAL_API Thread(THREADFUNCTION pThreadFunction, void *pData);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nThreadID
		*    A system specific thread ID, 0 for current thread
		*/
		PLGENERAL_API Thread(uint32 nThreadID);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API virtual ~Thread();

		/**
		*  @brief
		*    Returns the name of the thread
		*
		*  @return
		*    Thread name
		*
		*  @remarks
		*    The thread name is not used internally, it's for user usage only and especially
		*    for debugging purposes quite useful. It's recommended to give threads unique
		*    names. By default, no thread name is set.
		*/
		PLGENERAL_API String GetName() const;

		/**
		*  @brief
		*    Sets the name of the thread
		*
		*  @param[in] sName
		*    Thread name
		*
		*  @see
		*    - GetName()
		*/
		PLGENERAL_API void SetName(const String &sName);

		/**
		*  @brief
		*    Returns the unique system ID of the thread
		*
		*  @return
		*    Thread ID
		*/
		PLGENERAL_API uint32 GetID() const;

		/**
		*  @brief
		*    Returns whether the thread is active
		*
		*  @return
		*    'true' if the thread is active, else 'false'
		*/
		PLGENERAL_API bool IsActive() const;

		/**
		*  @brief
		*    Starts the execution of the thread
		*
		*  @return
		*    'true' if the thread could be started
		*/
		PLGENERAL_API bool Start();

		/**
		*  @brief
		*    Stops the execution of the thread
		*
		*  @return
		*    'true' if the thread could be stopped
		*
		*  @remarks
		*    Terminates the thread ungracefully. Instead of using this function you
		*    should signal the thread and wait until it has quit by itself.
		*/
		PLGENERAL_API bool Terminate();

		/**
		*  @brief
		*    Waits until the thread has been stopped
		*
		*  @return
		*    'true' if the thread has been stopped
		*
		*  @note
		*    - It's recommended to use the join version with a timeout instead of this function to
		*      ensure that the thread is stopped within a defined time (no deadlock's)
		*/
		PLGENERAL_API bool Join();

		/**
		*  @brief
		*    Waits until the thread has been stopped
		*
		*  @param[in] nTimeout
		*    Time in milliseconds to wait
		*
		*  @return
		*    'true' if the thread has been stopped
		*/
		PLGENERAL_API bool Join(uint32 nTimeout);

		/**
		*  @brief
		*    Returns the priority class the thread is in
		*
		*  @return
		*    The priority class the thread is in
		*
		*  @remarks
		*    The thread priority settings are only 'hints' for the OS how to deal with the thread. They
		*    are no 'facts' and may differ from OS to OS.
		*/
		PLGENERAL_API EPriorityClass GetPriorityClass() const;

		/**
		*  @brief
		*    Sets the priority class the thread is in
		*
		*  @param[in] nPriorityClass
		*    New priority class the thread is in
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @see
		*    - GetPriorityClass()
		*/
		PLGENERAL_API bool SetPriorityClass(EPriorityClass nPriorityClass = NormalPriorityClass);

		/**
		*  @brief
		*    Returns the thread priority within the priority class it is in
		*
		*  @return
		*    The thread priority within the priority class it is in
		*
		*  @see
		*    - GetPriorityClass()
		*/
		PLGENERAL_API EPriority GetPriority() const;

		/**
		*  @brief
		*    Sets the thread priority within the priority class it is in
		*
		*  @param[in] nPriority
		*    New thread priority within the priority class it is in
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @see
		*    - GetPriorityClass()
		*/
		PLGENERAL_API bool SetPriority(EPriority nPriority = NormalPriority);


	//[-------------------------------------------------------]
	//[ Public virtual ThreadFunction functions               ]
	//[-------------------------------------------------------]
	public:
		PLGENERAL_API virtual int Run();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Thread(const Thread &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Thread &operator =(const Thread &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		ThreadImpl	   *m_pThreadImpl;		/**< Pointer to the system specific implementation (assumed to be never NULL!) */
		ThreadFunction *m_pThreadFunction;	/**< Pointer to a thread function to execute, can be NULL */
		THREADFUNCTION  m_pStaticFunction;	/**< Pointer to a static function to execute, can be NULL */
		void		   *m_pStaticData;		/**< Additional data to pass to the static function, can be NULL */
		String			m_sName;			/**< Thread name */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_THREAD_H__
