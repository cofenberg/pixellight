/*********************************************************\
 *  File: RTTIObjectSignalMethodPointer.cpp              *
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
extern "C" {
	#include <Lua/lua.h>
}
#include <PLCore/Base/Object.h>
#include "PLScriptLua/RTTIObjectSlotPointer.h"
#include "PLScriptLua/RTTIObjectSignalMethodPointer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLScriptLua {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the build in method defined by a given string
*/
RTTIObjectSignalMethodPointer::EMethod RTTIObjectSignalMethodPointer::StringToMethod(const String &sMethod)
{
	if (sMethod == "Connect")
		return MethodConnect;
	else if (sMethod == "Disconnect")
		return MethodDisconnect;
	else
		return MethodUnknown;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RTTIObjectSignalMethodPointer::RTTIObjectSignalMethodPointer(Script &cScript, Object *pRTTIObject, DynEvent *pDynEvent, EMethod nMethod) : RTTIObjectSignalPointer(cScript, pRTTIObject, pDynEvent, TypeObjectSignalMethodPointer),
	m_nMethod(nMethod)
{
}

/**
*  @brief
*    Destructor
*/
RTTIObjectSignalMethodPointer::~RTTIObjectSignalMethodPointer()
{
}


//[-------------------------------------------------------]
//[ Protected virtual LuaUserData functions               ]
//[-------------------------------------------------------]
int RTTIObjectSignalMethodPointer::IndexMetamethod(lua_State *pLuaState)
{
	// Error! A signal method can't be called like an object...
	// [TODO] Write an error message into the log? (with current script line etc.)

	// Error!
	return 0;
}

int RTTIObjectSignalMethodPointer::NewIndexMetamethod(lua_State *pLuaState)
{
	// Error! A signal method can't be called like an object...
	// [TODO] Write an error message into the log? (with current script line etc.)

	// Done
	return 0;
}

void RTTIObjectSignalMethodPointer::CallMetamethod(lua_State *pLuaState)
{
	// Is there a RTTI object, a RTTI object signal and a valid build in signal method?
	if (m_pRTTIObject && m_pDynEvent && m_nMethod != MethodUnknown) {
		// Choose the method
		switch (m_nMethod) {
			// Connect method
			case MethodConnect:
			{
				// Get the valid RTTI slot to connect the RTTI signal with from the Lua stack without removing it
				DynEventHandler *pDynEventHandler = GetSlotFromLuaStack(pLuaState);
				if (pDynEventHandler) {
					// Connect the RTTI slot with the RTTI signal
					m_pDynEvent->Connect(pDynEventHandler);
				}
				break;
			}

			// Disconnect method
			case MethodDisconnect:
			{
				// Get the valid RTTI slot to disconnect the RTTI signal with from the Lua stack without removing it
				DynEventHandler *pDynEventHandler = GetSlotFromLuaStack(pLuaState);
				if (pDynEventHandler) {
					// Disconnect the RTTI slot with the RTTI signal
					m_pDynEvent->Disconnect(pDynEventHandler);
				}
				break;
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns a RTTI slot from the Lua stack without removing it
*/
DynEventHandler *RTTIObjectSignalMethodPointer::GetSlotFromLuaStack(lua_State *pLuaState)
{
	// There must be a user data on the Lua stack
	if (lua_isuserdata(pLuaState, 2)) {
		// Get user data from the Lua stack without removing it
		LuaUserData *pLuaUserData = GetUserDataFromLuaStack(pLuaState, 2);

		// Must be a slot
		if (pLuaUserData && pLuaUserData->GetType() == TypeObjectSlotPointer) {
			DynEventHandler *pDynEventHandler = reinterpret_cast<RTTIObjectSlotPointer*>(pLuaUserData)->GetDynEventHandler();
			if (pDynEventHandler) {
				// The signatures must match
				if (m_pDynEvent->GetSignature() == pDynEventHandler->GetSignature()) {
					// Finally, return the valid RTTI slot
					return pDynEventHandler;
				} else {
					// Error, RTTI signal/slot signature mismatch!

					// [TODO] Write an error message into the log? (with current script line etc.)
				}
			} else {
				// Error, there's no RTTI valid slot on the Lua stack!

				// [TODO] Write an error message into the log? (with current script line etc.)
			}
		} else {
			// Error, there's no RTTI slot on the Lua stack!

			// [TODO] Write an error message into the log? (with current script line etc.)
		}
	} else {
		// Error, there's no RTTI slot on the Lua stack!

		// [TODO] Write an error message into the log? (with current script line etc.)
	}

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua
