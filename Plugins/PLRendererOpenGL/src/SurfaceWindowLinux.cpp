/*********************************************************\
 *  File: SurfaceWindowLinux.cpp                         *
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
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/SurfaceWindowHandler.h>
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/ContextLinux.h"
#include "PLRendererOpenGL/SurfaceWindow.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::SurfaceWindow functions    ]
//[-------------------------------------------------------]
bool SurfaceWindow::GetGamma(float &fRed, float &fGreen, float &fBlue) const
{
	// Get the Linux OpenGL render context
	ContextLinux *pContextLinux = static_cast<ContextLinux*>(static_cast<Renderer&>(GetRenderer()).GetContext());
	if (pContextLinux) {
		// Get the X server display connection
		Display *pDisplay = pContextLinux->GetDisplay();

		XF86VidModeGamma gamma;
		if (XF86VidModeGetGamma(pDisplay, XDefaultScreen(pDisplay), &gamma)) {
			fRed   = gamma.red;
			fGreen = gamma.green;
			fBlue  = gamma.blue;

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool SurfaceWindow::SetGamma(float fRed, float fGreen, float fBlue)
{
	if (static_cast<int>(fRed*10) <= 10 && static_cast<int>(fGreen*10) <= 10 && static_cast<int>(fBlue*10) <= 10) {
		// Get the Linux OpenGL render context
		ContextLinux *pContextLinux = static_cast<ContextLinux*>(static_cast<Renderer&>(GetRenderer()).GetContext());
		if (pContextLinux) {
			// Get the X server display connection
			Display *pDisplay = pContextLinux->GetDisplay();

			// Gamma was changed...
			m_bGammaChanged = true;

			// Call the OS gamma ramp function
			XF86VidModeGamma gamma;
			gamma.red   = fRed;
			gamma.green = fGreen;
			gamma.blue  = fBlue;
			if (XF86VidModeSetGamma(pDisplay, XDefaultScreen(pDisplay), &gamma))
				return true; // Done
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Surface functions         ]
//[-------------------------------------------------------]
bool SurfaceWindow::Init()
{
	// First check if there's a native window
	const handle nNativeWindowHandle = GetNativeWindowHandle();
	if (nNativeWindowHandle) {
		// Backup the native window handle
		m_nNativeWindowHandle = nNativeWindowHandle;

		// Backup gamma
		GetGamma(m_fGammaBackup[0], m_fGammaBackup[1], m_fGammaBackup[2]);
		m_bGammaChanged = false;

		// Is fullscreen?
		if (m_bIsFullscreen) {
			// Get the renderer instance
			Renderer &cRenderer = static_cast<Renderer&>(GetRenderer());

			// Get the Linux OpenGL render context
			ContextLinux *pContextLinux = static_cast<ContextLinux*>(cRenderer.GetContext());
			if (pContextLinux) {

				// Get the X server display connection
				Display *pDisplay = XOpenDisplay(nullptr);
				if (pDisplay) {
					const int nScreen = XDefaultScreen(pDisplay);

					// Find correct display mode
					int nDisplayMode = 0;
					bool bFound = false;
					int nNumOfModes = 0;
					
					XRRScreenConfiguration *pScreenConfig = nullptr;
					XRRScreenSize *pScreenSizeList = nullptr;
					
					pScreenConfig = XRRGetScreenInfo( pDisplay,
                               RootWindow( pDisplay, nScreen ) );
					
					pScreenSizeList = XRRConfigSizes( pScreenConfig, &nNumOfModes );
					
					if (!nNumOfModes) {
						PL_LOG(Error, "PLRendererOpenGL fullscreen mode: Couldn't get mode lines")
						
						XRRFreeScreenConfigInfo( pScreenConfig );
						// Close X server display connection
						XCloseDisplay(pDisplay);

						// Error!
						return false;
					}
					
					int nBestMode = 0;
					for(int i = 0; i < nNumOfModes; i++ )
					{
						if (m_sDisplayMode.vSize.x	  == pScreenSizeList[i].width &&
							m_sDisplayMode.vSize.y	  == pScreenSizeList[i].height) {
							nBestMode = i;
							bFound = true;
							break;
						}
					}
					if (bFound) {
						// Save desktop-resolution before switching modes
						m_nOldSizeID = XRRConfigCurrentConfiguration( pScreenConfig, &m_nOldRotation );

						// Change display settings
						PL_LOG(Info, "PLRendererOpenGL fullscreen mode: Go into fullscreen mode")
						
						cRenderer.BackupDeviceObjects();
						
						Status status = XRRSetScreenConfig( pDisplay,
                                pScreenConfig,
                                RootWindow( pDisplay, nScreen ),
                                nBestMode,
                                RR_Rotate_0,
                                CurrentTime );

						if (status != RRSetConfigSuccess) {
 							PL_LOG(Error, "PLRendererOpenGL fullscreen mode: Couldn't set display mode!")
 							m_bIsFullscreen = false;
 							XRRFreeScreenConfigInfo( pScreenConfig );
							// Close X server display connection
							XCloseDisplay(pDisplay);
 
 							// Error!
 							return false;
 						}
						XRRFreeScreenConfigInfo( pScreenConfig );
						cRenderer.RestoreDeviceObjects();
					} else {
						PL_LOG(Error, "PLRendererOpenGL fullscreen mode: No correct display setting was found, can't change to fullscreen!")
						m_bIsFullscreen = false;
					}	
				}
				// Close X server display connection
				XCloseDisplay(pDisplay);
			}
		}

	}

	// Done
	return true;
}

void SurfaceWindow::DeInit()
{
	// First check if there's a native window handle
	if (m_nNativeWindowHandle) {
		// We're going to perform a cruel act - so give OpenGL a chance to flush and finish it's data...
		// just so be on the safe side, you never now...
		glFinish();
		
		// Get the renderer instance
		Renderer &cRenderer = static_cast<Renderer&>(GetRenderer());

		// If this is the current render target, make the main window to the new current one
		if (cRenderer.GetRenderTarget() == this)
			cRenderer.SetRenderTarget(nullptr);

		// Reset gamma - but only when the gamma was changed by using "SetGamma()"
		if (m_bGammaChanged) {
			SetGamma(m_fGammaBackup[0], m_fGammaBackup[1], m_fGammaBackup[2]);
			m_bGammaChanged = false;
		}

		// Is fullscreen?
		if (m_bIsFullscreen) {
			// Get the Linux OpenGL render context
			ContextLinux *pContextLinux = static_cast<ContextLinux*>(cRenderer.GetContext());
			if (pContextLinux) {
				// Get the X server display connection
				Display *pDisplay = XOpenDisplay(nullptr);
				if (pDisplay) {
					// Reset display settings
					PL_LOG(Info, "PLRendererOpenGL fullscreen mode: Set display mode to default")
					const int nScreen = XDefaultScreen(pDisplay);
					
					cRenderer.BackupDeviceObjects();
					
					XRRScreenConfiguration *pScreenConfig;

					pScreenConfig = XRRGetScreenInfo( pDisplay, RootWindow( pDisplay, nScreen ) );
					
					XRRSetScreenConfig( pDisplay,
										pScreenConfig,
										RootWindow( pDisplay, nScreen ),
										m_nOldSizeID,
										m_nOldRotation,
										CurrentTime );

					XRRFreeScreenConfigInfo( pScreenConfig );
					
					cRenderer.RestoreDeviceObjects();
					// Close X server display connection
					XCloseDisplay(pDisplay);
				}
			}
		}
	}
}

bool SurfaceWindow::MakeCurrent(uint8 nFace)
{
	// First check if there's a native window handle
	if (m_nNativeWindowHandle) {
		// Get the Linux OpenGL render context
		ContextLinux *pContextLinux = static_cast<ContextLinux*>(static_cast<Renderer&>(GetRenderer()).GetContext());
		if (pContextLinux) {
			// Make this surface current
			return glXMakeCurrent(pContextLinux->GetDisplay(), m_nNativeWindowHandle, pContextLinux->GetRenderContext());
		}
	}

	// Error!
	return false;
}

bool SurfaceWindow::Present()
{
	// First check if there's a native window handle
	if (m_nNativeWindowHandle) {
		// Get the Linux OpenGL render context
		Renderer &cRenderer = static_cast<Renderer&>(GetRenderer());
		ContextLinux *pContextLinux = static_cast<ContextLinux*>(cRenderer.GetContext());
		if (pContextLinux) {
			// Swap interval (vertical synchronisation) setting changed? (this setting is connected with the window, therefore we must do this update for every window)
			if (m_nSwapInterval != static_cast<int>(cRenderer.GetSwapInterval())) {
				m_nSwapInterval = cRenderer.GetSwapInterval();
				if (cRenderer.IsGLX_SGI_swap_control())
					glXSwapIntervalSGI(m_nSwapInterval);
			}

			// Swap buffers
			glXSwapBuffers(pContextLinux->GetDisplay(), m_nNativeWindowHandle);
		}

		// Done
		return true;
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
