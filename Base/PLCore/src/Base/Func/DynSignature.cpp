/*********************************************************\
 *  File: DynSignature.cpp                               *
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
#include "PLCore/Base/Type/Type.h"
#include "PLCore/Base/Func/DynSignature.h"


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
DynSignature::DynSignature()
{
}

/**
*  @brief
*    Destructor
*/
DynSignature::~DynSignature()
{
}


//[-------------------------------------------------------]
//[ Public virtual DynSignature functions                 ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get signature as string
*/
String DynSignature::GetSignature() const
{
	// No parameters
	return "";
}

/**
*  @brief
*    Get the return type ID
*/
int DynSignature::GetReturnTypeID() const
{
	// No function
	return TypeInvalid;
}

/**
*  @brief
*    Return the number of parameters
*/
uint32 DynSignature::GetNumOfParameters() const
{
	// No function
	return 0;
}

/**
*  @brief
*    Get a parameter type ID
*/
int DynSignature::GetParameterTypeID(uint32 nIndex) const
{
	// No function
	return TypeInvalid;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
