/*********************************************************\
 *  File: RTTIObjectSignalPointer.cpp                    *
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
#include "PLScriptLua/RTTIObjectSignalPointer.h"


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
RTTIObjectSignalPointer::RTTIObjectSignalPointer(Script &cScript, Object *pRTTIObject, DynEvent *pDynEvent) : RTTIObjectPointer(cScript, pRTTIObject),
	m_pDynEvent(pDynEvent)
{
}

/**
*  @brief
*    Destructor
*/
RTTIObjectSignalPointer::~RTTIObjectSignalPointer()
{
}


//[-------------------------------------------------------]
//[ Protected virtual LuaUserData functions               ]
//[-------------------------------------------------------]
void RTTIObjectSignalPointer::CallMetamethod(lua_State *pLuaState)
{
	// Is there a RTTI object and a RTTI object signal?
	if (m_pRTTIObject && m_pDynEvent) {
		// Get the number of arguments Lua gave to us
		String sParams;
		const int nNumOfArguments = lua_gettop(pLuaState) - 2;
		for (int i=3; i<=2+nNumOfArguments; i++)
			sParams += String("Param") + (i-3) + "=\"" + lua_tolstring(pLuaState, i, nullptr) + "\" ";

		// Emit the RTTI object signal
		m_pDynEvent->Emit(sParams);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua
