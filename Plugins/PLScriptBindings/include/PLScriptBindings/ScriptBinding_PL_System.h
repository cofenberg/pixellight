/*********************************************************\
 *  File: ScriptBinding_PL_System.h                      *
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


#ifndef __PLSCRIPTBINDINGS_PL_SYSTEM_H__
#define __PLSCRIPTBINDINGS_PL_SYSTEM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Script/ScriptBinding.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptBindings {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    System script binding class
*/
class ScriptBinding_PL_System : public PLCore::ScriptBinding {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, ScriptBinding_PL_System, "PLScriptBindings", PLCore::ScriptBinding, "System script binding class")
		// Properties
		pl_properties
			pl_property("Namespace",	"PL.System")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_0(IsWindows,	pl_ret_type(bool),	"Returns 'true' if we're currently running on a Windows platform, else 'false'",	"")
		pl_method_0(IsLinux,	pl_ret_type(bool),	"Returns 'true' if we're currently running on a Linux platform, else 'false'",		"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool IsWindows();
		bool IsLinux();


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		ScriptBinding_PL_System();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ScriptBinding_PL_System();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptBindings


#endif // __PLSCRIPTBINDINGS_PL_SYSTEM_H__
