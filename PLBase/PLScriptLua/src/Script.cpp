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
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}
#include <PLGeneral/Log/Log.h>
#include "PLScriptLua/LuaContext.h"
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

	// Remove all dynamic functions
	RemoveAllDynamicFunctions();

	// Release a context reference
	LuaContext::ReleaseContextReference();
}


//[-------------------------------------------------------]
//[ Public virtual PLScript::Script functions             ]
//[-------------------------------------------------------]
bool Script::AddDynamicFunction(const String &sFunction, const DynFunc &cDynFunc, const String &sNamespace)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		// Error!
		return false;
	} else {
		// Add the dynamic function
		DynamicFunction *psDynamicFunction = new DynamicFunction;
		psDynamicFunction->sFunction  = sFunction;
		psDynamicFunction->pDynFunc   = cDynFunc.Clone();
		psDynamicFunction->sNamespace = sNamespace;
		m_lstDynamicFunctions.Add(psDynamicFunction);

		// Done
		return true;
	}
}

bool Script::RemoveAllDynamicFunctions()
{
	// Is there a Lua state?
	if (m_pLuaState) {
		// Error!
		return false;
	} else {
		// Destroy the dynamic functions
		for (uint32 i=0; i<m_lstDynamicFunctions.GetNumOfElements(); i++) {
			delete m_lstDynamicFunctions[i]->pDynFunc;
			delete m_lstDynamicFunctions[i];
		}
		m_lstDynamicFunctions.Clear();

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

			// Add the dynamic functions
			for (uint32 i=0; i<m_lstDynamicFunctions.GetNumOfElements(); i++) {
				// Get the dynamic function
				DynamicFunction *psDynamicFunction = m_lstDynamicFunctions[i];

				// Is the function within a namespace? (= Lua table)
				if (psDynamicFunction->sNamespace.GetLength()) {
					// [TODO] Create and set Lua table

					// Table key
					lua_pushstring(m_pLuaState, psDynamicFunction->sFunction);			// Push the function name onto the Lua stack

					// Table value: Store a pointer to the dynamic function in the c-closure
					lua_pushlightuserdata(m_pLuaState, psDynamicFunction);				// Push a pointer to the dynamic function onto the Lua stack
					lua_pushcclosure(m_pLuaState, &Script::LuaFunctionCallback, 1);		// Push the function pointer onto the Lua stack

					// This function pops both the key and the value from the stack
					lua_settable(m_pLuaState, -3);

					// Pop the table from the Lua stack
					lua_pop(m_pLuaState, 1);
				} else {
					// Store a pointer to the dynamic function in the c-closure
					lua_pushlightuserdata(m_pLuaState, psDynamicFunction);
					lua_pushcclosure(m_pLuaState, &Script::LuaFunctionCallback, 1);
					lua_setglobal(m_pLuaState, psDynamicFunction->sFunction);
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

void Script::PushArgument(int nValue)
{
	// Is there a Lua state?
	if (m_pLuaState) {
		lua_pushinteger(m_pLuaState, nValue);
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

void Script::GetReturn(int &nValue)
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

	// Get the dynamic function
	DynamicFunction *psDynamicFunction = reinterpret_cast<DynamicFunction*>(lua_touserdata(pLuaState, lua_upvalueindex(1)));
	const String sReturn = psDynamicFunction->pDynFunc->CallWithReturn(sParams);
	if (sReturn.GetLength()) {
		// Process the functor return
		switch (psDynamicFunction->pDynFunc->GetReturnTypeID()) {
			case TypeBool:		lua_pushinteger(pLuaState, sReturn.GetBool());		break;
			case TypeDouble:	lua_pushnumber (pLuaState, sReturn.GetDouble());	break;
			case TypeFloat:		lua_pushnumber (pLuaState, sReturn.GetFloat());		break;
			case TypeInt:		lua_pushinteger(pLuaState, sReturn.GetInt());		break;
			case TypeInt16:		lua_pushinteger(pLuaState, sReturn.GetInt());		break;
			case TypeInt32:		lua_pushinteger(pLuaState, sReturn.GetInt());		break;
			case TypeInt64:		lua_pushinteger(pLuaState, sReturn.GetInt());		break;	// [TODO] TypeInt64 is currently handled just as long
			case TypeInt8:		lua_pushinteger(pLuaState, sReturn.GetInt());		break;
			case TypeString:	lua_pushstring (pLuaState, sReturn);				break;
			case TypeUInt16:	lua_pushinteger(pLuaState, sReturn.GetUInt16());	break;
			case TypeUInt32:	lua_pushinteger(pLuaState, sReturn.GetUInt32());	break;
			case TypeUInt64:	lua_pushinteger(pLuaState, sReturn.GetUInt64());	break;	// [TODO] TypeUInt64 is currently handled just as long
			case TypeUInt8:		lua_pushinteger(pLuaState, sReturn.GetUInt8());		break;
			default:			lua_pushstring (pLuaState, sReturn);				break;	// TypeVoid, TypeNull, TypeObjectPtr, -1
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
		if (lua_gettop(m_pLuaState))
			LogOutput(Log::Warning, "Script termination, but the stack is not empty");

		// Close the Lua state
		lua_close(m_pLuaState);
		m_pLuaState = nullptr;

		// Reset states
		m_sCurrentFunction = "";
		m_bFunctionResult  = false;
		m_nCurrentArgument = 0;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua
