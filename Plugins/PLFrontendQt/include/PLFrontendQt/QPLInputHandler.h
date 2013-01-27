/*********************************************************\
 *  File: QPLInputHandler.h                              *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
