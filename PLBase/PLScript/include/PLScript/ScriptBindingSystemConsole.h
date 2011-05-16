/*********************************************************\
 *  File: ScriptBindingSystemConsole.h                   *
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


#ifndef __PLSCRIPT_SCRIPTBINDING_SYSTEMCONSOLE_H__
#define __PLSCRIPT_SCRIPTBINDING_SYSTEMCONSOLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScript/ScriptBinding.h>
#include "PLScript/PLScript.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScript {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    System console script binding class
*
*  @note
*    - [TODO] Script support is currently under construction
*/
class ScriptBindingSystemConsole : public ScriptBinding {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLSCRIPT_RTTI_EXPORT, ScriptBindingSystemConsole, "PLScript", PLScript::ScriptBinding, "System console script binding class")
		pl_properties
			pl_property("Namespace", "PL.System.Console")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_1(Print, void, PLGeneral::String, "Prints the given string into the system console",   "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		PLSCRIPT_API void Print(PLGeneral::String sText);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLSCRIPT_API ScriptBindingSystemConsole();

		/**
		*  @brief
		*    Destructor
		*/
		PLSCRIPT_API virtual ~ScriptBindingSystemConsole();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScript


#endif // __PLSCRIPT_SCRIPTBINDING_SYSTEMCONSOLE_H__
