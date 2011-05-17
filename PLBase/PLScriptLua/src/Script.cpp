/*********************************************************\
 *  File: Script.cpp                                     *
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
	#include <Lua/lualib.h>
	#include <Lua/lauxlib.h>
}
#include <PLGeneral/Log/Log.h>
#include "PLScriptLua/LuaContext.h"
#include "PLScriptLua/RTTIObjectPointer.h"
#include "PLScriptLua/Script.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLScriptLua {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Script)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
Script::Script() :
	m_pLuaState(nullptr),
	m_bFunctionResult(false),
	m_nCurrentArgument(0)
{
	// Add a context reference
	LuaContext::AddContextReference();
}

/**
*  @brief
*    Destructor
*/
Script::~Script()
{
	// Clear the script
	Clear();

	// Remove all global functions
	RemoveAllGlobalFunctions();

	// Release a context reference
	LuaContext::ReleaseContextReference();
}

/**
*  @brief
*    Returns the Lua state
*/
lua_State *Script::GetLuaState() const
{
	return m_pLuaState;
}

/**
*  @brief
*    Writes the current Lua stack content into the log
*/
void Script::LuaStackDump()
{
	// Is there a Lua state?
	if (m_pLuaState) {
		// Get the number of elements on the Lua stack
		const int nNumOfStackElements = lua_gettop(m_pLuaState);

		// Write this number into the log
		LogOutput(Log::Info, String("Number of elements on the Lua stack: ") + nNumOfStackElements);

		// Iterate through the Lua stack
		for (int i=1; i<=nNumOfStackElements; i++) {
			const int nLuaType = lua_type(m_pLuaState, i);
			String sValue;
			switch (nLuaType) {
				case LUA_TNIL:
					sValue = "nil";
					break;

				case LUA_TNUMBER:
					sValue = lua_tonumber(m_pLuaState, i);
					break;

				case LUA_TBOOLEAN:
					sValue = lua_toboolean(m_pLuaState, i) ? "true" : "false";
					break;

				case LUA_TSTRING:
					sValue = lua_tostring(m_pLuaState, i);
					break;

				case LUA_TTABLE:
					sValue = "Table";
					break;

				case LUA_TFUNCTION:
					sValue = "Function";
					break;

				case LUA_TUSERDATA:
					sValue = "User data";
					break;

				case LUA_TTHREAD:
					sValue = "Thread";
					break;

				case LUA_TLIGHTUSERDATA:
					sValue = "Light user data";
					break;

				default:
					sValue = "?";
					break;
			}
			LogOutput(Log::Info, String("Lua stack element ") + (i-1) + ": \"" + sValue + "\" (Lua type name: \"" + lua_typename(m_pLuaState, nLuaType) + "\")");
		}
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLScript::Script functions             ]
//[-------------------------------------------------------]
bool Script::AddGlobalFunction(const String &sFunction, const DynFunc &cDynFunc, const String &sNamespace)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		// Error!
		return false;
	} else {
		// Add the global function
		GlobalFunction *psGlobalFunction = new GlobalFunction;
		psGlobalFunction->sFunction  = sFunction;
		psGlobalFunction->pDynFunc   = cDynFunc.Clone();
		psGlobalFunction->sNamespace = sNamespace;
		m_lstGlobalFunctions.Add(psGlobalFunction);

		// Done
		return true;
	}
}

bool Script::RemoveAllGlobalFunctions()
{
	// Is there a Lua state?
	if (m_pLuaState) {
		// Error!
		return false;
	} else {
		// Destroy the global functions
		for (uint32 i=0; i<m_lstGlobalFunctions.GetNumOfElements(); i++) {
			delete m_lstGlobalFunctions[i]->pDynFunc;
			delete m_lstGlobalFunctions[i];
		}
		m_lstGlobalFunctions.Clear();

		// Done
		return true;
	}
}

String Script::GetSourceCode() const
{
	return m_sSourceCode;
}

