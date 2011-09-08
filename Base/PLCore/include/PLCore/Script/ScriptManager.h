/*********************************************************\
 *  File: ScriptManager.h                                *
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


#ifndef __PLCORE_SCRIPTMANAGER_H__
#define __PLCORE_SCRIPTMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Core/Singleton.h"
#include "PLCore/Container/Array.h"
#include "PLCore/Container/HashMap.h"
#include "PLCore/Base/Event/EventHandler.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Class;
class Script;
class ScriptBinding;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Script manager
*/
class ScriptManager : public Singleton<ScriptManager> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Singleton<ScriptManager>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns a list of the names of the supported script languages
		*
		*  @return
		*    List of the names of the supported script languages
		*/
		PLCORE_API const Array<String> &GetScriptLanguages();

		/**
		*  @brief
		*    Returns the name of a script language by it's filename extension
		*
		*  @param[in] sExtension
		*    Script language filename extension to check (e.g. "js")
		*
		*  @return
		*    Script language, empty string on error (possibly not supported filename extension)
		*/
		PLCORE_API String GetScriptLanguageByExtension(const String &sExtension);

		/**
		*  @brief
		*    Checks whether or not a given script language is supported
		*
		*  @param[in] sScriptLanguage
		*    Script language to check
		*
		*  @return
		*    'true' if the given script language is supported, else 'false'
		*/
		PLCORE_API bool IsSupported(const String &sScriptLanguage);

		/**
		*  @brief
		*    Returns the filename extension of a given script language
		*
		*  @param[in] sScriptLanguage
		*    Script language to return the filename extension from
		*
		*  @return
		*    The filename extension of the given script language, empty string on error (possibly not supported script language)
		*
		*  @note
		*    - If the script language has more than one filename extension, the first filename extension will be returned
		*/
		PLCORE_API String GetScriptLanguageExtension(const String &sScriptLanguage);

		/**
		*  @brief
		*    Returns a list of all script binding instances
		*
		*  @return
		*    List of all script binding instances
		*/
		PLCORE_API const Array<ScriptBinding*> &GetScriptBindings();

		/**
		*  @brief
		*    Creates a script instance
		*
		*  @param[in] sScriptLanguage
		*    Script language to use
		*  @param[in] bAddBindings
		*    If 'true', add all available script bindings automatically (see "Script::AddBindings()")
		*
		*  @return
		*    The created script instance, null pointer on error
		*/
		PLCORE_API Script *Create(const String &sScriptLanguage, bool bAddBindings = true);

		/**
		*  @brief
		*    Creates a script instance by using a given filename
		*
		*  @param[in] sFilename
		*    Script filename
		*  @param[in] bAddBindings
		*    If 'true', add all available script bindings automatically (see "Script::AddBindings()")
		*
		*  @return
		*    The created script instance, null pointer on error (Unknown filename extension? File not found? Error within the script?)
		*
		*  @note
		*    - Convenience method
		*/
		PLCORE_API Script *CreateFromFile(const String &sFilename, bool bAddBindings = true);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API ScriptManager();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~ScriptManager();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Register a class
		*
		*  @param[in] pClass
		*    Class to register, must be valid!
		*
		*  @note
		*    - If the class is not derived from 'PLCore::Script' it is ignored
		*    - The given class must be a new one, so this function did not check whether the
		*      class is already registered
		*/
		void OnClassLoaded(const Class *pClass);

		/**
		*  @brief
		*    Registers queued classes
		*/
		void RegisterClasses();


	//[-------------------------------------------------------]
	//[ Private slots                                         ]
	//[-------------------------------------------------------]
	private:
		EventHandler<const Class*> SlotClassLoaded;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Array<const Class*>				m_lstNewClasses;					/**< New classes to register as soon as required */
		// Script languages
		Array<String>					m_lstScriptLanguages;				/**< List of script languages */
		HashMap<String, const Class*>	m_mapScriptLanguages;				/**< Map of script languages (key = class name) */
		HashMap<String, String>			m_mapScriptLanguagesByExtension;	/**< Map of script languages by extension (key = extension) */
		// Script bindings
		Array<ScriptBinding*>			m_lstScriptBindings;				/**< List of script bindings */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Template instance                                     ]
//[-------------------------------------------------------]
PLCORE_TEMPLATE template class PLCore::Singleton<PLCore::ScriptManager>;


#endif // __PLCORE_SCRIPTMANAGER_H__
