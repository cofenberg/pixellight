/*********************************************************\
 *  File: ScriptBinding_PL_Log.h                         *
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


#ifndef __PLSCRIPTBINDINGS_PL_LOG_H__
#define __PLSCRIPTBINDINGS_PL_LOG_H__
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
*    Log script binding class
*/
class ScriptBinding_PL_Log : public PLCore::ScriptBinding {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, ScriptBinding_PL_Log, "PLScriptBindings", PLCore::ScriptBinding, "Log script binding class")
		// Properties
		pl_properties
			pl_property("Namespace",	"PL.Log")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_1(OutputAlways,	pl_ret_type(void),	PLGeneral::String,	"Writes the given string into the log ('always' log level)",	"")
		pl_method_1(OutputCritical,	pl_ret_type(void),	PLGeneral::String,	"Writes the given string into the log ('critical' log level)",	"")
		pl_method_1(OutputError,	pl_ret_type(void),	PLGeneral::String,	"Writes the given string into the log ('error' log level)",		"")
		pl_method_1(OutputWarning,	pl_ret_type(void),	PLGeneral::String,	"Writes the given string into the log ('warning' log level)",	"")
		pl_method_1(OutputInfo,		pl_ret_type(void),	PLGeneral::String,	"Writes the given string into the log ('info' log level)",		"")
		pl_method_1(OutputDebug,	pl_ret_type(void),	PLGeneral::String,	"Writes the given string into the log ('debug' log level)",		"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		void OutputAlways(PLGeneral::String sText);
		void OutputCritical(PLGeneral::String sText);
		void OutputError(PLGeneral::String sText);
		void OutputWarning(PLGeneral::String sText);
		void OutputInfo(PLGeneral::String sText);
		void OutputDebug(PLGeneral::String sText);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		ScriptBinding_PL_Log();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ScriptBinding_PL_Log();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptBindings


#endif // __PLSCRIPTBINDINGS_PL_LOG_H__
