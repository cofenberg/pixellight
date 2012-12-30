/*********************************************************\
 *  File: QPLSceneContext.h                              *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
