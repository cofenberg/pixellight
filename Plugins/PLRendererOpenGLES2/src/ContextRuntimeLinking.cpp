/*********************************************************\
 *  File: ContextRuntimeLinking.h                        *
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
#include <PLCore/Runtime.h>
#include <PLCore/Log/Log.h>
#include <PLCore/System/DynLib.h>
#define DEFINERUNTIMELINKING
#include "PLRendererOpenGLES2/ExtensionsRuntimeLinking.h"
#include "PLRendererOpenGLES2/ContextRuntimeLinking.h"


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
*    Constructor
*/
ContextRuntimeLinking::ContextRuntimeLinking(Renderer &cRenderer, handle nNativeWindowHandle) : Context(cRenderer, nNativeWindowHandle),
	m_pEGLDynLib(new DynLib()),
	m_pGLESDynLib(new DynLib()),
	m_bEntryPointsRegistered(false),
	m_pExtensions(new ExtensionsRuntimeLinking())
{
	// Output log information
	PL_LOG(Info, "Performing OpenGL ES 2.0 dynamic runtime linking")

	// Load the dynamic libraries
	if (LoadLibraries()) {
		// Load the EGL entry points
		if (LoadEGLEntryPoints()) {
			// Load the OpenGL ES 2.0 entry points
			if (LoadGLESEntryPoints()) {
				// Entry points successfully registered
				m_bEntryPointsRegistered = true;
			}
		}
	}
}

/**
*  @brief
*    Destructor
*/
ContextRuntimeLinking::~ContextRuntimeLinking()
{
	// De-initialize the context while we still can
	DeInit();

	// Destroy the extensions instance
	delete m_pExtensions;

	// Destroy the dynamic library instances
	delete m_pEGLDynLib;
	delete m_pGLESDynLib;
}


//[-------------------------------------------------------]
//[ Public virtual Context functions                      ]
//[-------------------------------------------------------]
bool ContextRuntimeLinking::Init(uint32 nMultisampleAntialiasingSamples)
{
	// Entry points successfully registered?
	if (m_bEntryPointsRegistered) {
		// Call base implementation
		if (Context::Init(nMultisampleAntialiasingSamples)) {
			// Initialize the supported extensions
			m_pExtensions->Init();

			// Done
			return true;
		}
	}

	// Error!;
	return false;
}

const Extensions &ContextRuntimeLinking::GetExtensions() const
{
	return *m_pExtensions;
}


