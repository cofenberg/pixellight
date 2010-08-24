/*********************************************************\
 *  File: List.h                                         *
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


#ifndef __PLGENERAL_CONTAINER_LIST_H__
#define __PLGENERAL_CONTAINER_LIST_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/Container.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class ValueType> class ListIterator;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linked list class
*
*  @remarks
*    Within the double linked list each node knows it's previous and next element. If you
*    want to recive element x, internally the process begins with the first element and
*    goes to the next until element x was found. As you see the following example isn't
*    that performant:\n
*  @verbatim
*    for (uint32 i=0; i<lstList.GetNumOfElements(); i++) {
*      ListElement &cElement = lstList[i];
*    }
*  @endverbatim
*    Instead use the provided iterator whenever possible:\
*  @verbatim
*    Iterator<ListElement*> cIterator = m_lstList.GetIterator();
*    while (cIterator.HasNext()) {
*        ListElement *pElement = cIterator.Next();
*    }
*  @endverbatim
*/
template <class ValueType>
class List : public Container<ValueType> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ListIterator<ValueType>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		List();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] lstSource
		*    List to copy from
		*  @param[in] nStart
		*    Index the copy operation should start
		*  @param[in] nCount
		*    Number of elements to copy, if 0 copy all elements of lstSource behind nStart
		*/
		List(const List<ValueType> &lstSource, uint32 nStart = 0, uint32 nCount = 0);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] lstSource
		*    Container to copy from
		*  @param[in] nStart
		*    Index the copy operation should start
		*  @param[in] nCount
		*    Number of elements to copy, if 0 copy all elements of lstSource behind nStart
		*/
		List(const Container<ValueType> &lstSource, uint32 nStart = 0, uint32 nCount = 0);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~List();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] lstSource
		*    List to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Container<ValueType> &operator =(const List<ValueType> &lstSource);


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal linked list element
		*/
		struct ListElement {
			ListElement *pNextElement;		/**< Pointer to the next element in the list, can be NULL */
			ListElement *pPreviousElement;	/**< Pointer to the previous element in the list, can be NULL */
			ValueType	 Data;				/**< The stored data */
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		uint32		 m_nNumOfElements;	/**< Current number of elements */
		ListElement *m_pFirstElement;	/**< Pointer to first list element, can be NULL */
		ListElement *m_pLastElement;	/**< Pointer to last list element, can be NULL */


	//[-------------------------------------------------------]
	//[ Public virtual Iterable functions                     ]
	//[-------------------------------------------------------]
	public:
		virtual Iterator<ValueType> GetIterator(uint32 nIndex = 0) const;
		virtual ConstIterator<ValueType> GetConstIterator(uint32 nIndex = 0) const;
		virtual Iterator<ValueType> GetEndIterator() const;
		virtual ConstIterator<ValueType> GetConstEndIterator() const;


	//[-------------------------------------------------------]
	//[ Public virtual Container functions                    ]
	//[-------------------------------------------------------]
	public:
		virtual bool IsEmpty() const;
		virtual uint32 GetNumOfElements() const;
		virtual uint32 GetElementSize() const;
		virtual uint32 GetSize() const;
		virtual void Clear();
		virtual bool IsElement(const ValueType &Element) const;
		virtual int GetIndex(const ValueType &Element) const;
		virtual ValueType &Get(uint32 nIndex) const;
		virtual ValueType &operator [](uint32 nIndex) const;
		virtual bool Replace(const ValueType &Element1, const ValueType &Element2);
		virtual bool ReplaceAtIndex(uint32 nIndex, const ValueType &Element);
		virtual ValueType &Add();
		virtual ValueType &Add(const ValueType &Element);
		virtual uint32 Add(const ValueType *pElements, uint32 nCount);
		virtual Container<ValueType> &operator +=(const ValueType &Element);
		virtual bool Add(const Container<ValueType> &lstContainer, uint32 nStart = 0, uint32 nCount = 0);
		virtual Container<ValueType> &operator +=(const Container<ValueType> &lstContainer);
		virtual ValueType &AddAtIndex(int nIndex);
		virtual bool AddAtIndex(const ValueType &Element, int nIndex);
		virtual bool Remove(const ValueType &Element);
		virtual bool RemoveAtIndex(uint32 nElement);
		virtual Container<ValueType> &operator -=(const ValueType &Element);
		virtual bool Remove(const Container<ValueType> &lstContainer, uint32 nStart = 0, uint32 nCount = 0);
		virtual Container<ValueType> &operator -=(const Container<ValueType> &lstContainer);
		virtual bool Copy(const Container<ValueType> &lstContainer, uint32 nStart = 0, uint32 nCount = 0);
		virtual Container<ValueType> &operator =(const Container<ValueType> &lstContainer);
		virtual bool Compare(const Container<ValueType> &lstContainer, uint32 nStart = 0, uint32 nCount = 0) const;
		virtual bool operator ==(const Container<ValueType> &lstContainer) const;
		virtual bool operator !=(const Container<ValueType> &lstContainer) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/List.inl"


#endif // __PLGENERAL_CONTAINER_LIST_H__
