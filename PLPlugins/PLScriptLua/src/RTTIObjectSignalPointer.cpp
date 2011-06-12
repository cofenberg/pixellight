/*********************************************************\
 *  File: RTTIObjectSignalPointer.cpp                    *
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
#include "PLScriptLua/Script.h"
#include "PLScriptLua/RTTIObjectSignalMethodPointer.h"
#include "PLScriptLua/RTTIObjectSignalPointer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLScriptLua {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RTTIObjectSignalPointer::RTTIObjectSignalPointer(Script &cScript, Object *pRTTIObject, DynEvent *pDynEvent, EType nType) : RTTIObjectPointer(cScript, pRTTIObject, nType),
	m_pDynEvent(pDynEvent)
{
}

/**
*  @brief
*    Destructor
*/
RTTIObjectSignalPointer::~RTTIObjectSignalPointer()
{
}

/**
*  @brief
*    Returns the pointer to the RTTI object signal to wrap
*/
DynEvent *RTTIObjectSignalPointer::GetDynEvent() const
{
	return m_pDynEvent;
}


//[-------------------------------------------------------]
//[ Protected virtual LuaUserData functions               ]
//[-------------------------------------------------------]
int RTTIObjectSignalPointer::IndexMetamethod(lua_State *pLuaState)
{
	// This method deals with build in signal methods

	// There must be a string Lua stack (first argument is a user data)
	if (lua_isstring(pLuaState, 2)) {
		// Figure out the build in signal method to be called
		const RTTIObjectSignalMethodPointer::EMethod nMethod = RTTIObjectSignalMethodPointer::StringToMethod(lua_tolstring(pLuaState, 2, nullptr));
		if (nMethod != RTTIObjectSignalMethodPointer::MethodUnknown) {
			// It's a build in signal method... just put another user data instance on the Lua stack...
			// The destruction of the new RTTIObjectSignalMethodPointer instance is done by the Lua garbage collector
			new RTTIObjectSignalMethodPointer(*m_pScript, m_pRTTIObject, m_pDynEvent, nMethod);

			// Done
			return 1;
		} else {
			// Error, this is no valid build in signal method!

			// [TODO] Write an error message into the log? (with current script line etc.)
		}
	}

	// [TODO] Write an error message into the log? (with current script line etc.)

	// Error!
	return 0;
}

int RTTIObjectSignalPointer::NewIndexMetamethod(lua_State *pLuaState)
{
	// Error! A signal can't be called like an object...
	// [TODO] Write an error message into the log? (with current script line etc.)

	// Done
	return 0;
}

void RTTIObjectSignalPointer::CallMetamethod(lua_State *pLuaState)
{
	// Is there a RTTI object and a RTTI object signal?
	if (m_pRTTIObject && m_pDynEvent) {
		// Get the number of arguments Lua gave to us
		String sParams;
		const int nNumOfArguments = lua_gettop(pLuaState) - 2;
		for (int i=3; i<=2+nNumOfArguments; i++)
			sParams += String("Param") + (i-3) + "=\"" + lua_tolstring(pLuaState, i, nullptr) + "\" ";

		// Emit the RTTI object signal
		m_pDynEvent->Emit(sParams);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua
