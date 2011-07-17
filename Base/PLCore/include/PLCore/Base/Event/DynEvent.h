/*********************************************************\
 *  File: DynEvent.h                                     *
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


#ifndef __PLCORE_DYNEVENT_H__
#define __PLCORE_DYNEVENT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/SimpleList.h>
#include "PLCore/Base/Func/Signature.h"
#include "PLCore/Base/Func/DynSignature.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class XmlElement;
}
namespace PLCore {
	class EventDesc;
	class DynParams;
	class DynEventHandler;
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
*    Virtual base class for events
*
*  @remarks
*    This is the virtual base class to access events dynamically.
*
*  @note
*    - Implementation of the observer design pattern (this class is the subject/observable, the source)
*/
class DynEvent : public DynSignature {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		typedef Signature<void, DynParams&, void*>::FuncType FUNC;


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
		*  @param[in] cHandler
		*    Event handler
		*/
		PLCORE_API void Connect(DynEventHandler &cHandler);

		/**
		*  @brief
		*    Disconnect event handler from the event
		*
		*  @param[in] cHandler
		*    Event handler
		*/
		PLCORE_API void Disconnect(DynEventHandler &cHandler);

		/**
		*  @brief
		*    Return the number of connections
		*
		*  @return
		*    The number of connections
		*
		*  @note
		*    - Don't use this method within performance critical situations because due internal
		*      implementation, this request has a linear, not constant runtime!
		*/
		PLCORE_API PLGeneral::uint32 GetNumOfConnects() const;


	//[-------------------------------------------------------]
	//[ Public virtual DynEvent functions                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get event descriptor
		*
		*  @return
		*    Descriptor (can be a null pointer)
		*/
		PLCORE_API virtual const EventDesc *GetDesc() const;

		/**
		*  @brief
		*    Create a generic event handler which is compatible with this dynamic event
		*
		*  @param[in] pFunc
		*    Function to be called by the dynamic event handler
		*  @param[in] pUserData
		*    Optional pointer to user data to pass on to the given generic function when the event was emitted, can be a null pointer
		*
		*  @return
		*    The generic event handler which is compatible with this dynamic event, null pointer on error (delete the created instance if you no longer need it)
		*
		*  @note
		*    - This method just creates an instance of the generic event handler and does not automatically connect it with this dynamic event
		*    - Use typed instead of generic event handlers whenever possible, this method only exists for situations were no type information
		*      is available at compile time
		*/
		PLCORE_API virtual DynEventHandler *CreateGenericEventHandler(const FUNC &pFunc, void *pUserData = nullptr) const;

		/**
		*  @brief
		*    Emit event
		*
		*  @param[in] cParams
		*    Parameters
		*/
		PLCORE_API virtual void Emit(DynParams &cParams) const;

		/**
		*  @brief
		*    Emit event
		*
		*  @param[in] cParams
		*    Parameters
		*/
		PLCORE_API virtual void Emit(const DynParams &cParams) const;

		/**
		*  @brief
		*    Emit event
		*
		*  @param[in] sParams
		*    Parameters as string
		*/
		PLCORE_API virtual void Emit(const PLGeneral::String &sParams) const;

		/**
		*  @brief
		*    Emit event
		*
		*  @param[in] cElement
		*    Parameters as XML
		*/
		PLCORE_API virtual void Emit(const PLGeneral::XmlElement &cElement) const;


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
