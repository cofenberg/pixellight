/*********************************************************\
 *  File: Context.cpp                                    *
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
#include "PLRendererOpenGLES2/Context.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Public methods                                        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
Context::~Context()
{
	// Everything must be done in "DeInit()" because when we're in here, the dynamic libraries
	// are already unloaded and we are no longer allowed to use EGL or OpenGL ES 2.0 functions
}

/**
*  @brief
*    Returns the owner renderer
*/
Renderer &Context::GetRenderer() const
{
	return *m_pRenderer;
}

/**
*  @brief
*    Returns the handle of a native OS window which is valid as long as the renderer instance exists
*/
handle Context::GetNativeWindowHandle() const
{
	return m_nNativeWindowHandle;
}

/**
*  @brief
*    Returns the used EGL display
*/
EGLDisplay Context::GetEGLDisplay() const
{
	return m_hDisplay;
}

/**
*  @brief
*    Returns the used EGL config
*/
EGLConfig Context::GetEGLConfig() const
{
	return m_hConfig;
}

/**
*  @brief
*    Returns the used EGL context
*/
EGLContext Context::GetEGLContext() const
{
	return m_hContext;
}

/**
*  @brief
*    Returns the used EGL dummy surface
*/
EGLSurface Context::GetEGLDummySurface() const
{
	return m_hDummySurface;
}

/**
*  @brief
*    Makes a given EGL surface to the currently used one
*/
EGLBoolean Context::MakeCurrent(EGLSurface hEGLSurface)
{
	// Use the EGL dummy surface?
	if (!hEGLSurface)
		hEGLSurface = m_hDummySurface;

	// Make the EGL surface to the current one
	return eglMakeCurrent(m_hDisplay, hEGLSurface, hEGLSurface, m_hContext);
}


