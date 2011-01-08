/*********************************************************\
 *  File: Vector3i.h                                     *
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


#ifndef __PLMATH_VECTOR3I_H__
#define __PLMATH_VECTOR3I_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include "PLMath/PLMath.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    3D integer vector
*/
class Vector3i {


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		PLMATH_API static const Vector3i Zero;			/**<  0,  0,  0 */
		PLMATH_API static const Vector3i One;			/**<  1,  1,  1 */
		PLMATH_API static const Vector3i NegativeOne;	/**< -1, -1, -1 */
		PLMATH_API static const Vector3i UnitX;			/**<  1,  0,  0 */
		PLMATH_API static const Vector3i UnitY;			/**<  0,  1,  0 */
		PLMATH_API static const Vector3i UnitZ;			/**<  0,  0,  1 */
		PLMATH_API static const Vector3i NegativeUnitX;	/**< -1,  0,  0 */
		PLMATH_API static const Vector3i NegativeUnitY;	/**<  0, -1,  0 */
		PLMATH_API static const Vector3i NegativeUnitZ;	/**<  0,  0, -1 */


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Some direct vector element accesses
		*/
		union {
			/**
			*  @brief
			*    Vector element array access
			*/
			int nV[3];

			/**
			*  @brief
			*    Known vector element names when dealing with positions or directions
			*/
			struct {
				int x, y, z;
			};

			/**
			*  @brief
			*    Known vector element names when dealing with sizes
			*/
			struct {
				int width, height, depth;
			};
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor setting all components to 0
		*/
		inline Vector3i();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nX
		*    X component
		*  @param[in] nY
		*    Y component
		*  @param[in] nZ
		*    Z component
		*/
		inline Vector3i(int nX, int nY, int nZ);

		/**
		*  @brief
		*    Destructor
		*/
		inline ~Vector3i();

		//[-------------------------------------------------------]
		//[ Get and set                                           ]
		//[-------------------------------------------------------]
		inline operator int *() const;
		inline operator const int *() const;
		inline int &operator [](int nIndex);
		inline const int &operator [](int nIndex) const;

		/**
		*  @brief
		*    Set vector
		*
		*  @param[in] nX
		*    X component
		*  @param[in] nY
		*    Y component
		*  @param[in] nZ
		*    Z component
		*/
		inline void Set(int nX, int nY, int nZ);

		/**
		*  @brief
		*    Set X component
		*
		*  @param[in] nX
		*    X component
		*/
		inline void SetX(int nX);

		/**
		*  @brief
		*    Set Y component
		*
		*  @param[in] nY
		*    Y component
		*/
		inline void SetY(int nY);

		/**
		*  @brief
		*    Set Z component
		*
		*  @param[in] nZ
		*    Z component
		*/
		inline void SetZ(int nZ);

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] vV
		*    Source vector to copy
		*
		*  @return
		*    This vector
		*/
		inline Vector3i &operator =(const Vector3i &vV);

		/**
		*  @brief
		*    Compare operator
		*
		*  @param[in] vV
		*    Vector to compare with
		*
		*  @return
		*    'true' if equal, else 'false'
		*/
		inline bool operator ==(const Vector3i &vV) const;

		/**
		*  @brief
		*    Compare operator
		*
		*  @param[in] vV
		*    Vector to compare with
		*
		*  @return
		*    'true' if not equal, else 'false'
		*/
		inline bool operator !=(const Vector3i &vV) const;

		/**
		*  @brief
		*    Compares two vectors
		*
		*  @param[in] vV
		*    Vector to compare with
		*
		*  @return
		*    'true' if ALL components of this vector are greater, else 'false'
		*/
		inline bool operator >(const Vector3i &vV) const;

		/**
		*  @brief
		*    Compares two vectors
		*
		*  @param[in] vV
		*    Vector to compare with
		*
		*  @return
		*    'true' if ALL components of this vector are less, else 'false'
		*/
		inline bool operator <(const Vector3i &vV) const;

		/**
		*  @brief
		*    Compares two vectors
		*
		*  @param[in] vV
		*    Vector to compare with
		*
		*  @return
		*    'true' if ALL components of this vector are greater or equal, else 'false'
		*/
		inline bool operator >=(const Vector3i &vV) const;

		/**
		*  @brief
		*    Compares two vectors
		*
		*  @param[in] vV
		*    Vector to compare with
		*
		*  @return
		*    'true' if ALL components of this vector are less or equal, else 'false'
		*/
		inline bool operator <=(const Vector3i &vV) const;

		/**
		*  @brief
		*    Addition operator
		*
		*  @param[in] vV
		*    Vector to add
		*
		*  @return
		*    The resulting vector
		*/
		inline Vector3i operator +(const Vector3i &vV) const;

		/**
		*  @brief
		*    Addition operator
		*
		*  @param[in] vV
		*    Vector to add
		*
		*  @return
		*    This vector
		*/
		inline Vector3i &operator +=(const Vector3i &vV);

		/**
		*  @brief
		*    Subtraction operator
		*
		*  @param[in] vV
		*    Vector to subtract
		*
		*  @return
		*    The resulting vector
		*/
		inline Vector3i operator -(const Vector3i &vV) const;

		/**
		*  @brief
		*    Subtraction operator
		*
		*  @param[in] vV
		*    Vector to subtract
		*
		*  @return
		*    This vector
		*/
		inline Vector3i &operator -=(const Vector3i &vV);

		/**
		*  @brief
		*    Multiplication operator
		*
		*  @param[in] fFactor
		*    Floating point factor
		*
		*  @return
		*    The resulting vector
		*/
		inline Vector3i operator *(float fFactor) const;

		/**
		*  @brief
		*    Multiplication operator
		*
		*  @param[in] fFactor
		*    Floating point factor
		*
		*  @return
		*    This vector
		*/
		inline Vector3i &operator *=(float fFactor);

		/**
		*  @brief
		*    Division operator
		*
		*  @param[in] fFactor
		*    Floating point divisor
		*
		*  @return
		*    The resulting vector
		*/
		inline Vector3i operator /(float fFactor) const;

		/**
		*  @brief
		*    Division operator
		*
		*  @param[in] fFactor
		*    Floating point divisor
		*
		*  @return
		*    This vector
		*/
		inline Vector3i &operator /=(float fFactor);

		/**
		*  @brief
		*    To string
		*
		*  @return
		*    String with the data
		*/
		PLMATH_API PLGeneral::String ToString() const;

		/**
		*  @brief
		*    From string
		*
		*  @param[in] sString
		*    String with the data
		*/
		PLMATH_API bool FromString(const PLGeneral::String &sString);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLMath/Vector3i.inl"
#include "PLMath/TypeVector3i.inl"


#endif // __PLMATH_VECTOR3I_H__
