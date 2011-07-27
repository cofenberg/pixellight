/*********************************************************\
 *  File: QuickSort.h                                    *
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


#ifndef __PLCORE_QUICKSORT_H__
#define __PLCORE_QUICKSORT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/PLCore.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Quick sort class
*
*  @remarks
*  @verbatim
*    Usage example:
*    // Derive your own class from QuickSort to implement the compare function:
*    class QuickSortTest : public QuickSort {
*      private:
*        virtual char Compare(void *pElement1, void *pElement2) const {
*          if (*((int*)pElement1)  < *((int*)pElement2)) return -1;
*          if (*((int*)pElement1) == *((int*)pElement2)) return  0;
*          else                                          return  1;
*        };
*     };
*     // Sort example using the derived class above:
*     QuickSortTest cQuickSort;
*     int nTest[10] = {3, 6, 2, 6, 8, 4, 36, 22, 64, 99};
*     cQuickSort.Sort(nTest, 10, sizeof(int));
*  @endverbatim
*/
class QuickSort {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API QuickSort();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~QuickSort();

		/**
		*  @brief
		*    Sorts a set of data using the QuickSort algorithm
		*
		*  @param[in, out] pData
		*    Data to sort (MUST be valid!)
		*  @param[in]      nNumOfElements
		*    Number of data elements to sort (MUST be valid!)
		*  @param[in]      nElementSize
		*    Size of an element in bytes (MUST be valid!)
		*
		*  @return
		*    'true' if all went fine, else 'false' (invalid data etc.)
		*/
		PLCORE_API bool Sort(void *pData, uint32 nNumOfElements, uint32 nElementSize);


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
		QuickSort(const QuickSort &cSource);

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
		QuickSort &operator =(const QuickSort &cSource);

		/**
		*  @brief
		*    Sorts a set of data recursive using the QuickSort algorithm
		*
		*  @param[in] pLeftStart
		*    Left start element (always valid!)
		*  @param[in] pRightStart
		*    Right start element (always valid!)
		*/
		void SortRec(uint8 *pLeftStart, uint8 *pRightStart);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		uint8  *m_pData;		/**< Data to sort, can be a null pointer */
		uint32  m_nElementSize;	/**< Size of an element in bytes */
		uint8  *m_pTemp;		/**< Temp buffer for swapping, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Virtual private QuickSort functions                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Custom element compare function
		*
		*  @param[in] pElement1
		*    First element
		*  @param[in] pElement2
		*    Second element
		*
		*  @return
		*    < 0 pElement1 less than pElement2\n
		*    = 0 pElement1 equivalent to pElement2\n
		*    > 0 pElement1 greater than pElement2
		*/
		virtual char Compare(void *pElement1, void *pElement2) const = 0;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_QUICKSORT_H__
