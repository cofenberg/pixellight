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
	class DynEventHandler;
	class EventDesc;
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
		*    Get signature as string
		*
		*  @return
		*    Signature as string
		*/
		PLCORE_API virtual PLGeneral::String GetSignature() const;

		/**
		*  @brief
		*    Return the number of parameters
		*
		*  @return
		*    Number of parameters
		*/
		PLCORE_API virtual PLGeneral::uint32 GetNumOfParameters() const;

		/**
		*  @brief
		*    Get a parameter type ID
		*
		*  @param[in] nIndex
		*    Index of the parameter to return the type ID from
		*
		*  @return
		*    Parameter type ID (e.g. "TypeInt" for "void(int)"), "TypeInvalid" on error
		*/
		PLCORE_API virtual int GetParameterTypeID(PLGeneral::uint32 nIndex) const;

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