bool Script::SetSourceCode(const String &sSourceCode)
{
	// Clear the previous script
	Clear();

	// Backup the given source code
	m_sSourceCode = sSourceCode;

	// Is there source code?
	if (m_sSourceCode.GetLength()) {
		// Create the Lua state
		m_pLuaState = lua_open();
		if (m_pLuaState) {
			// [TODO] Check this
			// Setup Lua memory allocation
	//		lua_setallocf(m_pLuaState, Script::LuaMemoryAllocation, nullptr);

			// Open all standard Lua libraries into the given state
			luaL_openlibs(m_pLuaState);

			// Create the metatable for LuaUserData events
			LuaUserData::CreateMetatable(m_pLuaState);

			// Add the global functions
			for (uint32 i=0; i<m_lstGlobalFunctions.GetNumOfElements(); i++) {
				// Get the global function
				GlobalFunction *psGlobalFunction = m_lstGlobalFunctions[i];

				// Is the function within a namespace? (= Lua table)
				if (psGlobalFunction->sNamespace.GetLength()) {
					// Create a nested Lua table
					CreateNestedTable(m_pLuaState, psGlobalFunction->sNamespace);

					// Table key
					lua_pushstring(m_pLuaState, psGlobalFunction->sFunction);		// Push the function name onto the Lua stack

					// Table value: Store a pointer to the global function in the c-closure
					lua_pushlightuserdata(m_pLuaState, psGlobalFunction);			// Push a pointer to the global function onto the Lua stack
					lua_pushcclosure(m_pLuaState, &Script::LuaFunctionCallback, 1);	// Push the function pointer onto the Lua stack

					// This function pops both the key and the value from the stack
					lua_settable(m_pLuaState, -3);

					// Pop the table from the Lua stack
					lua_pop(m_pLuaState, 1);
				} else {
					// Store a pointer to the global function in the c-closure
					lua_pushlightuserdata(m_pLuaState, psGlobalFunction);
					lua_pushcclosure(m_pLuaState, &Script::LuaFunctionCallback, 1);
					lua_setglobal(m_pLuaState, psGlobalFunction->sFunction);
				}
			}

			// Load the script
			const int nResult = luaL_loadbuffer(m_pLuaState, sSourceCode, sSourceCode.GetLength(), Name.Get());
			if (!nResult && !lua_pcall(m_pLuaState, 0, 0, 0)) {
				// Done
				return true;
			} else {
				// Error!

				// Write a log mesage
				String sErrorDescription;
				switch (nResult) {
					case LUA_ERRSYNTAX:
						sErrorDescription = " (Syntax error during pre-compilation)";
						break;

					case LUA_ERRMEM:
						sErrorDescription = " (Memory allocation error)";
						break;
				}
				LogOutput(Log::Error, "Failed to compile the script" + sErrorDescription);

				// Report Lua errors
				ReportErrors();
			}
		}
	} else {
		// No script at all - done
		return true;
	}

	// Error!
	return false;
}

const Array<String> &Script::GetGlobalVariables()
{
	// Fill the list of all global variables right now?
	if (m_lstGlobalVariables.IsEmpty() && m_pLuaState) {
		// Push the global Lua table onto the stack
		lua_getglobal(m_pLuaState, "_G");
		if (lua_istable(m_pLuaState, -1)) {
			// Push the first key onto the Lua stack
			lua_pushnil(m_pLuaState);

			// Iterate through the Lua table
			while (lua_next(m_pLuaState, 1) != 0) {
				// Lua stack content: The 'key' is at index -2 and the 'value' at index -1

				// Check the 'key' type (at index -2) - must be a string
				if (lua_isstring(m_pLuaState, -2)) {
					// Check whether or not the 'value' (at index -1) is a global variable
					// (something like "_VERSION" is passing this test as well, but that's probably ok because it's just a Lua build in global variable)
					if (lua_isnumber(m_pLuaState, -1) || lua_isstring(m_pLuaState, -1)) {
						// Add the global variable to our list
						m_lstGlobalVariables.Add(lua_tostring(m_pLuaState, -2));
					}
				}

				// Next, please (removes 'value'; keeps 'key' for next iteration)
				lua_pop(m_pLuaState, 1);
			}
		}

		// Pop the global Lua table from the stack
		lua_pop(m_pLuaState, 1);
	}

	// Return a reference to the list of all global variables
	return m_lstGlobalVariables;
}

