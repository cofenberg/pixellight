/*********************************************************\
 *  File: QuickSort.cpp                                  *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Core/MemoryManager.h"
#include "PLCore/Tools/QuickSort.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
QuickSort::QuickSort() :
	m_pData(nullptr),
	m_nElementSize(0),
	m_pTemp(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
QuickSort::~QuickSort()
{
}

/**
*  @brief
*    Sorts a set of data using the QuickSort algorithm
*/
bool QuickSort::Sort(void *pData, uint32 nNumOfElements, uint32 nElementSize)
{
	// Check parameters
	if (!pData || !nElementSize)
		return false; // Error!

	// Already 'sorted'? (no elements are sorted *g*)
	if (nNumOfElements) {
		// Init data
		m_pData		   = static_cast<uint8*>(pData);
		m_nElementSize = nElementSize;
		m_pTemp		   = new uint8[nElementSize];

		// Start recursive sort
		SortRec(m_pData, m_pData+nElementSize*(nNumOfElements-1));

		// Cleanup
		delete [] m_pTemp;
		m_pTemp = nullptr;
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
QuickSort::QuickSort(const QuickSort &cSource) :
	m_pData(nullptr),
	m_nElementSize(0),
	m_pTemp(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
QuickSort &QuickSort::operator =(const QuickSort &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Sorts a set of data recursive using the QuickSort algorithm
*/
void QuickSort::SortRec(uint8 *pLeftStart, uint8 *pRightStart)
{
	// First, find pivot element
	uint8 *pPivot = pRightStart;

	// Sort
	uint8 *pLeft  = pLeftStart;
	uint8 *pRight = pRightStart;
	while (pLeft<pRight) {
		// Find left element to swap
		while (Compare(pLeft, pPivot) < 0)
			pLeft  += m_nElementSize;

		// Find right element to swap
		while (Compare(pRight, pPivot) > 0)
			pRight -= m_nElementSize;

		// Finished?
		if (pLeft >= pRight)
			break;

		// Swap the two elements
		MemoryManager::Copy(m_pTemp, pLeft,   m_nElementSize);
		MemoryManager::Copy(pLeft,   pRight,  m_nElementSize);
		MemoryManager::Copy(pRight,  m_pTemp, m_nElementSize);

		// Go to next elements
		pLeft  += m_nElementSize;
		pRight -= m_nElementSize;
	}

	// Swap pivot element
	MemoryManager::Copy(m_pTemp, pPivot,  m_nElementSize);
	MemoryManager::Copy(pPivot,  pLeft,   m_nElementSize);
	MemoryManager::Copy(pLeft,   m_pTemp, m_nElementSize);

	// Left recursion
	if (pLeft-m_nElementSize > pLeftStart)
		SortRec(pLeftStart,	pLeft-m_nElementSize);

	// Right recursion
	if (pLeft+m_nElementSize < pRightStart)
		SortRec(pLeft+m_nElementSize, pRightStart);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
