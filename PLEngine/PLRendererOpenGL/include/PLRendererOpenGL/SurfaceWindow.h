/*********************************************************\
 *  File: SurfaceWindow.h                                *
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


#ifndef __PLRENDEREROPENGL_SURFACE_WINDOW_H__
#define __PLRENDEREROPENGL_SURFACE_WINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/SurfaceWindow.h>
#ifdef WIN32
	#include <PLGeneral/PLGeneralWindowsIncludes.h>
#endif
#ifdef LINUX
	#include <X11/Xutil.h>
	#include <X11/extensions/xf86vmode.h>
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A OpenGL window renderer surface where we can render in
*/
class SurfaceWindow : public PLRenderer::SurfaceWindow {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Renderer;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SurfaceWindow();

	#ifdef WIN32
		/**
		*  @brief
		*    Returns the private GDI device context
		*
		*  @return
		*    Private GDI device context
		*/
		HDC GetDevice() const;

		/**
		*  @brief
		*    Returns the visual
		*
		*  @return
		*    Visual (for Windows the same as GetDevice())
		*/
		HDC GetVisual() const;
	#endif


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cHandler
		*    Renderer surface handler this surface is assigned with (MUST be valid!)
		*  @param[in] nWindow
		*    Handle to the native window the renderer surface is assigned with
		*  @param[in] sDisplayMode
		*    Display mode information
		*  @param[in] bFullscreen
		*    Fullscreen mode?
		*/
		SurfaceWindow(PLRenderer::SurfaceWindowHandler &cHandler, PLGeneral::handle nWindow, const PLRenderer::DisplayMode &sDisplayMode, bool bFullscreen = false);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::DisplayMode m_sDisplayMode;	/**< Display mode information */
	#ifdef WIN32
		HDC m_hDC;	/**< Private GDI device context */
	#endif
	#ifdef LINUX
		::Window			m_nWindow;
		XF86VidModeModeInfo	m_sDesktopModeBackup;	/**< Saved desktop-resolution before switching modes */
	#endif
		float m_fGammaBackup[3];	/**< Gamma settings at the time the render window was initialized */
		bool  m_bGammaChanged;		/**< Was the gamma changed by using "SetGamma"? */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::SurfaceWindow functions    ]
	//[-------------------------------------------------------]
	public:
		virtual bool GetGamma(float &fRed, float &fGreen, float &fBlue) const;
		virtual bool SetGamma(float fRed = 1.0f, float fGreen = 1.0f, float fBlue = 1.0f);


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Surface functions          ]
	//[-------------------------------------------------------]
	public:
		virtual PLMath::Vector2i GetSize() const;


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::Surface functions         ]
	//[-------------------------------------------------------]
	private:
		virtual bool Init();
		virtual void DeInit();
		virtual bool MakeCurrent(PLGeneral::uint8 nFace = 0);
		virtual bool Present();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_SURFACE_WINDOW_H__
