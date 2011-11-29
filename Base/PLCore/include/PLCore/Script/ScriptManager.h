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
	//[ Public static PLCore::Singleton functions             ]
	//[-------------------------------------------------------]
	// This solution enhances the compability with legacy compilers like GCC 4.2.1 used on Mac OS X 10.6
	// -> The C++11 feature "extern template" (C++11, see e.g. http://www2.research.att.com/~bs/C++0xFAQ.html#extern-templates) can only be used on modern compilers like GCC 4.6
	// -> We can't break legacy compiler support, especially when only the singletons are responsible for the break
	// -> See PLCore::Singleton for more details about singletons
	public:
		static PLCORE_API ScriptManager *GetInstance();
		static PLCORE_API bool HasInstance();


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
		*  @param[in] nStringFormat
		*    String encoding format to use when dealing with string functions (not supported by all file implementations)
		*
		*  @return
		*    The created script instance, null pointer on error (Unknown filename extension? File not found? Error within the script?)
		*
		*  @remarks
		*    While the "Create()"-method only creates an empty script instance, the "CreateFromFile()"-method will
		*    - Create an empty script instance by using the filename extension as indication of the script language to use
		*    - Load in the script source code by using the given script filename
		*    - Assign the loaded script source code to the created, previously empty, script
		*    The result is a ready to be used script by just using this one method. The drawback is, that you can't use
		*    custom global functions when using this method because the custom global functions have to be defined before
		*    the script source code is assigned to the script (resulting in script compilation).
		*
		*  @note
		*    - Convenience method
		*    - It's not recommended to use Unicode by because internally wchar_t is used and this data type has not
		*      the same size on every platform (use ASCII or UTF8 instead)
		*/
		PLCORE_API Script *CreateFromFile(const String &sFilename, bool bAddBindings = true, String::EFormat nStringFormat = String::ASCII);


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


#endif // __PLCORE_SCRIPTMANAGER_H__
