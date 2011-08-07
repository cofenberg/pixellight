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


#ifndef __PLSCENE_APPLICATION_H__
#define __PLSCENE_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Application/RendererApplication.h>
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLScene {
	class SceneContext;
	class SceneContainer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene application class
*
*  @remarks
*    An application class that provides a scene graph for rendering
*
*  @note
*    - The 'OnCreatePainter()'-implementation creates a 'SPScene' surface painter
*/
class SceneApplication : public PLRenderer::RendererApplication {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SceneApplication, "PLScene", PLRenderer::RendererApplication, "Scene application class")
		#ifdef PLSCENE_EXPORTS	// The following is only required when compiling PLScene
			// Constructors
			pl_constructor_1(ParameterConstructor,	PLCore::Frontend&,	"Parameter constructor. Frontend this application instance is running in as first parameter.",	"")
			// Methods
			pl_method_0(GetRootScene,	pl_ret_type(PLScene::SceneContainer*),	"Returns the root scene container, can be a null pointer.",	"")
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
		*  @param[in] cFrontend
		*    Frontend this application instance is running in
		*  @param[in] sSceneFilename
		*    Filename of the scene to load
		*/
		PLS_API SceneApplication(PLCore::Frontend &cFrontend, const PLCore::String &sSceneFilename = "");

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SceneApplication();

		/**
		*  @brief
		*    Returns the scene context
		*
		*  @return
		*    The scene context, a null pointer on error
		*/
		PLS_API PLScene::SceneContext *GetSceneContext() const;

		/**
		*  @brief
		*    Returns the root scene
		*
		*  @return
		*    Pointer to root scene container, can be a null pointer
		*/
		PLS_API PLScene::SceneContainer *GetRootScene() const;


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
		PLS_API void SetRootScene(PLScene::SceneContainer *pSceneContainer);


	//[-------------------------------------------------------]
	//[ Protected virtual PLCore::AbstractLifecycle functions ]
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
		*    - Everything that PLRenderer::RendererApplication::OnStart() does
		*    - Create scene context
		*    - Call OnCreateRootScene()
		*    - Return and go on with OnInit()
		*/
		PLS_API virtual bool OnStart() override;

		/**
		*  @brief
		*    De-initialization function that is called after OnDeInit()
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Destroy scene context
		*    - Everything that PLRenderer::RendererApplication::OnStop() does
		*/
		PLS_API virtual void OnStop() override;


	//[-------------------------------------------------------]
	//[ Protected virtual PLCore::AbstractFrontend functions  ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called to let the frontend update it's states
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Everything that PLRenderer::RendererApplication::OnUpdate() does
		*    - Update the scene context
		*/
		PLS_API virtual void OnUpdate() override;


	//[-------------------------------------------------------]
	//[ Protected virtual SceneApplication functions          ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Function that is called to create the application's root scene
		*
		*  @note
		*    - Part of the application framework initialization function "OnStart()"
		*    - The default implementation creates a standard root scene
		*/
		PLS_API virtual void OnCreateRootScene();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLScene::SceneContext	*m_pSceneContext;	/**< The scene context, can be a null pointer */
		PLScene::SceneContainer	*m_pRootScene;		/**< Root scene (can be a null pointer) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENE_APPLICATION_H__