//[-------------------------------------------------------]
//[ Public virtual Context functions                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initialize the context
*/
bool Context::Init(uint32 nMultisampleAntialiasingSamples)
{
	// Get display
	#if (defined(LINUX) && !defined(ANDROID))
		m_hDisplay = eglGetDisplay(static_cast<EGLNativeDisplayType>(m_pX11Display));
	#else
		m_hDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	#endif
	if (m_hDisplay != EGL_NO_DISPLAY) {
		// Initialize EGL
		EGLint nEGLMajorVersion, nEGLMinorVersion;
		if (eglInitialize(m_hDisplay, &nEGLMajorVersion, &nEGLMinorVersion) == EGL_TRUE) {
			{ // Output log information
				PL_LOG(Info, String::Format("Initialized EGL version %d.%d", nEGLMajorVersion, nEGLMinorVersion))
				// EGL_VENDOR
				const char *pszResult = eglQueryString(m_hDisplay, EGL_VENDOR);
				PL_LOG(Info, String::Format("EGL vendor: %s", pszResult ? pszResult : "-"))
				// EGL_VERSION
				pszResult = eglQueryString(m_hDisplay, EGL_VERSION);
				PL_LOG(Info, String::Format("EGL version: %s", pszResult ? pszResult : "-"))
				// EGL_EXTENSIONS
				pszResult = eglQueryString(m_hDisplay, EGL_EXTENSIONS);
				PL_LOG(Info, String::Format("Supported EGL extensions: %s", pszResult ? pszResult : "-"))
				// EGL_CLIENT_APIS
				pszResult = eglQueryString(m_hDisplay, EGL_CLIENT_APIS);
				PL_LOG(Info, String::Format("Supported EGL client rendering APIs: %s", pszResult ? pszResult : "-"))
			}

			// Choose a EGL configuration
			m_hConfig = ChooseConfig(nMultisampleAntialiasingSamples);

			// We can only go on if a EGL configuration was chosen properly
			if (m_hConfig) {
				// Create context
				EGLint pContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
				m_hContext = eglCreateContext(m_hDisplay, m_hConfig, EGL_NO_CONTEXT, pContextAttribs);
				if (m_hContext != EGL_NO_CONTEXT) {
					// Create a dummy native window?
					if (m_nNativeWindowHandle) {
						// There's no need to create a dummy native window, we've got a real native window to work with :D
						m_nDummyNativeWindow = (EGLNativeWindowType)m_nNativeWindowHandle;	// Interesting - in here, we have an OS dependent cast issue when using C++ casts: While we would need
																							// reinterpret_cast<EGLNativeWindowType>(nNativeWindowHandle) under MS Windows ("HWND"), we would need static_cast<EGLNativeWindowType>(nNativeWindowHandle)
																							// under Linux ("int")... so, to avoid #ifdefs, we just use old school c-style casts in here...

						#ifdef ANDROID
							// Reconfigure the ANativeWindow buffers to match
							EGLint nFormat;
							eglGetConfigAttrib(m_hDisplay, m_hConfig, EGL_NATIVE_VISUAL_ID, &nFormat);
							ANativeWindow_setBuffersGeometry(reinterpret_cast<ANativeWindow*>(m_nNativeWindowHandle), 0, 0, nFormat);
						#endif
					} else {
						// Create the dummy native window
						#ifdef WIN32
							HINSTANCE hModuleHandle = GetModuleHandle(nullptr);
							WNDCLASS sWindowClass;
							sWindowClass.hInstance		= hModuleHandle;
							sWindowClass.lpszClassName	= TEXT("PLOpenGLESDummyNativeWindow");
							sWindowClass.lpfnWndProc	= DefWindowProc;
							sWindowClass.style			= 0;
							sWindowClass.hIcon			= nullptr;
							sWindowClass.hCursor		= nullptr;
							sWindowClass.lpszMenuName	= nullptr;
							sWindowClass.cbClsExtra		= 0;
							sWindowClass.cbWndExtra		= 0;
							sWindowClass.hbrBackground	= nullptr;
							RegisterClass(&sWindowClass);
							m_nDummyNativeWindow = CreateWindow(TEXT("PLOpenGLESDummyNativeWindow"), TEXT("PFormat"), WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, 8, 8, HWND_DESKTOP, nullptr, hModuleHandle, nullptr);
						#endif
						#if (defined(LINUX) && !defined(ANDROID))
							// Create dummy window
							XSetWindowAttributes sSetWindowAttributes;
							sSetWindowAttributes.event_mask   = 0;
							sSetWindowAttributes.border_pixel = 0;
							m_nDummyNativeWindow = XCreateWindow(m_pX11Display, DefaultRootWindow(m_pX11Display), 0, 0, 300, 300, 0,
																 CopyFromParent, InputOutput, CopyFromParent,
																 CWBorderPixel|CWEventMask, &sSetWindowAttributes);
						#endif
					}

					// Create an EGL dummy surface
					m_hDummySurface = eglCreateWindowSurface(m_hDisplay, m_hConfig, m_nDummyNativeWindow, nullptr);
					if (m_hDummySurface == EGL_NO_SURFACE) {
						// Error!
						PL_LOG(Error, "Failed to create EGL dummy surface!")
					}

					// Make the internal dummy surface to the currently used one
					if (MakeCurrent(EGL_NO_SURFACE) == EGL_FALSE) {
						// Error!
						PL_LOG(Error, "Failed to make the EGL dummy surface to the current one!")
					}

					// Show some OpenGL ES information
					ShowOpenGLESInformation();

					// Done
					return true;
				} else {
					// Error!
					PL_LOG(Error, "Failed to create EGL context!")
				}
			} else {
				// Error!
				PL_LOG(Error, "Failed to choose EGL configuration! (OpenGL ES 2.0 not supported?)")
			}
		} else {
			// Error!
			PL_LOG(Error, "Failed to initialize EGL!")
		}
	} else {
		// Error!
		PL_LOG(Error, "Failed to get EGL default display!")
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Protected methods                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Context::Context(Renderer &cRenderer, handle nNativeWindowHandle) :
	m_pRenderer(&cRenderer),
	m_nNativeWindowHandle(nNativeWindowHandle),
	#if (defined(LINUX) && !defined(ANDROID))
		m_pX11Display(XOpenDisplay(nullptr)),
	#endif
	m_hDisplay(EGL_NO_DISPLAY),
	m_hConfig(nullptr),
	m_hContext(EGL_NO_CONTEXT),
	m_nDummyNativeWindow(NULL_HANDLE),
	m_hDummySurface(EGL_NO_SURFACE)
{
}

/**
*  @brief
*    De-initialize the context
*/
void Context::DeInit()
{
	// Don't touch anything in case we don't have a display
	if (m_hDisplay != EGL_NO_DISPLAY) {
		// Make 'nothing' current
		eglMakeCurrent(m_hDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

		// Destroy the EGL dummy surface
		if (m_hDummySurface != EGL_NO_SURFACE && eglDestroySurface(m_hDisplay, m_hDummySurface) == EGL_FALSE) {
			// Error!
			PL_LOG(Error, "Failed to destroy the used EGL dummy surface!")
		}
		m_hDummySurface = EGL_NO_SURFACE;

		// Destroy the EGL context
		if (m_hContext != EGL_NO_CONTEXT) {
			// Release all resources allocated by the shader compiler
			glReleaseShaderCompiler();

			// Destroy the EGL context
			if (eglDestroyContext(m_hDisplay, m_hContext) == EGL_FALSE) {
				// Error!
				PL_LOG(Error, "Failed to destroy the used EGL context!")
			}
			m_hContext = EGL_NO_CONTEXT;
		}

		// Return EGL to it's state at thread initialization
		if (eglReleaseThread() == EGL_FALSE) {
			// Error!
			PL_LOG(Error, "Failed to release the EGL thread!")
		}

		// Terminate the EGL display
		if (eglTerminate(m_hDisplay) == EGL_FALSE) {
			// Error!
			PL_LOG(Error, "Failed to terminate the used EGL display!")
		}
		m_hDisplay = EGL_NO_DISPLAY;
		m_hConfig  = nullptr;

		// Destroy the dummy native window, if required
		#ifdef WIN32
			if (!m_nNativeWindowHandle && m_nDummyNativeWindow) {
				DestroyWindow(m_nDummyNativeWindow);
				UnregisterClass(TEXT("PLOpenGLESDummyNativeWindow"), GetModuleHandle(nullptr));
			}
		#endif
		#if (defined(LINUX) && !defined(ANDROID))
			// Destroy the dummy native window
			if (!m_nNativeWindowHandle && m_nDummyNativeWindow)
				XDestroyWindow(m_pX11Display, m_nDummyNativeWindow);

			// Close the X server display connection
			if (m_pX11Display) {
				XCloseDisplay(m_pX11Display);
				m_pX11Display = nullptr;
			}
		#endif
		m_nDummyNativeWindow = NULL_HANDLE;
	}
}


//[-------------------------------------------------------]
//[ Protected virtual Context functions                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Chooses a EGL config
*/
EGLConfig Context::ChooseConfig(uint32 nMultisampleAntialiasingSamples) const
{
	// Try to find a working EGL configuration
	EGLConfig hConfig = nullptr;
	EGLint nConfigs = 0;
	bool bChooseConfigCapitulated = false;
	bool bMultisampleAntialiasing = false;
	EGLint nMultisampleAntialiasingSampleBuffers = 0;
	EGLint nMultisampleAntialiasingSamplesCurrent = static_cast<EGLint>(nMultisampleAntialiasingSamples);
	do {
		// Get the current multisample antialiasing settings
		bMultisampleAntialiasing = (nMultisampleAntialiasingSamplesCurrent > 1);	// Multisample antialiasing with just one sample per per pixel isn't real multisample, is it? :D
		nMultisampleAntialiasingSampleBuffers = bMultisampleAntialiasing ? 1 : 0;

		// Set desired configuration
		const EGLint pConfigAttribs[] =
		{
			EGL_LEVEL,				0,										// Frame buffer level
			EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,							// Which types of EGL surfaces are supported
			EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,						// Which client APIs are supported
			EGL_DEPTH_SIZE,			EGL_DONT_CARE,							// Bits of Z in the depth buffer
			EGL_SAMPLE_BUFFERS,		nMultisampleAntialiasingSampleBuffers,	// Number of multisample buffers (enable/disable multisample antialiasing)
			EGL_SAMPLES,			nMultisampleAntialiasingSamplesCurrent,	// Number of samples per pixel (multisample antialiasing samples)
			EGL_BUFFER_SIZE,		16,
			EGL_NONE
		};

		// Choose exactly one matching configuration
		if (eglChooseConfig(m_hDisplay, pConfigAttribs, &hConfig, 1, &nConfigs) == EGL_FALSE || nConfigs < 1) {
			// Can we change something on the multisample antialiasing? (may be the cause that no configuration was found!)
			if (bMultisampleAntialiasing) {
				if (nMultisampleAntialiasingSamplesCurrent > 8)
					nMultisampleAntialiasingSamplesCurrent = 8;
				else if (nMultisampleAntialiasingSamplesCurrent > 4)
					nMultisampleAntialiasingSamplesCurrent = 4;
				else if (nMultisampleAntialiasingSamplesCurrent > 2)
					nMultisampleAntialiasingSamplesCurrent = 2;
				else if (nMultisampleAntialiasingSamplesCurrent == 2)
					nMultisampleAntialiasingSamplesCurrent = 0;
			} else {
				// Don't mind, forget it...
				bChooseConfigCapitulated = true;
			}
		}
	} while (nConfigs < 1 && !bChooseConfigCapitulated);

	// Done
	return hConfig;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Context::Context(const Context &cSource) :
	m_pRenderer(nullptr),
	m_nNativeWindowHandle(NULL_HANDLE),
	#if (defined(LINUX) && !defined(ANDROID))
		m_pX11Display(nullptr),
	#endif
	m_hDisplay(EGL_NO_DISPLAY),
	m_hConfig(nullptr),
	m_hContext(EGL_NO_CONTEXT),
	m_nDummyNativeWindow(NULL_HANDLE),
	m_hDummySurface(EGL_NO_SURFACE)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Context &Context::operator =(const Context &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Shows some OpenGL ES information
*/
void Context::ShowOpenGLESInformation()
{
	GLint nValue = 0;

	// Print a list of all available extensions into the log
	PL_LOG(Info, "Extensions info:")
	WriteExtensionStringIntoLog(reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS)));

	// Show some OpenGL ES information
	PL_LOG(Info, String::Format("OpenGL ES 2.0 version: %s",		glGetString(GL_VERSION)	 ? reinterpret_cast<const char*>(glGetString(GL_VERSION))  : "-"))
	PL_LOG(Info, String::Format("OpenGL ES 2.0 vendor info: %s",	glGetString(GL_VENDOR)	 ? reinterpret_cast<const char*>(glGetString(GL_VENDOR))   : "-"))
	PL_LOG(Info, String::Format("OpenGL ES 2.0 renderer info: %s",	glGetString(GL_RENDERER) ? reinterpret_cast<const char*>(glGetString(GL_RENDERER)) : "-"))

	{ // Show some OpenGL ES shader information
		PL_LOG(Info, String::Format("OpenGL ES 2.0 shading language version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION) ? reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)) : "-"))

		// GL_MAX_VERTEX_ATTRIBS
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nValue);
		PL_LOG(Info, String::Format("OpenGL ES 2.0 maximum number of vertex attributes: %d", nValue))

		// GL_MAX_VERTEX_UNIFORM_VECTORS
		glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &nValue);
		PL_LOG(Info, String::Format("OpenGL ES 2.0 maximum number of uniform vertex vectors: %d", nValue))

		// GL_MAX_FRAGMENT_UNIFORM_VECTORS
		glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &nValue);
		PL_LOG(Info, String::Format("OpenGL ES 2.0 maximum number of uniform fragment vectors: %d", nValue))

		// GL_MAX_VARYING_VECTORS
		glGetIntegerv(GL_MAX_VARYING_VECTORS, &nValue);
		PL_LOG(Info, String::Format("OpenGL ES 2.0 maximum number of varying vectors: %d", nValue))

		// GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &nValue);
		PL_LOG(Info, String::Format("OpenGL ES 2.0 maximum number of combined texture image units: %d", nValue))

		// GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS
		glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &nValue);
		PL_LOG(Info, String::Format("OpenGL ES 2.0 maximum number of vertex texture image units: %d", nValue))

		// GL_MAX_TEXTURE_IMAGE_UNITS
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &nValue);
		PL_LOG(Info, String::Format("OpenGL ES 2.0 maximum number of texture image units: %d", nValue))
	}

	// GL_MAX_TEXTURE_SIZE
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &nValue);
	PL_LOG(Info, String::Format("OpenGL ES 2.0 maximum texture size: %d", nValue))

	// GL_MAX_CUBE_MAP_TEXTURE_SIZE
	glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &nValue);
	PL_LOG(Info, String::Format("OpenGL ES 2.0 maximum cube map texture size: %d", nValue))

	// GL_MAX_RENDERBUFFER_SIZE
	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &nValue);
	PL_LOG(Info, String::Format("OpenGL ES 2.0 maximum renderbuffer size: %d", nValue))

	{ // GL_MAX_VIEWPORT_DIMS
		GLint nDimension[2] = {0, 0};
		glGetIntegerv(GL_MAX_VIEWPORT_DIMS, nDimension);
		PL_LOG(Info, String::Format("OpenGL ES 2.0 maximum viewport dimension: %dx%d", nDimension[0], nDimension[1]))
	}
}

/**
*  @brief
*    Writes the extensions within a given extension string into the log
*/
void Context::WriteExtensionStringIntoLog(const char *pszExtensions) const
{
	// Check whether or not the given extensions string pointer is valid
	if (pszExtensions) {
		// Write the extensions into the log
		const char *pszSpace = pszExtensions;
		while (*pszSpace != '\0') {
			while (*pszSpace != ' ' && *pszSpace != '\0')
				pszSpace++;
			if (pszSpace-pszExtensions) {
				String sExtension;
				sExtension.Copy(pszExtensions, static_cast<uint32>(pszSpace-pszExtensions));
				PL_LOG(Info, sExtension)
			}
			if (*pszSpace != '\0') {
				pszSpace++; // Skip the space
				pszExtensions = pszSpace;
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
