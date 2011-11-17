/*********************************************************\
 *  File: QPLInputHandler.h                              *
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


#ifndef __PLFRONTENDQT_QPLINPUTHANDLER_H__
#define __PLFRONTENDQT_QPLINPUTHANDLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtCore/QList>
#include <QtCore/QPointF>
#include <QtCore/QObject>
#include <PLInput/Input/Virtual/VirtualStandardController.h>
#include "PLFrontendQt/InputHandler.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class QKeyEvent;
class QMouseEvent;
namespace PLScene {
	class SceneNode;
	class SceneNodeHandler;
}
namespace PLFrontendQt {
	class QPLSceneContext;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
class PLFRONTENDQT_API QPLInputHandler : public QObject, public InputHandler {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		explicit QPLInputHandler(QPLSceneContext *context, QObject *parent = nullptr);
		virtual ~QPLInputHandler();

		virtual void mousePressEvent(QMouseEvent*) override;
		virtual void mouseReleaseEvent(QMouseEvent*) override;
		virtual void mouseMoveEvent(QMouseEvent*) override;
		virtual void keyPressEvent(QKeyEvent*) override;
		virtual void keyReleaseEvent(QKeyEvent*) override;

		void AddSceneNode(PLScene::SceneNode* pSceneNode);
		void RemoveSceneNode(PLScene::SceneNode* pSceneNode);
		void CleanUpSceneNodeHandlerList(bool onlyEmpty = true);


	//[-------------------------------------------------------]
	//[ Private Qt slots (MOC)                                ]
	//[-------------------------------------------------------]
	private slots:
		void OnAfterFrameUpdate();
		void OnBeginContextChange();
		void OnEndContextChange();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		void UpdateInputAndSceneContext();
		void HandleKeyboardEvents(QKeyEvent*, bool pressed);
		void HandleMousePressReleaseEvents(QMouseEvent*, bool pressed);
		PLScene::SceneNodeHandler* GetHandlerForSceneNode(PLScene::SceneNode* pSceneNode);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLInput::VirtualStandardController	virtController;
		QPointF								m_mousePos;
		QPLSceneContext					   *m_pContext;
		QList<PLScene::SceneNodeHandler*>	m_lstSceneNodes;
		bool								m_disableUpdate;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_QPLINPUTHANDLER_H__
