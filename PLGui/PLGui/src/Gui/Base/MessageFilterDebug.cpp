/*********************************************************\
 *  File: MessageFilterDebug.cpp                         *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/System/System.h>
#include <PLGeneral/System/Console.h>
#include "PLGui/Gui/Base/GuiMessage.h"
#include "PLGui/Gui/Base/MessageFilterDebug.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MessageFilterDebug::MessageFilterDebug(EDebugMode nDebugMode) :
	m_nDebugMode(nDebugMode)
{
}

/**
*  @brief
*    Destructor
*/
MessageFilterDebug::~MessageFilterDebug()
{
}

/**
*  @brief
*    Get debug mode
*/
EDebugMode MessageFilterDebug::GetDebugMode() const
{
	// Return debug mode
	return m_nDebugMode;
}

/**
*  @brief
*    Set debug mode
*/
void MessageFilterDebug::SetDebugMode(EDebugMode nDebugMode)
{
	// Set debug mode
	m_nDebugMode = nDebugMode;
}


//[-------------------------------------------------------]
//[ Protected virtual MessageFilter functions             ]
//[-------------------------------------------------------]
void MessageFilterDebug::OnGuiMessage(const GuiMessage &cMessage)
{
	// Display anything at all?
	if (m_nDebugMode != DebugModeOff) {
		// Check if the message shall be displayed
		EMessageType nType	  = cMessage.GetType();
		bool		 bDisplay = false;
		if (m_nDebugMode == DebugModeAll) {
			// Display all messages
			bDisplay = true;
		} else if (m_nDebugMode == DebugModeFocus) {
			// Display all keyboard-focus related messages
			bDisplay = (nType == MessageOnGetFocus || nType == MessageOnLooseFocus);
		}

		// Display this message?
		if (bDisplay) {
			// Print message
			System::GetInstance()->GetConsole().Print(cMessage.ToString() + "\n");
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
