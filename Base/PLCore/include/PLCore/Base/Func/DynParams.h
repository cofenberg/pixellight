/*********************************************************\
 *  File: DynParams.h                                    *
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


#ifndef __PLCORE_DYNPARAMS_H__
#define __PLCORE_DYNPARAMS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Func/DynSignature.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Virtual base class for parameters
*
*  @remarks
*    This is the virtual base class to pass parameters from and to functions.
*/
class DynParams : public DynSignature {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API DynParams();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~DynParams();


	//[-------------------------------------------------------]
	//[ Public virtual DynParams functions                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get a pointer to the return value
		*
		*  @return
		*    Pointer to the return value, null pointer if there's no return value
		*
		*  @note
		*    - Whenever possible, don't use this method, use typed access instead
		*    - If you really need to use this generic method, use it at least very carefully and always use "GetReturnTypeID()" to check for the real type
		*/
		PLCORE_API virtual void *GetPointerToReturnValue();

		/**
		*  @brief
		*    Get a pointer to a parameter value
		*
		*  @param[in] nIndex
		*    Index of the parameter to return a pointer to the value from
		*
		*  @return
		*    Pointer to the parameter, null pointer on error
		*
		*  @note
		*    - Whenever possible, don't use this method, use typed access instead
		*    - If you really need to use this generic method, use it at least very carefully and always use "GetParameterTypeID()" to check for the real type
		*/
		PLCORE_API virtual void *GetPointerToParameterValue(uint32 nIndex);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_DYNPARAMS_H__
