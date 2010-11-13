/*********************************************************\
 *  File: DefaultValue.h                                 *
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


#ifndef __PLCORE_DEFAULTVALUE_H__
#define __PLCORE_DEFAULTVALUE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include "PLCore/Base/Tools/TypeTraits.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
// Enum type
template <typename T>
class EnumType;

// Flag type
template <typename T>
class FlagType;

template <typename T>
struct CheckType;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
template <typename T>
class DefaultValue : public DefaultValue< typename CheckType<T>::Type > {
};

template <>
class DefaultValue<bool> {
	public:
		static bool Default() {
			return false;
		}
};

/*
template <>
class DefaultValue<int> {
	public:
		static int Default() {
			return 0;
		}
};
*/

template <>
class DefaultValue<PLGeneral::int8> {
	public:
		static PLGeneral::int8 Default() {
			return 0;
		}
};

template <>
class DefaultValue<PLGeneral::int16> {
	public:
		static PLGeneral::int16 Default() {
			return 0;
		}
};

template <>
class DefaultValue<PLGeneral::int32> {
	public:
		static PLGeneral::int32 Default() {
			return 0;
		}
};

template <>
class DefaultValue<PLGeneral::int64> {
	public:
		static PLGeneral::int64 Default() {
			return 0;
		}
};

template <>
class DefaultValue<PLGeneral::uint8> {
	public:
		static PLGeneral::uint8 Default() {
			return 0;
		}
};

template <>
class DefaultValue<PLGeneral::uint16> {
	public:
		static PLGeneral::uint16 Default() {
			return 0;
		}
};

template <>
class DefaultValue<PLGeneral::uint32> {
	public:
		static PLGeneral::uint32 Default() {
			return 0;
		}
};

template <>
class DefaultValue<PLGeneral::uint64> {
	public:
		static PLGeneral::uint64 Default() {
			return 0;
		}
};

template <>
class DefaultValue<float> {
	public:
		static float Default() {
			return 0.0f;
		}
};

template <>
class DefaultValue<double> {
	public:
		static double Default() {
			return 0.0;
		}
};

template <>
class DefaultValue<PLGeneral::String> {
	public:
		static PLGeneral::String Default() {
			return "";
		}
};

template <typename T>
class DefaultValue<T*> {
	public:
		static T* Default() {
			return NULL;
		}
};

template <typename T>
class DefaultValue<T&> {
	public:
		static T& Default() {
			return *(T*)(NULL);
		}
};

template <typename ENUM>
class DefaultValue< EnumTypePlain<ENUM> > {
	public:
		static ENUM Default() {
			return (ENUM)0;
		}
};

template <typename ENUM>
class DefaultValue< EnumType<ENUM> > {
	public:
		// Type
		typedef typename ENUM::_Type _Type;

		static _Type Default() {
			return DefaultValue<_Type>::Default();
		}
};

template <typename ENUM>
class DefaultValue< FlagType<ENUM> > {
	public:
		// Type
		typedef typename ENUM::_Type _Type;

		static _Type Default() {
			return DefaultValue<_Type>::Default();
		}
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_DEFAULTVALUE_H__
