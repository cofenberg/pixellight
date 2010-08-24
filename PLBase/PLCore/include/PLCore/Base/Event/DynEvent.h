/*********************************************************\
 *  File: DynEvent.h                                     *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLCORE_DYNEVENT_H__
#define __PLCORE_DYNEVENT_H__
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
class DynEventHandler;
class EventDesc;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Virtual base class for events
*
*  @remarks
*    This is the virtual base class to access events dynamically.
*/
class DynEvent {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API DynEvent();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~DynEvent();

		/**
		*  @brief
		*    Connect event handler to the event
		*
		*  @param[in] pHandler
		*    Event handler
		*/
		PLCORE_API void Connect(DynEventHandler *pHandler);

		/**
		*  @brief
		*    Disconnect event handler from the event
		*
		*  @param[in] pHandler
		*    Event handler
		*/
		PLCORE_API void Disconnect(DynEventHandler *pHandler);


	//[-------------------------------------------------------]
	//[ Public virtual DynEvent functions                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get event descriptor
		*
		*  @return
		*    Descriptor (can be NULL)
		*/
		PLCORE_API virtual const EventDesc *GetDesc() const;

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
		*    Emit event
		*
		*  @param[in] cParams
		*    Parameters
		*/
		PLCORE_API virtual void Emit(const DynParams &cParams) const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::SimpleList<DynEventHandler*>	m_lstHandlers;	/**< List of event handlers */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_DYNEVENT_H__
