/*********************************************************\
 *  File: FrontendMain.h                                 *
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


#ifndef __PLCORE_FRONTENDMAIN_H__
#define __PLCORE_FRONTENDMAIN_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Main.h"
#include "PLCore/ModuleMain.h"
#include "PLCore/Frontend/Frontend.h"


//[-------------------------------------------------------]
//[ Macros                                                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Defines a default frontend for a module inside a plugin library
*
*  @param[in] ModuleName
*    Module name
*  @param[in] ApplicationClass
*    Name of the application RTTI class to use (must be derived from "PLCore::FrontendApplication") [TODO] Currently ignored
*
*  @remarks
*    Use this when you don't want to care about the program entry point.
*/
#define pl_module_application(ModuleName, ApplicationClass) \
	int PLMain(const PLCore::String &sExecutableFilename, const PLCore::Array<PLCore::String> &lstArguments) \
	{ \
		return PLCore::Frontend::Run(sExecutableFilename, lstArguments, "PLFrontendOS::Frontend", ApplicationClass); \
	} \
	\
	pl_module_plugin(ModuleName)

/**
*  @brief
*    Defines a frontend for a module inside a plugin library
*
*  @param[in] ModuleName
*    Module name
*  @param[in] ApplicationClass
*    Name of the application RTTI class to use (must be derived from "PLCore::FrontendApplication") [TODO] Currently ignored
*  @param[in] FrontendClass
*    Name of the frontend implementation RTTI class to use (e.g. "PLFrontendOS::Frontend")
*
*  @remarks
*    Use this when you don't want to care about the program entry point.
*/
#define pl_module_application_frontend(ModuleName, ApplicationClass, FrontendClass) \
	int PLMain(const PLCore::String &sExecutableFilename, const PLCore::Array<PLCore::String> &lstArguments) \
	{ \
		return PLCore::Frontend::Run(sExecutableFilename, lstArguments, FrontendClass, ApplicationClass); \
	} \
	\
	pl_module_plugin(ModuleName)


#endif // __PLCORE_FRONTENDMAIN_H__
