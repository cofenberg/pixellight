/*********************************************************\
 *  File: EventDesc.h                                    *
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


#ifndef __PLCORE_EVENTDESC_H__
#define __PLCORE_EVENTDESC_H__
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
class DynEvent;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Event descriptor
*
*  @remarks
*    This class contains a descriptor for an event and consists of information
*    belonging to a specific event, such as it's name and signature.
*/
class EventDesc : public MemberDesc {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sSignature
		*    Function signature
		*  @param[in] sName
		*    Function name
		*  @param[in] sDescription
		*    Function description
		*  @param[in] sAnnotation
		*    Function annotation
		*/
		PLCORE_API EventDesc(const PLGeneral::String &sSignature, const PLGeneral::String &sName, const PLGeneral::String &sDescription, const PLGeneral::String &sAnnotation);

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~EventDesc();

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


	//[-------------------------------------------------------]
	//[ Public virtual FuncDesc functions                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get signal
		*
		*  @return
		*    Pointer to signal (can be a null pointer)
		*/
		PLCORE_API virtual DynEvent *GetSignal(const Object *pObject) const;


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


#endif // __PLCORE_EVENTDESC_H__
