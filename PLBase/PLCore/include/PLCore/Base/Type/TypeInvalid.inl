/*********************************************************\
 *  File: TypeNullType.inl                               *
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


#ifndef __PLCORE_TYPE_INVALID_INL__
#define __PLCORE_TYPE_INVALID_INL__
#pragma once


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for invalid (unknown) types
*/
template <typename T>
class Type< InvalidType<T> > {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef T _Type;		/**< Real type */
		typedef T _StorageType;	/**< Storage type, for this type identical to the real type */

		// Type ID
		static const int TypeID = TypeInvalid;

		// Get type name
		static PLGeneral::String GetTypeName()
		{
			PLCORE_ERROR(Type_Not_Supported)
		}


};


template <typename T>
class Type< InvalidType< InvalidType<T> > > {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef T _Type;		/**< Real type */
		typedef T _StorageType;	/**< Storage type, for this type identical to the real type */

		// Type ID
		static const int TypeID = TypeInvalid;

		// Get type name
		static PLGeneral::String GetTypeName()
		{
			PLCORE_ERROR(Type_Not_Supported)
		}


};


#endif // __PLCORE_TYPE_INVALID_INL__
