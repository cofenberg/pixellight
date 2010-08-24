/*********************************************************\
 *  File: ClassManager.h                                 *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLCORE_CLASSMANAGER_H__
#define __PLCORE_CLASSMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Base/Singleton.h>
#include <PLGeneral/String/String.h>
#include <PLGeneral/Container/List.h>
#include <PLGeneral/Container/HashMap.h>
#include "PLCore/PLCoreDefinitions.h"
#include "PLCore/Base/Event/Event.h"


//[-------------------------------------------------------]
//[ Template instance                                     ]
//[-------------------------------------------------------]
namespace PLCore {
	class ClassManager;
}
PLCORE_TEMPLATE template class PLCORE_API PLGeneral::Singleton<PLCore::ClassManager>;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <typename T> class ModuleID;
class Module;
class Class;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Manager providing access to RTTI classes
*/
class ClassManager : public PLGeneral::Singleton<ClassManager> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLGeneral::Singleton<ClassManager>;
	friend class ModuleID<int>;
	friend class Class;


	//[-------------------------------------------------------]
	//[ Public events                                         ]
	//[-------------------------------------------------------]
	public:
		Event<const Module*> EventModuleLoaded;		/**< A module has been registered */
		Event<const Module*> EventModuleUnloaded;	/**< A module has been removed */
		Event<const Class*>	 EventClassLoaded;		/**< A class has been registered. Please note: At the time you receive this event, the class may not yet be fully initialized, this means that even "IsDerivedFrom" may not work, yet. */
		Event<const Class*>  EventClassUnloaded;	/**< A class has been removed */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get all registered modules
		*
		*  @return
		*    List of modules
		*/
		PLCORE_API const PLGeneral::List<const Module*> &GetModules() const;

		/**
		*  @brief
		*    Get module by ID
		*
		*  @param[in] nModuleID
		*    Module ID
		*
		*  @return
		*    Pointer to module (can be NULL)
		*/
		PLCORE_API const Module *GetModule(PLGeneral::uint32 nModuleID) const;

		/**
		*  @brief
		*    Scan a directory for compatible plugins and load them in
		*
		*  @param[in] sPath
		*    Directory to search in
		*  @param[in] nRecursive
		*    Also take sub-directories into account?
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*     This function scans for '.plugin'-files and registers the plugins if all went fine.
		*/
		PLCORE_API bool ScanPlugins(const PLGeneral::String &sPath, ERecursive nRecursive = Recursive);

		/**
		*  @brief
		*    Load plugin
		*
		*  @param[in] sFilename
		*    Filename of the plugin (must be a '.plugin'-file!)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool LoadPlugin(const PLGeneral::String &sFilename);

		/**
		*  @brief
		*    Unload plugin
		*
		*  @param[in] pModule
		*    Module to unload (must be valid!)
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe the module is static)
		*
		*  @note
		*    - You can only unload plugins modules, other modules will be ignored
		*/
		PLCORE_API bool UnloadPlugin(Module *pModule);

		/**
		*  @brief
		*    Unload all plugins
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool UnloadAllPlugins();

		/**
		*  @brief
		*    Get all registered classes
		*
		*  @return
		*    List of classes
		*/
		PLCORE_API const PLGeneral::List<const Class*> &GetClasses() const;

		/**
		*  @brief
		*    Get classes based on their base class and/or module (search for classes)
		*
		*  @param[out] lstClasses
		*    List that recieves the found classes
		*  @param[in] sClass
		*    Name of base class (with namespace)
		*  @param[in] nRecursive
		*    'Recursive' to list all subclasses of the base class, 'NonRecursive' to only list direct subclasses
		*  @param[in] nIncludeBase
		*    'IncludeBase' to include the base class itself, 'NoBase' to exclude it
		*  @param[in] nIncludeAbstract
		*    'IncludeAbstract' to include classes without a constructor, 'NoAbstract' to exlude them
		*  @param[in] nModuleID
		*    ID of module, or 0 to include the classes from all modules
		*
		*  @remarks
		*    The found classes will be added to the list that is passed as the first argument to the function.
		*    The class list is not automatically cleared by this function.
		*/
		PLCORE_API void GetClasses(PLGeneral::List<const Class*> &lstClasses, const PLGeneral::String &sClass, ERecursive nRecursive = Recursive, EIncludeBase nIncludeBase = IncludeBase, EIncludeAbstract nIncludeAbstract = IncludeAbstract, PLGeneral::uint32 nModuleID = 0) const;

		/**
		*  @brief
		*    Get class
		*
		*  @param[in] sClass
		*    Class name
		*
		*  @return
		*    Pointer to the class, or NULL on error
		*/
		PLCORE_API const Class *GetClass(const PLGeneral::String &sClass) const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API ClassManager();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~ClassManager();

		/**
		*  @brief
		*    Get a unique module ID
		*
		*  @return
		*    Unique module ID for a new module
		*/
		PLCORE_API PLGeneral::uint32 GetUniqueModuleID();

		/**
		*  @brief
		*    Create module
		*
		*  @param[in] nModuleID
		*    Module ID
		*
		*  @return
		*    Module belonging to that ID
		*
		*  @remarks
		*    If a module with that ID already exists, the function will return a pointer to it.
		*    Otherwise it will create a new module and assign it to the given ID.
		*/
		PLCORE_API Module *CreateModule(PLGeneral::uint32 nModuleID);

		/**
		*  @brief
		*    Register module
		*
		*  @param[in] nModuleID
		*    Module ID
		*  @param[in] sName
		*    Module name
		*  @param[in] sVendor
		*    Vendor name
		*  @param[in] sLicense
		*    Module license
		*  @param[in] sDescription
		*    Module description
		*/
		PLCORE_API void RegisterModule(PLGeneral::uint32 nModuleID, const PLGeneral::String &sName, const PLGeneral::String &sVendor, const PLGeneral::String &sLicense, const PLGeneral::String &sDescription);

		/**
		*  @brief
		*    Unregister module
		*
		*  @param[in] pModule
		*    Module (must be valid!)
		*/
		PLCORE_API void UnregisterModule(Module *pModule);

		/**
		*  @brief
		*    Register class
		*
		*  @param[in] nModuleID
		*    Module ID
		*  @param[in] pClass
		*    Pointer to class (must be valid)
		*/
		PLCORE_API void RegisterClass(PLGeneral::uint32 nModuleID, Class *pClass);

		/**
		*  @brief
		*    Unregister class
		*
		*  @param[in] nModuleID
		*    Module ID
		*  @param[in] pClass
		*    Pointer to class (must be valid)
		*/
		PLCORE_API void UnregisterClass(PLGeneral::uint32 nModuleID, Class *pClass);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Modules
		PLGeneral::uint32									 m_nModuleID;	/**< Module ID counter */
		PLGeneral::List<const Module*>						 m_lstModules;	/**< List of all modules */
		PLGeneral::HashMap<PLGeneral::uint32, const Module*> m_mapModules;	/**< Hash-map of module IDs to modules */

		// Classes
		PLGeneral::List<const Class*>						 m_lstClasses;	/**< List of all classes */
		PLGeneral::HashMap<PLGeneral::String, const Class*>	 m_mapClasses;	/**< Hash-map of class names to classes (with namespace) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CLASSMANAGER_H__
