/*********************************************************\
 *  File: ScriptApplication.h                            *
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


#ifndef __PLENGINE_SCRIPT_APPLICATION_H__
#define __PLENGINE_SCRIPT_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLEngine/Application/BasicSceneApplication.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class Script;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Script application class
*
*  @remarks
*    This class can load in and execute a given script out of the box.
*
*  @note
*    - If a script filename was given to the constructor, the script is started within the "OnInit()"-method
*    - Adds the global variable "this" to the script so that it's able to access "this" RTTI class instance
*/
class ScriptApplication : public BasicSceneApplication {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, ScriptApplication, "PLEngine", PLEngine::BasicSceneApplication, "Script application class")
		// Attributes
		pl_attribute(OnInitFunction,	PLGeneral::String,	"OnInit",	ReadWrite,	DirectValue,	"Name of the optional script function called by C++ when the application should initialize itself",		"")
		pl_attribute(OnUpdateFunction,	PLGeneral::String,	"OnUpdate",	ReadWrite,	DirectValue,	"Name of the optional script function called by C++ when the application should update itself",			"")
		pl_attribute(OnDeInitFunction,	PLGeneral::String,	"OnDeInit",	ReadWrite,	DirectValue,	"Name of the optional script function called by C++ when the application should de-initialize itself",	"")
		#ifdef PLENGINE_EXPORTS	// The following is only required when compiling PLEngine
			// Constructors
			pl_constructor_0(DefaultConstructor,																					"Default constructor",																																																															"")
			pl_constructor_4(ConstructorParameter,	PLGeneral::String,	PLGeneral::String,	PLGeneral::String,	PLGeneral::String,	"Constructor with the filename of the script to load as first parameter, the following parameters name, title and subdirectory for application data files are optional and will be constructed automatically by using the filename of the script if an empty string is given",	"")
			// Methods
			pl_method_0(GetBaseDirectory,	pl_ret_type(PLGeneral::String),								"Returns the base directory of the application",										"")
			pl_method_1(SetBaseDirectory,	pl_ret_type(void),				const PLGeneral::String&,	"Sets the base directory of the application, base directory as the first parameter",	"")
		#endif
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PL_API ScriptApplication();

		/**
		*  @brief
		*    Constructor for loading in and executing a scripted stand-alone application using just a single line of C++ code
		*
		*  @param[in] sScriptFilename
		*    Filename of the script to load
		*  @param[in] sName
		*    Optional name of the application, if empty string a name is constructed automatically by using the filename of the script
		*  @param[in] sTitle
		*    Optional title of the application, if empty string a title is constructed automatically by using the filename of the script
		*  @param[in] sAppDataSubdir
		*    Optional subdirectory for application data files, if empty string a directory is constructed automatically by using the filename of the script
		*
		*  @remarks
		*  @verbatim
		*    Usage example:
		*    int PLMain(const String &sFilename, const Array<String> &lstArguments)
		*    {
		*        return ScriptApplication("Data/Scripts/PLDemoSimpleScene.lua").Run(sFilename, lstArguments);
		*    }
		*  @endverbatim
		*/
		PL_API ScriptApplication(PLGeneral::String sScriptFilename, PLGeneral::String sName = "", PLGeneral::String sTitle = "", PLGeneral::String sAppDataSubdir = "");

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~ScriptApplication();

		/**
		*  @brief
		*    Returns the base directory of the application
		*
		*  @return
		*    The base directory of the application
		*/
		PL_API PLGeneral::String GetBaseDirectory() const;

		/**
		*  @brief
		*    Sets the base directory of the application
		*
		*  @param[in] sBaseDirectory
		*    The base directory of the application
		*/
		PL_API void SetBaseDirectory(const PLGeneral::String &sBaseDirectory);


	//[-------------------------------------------------------]
	//[ Protected virtual PLCore::ConsoleApplication functions]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called when application should initialize itself
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Everything that BasicSceneApplication::OnInit() does
		*    - Load the script given to the constructor
		*    - Call optional <OnInitFunction> script function
		*    - Return and go on with Main()
		*/
		PL_API virtual void OnInit();

		/**
		*  @brief
		*    Called when application should de-initialize itself
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Call optional <OnDeInitFunction> script function
		*    - Destroy the script
		*    - Everything that BasicSceneApplication::OnDeInit() does
		*/
		PL_API virtual void OnDeInit();


	//[-------------------------------------------------------]
	//[ Protected virtual RenderApplication functions         ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Function that is called once per update loop
		*
		*  @return
		*    'true' when the update was performed, else 'false'
		*    (an implementation has blocked the update due some own criterion)
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Call optional <OnUpdateFunction> script function
		*    - Everything that BasicSceneApplication::OnUpdate() does
		*/
		PL_API virtual bool OnUpdate();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Loads a script
		*
		*  @param[in] sFilename
		*    Filename of the script to load
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - Calls the optional script function <OnInitFunction>
		*/
		PL_API bool LoadScript(const PLGeneral::String &sFilename);

		/**
		*  @brief
		*    Destroys the currently used script
		*
		*  @note
		*    - Calls the optional script function <OnDeInitFunction>
		*/
		PL_API void DestroyScript();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::String	 m_sCurrentSceneBaseDirectory;	/**< Base directory of the currently loaded scene */
		PLGeneral::String	 m_sScriptFilename;				/**< Filename of the used script */
		PLCore::Script		*m_pScript;						/**< Used script instance, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_SCRIPT_APPLICATION_H__