bool Script::IsGlobalVariable(const String &sName)
{
	bool bGlobalVariable = false;

	// Is there a Lua state?
	if (m_pLuaState) {
		// Push the global variable onto the Lua state stack
		lua_getglobal(m_pLuaState, sName);

		// Check the type of the global variable
		bGlobalVariable = (lua_isnumber(m_pLuaState, -1) || lua_isstring(m_pLuaState, -1));

		// Pop the global variable from the Lua state stack
		lua_pop(m_pLuaState, 1);
	}

	// Done
	return bGlobalVariable;
}

ETypeID Script::GetGlobalVariableType(const String &sName)
{
	ETypeID nType = TypeInvalid;

	// Is there a Lua state?
	if (m_pLuaState) {
		// Push the global variable onto the Lua state stack
		lua_getglobal(m_pLuaState, sName);

		// Check the type of the global variable
		if (lua_isboolean(m_pLuaState, -1))
			nType = TypeBool;
		else if (lua_isnumber(m_pLuaState, -1))
			nType = TypeDouble;
		else if (lua_isstring(m_pLuaState, -1))
			nType = TypeString;

		// Pop the global variable from the Lua state stack
		lua_pop(m_pLuaState, 1);
	}

	// Done
	return nType;
}

String Script::GetGlobalVariable(const String &sName)
{
	String sValue;

	// Is there a Lua state?
	if (m_pLuaState) {
		// Push the global variable onto the Lua state stack
		lua_getglobal(m_pLuaState, sName);

		// Get the value of the global variable as string
		sValue = lua_tostring(m_pLuaState, -1);

		// Pop the global variable from the Lua state stack
		lua_pop(m_pLuaState, 1);
	}

	// Done
	return sValue;
}

void Script::SetGlobalVariable(const String &sName, const String &sValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		// Get the type of the global variable (because we don't want to change it's type)
		const ETypeID nType = GetGlobalVariableType(sName);
		if (nType != TypeInvalid) {
			// Push the value of the global variable onto the Lua stack
			switch (nType) {
				case TypeBool:
					lua_pushboolean(m_pLuaState, sValue.GetBool());
					break;

				case TypeDouble:
					lua_pushnumber(m_pLuaState, sValue.GetDouble());
					break;

				case TypeString:
					lua_pushstring(m_pLuaState, sValue);
					break;
			}

			// Push the name of the global variable onto the Lua stack - this sets the global variable
			lua_setglobal(m_pLuaState, sName);
		}
	}
}

bool Script::BeginCall(const String &sFunctionName, const String &sFunctionSignature)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		// Push the function to be called onto the Lua state stack
		lua_getglobal(m_pLuaState, sFunctionName);
		if (lua_isfunction(m_pLuaState, -1)) {
			// Backup the name of the current function (we may need it for error log output)
			m_sCurrentFunction = sFunctionName;

			// Has the current function a result?
			m_bFunctionResult = !sFunctionSignature.Compare("void", 0, 4);

			// Current argument is 0
			m_nCurrentArgument = 0;

			// Done
			return true;
		} else {
			// Error!
			LogOutput(Log::Error, "The function '" + sFunctionName + "' was not found");
			lua_pop(m_pLuaState, 1);	// Remove the function name from the Lua state runtime stack
		}
	}

	// Error!
	return false;
}

void Script::PushArgument(bool bValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		lua_pushboolean(m_pLuaState, bValue);
		m_nCurrentArgument++;
	}
}

void Script::PushArgument(float fValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		lua_pushnumber(m_pLuaState, fValue);
		m_nCurrentArgument++;
	}
}

void Script::PushArgument(double fValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		lua_pushnumber(m_pLuaState, fValue);
		m_nCurrentArgument++;
	}
}

void Script::PushArgument(int8 nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		lua_pushinteger(m_pLuaState, nValue);
		m_nCurrentArgument++;
	}
}

void Script::PushArgument(int16 nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		lua_pushinteger(m_pLuaState, nValue);
		m_nCurrentArgument++;
	}
}

void Script::PushArgument(int32 nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		lua_pushinteger(m_pLuaState, nValue);
		m_nCurrentArgument++;
	}
}

