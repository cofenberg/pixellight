/*********************************************************\
 *  File: ClassReal.h                                    *
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


#ifndef __PLCORE_CLASS_REAL_H__
#define __PLCORE_CLASS_REAL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/ClassImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Real 'Class' implementation
*
*  @note
*    - The class instance is created and destroyed automatically by the RTTI system (see "pl_class"-macro)
*/
class ClassReal : public ClassImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class MemberDesc;
	friend class ClassManager;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nModuleID
		*    ID of owner module
		*  @param[in] sName
		*    Name
		*  @param[in] sDescription
		*    Description
		*  @param[in] sNamespace
		*    Namespace
		*  @param[in] sBaseClass
		*    Base class
		*/
		PLCORE_API ClassReal(PLGeneral::uint32 nModuleID, const PLGeneral::String &sName, const PLGeneral::String &sDescription, const PLGeneral::String &sNamespace, const PLGeneral::String &sBaseClass);

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~ClassReal();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Add member
		*
		*  @param[in] pMemberDesc
		*    Member descriptor
		*/
		PLCORE_API void AddMember(MemberDesc *pMemberDesc);

		/**
		*  @brief
		*    Add property
		*
		*  @param[in] sName
		*    Property name
		*  @param[in] sValue
		*    Property value
		*/
		PLCORE_API void AddProperty(const PLGeneral::String &sName, const PLGeneral::String &sValue);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLCORE_CLASS_REAL_H__