/*********************************************************\
 *  File: Application.cpp                                *
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
#include <PLCore/Runtime.h>
#include <PLCore/Log/Log.h>
#include <PLCore/Tools/Timing.h>
#include <PLCore/Tools/LoadableManager.h>
#include <PLInput/Input/InputManager.h>
#include <PLRenderer/Renderer/FontManager.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/RendererContext.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/QPLContext.h"
#include "PLFrontendQt/Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendQt {


Application::Application(int &argc, char **argv): QApplication(argc, argv)
{
	Init();
}

Application::Application(int &argc, char **argv, bool GUIenabled): QApplication(argc, argv, GUIenabled)
{
	Init();
}

Application::Application(int &argc, char **argv, QApplication::Type type): QApplication(argc, argv, type)
{
	Init();
}

// [TODO] Check this: Linux only, is this really required?
/*
Application::Application(Display* dpy, Qt::HANDLE visual, Qt::HANDLE cmap): QApplication(dpy, visual, cmap)
{
    Init();
}

Application::Application(Display* dpy, int& argc, char** argv, Qt::HANDLE visual, Qt::HANDLE cmap): QApplication(dpy, argc, argv, visual, cmap)
{
    Init();
}*/

Application::~Application()
{
	if (m_TimerId != 0)
		killTimer(m_TimerId);

	// close log
	Log::GetInstance()->Close();
	if (m_pRendererContext)
		delete m_pRendererContext;
}

/**
*  @brief
*    Returns the configuration instance
*/
Config &Application::GetConfig()
{
	return m_cConfig;
}

/**
*  @brief
*    Adds a base directory to PL
*/
void Application::AddBasePath(const QString &path)
{
	LoadableManager::GetInstance()->AddBaseDir(QtStringAdapter::QtToPL(path));
}

/**
*  @brief
*    Removes a base directory from PixelLight
*/
void Application::RemoveBasePath(const QString &path)
{
	LoadableManager::GetInstance()->RemoveBaseDir(QtStringAdapter::QtToPL(path));
}

/**
*  @brief
*    Returns the RendererContext, can be nullptr
*/
PLRenderer::RendererContext *Application::GetRendererContext()
{
	// Create renderer context when the context is requested for the first time
	if (!m_pRendererContext)
		CreateRenderContext();

	return m_pRendererContext;
}

void Application::SetUpdateInterval(int msec)
{
	if (m_TimerId != 0)
		killTimer(m_TimerId);
	m_updateInterval = msec;
	
	if (msec == -1)
		return;
	
	m_TimerId = startTimer(msec);
}

bool Application::AreShaderSupported()
{
	return GetRendererContext() ? (GetRendererContext()->GetRenderer().GetDefaultShaderLanguage().GetLength() != 0) : false;
}

void Application::DoInpuUpdate()
{
	PLInput::InputManager::GetInstance()->Update();
}

void Application::SetContextForUpdate(QPLContext* context)
{
	if (m_pContext)
		m_pContext->disconnect(this);
	m_pContext = context;

	if (m_pContext) {
		connect(m_pContext, SIGNAL(BeginContextChange()), this,  SLOT(OnBeginContextChange()));
		connect(m_pContext, SIGNAL(EndContextChange()),   this,  SLOT(OnEndContextChange()));
	}
}


//[-------------------------------------------------------]
//[ Protected virtual QObject functions                   ]
//[-------------------------------------------------------]
void Application::timerEvent(QTimerEvent *pQTimerEvent)
{
	if (pQTimerEvent->timerId() == m_TimerId) {
		// Check if we're allowed to perform an update right now
		if (Timing::GetInstance()->Update()) {
			// Update input handling
			if (m_doInputUpdates)
				DoInpuUpdate();

			// Update context
			if (!m_suspendRendererContextUpdates && m_doRendererContextUpdates && m_pContext) {
				m_pContext->Update();
				emit AfterFrameUpdate();
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
void Application::Init()
{
	m_suspendRendererContextUpdates = false;
	m_pContext = nullptr;
	m_doInputUpdates = false;
	m_doRendererContextUpdates = false;
	m_pRendererContext = nullptr;
	m_TimerId = 0;

	// Initialize log
	String str = QtStringAdapter::QtToPL(applicationDirPath()) + "/PLFrontendQt.log";
	Log::GetInstance()->Open(str);
	Log::GetInstance()->SetLogLevel(Log::Debug);

	// Scan PL-runtime directory for compatible plugins and load them in as well as scan for compatible data and register it
	Runtime::ScanDirectoryPluginsAndData();

	SetUpdateInterval(10);
}

/**
*  @brief
*    Destroys the renderer context
*/
void Application::DestroyRenderContext()
{
	// Destroy the renderer context
	if (m_pRendererContext) {
		// Destroy
		delete m_pRendererContext;
		m_pRendererContext = nullptr;
	}
}

/**
*  @brief
*    Returns the renderer context
*/
void Application::CreateRenderContext(const String &sRendererName)
{
	// Destroy an renderer context that might be created
	DestroyRenderContext();

	if (!m_pRendererContext) {
		String sRenderer = GetConfig().GetVar("PLRenderer::Config", "RendererAPI");
		const uint32 nRendererMode = GetConfig().GetVarInt("PLRenderer::Config", "RendererMode");

		// Get Z buffer bits (for example 24)
		const uint32 nZBufferBits = GetConfig().GetVarInt("PLRenderer::Config", "ZBufferBits");

		// Stencil buffer bits (for example 8)
		const uint32 nStencilBits = GetConfig().GetVarInt("PLRenderer::Config", "StencilBits");

		// Get the number of multisample antialiasing samples per pixel
		const uint32 nMultisampleAntialiasingSamples = GetConfig().GetVarInt("PLRenderer::Config", "MultisampleAntialiasingSamples");

		// Get the name of the default shader language to use
		const String sDefaultShaderLanguage = GetConfig().GetVar("PLRenderer::Config", "DefaultShaderLanguage");

		if (!sRenderer.GetLength())
			sRenderer = sRendererName;

		// Create an instance of a RendererContext with an renderer given by name
		m_pRendererContext = PLRenderer::RendererContext::CreateInstance(sRenderer, NULL_HANDLE, (PLRenderer::Renderer::EMode)nRendererMode, nZBufferBits, nStencilBits, nMultisampleAntialiasingSamples, sDefaultShaderLanguage);
	}
}


//[-------------------------------------------------------]
//[ Private Qt slots (MOC)                                ]
//[-------------------------------------------------------]
void Application::OnBeginContextChange()
{
	m_suspendRendererContextUpdates = true;
}

void Application::OnEndContextChange()
{
	m_suspendRendererContextUpdates = false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
