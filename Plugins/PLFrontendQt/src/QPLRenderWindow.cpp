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
QPLRenderWindow::QPLRenderWindow(QPLContext *pContext, const PLRenderer::DisplayMode *pDisplayMode, QWidget *parent) : QWidget(parent),
	m_nWindowRedrawTimerID(startTimer(10)),	// An interval of 10 milliseconds should be enough
	m_pContext(pContext),
	m_pInputHandler(nullptr)
{
	// Disable window system background to avoid "white flickering" caused by automatic overdraw
	// (same settings as used in Qt's QGLWidget)
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);

	// Now, there's still "black flickering" - in order to get rid of this we're not using any built-in paint engines of Qt
	// -> Overwrite the "QPaintDevice::paintEngine()"-method and just return a null pointer
	// -> Set the following attribute
	setAttribute(Qt::WA_OpaquePaintEvent, true);

	InitWindow(pDisplayMode);
}

QPLRenderWindow::QPLRenderWindow(QWidget *parent) : QWidget(parent),
	m_nWindowRedrawTimerID(startTimer(10)),	// An interval of 10 milliseconds should be enough
	m_pContext(nullptr),
	m_pInputHandler(nullptr)
{
	// Disable window system background to avoid "white flickering" caused by automatic overdraw
	// (same settings as used in Qt's QGLWidget)
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);

	// Now, there's still "black flickering" - in order to get rid of this we're not using any built-in paint engines of Qt
	// -> Overwrite the "QPaintDevice::paintEngine()"-method and just return a null pointer
	// -> Set the following attribute
	setAttribute(Qt::WA_OpaquePaintEvent, true);
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
		// Ask Qt politly to update (and repaint) the widget
		update();
	}
}


//[-------------------------------------------------------]
//[ Protected virtual QPaintDevice functions              ]
//[-------------------------------------------------------]
QPaintEngine *QPLRenderWindow::paintEngine() const
{
	#if defined(Q_WS_WIN)
		// We're not using any built-in paint engines of Qt ("flickering"-avoidance)
		return nullptr;
	#else
		// On Linux there's no "flickering"-issue and when returning a null pointer in here
		// "QPainter::begin: Paint device returned engine == 0, type: 1" will be written
		// into the console - all the time.

		// Call base implementation
		return QWidget::paintEngine();
	#endif
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
