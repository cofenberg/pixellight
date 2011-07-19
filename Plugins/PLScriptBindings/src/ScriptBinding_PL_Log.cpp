/*********************************************************\
 *  File: ScriptBinding_PL_Log.cpp                       *
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
#include <PLCore/Log/Log.h>
#include "PLScriptBindings/ScriptBinding_PL_Log.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLScriptBindings {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ScriptBinding_PL_Log)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
void ScriptBinding_PL_Log::OutputAlways(String sText)
{
	Log::GetInstance()->Output(Log::Always, sText);
}

void ScriptBinding_PL_Log::OutputCritical(String sText)
{
	Log::GetInstance()->Output(Log::Critical, sText);
}

void ScriptBinding_PL_Log::OutputError(String sText)
{
	Log::GetInstance()->Output(Log::Error, sText);
}

void ScriptBinding_PL_Log::OutputWarning(String sText)
{
	Log::GetInstance()->Output(Log::Warning, sText);
}

void ScriptBinding_PL_Log::OutputInfo(String sText)
{
	Log::GetInstance()->Output(Log::Info, sText);
}

void ScriptBinding_PL_Log::OutputDebug(String sText)
{
	Log::GetInstance()->Output(Log::Debug, sText);
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ScriptBinding_PL_Log::ScriptBinding_PL_Log()
{
}

/**
*  @brief
*    Destructor
*/
ScriptBinding_PL_Log::~ScriptBinding_PL_Log()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptBindings
