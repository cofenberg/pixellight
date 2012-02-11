/*********************************************************\
 *  File: ScriptBinding_PL_Timing.cpp                    *
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
#include <PLCore/Tools/Timing.h>
#include "PLScriptBindings/ScriptBinding_PL_Timing.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLScriptBindings {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ScriptBinding_PL_Timing)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
float ScriptBinding_PL_Timing::GetTimeDifference()
{
	return m_pTiming->GetTimeDifference();
}

float ScriptBinding_PL_Timing::GetFramesPerSecond()
{
	return m_pTiming->GetFramesPerSecond();
}

bool ScriptBinding_PL_Timing::IsPaused()
{
	return m_pTiming->IsPaused();
}

void ScriptBinding_PL_Timing::Pause(bool bPause)
{
	m_pTiming->Pause(bPause);
}

float ScriptBinding_PL_Timing::GetTimeScaleFactor()
{
	return m_pTiming->GetTimeScaleFactor();
}

bool ScriptBinding_PL_Timing::SetTimeScaleFactor(float fFactor)
{
	return m_pTiming->SetTimeScaleFactor(fFactor);
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ScriptBinding_PL_Timing::ScriptBinding_PL_Timing() :
	m_pTiming(Timing::GetInstance())
{
}

/**
*  @brief
*    Destructor
*/
ScriptBinding_PL_Timing::~ScriptBinding_PL_Timing()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptBindings
