/*********************************************************\
 *  File: SurfaceWindowHandler.h                         *
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


#ifndef __PLRENDERER_SURFACE_WINDOW_HANDLER_H__
#define __PLRENDERER_SURFACE_WINDOW_HANDLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneral.h>
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	struct DisplayMode;
	class Surface;
	class Renderer;
	class SurfaceHandler;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A renderer surface window handler will be informed automatically
*    if it's renderer surface is destroyed
*/
class SurfaceWindowHandler {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SurfaceWindow;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLRENDERER_API SurfaceWindowHandler();

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~SurfaceWindowHandler();

		/**
		*  @brief
		*    Returns the owner renderer
		*
		*  @return
		*    The owner renderer, can be NULL
		*/
		PLRENDERER_API Renderer *GetRenderer() const;

		/**
		*  @brief
		*    Returns the renderer surface of this handler
		*
		*  @return
		*    The renderer surface of this handler, can be NULL
		*/
		PLRENDERER_API Surface *GetSurface() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Initializes the surface window handler
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*  @param[in] nWindow
		*    Native window of renderer surface handler is assigned with
		*  @param[in] sDisplayMode
		*    Display mode information
		*  @param[in] bFullscreen
		*    Fullscreen mode?
		*/
		PLRENDERER_API void Init(Renderer &cRenderer, PLGeneral::handle nWindow, const DisplayMode &sDisplayMode, bool bFullscreen = false);

		/**
		*  @brief
		*    De-initializes the surface window handler
		*/
		PLRENDERER_API void DeInit();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Renderer	   *m_pRenderer;		/**< Owner renderer (can be NULL) */
		SurfaceHandler *m_pSurfaceHandler;	/**< The renderer surface handler (NEVER NULL!) */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		SurfaceWindowHandler(const SurfaceWindowHandler &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		SurfaceWindowHandler &operator =(const SurfaceWindowHandler &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_SURFACE_WINDOW_HANDLER_H__
