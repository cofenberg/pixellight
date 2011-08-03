/*********************************************************\
 *  File: RenderApplication.cpp                         *
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
#include <PLCore/Log/Log.h>
#include <PLCore/Tools/Timing.h>
#include <PLCore/System/System.h>
#include <PLCore/Frontend/Frontend.h>
#include <PLInput/Input/InputManager.h>
#include <PLInput/Input/Virtual/VirtualController.h>
#include <PLInput/Input/Virtual/VirtualStandardController.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/Surface.h>
#include <PLRenderer/Renderer/FontManager.h>
#include <PLRenderer/Renderer/SurfacePainter.h>
#include <PLRenderer/Texture/TextureManager.h>
#include "PLEngine/Application/RenderApplication.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLInput;
using namespace PLRenderer;
namespace PLEngine {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(RenderApplication)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RenderApplication::RenderApplication(const String &sSurfacePainter) : FrontendApplication(),
	m_sSurfacePainter(sSurfacePainter),
	m_pRendererContext(nullptr),
	m_pInputController(nullptr)
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
	// Get the surface
	const Surface *pSurface = GetSurface();
	if (pSurface) {
		// Return painter
		return pSurface->GetPainter();
	}

	// Error!
	return nullptr;
}

/**
*  @brief
*    Set surface painter of the main window
*/
void RenderApplication::SetPainter(SurfacePainter *pPainter)
{
	// Get the surface
	Surface *pSurface = GetSurface();
	if (pSurface) {
		// Set painter
		pSurface->SetPainter(pPainter);
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
	// [TODO]
	/*
	// Get the main widget
	Widget *pWidget = GetMainWindow();
	if (pWidget && pWidget->IsInstanceOf("PLEngine::RenderWindow")) {
		// Return the current state
		return static_cast<RenderWindow*>(pWidget)->IsFullscreen();
	}*/

	// Error!
	return false;
}

/**
*  @brief
*    Sets whether or not the main window is currently fullscreen or not
*/
void RenderApplication::SetFullscreen(bool bFullscreen)
{
	// [TODO]
	/*
	// Get the main widget
	Widget *pWidget = GetMainWindow();
	if (pWidget && pWidget->IsInstanceOf("PLEngine::RenderWindow")) {
		// Set the current state
		static_cast<RenderWindow*>(pWidget)->SetFullscreen(bFullscreen);
	}
	*/
}

/**
*  @brief
*    Update application
*/
bool RenderApplication::Update(bool bForceUpdate)
{
	// Force or is it time for an update?
	if (bForceUpdate) {
		// Update timing
		Timing::GetInstance()->Update();

		// Call the application's update function
		return OnUpdate();
	} else {
		// Check if we're allowed to perform an update right now
		uint64 nTimeToWait = 0;
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
//[ Protected virtual PLCore::ConsoleApplication functions ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initialization function that is called prior to OnInit()
*/
bool RenderApplication::Init()
{
	// Call base implementation
	if (FrontendApplication::Init()) {
		// Create renderer context
		OnCreateRendererContext();
		if (!m_bRunning)
			return false;

		// Check if a renderer context has been created
		if (m_pRendererContext) {
			// [TODO] Shouldn't this be done rather inside FontManager itself? What happens if we do not set a default
			//        font here, do we then have no font at all? Or ist the a default-default-font in FontManager?

			// Create default font
			PLRenderer::FontManager &cFontManager = m_pRendererContext->GetRenderer().GetFontManager();
			const String sDefaultFontTexture     = GetConfig().GetVar("PLScene::EngineGraphicConfig", "DefaultFontTexture");
			const uint32 nDefaultFontTextureSize = GetConfig().GetVar("PLScene::EngineGraphicConfig", "DefaultFontTextureSize").GetInt();
			cFontManager.SetDefaultFontTexture(cFontManager.GetFontTexture(sDefaultFontTexture, nDefaultFontTextureSize));

			// Create surface painter
			OnCreatePainter();
			if (!m_bRunning)
				return false;

			// Initialize input system
			InputManager::GetInstance()->DetectDevices();

			// Create virtual input controller
			OnCreateInputController();
			if (!m_bRunning)
				return false;

			// Done
			return true;
		}
	}

	// Error
	return false;
}

/**
*  @brief
*    De-initialization function that is called after OnDeInit()
*/
void RenderApplication::DeInit()
{
	// Destroy renderer context
	if (m_pRendererContext) {
		delete m_pRendererContext;
		m_pRendererContext = nullptr;
	}

	// Destroy virtual input controller
	if (m_pInputController) {
		delete m_pInputController;
		m_pInputController = nullptr;
	}

	// Call base implementation
	FrontendApplication::DeInit();
}


//[-------------------------------------------------------]
//[ Protected virtual PLCore::FrontendApplication functions ]
//[-------------------------------------------------------]
void RenderApplication::OnDraw()
{
	Update();
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
	m_pRendererContext = sRenderer.GetLength() ? RendererContext::CreateInstance(sRenderer, static_cast<Renderer::EMode>(nRendererMode), nZBufferBits, nStencilBits, nMultisampleAntialiasingSamples, sDefaultShaderLanguage) : nullptr;
	if (!m_pRendererContext) {
		// Error!
		PL_LOG(Error, "Can't create renderer context instance: " + sRenderer)
	} else {
		// Set the swap interval (vertical synchronisation)
		m_pRendererContext->GetRenderer().SetSwapInterval(GetConfig().GetVar("PLEngine::RendererConfig", "SwapInterval").GetUInt32());

		// Set texture manager settings
		TextureManager &cTextureManager = m_pRendererContext->GetTextureManager();
		cTextureManager.SetTextureQuality			(GetConfig().GetVar("PLEngine::RendererConfig", "TextureQuality").GetFloat());
		cTextureManager.SetTextureMipmapsAllowed	(GetConfig().GetVar("PLEngine::RendererConfig", "TextureMipmaps").GetBool());
		cTextureManager.SetTextureCompressionAllowed(GetConfig().GetVar("PLEngine::RendererConfig", "TextureCompression").GetBool());

		// [TODO] Move this somewere else
		Frontend *pFrontend = GetFrontend();
		if (pFrontend) {
			// [TODO] No build in options
			DisplayMode sDisplayMode;
			sDisplayMode.vSize.x = pFrontend->GetWidth();
			sDisplayMode.vSize.y = pFrontend->GetHeight();
			sDisplayMode.nColorBits = 32;
			sDisplayMode.nFrequency = 60;
			SurfaceWindowHandler::Init(m_pRendererContext->GetRenderer(), pFrontend->GetNativeWindowHandle(), sDisplayMode);
		}
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
