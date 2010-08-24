/*********************************************************\
 *  File: RenderApplication.cpp                         *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLGeneral/Tools/Timing.h>
#include <PLGeneral/Log/Log.h>
#include <PLGui/Gui/Gui.h>
#include <PLInput/Input/InputManager.h>
#include <PLInput/Input/Virtual/VirtualController.h>
#include <PLInput/Input/Virtual/VirtualStandardController.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/Surface.h>
#include <PLRenderer/Renderer/FontManager.h>
#include <PLRenderer/Renderer/SurfacePainter.h>
#include <PLRenderer/Texture/TextureManager.h>
#include "PLEngine/Gui/RenderWidget.h"
#include "PLEngine/Gui/RenderWindow.h"
#include "PLEngine/Application/RenderApplication.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLGui;
using namespace PLInput;
using namespace PLRenderer;
namespace PLEngine {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RenderApplication::RenderApplication(const String &sSurfacePainter) : GuiApplication(),
	m_sSurfacePainter(sSurfacePainter),
	m_pRendererContext(NULL),
	m_pInputController(NULL),
	EventHandlerDestroy       (&RenderApplication::NotifyDestroy,    this),
	EventHandlerActivate	  (&RenderApplication::NotifyActivate,	 this),
	EventHandlerDisplayMode   (&RenderApplication::OnDisplayMode,    this),
	EventHandlerFullscreenMode(&RenderApplication::OnFullscreenMode, this)
{
	// Set application title
	SetTitle("PixelLight render application");
}

/**
*  @brief
*    Destructor
*/
RenderApplication::~RenderApplication()
{
}

/**
*  @brief
*    Returns the renderer context
*/
RendererContext *RenderApplication::GetRendererContext() const
{
	return m_pRendererContext;
}

/**
*  @brief
*    Get surface painter of the main window
*/
SurfacePainter *RenderApplication::GetPainter() const
{
	// Get the main widget
	const Widget *pWidget = GetMainWindow();
	if (pWidget) {
		// Get the surface
		const Surface *pSurface = GetSurface(pWidget);
		if (pSurface) {
			// Return painter
			return pSurface->GetPainter();
		}
	}

	// Error!
	return NULL;
}

/**
*  @brief
*    Set surface painter of the main window
*/
void RenderApplication::SetPainter(SurfacePainter *pPainter)
{
	// Get the main widget
	const Widget *pWidget = GetMainWindow();
	if (pWidget) {
		// Get the surface
		Surface *pSurface = GetSurface(pWidget);
		if (pSurface) {
			// Set painter
			pSurface->SetPainter(pPainter);
		}
	}
}

/**
*  @brief
*    Get virtual input controller
*/
VirtualController *RenderApplication::GetInputController() const
{
	// Return input controller
	return m_pInputController;
}

/**
*  @brief
*    Set virtual input controller
*/
void RenderApplication::SetInputController(VirtualController *pInputController)
{
	// Set input controller
	m_pInputController = pInputController;
}

/**
*  @brief
*    Returns whether or not the main window is currently fullscreen or not
*/
bool RenderApplication::IsFullscreen() const
{
	// Get the main widget
	Widget *pWidget = GetMainWindow();
	if (pWidget && pWidget->IsInstanceOf("PLEngine::RenderWindow")) {
		// Return the current state
		return ((RenderWindow*)pWidget)->IsFullscreen();
	}

	// Error!
	return false;
}

/**
*  @brief
*    Sets whether or not the main window is currently fullscreen or not
*/
void RenderApplication::SetFullscreen(bool bFullscreen)
{
	// Get the main widget
	Widget *pWidget = GetMainWindow();
	if (pWidget && pWidget->IsInstanceOf("PLEngine::RenderWindow")) {
		// Set the current state
		((RenderWindow*)pWidget)->SetFullscreen(bFullscreen);
	}
}

