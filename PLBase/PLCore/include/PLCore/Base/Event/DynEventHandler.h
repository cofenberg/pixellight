/*********************************************************\
 *  File: DynEventHandler.h                              *
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


#ifndef __PLCORE_DYNEVENTHANDLER_H__
#define __PLCORE_DYNEVENTHANDLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/SimpleList.h>
#include <PLGeneral/String/String.h>
#include "PLCore/PLCore.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class DynParams;
class DynEvent;
class EventHandlerDesc;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Virtual base class for event handlers
*
*  @remarks
*    This is the virtual base class to access event handlers dynamically.
*/
class DynEventHandler {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class DynEvent;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API DynEventHandler();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~DynEventHandler();


	//[-------------------------------------------------------]
	//[ Public virtual DynEventHandler functions              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get event handler descriptor
		*
		*  @return
		*    Descriptor (can be a null pointer)
		*/
		PLCORE_API virtual const EventHandlerDesc *GetDesc() const;

		/**
		*  @brief
		*    Get signature as string
		*
		*  @return
		*    Signature as string
		*/
		PLCORE_API virtual PLGeneral::String GetSignature() const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::SimpleList<DynEvent*> m_lstEvents;	/**< List of events */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_DYNEVENTHANDLER_H__
