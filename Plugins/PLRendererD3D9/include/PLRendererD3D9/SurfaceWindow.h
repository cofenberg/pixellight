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


#ifndef __PLRENDERERD3D9_SURFACEWINDOW_H__
#define __PLRENDERERD3D9_SURFACEWINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/Event.h>
#include <PLRenderer/Renderer/SurfaceWindow.h>
#include "PLRendererD3D9/PLRendererD3D9.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class Vector2i;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererD3D9 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A Direct3D 9 window renderer surface where we can render in
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
		*  @param[in] bFullscreen
		*    Fullscreen mode?
		*/
		SurfaceWindow(PLRenderer::SurfaceWindowHandler &cHandler, PLGeneral::handle nWindow, bool bFullscreen = false);

		/**
		*  @brief
		*    Called when the window size has been changed
		*
		*  @param[in] vSize
		*    New window size
		*/
		void OnSize(const PLMath::Vector2i &vSize);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<const PLMath::Vector2i &> EventHandlerSize;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		IDirect3DSwapChain9 *m_pSwapChain;
		LPDIRECT3DSURFACE9   m_pBackBuffer;


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
		virtual bool UnmakeCurrent();
		virtual bool Present();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D9


#endif // __PLRENDERERD3D9_SURFACEWINDOW_H__
