/*********************************************************\
 *  File: BitsetIterator.cpp                             *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/Bitset.h"
#include "PLGeneral/Container/BitsetIterator.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BitsetIterator::BitsetIterator(const Bitset &lstBitset, uint32 nIndex) :
	m_plstBitset(&lstBitset),
	m_nNextID((nIndex > lstBitset.GetNumOfElements()-1) ? lstBitset.GetNumOfElements()-1 : nIndex)
{
}

/**
*  @brief
*    Constructor
*/
BitsetIterator::BitsetIterator(const Bitset &lstBitset) :
	m_plstBitset(&lstBitset),
	m_nNextID(lstBitset.GetNumOfElements())
{
}

/**
*  @brief
*    Copy constructor
*/
BitsetIterator::BitsetIterator(const BitsetIterator &cSource) :
	m_plstBitset(cSource.m_plstBitset),
	m_nNextID(cSource.m_nNextID)
{
}

/**
*  @brief
*    Destructor
*/
BitsetIterator::~BitsetIterator()
{
}


//[-------------------------------------------------------]
//[ Private virtual IteratorImpl functions                ]
//[-------------------------------------------------------]
IteratorImpl<bool> *BitsetIterator::Clone() const
{
	return new BitsetIterator(*this);
}

bool BitsetIterator::HasNext() const
{
	return (m_nNextID < m_plstBitset->GetNumOfElements());
}

bool &BitsetIterator::Next()
{
	return (m_nNextID < m_plstBitset->GetNumOfElements()) ? m_plstBitset->Get(m_nNextID++) : Bitset::Null;
}

bool BitsetIterator::HasPrevious() const
{
	return (m_nNextID != 0);
}

bool &BitsetIterator::Previous()
{
	return m_nNextID ? m_plstBitset->Get(--m_nNextID) : Bitset::Null;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
