/*********************************************************\
 *  File: SceneContext.h                                 *
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


#ifndef __PLSCENE_SCENECONTEXT_H__
#define __PLSCENE_SCENECONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/Array.h>
#include <PLCore/Base/Event/Event.h>
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class RendererContext;
}
namespace PLMesh {
	class MeshManager;
}
namespace PLInput {
	class Controller;
	class VirtualController;
}
namespace PLScene {
	class SceneNode;
	class VisManager;
	class SceneContainer;
	class SceneNodeHandler;
	class SceneRendererManager;
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
*    Scene context
*/
class SceneContext {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SceneNode;


	//[-------------------------------------------------------]
	//[ Public events                                         ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<PLInput::Controller*, PLGeneral::String> EventInputControllerFound;	/**< An input controller has been found. Use this event to for instance connect the input controller to real input devices. Found input controller as first parameter, input semantic as second parameter. */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRendererContext
		*    Renderer context to use
		*/
		PLS_API SceneContext(PLRenderer::RendererContext &cRendererContext);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API ~SceneContext();

		/**
		*  @brief
		*    Returns the used renderer context
		*
		*  @return
		*    The used renderer context
		*/
		PLS_API PLRenderer::RendererContext &GetRendererContext() const;

		/**
		*  @brief
		*    Returns the mesh manager
		*
		*  @return
		*    The mesh manager
		*/
		PLS_API PLMesh::MeshManager &GetMeshManager();

		/**
		*  @brief
		*    Returns the root of the scene graph
		*
		*  @return
		*    The root of the scene graph, NULL on (terrible) error
		*
		*  @see
		*    - SceneNode and SceneContainer for more information
		*/
		PLS_API SceneContainer *GetRoot();

		/**
		*  @brief
		*    Performs a cleanup-operation
		*
		*  @remarks
		*    If SceneNode::Delete() is called, scene nodes are not destroyed immediately,
		*    instead they register themself into a 'to delete' list of the scene graph. As
		*    soon this function is called, the scene nodes are destroyed. Normally this function
		*    is called once per frame automatically.
		*/
		PLS_API void Cleanup();

		/**
		*  @brief
		*    Returns the scene renderer manager
		*
		*  @return
		*    The scene renderer manager
		*/
		PLS_API SceneRendererManager &GetSceneRendererManager();

		/**
		*  @brief
		*    Returns the visibility manager
		*
		*  @return
		*    The visibility manager
		*/
		PLS_API VisManager &GetVisManager();

		/**
		*  @brief
		*    Get default virtual input controller
		*
		*  @return
		*    Virtual input controller (can be NULL)
		*/
		PLS_API PLInput::VirtualController *GetDefaultInputController() const;

		/**
		*  @brief
		*    Set default virtual input controller
		*
		*  @param[in] pInputController
		*    Virtual input controller (can be NULL)
		*/
		PLS_API void SetDefaultInputController(PLInput::VirtualController *pInputController);


		//[-------------------------------------------------------]
		//[ Processing                                            ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Starts a scene process
		*
		*  @remarks
		*    During scene traversal using for instance the hierarchie of a scene container, a scene node can
		*    be processed multiple times. If this is NOT desired, a scene node must be 'marked' as already
		*    processed so it isn't touched multiple times. The scene graph class offers 3 functions for this
		*    purpose: StartProcess(), TouchNode() and EndProcess(). If a scene process starts, StartProcess()
		*    is called with internally increases a counter. If a node should be processes TouchNode() is called,
		*    if 'true' is retured the node was already processed. After the hole scene process is finished, call
		*    EndProcess(). This is NOT 'multi threading save' and only ONE scene process can be performed at the
		*    same time, but this technique is incredible fast because internally only counters are compared!
		*
		*  @return
		*    'true' if all went fine, else 'false' (there's already a process running)
		*/
		PLS_API bool StartProcess();

		/**
		*  @brief
		*    Checks whether a scene node was touched
		*
		*  @param[in] cSceneNode
		*    Scene node to check
		*
		*  @return
		*    'true' if the scene node was touched, else 'false'
		*
		*  @see
		*    - StartProcess()
		*/
		PLS_API bool IsNodeTouched(SceneNode &cSceneNode) const;

		/**
		*  @brief
		*    Touches a scene node
		*
		*  @param[in] cSceneNode
		*    Scene node to touch
		*
		*  @return
		*    'true' if all went fine and the scene node was touched the first time during the
		*    current process, else 'false' if the scene node was already touched during the current
		*    process or there's currently no active process or the given scene node is invalid
		*
		*  @see
		*    - StartProcess()
		*/
		PLS_API bool TouchNode(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Ends a scene process
		*
		*  @see
		*    - StartProcess()
		*
		*  @return
		*    'true' if all went fine, else 'false' (there's currently no process running)
		*/
		PLS_API bool EndProcess();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::RendererContext  *m_pRendererContext;			/**< The used renderer context, not destroyed by the scene context (always valid!) */
		PLMesh::MeshManager			 *m_pMeshManager;				/**< The mesh manager, can be NULL */
		SceneNodeHandler			 *m_pRoot;						/**< The root of the scene graph (always valid!) */
		PLGeneral::Array<SceneNode*>  m_lstDeleteNodes;				/**< List of scene nodes to delete */
		SceneRendererManager		 *m_pSceneRendererManager;		/**< Scene renderer manager, can be NULL */
		VisManager					 *m_pVisManager;				/**< Visibility manager, can be NULL */
		bool						  m_bProcessActive;				/**< Is there currently an active process? */
		PLGeneral::uint32			  m_nProcessCounter;			/**< Internal process counter */
		PLInput::VirtualController	 *m_pDefaultInputController;	/**< Default input controller, can be NULL */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENECONTEXT_H__
