/*********************************************************\
 *  File: DynEvent.cpp                                   *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Func/DynParams.h"
#include "PLCore/Base/Event/DynEventHandler.h"
#include "PLCore/Base/Event/DynEvent.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DynEvent::DynEvent()
{
}

/**
*  @brief
*    Destructor
*/
DynEvent::~DynEvent()
{
	// Force disconnection of event handlers
	const SimpleList<DynEventHandler*>::ListElement *pElement = m_lstHandlers.pFirstElement;
	while (pElement) {
		pElement->Data->m_lstEvents.Remove(this);
		pElement = pElement->pNextElement;
	}
}

/**
*  @brief
*    Connect event handler to the event
*/
void DynEvent::Connect(DynEventHandler &cHandler)
{
	// The handler must not be connected already
	if (!cHandler.m_lstEvents.IsElement(this)) {
		// Signatures must match!
		if (cHandler.GetSignature() == GetSignature()) {
			// Connect handler
			m_lstHandlers.Add(&cHandler);
			cHandler.m_lstEvents.Add(this);
		}
	}
}

/**
*  @brief
*    Disconnect a handler from the event
*/
void DynEvent::Disconnect(DynEventHandler &cHandler)
{
	// Disconnect handler
	if (m_lstHandlers.IsElement(&cHandler)) {
		m_lstHandlers.Remove(&cHandler);
		cHandler.m_lstEvents.Remove(this);
	}
}


//[-------------------------------------------------------]
//[ Public virtual DynEvent functions                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get event descriptor
*/
const EventDesc *DynEvent::GetDesc() const
{
	// No descriptor by default
	return nullptr;
}

/**
*  @brief
*    Create a generic event handler which is compatible with this dynamic event
*/
DynEventHandler *DynEvent::CreateGenericEventHandler(const FUNC &pFunc, void *pUserData) const
{
	// No function
	return nullptr;
}

/**
*  @brief
*    Call function
*/
void DynEvent::Emit(DynParams &cParams) const
{
	// No function
}

/**
*  @brief
*    Call function
*/
void DynEvent::Emit(const DynParams &cParams) const
{
	// No function
}

/**
*  @brief
*    Emit event
*/
void DynEvent::Emit(const String &sParams) const
{
	// No function
}

/**
*  @brief
*    Emit event
*/
void DynEvent::Emit(const XmlElement &cElement) const
{
	// No function
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
