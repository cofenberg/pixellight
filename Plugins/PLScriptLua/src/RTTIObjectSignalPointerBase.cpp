/*********************************************************\
 *  File: RTTIObjectSignalPointerBase.cpp                *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLScriptLua/LuaContext.h"
#include "PLScriptLua/RTTIObjectMethodPointer.h"
#include "PLScriptLua/RTTIObjectSignalMethodPointer.h"
#include "PLScriptLua/RTTIObjectSignalPointerBase.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLScriptLua {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
RTTIObjectSignalPointerBase::~RTTIObjectSignalPointerBase()
{
}

/**
*  @brief
*    Returns the pointer to the RTTI object signal to wrap
*/
DynEvent *RTTIObjectSignalPointerBase::GetDynEvent() const
{
	return m_pDynEvent;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RTTIObjectSignalPointerBase::RTTIObjectSignalPointerBase(EType nType) : RTTIObjectPointerBase(nType),
	m_pDynEvent(nullptr)
{
}

/**
*  @brief
*    Initializes this instance
*/
void RTTIObjectSignalPointerBase::InitializeInstance(Script &cScript, Object *pRTTIObject, DynEvent *pDynEvent)
{
	// Call base implementation
	RTTIObjectPointerBase::InitializeInstance(cScript, pRTTIObject);

	// Set given data
	m_pDynEvent = pDynEvent;
}


//[-------------------------------------------------------]
//[ Protected virtual LuaUserData functions               ]
//[-------------------------------------------------------]
int RTTIObjectSignalPointerBase::IndexMetamethod(lua_State *pLuaState)
{
	// This method deals with build in signal methods

	// There must be a string Lua stack (first argument is a user data)
	if (lua_isstring(pLuaState, 2)) {
		// Figure out the build in signal method to be called
		const RTTIObjectSignalMethodPointer::EMethod nMethod = RTTIObjectSignalMethodPointer::StringToMethod(lua_tolstring(pLuaState, 2, nullptr));
		if (nMethod != RTTIObjectSignalMethodPointer::MethodUnknown) {
			// It's a build in signal method... just put another user data instance on the Lua stack...
			// The destruction of the new RTTIObjectSignalMethodPointer instance is done by the Lua garbage collector
			LuaContext::GetRTTIObjectSignalMethodPointer(*m_pScript, GetObject(), m_pDynEvent, nMethod);

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

int RTTIObjectSignalPointerBase::NewIndexMetamethod(lua_State *pLuaState)
{
	// Error! A signal can't be called like an object...
	// [TODO] Write an error message into the log? (with current script line etc.)

	// Done
	return 0;
}

void RTTIObjectSignalPointerBase::CallMetamethod(lua_State *pLuaState)
{
	// Is there a RTTI object and a RTTI object signal?
	if (GetObject() && m_pDynEvent) {
		// Get the current Lua function parameters on the Lua stack as string
		Array<String> lstTempStrings;
		const String sParams = RTTIObjectMethodPointer::GetLuaFunctionParametersAsString(*m_pScript, *m_pDynEvent, true, lstTempStrings);

		// Emit the RTTI object signal
		m_pDynEvent->Emit(sParams);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua
