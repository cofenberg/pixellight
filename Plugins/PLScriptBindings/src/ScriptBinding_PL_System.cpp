/*********************************************************\
 *  File: ScriptBinding_PL_System.cpp                    *
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
#include <PLCore/System/System.h>
#include <PLCore/System/Console.h>
#include "PLScriptBindings/ScriptBinding_PL_System.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLScriptBindings {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ScriptBinding_PL_System)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool ScriptBinding_PL_System::IsWindows()
{
	#ifdef WIN32
		return true;
	#else
		return false;
	#endif
}

bool ScriptBinding_PL_System::IsLinux()
{
	#ifdef LINUX
		return true;
	#else
		return false;
	#endif
}

String ScriptBinding_PL_System::GetPlatformArchitecture()
{
	return System::GetInstance()->GetPlatformArchitecture();
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ScriptBinding_PL_System::ScriptBinding_PL_System()
{
}

/**
*  @brief
*    Destructor
*/
ScriptBinding_PL_System::~ScriptBinding_PL_System()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptBindings
