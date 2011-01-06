/*********************************************************\
 *  File: Queue.h                                        *
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


#ifndef __PLGENERAL_CONTAINER_QUEUE_H__
#define __PLGENERAL_CONTAINER_QUEUE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/PLGeneral.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Queue (FIFO -> First In First Out) template
*
*  @remarks
*  @verbatim
*    Simple extendable queue using a linked list.
*    The queue will hold copies of the type used in the queue,
*    so note that your classes should supply a copy (=) operator!
*
*    Usage example:
*    Queue<MyClass> cQueue;  // Create queue
*    MyClass T, T1, T2, T3;  // Test class instances
*    cQueue.Push(T1);        // Push a copy of T1 onto the queue
*    cQueue.Push(T2);        // Push a copy of T2 onto the queue
*    cQueue.Push(T3);        // Push a copy of T3 onto the queue
*    cQueue.Pop(&T);         // Pop last element (T1)
*    cQueue.Pop(&T);         // Pop last element (T2)
*    cQueue.Pop(&T);         // Pop last element (T3)
*  @endverbatim
*/
template <class ValueType>
class Queue {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		Queue();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source queue to copy from
		*/
		Queue(const Queue<ValueType> &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		~Queue();

		/**
		*  @brief
		*    Push an element onto the queue (enqueue)
		*
		*  @param[in] Element
		*    New queue element
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool Push(const ValueType &Element);

		/**
		*  @brief
		*    Pops the bottom element from the queue (dequeue)
		*
		*  @param[out] pElement
		*    If not a null pointer, this will receive the popped element
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - On error, pElement is NOT touched, so ensure that you take this case into account!
		*/
		bool Pop(ValueType *pElement = nullptr);

		/**
		*  @brief
		*    Returns the bottom element without removing it
		*
		*  @return
		*    Bottom queue element
		*/
		ValueType Bottom() const;

		/**
		*  @brief
		*    Returns the number of elements on the queue
		*
		*  @return
		*    Number of queue elements
		*/
		uint32 GetNumOfElements() const;

		/**
		*  @brief
		*    Copies the data from another queue
		*
		*  @param[in] cSource
		*    Queue to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Queue<ValueType> &operator =(const Queue<ValueType> &cSource);

		/**
		*  @brief
		*    Clears the whole queue
		*/
		void Clear();


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal queue element
		*/
		struct QueueElement {
			QueueElement *pNext;	/**< Pointer to the next element on the queue, can be a null pointer */
			ValueType	  Data;		/**< The stored data */
		};


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		static ValueType temp;	/** Temp object */


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		uint32		  m_nNumOfElements;	/**< Number of elements on the queue */
		QueueElement *m_pTop;			/**< Pointer to the top element, can be a null pointer */
		QueueElement *m_pBottom;		/**< Pointer to the bottom element, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/Queue.inl"


#endif // __PLGENERAL_CONTAINER_QUEUE_H__
