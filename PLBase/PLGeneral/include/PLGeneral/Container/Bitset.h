/*********************************************************\
 *  File: Bitset.h                                       *
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


#ifndef __PLGENERAL_CONTAINER_BITSET_H__
#define __PLGENERAL_CONTAINER_BITSET_H__
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
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Bit set class
*
*  @remarks
*    The bit set class which is useful when dealing with many binary states because
*    many bits will be put together in variables to save memory. The bit set is
*    resized automatically if required.
*/
class Bitset : public Container<bool> {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nMaxNumOfElements
		*    Maximum number of elements within the bit set
		*  @param[in] bAdded
		*    Are all elements added? (GetNumOfElements() = GetMaxNumOfElements())
		*  @param[in] bInit
		*    Initialize new elements by setting them to null?
		*/
		PLGENERAL_API Bitset(uint32 nMaxNumOfElements = 0, bool bAdded = true, bool bInit = false);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] lstSource
		*    Bitset to copy from
		*  @param[in] nStart
		*    Index the copy operation should start
		*  @param[in] nCount
		*    Number of elements to copy, if 0 copy all elements of lstSource behind nStart
		*/
		PLGENERAL_API Bitset(const Bitset &lstSource, uint32 nStart = 0, uint32 nCount = 0);

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
		PLGENERAL_API Bitset(const Container<bool> &lstSource, uint32 nStart = 0, uint32 nCount = 0);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API virtual ~Bitset();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] lstSource
		*    Bitset to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		inline Container<bool> &operator =(const Bitset &lstSource);

		/**
		*  @brief
		*    Returns the maximum number of elements in the bit set
		*
		*  @return
		*    Maximum number of element in the bit set
		*/
		inline uint32 GetMaxNumOfElements() const;

		/**
		*  @brief
		*    Sets the maximum number of elements in the bit set
		*
		*  @param[in] nMaxNumOfElements
		*    New maximum number of elements (0 = clear bit set)
		*  @param[in] bAdded
		*    Are all elements added? (GetNumOfElements() = GetMaxNumOfElements())
		*  @param[in] bInit
		*    Initialize new elements by setting them to null?
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLGENERAL_API bool Resize(uint32 nMaxNumOfElements, bool bAdded = true, bool bInit = false);

		/**
		*  @brief
		*    Returns the number of elements automatically added if the bit set
		*    size is to small
		*
		*  @return
		*    Number of elements automatically added if the bit set size is to small
		*/
		inline uint32 GetResizeCount() const;

		/**
		*  @brief
		*    Sets the number of elements automatically added if the bit set
		*    size is to small
		*
		*  @param[in] nCount
		*    Number of elements automatically added if the bit set size is to small
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If nCount is 0, the array size isn't changed automatically
		*/
		inline bool SetResizeCount(uint32 nCount = 64);

		/**
		*  @brief
		*    Clears a bit to 0
		*
		*  @param[in] nIndex
		*    Index of the bit to clear
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		inline bool Clear(uint32 nIndex);

		/**
		*  @brief
		*    Clears all bits to 0
		*/
		PLGENERAL_API void ClearAll();

		/**
		*  @brief
		*    Sets the desired bit
		*
		*  @param[in] nIndex
		*    Index of the bit to set
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		inline bool Set(uint32 nIndex);

		/**
		*  @brief
		*    Sets all bits to 1
		*/
		PLGENERAL_API void SetAll();

		/**
		*  @brief
		*    Inverts the desired bit
		*
		*  @param[in] nIndex
		*    Index of the bit to invert
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		inline bool Invert(uint32 nIndex);

		/**
		*  @brief
		*    Inverts all bits
		*/
		inline void InvertAll();

		/**
		*  @brief
		*    Returns if the desired bit slot is a 1 or a 0
		*
		*  @param[in] nIndex
		*    Index of the bit to check
		*
		*  @return
		*    'true' if the bit is set, else 'false'
		*/
		inline bool IsSet(uint32 nIndex) const;

		/**
		*  @brief
		*    Returns the number of set bits (value = 'true')
		*
		*  @return
		*    The number of set bits (value = 'true')
		*/
		PLGENERAL_API uint32 GetNumOfSetBits() const;

		/**
		*  @brief
		*    Returns the internal number of integers (32 bit) used to store the bits
		*
		*  @return
		*    The internal number of integers used to store the bits
		*/
		inline uint32 GetNumOfIntegers() const;

		/**
		*  @brief
		*    Returns the internal integers (32 bit) used to store the bits
		*
		*  @return
		*    The internal integers used to store the bits, can be NULL, DON'T delete the memory!
		*/
		inline const uint32 *GetIntegers() const;

		/**
		*  @brief
		*    Resets the bitset
		*
		*  @remarks
		*    While the Clear() function destroys also the data, this function will only
		*    reset the current number of elements within the array to 0.
		*/
		inline void Reset();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		uint32  m_nMaxNumOfElements;	/**< Maximum number of elements */
		uint32  m_nNumOfElements;		/**< Current number of elements */
		uint32  m_nNumOfIntegers;		/**< Number of integers */
		uint32 *m_pnIntegers;			/**< Bits data, can be NULL */
		uint32  m_nResizeCount;			/**< Automatic resize count */
		// Static data
		PLGENERAL_API static bool m_bBit;	/**< Last returned bit */


	//[-------------------------------------------------------]
	//[ Public virtual Iterable functions                     ]
	//[-------------------------------------------------------]
	public:
		PLGENERAL_API virtual Iterator<bool> GetIterator(uint32 nIndex = 0) const;
		PLGENERAL_API virtual ConstIterator<bool> GetConstIterator(uint32 nIndex = 0) const;
		PLGENERAL_API virtual Iterator<bool> GetEndIterator() const;
		PLGENERAL_API virtual ConstIterator<bool> GetConstEndIterator() const;


	//[-------------------------------------------------------]
	//[ Public virtual Container functions                    ]
	//[-------------------------------------------------------]
	public:
		inline virtual bool IsEmpty() const;
		inline virtual uint32 GetNumOfElements() const;
		inline virtual uint32 GetElementSize() const;
		inline virtual uint32 GetSize() const;
		PLGENERAL_API virtual void Clear();
		inline virtual bool IsElement(const bool &Element) const;
		inline virtual int GetIndex(const bool &Element) const;
		inline virtual bool &Get(uint32 nIndex) const;
		inline virtual bool &operator [](uint32 nIndex) const;
		inline virtual bool Replace(const bool &Element1, const bool &Element2);
		inline virtual bool ReplaceAtIndex(uint32 nIndex, const bool &Element);
		PLGENERAL_API virtual bool &Add();
		PLGENERAL_API virtual bool &Add(const bool &Element);
		PLGENERAL_API virtual uint32 Add(const bool *pElements, uint32 nCount);
		inline virtual Container<bool> &operator +=(const bool &Element);
		PLGENERAL_API virtual bool Add(const Container<bool> &lstContainer, uint32 nStart = 0, uint32 nCount = 0);
		inline virtual Container<bool> &operator +=(const Container<bool> &lstContainer);
		PLGENERAL_API virtual bool &AddAtIndex(int nIndex);
		PLGENERAL_API virtual bool AddAtIndex(const bool &Element, int nIndex);
		inline virtual bool Remove(const bool &Element);
		PLGENERAL_API virtual bool RemoveAtIndex(uint32 nElement);
		inline virtual Container<bool> &operator -=(const bool &Element);
		PLGENERAL_API virtual bool Remove(const Container<bool> &lstContainer, uint32 nStart = 0, uint32 nCount = 0);
		inline virtual Container<bool> &operator -=(const Container<bool> &lstContainer);
		PLGENERAL_API virtual bool Copy(const Container<bool> &lstContainer, uint32 nStart = 0, uint32 nCount = 0);
		inline virtual Container<bool> &operator =(const Container<bool> &lstContainer);
		PLGENERAL_API virtual bool Compare(const Container<bool> &lstContainer, uint32 nStart = 0, uint32 nCount = 0) const;
		inline virtual bool operator ==(const Container<bool> &lstContainer) const;
		inline virtual bool operator !=(const Container<bool> &lstContainer) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/Bitset.inl"


#endif // __PLGENERAL_CONTAINER_BITSET_H__
