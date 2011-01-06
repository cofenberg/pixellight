/*********************************************************\
 *  File: ConstructorDesc.h                              *
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


#ifndef __PLCORE_CONSTRUCTORDESC_H__
#define __PLCORE_CONSTRUCTORDESC_H__
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
class DynFunc;
class DynParams;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor descriptor
*
*  @remarks
*    This class contains a descriptor for a specific constructor of a class
*/
class ConstructorDesc : public MemberDesc {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sSignature
		*    Signature
		*  @param[in] sName
		*    Name
		*  @param[in] sDescription
		*    Description
		*  @param[in] sAnnotation
		*    Annotation
		*/
		PLCORE_API ConstructorDesc(const PLGeneral::String &sSignature, const PLGeneral::String &sName, const PLGeneral::String &sDescription, const PLGeneral::String &sAnnotation);

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~ConstructorDesc();

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
		*    Get signature
		*
		*  @return
		*    Signature
		*/
		PLCORE_API PLGeneral::String GetSignature() const;

		/**
		*  @brief
		*    Check if this is a default constructor
		*
		*  @return
		*    'true' if the constructor is a default constructor, else 'false'
		*/
		PLCORE_API bool IsDefaultConstructor() const;


	//[-------------------------------------------------------]
	//[ Public virtual ConstructorDesc functions              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get constructor
		*
		*  @return
		*    Pointer to constructor (can be a null pointer)
		*/
		PLCORE_API virtual DynFunc *GetConstructor() const;

		/**
		*  @brief
		*    Create object
		*
		*  @return
		*    Pointer to new object (can be a null pointer)
		*/
		PLCORE_API virtual Object *Create(const DynParams &cParams);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::String m_sSignature;		/**< Signature */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CONSTRUCTORDESC_H__