/**
*  @brief
*    Update application
*/
bool RenderApplication::Update(bool bForceUpdate)
{
	// Check if there are system messages waiting (make a non-blocking main loop)
	if (Gui::GetSystemGui()->HasPendingMessages())
		Gui::GetSystemGui()->ProcessMessages();

	// Force or is it time for an update?
	if (bForceUpdate) {
		// Update timing
		Timing::GetInstance()->Update();

		// Call the application's update function
		return OnUpdate();
	} else {
		// Check if we're allowed to perform an update right now
		uint32 nTimeToWait = 0;
		if (Timing::GetInstance()->Update(&nTimeToWait)) {
			// Call the application's update function
			return OnUpdate();
		} else {
			// Let the system some time to process other system tasks etc.
			// If this isn't done the CPU usage is always up to 100%!!
			// Please note that there's no guaranty that the resulting FPS always reaches
			// exactly the maximum FPS limit.
			System::GetInstance()->Sleep(nTimeToWait);

			// Not updated
			return false;
		}
	}
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get render surface from a window
*/
Surface *RenderApplication::GetSurface(const Widget *pWidget) const
{
	// Valid widget given?
	if (pWidget) {
		// Get surface from RenderWidget or RenderWindow
		if (pWidget->IsInstanceOf("PLEngine::RenderWidget")) {
			return ((const RenderWidget*)pWidget)->GetSurface();
		} else if (pWidget->IsInstanceOf("PLEngine::RenderWindow")) {
			return ((const RenderWindow*)pWidget)->GetSurface();
		}
	}

	// No surface attached to this widget
	return NULL;
}


//[-------------------------------------------------------]
//[ Protected virtual ConsoleApplication functions        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initialization function that is called prior to Main()
*/
bool RenderApplication::Init()
{
	// Call base implementation
	// Note: GuiApplication::Init() is not used, because OnCreateRendererContext() has to be called prior to OnCreateMainWindow()
	if (ConsoleApplication::Init()) {
		// Create renderer context
		OnCreateRendererContext();
		if (!m_bRunning) return false;

		// Check if a renderer context has been created
		if (m_pRendererContext) {
			// [TODO] Shouldn't this be done rather inside FontManager itself? What happens if we do not set a default
			//        font here, do we then have no font at all? Or ist the a default-default-font in FontManager?

			// Create default font
			PLRenderer::FontManager &cFontManager = m_pRendererContext->GetRenderer().GetFontManager();
			const String sDefaultFontTexture     = GetConfig().GetVar("PLScene::EngineGraphicConfig", "DefaultFontTexture");
			const uint32 nDefaultFontTextureSize = GetConfig().GetVar("PLScene::EngineGraphicConfig", "DefaultFontTextureSize").GetInt();
			cFontManager.SetDefaultFontTexture(cFontManager.GetFontTexture(sDefaultFontTexture, nDefaultFontTextureSize));

			// Create main window
			OnCreateMainWindow();
			if (!m_bRunning) return false;

			// Create surface painter
			OnCreatePainter();
			if (!m_bRunning) return false;

			// Initialize input system
			InputManager::GetInstance()->DetectDevices();

			// Create virtual input controller
			OnCreateInputController();
			if (!m_bRunning) return false;

			// Done
			return true;
		}
	}

	// Error
	return false;
}

/**
*  @brief
*    Main function
*/
void RenderApplication::Main()
{
	// Run main loop
	Gui *pGui = Gui::GetSystemGui();
	while (pGui->IsActive() && m_bRunning) {
		// Update application
		Update();
	}
}

/**
*  @brief
*    De-initialization function that is called after Main()
*/
void RenderApplication::DeInit()
{
	// Destroy main widget before the renderer context is destroyed, this way we have a clean and safe shutdown
	Widget *pWidget = GetMainWindow();
	if (pWidget) {
		pWidget->Destroy();
	}

	// Destroy renderer context
	if (m_pRendererContext) {
		delete m_pRendererContext;
		m_pRendererContext = NULL;
	}

	// Destroy virtual input controller
	if (m_pInputController) {
		delete m_pInputController;
		m_pInputController = NULL;
	}

	// Call base implementation
	GuiApplication::DeInit();
}


//[-------------------------------------------------------]
//[ Protected virtual GuiApplication functions            ]
//[-------------------------------------------------------]
void RenderApplication::OnCreateMainWindow()
{
	// Fill display mode information
	DisplayMode sDisplayMode;
	sDisplayMode.vSize.x    = GetConfig().GetVarInt("PLEngine::RendererConfig", "DisplayWidth");
	sDisplayMode.vSize.y    = GetConfig().GetVarInt("PLEngine::RendererConfig", "DisplayHeight");
	sDisplayMode.nColorBits = GetConfig().GetVarInt("PLEngine::RendererConfig", "DisplayColorBits");
	sDisplayMode.nFrequency = GetConfig().GetVarInt("PLEngine::RendererConfig", "DisplayFrequency");

	// Create renderer window
	RenderWindow *pWindow = new RenderWindow(m_pRendererContext->GetRenderer(), NULL, &sDisplayMode,
											 GetConfig().GetVar("PLEngine::RendererConfig", "Fullscreen").GetBool());
	pWindow->AddModifier("PLGui::ModClose", "ExitApplication=true");	// By default, when clicking on 'x', close the application
	pWindow->SetTitle(GetTitle());
	pWindow->SetVisible(true);
	pWindow->Activate();

	// Connect event handler
	pWindow->EventActivate		.Connect(&EventHandlerActivate);
	pWindow->EventDestroy       .Connect(&EventHandlerDestroy);
	pWindow->EventDisplayMode   .Connect(&EventHandlerDisplayMode);
	pWindow->EventFullscreenMode.Connect(&EventHandlerFullscreenMode);

	// Set main window
	SetMainWindow(pWindow);
}


//[-------------------------------------------------------]
//[ Protected virtual RenderApplication functions         ]
//[-------------------------------------------------------]
/**
*  @brief
*    Function that is called to create the application's renderer context
*/
void RenderApplication::OnCreateRendererContext()
{
	// Get the class name of the renderer to use
	const String sRenderer     = GetConfig().GetVar("PLScene::EngineGraphicConfig", "RendererAPI");
	const uint32 nRendererMode = GetConfig().GetVarInt("PLScene::EngineGraphicConfig", "RendererMode");

	// Get Z buffer bits (for example 24)
	const uint32 nZBufferBits = GetConfig().GetVarInt("PLEngine::RendererConfig", "ZBufferBits");

	// Stencil buffer bits (for example 8)
	const uint32 nStencilBits = GetConfig().GetVarInt("PLEngine::RendererConfig", "StencilBits");

	// Get the number of multisample antialiasing samples per pixel
	const uint32 nMultisampleAntialiasingSamples = GetConfig().GetVarInt("PLEngine::RendererConfig", "MultisampleAntialiasingSamples");

	// Get the name of the default shader language to use
	const String sDefaultShaderLanguage = GetConfig().GetVar("PLEngine::RendererConfig", "DefaultShaderLanguage");

	// Create and return renderer context instance
	m_pRendererContext = sRenderer.GetLength() ? RendererContext::CreateInstance(sRenderer, (Renderer::EMode)nRendererMode, nZBufferBits, nStencilBits, nMultisampleAntialiasingSamples, sDefaultShaderLanguage) : NULL;
	if (!m_pRendererContext) {
		// Error!
		PL_LOG(Error, "Can't create renderer context instance: " + sRenderer)
	} else {
		// Set texture manager settings
		TextureManager &cTextureManager = m_pRendererContext->GetTextureManager();
		cTextureManager.SetTextureQuality			(GetConfig().GetVar("PLEngine::RendererConfig", "TextureQuality").GetFloat());
		cTextureManager.SetTextureMipmapsAllowed	(GetConfig().GetVar("PLEngine::RendererConfig", "TextureMipmaps").GetBool());
		cTextureManager.SetTextureCompressionAllowed(GetConfig().GetVar("PLEngine::RendererConfig", "TextureCompression").GetBool());
	}
}

/**
*  @brief
*    Function that is called to create the application's surface painter
*/
void RenderApplication::OnCreatePainter()
{
	// Is there a renderer context?
	if (m_pRendererContext) {
		// Create and set the surface painter
		SetPainter(m_pRendererContext->GetRenderer().CreateSurfacePainter(m_sSurfacePainter));
	}
}

/**
*  @brief
*    Function that is called to initialize the application's virtual input controller
*/
void RenderApplication::OnCreateInputController()
{
	// Create virtual standard controller
	VirtualStandardController *pController = new VirtualStandardController();

	// Connect to physical devices
	pController->ConnectToDevices();

	// Set virtual input controller
	SetInputController(pController);
}

/**
*  @brief
*    Called when the display mode was changed
*/
void RenderApplication::OnDisplayMode()
{
	// Do nothing by default
}

/**
*  @brief
*    Called when the fullscreen mode was changed
*/
void RenderApplication::OnFullscreenMode()
{
	// Do nothing by default
}

/**
*  @brief
*    Function that is called once per update loop
*/
bool RenderApplication::OnUpdate()
{
	// Update input manager
	InputManager::GetInstance()->Update();

	// Update renderer context
	if (m_pRendererContext)
		m_pRendererContext->Update();

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when main window was destroyed
*/
void RenderApplication::NotifyDestroy()
{
	// Get the main widget
	const Widget *pWidget = GetMainWindow();
	if (pWidget && pWidget->IsInstanceOf("PLEngine::RenderWindow")) {
		// Write fullscreen state back to the configuration
		GetConfig().SetVar("PLEngine::RendererConfig", "Fullscreen", String::Format("%d", ((const RenderWindow*)pWidget)->IsFullscreen()));

		// Write down display mode information
		const DisplayMode &sDisplayMode = ((const RenderWindow*)pWidget)->GetDisplayMode();
		GetConfig().SetVar("PLEngine::RendererConfig", "DisplayWidth",     String::Format("%d", sDisplayMode.vSize.x));
		GetConfig().SetVar("PLEngine::RendererConfig", "DisplayHeight",    String::Format("%d", sDisplayMode.vSize.y));
		GetConfig().SetVar("PLEngine::RendererConfig", "DisplayColorBits", String::Format("%d", sDisplayMode.nColorBits));
		GetConfig().SetVar("PLEngine::RendererConfig", "DisplayFrequency", String::Format("%d", sDisplayMode.nFrequency));
	}
}

/**
*  @brief
*    Called when main window was (de-)activated
*/
void RenderApplication::NotifyActivate(bool bActivate)
{
	// Activate input controller when window is active, otherwise stop input
	if (m_pInputController) {
		m_pInputController->SetActive(bActivate);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
