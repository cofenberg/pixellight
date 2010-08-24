/*********************************************************\
 *  File: Type.h                                         *
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


#ifndef __PLCORE_TYPE_H__
#define __PLCORE_TYPE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLGeneral/String/Tokenizer.h>
#include "PLCore/PLCoreDefinitions.h"
#include "PLCore/Base/Tools/CompileError.h"
#include "PLCore/Base/Tools/TypeTraits.h"
#include "PLCore/Base/Var/DynVar.h"
#include "PLCore/Base/Type/EnumType.h"
#include "PLCore/Base/TypeInfo/TypeInfo.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Generic type wrapper
*/
template <typename T>
class Type : public Type< typename CheckType<T>::Type > {
};


//[-------------------------------------------------------]
//[ Include type implementations                          ]
//[-------------------------------------------------------]
#include "TypeInvalid.inl"
#include "TypeNull.inl"
#include "TypeVoid.inl"
#include "TypeBool.inl"
//#include "TypeInt.inl"		// Should be the same as int32
#include "TypeInt8.inl"
#include "TypeInt16.inl"
#include "TypeInt32.inl"
#include "TypeUInt8.inl"
#include "TypeUInt16.inl"
#include "TypeUInt32.inl"
#include "TypeFloat.inl"
#include "TypeDouble.inl"
#include "TypeString.inl"
#include "TypeEnumPlain.inl"
#include "TypeEnum.inl"
#include "TypeFlag.inl"
#include "TypePtr.inl"
#include "TypeRef.inl"
#include "TypeObjectPtr.inl"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_TYPE_H__
