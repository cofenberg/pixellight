/*********************************************************\
 *  File: Module.h                                       *
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


#ifndef __PLCORE_MODULE_H__
#define __PLCORE_MODULE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/List.h>
#include <PLGeneral/String/String.h>
#include "PLCore/PLCore.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class DynLib;
}
namespace PLCore {
	class Class;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Description and interface for modules
*
*  @remarks
*    A module is a unit like for example an executable or a shared library that contains RTTI content.
*    There can only be one RTTI module per executable or a shared library. A module can either be a
*    plugin or not. The term plugin means in this case that a module is not explicitly linked to the
*    executable or to a used shared library and therefore not loaded automatically by the operation
*    system on startup.
*/
class Module {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ClassDummy;
	friend class ClassManager;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get module ID
		*
		*  @return
		*    Module ID
		*/
		PLCORE_API PLGeneral::uint32 GetModuleID() const;

		/**
		*  @brief
		*    Check if module is loaded as a plugin
		*
		*  @return
		*    'true' if module is a plugin, else 'false'
		*/
		PLCORE_API bool IsPlugin() const;

		/**
		*  @brief
		*    Get dynamic library that contains the plugin
		*
		*  @return
		*    Pointer to dynamic library (can be a null pointer, if the module is not a plugin, do NOT destroy the returned instance!)
		*
		*  @remarks
		*    This function will only return a dynamic library, if the module is a plugin
		*/
		PLCORE_API PLGeneral::DynLib *GetDynLib() const;

		/**
		*  @brief
		*    Get absolute filename of dynamic library that contains the plugin
		*
		*  @return
		*    Absolute filename of dynamic library (can be empty, if the module is not a plugin)
		*
		*  @remarks
		*    This function will only return an absolute filename, if the module is a plugin
		*/
		PLCORE_API PLGeneral::String GetFilename() const;

		/**
		*  @brief
		*    Get module name
		*
		*  @return
		*    Name
		*/
		PLCORE_API PLGeneral::String GetName() const;

		/**
		*  @brief
		*    Get module vendor
		*
		*  @return
		*    Vendor name
		*/
		PLCORE_API PLGeneral::String GetVendor() const;

		/**
		*  @brief
		*    Get module license
		*
		*  @return
		*    License
		*/
		PLCORE_API PLGeneral::String GetLicense() const;

		/**
		*  @brief
		*    Get module description
		*
		*  @return
		*    Description
		*/
		PLCORE_API PLGeneral::String GetDescription() const;

		/**
		*  @brief
		*    Get classes of module
		*
		*  @return
		*    List of classes
		*
		*  @remarks
		*    This method always returns all classes of a module.
		*    If you want to search for classes with more specific search criteria,
		*    have a look at ClassManager::GetClasses().
		*/
		PLCORE_API const PLGeneral::List<const Class*> &GetClasses() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nModuleID
		*    Module ID
		*/
		PLCORE_API Module(PLGeneral::uint32 nModuleID);

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API ~Module();

		/**
		*  @brief
		*    Set module information
		*
		*  @param[in] sName
		*    Module name
		*  @param[in] sVendor
		*    Module vendor
		*  @param[in] sLicense
		*    Module license
		*  @param[in] sDescription
		*    Module description
		*/
		PLCORE_API void SetModuleInfo(const PLGeneral::String &sName, const PLGeneral::String &sVendor, const PLGeneral::String &sLicense, const PLGeneral::String &sDescription);

		/**
		*  @brief
		*    Add class
		*
		*  @param[in] pClass
		*    Pointer to class (must be valid)
		*/
		PLCORE_API void AddClass(Class *pClass);

		/**
		*  @brief
		*    Remove class
		*
		*  @param[in] pClass
		*    Pointer to class (must be valid)
		*/
		PLCORE_API void RemoveClass(Class *pClass);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Module information
		PLGeneral::uint32			  m_nModuleID;		/**< Module ID */
		bool						  m_bPlugin;		/**< Is module a plugin? */
		PLGeneral::DynLib			 *m_pDynLib;		/**< Plugin library (can be a null pointer, has the ownership over the dynamic library instance) */
		PLGeneral::String			  m_sFilename;		/**< Absolute plugin filename (can be empty) */
		PLGeneral::String			  m_sName;			/**< Name of module */
		PLGeneral::String			  m_sVendor;		/**< Vendor of module */
		PLGeneral::String			  m_sLicense;		/**< License of module */
		PLGeneral::String			  m_sDescription;	/**< Description of module */

		// Classes
		PLGeneral::List<const Class*> m_lstClasses;		/**< List of classes */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_MODULE_H__
