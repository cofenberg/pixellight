/*********************************************************\
 *  File: LuaUserData.cpp                                *
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
	#include <Lua/lauxlib.h>
}
#include "PLScriptLua/Script.h"
#include "PLScriptLua/LuaUserData.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptLua {


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
char LuaUserData::LuaMetatable = 42;


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Creates the metatable for LuaUserData events
*/
void LuaUserData::CreateMetatable(lua_State *pLuaState)
{
	lua_pushlightuserdata(pLuaState, &LuaMetatable);
	lua_newtable(pLuaState);

	// Lua __index metamethod callback (for table accesses)
	lua_pushstring(pLuaState, "__index");
	lua_pushcfunction(pLuaState, LuaIndexMetamethodCallback);
	lua_rawset(pLuaState, -3);

	// Lua __newindex metamethod callback (for table updates)
	lua_pushstring(pLuaState, "__newindex");
	lua_pushcfunction(pLuaState, LuaNewIndexMetamethodCallback);
	lua_rawset(pLuaState, -3);

	// Lua __gc metamethod callback (finalizer/destructor called by garbage collector)
	lua_pushstring(pLuaState, "__gc");
	lua_pushcfunction(pLuaState, LuaCGMetamethodCallback);
	lua_rawset(pLuaState, -3);

	// Lua __call metamethod callback (called when Lua calls a value)
	lua_pushstring(pLuaState, "__call");
	lua_pushcfunction(pLuaState, LuaCallMetamethodCallback);
	lua_rawset(pLuaState, -3);

	lua_rawset(pLuaState, LUA_REGISTRYINDEX);
}

/**
*  @brief
*    Destroys the metatable for LuaUserData events
*/
void LuaUserData::DestroyMetatable(lua_State *pLuaState)
{
	lua_pushlightuserdata(pLuaState, &LuaMetatable);
	lua_pushnil(pLuaState);
	lua_rawset(pLuaState, LUA_REGISTRYINDEX);
}

/**
*  @brief
*    Returns user data from the Lua stack without removing it
*/
LuaUserData *LuaUserData::GetUserDataFromLuaStack(lua_State *pLuaState, int nIndex)
{
	// Must be a metatable
	if (lua_getmetatable(pLuaState, nIndex)) {
		lua_pushlightuserdata(pLuaState, &LuaMetatable);
		lua_rawget(pLuaState, LUA_REGISTRYINDEX);
		if (lua_rawequal(pLuaState, -2, -1)) {
			lua_pop(pLuaState, 2);
			LuaUserData **ppLuaUserData = static_cast<LuaUserData**>(lua_touserdata(pLuaState, nIndex));
			return *ppLuaUserData;
		}
		lua_pop(pLuaState, 1);
	}
	lua_pop(pLuaState, 1);

	// Error!
	return nullptr;
}

/**
*  @brief
*    Returns user data from the top of the Lua stack and removes it from the Lua stack
*/
LuaUserData *LuaUserData::PopUserDataFromLuaStack(lua_State *pLuaState)
{
	// Must be a metatable
	if (lua_getmetatable(pLuaState, -1)) {
		lua_pushlightuserdata(pLuaState, &LuaMetatable);
		lua_rawget(pLuaState, LUA_REGISTRYINDEX);
		if (lua_rawequal(pLuaState, -2, -1)) {
			lua_pop(pLuaState, 2);
			LuaUserData **ppLuaUserData = static_cast<LuaUserData**>(lua_touserdata(pLuaState, -1));
			lua_pop(pLuaState, 1);
			return *ppLuaUserData;
		}
		lua_pop(pLuaState, 1);
	}
	lua_pop(pLuaState, 1);
	lua_pop(pLuaState, 1);

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Return the Lua user data type
*/
LuaUserData::EType LuaUserData::GetType() const
{
	return m_nType;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
LuaUserData::LuaUserData(Script &cScript, EType nType) :
	m_pScript(&cScript),
	m_nType(nType)
{
	// Get the Lua state
	lua_State *pLuaState = m_pScript->GetLuaState();

	// Allocate memory for a pointer to to object
	LuaUserData **ppLuaUserData = reinterpret_cast<LuaUserData**>(lua_newuserdata(pLuaState, sizeof(LuaUserData*)));

	// Set as data a pointer to this instance and increase the reference count
	*ppLuaUserData = this;
	AddReference();

	// Attach metatable
	lua_pushlightuserdata(pLuaState, &LuaMetatable);
	lua_rawget(pLuaState, LUA_REGISTRYINDEX);
	lua_setmetatable(pLuaState, -2);
}

/**
*  @brief
*    Destructor
*/
LuaUserData::~LuaUserData()
{
}


//[-------------------------------------------------------]
//[ Private static Lua callback functions                 ]
//[-------------------------------------------------------]
/*
*  @brief
*    Lua __index metamethod callback (for table accesses)
*/
int LuaUserData::LuaIndexMetamethodCallback(lua_State *pLuaState)
{
	// Get user data from the Lua stack without removing it
	LuaUserData *pLuaUserData = GetUserDataFromLuaStack(pLuaState, 1);
	if (pLuaUserData) {
		// Call the virtual method
		return pLuaUserData->IndexMetamethod(pLuaState);
	}

	// Error!
	return 0;
}

/*
*  @brief
*    Lua __newindex metamethod callback (for table updates)
*/
int LuaUserData::LuaNewIndexMetamethodCallback(lua_State *pLuaState)
{
	// Get user data from the Lua stack without removing it
	LuaUserData *pLuaUserData = GetUserDataFromLuaStack(pLuaState, 1);
	if (pLuaUserData) {
		// Call the virtual method
		return pLuaUserData->NewIndexMetamethod(pLuaState);
	}

	// Error!
	return 0;
}

/*
*  @brief
*    Lua __gc metamethod callback (finalizer/destructor called by garbage collector)
*/
int LuaUserData::LuaCGMetamethodCallback(lua_State *pLuaState)
{
	// Get user data from the Lua stack without removing it
	LuaUserData *pLuaUserData = GetUserDataFromLuaStack(pLuaState, 1);
	if (pLuaUserData) {
		// Call the virtual method
		pLuaUserData->CGMetamethod(pLuaState);

		// Release the instance
		pLuaUserData->Release();
	}

	// Done
	return 0;
}

/*
*  @brief
*    Lua __call metamethod callback (called when Lua calls a value)
*/
int LuaUserData::LuaCallMetamethodCallback(lua_State *pLuaState)
{
	// Get the current top of the Lua stack
	const int nLuaStackTop = lua_gettop(pLuaState);

	// Get user data from the Lua stack without removing it
	LuaUserData *pLuaUserData = GetUserDataFromLuaStack(pLuaState, 1);
	if (pLuaUserData) {
		// Call the virtual method
		pLuaUserData->CallMetamethod(pLuaState);
	}

	// Done, inform Lua what's on the stack
	return lua_gettop(pLuaState) - nLuaStackTop;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
LuaUserData::LuaUserData()
{
}

/**
*  @brief
*    Copy constructor
*/
LuaUserData::LuaUserData(const LuaUserData &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
LuaUserData &LuaUserData::operator =(const LuaUserData &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua
