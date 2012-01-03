/*********************************************************\
 *  File: DynSignature.h                                 *
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


#ifndef __PLCORE_DYNSIGNATURE_H__
#define __PLCORE_DYNSIGNATURE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Virtual base class for signatures
*/
class DynSignature {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API DynSignature();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~DynSignature();


	//[-------------------------------------------------------]
	//[ Public virtual DynSignature functions                 ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get signature as string
		*
		*  @return
		*    Signature (e.g. "void(int,float)")
		*/
		PLCORE_API virtual String GetSignature() const;

		/**
		*  @brief
		*    Get the return type ID
		*
		*  @return
		*    Return type ID (e.g. "TypeNull" for "void()" or "TypeInt" for "int()"), "TypeInvalid" if there's no return type
		*/
		PLCORE_API virtual int GetReturnTypeID() const;

		/**
		*  @brief
		*    Return the number of parameters
		*
		*  @return
		*    Number of parameters
		*/
		PLCORE_API virtual uint32 GetNumOfParameters() const;

		/**
		*  @brief
		*    Get a parameter type ID
		*
		*  @param[in] nIndex
		*    Index of the parameter to return the type ID from
		*
		*  @return
		*    Parameter type ID (e.g. "TypeInt" for "void(int)"), "TypeInvalid" on error
		*/
		PLCORE_API virtual int GetParameterTypeID(uint32 nIndex) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_DYNSIGNATURE_H__
