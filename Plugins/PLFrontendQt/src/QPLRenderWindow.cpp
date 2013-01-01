/*********************************************************\
 *  File: QPLRenderWindow.cpp                            *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
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
#include <QtGui/QKeyEvent>
#include <PLCore/Log/Log.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/Surface.h>
#include <PLRenderer/Renderer/SurfacePainter.h>
#include <PLScene/Scene/SPScene.h>
#include "PLFrontendQt/QPLContext.h"
#include "PLFrontendQt/InputHandler.h"
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/QPLSceneContext.h"
#include "PLFrontendQt/QPLRenderWindow.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
namespace PLFrontendQt {


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
QPLRenderWindow::QPLRenderWindow(QPLContext *pContext, const PLRenderer::DisplayMode *pDisplayMode, QWidget *parent) : FrontendRenderWindow(parent),
	m_nWindowRedrawTimerID(startTimer(10)),	// An interval of 10 milliseconds should be enough
	m_pContext(pContext),
	m_pInputHandler(nullptr)
{
	InitWindow(pDisplayMode);
}

QPLRenderWindow::QPLRenderWindow(QWidget *parent) : FrontendRenderWindow(parent),
	m_nWindowRedrawTimerID(startTimer(10)),	// An interval of 10 milliseconds should be enough
	m_pContext(nullptr),
	m_pInputHandler(nullptr)
{
}

void QPLRenderWindow::SetupWindow(QPLContext *pContext, const PLRenderer::DisplayMode *pDisplayMode)
{
	m_pContext = pContext;
	InitWindow(pDisplayMode);
}

/**
*  @brief
*    Destructor
*/
QPLRenderWindow::~QPLRenderWindow()
{
	// Stop window redraw timer
	if (m_nWindowRedrawTimerID)
		killTimer(m_nWindowRedrawTimerID);

	m_pContext = nullptr;
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
}

void QPLRenderWindow::OnContextChanged()
{
	SurfacePainter *pPainter = GetPainter();
	if (pPainter && pPainter->IsInstanceOf("PLScene::SPScene") && m_pContext->inherits("PLFrontendQt::QPLSceneContext")) {
		PLScene::SPScene *pSPScene = static_cast<PLScene::SPScene*>(pPainter);
		QPLSceneContext *sceneContext = static_cast<QPLSceneContext*>(m_pContext);
		//if (sceneContext->GetCamera())
		pSPScene->SetCamera(sceneContext->GetCamera());

		pSPScene->SetDefaultSceneRenderer("");
		pSPScene->SetDefaultSceneRenderer(sceneContext->GetSceneRenderer());
	}
}


//[-------------------------------------------------------]
//[ Protected virtual QObject functions                   ]
//[-------------------------------------------------------]
void QPLRenderWindow::timerEvent(QTimerEvent *pQTimerEvent)
{
	if (pQTimerEvent->timerId() == m_nWindowRedrawTimerID) {
		// Ask Qt politely to update (and repaint) the widget
		update();
	}
}


//[-------------------------------------------------------]
//[ Protected virtual QWidget functions                   ]
//[-------------------------------------------------------]
void QPLRenderWindow::paintEvent(QPaintEvent *)
{
	// Qt only calls this method if the draw area isn't null

	// Get the renderer surface
	Surface *pSurface = GetSurface();
	if (pSurface) {
		// Draw the renderer surface
		pSurface->Draw();
	}
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
			PL_LOG(Error, "Can't create Painter instance " + QtStringAdapter::QtToPL(m_pContext->GetPainterName()))
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
		Init(m_pContext->GetRendererContext()->GetRenderer(), (PLCore::handle)winId(), m_sDisplayMode, false);

		ChangeContext(m_pContext);
	} else {
		// Error!
		PL_LOG(Error, "Can't init window without an renderer context")
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
