/*********************************************************\
 *  File: ContextDesktop.h                               *
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
#include <PLCore/System/DynLib.h>
#define DEFINEDESKTOP
#include "PLRendererOpenGLES2/ContextDesktop.h"


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
ContextDesktop::ContextDesktop(Renderer &cRenderer, handle nNativeWindowHandle) : Context(cRenderer, nNativeWindowHandle),
	m_pDynLib(new DynLib())
{
	// Load the OpenGL ES 2.0 dynamic library
	if (LoadLibrary()) {
		// Load the EGL entry points
		if (LoadEGLEntryPoints()) {
			// Load the OpenGL ES 2.0 entry points
			LoadGLESEntryPoints();
		}
	}
}

/**
*  @brief
*    Destructor
*/
ContextDesktop::~ContextDesktop()
{
	// Destroy the dynamic library instance
	delete m_pDynLib;
}


//[-------------------------------------------------------]
//[ Protected virtual Context functions                   ]
//[-------------------------------------------------------]
EGLConfig ContextDesktop::ChooseConfig(uint32 nMultisampleAntialiasingSamples) const
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
			EGL_DEPTH_SIZE,			EGL_DONT_CARE,							// Bits of Z in the depth buffer
			// [TODO] Currently something looks wrong - just black screen when using multisample ("AMD Catalyst 11.8" on a "ATI Mobility Radeon HD 4850")
//			EGL_SAMPLE_BUFFERS,		nMultisampleAntialiasingSampleBuffers,	// Number of multisample buffers (enable/disable multisample antialiasing)
//			EGL_SAMPLES,			nMultisampleAntialiasingSamplesCurrent,	// Number of samples per pixel (multisample antialiasing samples)
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
//[ Private methods                                       ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loads the OpenGL ES 2.0 dynamic library
*/
bool ContextDesktop::LoadLibrary()
{
	bool bResult = false;	// Error by default

	// Load in the dynamic library
	#ifdef WIN32
		// First, try the AMD/ATI driver
		bResult = m_pDynLib->Load("atioglxx.dll");
		if (!bResult) {
			// Second, try the NVIDIA driver
			bResult = m_pDynLib->Load("nvoglv32.dll");
		}
	#elif LINUX
		bResult = m_pDynLib->Load("libGL.so");
	#endif

	// Success?
	if (bResult)
		PL_LOG(Info, "Using OpenGL ES 2.0 dynamic library \"" + m_pDynLib->GetAbsPath() + '\"')
	else
		PL_LOG(Error, "Failed to load OpenGL ES 2.0 dynamic library")

	// Done
	return bResult;
}

/**
*  @brief
*    Loads the EGL entry points
*/
bool ContextDesktop::LoadEGLEntryPoints()
{
	bool bResult = true;	// Success by default

	// Define a helper macro
	#define IMPORT_FUNC_DLL(funcName) {						\
		void *pSymbol = m_pDynLib->GetSymbol(#funcName);	\
		if (!pSymbol) bResult = false;						\
		*(reinterpret_cast<void**>(&(funcName))) = pSymbol; }

	// Load the entry points
	IMPORT_FUNC_DLL(eglGetError);
	IMPORT_FUNC_DLL(eglGetDisplay);
	IMPORT_FUNC_DLL(eglInitialize);
	IMPORT_FUNC_DLL(eglTerminate);
	IMPORT_FUNC_DLL(eglQueryString);
	IMPORT_FUNC_DLL(eglGetConfigs);
	IMPORT_FUNC_DLL(eglChooseConfig);
	IMPORT_FUNC_DLL(eglGetConfigAttrib);
	IMPORT_FUNC_DLL(eglCreateWindowSurface);
	IMPORT_FUNC_DLL(eglDestroySurface);
	IMPORT_FUNC_DLL(eglQuerySurface);
	IMPORT_FUNC_DLL(eglBindAPI);
	IMPORT_FUNC_DLL(eglQueryAPI);
	IMPORT_FUNC_DLL(eglWaitClient);
	IMPORT_FUNC_DLL(eglReleaseThread);
	IMPORT_FUNC_DLL(eglSurfaceAttrib);
	IMPORT_FUNC_DLL(eglBindTexImage);
	IMPORT_FUNC_DLL(eglReleaseTexImage);
	IMPORT_FUNC_DLL(eglSwapInterval);
	IMPORT_FUNC_DLL(eglCreateContext);
	IMPORT_FUNC_DLL(eglDestroyContext);
	IMPORT_FUNC_DLL(eglMakeCurrent);
	IMPORT_FUNC_DLL(eglGetCurrentContext);
	IMPORT_FUNC_DLL(eglGetCurrentSurface);
	IMPORT_FUNC_DLL(eglGetCurrentDisplay);
	IMPORT_FUNC_DLL(eglQueryContext);
	IMPORT_FUNC_DLL(eglWaitGL);
	IMPORT_FUNC_DLL(eglWaitNative);
	IMPORT_FUNC_DLL(eglSwapBuffers);
	IMPORT_FUNC_DLL(eglCopyBuffers);
	IMPORT_FUNC_DLL(eglGetProcAddress);

	// Undefine the helper macro
	#undef IMPORT_FUNC

	// Done
	return bResult;
}

/**
*  @brief
*    Loads the OpenGL ES 2.0 entry points
*/
bool ContextDesktop::LoadGLESEntryPoints()
{
	bool bResult = true;	// Success by default

	// Define a helper macro (The specification states "eglGetProcAddress" is only for extension functions, but in here we have no other choice, do we?)
	#define IMPORT_FUNC(funcName) {						\
		void *pSymbol = eglGetProcAddress((#funcName));	\
		if (!pSymbol) bResult = false;					\
		*(reinterpret_cast<void**>(&(funcName))) = pSymbol; }

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
