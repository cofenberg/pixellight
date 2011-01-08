/*********************************************************\
 *  File: DynEventHandler.cpp                            *
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
#include "PLCore/Base/Event/DynEvent.h"
#include "PLCore/Base/Event/DynEventHandler.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DynEventHandler::DynEventHandler()
{
}

/**
*  @brief
*    Destructor
*/
DynEventHandler::~DynEventHandler()
{
	// Disconnect all events
	while (!m_lstEvents.IsEmpty()) {
		m_lstEvents[0]->Disconnect(this);
	}
}


//[-------------------------------------------------------]
//[ Public virtual DynEventHandler functions              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get event handler descriptor
*/
const EventHandlerDesc *DynEventHandler::GetDesc() const
{
	// No descriptor by default
	return nullptr;
}

/**
*  @brief
*    Get signature as string
*/
String DynEventHandler::GetSignature() const
{
	// No function
	return "";
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
