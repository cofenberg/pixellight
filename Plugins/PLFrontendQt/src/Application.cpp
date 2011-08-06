/*********************************************************\
 *  File: Application.cpp                                *
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
#include <PLCore/Core.h>
#include <PLCore/Log/Log.h>
#include <PLCore/File/Url.h>
#include <PLCore/File/File.h>
#include <PLCore/File/Directory.h>
#include <PLCore/File/FileSearch.h>
#include <PLCore/String/String.h>
#include <PLCore/System/System.h>
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
		// Update timing
		Timing::GetInstance()->Update();

		if (m_doInputUpdates) {
			// Update input handling
			DoInpuUpdate();
		}

		if (!m_suspendRendererContextUpdates && m_doRendererContextUpdates && m_pContext) {
			m_pContext->Update();
			emit AfterFrameUpdate();
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

	bool useRuntimeDir = m_cConfig.GetVar("PLCore::CoreGeneralConfig", "UsePixelLightRuntime").GetBool();
	InitCore(useRuntimeDir);

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
		String sRenderer = GetConfig().GetVar("PLScene::EngineGraphicConfig", "RendererAPI");
		const uint32 nRendererMode = GetConfig().GetVarInt("PLScene::EngineGraphicConfig", "RendererMode");

		// Get Z buffer bits (for example 24)
		const uint32 nZBufferBits = GetConfig().GetVarInt("PLEngine::RendererConfig", "ZBufferBits");

		// Stencil buffer bits (for example 8)
		const uint32 nStencilBits = GetConfig().GetVarInt("PLEngine::RendererConfig", "StencilBits");

		// Get the number of multisample antialiasing samples per pixel
		const uint32 nMultisampleAntialiasingSamples = GetConfig().GetVarInt("PLEngine::RendererConfig", "MultisampleAntialiasingSamples");

		// Get the name of the default shader language to use
		const String sDefaultShaderLanguage = GetConfig().GetVar("PLEngine::RendererConfig", "DefaultShaderLanguage");

		if (!sRenderer.GetLength())
			sRenderer = sRendererName;

		// Create an instance of a RendererContext with an renderer given by name
		m_pRendererContext = PLRenderer::RendererContext::CreateInstance(sRenderer,(PLRenderer::Renderer::EMode)nRendererMode, nZBufferBits, nStencilBits, nMultisampleAntialiasingSamples, sDefaultShaderLanguage);
	}

	if (m_pRendererContext) {
		// Create the default texture font
		PLRenderer::FontManager &cFontManager = m_pRendererContext->GetRenderer().GetFontManager();
		const String sDefaultFontTexture     = GetConfig().GetVar("PLScene::EngineGraphicConfig", "DefaultFontTexture");
		const uint32 nDefaultFontTextureSize = GetConfig().GetVar("PLScene::EngineGraphicConfig", "DefaultFontTextureSize").GetInt();
		cFontManager.SetDefaultFontTexture(cFontManager.GetFontTexture(sDefaultFontTexture, nDefaultFontTextureSize));
	}
}

/**
*  @brief
*    Initializes the core of PL
*/
void Application::InitCore(bool useRuntimeDir)
{
	// Use PixelLight runtime?
	if (useRuntimeDir) {
		// Scan PL-runtime directory for compatible plugins and load them in
		Core::ScanRuntimeDirectoryPlugins();

		// Get PixelLight runtime directory
		String sPLDirectory = Core::GetRuntimeDirectory();
		if (sPLDirectory.GetLength())
			ScanFSArchives(sPLDirectory + "/Data/");
	}
}

/**
*  @brief
*    Scan an directory for archives which gets added as base paths
*/
bool Application::ScanFSArchives(const String &sDirectory, const String &sExtension)
{
	// Check parameters
	if (sDirectory.GetLength() && sExtension.GetLength()) {
		// Add FS base directories
		Directory cDir(sDirectory);
		if (cDir.IsDirectory()) {
			FileSearch cSearch(cDir);
			while (cSearch.HasNextFile()) {
				// Get next file
				String sFilename = cSearch.GetNextFile();
				String sPath     = cDir.GetUrl().GetUrl() + "/" + sFilename;

				// Add all found files to the base-directories (meaning these must be packages ...)
				if (File(sPath).IsFile())
					LoadableManager::GetInstance()->AddBaseDir(sPath + "/");
			}

			// Done
			return true;
		}
	}

	// Error!
	return false;
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
