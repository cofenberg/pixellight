/*********************************************************\
 *  File: Context.h                                      *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLRENDEREROPENGLES2_CONTEXT_H__
#define __PLRENDEREROPENGLES2_CONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#if (defined(LINUX) && !defined(ANDROID))
	#include <X11/Xutil.h>	// For "Display"
#endif
#include <EGL/egl.h>
#undef Yield 		// We undef this to avoid name conflicts with OS macros, why do they need to use macros?!
#undef Success		// We undef this to avoid name conflicts with OS macros, why do they need to use macros?!
#undef None			// We undef this to avoid name conflicts with OS macros, why do they need to use macros?!
#undef Always		// We undef this to avoid name conflicts with OS macros, why do they need to use macros?!
#undef GetClassName // We undef this to avoid name conflicts with OS macros, why do they need to use macros?!
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <PLCore/Core/AbstractContext.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Renderer;
class Extensions;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract OpenGL ES context base class
*/
class Context : public PLCore::AbstractContext {


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Context();

		/**
		*  @brief
		*    Returns the owner renderer
		*
		*  @return
		*    The owner renderer
		*/
		Renderer &GetRenderer() const;

		/**
		*  @brief
		*    Returns the handle of a native OS window which is valid as long as the renderer instance exists
		*
		*  @return
		*    The handle of a native OS window which is valid as long as the renderer instance exists, "NULL_HANDLE" if there's no such window
		*/
		PLCore::handle GetNativeWindowHandle() const;

		/**
		*  @brief
		*    Returns the used EGL display
		*
		*  @return
		*    The used EGL display
		*/
		EGLDisplay GetEGLDisplay() const;

		/**
		*  @brief
		*    Returns the used EGL config
		*
		*  @return
		*    The used EGL config
		*/
		EGLConfig GetEGLConfig() const;

		/**
		*  @brief
		*    Returns the used EGL context
		*
		*  @return
		*    The used EGL context
		*/
		EGLContext GetEGLContext() const;

		/**
		*  @brief
		*    Returns the used EGL dummy surface
		*
		*  @return
		*    The used EGL dummy surface
		*/
		EGLSurface GetEGLDummySurface() const;

		/**
		*  @brief
		*    Makes a given EGL surface to the currently used one
		*
		*  @param[in] hEGLSurface
		*    EGL surface to make to the current one, can be a null pointer, in this case an internal dummy surface is set
		*
		*  @return
		*    'EGL_TRUE' if all went fine, else 'EGL_FALSE'
		*/
		EGLBoolean MakeCurrent(EGLSurface hEGLSurface);


	//[-------------------------------------------------------]
	//[ Public virtual Context functions                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Initialize the context
		*
		*  @param[in] nMultisampleAntialiasingSamples
		*    Multisample antialiasing samples per pixel, <=1 means no antialiasing
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Init(PLCore::uint32 nMultisampleAntialiasingSamples);

		/**
		*  @brief
		*    Returns the available extensions
		*
		*  @return
		*    The available extensions
		*/
		virtual const Extensions &GetExtensions() const = 0;


	//[-------------------------------------------------------]
	//[ Protected methods                                     ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    The owner renderer
		*  @param[in] nNativeWindowHandle
		*    Handle of a native OS window which is valid as long as the renderer instance exists, "NULL_HANDLE" if there's no such window
		*/
		Context(Renderer &cRenderer, PLCore::handle nNativeWindowHandle);

		/**
		*  @brief
		*    De-initialize the context
		*/
		void DeInit();


	//[-------------------------------------------------------]
	//[ Protected virtual Context functions                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Chooses a EGL config
		*
		*  @param[in] nMultisampleAntialiasingSamples
		*    Multisample antialiasing samples per pixel
		*
		*  @return
		*    The chosen EGL config, a null pointer on error
		*
		*  @note
		*    - Automatically tries to find fallback configurations
		*/
		virtual EGLConfig ChooseConfig(PLCore::uint32 nMultisampleAntialiasingSamples) const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Renderer		   *m_pRenderer;			/**< The owner renderer, always valid! */
		PLCore::handle		m_nNativeWindowHandle;	/**< Handle of a native OS window which is valid as long as the renderer instance exists, "NULL_HANDLE" if there's no such window */
		// X11
		#if (defined(LINUX) && !defined(ANDROID))
			::Display	   *m_pX11Display;
		#endif
		// EGL
		EGLDisplay			m_hDisplay;
		// EGL
		EGLConfig			m_hConfig;
		EGLContext			m_hContext;
		EGLNativeWindowType	m_nDummyNativeWindow;	/**< Native dummy window handle, can be identical to "m_nNativeWindowHandle" if it's in fact no dummy at all, can be "NULL_HANDLE" */
		EGLSurface			m_hDummySurface;


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
		Context(const Context &cSource);

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
		Context &operator =(const Context &cSource);

		/**
		*  @brief
		*    Shows some OpenGL ES information
		*/
		void ShowOpenGLESInformation();

		/**
		*  @brief
		*    Writes the extensions within a given extension string into the log
		*
		*  @param[in] pszExtensions
		*    Extension string, if a null pointer, nothing happens
		*/
		void WriteExtensionStringIntoLog(const char *pszExtensions) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2


//[-------------------------------------------------------]
//[ Implementation includes                               ]
//[-------------------------------------------------------]
#include "PLRendererOpenGLES2/ContextRuntimeLinking.h"	// Required in here because we redefine the OpenGL ES 2.0 functions for dynamic runtime linking


#endif // __PLRENDEREROPENGLES2_CONTEXT_H__