//[-------------------------------------------------------]
//[ Protected virtual Context functions                   ]
//[-------------------------------------------------------]
EGLConfig ContextRuntimeLinking::ChooseConfig(uint32 nMultisampleAntialiasingSamples) const
{
	// Try to find a working EGL configuration
	EGLConfig hConfig = nullptr;
	EGLint nConfigs = 0;
	bool bChooseConfigCapitulated = false;
	bool bMultisampleAntialiasing = false;
	uint32 nMultisampleAntialiasingSampleBuffers = 0;
	uint32 nMultisampleAntialiasingSamplesCurrent = nMultisampleAntialiasingSamples;
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
			EGL_RED_SIZE,			8,										// Bits of red color component
			EGL_GREEN_SIZE,			8,										// Bits of red color component
			EGL_BLUE_SIZE,			8,										// Bits of red color component
			EGL_DEPTH_SIZE,			16,										// Bits of Z in the depth buffer [TODO] Make it possible to set this from the outside, but do also automatically go down if it fails, e.g. 24 doesn't work for me
			// [TODO] Currently something looks wrong when using the desktop drivers - just black screen when using multisample ("AMD Catalyst 11.8" on a "ATI Mobility Radeon HD 4850")
			//       -> No issues with Android on the device (but it looks like there's no antialiasing, check it later in detail)
		//	EGL_SAMPLE_BUFFERS,		nMultisampleAntialiasingSampleBuffers,	// Number of multisample buffers (enable/disable multisample antialiasing)
		//	EGL_SAMPLES,			nMultisampleAntialiasingSamplesCurrent,	// Number of samples per pixel (multisample antialiasing samples)
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
//[ Private methods                                       ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loads the EGL dynamic library
*/
bool ContextRuntimeLinking::LoadLibraries()
{
	bool bResult = false;	// Error by default

	// EGL and OpenGL ES 2.0 may be within a single dynamic library, or within two separate dynamic libraries

	// Load in the dynamic library
	#ifdef WIN32
		// First, try the OpenGL ES 2.0 emulator from ARM (it's possible to move around this dll without issues, so, this one first)
		bResult = m_pEGLDynLib->Load("libEGL.dll");
		if (bResult) {
			bResult = m_pGLESDynLib->Load("libGLESv2.dll");
		} else {
			// Second, try the AMD/ATI driver
			bResult = m_pEGLDynLib->Load("atioglxx.dll");
			if (bResult) {
				bResult = m_pGLESDynLib->Load("atioglxx.dll");
			} else {
				// Third, try the NVIDIA driver
				bResult = m_pEGLDynLib->Load("nvoglv32.dll");
				if (bResult)
					bResult = m_pGLESDynLib->Load("nvoglv32.dll");
			}
		}
	#elif ANDROID
		bResult = m_pEGLDynLib->Load("libEGL.so");
		if (bResult)
			bResult = m_pGLESDynLib->Load("libGLESv2.so");
	#elif LINUX
		// First, try the OpenGL ES 2.0 emulator from ARM (it's possible to move around this dll without issues, so, this one first)
		// Give Linux an absolute path, if this is not done, I just rececive a polite "[PLCore] error while loading libEGL.so " -> "libEGL.so: cannot open shared object file: No such file or directory"
		const String sRuntimeDirectory = Runtime::GetDirectory();
		bResult = m_pEGLDynLib->Load(sRuntimeDirectory.GetLength() ? (sRuntimeDirectory + "/libEGL.so") : "libEGL.so");
		if (bResult) {
			bResult = m_pGLESDynLib->Load(sRuntimeDirectory.GetLength() ? (sRuntimeDirectory + "/libGLESv2.so") : "libGLESv2.so");
		} else {
			// Second, try the system driver
			bResult = m_pEGLDynLib->Load("libGL.so");
			if (bResult)
				bResult = m_pGLESDynLib->Load("libGL.so");
		}
	#endif

	// Success?
	if (bResult) {
		PL_LOG(Info, "Using EGL dynamic library \"" + m_pEGLDynLib->GetAbsPath() + '\"')
		PL_LOG(Info, "Using OpenGL ES 2.0 dynamic library \"" + m_pGLESDynLib->GetAbsPath() + '\"')
	} else {
		PL_LOG(Error, "Failed to load OpenGL ES 2.0 dynamic library")
	}

	// Done
	return bResult;
}

/**
*  @brief
*    Loads the EGL entry points
*/
bool ContextRuntimeLinking::LoadEGLEntryPoints()
{
	bool bResult = true;	// Success by default

	// Define a helper macro
	#define IMPORT_FUNC(funcName)																																	\
		if (bResult) {																																				\
			void *pSymbol = m_pEGLDynLib->GetSymbol(#funcName);																										\
			if (!pSymbol) {																																			\
				/* The specification states that "eglGetProcAddress" is only for extension functions, but when using OpenGL ES 2.0 on desktop PC by using a			\
				   native OpenGL ES 2.0 capable graphics driver under Linux (tested with "AMD Catalyst 11.8"), only this way will work */							\
				pSymbol = eglGetProcAddress(#funcName);																												\
			}																																						\
			if (pSymbol) {																																			\
				*(reinterpret_cast<void**>(&(funcName))) = pSymbol;																									\
			} else {																																				\
				PL_LOG(Error, String("Failed to find the entry point \"") + #funcName + "\" within the EGL dynamic library \"" + m_pEGLDynLib->GetAbsPath() + '\"')	\
				bResult = false;																																	\
			}																																						\
		}																																							\

	// Load the entry points
	IMPORT_FUNC(eglGetProcAddress);
	IMPORT_FUNC(eglGetError);
	IMPORT_FUNC(eglGetDisplay);
	IMPORT_FUNC(eglInitialize);
	IMPORT_FUNC(eglTerminate);
	IMPORT_FUNC(eglQueryString);
	IMPORT_FUNC(eglGetConfigs);
	IMPORT_FUNC(eglChooseConfig);
	IMPORT_FUNC(eglGetConfigAttrib);
	IMPORT_FUNC(eglCreateWindowSurface);
	IMPORT_FUNC(eglDestroySurface);
	IMPORT_FUNC(eglQuerySurface);
	IMPORT_FUNC(eglBindAPI);
	IMPORT_FUNC(eglQueryAPI);
	IMPORT_FUNC(eglWaitClient);
	IMPORT_FUNC(eglReleaseThread);
	IMPORT_FUNC(eglSurfaceAttrib);
	IMPORT_FUNC(eglBindTexImage);
	IMPORT_FUNC(eglReleaseTexImage);
	IMPORT_FUNC(eglSwapInterval);
	IMPORT_FUNC(eglCreateContext);
	IMPORT_FUNC(eglDestroyContext);
	IMPORT_FUNC(eglMakeCurrent);
	IMPORT_FUNC(eglGetCurrentContext);
	IMPORT_FUNC(eglGetCurrentSurface);
	IMPORT_FUNC(eglGetCurrentDisplay);
	IMPORT_FUNC(eglQueryContext);
	IMPORT_FUNC(eglWaitGL);
	IMPORT_FUNC(eglWaitNative);
	IMPORT_FUNC(eglSwapBuffers);
	IMPORT_FUNC(eglCopyBuffers);

	// Undefine the helper macro
	#undef IMPORT_FUNC

	// Done
	return bResult;
}

/**
*  @brief
*    Loads the OpenGL ES 2.0 entry points
*/
bool ContextRuntimeLinking::LoadGLESEntryPoints()
{
	bool bResult = true;	// Success by default

	// Define a helper macro
	#define IMPORT_FUNC(funcName)																																				\
		if (bResult) {																																							\
			void *pSymbol = m_pGLESDynLib->GetSymbol(#funcName);																												\
			if (!pSymbol) {																																						\
				/* The specification states that "eglGetProcAddress" is only for extension functions, but when using OpenGL ES 2.0 on desktop PC by using a						\
				   native OpenGL ES 2.0 capable graphics driver (tested with "AMD Catalyst 11.8"), only this way will work */													\
				pSymbol = eglGetProcAddress(#funcName);																															\
			}																																									\
			if (pSymbol) {																																						\
				*(reinterpret_cast<void**>(&(funcName))) = pSymbol;																												\
			} else {																																							\
				PL_LOG(Error, String("Failed to find the entry point \"") + #funcName + "\" within the OpenGL ES 2.0 dynamic library \"" + m_pGLESDynLib->GetAbsPath() + '\"')	\
				bResult = false;																																				\
			}																																									\
		}																																										\

	// Load the entry points
	IMPORT_FUNC(glActiveTexture);
	IMPORT_FUNC(glAttachShader);
	IMPORT_FUNC(glBindAttribLocation);
	IMPORT_FUNC(glBindBuffer);
	IMPORT_FUNC(glBindFramebuffer);
	IMPORT_FUNC(glBindRenderbuffer);
	IMPORT_FUNC(glBindTexture);
	IMPORT_FUNC(glBlendColor);
	IMPORT_FUNC(glBlendEquation);
	IMPORT_FUNC(glBlendEquationSeparate);
	IMPORT_FUNC(glBlendFunc);
	IMPORT_FUNC(glBlendFuncSeparate);
	IMPORT_FUNC(glBufferData);
	IMPORT_FUNC(glBufferSubData);
	IMPORT_FUNC(glCheckFramebufferStatus);
	IMPORT_FUNC(glClear);
	IMPORT_FUNC(glClearColor);
	IMPORT_FUNC(glClearDepthf);
	IMPORT_FUNC(glClearStencil);
	IMPORT_FUNC(glColorMask);
	IMPORT_FUNC(glCompileShader);
	IMPORT_FUNC(glCompressedTexImage2D);
	IMPORT_FUNC(glCompressedTexSubImage2D);
	IMPORT_FUNC(glCopyTexImage2D);
	IMPORT_FUNC(glCopyTexSubImage2D);
	IMPORT_FUNC(glCreateProgram);
	IMPORT_FUNC(glCreateShader);
	IMPORT_FUNC(glCullFace);
	IMPORT_FUNC(glDeleteBuffers);
	IMPORT_FUNC(glDeleteFramebuffers);
	IMPORT_FUNC(glDeleteProgram);
	IMPORT_FUNC(glDeleteRenderbuffers);
	IMPORT_FUNC(glDeleteShader);
	IMPORT_FUNC(glDeleteTextures);
	IMPORT_FUNC(glDepthFunc);
	IMPORT_FUNC(glDepthMask);
	IMPORT_FUNC(glDepthRangef);
	IMPORT_FUNC(glDetachShader);
	IMPORT_FUNC(glDisable);
	IMPORT_FUNC(glDisableVertexAttribArray);
	IMPORT_FUNC(glDrawArrays);
	IMPORT_FUNC(glDrawElements);
	IMPORT_FUNC(glEnable);
	IMPORT_FUNC(glEnableVertexAttribArray);
	IMPORT_FUNC(glFinish);
	IMPORT_FUNC(glFlush);
	IMPORT_FUNC(glFramebufferRenderbuffer);
	IMPORT_FUNC(glFramebufferTexture2D);
	IMPORT_FUNC(glFrontFace);
	IMPORT_FUNC(glGenBuffers);
	IMPORT_FUNC(glGenerateMipmap);
	IMPORT_FUNC(glGenFramebuffers);
	IMPORT_FUNC(glGenRenderbuffers);
	IMPORT_FUNC(glGenTextures);
	IMPORT_FUNC(glGetActiveAttrib);
	IMPORT_FUNC(glGetActiveUniform);
	IMPORT_FUNC(glGetAttachedShaders);
	IMPORT_FUNC(glGetAttribLocation);
	IMPORT_FUNC(glGetBooleanv);
	IMPORT_FUNC(glGetBufferParameteriv);
	IMPORT_FUNC(glGetError);
	IMPORT_FUNC(glGetFloatv);
	IMPORT_FUNC(glGetFramebufferAttachmentParameteriv);
	IMPORT_FUNC(glGetIntegerv);
	IMPORT_FUNC(glGetProgramiv);
	IMPORT_FUNC(glGetProgramInfoLog);
	IMPORT_FUNC(glGetRenderbufferParameteriv);
	IMPORT_FUNC(glGetShaderiv);
	IMPORT_FUNC(glGetShaderInfoLog);
	IMPORT_FUNC(glGetShaderPrecisionFormat);
	IMPORT_FUNC(glGetShaderSource);
	IMPORT_FUNC(glGetString);
	IMPORT_FUNC(glGetTexParameterfv);
	IMPORT_FUNC(glGetTexParameteriv);
	IMPORT_FUNC(glGetUniformfv);
	IMPORT_FUNC(glGetUniformiv);
	IMPORT_FUNC(glGetUniformLocation);
	IMPORT_FUNC(glGetVertexAttribfv);
	IMPORT_FUNC(glGetVertexAttribiv);
	IMPORT_FUNC(glGetVertexAttribPointerv);
	IMPORT_FUNC(glHint);
	IMPORT_FUNC(glIsBuffer);
	IMPORT_FUNC(glIsEnabled);
	IMPORT_FUNC(glIsFramebuffer);
	IMPORT_FUNC(glIsProgram);
	IMPORT_FUNC(glIsRenderbuffer);
	IMPORT_FUNC(glIsShader);
	IMPORT_FUNC(glIsTexture);
	IMPORT_FUNC(glLineWidth);
	IMPORT_FUNC(glLinkProgram);
	IMPORT_FUNC(glPixelStorei);
	IMPORT_FUNC(glPolygonOffset);
	IMPORT_FUNC(glReadPixels);
	IMPORT_FUNC(glReleaseShaderCompiler);
	IMPORT_FUNC(glRenderbufferStorage);
	IMPORT_FUNC(glSampleCoverage);
	IMPORT_FUNC(glScissor);
	IMPORT_FUNC(glShaderBinary);
	IMPORT_FUNC(glShaderSource);
	IMPORT_FUNC(glStencilFunc);
	IMPORT_FUNC(glStencilFuncSeparate);
	IMPORT_FUNC(glStencilMask);
	IMPORT_FUNC(glStencilMaskSeparate);
	IMPORT_FUNC(glStencilOp);
	IMPORT_FUNC(glStencilOpSeparate);
	IMPORT_FUNC(glTexImage2D);
	IMPORT_FUNC(glTexParameterf);
	IMPORT_FUNC(glTexParameterfv);
	IMPORT_FUNC(glTexParameteri);
	IMPORT_FUNC(glTexParameteriv);
	IMPORT_FUNC(glTexSubImage2D);
	IMPORT_FUNC(glUniform1f);
	IMPORT_FUNC(glUniform1fv);
	IMPORT_FUNC(glUniform1i);
	IMPORT_FUNC(glUniform1iv);
	IMPORT_FUNC(glUniform2f);
	IMPORT_FUNC(glUniform2fv);
	IMPORT_FUNC(glUniform2i);
	IMPORT_FUNC(glUniform2iv);
	IMPORT_FUNC(glUniform3f);
	IMPORT_FUNC(glUniform3fv);
	IMPORT_FUNC(glUniform3i);
	IMPORT_FUNC(glUniform3iv);
	IMPORT_FUNC(glUniform4f);
	IMPORT_FUNC(glUniform4fv);
	IMPORT_FUNC(glUniform4i);
	IMPORT_FUNC(glUniform4iv);
	IMPORT_FUNC(glUniformMatrix2fv);
	IMPORT_FUNC(glUniformMatrix3fv);
	IMPORT_FUNC(glUniformMatrix4fv);
	IMPORT_FUNC(glUseProgram);
	IMPORT_FUNC(glValidateProgram);
	IMPORT_FUNC(glVertexAttrib1f);
	IMPORT_FUNC(glVertexAttrib1fv);
	IMPORT_FUNC(glVertexAttrib2f);
	IMPORT_FUNC(glVertexAttrib2fv);
	IMPORT_FUNC(glVertexAttrib3f);
	IMPORT_FUNC(glVertexAttrib3fv);
	IMPORT_FUNC(glVertexAttrib4f);
	IMPORT_FUNC(glVertexAttrib4fv);
	IMPORT_FUNC(glVertexAttribPointer);
	IMPORT_FUNC(glViewport);

	// Undefine the helper macro
	#undef IMPORT_FUNC

	// Done
	return bResult;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
