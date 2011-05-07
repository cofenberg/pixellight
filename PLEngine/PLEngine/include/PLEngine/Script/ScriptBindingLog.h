/*********************************************************\
 *  File: ScriptBindingLog.h                             *
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


#ifndef __PLENGINE_SCRIPT_SCRIPTBINDING_LOG_H__
#define __PLENGINE_SCRIPT_SCRIPTBINDING_LOG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScript/ScriptBinding.h>
#include "PLEngine/PLEngine.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Log script binding class
*
*  @note
*    - [TODO] Script support is currently under construction
*/
class ScriptBindingLog : public PLScript::ScriptBinding {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, ScriptBindingLog, "PLEngine", PLScript::ScriptBinding, "Log script binding class")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_1(OutputAlways,   void, PLGeneral::String, "Writes the given string into the log ('always' log level)",   "")
		pl_method_1(OutputCritical, void, PLGeneral::String, "Writes the given string into the log ('critical' log level)", "")
		pl_method_1(OutputError,    void, PLGeneral::String, "Writes the given string into the log ('error' log level)",    "")
		pl_method_1(OutputWarning,  void, PLGeneral::String, "Writes the given string into the log ('warning' log level)",  "")
		pl_method_1(OutputInfo,     void, PLGeneral::String, "Writes the given string into the log ('info' log level)",     "")
		pl_method_1(OutputDebug,    void, PLGeneral::String, "Writes the given string into the log ('debug' log level)",    "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		PL_API void OutputAlways(PLGeneral::String sText);
		PL_API void OutputCritical(PLGeneral::String sText);
		PL_API void OutputError(PLGeneral::String sText);
		PL_API void OutputWarning(PLGeneral::String sText);
		PL_API void OutputInfo(PLGeneral::String sText);
		PL_API void OutputDebug(PLGeneral::String sText);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PL_API ScriptBindingLog();

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~ScriptBindingLog();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_SCRIPT_SCRIPTBINDING_LOG_H__
