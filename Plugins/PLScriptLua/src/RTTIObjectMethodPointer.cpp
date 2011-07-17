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
	uint32 nParameterIndex = 0;
	const int nOffset				= bIsMethod ? 2 : 0;
	const int nNumOfArguments		= lua_gettop(pLuaState) - nOffset;
	const int nIndexOfFirstArgument	= 1+nOffset;
	for (int i=nIndexOfFirstArgument; i<=nOffset+nNumOfArguments; i++, nParameterIndex++) {
		const String sPrefix = String("Param") + nParameterIndex;

		// Is it user data?
		if (lua_isuserdata(pLuaState, i)) {
			// Get user data from the Lua stack without removing it
			Object *pObject = nullptr;
			LuaUserData *pLuaUserData = GetUserDataFromLuaStack(pLuaState, i);
			if (pLuaUserData) {
				// [TODO] Do any type tests in here?
				pObject = reinterpret_cast<RTTIObjectPointer*>(pLuaUserData)->GetObject();
			}

			// Add the Lua argument to the parameter string
			if (pObject)
				sParams += sPrefix + '=' + Type<Object*>::ConvertToString(pObject) + ' ';
			else
				sParams += sPrefix + "=0 ";

		// Is it nil?
		} else if (lua_isnil(pLuaState, i)) {
			// Add the Lua argument to the parameter string
			sParams += sPrefix + "=0 ";

		// Is it boolean?
		} else if (lua_isboolean(pLuaState, -1)) {
			// Add the Lua argument to the parameter string
			sParams += sPrefix + ((lua_toboolean(pLuaState, -1) != 0) ? "=1 " : "=0 ");

		// Is it string?
		} else if (lua_isstring(pLuaState, -1)) {
			// Strings are somewhat of a special case... see method documentation for details
			const int nTypeID = cDynSignature.GetParameterTypeID(nParameterIndex);
			switch (nTypeID) {
				case TypeRef:
					// Give the RTTI method a reference to the temporaty string and add the Lua argument to the parameter string
					sParams += sPrefix + '=' + Type<String&>::ConvertToString(lstTempStrings.Add(lua_tolstring(pLuaState, i, nullptr))) + ' ';
					break;

				case TypePtr:
					// Give the RTTI method a pointer to the temporaty string and add the Lua argument to the parameter string
					sParams += sPrefix + '=' + Type<String*>::ConvertToString(&lstTempStrings.Add(lua_tolstring(pLuaState, i, nullptr))) + ' ';
					break;

				default:
				{
					// It's a blank string, look out with the used quotation mark!
					// If the string content is "Name="Bob"" the resulting parameter string will be Param0="Name="Bob"" and the
					// parser will have troubles with it and will take "Name=" instead of "Name="Bob"" for the value of "Param0"

					// Get the string
					const String sValue = lua_tolstring(pLuaState, i, nullptr);

					// Check for " within the string
					if (sValue.IndexOf('\"') > -1)
						sParams += sPrefix + "='" + sValue + "' ";		// Use ' as quotation mark
					else
						sParams += sPrefix + "=\"" + sValue + "\" ";	// Use " as quotation mark
					break;
				}
			}

		// ...
		} else {
			// If not just let Lua decide how to convert the stuff into a string... but only if it's no object pointer!

			// Add the Lua argument to the parameter string
			if ((cDynSignature.GetParameterTypeID(nParameterIndex) == Type<Object*>::TypeID))
				sParams += sPrefix + "=0 ";
			else
				sParams += sPrefix + "=\"" + lua_tolstring(pLuaState, i, nullptr) + "\" ";
		}
	}

	// Does the RTTI signature demand more parameters as the script programmer provided?
	if (nParameterIndex < cDynSignature.GetNumOfParameters()) {
		// Add the missing parameters by using an empty string
		for (; nParameterIndex<cDynSignature.GetNumOfParameters(); nParameterIndex++) {
			String sValue = "";

			// Strings are somewhat of a special case... see method documentation for details
			// In here, TypePtr is not interesting because it automatically results in a null pointer
			if (cDynSignature.GetParameterTypeID(nParameterIndex) == TypeRef) {
				// Give the RTTI method a reference to the temporaty string
				sValue = Type<String&>::ConvertToString(lstTempStrings.Add(sValue));
			}

			// Add the dummy to the parameter string
			sParams += String("Param") + (nParameterIndex) + "=\"" + sValue + "\" ";
		}
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
