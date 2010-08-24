/*********************************************************\
 *  File: HashMapIterator.inl                            *
 *      Hash map iterator template implementation
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
#include "PLGeneral/Container/HashMap.h"


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
template <class KeyType, class ValueType, class Hasher, class Comparer, class Grower>
HashMapIterator<KeyType, ValueType, Hasher, Comparer, Grower>::HashMapIterator(const HashMap<KeyType, ValueType, Hasher, Comparer, Grower> &mapOwner, uint32 nIndex) :
	m_pmapOwner(&mapOwner),
	m_pNextSlot(NULL),
	m_pPreviousSlot(NULL)
{
	// Is there at least one element within the hash map? (we do not need to check whether the slots are already created :)
	if (m_pmapOwner->GetNumOfElements()) {
		// Find start slot
		if (nIndex <= m_pmapOwner->GetNumOfElements()/2) {
			// Find the first slot
			for (m_nNextSlots=0; m_nNextSlots<m_pmapOwner->GetNumOfSlots(); m_nNextSlots++) {
				// Are there any slots within this list?
				if (m_pmapOwner->m_plstSlots[m_nNextSlots].m_pFirstSlot) {
					// Ok, we found a slots list which has any slots within it
					m_pNextSlot = m_pmapOwner->m_plstSlots[m_nNextSlots].m_pFirstSlot;
					break;
				}
			}

			// Find the correct start slot
			m_nPreviousSlots = m_nNextSlots;
			m_pPreviousSlot  = NULL;
			uint32 nCurrentIndex = 0;
			while (HasNext() && nCurrentIndex < nIndex) {
				m_nPreviousSlots = m_nNextSlots;
				m_pPreviousSlot  = m_pNextSlot;
				Next();
				nCurrentIndex++;
			}
		} else {
			// Find the last slot
			m_nPreviousSlots = m_pmapOwner->GetNumOfSlots()-1;
			int nPreviousSlots = m_nPreviousSlots;
			for (; nPreviousSlots>=0; nPreviousSlots--) {
				// Are there any slots within this list?
				if (m_pmapOwner->m_plstSlots[nPreviousSlots].m_pLastSlot) {
					// Ok, we found a slots list which has any slots within it
					m_pPreviousSlot = m_pmapOwner->m_plstSlots[nPreviousSlots].m_pLastSlot;
					break;
				}
			}
			m_nPreviousSlots = (nPreviousSlots < 0) ? 0 : nPreviousSlots;

			// Find the correct start slot
			m_nNextSlots = m_nPreviousSlots;
			m_pNextSlot  = NULL;
			uint32 nCurrentIndex = m_pmapOwner->GetNumOfElements()-1;
			while (HasPrevious() && nCurrentIndex > nIndex) {
				m_nNextSlots = m_nPreviousSlots;
				m_pNextSlot  = m_pPreviousSlot;
				Previous();
				nCurrentIndex--;
			}
		}
	}
}

/**
*  @brief
*    Constructor
*/
template <class KeyType, class ValueType, class Hasher, class Comparer, class Grower>
HashMapIterator<KeyType, ValueType, Hasher, Comparer, Grower>::HashMapIterator(const HashMap<KeyType, ValueType, Hasher, Comparer, Grower> &mapOwner) :
	m_pmapOwner(&mapOwner),
	m_pNextSlot(NULL),
	m_pPreviousSlot(NULL)
{
	// Is there at least one element within the hash map? (we do not need to check whether the slots are already created :)
	if (m_pmapOwner->GetNumOfElements()) {
		// Find the last slot
		m_nPreviousSlots = m_pmapOwner->GetNumOfSlots()-1;
		int nPreviousSlots = m_nPreviousSlots;
		for (; nPreviousSlots>=0; nPreviousSlots--) {
			// Are there any slots within this list?
			if (m_pmapOwner->m_plstSlots[nPreviousSlots].m_pLastSlot) {
				// Ok, we found a slots list which has any slots within it
				m_pPreviousSlot = m_pmapOwner->m_plstSlots[nPreviousSlots].m_pLastSlot;
				break;
			}
		}
		m_nPreviousSlots = (nPreviousSlots < 0) ? 0 : nPreviousSlots;

		// Find the correct start slot
		m_nNextSlots = m_nPreviousSlots;
		m_pNextSlot  = NULL;
	}
}

