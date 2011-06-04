/*********************************************************\
 *  File: ScriptBindingLog.cpp                           *
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
#include <PLGeneral/Log/Log.h>
#include "PLScriptBindings/ScriptBindingLog.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLScriptBindings {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ScriptBindingLog)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
void ScriptBindingLog::OutputAlways(String sText)
{
	Log::GetInstance()->Output(Log::Always, sText);
}

void ScriptBindingLog::OutputCritical(String sText)
{
	Log::GetInstance()->Output(Log::Critical, sText);
}

void ScriptBindingLog::OutputError(String sText)
{
	Log::GetInstance()->Output(Log::Error, sText);
}

void ScriptBindingLog::OutputWarning(String sText)
{
	Log::GetInstance()->Output(Log::Warning, sText);
}

void ScriptBindingLog::OutputInfo(String sText)
{
	Log::GetInstance()->Output(Log::Info, sText);
}

void ScriptBindingLog::OutputDebug(String sText)
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
ScriptBindingLog::ScriptBindingLog()
{
}

/**
*  @brief
*    Destructor
*/
ScriptBindingLog::~ScriptBindingLog()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptBindings
