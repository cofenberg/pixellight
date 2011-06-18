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
*    Returns the current Lua function parameters on the Lua stack as string
*/
String RTTIObjectMethodPointer::GetLuaFunctionParametersAsString(Script &cScript, DynSignature &cDynSignature, bool bIsMethod, Array<String> &lstTempStrings)
{
	// Get the Lua state
	lua_State *pLuaState = cScript.GetLuaState();

	// Get the number of arguments Lua gave to us
	String sParams;
	const int nOffset				= bIsMethod ? 2 : 0;
	const int nNumOfArguments		= lua_gettop(pLuaState) - nOffset;
	const int nIndexOfFirstArgument	= 1+nOffset;
	for (int i=nIndexOfFirstArgument; i<=nOffset+nNumOfArguments; i++) {
		const uint32 nParameterIndex = i - nIndexOfFirstArgument;
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

			// Is it string?
			} else if (lua_isstring(pLuaState, -1)) {
				sValue = lua_tolstring(pLuaState, i, nullptr);

				// Strings are somewhat of a special case... see method documentation for details
				const int nTypeID = cDynSignature.GetParameterTypeID(nParameterIndex);
				switch (nTypeID) {
					case TypeRef:
						// Give the RTTI method a reference to the temporaty string
						sValue = Type<String&>::ConvertToString(lstTempStrings.Add(sValue));
						break;

					case TypePtr:
						// Give the RTTI method a pointer to the temporaty string
						sValue = Type<String*>::ConvertToString(&lstTempStrings.Add(sValue));
						break;
				}

			// ...
			} else {
				// If not just let Lua decide how to convert the stuff into a string... but only if it's no object pointer!
				sValue = (cDynSignature.GetParameterTypeID(nParameterIndex) == Type<Object*>::TypeID) ? "0" : lua_tolstring(pLuaState, i, nullptr);
			}
		}

		// Add the Lua argument to the parameter string
		sParams += String("Param") + (nParameterIndex) + "=\"" + sValue + "\" ";
	}

	// Return the parameters string
	return sParams;
}

/**
*  @brief
*    Calls the current Lua stack dynamic function
*/
int RTTIObjectMethodPointer::CallDynFunc(Script &cScript, DynFunc &cDynFunc, bool bIsMethod)
{
	// Get the Lua state
	lua_State *pLuaState = cScript.GetLuaState();

	// Get the current Lua function parameters on the Lua stack as string
	Array<String> lstTempStrings;
	const String sParams = GetLuaFunctionParametersAsString(cScript, cDynFunc, bIsMethod, lstTempStrings);

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
			case TypeRef:
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
RTTIObjectMethodPointer::RTTIObjectMethodPointer(Script &cScript, Object *pRTTIObject, DynFuncPtr pDynFunc) : RTTIObjectPointer(cScript, pRTTIObject, TypeObjectMethodPointer),
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

/**
*  @brief
*    Returns the pointer to the RTTI object method to wrap
*/
DynFuncPtr RTTIObjectMethodPointer::GetDynFuncPtr() const
{
	return m_pDynFunc;
}


//[-------------------------------------------------------]
//[ Protected virtual LuaUserData functions               ]
//[-------------------------------------------------------]
int RTTIObjectMethodPointer::IndexMetamethod(lua_State *pLuaState)
{
	// Error! A method can't be called like an object...
	// [TODO] Write an error message into the log? (with current script line etc.)

	// Error!
	return 0;
}

int RTTIObjectMethodPointer::NewIndexMetamethod(lua_State *pLuaState)
{
	// Error! A method can't be called like an object...
	// [TODO] Write an error message into the log? (with current script line etc.)

	// Done
	return 0;
}

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