void Script::PushArgument(int64 nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		// [TODO] There's no int64 support in Lua (?)
		lua_pushinteger(m_pLuaState, static_cast<lua_Integer>(nValue));
		m_nCurrentArgument++;
	}
}

void Script::PushArgument(uint8 nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		lua_pushinteger(m_pLuaState, nValue);
		m_nCurrentArgument++;
	}
}

void Script::PushArgument(uint16 nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		lua_pushinteger(m_pLuaState, nValue);
		m_nCurrentArgument++;
	}
}

void Script::PushArgument(uint32 nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		lua_pushinteger(m_pLuaState, nValue);
		m_nCurrentArgument++;
	}
}

void Script::PushArgument(uint64 nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		// [TODO] There's no uint64 support in Lua (?)
		lua_pushinteger(m_pLuaState, static_cast<lua_Integer>(nValue));
		m_nCurrentArgument++;
	}
}

void Script::PushArgument(const String &sString)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		lua_pushstring(m_pLuaState, sString);
		m_nCurrentArgument++;
	}
}

void Script::PushArgument(Object *pObject)
{
	// The destruction of the new RTTIObjectPointer instance is done by the Lua garbage collector
	new RTTIObjectPointer(*this, pObject);
	m_nCurrentArgument++;
}

bool Script::EndCall()
{
	// Is there a Lua state?
	if (m_pLuaState) {
		// Do the call ('m_nCurrentArgument' arguments, 1 result)
		const int nResult = lua_pcall(m_pLuaState, m_nCurrentArgument, m_bFunctionResult, 0);
		if (nResult) {
			// Write a log mesage
			String sErrorDescription;
			switch (nResult) {
				case LUA_ERRRUN:
					sErrorDescription = " (A runtime error)";
					break;

				case LUA_ERRMEM:
					sErrorDescription = " (Memory allocation error)";
					break;

				case LUA_ERRERR:
					sErrorDescription = " (Error while running the error handler function)";
					break;
			}
			LogOutput(Log::Error, "Error running function '" + m_sCurrentFunction + '\'' + sErrorDescription);

			// Report Lua errors
			ReportErrors();
		} else {
			// Done
			return true;
		}
	}

	// Error!
	return false;
}

void Script::GetReturn(bool &bValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		if (!lua_isboolean(m_pLuaState, -1))
			LogOutput(Log::Error, "Function '" + m_sCurrentFunction + "' must return a boolean");
		bValue = (lua_toboolean(m_pLuaState, -1) != 0);
		lua_pop(m_pLuaState, 1);
	} else {
		// Error!
		bValue = false;
	}
}

void Script::GetReturn(float &fValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		if (!lua_isnumber(m_pLuaState, -1))
			LogOutput(Log::Error, "Function '" + m_sCurrentFunction + "' must return a number");
		fValue = static_cast<float>(lua_tonumber(m_pLuaState, -1));
		lua_pop(m_pLuaState, 1);
	} else {
		// Error!
		fValue = 0.0f;
	}
}

void Script::GetReturn(double &fValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		if (!lua_isnumber(m_pLuaState, -1))
			LogOutput(Log::Error, "Function '" + m_sCurrentFunction + "' must return a number");
		fValue = lua_tonumber(m_pLuaState, -1);
		lua_pop(m_pLuaState, 1);
	} else {
		// Error!
		fValue = 0.0;
	}
}

void Script::GetReturn(int8 &nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		if (!lua_isnumber(m_pLuaState, -1))
			LogOutput(Log::Error, "Function '" + m_sCurrentFunction + "' must return a number");
		nValue = static_cast<uint8>(lua_tointeger(m_pLuaState, -1));
		lua_pop(m_pLuaState, 1);
	} else {
		// Error!
		nValue = 0;
	}
}

void Script::GetReturn(int16 &nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		if (!lua_isnumber(m_pLuaState, -1))
			LogOutput(Log::Error, "Function '" + m_sCurrentFunction + "' must return a number");
		nValue = static_cast<uint16>(lua_tointeger(m_pLuaState, -1));
		lua_pop(m_pLuaState, 1);
	} else {
		// Error!
		nValue = 0;
	}
}

