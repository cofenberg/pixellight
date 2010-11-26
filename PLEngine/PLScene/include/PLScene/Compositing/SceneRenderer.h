/*********************************************************\
 *  File: SceneRenderer.h                                *
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


#ifndef __PLSCENE_COMPOSITING_SCENERENDERER_H__
#define __PLSCENE_COMPOSITING_SCENERENDERER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/Resource.h>
#include "PLScene/Compositing/SceneRendererPass.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class SceneRendererManager;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene renderer class
*
*  @remarks
*    A scene renderer 'just' renders the scene visibility tree provided by the scene cull query. (SQCull)
*    Quite primive scene renderers can be implemented completely within one scene renderer class.
*    If a lot of special effects and so one are required, we strongly recommend to split up the rendering into
*    multiple self-containing rendering passes. Have a look into the 'SceneRendererPass' class documentation
*    for more information about this topic.
*
*  @note
*    - Derived classes should use a 'SR'-prefix (example: SRBegin)
*    - Prefer creating new scene renderer passes instead of scene renderer
*/
class SceneRenderer : public PLCore::Resource<SceneRenderer>, public PLGeneral::ElementManager<SceneRendererPass> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SPScene;
	friend class SceneRendererManager;
	friend class PLCore::ResourceManager<SceneRenderer>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the scene renderer manager this scene renderer is in
		*
		*  @return
		*     The scene renderer manager this shader is in
		*/
		PLS_API SceneRendererManager &GetSceneRendererManager() const;

		/**
		*  @brief
		*    Creates a new scene renderer pass
		*
		*  @param[in] sClass
		*    Name of the scene renderer pass class to create an instance from
		*  @param[in] sName
		*    Scene renderer pass name
		*  @param[in] sParameters
		*    Optional parameter string
		*
		*  @return
		*    Pointer to the new scene renderer pass or NULL if something went wrong
		*    (maybe unknown class or the class is not derived from SceneRendererPass)
		*
		*  @note
		*    - If the desired name is already in use, the name is chosen automatically
		*/
		PLS_API SceneRendererPass *Create(const PLGeneral::String &sClass, const PLGeneral::String &sName = "",
										 const PLGeneral::String &sParameters = "");


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cManager
		*    Scene renderer manager using this resource
		*  @param[in] sName
		*    Resource name to set
		*/
		PLS_API SceneRenderer(SceneRendererManager &cManager, const PLGeneral::String &sName);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SceneRenderer();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Draws the scene using this scene renderer
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cCullQuery
		*    Cull scene query to use
		*/
		PLS_API virtual void DrawScene(PLRenderer::Renderer &cRenderer, const SQCull &cCullQuery);


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Loadable functions             ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual bool Unload();
		PLS_API virtual PLGeneral::String GetLoadableTypeName() const;


	//[-------------------------------------------------------]
	//[ Private virtual PLGeneral::ElementManager functions   ]
	//[-------------------------------------------------------]
	private:
		PLS_API virtual SceneRendererPass *CreateElement(const PLGeneral::String &sName);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_COMPOSITING_SCENERENDERER_H__
