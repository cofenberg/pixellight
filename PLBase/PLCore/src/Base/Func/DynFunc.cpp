/*********************************************************\
 *  File: DynFunc.cpp                                    *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Func/DynFunc.h"
#include "PLCore/Base/Func/DynParams.h"


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
*    Destructor
*/
DynFunc::~DynFunc()
{
}


//[-------------------------------------------------------]
//[ Public virtual DynFunc functions                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get function descriptor
*/
const FuncDesc *DynFunc::GetDesc() const
{
	// No descriptor by default
	return nullptr;
}

/**
*  @brief
*    Get signature as string
*/
String DynFunc::GetSignature() const
{
	// No function
	return "";
}

/**
*  @brief
*    Call function
*/
void DynFunc::Call(DynParams &cParams)
{
	// No function
}

/**
*  @brief
*    Call function
*/
void DynFunc::Call(const DynParams &cParams)
{
	// No function
}

/**
*  @brief
*    Call function
*/
void DynFunc::Call(const String &sParams)
{
	// No function
}

/**
*  @brief
*    Call function
*/
void DynFunc::Call(const XmlElement &cElement)
{
	// No function
}

/**
*  @brief
*    Clone function object
*/
DynFunc *DynFunc::Clone() const
{
	// No function
	return nullptr;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
DynFunc::DynFunc()
{
}

/**
*  @brief
*    Copy constructor
*/
DynFunc::DynFunc(const DynFunc &cDynFunc)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*
*/
DynFunc &DynFunc::operator =(const DynFunc &cDynFunc)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
