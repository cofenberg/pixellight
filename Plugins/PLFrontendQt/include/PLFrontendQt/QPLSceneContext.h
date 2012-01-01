/*********************************************************\
 *  File: QPLSceneContext.h                              *
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


#ifndef __PLFRONTENDQT_QPLSCENECONTEXT_H__
#define __PLFRONTENDQT_QPLSCENECONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLFrontendQt/QPLContext.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLScene {
	class SNCamera;
	class SceneNode;
	class SceneQuery;
	class SceneContext;
	class SceneContainer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
class PLFRONTENDQT_API QPLSceneContext : public QPLContext {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Qt signals (MOC)                                      ]
	//[-------------------------------------------------------]
	signals:
		void SceneChanged();


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		QPLSceneContext(const QString& sPainterName = "PLScene::SPScene", PLRenderer::RendererContext* pRendererContext = nullptr);
		virtual ~QPLSceneContext();
		virtual void Update() override;
		virtual PLRenderer::SurfacePainter* CreateSurfacePainter() override;
		void InitScene();
		PLScene::SceneContext* GetSceneContext();
		PLScene::SceneContainer* GetScene();
		PLScene::SceneContainer* GetRootScene();
		PLScene::SceneNode* GetNodeFromScene(const PLCore::String &nodeName);
		void UpdateSceneContext();
		bool LoadSceneFromFile(const QString& sSceneFile);
		PLScene::SNCamera* GetCamera() { return m_pCamera; }
		void SetSceneRenderer(const PLCore::String & sSceneRenderer);
		const PLCore::String& GetSceneRenderer();


	protected:
		virtual void OnCreateScene(PLScene::SceneContainer& cContainer) { SetScene(&cContainer); };
		void SetCamera(PLScene::SNCamera *pCamera);
		void SetScene(PLScene::SceneContainer *pScene) {
			m_pScene = pScene;
		}
		
		// makes an cleanup on the pl scene context
		void PLSceneContextCleanUp();


	private:
		void CreateRootScene();
		void SetRootScene(PLScene::SceneContainer *pRootScene);


	private:
		/**
		*  @brief
		*    Called when a scene node was found
		*
		*  @param[in] cQuery
		*    Query found the scene node
		*  @param[in] cSceneNode
		*    Found scene node
		*/
		void OnSceneNode(PLScene::SceneQuery &cQuery, PLScene::SceneNode &cSceneNode);


	private:
		PLScene::SceneContext	*m_pSceneContext;		/**< The scene context, can be nullptr */
		PLScene::SceneContainer	*m_pRootScene;			/**< Root scene (can be nullptr) */;
		PLScene::SceneContainer	*m_pScene;			/**< concrete scene (can be nullptr) */;
		PLScene::SNCamera		*m_pCamera;
		PLCore::EventHandler<PLScene::SceneQuery &, PLScene::SceneNode &>	 EventHandlerSceneNode;
		PLScene::SceneNode *m_pFirstFoundCamera;
		PLCore::String	m_sStartCamera;
		PLCore::String m_sSceneRenderer;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_QPLSCENECONTEXT_H__
