/*********************************************************\
 *  File: QPLInputHandler.cpp                            *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
#include <PLScene/Scene/SceneNode.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SceneNodeHandler.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include <PLInput/Input/Controller.h>
#include <PLInput/Input/Controls/Control.h>
#include <PLInput/Input/Connection/Connection.h>
#include "PLFrontendQt/Application.h"
#include "PLFrontendQt/QPLSceneContext.h"
#include "PLFrontendQt/QPLInputHandler.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


QPLInputHandler::QPLInputHandler(QPLSceneContext *context, QObject *parent) : QObject(parent),
	m_mousePos(0, 0),
	m_pContext(context)
{
	connect(qApp, SIGNAL(AfterFrameUpdate()), this, SLOT(OnAfterFrameUpdate()));
}

QPLInputHandler::~QPLInputHandler()
{
	CleanUpSceneNodeHandlerList(false);
}

void QPLInputHandler::mousePressEvent(QMouseEvent* ev)
{
	virtController.MouseX.SetValue(ev->posF().x(), false);
	virtController.MouseY.SetValue(ev->posF().y(), false);
	m_mousePos = ev->posF();
	HandleMousePressReleaseEvents(ev, true);
}

void QPLInputHandler::mouseReleaseEvent(QMouseEvent* ev)
{
	HandleMousePressReleaseEvents(ev, false);
}

void QPLInputHandler::mouseMoveEvent(QMouseEvent* ev)
{
	virtController.MouseX.SetValue(ev->posF().x(), false);
	virtController.MouseY.SetValue(ev->posF().y(), false);
	virtController.RotX.SetValue((ev->posF().y() - m_mousePos.y()), true);
	virtController.RotY.SetValue((ev->posF().x() - m_mousePos.x())* -1.5f, true);

	m_mousePos = ev->posF();
	UpdateInputAndSceneContext();

//         virtController.RotX.SetValue(0, true);
//         virtController.RotY.SetValue(0, true);
//
//         UpdateInputAndSceneContext();
}

void QPLInputHandler::keyPressEvent(QKeyEvent* ev)
{
	HandleKeyboardEvents(ev, true);
}
void QPLInputHandler::keyReleaseEvent(QKeyEvent* ev)
{
	HandleKeyboardEvents(ev, false);
}

void QPLInputHandler::AddSceneNode(PLScene::SceneNode* pSceneNode)
{
	if (!pSceneNode || GetHandlerForSceneNode(pSceneNode))
		return;

	PLScene::SceneNodeHandler *pHandler = new PLScene::SceneNodeHandler();
	pHandler->SetElement(pSceneNode);

	if (pSceneNode->GetInputController()) {
		PLInput::Controller *controller = pSceneNode->GetInputController();
		controller->ConnectAll(&virtController, "", "");
	}
	int count = pSceneNode->GetNumOfModifiers();
	for (int i = 0; i < count; ++i) {
		PLScene::SceneNodeModifier *pModifier = pSceneNode->GetModifier("", i);
		if (pModifier && pModifier->GetInputController()) {
			PLInput::Controller *controller = pModifier->GetInputController();
			controller->ConnectAll(&virtController, "", "");
		}
	}
}

void QPLInputHandler::RemoveSceneNode(PLScene::SceneNode* pSceneNode)
{
	PLScene::SceneNodeHandler *pHandler = GetHandlerForSceneNode(pSceneNode);
	if (!pHandler)
		return;

	m_lstSceneNodes.removeOne(pHandler);

	delete pHandler;

	// Disconnect
	int count = pSceneNode->GetNumOfModifiers();
	for (int i = 0; i < count; ++i) {
		PLScene::SceneNodeModifier *pModifier = pSceneNode->GetModifier("", i);
		if (pModifier && pModifier->GetInputController()) {
			PLInput::Controller *controller = pModifier->GetInputController();
			PLCore::List<PLInput::Connection*> connections = controller->GetConnections();
			for (int j = 0; j < connections.GetNumOfElements(); ++j) {
				PLInput::Connection *con = connections.Get(j);
				if (con->GetInputControl()->GetController() == &virtController) {
					controller->Disconnect(con);
				}
			}
		}
	}
}

void QPLInputHandler::UpdateInputAndSceneContext()
{
//         if (m_disableUpdate)
//             return;
	qApp->DoInpuUpdate();
//          if (m_pContext)
//              m_pContext->UpdateSceneContext();
}

void QPLInputHandler::HandleKeyboardEvents(QKeyEvent* ev, bool pressed)
{
	bool handled = false;
	if (ev->key() == Qt::Key_D && !ev->isAutoRepeat()) {
		handled = true;
		virtController.StrafeRight.SetPressed(pressed);
	} else if (ev->key() == Qt::Key_W && !ev->isAutoRepeat()) {
		handled = true;
		virtController.Forward.SetPressed(pressed);
	} else if (ev->key() == Qt::Key_S && !ev->isAutoRepeat()) {
		handled = true;
		virtController.Backward.SetPressed(pressed);
	} else if (ev->key() == Qt::Key_A && !ev->isAutoRepeat()) {
		handled = true;
		virtController.StrafeLeft.SetPressed(pressed);
	} else if (ev->key() == Qt::Key_Space && !ev->isAutoRepeat()) {
		handled = true;
		virtController.KeySpace.SetPressed(pressed);
		virtController.Jump.SetPressed(pressed);
	}

	if (ev->modifiers() & Qt::ControlModifier && !ev->isAutoRepeat()) {
		handled = true;
		virtController.KeyControl.SetPressed(pressed);
	}
	if (!ev->isAutoRepeat()) {
		bool pres = (ev->modifiers() & Qt::ControlModifier);
		if (virtController.KeyControl.IsPressed() != pres) {
			virtController.KeyControl.SetPressed(pres);
			handled = true;
		}

		pres = (ev->modifiers() & Qt::ShiftModifier);
		if (virtController.KeyShift.IsPressed() != pres
		        || virtController.Run.IsPressed() != pres) {
			virtController.KeyShift.SetPressed(pres);
			virtController.Run.SetPressed(pres);
			handled = true;
		}

		pres = (ev->modifiers() & Qt::AltModifier);
		if (virtController.KeyAlt.IsPressed() != pres) {
			virtController.KeyAlt.SetPressed(pres);
			handled = true;
		}
	}

	if (handled)
		UpdateInputAndSceneContext();
}

void QPLInputHandler::HandleMousePressReleaseEvents(QMouseEvent* ev, bool pressed)
{
	bool handled = false;;
	if (ev->button() == Qt::LeftButton) {
		virtController.MouseLeft.SetPressed(pressed);
		virtController.Rotate.SetPressed(pressed);
		handled = true;
	} else if (ev->button() == Qt::MidButton) {
		virtController.MouseMiddle.SetPressed(pressed);
		virtController.Pickup.SetPressed(pressed);
		handled = true;
	} else if (ev->buttons() == Qt::RightButton) {
		virtController.MouseRight.SetPressed(pressed);
		handled = true;
	}

	if (handled) {
		UpdateInputAndSceneContext();
	}
}

void QPLInputHandler::OnAfterFrameUpdate()
{
	virtController.RotX.SetValue(0, true);
	virtController.RotY.SetValue(0, true);
	UpdateInputAndSceneContext();
}

void QPLInputHandler::OnBeginContextChange()
{
	m_disableUpdate = true;
}
void QPLInputHandler::OnEndContextChange()
{
	m_disableUpdate = false;
}

PLScene::SceneNodeHandler* QPLInputHandler::GetHandlerForSceneNode(PLScene::SceneNode* pSceneNode)
{
	if (!pSceneNode)
		return nullptr;

	foreach(PLScene::SceneNodeHandler* pHandler, m_lstSceneNodes) {
		if (pHandler->GetElement() == pSceneNode)
			return pHandler;
	}
	return nullptr;
}

void QPLInputHandler::CleanUpSceneNodeHandlerList(bool onlyEmpty)
{
	for (int i = m_lstSceneNodes.count() - 1; i >= 0; --i) {
		PLScene::SceneNodeHandler *pHandler = m_lstSceneNodes[i];
		if (!onlyEmpty || !pHandler->GetElement()) {
			m_lstSceneNodes.removeAt(i);
			delete pHandler;
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