/**
*  @brief
*    Copy constructor
*/
template <class KeyType, class ValueType, class Hasher, class Comparer, class Grower>
HashMapIterator<KeyType, ValueType, Hasher, Comparer, Grower>::HashMapIterator(const HashMapIterator<KeyType, ValueType, Hasher, Comparer, Grower> &cSource) :
	m_pmapOwner(cSource.m_pmapOwner),
	m_nNextSlots(cSource.m_nNextSlots),
	m_pNextSlot(cSource.m_pNextSlot),
	m_nPreviousSlots(cSource.m_nPreviousSlots),
	m_pPreviousSlot(cSource.m_pPreviousSlot)
{
}

/**
*  @brief
*    Destructor
*/
template <class KeyType, class ValueType, class Hasher, class Comparer, class Grower>
HashMapIterator<KeyType, ValueType, Hasher, Comparer, Grower>::~HashMapIterator()
{
}


//[-------------------------------------------------------]
//[ Private virtual IteratorImpl functions                ]
//[-------------------------------------------------------]
template <class KeyType, class ValueType, class Hasher, class Comparer, class Grower>
IteratorImpl<ValueType> *HashMapIterator<KeyType, ValueType, Hasher, Comparer, Grower>::Clone() const
{
	return new HashMapIterator<KeyType, ValueType, Hasher, Comparer, Grower>(*this);
}

template <class KeyType, class ValueType, class Hasher, class Comparer, class Grower>
bool HashMapIterator<KeyType, ValueType, Hasher, Comparer, Grower>::HasNext() const
{
	return (m_pNextSlot != NULL);
}

template <class KeyType, class ValueType, class Hasher, class Comparer, class Grower>
ValueType &HashMapIterator<KeyType, ValueType, Hasher, Comparer, Grower>::Next()
{
	// Is there's a next slot?
	if (!m_pNextSlot)
		return HashMap<KeyType, ValueType, Hasher, Comparer, Grower>::Null; // Error!

	// Get the next slot
	m_nPreviousSlots = m_nNextSlots;
	m_pPreviousSlot  = m_pNextSlot;
	m_pNextSlot      = m_pNextSlot->pNextSlot;

	// Is there a next slot?
	if (!m_pNextSlot && m_nNextSlots < m_pmapOwner->GetNumOfSlots()-1) {
		// Ok, now it becomes a bit tricky... look for the next slots list which has any slots within it
		m_nNextSlots++;
		for (; m_nNextSlots<m_pmapOwner->GetNumOfSlots(); m_nNextSlots++) {
			// Are there any slots within this list?
			if (m_pmapOwner->m_plstSlots[m_nNextSlots].m_pFirstSlot) {
				// Ok, we found a slots list which has any slots within it
				m_pNextSlot = m_pmapOwner->m_plstSlots[m_nNextSlots].m_pFirstSlot;
				break;
			}
		}
	}

	// Return the value of the 'current' slot
	return m_pPreviousSlot->Value;
}

template <class KeyType, class ValueType, class Hasher, class Comparer, class Grower>
bool HashMapIterator<KeyType, ValueType, Hasher, Comparer, Grower>::HasPrevious() const
{
	return (m_pPreviousSlot != NULL);
}

template <class KeyType, class ValueType, class Hasher, class Comparer, class Grower>
ValueType &HashMapIterator<KeyType, ValueType, Hasher, Comparer, Grower>::Previous()
{
	// Is there's a previous slot?
	if (!m_pPreviousSlot)
		return HashMap<KeyType, ValueType, Hasher, Comparer, Grower>::Null; // Error!

	// Get the previous slot
	m_nNextSlots    = m_nPreviousSlots;
	m_pNextSlot     = m_pPreviousSlot;
	m_pPreviousSlot = m_pPreviousSlot->pPreviousSlot;

	// Is there a previous slot?
	if (!m_pPreviousSlot && m_nPreviousSlots > 0) {
		// Ok, now it becomes a bit tricky... look for the previous slots list which has any slots within it
		int nPreviousSlots;
		m_nPreviousSlots--;
		for (nPreviousSlots=m_nPreviousSlots; nPreviousSlots>=0; nPreviousSlots--) {
			// Are there any slots within this list?
			if (m_pmapOwner->m_plstSlots[nPreviousSlots].m_pLastSlot) {
				// Ok, we found a slots list which has any slots within it
				m_pPreviousSlot = m_pmapOwner->m_plstSlots[nPreviousSlots].m_pLastSlot;
				break;
			}
		}
		m_nPreviousSlots = (nPreviousSlots < 0) ? 0 : nPreviousSlots;
	}

	// Return the value of the 'current' slot
	return m_pNextSlot->Value;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
