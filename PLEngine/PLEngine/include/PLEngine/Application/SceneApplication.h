/*********************************************************\
 *  File: SceneApplication.h                             *
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


#ifndef __PLENGINE_SCENE_APPLICATION_H__
#define __PLENGINE_SCENE_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Gui/WidgetHandler.h>
#include "PLEngine/Application/RenderApplication.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLInput {
	class Controller;
}
namespace PLScene {
	class SceneContext;
	class ConsoleCommand;
	class SceneContainer;
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
*    Scene application class
*
*  @remarks
*    An application class that provides a scene graph for rendering as well as a generic edit-dialog.
*
*  @note
*    - The 'OnCreatePainter()'-implementation creates a 'SPScene' surface painter
*/
class SceneApplication : public RenderApplication {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, SceneApplication, "PLEngine", PLEngine::RenderApplication, "Scene application class")
		#ifdef PLENGINE_EXPORTS	// The following is only required when compiling PLEngine
			// Constructors
			pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
			// Methods
			pl_method_0(GetRootScene,	pl_ret_type(PLScene::SceneContainer*),	"Returns the root scene container, can be a null pointer",	"")
		#endif
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sSceneFilename
		*    Filename of the scene to load
		*/
		PL_API SceneApplication(const PLGeneral::String &sSceneFilename = "");

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~SceneApplication();

		/**
		*  @brief
		*    Returns the scene context
		*
		*  @return
		*    The scene context, a null pointer on error
		*/
		PL_API PLScene::SceneContext *GetSceneContext() const;

		/**
		*  @brief
		*    Returns the root scene
		*
		*  @return
		*    Pointer to root scene container, can be a null pointer
		*/
		PL_API PLScene::SceneContainer *GetRootScene() const;

		//[-------------------------------------------------------]
		//[ Edit functions                                        ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns whether or not edit mode is enabled
		*
		*  @return
		*    'true' if edit mode is enabled, else 'false'
		*
		*  @remarks
		*    This class introduces some generic edit features which are enabled by default. For public release
		*    versions you may disable the edit mode so users can't for example use edit features to chat.
		*/
		PL_API bool IsEditModeEnabled() const;

		/**
		*  @brief
		*    Sets whether or not edit mode is enabled
		*
		*  @param[in] bEnabled
		*    'true' if edit mode is enabled, else 'false'
		*
		*  @remarks
		*    If edit mode is disabled, this function will automatically close the edit dialog if it's currently
		*    opened. Also the scene nodes 'SNEngineInformation0' and 'SNConsole0' from the root scene are enabled/disabled.
		*    By default, edit mode is enabled.
		*
		*  @see
		*    - IsEditModeEnabled()
		*/
		PL_API void SetEditModeEnabled(bool bEnabled = true);

		/**
		*  @brief
		*    Returns whether the edit dialog is currently opened or not
		*
		*  @return
		*    'true' if the edit dialog is currently opened, else 'false'
		*
		*  @see
		*    - IsEditModeEnabled()
		*/
		PL_API bool IsEditDialogOpend();

		/**
		*  @brief
		*    Opens the edit dialog
		*
		*  @param[in] pParent
		*    Parent widget, can be a null pointer
		*
		*  @note
		*    - Can only be opened if edit mode is enabled!
		*
		*  @see
		*    - IsEditModeEnabled()
		*/
		PL_API void OpenEditDialog(PLGui::Widget *pParent = nullptr);

		/**
		*  @brief
		*    Closes the edit dialog
		*
		*  @return
		*    'true' if the edit dialog was closed, else 'false'
		*
		*  @see
		*    - IsEditModeEnabled()
		*/
		PL_API bool CloseEditDialog();

		//[-------------------------------------------------------]
		//[ Console functions                                     ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Quit the engine
		*
		*  @param[in] cCommand
		*    Calling command
		*/
		PL_API void ConsoleCommandQuit(PLScene::ConsoleCommand &cCommand);

		/**
		*  @brief
		*    Opens the engine edit dialog and deactivates the owner console automatically
		*
		*  @param[in] cCommand
		*    Calling command
		*/
		PL_API void ConsoleCommandEditDialog(PLScene::ConsoleCommand &cCommand);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Set root scene
		*
		*  @param[in] pSceneContainer
		*    Pointer to root scene container, can be a null pointer
		*/
		PL_API void SetRootScene(PLScene::SceneContainer *pSceneContainer);


	//[-------------------------------------------------------]
	//[ Protected virtual ConsoleApplication functions        ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Initialization function that is called prior to OnInit()
		*
		*  @return
		*    'true' if all went fine, else 'false' which will stop the application
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Everything that RenderApplication::Init() does
		*    - Create scene context
		*    - Set default virtual input controller of scene context
		*    - Call OnCreateRootScene()
		*    - Return and go on with OnInit()
		*/
		PL_API virtual bool Init();

		/**
		*  @brief
		*    De-initialization function that is called after OnDeInit()
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Close edit dialog
		*    - Destroy scene context
		*    - Everything that RenderApplication::DeInit() does
		*/
		PL_API virtual void DeInit();


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
		*    - Update the scene context
		*    - Everything that RenderApplication::OnUpdate() does
		*/
		PL_API virtual bool OnUpdate();


	//[-------------------------------------------------------]
	//[ Protected virtual SceneApplication functions          ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Function that is called to create the application's root scene
		*
		*  @note
		*    - Part of the application framework initialization function "Init()"
		*    - The default implementation creates a standard root scene
		*/
		PL_API virtual void OnCreateRootScene();

		/**
		*  @brief
		*    Function that is called when an input controller has been found
		*
		*  @param[in] pInputController
		*    Found input controller, always valid
		*  @param[in] sInputSemantic
		*    Purpose of this input controller
		*
		*  @remarks
		*    Use this virtual method for instance to connect the input controller to real input devices.
		*
		*  @note
		*    - Connected to the "PLScene::SceneContext::EventInputControllerFound"-event
		*    - The default implementation tries to connect all controls automatically with the virtual standard controller
		*/
		PL_API virtual void OnInputControllerFound(PLInput::Controller *pInputController, PLGeneral::String sInputSemantic);


	//[-------------------------------------------------------]
	//[ Protected event handlers                              ]
	//[-------------------------------------------------------]
	protected:
		PLCore::EventHandler<PLInput::Controller*, PLGeneral::String> EventHandlerInputControllerFound;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLScene::SceneContext	*m_pSceneContext;		/**< The scene context, can be a null pointer */
		PLScene::SceneContainer	*m_pRootScene;			/**< Root scene (can be a null pointer) */
		bool					 m_bEditModeEnabled;	/**< Edit mode enabled? */
		PLGui::WidgetHandler	 m_cEditDialog;			/**< Edit dialog handler */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_SCENE_APPLICATION_H__
