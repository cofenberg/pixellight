/*********************************************************\
 *  File: DynVar.cpp                                     *
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
#include "PLCore/PLCoreDefinitions.h"
#include "PLCore/Base/Type/Type.h"
#include "PLCore/Base/Var/DynVar.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DynVar::DynVar()
{
}

/**
*  @brief
*    Destructor
*/
DynVar::~DynVar()
{
}


//[-------------------------------------------------------]
//[ Public virtual DynVar functions                       ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get variable descriptor
*/
const VarDesc *DynVar::GetDesc() const
{
	// No descriptor by default
	return NULL;
}

/**
*  @brief
*    Get type
*/
DynTypeInfo &DynVar::GetType() const
{
	// Return unknown type
	return TypeInfo<NullType>::Instance;
}

/**
*  @brief
*    Get type ID
*/
int DynVar::GetTypeID() const
{
	// Return unknown type
	return TypeNull;
}

/**
*  @brief
*    Get type name
*/
String DynVar::GetTypeName() const
{
	// Return unknown type
	return "";
}

/**
*  @brief
*    Check if variable is set to default value
*/
bool DynVar::IsDefault() const
{
	// No data
	return false;
}

/**
*  @brief
*    Set variable to default value
*/
void DynVar::SetDefault()
{
	// No data
}

/**
*  @brief
*    Get default value as string
*/
String DynVar::GetDefault() const
{
	// No data
	return "";
}

/**
*  @brief
*    Set value
*/
void DynVar::SetVar(const DynVar *pValue)
{
	// No data
}

/**
*  @brief
*    Get value
*/
bool DynVar::GetBool() const
{
	// No data available
	return false;
}

/**
*  @brief
*    Set value
*/
void DynVar::SetBool(bool bValue)
{
	// No data
}

/**
*  @brief
*    Get value
*/
int DynVar::GetInt() const
{
	// No data available
	return 0;
}

/**
*  @brief
*    Set value
*/
void DynVar::SetInt(int nValue)
{
	// No data
}

/**
*  @brief
*    Get value
*/
int8 DynVar::GetInt8() const
{
	// No data available
	return 0;
}

/**
*  @brief
*    Set value
*/
void DynVar::SetInt8(int8 nValue)
{
	// No data
}

/**
*  @brief
*    Get value
*/
int16 DynVar::GetInt16() const
{
	// No data available
	return 0;
}

/**
*  @brief
*    Set value
*/
void DynVar::SetInt16(int16 nValue)
{
	// No data
}

/**
*  @brief
*    Get value
*/
int32 DynVar::GetInt32() const
{
	// No data available
	return 0;
}

/**
*  @brief
*    Set value
*/
void DynVar::SetInt32(int32 nValue)
{
	// No data
}

/**
*  @brief
*    Get value
*/
int64 DynVar::GetInt64() const
{
	// No data available
	return 0;
}

/**
*  @brief
*    Set value
*/
void DynVar::SetInt64(int64 nValue)
{
	// No data
}

/**
*  @brief
*    Get value
*/
uint8 DynVar::GetUInt8() const
{
	// No data available
	return 0;
}

/**
*  @brief
*    Set value
*/
void DynVar::SetUInt8(uint8 nValue)
{
	// No data
}

/**
*  @brief
*    Get value
*/
uint16 DynVar::GetUInt16() const
{
	// No data available
	return 0;
}

/**
*  @brief
*    Set value
*/
void DynVar::SetUInt16(uint16 nValue)
{
	// No data
}

/**
*  @brief
*    Get value
*/
uint32 DynVar::GetUInt32() const
{
	// No data available
	return 0;
}

/**
*  @brief
*    Set value
*/
void DynVar::SetUInt32(uint32 nValue)
{
	// No data
}

/**
*  @brief
*    Get value
*/
uint64 DynVar::GetUInt64() const
{
	// No data available
	return 0;
}

/**
*  @brief
*    Set value
*/
void DynVar::SetUInt64(uint64 nValue)
{
	// No data
}

/**
*  @brief
*    Get value
*/
uint_ptr DynVar::GetUIntPtr() const
{
	// No data available
	return 0;
}

/**
*  @brief
*    Set value
*/
void DynVar::SetUIntPtr(uint_ptr nValue)
{
	// No data
}

/**
*  @brief
*    Get value
*/
float DynVar::GetFloat() const
{
	// No data available
	return 0.0f;
}

/**
*  @brief
*    Set value
*/
void DynVar::SetFloat(float fValue)
{
	// No data
}

/**
*  @brief
*    Get value
*/
double DynVar::GetDouble() const
{
	// No data available
	return 0.0;
}

/**
*  @brief
*    Set value
*/
void DynVar::SetDouble(double dValue)
{
	// No data
}

/**
*  @brief
*    Get value
*/
String DynVar::GetString() const
{
	// No data available
	return "";
}

/**
*  @brief
*    Set value
*/
void DynVar::SetString(const String &sValue)
{
	// No data
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
