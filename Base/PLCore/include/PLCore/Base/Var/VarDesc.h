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
		PLCORE_API VarDesc(int nType, const String &sType, const String &sName, const String &sDescription, const String &sAnnotation);

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
		inline int GetTypeID() const;

		/**
		*  @brief
		*    Get type name
		*
		*  @return
		*    Type name
		*/
		inline String GetTypeName() const;


	//[-------------------------------------------------------]
	//[ Public virtual VarDesc functions                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get default value as string
		*
		*  @return
		*    Default value as string
		*/
		PLCORE_API virtual String GetDefault() const;

		/**
		*  @brief
		*    Get attribute
		*
		*  @param[in] cObject
		*    Object to return the attribute pointer from
		*
		*  @return
		*    Pointer to var (can be a null pointer, do not destroy the returned instance)
		*/
		PLCORE_API virtual DynVar *GetAttribute(const Object &cObject) const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		int		m_nType;	/**< Type ID */
		String	m_sType;	/**< Type name */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Base/Var/VarDesc.inl"


#endif // __PLCORE_VARDESC_H__