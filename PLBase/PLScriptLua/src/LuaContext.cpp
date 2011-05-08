/*********************************************************\
 *  File: LuaContext.cpp                                 *
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
#include <PLGeneral/Log/Log.h>
#include "PLScriptLua/LuaContext.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLScriptLua {


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
uint32 LuaContext::m_nContexCounter = 0;


//[-------------------------------------------------------]
//[ Public static methods                                 ]
//[-------------------------------------------------------]
/**
*  @brief
*    Adds a context reference
*/
void LuaContext::AddContextReference()
{
	// Check context
	if (!m_nContexCounter)
		PL_LOG(Info, String("Initialize ") + LUA_RELEASE)
	m_nContexCounter++;
}

/**
*  @brief
*    Releases a context reference
*/
void LuaContext::ReleaseContextReference()
{
	// Check context
	m_nContexCounter--;
	if (!m_nContexCounter)
		PL_LOG(Info, String("De-initialize" ) + LUA_RELEASE)
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptAngelScript
