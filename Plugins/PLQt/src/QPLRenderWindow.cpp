/*********************************************************\
 *  File: QPLRenderWindow.cpp                            *
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
#include <QtGui/QMouseEvent>
#include <QtGui/QKeyEvent>
#include <PLGeneral/Log/Log.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/Surface.h>
#include <PLRenderer/Renderer/SurfacePainter.h>
#include <PLScene/Scene/SPScene.h>
#include "PLQt/QPLContext.h"
#include "PLQt/InputHandler.h"
#include "PLQt/QtStringAdapter.h"
#include "PLQt/QPLSceneContext.h"
#include "PLQt/QPLRenderWindow.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace PLQt {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*
*  @param[in] parent
*    parent widget of this widget
*/
QPLRenderWindow::QPLRenderWindow(QPLContext *pContext, bool updateContext, const PLRenderer::DisplayMode *pDisplayMode, QWidget *parent) : QWidget(parent),
	m_pContext(pContext),
	m_bUpdateContext(updateContext),
	m_pInputHandler(nullptr)
{
	// Set widget attribut to indicated that someone is directly drawing to the screen
	// in this case it is PL which draws directly to the screen.
	setAttribute(Qt::WA_PaintOnScreen);

	// Set widget attribut that this window has no background. Avoids flicker when the widget gets resized because Qt doesn't paint the background
	setAttribute(Qt::WA_NoSystemBackground);

	InitWindow(pDisplayMode);
}

QPLRenderWindow::QPLRenderWindow(QWidget *parent) : QWidget(parent),
	m_pContext(nullptr),
	m_bUpdateContext(false),
	m_pInputHandler(nullptr)
{
	// Set widget attribut to indicated that someone is directly drawing to the screen
	// in this case it is PL which draws directly to the screen.
	setAttribute(Qt::WA_PaintOnScreen);

	// Set widget attribut that this window has no background. Avoids flicker when the widget gets resized because Qt doesn't paint the background
	setAttribute(Qt::WA_NoSystemBackground);
}

void QPLRenderWindow::SetupWindow(QPLContext *pContext, bool updateContext, const PLRenderer::DisplayMode *pDisplayMode)
{
	m_pContext = pContext;
	m_bUpdateContext = updateContext;
	InitWindow(pDisplayMode);
}

/**
*  @brief
*    Destructor
*/
QPLRenderWindow::~QPLRenderWindow()
{
	m_pContext = nullptr;
}

/**
*  @brief
*    Let PL draw one frame
*/
void QPLRenderWindow::Update()
{
	// Don't do update to surface when it's not visible
	if (isVisible()) {
		if (m_bUpdateContext && m_pContext)
			m_pContext->Update();
		else if (GetSurface())
			GetSurface()->Update();
	}
}

/**
*  @brief
*    Get SurfacePainter for this window
*/
PLRenderer::SurfacePainter *QPLRenderWindow::GetPainter()
{
	return GetSurface() ? GetSurface()->GetPainter() : nullptr;
}

QPLContext *QPLRenderWindow::GetContext()
{
	return m_pContext;
}

void QPLRenderWindow::SetInputHandler(InputHandler *pInputHandler)
{
	m_pInputHandler = pInputHandler;
}

void QPLRenderWindow::ChangeContext(QPLContext *pNewContext)
{
	// [TODO] what if the new context uses an different renderer context?
	m_pContext = pNewContext;
	SetPainter();
	connect(m_pContext, SIGNAL(ContextChanged()), this, SLOT(OnContextChanged()));
	OnContextChanged();
	Update();
}

void QPLRenderWindow::OnContextChanged()
{
	SurfacePainter *pPainter = GetPainter();
	if (pPainter && pPainter->IsInstanceOf("PLScene::SPScene") && m_pContext->inherits("PLQt::QPLSceneContext")) {
		PLScene::SPScene *pSPScene = static_cast<PLScene::SPScene*>(pPainter);
		QPLSceneContext *sceneContext = static_cast<QPLSceneContext*>(m_pContext);
		//if (sceneContext->GetCamera())
		pSPScene->SetCamera(sceneContext->GetCamera());

		pSPScene->SetDefaultSceneRenderer("");
		pSPScene->SetDefaultSceneRenderer(sceneContext->GetSceneRenderer());
	}
}


//[-------------------------------------------------------]
//[ Protected virtual QWidget functions                   ]
//[-------------------------------------------------------]
void QPLRenderWindow::paintEvent(QPaintEvent *)
{
	if (isVisible()) {
		// Let PL draw one frame
		Update();
	}
}

void QPLRenderWindow::resizeEvent(QResizeEvent *)
{
	if (isVisible()) {
		// Let PL draw one frame
		Update();
	}
}

void QPLRenderWindow::showEvent(QShowEvent *)
{
	// [TODO] Check this
	/*
	if (isVisible()) {
		// Let PL draw one frame
		Update();
	}
	*/
}

void QPLRenderWindow::mousePressEvent(QMouseEvent* ev)
{
	if (m_pInputHandler)
		m_pInputHandler->mousePressEvent(ev);
}

void QPLRenderWindow::mouseReleaseEvent(QMouseEvent* ev)
{
	if (m_pInputHandler)
		m_pInputHandler->mouseReleaseEvent(ev);
}

void QPLRenderWindow::mouseMoveEvent(QMouseEvent* ev)
{
	if (m_pInputHandler)
		m_pInputHandler->mouseMoveEvent(ev);
}

void QPLRenderWindow::keyPressEvent(QKeyEvent* ev)
{
	if (m_pInputHandler)
		m_pInputHandler->keyPressEvent(ev);
}

void QPLRenderWindow::keyReleaseEvent(QKeyEvent* ev)
{
	if (m_pInputHandler)
		m_pInputHandler->keyReleaseEvent(ev);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Set surface painter for this window
*/
void QPLRenderWindow::SetPainter()
{
	if (m_pContext && GetSurface()) {
		// Create SurfacePainter
		SurfacePainter *pPainter = m_pContext->CreateSurfacePainter();
		if (pPainter) {
			// Set the Painter tor the Surface
			GetSurface()->SetPainter(pPainter);
		} else {
			PL_LOG(Error, "Can't create Painter instance " + QtStringAdapter::QtToPL(m_pContext->GetPainterName()));
		}
	}
}

/**
*  @brief
*    Initialize the window and the surface handler
*/
void QPLRenderWindow::InitWindow(const PLRenderer::DisplayMode *pDisplayMode)
{
	if (m_pContext && m_pContext->GetRendererContext()) {
		// De-init window
		DeInit();

		// Display mode information given?
		if (pDisplayMode) {
			// Just copy over the given information
			m_sDisplayMode = *pDisplayMode;
		} else {
			// Use default settings
			m_sDisplayMode.vSize        = PLMath::Vector2i(width(), height());
			m_sDisplayMode.nColorBits   = 32;
			m_sDisplayMode.nFrequency   = 60;
		}

		// Initialize renderer surface handler
		Init(m_pContext->GetRendererContext()->GetRenderer(), (PLGeneral::handle)winId(), m_sDisplayMode, false);

		ChangeContext(m_pContext);
	} else {
		// Error!
		PL_LOG(Error, "Can't init window without an renderer context");
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLQt
