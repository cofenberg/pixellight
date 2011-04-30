/*********************************************************\
 *  File: DynFunc.h                                      *
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


#ifndef __PLCORE_DYNFUNC_H__
#define __PLCORE_DYNFUNC_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include "PLCore/PLCore.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class XmlElement;
}
namespace PLCore {
	class DynParams;
	class FuncDesc;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Virtual base class for function objects (functoids)
*
*  @remarks
*    This is the virtual base class to access functions and function objects dynamically.
*    It is a virtual interface that allows you to call a function or function like object
*    regardless of it's actual type (e.g. static function, method of an object or function object).
*/
class DynFunc {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~DynFunc();


	//[-------------------------------------------------------]
	//[ Public virtual DynFunc functions                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get function descriptor
		*
		*  @return
		*    Descriptor (can be a null pointer)
		*/
		PLCORE_API virtual const FuncDesc *GetDesc() const;

		/**
		*  @brief
		*    Get signature as string
		*
		*  @return
		*    Signature as string
		*/
		PLCORE_API virtual PLGeneral::String GetSignature() const;

		/**
		*  @brief
		*    Call function
		*
		*  @param[in] cParams
		*    Parameters
		*/
		PLCORE_API virtual void Call(DynParams &cParams);

		/**
		*  @brief
		*    Call function
		*
		*  @param[in] cParams
		*    Parameters
		*/
		PLCORE_API virtual void Call(const DynParams &cParams);

		/**
		*  @brief
		*    Call function
		*
		*  @param[in] sParams
		*    Parameters as string
		*/
		PLCORE_API virtual void Call(const PLGeneral::String &sParams);

		/**
		*  @brief
		*    Call function
		*
		*  @param[in] cElement
		*    Parameters as XML
		*/
		PLCORE_API virtual void Call(const PLGeneral::XmlElement &cElement);

		/**
		*  @brief
		*    Clone function object
		*
		*  @return
		*    Copy of this functoid (can be a null pointer!)
		*/
		PLCORE_API virtual DynFunc *Clone() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCORE_API DynFunc();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cDynFunc
		*    Source to copy from
		*/
		PLCORE_API DynFunc(const DynFunc &cDynFunc);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cDynFunc
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		PLCORE_API DynFunc &operator =(const DynFunc &cDynFunc);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_DYNFUNC_H__
