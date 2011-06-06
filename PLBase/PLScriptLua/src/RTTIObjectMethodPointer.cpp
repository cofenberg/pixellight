/*********************************************************\
 *  File: RTTIObjectMethodPointer.cpp                    *
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
#include "PLScriptLua/RTTIObjectMethodPointer.h"


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
*    Calls the current Lua stack dynamic function
*/
int RTTIObjectMethodPointer::CallDynFunc(Script &cScript, DynFunc &cDynFunc, bool bIsMethod)
{
	// Get the Lua state
	lua_State *pLuaState = cScript.GetLuaState();

	// Get the number of arguments Lua gave to us
	String sParams;
	const int nOffset = bIsMethod ? 2 : 0;
	const int nNumOfArguments = lua_gettop(pLuaState) - nOffset;
	for (int i=1+nOffset; i<=nOffset+nNumOfArguments; i++) {
		String sValue;

		// Is it user data?
		if (lua_isuserdata(pLuaState, i)) {
			// Get user data from the Lua stack without removing it
			Object *pObject = nullptr;
			LuaUserData *pLuaUserData = GetUserDataFromLuaStack(pLuaState, i);
			if (pLuaUserData) {
				// [TODO] Do any type tests in here?
				pObject = reinterpret_cast<RTTIObjectPointer*>(pLuaUserData)->GetObject();
			}

			// Convert the object pointer to a string
			sValue = pObject ? Type<Object*>::ConvertToString(pObject) : "0";
		} else {
			// Is it nil?
			if (lua_isnil(pLuaState, i)) {
				sValue = "0";

			// Is it boolean?
			} else if (lua_isboolean(pLuaState, -1)) {
				sValue = (lua_toboolean(pLuaState, -1) != 0) ? "1" : "0";

			// ...
			} else {
				// If not just let Lua decide how to convert the stuff into a string... but only if it's no object pointer!
				sValue = (cDynFunc.GetParameterTypeID(nNumOfArguments-1) == Type<Object*>::TypeID) ? "0" : lua_tolstring(pLuaState, i, nullptr);
			}
		}

		// Add the Lua argument to the parameter string
		sParams += String("Param") + (i-1+nOffset) + "=\"" + sValue + "\" ";
	}

	// Get the global function
	const String sReturn = cDynFunc.CallWithReturn(sParams);
	if (sReturn.GetLength()) {
		// Process the functor return
		switch (cDynFunc.GetReturnTypeID()) {
			case TypeVoid:																								return 0;	// The function returns nothing
			case TypeBool:		lua_pushboolean(pLuaState, sReturn.GetBool());											break;
			case TypeDouble:	lua_pushnumber (pLuaState, sReturn.GetDouble());										break;
			case TypeFloat:		lua_pushnumber (pLuaState, sReturn.GetFloat());											break;
			case TypeInt:		lua_pushinteger(pLuaState, sReturn.GetInt());											break;
			case TypeInt16:		lua_pushinteger(pLuaState, sReturn.GetInt());											break;
			case TypeInt32:		lua_pushinteger(pLuaState, sReturn.GetInt());											break;
			case TypeInt64:		lua_pushinteger(pLuaState, sReturn.GetInt());											break;	// [TODO] TypeInt64 is currently handled just as long
			case TypeInt8:		lua_pushinteger(pLuaState, sReturn.GetInt());											break;
			case TypeString:	lua_pushstring (pLuaState, sReturn);													break;
			case TypeUInt16:	lua_pushinteger(pLuaState, sReturn.GetUInt16());										break;
			case TypeUInt32:	lua_pushinteger(pLuaState, sReturn.GetUInt32());										break;
			case TypeUInt64:	lua_pushinteger(pLuaState, static_cast<lua_Integer>(sReturn.GetUInt64()));				break;	// [TODO] TypeUInt64 is currently handled just as long
			case TypeUInt8:		lua_pushinteger(pLuaState, sReturn.GetUInt8());											break;

			// [HACK] Currently, classes derived from "PLCore::Object" are just recognized as type "void*"... but "PLCore::Object*" type would be perfect
			case TypePtr:
			case TypeObjectPtr:
				RTTIObjectPointer::LuaStackPush(cScript, Type<Object*>::ConvertFromString(sReturn));
				break;

			default:			lua_pushstring (pLuaState, sReturn);													break;	// Unkown type
		}

		// The function returns one argument
		return 1;
	} else {
		// The function returns nothing
		return 0;
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RTTIObjectMethodPointer::RTTIObjectMethodPointer(Script &cScript, Object *pRTTIObject, DynFuncPtr pDynFunc) : RTTIObjectPointer(cScript, pRTTIObject),
	m_pDynFunc(pDynFunc)
{
}

/**
*  @brief
*    Destructor
*/
RTTIObjectMethodPointer::~RTTIObjectMethodPointer()
{
}


//[-------------------------------------------------------]
//[ Protected virtual LuaUserData functions               ]
//[-------------------------------------------------------]
void RTTIObjectMethodPointer::CallMetamethod(lua_State *pLuaState)
{
	// Is there a RTTI object and a RTTI object method?
	if (m_pRTTIObject && m_pDynFunc) {
		// Call the dynamic function
		CallDynFunc(*m_pScript, *m_pDynFunc, true);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua
