/*********************************************************\
 *  File: MemberDesc.h                                   *
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


#ifndef __PLCORE_MEMBERDESC_H__
#define __PLCORE_MEMBERDESC_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/String.h"
#include "PLCore/PLCoreDefinitions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class ClassReal;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Member descriptor
*
*  @remarks
*    This class contains a descriptor for a member of a class, such as a variable
*    or a method. It consists of information equal for all member types (name, description, etc.).
*/
class MemberDesc {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nMemberType
		*    Member type
		*  @param[in] sName
		*    Var name
		*  @param[in] sDescription
		*    Var description
		*  @param[in] sAnnotation
		*    Var annotation
		*/
		PLCORE_API MemberDesc(EMemberType nMemberType, const String &sName, const String &sDescription, const String &sAnnotation);

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~MemberDesc();

		/**
		*  @brief
		*    Get member type
		*
		*  @return
		*    Member type
		*/
		inline EMemberType GetMemberType() const;

		/**
		*  @brief
		*    Get name
		*
		*  @return
		*    Name
		*/
		inline String GetName() const;

		/**
		*  @brief
		*    Get description
		*
		*  @return
		*    Description
		*/
		inline String GetDescription() const;

		/**
		*  @brief
		*    Get annotation
		*
		*  @return
		*    Annotation
		*/
		inline String GetAnnotation() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Register member at class
		*
		*  @param[in] pClass
		*    Pointer to class (must be valid!)
		*/
		PLCORE_API void Register(ClassReal *pClass);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		EMemberType	m_nMemberType;	/**< Member type */
		String		m_sName;		/**< Name */
		String		m_sDescription;	/**< Description */
		String		m_sAnnotation;	/**< Annotation */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Base/MemberDesc.inl"


#endif // __PLCORE_MEMBERDESC_H__
