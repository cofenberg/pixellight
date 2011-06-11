/*********************************************************\
 *  File: ScriptBinding_PL_System_Console.h              *
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


#ifndef __PLSCRIPTBINDINGS_PL_SYSTEM_CONSOLE_H__
#define __PLSCRIPTBINDINGS_PL_SYSTEM_CONSOLE_H__
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
*    System console script binding class
*/
class ScriptBinding_PL_System_Console : public PLScript::ScriptBinding {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, ScriptBinding_PL_System_Console, "PLScriptBindings", PLScript::ScriptBinding, "System console script binding class")
		// Properties
		pl_properties
			pl_property("Namespace",	"PL.System.Console")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	 "Default constructor",		"")
		// Methods
		pl_method_1(Print,	pl_ret_type(void),	PLGeneral::String,	"Prints the given string into the system console",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		void Print(PLGeneral::String sText);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		ScriptBinding_PL_System_Console();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ScriptBinding_PL_System_Console();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptBindings


#endif // __PLSCRIPTBINDINGS_PL_SYSTEM_CONSOLE_H__
