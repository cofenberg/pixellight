/*********************************************************\
 *  File: VarDesc.h                                      *
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


#ifndef __PLCORE_VARDESC_H__
#define __PLCORE_VARDESC_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include "PLCore/Base/MemberDesc.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Object;
class DynVar;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Variable descriptor
*
*  @remarks
*    This class contains a descriptor for a variable and consists of information
*    belonging to a specific variable, such as it's name, type and description.
*/
class VarDesc : public MemberDesc {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nType
		*    Type ID
		*  @param[in] sType
		*    Type name
		*  @param[in] sName
		*    Var name
		*  @param[in] sDescription
		*    Var description
		*  @param[in] sAnnotation
		*    Var annotation
		*/
		PLCORE_API VarDesc(int nType, const PLGeneral::String &sType, const PLGeneral::String &sName, const PLGeneral::String &sDescription, const PLGeneral::String &sAnnotation);

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~VarDesc();

		/**
		*  @brief
		*    Initialize instance
		*
		*  @remarks
		*    This method is just here to ensure, that the compiler will actually create static instances
		*/
		PLCORE_API void Dummy();

		/**
		*  @brief
		*    Get type ID
		*
		*  @return
		*    Type ID
		*/
		PLCORE_API int GetTypeID() const;

		/**
		*  @brief
		*    Get type name
		*
		*  @return
		*    Type name
		*/
		PLCORE_API PLGeneral::String GetTypeName() const;


	//[-------------------------------------------------------]
	//[ Public virtual VarDesc functions                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get attribute
		*
		*  @return
		*    Pointer to var (can be a null pointer)
		*/
		PLCORE_API virtual DynVar *GetAttribute(const Object *pObject) const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		int					m_nType;	/**< Type ID */
		PLGeneral::String	m_sType;	/**< Type name */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_VARDESC_H__
