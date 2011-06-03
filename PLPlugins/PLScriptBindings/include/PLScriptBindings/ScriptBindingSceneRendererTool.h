/*********************************************************\
 *  File: ScriptBindingSceneRendererTool.h               *
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


#ifndef __PLSCRIPTBINDINGS_SCENERENDERERTOOL_H__
#define __PLSCRIPTBINDINGS_SCENERENDERERTOOL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScript/ScriptBinding.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptBindings {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene renderer tool script binding class
*/
class ScriptBindingSceneRendererTool : public PLScript::ScriptBinding {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, ScriptBindingSceneRendererTool, "PLScriptBindings", PLScript::ScriptBinding, "Scene renderer tool script binding class")
		pl_properties
			pl_property("Namespace", "PL.Application.SceneRendererTool")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_3(SetPassAttribute, bool, PLGeneral::String, PLGeneral::String, PLGeneral::String, "Sets a scene renderer pass attribute value using a string, name of the scene renderer pass as first parameter, name of the scene renderer pass attribute as second parameter and value to set as third parameter", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool SetPassAttribute(PLGeneral::String sSceneRendererPassName, PLGeneral::String sAttributeName, PLGeneral::String sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		ScriptBindingSceneRendererTool();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ScriptBindingSceneRendererTool();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptBindings


#endif // __PLSCRIPTBINDINGS_SCENERENDERERTOOL_H__
