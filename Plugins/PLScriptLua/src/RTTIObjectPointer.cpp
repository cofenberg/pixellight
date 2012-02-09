/*********************************************************\
 *  File: RTTIObjectPointer.cpp                          *
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
#include "PLScriptLua/Script.h"
#include "PLScriptLua/LuaContext.h"
#include "PLScriptLua/RTTIObjectPointer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLScriptLua {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Pushes an RTTI class instance onto the Lua stack
*/
void RTTIObjectPointer::LuaStackPush(Script &cScript, Object *pRTTIObject)
{
	// Valid RTTI object given?
	if (pRTTIObject)
		LuaContext::GetRTTIObjectPointer(cScript, pRTTIObject);
	else
		lua_pushnil(cScript.GetLuaState());
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
RTTIObjectPointer::RTTIObjectPointer()
{
}

/**
*  @brief
*    Destructor
*/
RTTIObjectPointer::~RTTIObjectPointer()
{
}


//[-------------------------------------------------------]
//[ Protected virtual LuaUserData functions               ]
//[-------------------------------------------------------]
void RTTIObjectPointer::CGMetamethod(lua_State *pLuaState)
{
	// De-initializes this instance
	RTTIObjectPointerBase::DeInitializeInstance();

	// Release this instance, but do not delete it because we can reuse it later on
	LuaContext::ReleaseRTTIObjectPointer(*this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua
