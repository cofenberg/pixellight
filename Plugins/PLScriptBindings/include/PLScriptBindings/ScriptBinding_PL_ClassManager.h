/*********************************************************\
 *  File: ScriptBinding_PL_ClassManager.h                *
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


#ifndef __PLSCRIPTBINDINGS_PL_CLASSMANAGER_H__
#define __PLSCRIPTBINDINGS_PL_CLASSMANAGER_H__
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
*    Class manager script binding class
*/
class ScriptBinding_PL_ClassManager : public PLCore::ScriptBinding {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, ScriptBinding_PL_ClassManager, "PLScriptBindings", PLCore::ScriptBinding, "Class manager script binding class")
		// Properties
		pl_properties
			pl_property("Namespace",	"PL.ClassManager")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_3(ScanPlugins,	pl_ret_type(bool),	PLCore::String, bool, bool, "Scan a directory for compatible plugins and load them in. Directory to search in as first parameter, boolean value deciding whether or not to take sub-directories into account as second parameter, boolean value deciding whether or not its allowed to perform delayed shared library loading to speed up the program start as third parameter. Returns 'true' if all went fine, else 'false'.", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool ScanPlugins(PLCore::String sPath, bool bRecursive, bool bDelayedPluginLoading);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		ScriptBinding_PL_ClassManager();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ScriptBinding_PL_ClassManager();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptBindings


#endif // __PLSCRIPTBINDINGS_PL_CLASSMANAGER_H__