void Script::GetReturn(int32 &nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		if (!lua_isnumber(m_pLuaState, -1))
			LogOutput(Log::Error, "Function '" + m_sCurrentFunction + "' must return a number");
		nValue = lua_tointeger(m_pLuaState, -1);
		lua_pop(m_pLuaState, 1);
	} else {
		// Error!
		nValue = 0;
	}
}

void Script::GetReturn(int64 &nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		if (!lua_isnumber(m_pLuaState, -1))
			LogOutput(Log::Error, "Function '" + m_sCurrentFunction + "' must return a number");
		// [TODO] There's no int64 support in Lua (?)
		nValue = lua_tointeger(m_pLuaState, -1);
		lua_pop(m_pLuaState, 1);
	} else {
		// Error!
		nValue = 0;
	}
}

void Script::GetReturn(uint8 &nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		if (!lua_isnumber(m_pLuaState, -1))
			LogOutput(Log::Error, "Function '" + m_sCurrentFunction + "' must return a number");
		nValue = static_cast<uint8>(lua_tointeger(m_pLuaState, -1));
		lua_pop(m_pLuaState, 1);
	} else {
		// Error!
		nValue = 0;
	}
}

void Script::GetReturn(uint16 &nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		if (!lua_isnumber(m_pLuaState, -1))
			LogOutput(Log::Error, "Function '" + m_sCurrentFunction + "' must return a number");
		nValue = static_cast<uint16>(lua_tointeger(m_pLuaState, -1));
		lua_pop(m_pLuaState, 1);
	} else {
		// Error!
		nValue = 0;
	}
}

void Script::GetReturn(uint32 &nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		if (!lua_isnumber(m_pLuaState, -1))
			LogOutput(Log::Error, "Function '" + m_sCurrentFunction + "' must return a number");
		nValue = lua_tointeger(m_pLuaState, -1);
		lua_pop(m_pLuaState, 1);
	} else {
		// Error!
		nValue = 0;
	}
}

void Script::GetReturn(uint64 &nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		if (!lua_isnumber(m_pLuaState, -1))
			LogOutput(Log::Error, "Function '" + m_sCurrentFunction + "' must return a number");
		// [TODO] There's no uint64 support in Lua (?)
		nValue = lua_tointeger(m_pLuaState, -1);
		lua_pop(m_pLuaState, 1);
	} else {
		// Error!
		nValue = 0;
	}
}

void Script::GetReturn(String &sValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		if (!lua_isstring(m_pLuaState, -1))
			LogOutput(Log::Error, "Function '" + m_sCurrentFunction + "' must return a string");
		sValue = lua_tostring(m_pLuaState, -1);
		lua_pop(m_pLuaState, 1);
	} else {
		// Error!
		sValue = "";
	}
}


//[-------------------------------------------------------]
//[ Private static Lua callback functions                 ]
//[-------------------------------------------------------]
/*
*  @brief
*    Lua memory allocation
*/
void *Script::LuaMemoryAllocation(void *pUserData, void *pPointer, size_t nOriginalBlockSize, size_t nNewBlockSize)
{
	if (nNewBlockSize) {
		return MemoryManager::Reallocator(pPointer, nNewBlockSize);
	} else {
		delete [] pPointer;
		return nullptr;
	}
}

