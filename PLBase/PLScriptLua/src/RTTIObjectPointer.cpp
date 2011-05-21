/*********************************************************\
 *  File: RTTIObjectPointer.cpp                          *
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
#include <PLGeneral/String/String.h>
#include <PLCore/Base/Object.h>
#include "PLScriptLua/Script.h"
#include "PLScriptLua/RTTIObjectMethodPointer.h"
#include "PLScriptLua/RTTIObjectSignalPointer.h"
#include "PLScriptLua/RTTIObjectPointer.h"


// [TODO] Slot, Enum


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
RTTIObjectPointer::RTTIObjectPointer(Script &cScript, Object *pRTTIObject) : LuaUserData(cScript),
	m_pRTTIObject(pRTTIObject)
{
}

/**
*  @brief
*    Destructor
*/
RTTIObjectPointer::~RTTIObjectPointer()
{
}

/**
*  @brief
*    Returns the pointer to the RTTI object to wrap
*/
Object *RTTIObjectPointer::GetObject() const
{
	return m_pRTTIObject;
}


//[-------------------------------------------------------]
//[ Protected virtual LuaUserData functions               ]
//[-------------------------------------------------------]
int RTTIObjectPointer::IndexMetamethod(lua_State *pLuaState)
{
	// Valid RTTI object?
	if (m_pRTTIObject) {
		// Get the indexed name
		const String sName = lua_tostring(pLuaState, 2);

		// [TODO] Currently we can use within Lua the dot operator to access RTTI attributes and properties, but there may occure name conflicts...

		// Is it an attribute or a property?
		DynVar *pDynVar = m_pRTTIObject->GetAttribute(sName);
		if (pDynVar) {
			// It's an attribute
			switch (pDynVar->GetType().GetTypeID()) {
				case TypeBool:		lua_pushboolean(pLuaState, pDynVar->GetBool());								break;
				case TypeDouble:	lua_pushnumber (pLuaState, pDynVar->GetDouble());							break;
				case TypeFloat:		lua_pushnumber (pLuaState, pDynVar->GetFloat());							break;
				case TypeInt:		lua_pushinteger(pLuaState, pDynVar->GetInt());								break;
				case TypeInt16:		lua_pushinteger(pLuaState, pDynVar->GetInt());								break;
				case TypeInt32:		lua_pushinteger(pLuaState, pDynVar->GetInt());								break;
				case TypeInt64:		lua_pushinteger(pLuaState, pDynVar->GetInt());								break;	// [TODO] TypeInt64 is currently handled just as long
				case TypeInt8:		lua_pushinteger(pLuaState, pDynVar->GetInt());								break;
				case TypeString:	lua_pushstring (pLuaState, pDynVar->GetString());							break;
				case TypeUInt16:	lua_pushinteger(pLuaState, pDynVar->GetUInt16());							break;
				case TypeUInt32:	lua_pushinteger(pLuaState, pDynVar->GetUInt32());							break;
				case TypeUInt64:	lua_pushinteger(pLuaState, static_cast<lua_Integer>(pDynVar->GetUInt64()));	break;	// [TODO] TypeUInt64 is currently handled just as long
				case TypeUInt8:		lua_pushinteger(pLuaState, pDynVar->GetUInt8());							break;
				default:			lua_pushstring (pLuaState, pDynVar->GetString());							break;	// TypeVoid, TypeNull, TypeObjectPtr, -1
			}

			// Done
			return 1;
		} else {
			// Is it a property?
			const String sValue = m_pRTTIObject->GetClass()->GetProperties().Get(sName);
			if (sValue.GetLength()) {
				lua_pushstring(pLuaState, sValue);

				// Done
				return 1;
			} else {

				// [TODO] Currently methods and signals may have name conflicts because their usage is identical (but that's a general 'problem'...)

				// Is it a method?
				DynFunc *pDynFunc = m_pRTTIObject->GetMethod(sName);
				if (pDynFunc) {
					// It's a method... just put another user data instance on the Lua stack...
					// The destruction of the new RTTIObjectMethodPointer instance is done by the Lua garbage collector
					new RTTIObjectMethodPointer(*m_pScript, m_pRTTIObject, pDynFunc);

					// Done
					return 1;
				} else {
					// Is it a signal?
					DynEvent *pDynEvent = m_pRTTIObject->GetSignal(sName);
					if (pDynEvent) {
						// It's a signal... just put another user data instance on the Lua stack...
						// The destruction of the new RTTIObjectSignalPointer instance is done by the Lua garbage collector
						new RTTIObjectSignalPointer(*m_pScript, m_pRTTIObject, pDynEvent);

						// Done
						return 1;
					}
				}
			}
		}
	}

	// Error!
	return 0;
}

int RTTIObjectPointer::NewIndexMetamethod(lua_State *pLuaState)
{
	// Set the RTTI attribute
	m_pRTTIObject->SetAttribute(lua_tostring(pLuaState, 2), lua_tostring(pLuaState, 3));

	// Done
	return 0;
}

void RTTIObjectPointer::CGMetamethod(lua_State *pLuaState)
{
	// Nothing to do in here
}

void RTTIObjectPointer::CallMetamethod(lua_State *pLuaState)
{
	// Nothing to do in here
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua
