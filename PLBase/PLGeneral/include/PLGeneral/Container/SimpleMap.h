/*********************************************************\
 *  File: SimpleMap.h                                    *
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


#ifndef __PLGENERAL_CONTAINER_SIMPLEMAP_H__
#define __PLGENERAL_CONTAINER_SIMPLEMAP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/Map.h"
#include "PLGeneral/Container/FastPool.h"
#include "PLGeneral/Container/Functions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class KeyType, class ValueType, class Comparer> class SimpleMapIterator;
template <class KeyType, class ValueType, class Comparer> class SimpleMapKeyIterator;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Simple map template
*
*  @remarks
*    This map implementation is quite simple, but not that performant. It's not recommended
*    to use this implementation if you have a lot of elements within the map.
*/
template <class KeyType, class ValueType, class Comparer = CompareFunction>
class SimpleMap : public Map<KeyType, ValueType> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SimpleMapIterator<KeyType, ValueType, Comparer>;
	friend class SimpleMapKeyIterator<KeyType, ValueType, Comparer>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		SimpleMap();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SimpleMap();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    'SimpleMap' to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Map<KeyType, ValueType> &operator =(const SimpleMap<KeyType, ValueType, Comparer> &cSource);


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal fast pool element
		*/
		class Element : public FastPoolElement<Element> {
			public:
				KeyType	  Key;		/**< The key*/
				ValueType Value;	/**< The value */
				bool operator ==(const Element &cOther) const
				{
					return false;
				}
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		FastPool<Element> m_lstElements;	/**< List of elements */


	//[-------------------------------------------------------]
	//[ Public virtual Iterable functions                     ]
	//[-------------------------------------------------------]
	public:
		virtual Iterator<ValueType> GetIterator(uint32 nIndex = 0) const;
		virtual ConstIterator<ValueType> GetConstIterator(uint32 nIndex = 0) const;
		virtual Iterator<ValueType> GetEndIterator() const;
		virtual ConstIterator<ValueType> GetConstEndIterator() const;


	//[-------------------------------------------------------]
	//[ Public virtual Map functions                          ]
	//[-------------------------------------------------------]
	public:
		virtual void Clear();
		virtual bool IsEmpty() const;
		virtual uint32 GetNumOfElements() const;
		virtual bool Add(const KeyType &Key, const ValueType &Value);
		virtual bool Replace(const KeyType &Key, const ValueType &NewValue);
		virtual bool Set(const KeyType &Key, const ValueType &Value);
		virtual bool Remove(const KeyType &Key);
		virtual uint32 RemoveValue(const ValueType &Value);
		virtual const ValueType &Get(const KeyType &Key) const;
		virtual ValueType &Get(const KeyType &Key);
		virtual Iterator<KeyType> GetKeyIterator(uint32 nIndex = 0) const;
		virtual ConstIterator<KeyType> GetConstKeyIterator(uint32 nIndex = 0) const;
		virtual Iterator<KeyType> GetEndKeyIterator() const;
		virtual ConstIterator<KeyType> GetConstEndKeyIterator() const;


	//[-------------------------------------------------------]
	//[ Private virtual Map functions                         ]
	//[-------------------------------------------------------]
	private:
		virtual Map<KeyType, ValueType> &operator =(const Map<KeyType, ValueType> &cMap);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/SimpleMap.inl"


#endif // __PLGENERAL_CONTAINER_SIMPLEMAP_H__
