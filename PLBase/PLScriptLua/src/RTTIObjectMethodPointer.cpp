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
#include <PLGeneral/String/String.h>
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
int RTTIObjectMethodPointer::CallDynFunc(Script &cScript, DynFunc &cDynFunc)
{
	// Get the Lua state
	lua_State *pLuaState = cScript.GetLuaState();

	// Get the number of arguments Lua gave to us
	String sParams;
	const int nNumOfArguments = lua_gettop(pLuaState);
	for (int i=1; i<=nNumOfArguments; i++)
		sParams += String("Param") + (i-1) + "=\"" + lua_tolstring(pLuaState, i, nullptr) + "\" ";

	// Get the global function
	const String sReturn = cDynFunc.CallWithReturn(sParams);
	if (sReturn.GetLength()) {
		// Process the functor return
		switch (cDynFunc.GetReturnTypeID()) {
			case TypeVoid:																					return 0;	// The function returns nothing
			case TypeBool:		lua_pushboolean(pLuaState, sReturn.GetBool());								break;
			case TypeDouble:	lua_pushnumber (pLuaState, sReturn.GetDouble());							break;
			case TypeFloat:		lua_pushnumber (pLuaState, sReturn.GetFloat());								break;
			case TypeInt:		lua_pushinteger(pLuaState, sReturn.GetInt());								break;
			case TypeInt16:		lua_pushinteger(pLuaState, sReturn.GetInt());								break;
			case TypeInt32:		lua_pushinteger(pLuaState, sReturn.GetInt());								break;
			case TypeInt64:		lua_pushinteger(pLuaState, sReturn.GetInt());								break;	// [TODO] TypeInt64 is currently handled just as long
			case TypeInt8:		lua_pushinteger(pLuaState, sReturn.GetInt());								break;
			case TypeString:	lua_pushstring (pLuaState, sReturn);										break;
			case TypeUInt16:	lua_pushinteger(pLuaState, sReturn.GetUInt16());							break;
			case TypeUInt32:	lua_pushinteger(pLuaState, sReturn.GetUInt32());							break;
			case TypeUInt64:	lua_pushinteger(pLuaState, static_cast<lua_Integer>(sReturn.GetUInt64()));	break;	// [TODO] TypeUInt64 is currently handled just as long
			case TypeUInt8:		lua_pushinteger(pLuaState, sReturn.GetUInt8());								break;
			case TypeObjectPtr:	new RTTIObjectPointer(cScript, Type<Object*>::ConvertFromString(sReturn));	break;	// The destruction of the new RTTIObjectPointer instance is done by the Lua garbage collector
			default:			lua_pushstring (pLuaState, sReturn);										break;	// Unkown type
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
RTTIObjectMethodPointer::RTTIObjectMethodPointer(Script &cScript, Object *pRTTIObject, DynFunc *pDynFunc) : RTTIObjectPointer(cScript, pRTTIObject),
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
		CallDynFunc(*m_pScript, *m_pDynFunc);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua
