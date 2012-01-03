/*********************************************************\
 *  File: List.h                                         *
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


#ifndef __PLCORE_CONTAINER_LIST_H__
#define __PLCORE_CONTAINER_LIST_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Container/Container.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


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
*    want to receive element x, internally the process begins with the first element and
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
			ListElement *pNextElement;		/**< Pointer to the next element in the list, can be a null pointer */
			ListElement *pPreviousElement;	/**< Pointer to the previous element in the list, can be a null pointer */
			ValueType	 Data;				/**< The stored data */
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		uint32		 m_nNumOfElements;	/**< Current number of elements */
		ListElement *m_pFirstElement;	/**< Pointer to first list element, can be a null pointer */
		ListElement *m_pLastElement;	/**< Pointer to last list element, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Public virtual Iterable functions                     ]
	//[-------------------------------------------------------]
	public:
		virtual Iterator<ValueType> GetIterator(uint32 nIndex = 0) const override;
		virtual ConstIterator<ValueType> GetConstIterator(uint32 nIndex = 0) const override;
		virtual Iterator<ValueType> GetEndIterator() const override;
		virtual ConstIterator<ValueType> GetConstEndIterator() const override;


	//[-------------------------------------------------------]
	//[ Public virtual Container functions                    ]
	//[-------------------------------------------------------]
	public:
		virtual bool IsEmpty() const override;
		virtual uint32 GetNumOfElements() const override;
		virtual uint32 GetElementSize() const override;
		virtual uint32 GetSize() const override;
		virtual void Clear() override;
		virtual bool IsElement(const ValueType &Element) const override;
		virtual int GetIndex(const ValueType &Element) const override;
		virtual ValueType &Get(uint32 nIndex) const override;
		virtual ValueType &operator [](uint32 nIndex) const override;
		virtual bool Replace(const ValueType &Element1, const ValueType &Element2) override;
		virtual bool ReplaceAtIndex(uint32 nIndex, const ValueType &Element) override;
		virtual ValueType &Add() override;
		virtual ValueType &Add(const ValueType &Element) override;
		virtual uint32 Add(const ValueType *pElements, uint32 nCount) override;
		virtual Container<ValueType> &operator +=(const ValueType &Element) override;
		virtual bool Add(const Container<ValueType> &lstContainer, uint32 nStart = 0, uint32 nCount = 0) override;
		virtual Container<ValueType> &operator +=(const Container<ValueType> &lstContainer) override;
		virtual ValueType &AddAtIndex(int nIndex) override;
		virtual ValueType &AddAtIndex(const ValueType &Element, int nIndex) override;
		virtual bool Remove(const ValueType &Element) override;
		virtual bool RemoveAtIndex(uint32 nElement) override;
		virtual Container<ValueType> &operator -=(const ValueType &Element) override;
		virtual bool Remove(const Container<ValueType> &lstContainer, uint32 nStart = 0, uint32 nCount = 0) override;
		virtual Container<ValueType> &operator -=(const Container<ValueType> &lstContainer) override;
		virtual bool Copy(const Container<ValueType> &lstContainer, uint32 nStart = 0, uint32 nCount = 0) override;
		virtual Container<ValueType> &operator =(const Container<ValueType> &lstContainer) override;
		virtual bool Compare(const Container<ValueType> &lstContainer, uint32 nStart = 0, uint32 nCount = 0) const override;
		virtual bool operator ==(const Container<ValueType> &lstContainer) const override;
		virtual bool operator !=(const Container<ValueType> &lstContainer) const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Container/List.inl"


#endif // __PLCORE_CONTAINER_LIST_H__
