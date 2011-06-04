/*********************************************************\
 *  File: ScriptBindingSceneRendererTool.cpp             *
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
#include <PLScene/Scene/SceneContainer.h>
#include <PLEngine/Application/BasicSceneApplication.h>
#include "PLScriptBindings/ScriptBindingSceneRendererTool.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLScene;
using namespace PLEngine;
namespace PLScriptBindings {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ScriptBindingSceneRendererTool)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool ScriptBindingSceneRendererTool::SetPassAttribute(String sSceneRendererPassName, String sAttributeName, String sValue)
{
	// [TODO] Do any type checks?
	// Get the basic scene application instance
	BasicSceneApplication *pBasicSceneApplication = static_cast<BasicSceneApplication*>(BasicSceneApplication::GetApplication());

	// Make the call
	return pBasicSceneApplication ? pBasicSceneApplication->GetSceneRendererTool().SetPassAttribute(sSceneRendererPassName, sAttributeName, sValue) : false;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ScriptBindingSceneRendererTool::ScriptBindingSceneRendererTool()
{
}

/**
*  @brief
*    Destructor
*/
ScriptBindingSceneRendererTool::~ScriptBindingSceneRendererTool()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptBindings
