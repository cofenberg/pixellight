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


#ifndef __PLRENDERER_SURFACE_WINDOW_H__
#define __PLRENDERER_SURFACE_WINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Renderer/Surface.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class SurfaceWindowHandler;
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
*    A window renderer surface where we can render in
*/
class SurfaceWindow : public Surface {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SurfaceWindowHandler;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~SurfaceWindow();

		/**
		*  @brief
		*    Returns the renderer surface handler this surface is assigned with
		*
		*  @return
		*    The renderer surface handler this surface is assigned with, can be NULL
		*/
		PLRENDERER_API SurfaceWindowHandler *GetHandler() const;

		/**
		*  @brief
		*    Returns the native window the surface is assigned with
		*
		*  @return
		*    The native window the surface is assigned with, can be NULL
		*/
		PLRENDERER_API PLGeneral::handle GetWindow() const;

		/**
		*  @brief
		*    Returns whether the window is in fullscreen mode or not
		*
		*  @return
		*    'true' if the window is in fullscreen mode, else 'false'
		*/
		PLRENDERER_API bool IsFullscreen() const;


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Gets the current gamma components
		*
		*  @param[out] fRed
		*    Receives the red gamma component value
		*  @param[out] fGreen
		*    Receives the green gamma component value
		*  @param[out] fBlue
		*    Receives the blue gamma component value
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*    (e.g. device does not support gamma correction)
		*/
		virtual bool GetGamma(float &fRed, float &fGreen, float &fBlue) const = 0;

		/**
		*  @brief
		*    Sets the current gamma components
		*
		*  @param[in] fRed
		*    Red gamma component value
		*  @param[in] fGreen
		*    Green gamma component value
		*  @param[in] fBlue
		*    Blue gamma component value
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*    (e.g. device does not support gamma correction)
		*/
		virtual bool SetGamma(float fRed = 1.0f, float fGreen = 1.0f, float fBlue = 1.0f) = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cHandler
		*    Renderer surface handler this surface is assigned with (MUST be valid!)
		*  @param[in] nWindow
		*    Window the surface is assigned with
		*  @param[in] bFullscreen
		*    Fullscreen mode?
		*/
		PLRENDERER_API SurfaceWindow(SurfaceWindowHandler &cHandler, PLGeneral::handle nWindow, bool bFullscreen = false);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		bool m_bIsFullscreen;	/**< Is this window in fullscreen mode? */


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
		SurfaceWindow(const SurfaceWindow &cSource);

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
		SurfaceWindow &operator =(const SurfaceWindow &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		SurfaceWindowHandler *m_pHandler;	/**< Renderer surface handler this surface
												 is assigned with, can be NULL */
		PLGeneral::handle	  m_nWindow;	/**< Window the surface is assigned with, can be NULL */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_SURFACE_WINDOW_H__
