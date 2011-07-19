/*********************************************************\
 *  File: ModuleMain.h                                   *
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


#ifndef __PLCORE_MODULEMAIN_H__
#define __PLCORE_MODULEMAIN_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Core/MemoryManager.inl"	// By adding this in here, usually every PixelLight basing project will add automatically the correct memory manager features
#include "PLCore/Base/Rtti.h"


//[-------------------------------------------------------]
//[ Macros                                                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Defines a module inside an application or library
*
*  @param[in] Name
*    Module name
*
*  @remarks
*    Use this in applications or libraries that are linked
*    directly to the main project (statically or dynamically),
*    but not inside a dynamically loaded plugin library.
*/
#define pl_module(Name) \
	class ModuleInfo { \
		public: \
			ModuleInfo() { \
				ModuleInfo::Register(); \
			} \
		private: \
			static void Register() \
			{ \
				PLCore::String sName        = Name; \
				PLCore::String sVendor      = "Unknown"; \
				PLCore::String sLicense     = "Unknown"; \
				PLCore::String sDescription = "Unknown module"; \

/**
*  @brief
*    Defines a module inside a plugin library
*
*  @param[in] Name
*    Module name
*
*  @remarks
*    Use this in a library that is dynamically loaded as a plugin
*/
#define pl_module_plugin(Name) \
	extern "C" PLCORE_PLUGIN_API bool PLIsPluginDebugBuild() \
	{ \
		return PLCORE_IS_DEBUGMODE; \
	} \
	\
	extern "C" PLCORE_PLUGIN_API int PLGetPluginInfo() \
	{ \
		return PLCore::ModuleID<int>::GetModuleID(); \
	} \
	\
	pl_module(Name) \

/**
*  @brief
*    Sets the module vendor name
*
*  @param[in] Vendor
*    Vendor name
*/
#define pl_module_vendor(Vendor) \
			sVendor = Vendor; \

/**
*  @brief
*    Sets the module license
*
*  @param[in] License
*    License
*/
#define pl_module_license(License) \
			sLicense = License; \

/**
*  @brief
*    Sets the module description
*
*  @param[in] Description
*    Module description
*/
#define pl_module_description(Description) \
			sDescription = Description; \

/**
*  @brief
*    Sets the module version
*
*  @param[in] Version
*    Version string
*/
#define pl_module_version(Version)

/**
*  @brief
*    Sets the module dependencies for Win32 release mode
*
*  @param[in] Dependencies
*    Module dependencies
*/
#define pl_module_dependencies_win32_release(Dependencies)

/**
*  @brief
*    Sets the module dependencies for Win32 debug mode
*
*  @param[in] Dependencies
*    Module dependencies
*/
#define pl_module_dependencies_win32_debug(Dependencies)

/**
*  @brief
*    Sets the module dependencies for Win64 release mode
*
*  @param[in] Dependencies
*    Module dependencies
*/
#define pl_module_dependencies_win64_release(Dependencies)

/**
*  @brief
*    Sets the module dependencies for Win64 debug mode
*
*  @param[in] Dependencies
*    Module dependencies
*/
#define pl_module_dependencies_win64_debug(Dependencies)

/**
*  @brief
*    Sets the module dependencies for Linux release mode
*
*  @param[in] Dependencies
*    Module dependencies
*/
#define pl_module_dependencies_linux_release(Dependencies)

/**
*  @brief
*    Sets the module dependencies for Linux debug mode
*
*  @param[in] Dependencies
*    Module dependencies
*/
#define pl_module_dependencies_linux_debug(Dependencies)

/**
*  @brief
*    Sets the module's default active state
*
*  @param[in] Active
*    Default active state (1 or 0)
*
*  @note
*    - If not other defined, modules are active by default
*/
#define pl_module_active(Active)

/**
*  @brief
*    Sets the module's default delayed shared library loading state
*
*  @param[in] Delayed
*    Default delayed shared library loading state (1 or 0)
*
*  @note
*    - If not other defined, modules are loading their shared libraries delayed by default
*/
#define pl_module_delayed(Delayed)

/**
*  @brief
*    Ends the module definition
*/
#define pl_module_end \
			PLCore::ModuleID<int>::RegisterModule(sName, sVendor, sLicense, sDescription); \
		} \
	}; \
	\
	ModuleInfo __ModuleInfo;


#endif // __PLCORE_MODULEMAIN_H__
