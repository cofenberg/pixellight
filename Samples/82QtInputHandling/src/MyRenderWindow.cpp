/*/*********************************************************\
 *  File: MyRenderWindow.cpp                               *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtGui/QMouseEvent>
#include <PLScene/Scene/SPScene.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include <PLFrontendQt/Application.h>
#include <PLFrontendQt/QtStringAdapter.h>
#include <PLFrontendQt/QPLSceneContext.h>
#include "MyRenderWindow.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
using namespace PLScene;
using namespace PLFrontendQt;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MyRenderWindow::MyRenderWindow(QPLSceneContext &cContext, const QString &sCameraNodeName, const DisplayMode *pDisplayMode, QWidget *pParent): QPLRenderWindow(&cContext, pDisplayMode, pParent),
	m_vPreviousMousePosition(0, 0),
	m_pSceneNode(nullptr)
{
	setFocusPolicy(Qt::StrongFocus);
	if (cContext.GetSceneContext()) {
		// Get the requested scene node
		m_pSceneNode = cContext.GetNodeFromScene(QtStringAdapter::QtToPL(sCameraNodeName));
		if (m_pSceneNode) {
			// Get the used surface painter
			SurfacePainter *pSurfacePainter = GetPainter();
			if (pSurfacePainter && pSurfacePainter->IsInstanceOf("PLScene::SPScene")) {
				// Assign the provided camera to the used surface painter
				static_cast<SPScene*>(pSurfacePainter)->SetCamera(reinterpret_cast<SNCamera*>(m_pSceneNode));
			}

			// Loop through all scene node modifiers of the given scene node
			for (uint32 i=0; i<m_pSceneNode->GetNumOfModifiers(); i++) {
				// Get the scene node modifier
				SceneNodeModifier *pSceneNodeModifier = m_pSceneNode->GetModifier("", i);
				if (pSceneNodeModifier && pSceneNodeModifier->GetInputController())
					pSceneNodeModifier->GetInputController()->ConnectAll(&m_cVirtualStandardController, "", "");
			}

			// Set the window title
			setWindowTitle("Used camera: " + sCameraNodeName);
		}
	}
}

/**
*  @brief
*    Destructor
*/
MyRenderWindow::~MyRenderWindow()
{
}


//[-------------------------------------------------------]
//[ Protected virtual QWidget functions                   ]
//[-------------------------------------------------------]
void MyRenderWindow::mousePressEvent(QMouseEvent *pQMouseEvent)
{
	HandleMousePressReleaseEvents(pQMouseEvent, true);
}

void MyRenderWindow::mouseReleaseEvent(QMouseEvent *pQMouseEvent)
{
	HandleMousePressReleaseEvents(pQMouseEvent, false);
}

void MyRenderWindow::mouseMoveEvent(QMouseEvent *pQMouseEvent)
{
	// Update the rotation of the virtual standard controller
	m_cVirtualStandardController.RotX.SetValue( pQMouseEvent->posF().y() - m_vPreviousMousePosition.y(),		true);
	m_cVirtualStandardController.RotY.SetValue((pQMouseEvent->posF().x() - m_vPreviousMousePosition.x())*-1.5f,	true);

	// Backup the current mouse position
	m_vPreviousMousePosition = pQMouseEvent->posF();

	UpdateInputAndSceneContext();

	m_cVirtualStandardController.RotX.SetValue(0, true);
	m_cVirtualStandardController.RotY.SetValue(0, true);

	UpdateInputAndSceneContext();
}

void MyRenderWindow::keyPressEvent(QKeyEvent *pQKeyEvent)
{
	HandleKeyboardEvents(pQKeyEvent, true);
}

void MyRenderWindow::keyReleaseEvent(QKeyEvent *pQKeyEvent)
{
	HandleKeyboardEvents(pQKeyEvent, false);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
void MyRenderWindow::UpdateInputAndSceneContext()
{
	qApp->DoInpuUpdate();
	static_cast<QPLSceneContext*>(GetContext())->UpdateSceneContext();
}

void MyRenderWindow::HandleKeyboardEvents(QKeyEvent *pQKeyEvent, bool bPressed)
{
	bool bHandled = false;

	// D
	if (pQKeyEvent->key() == Qt::Key_D && !pQKeyEvent->isAutoRepeat()) {
		bHandled = true;
		m_cVirtualStandardController.StrafeRight.SetPressed(bPressed);

	// W
	} else if (pQKeyEvent->key() == Qt::Key_W && !pQKeyEvent->isAutoRepeat()) {
		bHandled = true;
		m_cVirtualStandardController.Forward.SetPressed(bPressed);

	// S
	} else if (pQKeyEvent->key() == Qt::Key_S && !pQKeyEvent->isAutoRepeat()) {
		bHandled = true;
		m_cVirtualStandardController.Backward.SetPressed(bPressed);

	// A
	} else if (pQKeyEvent->key() == Qt::Key_A && !pQKeyEvent->isAutoRepeat()) {
		bHandled = true;
		m_cVirtualStandardController.StrafeLeft.SetPressed(bPressed);
	}

	if(bHandled)
		UpdateInputAndSceneContext();
}

void MyRenderWindow::HandleMousePressReleaseEvents(QMouseEvent *pQMouseEvent, bool bPressed)
{
	bool bHandled = false;

	if (pQMouseEvent->buttons() & Qt::LeftButton) {
		if (bPressed)
			m_vPreviousMousePosition = pQMouseEvent->posF();
		m_cVirtualStandardController.Rotate.SetPressed(bPressed);
		bHandled = true;
	}

	if (bHandled)
		UpdateInputAndSceneContext();
}
