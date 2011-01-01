/*********************************************************\
 *  File: Stack.h                                        *
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


#ifndef __PLGENERAL_CONTAINER_STACK_H__
#define __PLGENERAL_CONTAINER_STACK_H__
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
*    Stack template (FILO -> First In Last Out)
*
*  @remarks
*  @verbatim
*    Simple extendable stack using a linked list
*    The stack will hold copies of the type used in the stack,
*    so note that your classes should supply a copy (=) operator!
*
*    Usage example:
*    Stack<MyClass> cStack;  // Create stack
*    MyClass T, T1, T2, T3;  // Test class instances
*    cStack.Push(T1);        // Push a copy of T1 onto the stack
*    cStack.Push(T2);        // Push a copy of T2 onto the stack
*    cStack.Push(T3);        // Push a copy of T3 onto the stack
*    cStack.Pop(&T);         // Pop last element (T3)
*    cStack.Pop(&T);         // Pop last element (T2)
*    cStack.Pop(&T);         // Pop last element (T1)
*  @endverbatim
*/
template <class ValueType>
class Stack {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		Stack();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source stack to copy from
		*/
		Stack(const Stack<ValueType> &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		~Stack();

		/**
		*  @brief
		*    Push an element onto the stack (enqueue)
		*
		*  @param[in] Element
		*    New stack element
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool Push(const ValueType &Element);

		/**
		*  @brief
		*    Pops the top element from the stack (dequeue)
		*
		*  @param[out] pElement
		*    If not NULL, this will receive the popped element
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - On error, pElement is NOT touched, so ensure that you take this case into account!
		*/
		bool Pop(ValueType *pElement = NULL);

		/**
		*  @brief
		*    Returns the top element without removing it
		*
		*  @return
		*    Top stack element
		*/
		ValueType Top() const;

		/**
		*  @brief
		*    Returns the number of elements on the stack
		*
		*  @return
		*    Number of stack elements
		*/
		uint32 GetNumOfElements() const;

		/**
		*  @brief
		*    Copies the data from another stack
		*
		*  @param[in] cSource
		*    Stack to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Stack<ValueType> &operator =(const Stack<ValueType> &cSource);

		/**
		*  @brief
		*    Clears the whole stack
		*/
		void Clear();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Push an element to the back of the stack
		*
		*  @param[in] Element
		*    New stack element
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool PushBack(const ValueType &Element);


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal stack element
		*/
		struct StackElement {
			StackElement *pNext;	/**< Pointer to the next element on the stack, can be NULL */
			ValueType		  Data;		/**< The stored data */
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
		uint32		  m_nNumOfElements;	/**< Number of elements on the stack */
		StackElement *m_pTop;			/**< Pointer to the top element, can be NULL */
		StackElement *m_pBottom;		/**< Pointer to the bottom element, can be NULL */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/Stack.inl"


#endif // __PLGENERAL_CONTAINER_STACK_H__
