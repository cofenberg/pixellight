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
*/
class ScriptApplication : public BasicSceneApplication {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, ScriptApplication, "PLEngine", PLEngine::BasicSceneApplication, "Script application class")
		// Constructors
		pl_constructor_0(DefaultConstructor,						"Default constructor",														"")
		pl_constructor_1(ConstructorParameter,	PLGeneral::String,	"Constructor with the filename of the script to load as first parameter",	"")
		// Methods
		pl_method_0(GetBaseDirectory,	pl_ret_type(PLGeneral::String),						"Returns the base directory of the application",										"")
		pl_method_1(SetBaseDirectory,	pl_ret_type(void),				PLGeneral::String,	"Sets the base directory of the application, base directory as the first parameter",	"")
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
		*    Constructor
		*
		*  @param[in] sScriptFilename
		*    Filename of the script to load
		*/
		PL_API ScriptApplication(PLGeneral::String sScriptFilename);

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
		PL_API void SetBaseDirectory(PLGeneral::String sBaseDirectory);


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
		*    - Call "OnInit" script function
		*    - Return and go on with Main()
		*/
		PL_API virtual void OnInit();

		/**
		*  @brief
		*    Called when application should de-initialize itself
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Call "OnDeInit" script function
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
		*    - Call "OnUpdate" script function
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
		*    - Calls the script function "OnInit"
		*/
		PL_API bool LoadScript(const PLGeneral::String &sFilename);

		/**
		*  @brief
		*    Destroys the currently used script
		*
		*  @note
		*    - Calls the script function "OnDeInit"
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
