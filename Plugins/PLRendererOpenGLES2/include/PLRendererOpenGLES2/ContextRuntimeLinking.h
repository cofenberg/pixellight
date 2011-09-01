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


#ifndef __PLRENDEREROPENGLES2_RUNTIMELINKING_H__
#define __PLRENDEREROPENGLES2_RUNTIMELINKING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRendererOpenGLES2/Context.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class DynLib;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL ES 2.0 desktop context
*
*  @remarks
*    This context implementation links against the OpenGL ES 2.0 dynamic libraries at runtime. There are
*    three typical variations of this OpenGL ES 2.0 dynamic libraries:
*
*    - Implementation for OpenGL ES 2.0 on mobile devices.
*
*    - Implementation for OpenGL ES 2.0 on desktop PC by using a OpenGL ES 2.0 capable graphics driver.
*      Basing on the example http://developer.amd.com/samples/assets/egl_sample.zip from
*      http://blogs.amd.com/developer/2010/07/26/opengl-es-2-0-coming-to-a-desktop-near-you/
*      Tested with "AMD Catalyst 11.8" on a "ATI Mobility Radeon HD 4850", no errors, but just got
*      a white screen when Windows Aero is active. As soon as I disabled Windows Aero all went fine.
*
*    - Implementation for testing OpenGL ES 2.0 on a desktop PC using OpenGL ES 2.0 Emulator from ARM
*      (http://www.malideveloper.com/tools/software-development/opengl-es-20-emulator.php). If you have
*      a OpenGL ES 2.0 capable graphics driver, you may want to use the "ContextNative"-implementation
*      instead.
*/
class ContextRuntimeLinking : public Context {


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
		*  @param[in] nNativeWindowHandle
		*    Handle of a native OS window which is valid as long as the renderer instance exists, "NULL_HANDLE" if there's no such window
		*/
		ContextRuntimeLinking(Renderer &cRenderer, PLCore::handle nNativeWindowHandle);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ContextRuntimeLinking();


	//[-------------------------------------------------------]
	//[ Public virtual Context functions                      ]
	//[-------------------------------------------------------]
	public:
		virtual bool Init(PLCore::uint32 nMultisampleAntialiasingSamples) override;


	//[-------------------------------------------------------]
	//[ Protected virtual Context functions                   ]
	//[-------------------------------------------------------]
	protected:
		virtual EGLConfig ChooseConfig(PLCore::uint32 nMultisampleAntialiasingSamples) const override;


	//[-------------------------------------------------------]
	//[ Private methods                                       ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Loads the dynamic libraries
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadLibraries();

		/**
		*  @brief
		*    Loads the EGL entry points
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - Do only call this method if the OpenGL ES 2.0 dynamic library was loaded successfully
		*/
		bool LoadEGLEntryPoints();

		/**
		*  @brief
		*    Loads the OpenGL ES 2.0 entry points
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - Do only call this method if the OpenGL ES 2.0 dynamic library was loaded successfully
		*/
		bool LoadGLESEntryPoints();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::DynLib *m_pEGLDynLib;				/**< EGL dynamic library, always valid! (at least the class instance) */
		PLCore::DynLib *m_pGLESDynLib;				/**< OpenGL ES 2.0 dynamic library, always valid! (at least the class instance) */
		bool			m_bEntryPointsRegistered;	/**< Entry points successfully registered? */


};


//[-------------------------------------------------------]
//[ Macros & definitions                                  ]
//[-------------------------------------------------------]
#ifdef DEFINEDESKTOP
	#define FNDEF(retType, funcName, args) retType (APIENTRY *funcPtr_##funcName) args
#else
	#define FNDEF(retType, funcName, args) extern retType (APIENTRY *funcPtr_##funcName) args
#endif

#ifndef GLchar
	#define GLchar char
#endif
#ifndef GLenum
	#define GLenum GLint
#endif


//[-------------------------------------------------------]
//[ EGL functions                                         ]
//[-------------------------------------------------------]
FNDEF(EGLint,		eglGetError,			(void));
FNDEF(EGLDisplay,	eglGetDisplay,			(NativeDisplayType display));
FNDEF(EGLBoolean,	eglInitialize,			(EGLDisplay dpy, EGLint *major, EGLint *minor));
FNDEF(EGLBoolean,	eglTerminate,			(EGLDisplay dpy));
FNDEF(const char*,	eglQueryString,			(EGLDisplay dpy, EGLint name));
FNDEF(EGLBoolean,	eglGetConfigs,			(EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config));
FNDEF(EGLBoolean,	eglChooseConfig,		(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config));
FNDEF(EGLBoolean,	eglGetConfigAttrib,		(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value));
FNDEF(EGLSurface,	eglCreateWindowSurface,	(EGLDisplay dpy, EGLConfig config, NativeWindowType window, const EGLint *attrib_list));
FNDEF(EGLBoolean,	eglDestroySurface,		(EGLDisplay dpy, EGLSurface surface));
FNDEF(EGLBoolean,	eglQuerySurface,		(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value));
FNDEF(EGLBoolean,	eglBindAPI,				(EGLenum api));
FNDEF(EGLenum,		eglQueryAPI,			(void));
FNDEF(EGLBoolean,	eglWaitClient,			(void));
FNDEF(EGLBoolean,	eglReleaseThread,		(void));
FNDEF(EGLBoolean,	eglSurfaceAttrib,		(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value));
FNDEF(EGLBoolean,	eglBindTexImage,		(EGLDisplay dpy, EGLSurface surface, EGLint buffer));
FNDEF(EGLBoolean,	eglReleaseTexImage,		(EGLDisplay dpy, EGLSurface surface, EGLint buffer));
FNDEF(EGLBoolean,	eglSwapInterval,		(EGLDisplay dpy, EGLint interval));
FNDEF(EGLContext,	eglCreateContext,		(EGLDisplay dpy, EGLConfig config, EGLContext share_list, const EGLint *attrib_list));
FNDEF(EGLBoolean,	eglDestroyContext,		(EGLDisplay dpy, EGLContext ctx));
FNDEF(EGLBoolean,	eglMakeCurrent,			(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx));
FNDEF(EGLContext,	eglGetCurrentContext,	(void));
FNDEF(EGLSurface,	eglGetCurrentSurface,	(EGLint readdraw));
FNDEF(EGLDisplay,	eglGetCurrentDisplay,	(void));
FNDEF(EGLBoolean,	eglQueryContext,		(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value));
FNDEF(EGLBoolean,	eglWaitGL,				(void));
FNDEF(EGLBoolean,	eglWaitNative,			(EGLint engine));
FNDEF(EGLBoolean,	eglSwapBuffers,			(EGLDisplay dpy, EGLSurface draw));
FNDEF(EGLBoolean,	eglCopyBuffers,			(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target));
FNDEF(void*,		eglGetProcAddress,		(const char *procname));


//[-------------------------------------------------------]
//[ GL core functions                                     ]
//[-------------------------------------------------------]
FNDEF(void,				glActiveTexture,						(GLenum texture));
FNDEF(void,				glAttachShader,							(GLuint program, GLuint shader));
FNDEF(void,				glBindAttribLocation,					(GLuint program, GLuint index, const GLchar* name));
FNDEF(void,				glBindBuffer,							(GLenum target, GLuint buffer));
FNDEF(void,				glBindFramebuffer,						(GLenum target, GLuint framebuffer));
FNDEF(void,				glBindRenderbuffer,						(GLenum target, GLuint renderbuffer));
FNDEF(void,				glBindTexture,							(GLenum target, GLuint texture));
FNDEF(void,				glBlendColor,							(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha));
FNDEF(void,				glBlendEquation,						(GLenum mode));
FNDEF(void,				glBlendEquationSeparate,				(GLenum modeRGB, GLenum modeAlpha));
FNDEF(void,				glBlendFunc,							(GLenum sfactor, GLenum dfactor));
FNDEF(void,				glBlendFuncSeparate,					(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha));
FNDEF(void,				glBufferData,							(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage));
FNDEF(void,				glBufferSubData,						(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data));
FNDEF(GLenum,			glCheckFramebufferStatus,				(GLenum target));
FNDEF(void,				glClear,								(GLbitfield mask));
FNDEF(void,				glClearColor,							(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha));
FNDEF(void,				glClearDepthf,							(GLclampf depth));
FNDEF(void,				glClearStencil,							(GLint s));
FNDEF(void,				glColorMask,							(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha));
FNDEF(void,				glCompileShader,						(GLuint shader));
FNDEF(void,				glCompressedTexImage2D,					(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data));
FNDEF(void,				glCompressedTexSubImage2D,				(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data));
FNDEF(void,				glCopyTexImage2D,						(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border));
FNDEF(void,				glCopyTexSubImage2D,					(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height));
FNDEF(GLuint,			glCreateProgram,						(void));
FNDEF(GLuint,			glCreateShader,							(GLenum type));
FNDEF(void,				glCullFace,								(GLenum mode));
FNDEF(void,				glDeleteBuffers,						(GLsizei n, const GLuint* buffers));
FNDEF(void,				glDeleteFramebuffers,					(GLsizei n, const GLuint* framebuffers));
FNDEF(void,				glDeleteProgram,						(GLuint program));
FNDEF(void,				glDeleteRenderbuffers,					(GLsizei n, const GLuint* renderbuffers));
FNDEF(void,				glDeleteShader,							(GLuint shader));
FNDEF(void,				glDeleteTextures,						(GLsizei n, const GLuint* textures));
FNDEF(void,				glDepthFunc,							(GLenum func));
FNDEF(void,				glDepthMask,							(GLboolean flag));
FNDEF(void,				glDepthRangef,							(GLclampf zNear, GLclampf zFar));
FNDEF(void,				glDetachShader,							(GLuint program, GLuint shader));
FNDEF(void,				glDisable,								(GLenum cap));
FNDEF(void,				glDisableVertexAttribArray,				(GLuint index));
FNDEF(void,				glDrawArrays,							(GLenum mode, GLint first, GLsizei count));
FNDEF(void,				glDrawElements,							(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices));
FNDEF(void,				glEnable,								(GLenum cap));
FNDEF(void,				glEnableVertexAttribArray,				(GLuint index));
FNDEF(void,				glFinish,								(void));
FNDEF(void,				glFlush,								(void));
FNDEF(void,				glFramebufferRenderbuffer,				(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer));
FNDEF(void,				glFramebufferTexture2D,					(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level));
FNDEF(void,				glFrontFace,							(GLenum mode));
FNDEF(void,				glGenBuffers,							(GLsizei n, GLuint* buffers));
FNDEF(void,				glGenerateMipmap,						(GLenum target));
FNDEF(void,				glGenFramebuffers,						(GLsizei n, GLuint* framebuffers));
FNDEF(void,				glGenRenderbuffers,						(GLsizei n, GLuint* renderbuffers));
FNDEF(void,				glGenTextures,							(GLsizei n, GLuint* textures));
FNDEF(void,				glGetActiveAttrib,						(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name));
FNDEF(void,				glGetActiveUniform,						(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name));
FNDEF(void,				glGetAttachedShaders,					(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders));
FNDEF(int,				glGetAttribLocation,					(GLuint program, const GLchar* name));
FNDEF(void,				glGetBooleanv,							(GLenum pname, GLboolean* params));
FNDEF(void,				glGetBufferParameteriv,					(GLenum target, GLenum pname, GLint* params));
FNDEF(GLenum,			glGetError,								(void));
FNDEF(void,				glGetFloatv,							(GLenum pname, GLfloat* params));
FNDEF(void,				glGetFramebufferAttachmentParameteriv,	(GLenum target, GLenum attachment, GLenum pname, GLint* params));
FNDEF(void,				glGetIntegerv,							(GLenum pname, GLint* params));
FNDEF(void,				glGetProgramiv,							(GLuint program, GLenum pname, GLint* params));
FNDEF(void,				glGetProgramInfoLog,					(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog));
FNDEF(void,				glGetRenderbufferParameteriv,			(GLenum target, GLenum pname, GLint* params));
FNDEF(void,				glGetShaderiv,							(GLuint shader, GLenum pname, GLint* params));
FNDEF(void,				glGetShaderInfoLog,						(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog));
FNDEF(void,				glGetShaderPrecisionFormat,				(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision));
FNDEF(void,				glGetShaderSource,						(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source));
FNDEF(const GLubyte*,	glGetString,							(GLenum name));
FNDEF(void,				glGetTexParameterfv,					(GLenum target, GLenum pname, GLfloat* params));
FNDEF(void,				glGetTexParameteriv,					(GLenum target, GLenum pname, GLint* params));
FNDEF(void,				glGetUniformfv,							(GLuint program, GLint location, GLfloat* params));
FNDEF(void,				glGetUniformiv,							(GLuint program, GLint location, GLint* params));
FNDEF(int,				glGetUniformLocation,					(GLuint program, const GLchar* name));
FNDEF(void,				glGetVertexAttribfv,					(GLuint index, GLenum pname, GLfloat* params));
FNDEF(void,				glGetVertexAttribiv,					(GLuint index, GLenum pname, GLint* params));
FNDEF(void,				glGetVertexAttribPointerv,				(GLuint index, GLenum pname, GLvoid** pointer));
FNDEF(void,				glHint,									(GLenum target, GLenum mode));
FNDEF(GLboolean,		glIsBuffer,								(GLuint buffer));
FNDEF(GLboolean,		glIsEnabled,							(GLenum cap));
FNDEF(GLboolean,		glIsFramebuffer,						(GLuint framebuffer));
FNDEF(GLboolean,		glIsProgram,							(GLuint program));
FNDEF(GLboolean,		glIsRenderbuffer,						(GLuint renderbuffer));
FNDEF(GLboolean,		glIsShader,								(GLuint shader));
FNDEF(GLboolean,		glIsTexture,							(GLuint texture));
FNDEF(void,				glLineWidth,							(GLfloat width));
FNDEF(void,				glLinkProgram,							(GLuint program));
FNDEF(void,				glPixelStorei,							(GLenum pname, GLint param));
FNDEF(void,				glPolygonOffset,						(GLfloat factor, GLfloat units));
FNDEF(void,				glReadPixels,							(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels));
FNDEF(void,				glReleaseShaderCompiler,				(void));
FNDEF(void,				glRenderbufferStorage,					(GLenum target, GLenum internalformat, GLsizei width, GLsizei height));
FNDEF(void,				glSampleCoverage,						(GLclampf value, GLboolean invert));
FNDEF(void,				glScissor,								(GLint x, GLint y, GLsizei width, GLsizei height));
FNDEF(void,				glShaderBinary,							(GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length));
FNDEF(void,				glShaderSource,							(GLuint shader, GLsizei count, const GLchar** string, const GLint* length));
FNDEF(void,				glStencilFunc,							(GLenum func, GLint ref, GLuint mask));
FNDEF(void,				glStencilFuncSeparate,					(GLenum face, GLenum func, GLint ref, GLuint mask));
FNDEF(void,				glStencilMask,							(GLuint mask));
FNDEF(void,				glStencilMaskSeparate,					(GLenum face, GLuint mask));
FNDEF(void,				glStencilOp,							(GLenum fail, GLenum zfail, GLenum zpass));
FNDEF(void,				glStencilOpSeparate,					(GLenum face, GLenum fail, GLenum zfail, GLenum zpass));
FNDEF(void,				glTexImage2D,							(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels));
FNDEF(void,				glTexParameterf,						(GLenum target, GLenum pname, GLfloat param));
FNDEF(void,				glTexParameterfv,						(GLenum target, GLenum pname, const GLfloat* params));
FNDEF(void,				glTexParameteri,						(GLenum target, GLenum pname, GLint param));
FNDEF(void,				glTexParameteriv,						(GLenum target, GLenum pname, const GLint* params));
FNDEF(void,				glTexSubImage2D,						(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels));
FNDEF(void,				glUniform1f,							(GLint location, GLfloat x));
FNDEF(void,				glUniform1fv,							(GLint location, GLsizei count, const GLfloat* v));
FNDEF(void,				glUniform1i,							(GLint location, GLint x));
FNDEF(void,				glUniform1iv,							(GLint location, GLsizei count, const GLint* v));
FNDEF(void,				glUniform2f,							(GLint location, GLfloat x, GLfloat y));
FNDEF(void,				glUniform2fv,							(GLint location, GLsizei count, const GLfloat* v));
FNDEF(void,				glUniform2i,							(GLint location, GLint x, GLint y));
FNDEF(void,				glUniform2iv,							(GLint location, GLsizei count, const GLint* v));
FNDEF(void,				glUniform3f,							(GLint location, GLfloat x, GLfloat y, GLfloat z));
FNDEF(void,				glUniform3fv,							(GLint location, GLsizei count, const GLfloat* v));
FNDEF(void,				glUniform3i,							(GLint location, GLint x, GLint y, GLint z));
FNDEF(void,				glUniform3iv,							(GLint location, GLsizei count, const GLint* v));
FNDEF(void,				glUniform4f,							(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w));
FNDEF(void,				glUniform4fv,							(GLint location, GLsizei count, const GLfloat* v));
FNDEF(void,				glUniform4i,							(GLint location, GLint x, GLint y, GLint z, GLint w));
FNDEF(void,				glUniform4iv,							(GLint location, GLsizei count, const GLint* v));
FNDEF(void,				glUniformMatrix2fv,						(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value));
FNDEF(void,				glUniformMatrix3fv,						(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value));
FNDEF(void,				glUniformMatrix4fv,						(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value));
FNDEF(void,				glUseProgram,							(GLuint program));
FNDEF(void,				glValidateProgram,						(GLuint program));
FNDEF(void,				glVertexAttrib1f,						(GLuint indx, GLfloat x));
FNDEF(void,				glVertexAttrib1fv,						(GLuint indx, const GLfloat* values));
FNDEF(void,				glVertexAttrib2f,						(GLuint indx, GLfloat x, GLfloat y));
FNDEF(void,				glVertexAttrib2fv,						(GLuint indx, const GLfloat* values));
FNDEF(void,				glVertexAttrib3f,						(GLuint indx, GLfloat x, GLfloat y, GLfloat z));
FNDEF(void,				glVertexAttrib3fv,						(GLuint indx, const GLfloat* values));
FNDEF(void,				glVertexAttrib4f,						(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w));
FNDEF(void,				glVertexAttrib4fv,						(GLuint indx, const GLfloat* values));
FNDEF(void,				glVertexAttribPointer,					(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr));
FNDEF(void,				glViewport,								(GLint x, GLint y, GLsizei width, GLsizei height));


//[-------------------------------------------------------]
//[ Macros & definitions                                  ]
//[-------------------------------------------------------]
#define FNPTR(name) funcPtr_##name

// Redirect egl* and gl* function calls to funcPtr_egl* and funcPtr_gl*

// EGL 1.4
#define eglGetError				FNPTR(eglGetError)
#define eglGetDisplay			FNPTR(eglGetDisplay)
#define eglInitialize			FNPTR(eglInitialize)
#define eglTerminate			FNPTR(eglTerminate)
#define eglQueryString			FNPTR(eglQueryString)
#define eglGetConfigs			FNPTR(eglGetConfigs)
#define eglChooseConfig			FNPTR(eglChooseConfig)
#define eglGetConfigAttrib		FNPTR(eglGetConfigAttrib)
#define eglCreateWindowSurface	FNPTR(eglCreateWindowSurface)
#define eglDestroySurface		FNPTR(eglDestroySurface)
#define eglQuerySurface			FNPTR(eglQuerySurface)
#define eglBindAPI				FNPTR(eglBindAPI)
#define eglQueryAPI				FNPTR(eglQueryAPI)
#define eglWaitClient			FNPTR(eglWaitClient)
#define eglReleaseThread		FNPTR(eglReleaseThread)
#define eglSurfaceAttrib		FNPTR(eglSurfaceAttrib)
#define eglBindTexImage			FNPTR(eglBindTexImage)
#define eglReleaseTexImage		FNPTR(eglReleaseTexImage)
#define eglSwapInterval			FNPTR(eglSwapInterval)
#define eglCreateContext		FNPTR(eglCreateContext)
#define eglDestroyContext		FNPTR(eglDestroyContext)
#define eglMakeCurrent			FNPTR(eglMakeCurrent)
#define eglGetCurrentContext	FNPTR(eglGetCurrentContext)
#define eglGetCurrentSurface	FNPTR(eglGetCurrentSurface)
#define eglGetCurrentDisplay	FNPTR(eglGetCurrentDisplay)
#define eglQueryContext			FNPTR(eglQueryContext)
#define eglWaitGL				FNPTR(eglWaitGL)
#define eglWaitNative			FNPTR(eglWaitNative)
#define eglSwapBuffers			FNPTR(eglSwapBuffers)
#define eglCopyBuffers			FNPTR(eglCopyBuffers)
#define eglGetProcAddress		FNPTR(eglGetProcAddress)

// ES 2.0
#define	glActiveTexture							FNPTR(glActiveTexture)
#define	glAttachShader							FNPTR(glAttachShader)
#define	glBindAttribLocation					FNPTR(glBindAttribLocation)
#define	glBindBuffer							FNPTR(glBindBuffer)
#define	glBindFramebuffer						FNPTR(glBindFramebuffer)
#define	glBindRenderbuffer						FNPTR(glBindRenderbuffer)
#define	glBindTexture							FNPTR(glBindTexture)
#define	glBlendColor							FNPTR(glBlendColor)
#define	glBlendEquation							FNPTR(glBlendEquation)
#define	glBlendEquationSeparate					FNPTR(glBlendEquationSeparate)
#define	glBlendFunc								FNPTR(glBlendFunc)
#define	glBlendFuncSeparate						FNPTR(glBlendFuncSeparate)
#define	glBufferData							FNPTR(glBufferData)
#define	glBufferSubData							FNPTR(glBufferSubData)
#define	glCheckFramebufferStatus				FNPTR(glCheckFramebufferStatus)
#define	glClear									FNPTR(glClear)
#define	glClearColor							FNPTR(glClearColor)
#define	glClearDepthf							FNPTR(glClearDepthf)
#define	glClearStencil							FNPTR(glClearStencil)
#define	glColorMask								FNPTR(glColorMask)
#define	glCompileShader							FNPTR(glCompileShader)
#define	glCompressedTexImage2D					FNPTR(glCompressedTexImage2D)
#define	glCompressedTexSubImage2D				FNPTR(glCompressedTexSubImage2D)
#define	glCopyTexImage2D						FNPTR(glCopyTexImage2D)
#define	glCopyTexSubImage2D						FNPTR(glCopyTexSubImage2D)
#define	glCreateProgram							FNPTR(glCreateProgram)
#define	glCreateShader							FNPTR(glCreateShader)
#define	glCullFace								FNPTR(glCullFace)
#define	glDeleteBuffers							FNPTR(glDeleteBuffers)
#define	glDeleteFramebuffers					FNPTR(glDeleteFramebuffers)
#define	glDeleteProgram							FNPTR(glDeleteProgram)
#define	glDeleteRenderbuffers					FNPTR(glDeleteRenderbuffers)
#define	glDeleteShader							FNPTR(glDeleteShader)
#define	glDeleteTextures						FNPTR(glDeleteTextures)
#define	glDepthFunc								FNPTR(glDepthFunc)
#define	glDepthMask								FNPTR(glDepthMask)
#define	glDepthRangef							FNPTR(glDepthRangef)
#define	glDetachShader							FNPTR(glDetachShader)
#define	glDisable								FNPTR(glDisable)
#define	glDisableVertexAttribArray				FNPTR(glDisableVertexAttribArray)
#define	glDrawArrays							FNPTR(glDrawArrays)
#define	glDrawElements							FNPTR(glDrawElements)
#define	glEnable								FNPTR(glEnable)
#define	glEnableVertexAttribArray				FNPTR(glEnableVertexAttribArray)
#define	glFinish								FNPTR(glFinish)
#define	glFlush									FNPTR(glFlush)
#define	glFramebufferRenderbuffer				FNPTR(glFramebufferRenderbuffer)
#define	glFramebufferTexture2D					FNPTR(glFramebufferTexture2D)
#define	glFrontFace								FNPTR(glFrontFace)
#define	glGenBuffers							FNPTR(glGenBuffers)
#define	glGenerateMipmap						FNPTR(glGenerateMipmap)
#define	glGenFramebuffers						FNPTR(glGenFramebuffers)
#define	glGenRenderbuffers						FNPTR(glGenRenderbuffers)
#define	glGenTextures							FNPTR(glGenTextures)
#define	glGetActiveAttrib						FNPTR(glGetActiveAttrib)
#define	glGetActiveUniform						FNPTR(glGetActiveUniform)
#define	glGetAttachedShaders					FNPTR(glGetAttachedShaders)
#define	glGetAttribLocation						FNPTR(glGetAttribLocation)
#define	glGetBooleanv							FNPTR(glGetBooleanv)
#define	glGetBufferParameteriv					FNPTR(glGetBufferParameteriv)
#define	glGetError								FNPTR(glGetError)
#define	glGetFloatv								FNPTR(glGetFloatv)
#define	glGetFramebufferAttachmentParameteriv	FNPTR(glGetFramebufferAttachmentParameteriv)
#define	glGetIntegerv							FNPTR(glGetIntegerv)
#define	glGetProgramiv							FNPTR(glGetProgramiv)
#define	glGetProgramInfoLog						FNPTR(glGetProgramInfoLog)
#define	glGetRenderbufferParameteriv			FNPTR(glGetRenderbufferParameteriv)
#define	glGetShaderiv							FNPTR(glGetShaderiv)
#define	glGetShaderInfoLog						FNPTR(glGetShaderInfoLog)
#define	glGetShaderPrecisionFormat				FNPTR(glGetShaderPrecisionFormat)
#define	glGetShaderSource						FNPTR(glGetShaderSource)
#define	glGetString								FNPTR(glGetString)
#define	glGetTexParameterfv						FNPTR(glGetTexParameterfv)
#define	glGetTexParameteriv						FNPTR(glGetTexParameteriv)
#define	glGetUniformfv							FNPTR(glGetUniformfv)
#define	glGetUniformiv							FNPTR(glGetUniformiv)
#define	glGetUniformLocation					FNPTR(glGetUniformLocation)
#define	glGetVertexAttribfv						FNPTR(glGetVertexAttribfv)
#define	glGetVertexAttribiv						FNPTR(glGetVertexAttribiv)
#define	glGetVertexAttribPointerv				FNPTR(glGetVertexAttribPointerv)
#define	glHint									FNPTR(glHint)
#define	glIsBuffer								FNPTR(glIsBuffer)
#define	glIsEnabled								FNPTR(glIsEnabled)
#define	glIsFramebuffer							FNPTR(glIsFramebuffer)
#define	glIsProgram								FNPTR(glIsProgram)
#define	glIsRenderbuffer						FNPTR(glIsRenderbuffer)
#define	glIsShader								FNPTR(glIsShader)
#define	glIsTexture								FNPTR(glIsTexture)
#define	glLineWidth								FNPTR(glLineWidth)
#define	glLinkProgram							FNPTR(glLinkProgram)
#define	glPixelStorei							FNPTR(glPixelStorei)
#define	glPolygonOffset							FNPTR(glPolygonOffset)
#define	glReadPixels							FNPTR(glReadPixels)
#define	glReleaseShaderCompiler					FNPTR(glReleaseShaderCompiler)
#define	glRenderbufferStorage					FNPTR(glRenderbufferStorage)
#define	glSampleCoverage						FNPTR(glSampleCoverage)
#define	glScissor								FNPTR(glScissor)
#define	glShaderBinary							FNPTR(glShaderBinary)
#define	glShaderSource							FNPTR(glShaderSource)
#define	glStencilFunc							FNPTR(glStencilFunc)
#define	glStencilFuncSeparate					FNPTR(glStencilFuncSeparate)
#define	glStencilMask							FNPTR(glStencilMask)
#define	glStencilMaskSeparate					FNPTR(glStencilMaskSeparate)
#define	glStencilOp								FNPTR(glStencilOp)
#define	glStencilOpSeparate						FNPTR(glStencilOpSeparate)
#define	glTexImage2D							FNPTR(glTexImage2D)
#define	glTexParameterf							FNPTR(glTexParameterf)
#define	glTexParameterfv						FNPTR(glTexParameterfv)
#define	glTexParameteri							FNPTR(glTexParameteri)
#define	glTexParameteriv						FNPTR(glTexParameteriv)
#define	glTexSubImage2D							FNPTR(glTexSubImage2D)
#define	glUniform1f								FNPTR(glUniform1f)
#define	glUniform1fv							FNPTR(glUniform1fv)
#define	glUniform1i								FNPTR(glUniform1i)
#define	glUniform1iv							FNPTR(glUniform1iv)
#define	glUniform2f								FNPTR(glUniform2f)
#define	glUniform2fv							FNPTR(glUniform2fv)
#define	glUniform2i								FNPTR(glUniform2i)
#define	glUniform2iv							FNPTR(glUniform2iv)
#define	glUniform3f								FNPTR(glUniform3f)
#define	glUniform3fv							FNPTR(glUniform3fv)
#define	glUniform3i								FNPTR(glUniform3i)
#define	glUniform3iv							FNPTR(glUniform3iv)
#define	glUniform4f								FNPTR(glUniform4f)
#define	glUniform4fv							FNPTR(glUniform4fv)
#define	glUniform4i								FNPTR(glUniform4i)
#define	glUniform4iv							FNPTR(glUniform4iv)
#define	glUniformMatrix2fv						FNPTR(glUniformMatrix2fv)
#define	glUniformMatrix3fv						FNPTR(glUniformMatrix3fv)
#define	glUniformMatrix4fv						FNPTR(glUniformMatrix4fv)
#define	glUseProgram							FNPTR(glUseProgram)
#define	glValidateProgram						FNPTR(glValidateProgram)
#define	glVertexAttrib1f						FNPTR(glVertexAttrib1f)
#define	glVertexAttrib1fv						FNPTR(glVertexAttrib1fv)
#define	glVertexAttrib2f						FNPTR(glVertexAttrib2f)
#define	glVertexAttrib2fv						FNPTR(glVertexAttrib2fv)
#define	glVertexAttrib3f						FNPTR(glVertexAttrib3f)
#define	glVertexAttrib3fv						FNPTR(glVertexAttrib3fv)
#define	glVertexAttrib4f						FNPTR(glVertexAttrib4f)
#define	glVertexAttrib4fv						FNPTR(glVertexAttrib4fv)
#define	glVertexAttribPointer					FNPTR(glVertexAttribPointer)
#define	glViewport								FNPTR(glViewport)


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2


#endif // __PLRENDEREROPENGLES2_RUNTIMELINKING_H__
