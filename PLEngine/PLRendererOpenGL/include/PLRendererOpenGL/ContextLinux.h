/*********************************************************\
 *  File: ContextLinux.h                                 *
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


#ifndef __PLRENDEREROPENGL_CONTEXTLINUX_H__
#define __PLRENDEREROPENGL_CONTEXTLINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <X11/Xutil.h>
#include <X11/extensions/xf86vmode.h>
#include <GL/glx.h>
#include "PLRendererOpenGL/Context.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linux OpenGL context
*/
class ContextLinux : public Context {


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		ContextLinux();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ContextLinux();

		/**
		*  @brief
		*    Returns the X server display connection
		*
		*  @return
		*    The X server display connection, a null pointer on error
		*/
		Display *GetDisplay() const;

		/**
		*  @brief
		*    Returns the primary render context
		*
		*  @return
		*    The primary render context, a null pointer on error
		*/
		GLXContext GetRenderContext() const;


	//[-------------------------------------------------------]
	//[ Public virtual Context methods                        ]
	//[-------------------------------------------------------]
	public:
		virtual bool IsValid() const;
		virtual void MakeDummyCurrent() const;
		virtual bool QueryDisplayModes(PLGeneral::Array<const PLRenderer::DisplayMode*> &lstDisplayModeList);
		virtual void SwapInterval(bool bEnabled);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Display     *m_pDisplay;					/**< X server display connection, a null pointer on error */
		Window       m_hDummyNativeWindow;			/**< Native dummy window, always valid */
		XVisualInfo *m_pDummyVisualInfo;
		GLXContext	 m_hDummyWindowRenderContext;	/**< The render context of the OpenGL dummy window, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_CONTEXTLINUX_H__
