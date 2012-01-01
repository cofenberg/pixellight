/*********************************************************\
 *  File: Module.h                                       *
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


#ifndef __PLCORE_MODULE_H__
#define __PLCORE_MODULE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/String.h"
#include "PLCore/Container/List.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Class;
class DynLib;


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
		inline uint32 GetModuleID() const;

		/**
		*  @brief
		*    Check if module is loaded as a plugin
		*
		*  @return
		*    'true' if module is a plugin, else 'false'
		*/
		inline bool IsPlugin() const;

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
		inline DynLib *GetDynLib() const;

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
		inline String GetFilename() const;

		/**
		*  @brief
		*    Get module name
		*
		*  @return
		*    Name
		*/
		inline String GetName() const;

		/**
		*  @brief
		*    Get module vendor
		*
		*  @return
		*    Vendor name
		*/
		inline String GetVendor() const;

		/**
		*  @brief
		*    Get module license
		*
		*  @return
		*    License
		*/
		inline String GetLicense() const;

		/**
		*  @brief
		*    Get module description
		*
		*  @return
		*    Description
		*/
		inline String GetDescription() const;

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
		inline const List<const Class*> &GetClasses() const;


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
		PLCORE_API Module(uint32 nModuleID);

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
		PLCORE_API void SetModuleInfo(const String &sName, const String &sVendor, const String &sLicense, const String &sDescription);

		/**
		*  @brief
		*    Add class
		*
		*  @param[in] pClass
		*    Pointer to class (must be valid)
		*/
		inline void AddClass(const Class *pClass);

		/**
		*  @brief
		*    Remove class
		*
		*  @param[in] pClass
		*    Pointer to class (must be valid)
		*/
		inline void RemoveClass(const Class *pClass);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Module information
		uint32			   m_nModuleID;		/**< Module ID */
		bool			   m_bPlugin;		/**< Is module a plugin? */
		DynLib			  *m_pDynLib;		/**< Plugin library (can be a null pointer, has the ownership over the dynamic library instance) */
		String			   m_sFilename;		/**< Absolute plugin filename (can be empty) */
		String			   m_sName;			/**< Name of module */
		String			   m_sVendor;		/**< Vendor of module */
		String			   m_sLicense;		/**< License of module */
		String			   m_sDescription;	/**< Description of module */
		// Classes
		List<const Class*> m_lstClasses;	/**< List of classes */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Base/Module.inl"


#endif // __PLCORE_MODULE_H__