/*
*  @brief
*    Lua function callback
*/
int Script::LuaFunctionCallback(lua_State *pLuaState)
{
	// Get the number of arguments Lua gave to us
	String sParams;
	const int nNumOfArguments = lua_gettop(pLuaState);
	for (int i=1; i<=nNumOfArguments; i++)
		sParams += String("Param") + (i-1) + "=\"" + lua_tolstring(pLuaState, i, nullptr) + "\" ";

	// Get the global function
	GlobalFunction *psGlobalFunction = reinterpret_cast<GlobalFunction*>(lua_touserdata(pLuaState, lua_upvalueindex(1)));
	const String sReturn = psGlobalFunction->pDynFunc->CallWithReturn(sParams);
	if (sReturn.GetLength()) {
		// Process the functor return
		switch (psGlobalFunction->pDynFunc->GetReturnTypeID()) {
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
			default:			lua_pushstring (pLuaState, sReturn);										break;	// TypeVoid, TypeNull, TypeObjectPtr, -1
		}

		// The function returns one argument
		return 1;
	} else {
		// The function returns nothing
		return 0;
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Script::Script(const Script &cSource) :
	m_pLuaState(nullptr),
	m_bFunctionResult(false),
	m_nCurrentArgument(0)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Script &Script::operator =(const Script &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Reports Lua errors
*/
void Script::ReportErrors()
{
	// Output the Lua errors
	LogOutput(Log::Error, lua_tostring(m_pLuaState, -1));

	// Pop the error value from the stack
	lua_pop(m_pLuaState, 1);
}

/**
*  @brief
*    Clears the script
*/
void Script::Clear()
{
	// Is there a Lua state?
	if (m_pLuaState) {
		// Reset the source code
		m_sSourceCode = "";

		// Verify the stack and write a warning into the log if the script stack is not empty
		if (lua_gettop(m_pLuaState)) {
			LogOutput(Log::Warning, "Script termination, but the stack is not empty");
			LuaStackDump();
		}

		// Clear all global variables
		while (true) {
			lua_pushnil(m_pLuaState);
			if (!lua_next(m_pLuaState, LUA_GLOBALSINDEX))
				break;
			lua_pop(m_pLuaState, 1);
			lua_pushnil(m_pLuaState);
			lua_rawset(m_pLuaState, LUA_GLOBALSINDEX);
		}

		// Force the garbage collector to cleanup right now... because required stuff like the LuaUserData metatable are still there at the moment...
		lua_gc(m_pLuaState, LUA_GCCOLLECT, 0);

		// Destroy the metatable for LuaUserData events
		LuaUserData::DestroyMetatable(m_pLuaState);

		// Close the Lua state
		lua_close(m_pLuaState);
		m_pLuaState = nullptr;

		// Reset states
		m_sCurrentFunction = "";
		m_bFunctionResult  = false;
		m_nCurrentArgument = 0;

		// Clear the list of all global variables
		m_lstGlobalVariables.Clear();
	}
}

/**
*  @brief
*    Creates a nested Lua table
*/
bool Script::CreateNestedTable(lua_State *pLuaState, const String &sTableName)
{
	// Loop through all components within the given nested Lua table name
	uint32 nPartBegin = 0;
	while (nPartBegin<=sTableName.GetLength()) {
		// Find the next "." within the given nested Lua table name
		int nPartEnd = sTableName.IndexOf(".", nPartBegin);
		if (nPartEnd < 0)
			nPartEnd = sTableName.GetLength();

		// Get the current Lua table name
		const String sSubTableName = sTableName.GetSubstring(nPartBegin, nPartEnd - nPartBegin);

		// Each table must have a name!
		if (!sSubTableName.GetLength())
			return false;	// Error!

		// Does the Lua table already exist within the current Lua table?
		if (nPartBegin) {
			// We're already within a Lua table
			lua_pushstring(pLuaState, sSubTableName);
			lua_gettable(pLuaState, -2);
			if (!lua_isnil(pLuaState, -1))
				lua_remove(pLuaState, -2);
		} else {
			// Currently we're in global space
			lua_pushstring(pLuaState, sSubTableName);
			lua_gettable(pLuaState, LUA_GLOBALSINDEX);
		}

		// Lua table found?
		if (lua_isnil(pLuaState, -1)) {
			// Nope, create a new one

			// Pop nil from the Lua stack
			lua_pop(pLuaState, 1);

			// Create new Lua table on the Lua stack
			lua_newtable(pLuaState);
			lua_pushstring(pLuaState, sSubTableName);
			lua_pushvalue(pLuaState, -2);	// Pushes a copy of the element at the given valid index onto the stack
			if (nPartBegin) {
				// We're already within a Lua table
				lua_settable(pLuaState, -4);
				lua_remove(pLuaState, -2);
			} else {
				// Currently we're in global space
				lua_settable(pLuaState, LUA_GLOBALSINDEX);
			}
		}

		// Skip "."
		nPartBegin = nPartEnd + 1;
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua
