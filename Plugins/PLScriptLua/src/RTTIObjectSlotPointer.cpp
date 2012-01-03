/*********************************************************\
 *  File: RTTIObjectSlotPointer.cpp                      *
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
#include "PLScriptLua/RTTIObjectSlotPointer.h"


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
*    Constructor
*/
RTTIObjectSlotPointer::RTTIObjectSlotPointer(Script &cScript, Object *pRTTIObject, DynEventHandler *pDynEventHandler) : RTTIObjectPointer(cScript, pRTTIObject, TypeObjectSlotPointer),
	m_pDynEventHandler(pDynEventHandler)
{
}

/**
*  @brief
*    Destructor
*/
RTTIObjectSlotPointer::~RTTIObjectSlotPointer()
{
}

/**
*  @brief
*    Returns the pointer to the RTTI object slot to wrap
*/
DynEventHandler *RTTIObjectSlotPointer::GetDynEventHandler() const
{
	return m_pDynEventHandler;
}


//[-------------------------------------------------------]
//[ Protected virtual LuaUserData functions               ]
//[-------------------------------------------------------]
int RTTIObjectSlotPointer::IndexMetamethod(lua_State *pLuaState)
{
	// Error! A slot can't be called like an object...
	// [TODO] Write an error message into the log? (with current script line etc.)

	// Error!
	return 0;
}

int RTTIObjectSlotPointer::NewIndexMetamethod(lua_State *pLuaState)
{
	// Error! A slot can't be called like an object...
	// [TODO] Write an error message into the log? (with current script line etc.)

	// Done
	return 0;
}

void RTTIObjectSlotPointer::CallMetamethod(lua_State *pLuaState)
{
	// Error! A slot can't be called like a function...
	// [TODO] Write an error message into the log? (with current script line etc.)
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua
