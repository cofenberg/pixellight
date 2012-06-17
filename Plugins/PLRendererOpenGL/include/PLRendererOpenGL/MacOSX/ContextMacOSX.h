/*********************************************************\
 *  File: ContextMacOSX.h                                *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLRENDEREROPENGL_CONTEXTMACOSX_H__
#define __PLRENDEREROPENGL_CONTEXTMACOSX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <OpenGL/CGLTypes.h>
#include "PLRendererOpenGL/Context.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Renderer;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mac OS X OpenGL context
*
*  @remarks
*    According to http://www.opengl.org/wiki/Programming_OpenGL_on_Mac_OS_X there are several relevant API's on Mac OS X:
*    - AGL/Carbon: "AGL is the old Carbon-based API with C bindings" (see http://developer.apple.com/library/mac/#documentation/GraphicsImaging/Reference/AGL_OpenGL/Reference/reference.html)
*    - Cocoa/NSOpenGL (aka NSGL): "Cocoa is the modern API with Objective-C bindings"
*    -> Both building on top of the low level CGL (Core OpenGL) (see http://developer.apple.com/library/mac/#documentation/GraphicsImaging/Reference/CGL_OpenGL/Reference/reference.html)
*    -> To keep things maintainable, we're only supporting the modern CGL/Cocoa/NSOpenGL way.
*/
class ContextMacOSX : public Context {


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    The owner renderer
		*/
		ContextMacOSX(Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ContextMacOSX();

		/**
		*  @brief
		*    Returns the primary render context
		*
		*  @return
		*    The primary render context, a null pointer on error
		*/
		CGLContextObj GetRenderContext() const;


	//[-------------------------------------------------------]
	//[ Public virtual Context methods                        ]
	//[-------------------------------------------------------]
	public:
		virtual bool IsValid() const override;
		virtual void MakeDummyCurrent() const override;
		virtual bool QueryDisplayModes(PLCore::Array<const PLRenderer::DisplayMode*> &lstDisplayModeList) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Renderer	  *m_pRenderer;			/**< The owner renderer, always valid! */
		CGLContextObj  m_pCGLContextObj;	/**< Pointer to an opaque CGL context object, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_CONTEXTMACOSX_H__
