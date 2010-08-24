/*********************************************************\
 *  File: ExtensionDefinitions.h                         *
 *      OpenGL extension definitions
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PL_RENDERER_OPENGL_EXTENSION_DEFINITIONS_H__
#define __PL_RENDERER_OPENGL_EXTENSION_DEFINITIONS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRendererOpenGL/PLRendererOpenGL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


// WGL (Windows only)
#ifdef WIN32
	// WGL_ARB_extensions_string
	extern PFNWGLGETEXTENSIONSSTRINGARBPROC	wglGetExtensionsStringARB;

	// WGL_ARB_pbuffer
	extern PFNWGLCREATEPBUFFERARBPROC		wglCreatePbufferARB;
	extern PFNWGLGETPBUFFERDCARBPROC		wglGetPbufferDCARB;
	extern PFNWGLRELEASEPBUFFERDCARBPROC	wglReleasePbufferDCARB;
	extern PFNWGLDESTROYPBUFFERARBPROC		wglDestroyPbufferARB;
	extern PFNWGLQUERYPBUFFERARBPROC		wglQueryPbufferARB;

	// WGL_ARB_pixel_format
	extern PFNWGLGETPIXELFORMATATTRIBIVARBPROC	wglGetPixelFormatAttribivARB;
	extern PFNWGLGETPIXELFORMATATTRIBFVARBPROC	wglGetPixelFormatAttribfvARB;
	extern PFNWGLCHOOSEPIXELFORMATARBPROC		wglChoosePixelFormatARB;

	// WGL_ARB_render_texture
	extern PFNWGLBINDTEXIMAGEARBPROC		wglBindTexImageARB;
	extern PFNWGLRELEASETEXIMAGEARBPROC		wglReleaseTexImageARB;
	extern PFNWGLSETPBUFFERATTRIBARBPROC	wglSetPbufferAttribARB;

	// WGL_ARB_make_current_read
	extern PFNWGLMAKECONTEXTCURRENTARBPROC	wglMakeContextCurrentARB;
	extern PFNWGLGETCURRENTREADDCARBPROC	wglGetCurrentReadDCARB;

	// WGL_EXT_swap_control
	extern PFNWGLSWAPINTERVALEXTPROC	wglSwapIntervalEXT;
	extern PFNWGLGETSWAPINTERVALEXTPROC	wglGetSwapIntervalEXT;
#endif


// GL_EXT_compiled_vertex_array
extern PFNGLLOCKARRAYSEXTPROC	glLockArraysEXT;
extern PFNGLUNLOCKARRAYSEXTPROC	glUnlockArraysEXT;

// GL_EXT_draw_range_elements
extern PFNGLDRAWRANGEELEMENTSEXTPROC	glDrawRangeElementsEXT;

// GL_EXT_fog_coord
extern PFNGLFOGCOORDFEXTPROC		glFogCoordfEXT;
extern PFNGLFOGCOORDFVEXTPROC		glFogCoordfvEXT;
extern PFNGLFOGCOORDDEXTPROC		glFogCoorddEXT;
extern PFNGLFOGCOORDDVEXTPROC		glFogCoorddvEXT;
extern PFNGLFOGCOORDPOINTEREXTPROC	glFogCoordPointerEXT;

// GL_EXT_secondary_color
extern PFNGLSECONDARYCOLOR3BEXTPROC			glSecondaryColor3bEXT;
extern PFNGLSECONDARYCOLOR3BVEXTPROC		glSecondaryColor3bvEXT;
extern PFNGLSECONDARYCOLOR3DEXTPROC			glSecondaryColor3dEXT;
extern PFNGLSECONDARYCOLOR3DVEXTPROC		glSecondaryColor3dvEXT;
extern PFNGLSECONDARYCOLOR3FEXTPROC			glSecondaryColor3fEXT;
extern PFNGLSECONDARYCOLOR3FVEXTPROC		glSecondaryColor3fvEXT;
extern PFNGLSECONDARYCOLOR3IEXTPROC			glSecondaryColor3iEXT;
extern PFNGLSECONDARYCOLOR3IVEXTPROC		glSecondaryColor3ivEXT;
extern PFNGLSECONDARYCOLOR3SEXTPROC			glSecondaryColor3sEXT;
extern PFNGLSECONDARYCOLOR3SVEXTPROC		glSecondaryColor3svEXT;
extern PFNGLSECONDARYCOLOR3UBEXTPROC		glSecondaryColor3ubEXT;
extern PFNGLSECONDARYCOLOR3UBVEXTPROC		glSecondaryColor3ubvEXT;
extern PFNGLSECONDARYCOLOR3UIEXTPROC		glSecondaryColor3uiEXT;
extern PFNGLSECONDARYCOLOR3UIVEXTPROC		glSecondaryColor3uivEXT;
extern PFNGLSECONDARYCOLOR3USEXTPROC		glSecondaryColor3usEXT;
extern PFNGLSECONDARYCOLOR3USVEXTPROC		glSecondaryColor3usvEXT;
extern PFNGLSECONDARYCOLORPOINTEREXTPROC	glSecondaryColorPointerEXT;

// GL_EXT_texture3D
extern PFNGLTEXIMAGE3DEXTPROC		glTexImage3DEXT;
extern PFNGLTEXSUBIMAGE3DEXTPROC	glTexSubImage3DEXT;

// GL_EXT_stencil_two_side
extern PFNGLACTIVESTENCILFACEEXTPROC	glActiveStencilFaceEXT;

// GL_EXT_depth_bounds_test
extern PFNGLDEPTHBOUNDSEXTPROC	glDepthBoundsEXT;

// GL_EXT_framebuffer_object
extern PFNGLISRENDERBUFFEREXTPROC						glIsRenderbufferEXT;
extern PFNGLBINDRENDERBUFFEREXTPROC						glBindRenderbufferEXT;
extern PFNGLDELETERENDERBUFFERSEXTPROC					glDeleteRenderbuffersEXT;
extern PFNGLGENRENDERBUFFERSEXTPROC						glGenRenderbuffersEXT;
extern PFNGLRENDERBUFFERSTORAGEEXTPROC					glRenderbufferStorageEXT;
extern PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC			glGetRenderbufferParameterivEXT;
extern PFNGLISFRAMEBUFFEREXTPROC						glIsFramebufferEXT;
extern PFNGLBINDFRAMEBUFFEREXTPROC						glBindFramebufferEXT;
extern PFNGLDELETEFRAMEBUFFERSEXTPROC					glDeleteFramebuffersEXT;
extern PFNGLGENFRAMEBUFFERSEXTPROC						glGenFramebuffersEXT;
extern PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC				glCheckFramebufferStatusEXT;
extern PFNGLFRAMEBUFFERTEXTURE1DEXTPROC					glFramebufferTexture1DEXT;
extern PFNGLFRAMEBUFFERTEXTURE2DEXTPROC					glFramebufferTexture2DEXT;
extern PFNGLFRAMEBUFFERTEXTURE3DEXTPROC					glFramebufferTexture3DEXT;
extern PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC				glFramebufferRenderbufferEXT;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC	glGetFramebufferAttachmentParameterivEXT;
extern PFNGLGENERATEMIPMAPEXTPROC						glGenerateMipmapEXT;

// GL_EXT_framebuffer_multisample
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC		glRenderbufferStorageMultisampleEXT;

// GL_EXT_framebuffer_blit
extern PFNGLBLITFRAMEBUFFEREXTPROC						glBlitFramebufferEXT;

// GL_EXT_geometry_shader4
extern PFNGLPROGRAMPARAMETERIEXTPROC					glProgramParameteriEXT;


// GL_ARB_color_buffer_float
extern PFNGLCLAMPCOLORARBPROC			glClampColorARB;

// GL_ARB_multitexture
extern PFNGLACTIVETEXTUREARBPROC		glActiveTextureARB;
extern PFNGLCLIENTACTIVETEXTUREARBPROC	glClientActiveTextureARB;
extern PFNGLMULTITEXCOORD1DARBPROC		glMultiTexCoord1dARB;
extern PFNGLMULTITEXCOORD1DVARBPROC		glMultiTexCoord1dvARB;
extern PFNGLMULTITEXCOORD1FARBPROC		glMultiTexCoord1fARB;
extern PFNGLMULTITEXCOORD1FVARBPROC		glMultiTexCoord1fvARB;
extern PFNGLMULTITEXCOORD1IARBPROC		glMultiTexCoord1iARB;
extern PFNGLMULTITEXCOORD1IVARBPROC		glMultiTexCoord1ivARB;
extern PFNGLMULTITEXCOORD1SARBPROC		glMultiTexCoord1sARB;
extern PFNGLMULTITEXCOORD1SVARBPROC		glMultiTexCoord1svARB;
extern PFNGLMULTITEXCOORD2DARBPROC		glMultiTexCoord2dARB;
extern PFNGLMULTITEXCOORD2DVARBPROC		glMultiTexCoord2dvARB;
extern PFNGLMULTITEXCOORD2FARBPROC		glMultiTexCoord2fARB;
extern PFNGLMULTITEXCOORD2FVARBPROC		glMultiTexCoord2fvARB;
extern PFNGLMULTITEXCOORD2IARBPROC		glMultiTexCoord2iARB;
extern PFNGLMULTITEXCOORD2IVARBPROC		glMultiTexCoord2ivARB;
extern PFNGLMULTITEXCOORD2SARBPROC		glMultiTexCoord2sARB;
extern PFNGLMULTITEXCOORD2SVARBPROC		glMultiTexCoord2svARB;
extern PFNGLMULTITEXCOORD3DARBPROC		glMultiTexCoord3dARB;
extern PFNGLMULTITEXCOORD3DVARBPROC		glMultiTexCoord3dvARB;
extern PFNGLMULTITEXCOORD3FARBPROC		glMultiTexCoord3fARB;
extern PFNGLMULTITEXCOORD3FVARBPROC		glMultiTexCoord3fvARB;
extern PFNGLMULTITEXCOORD3IARBPROC		glMultiTexCoord3iARB;
extern PFNGLMULTITEXCOORD3IVARBPROC		glMultiTexCoord3ivARB;
extern PFNGLMULTITEXCOORD3SARBPROC		glMultiTexCoord3sARB;
extern PFNGLMULTITEXCOORD3SVARBPROC		glMultiTexCoord3svARB;
extern PFNGLMULTITEXCOORD4DARBPROC		glMultiTexCoord4dARB;
extern PFNGLMULTITEXCOORD4DVARBPROC		glMultiTexCoord4dvARB;
extern PFNGLMULTITEXCOORD4FARBPROC		glMultiTexCoord4fARB;
extern PFNGLMULTITEXCOORD4FVARBPROC		glMultiTexCoord4fvARB;
extern PFNGLMULTITEXCOORD4IARBPROC		glMultiTexCoord4iARB;
extern PFNGLMULTITEXCOORD4IVARBPROC		glMultiTexCoord4ivARB;
extern PFNGLMULTITEXCOORD4SARBPROC		glMultiTexCoord4sARB;
extern PFNGLMULTITEXCOORD4SVARBPROC		glMultiTexCoord4svARB;

// GL_ARB_vertex_buffer_object
extern PFNGLBINDBUFFERARBPROC			glBindBufferARB;
extern PFNGLDELETEBUFFERSARBPROC		glDeleteBuffersARB;
extern PFNGLGENBUFFERSARBPROC			glGenBuffersARB;
extern PFNGLBUFFERDATAARBPROC			glBufferDataARB;
extern PFNGLBUFFERSUBDATAARBPROC		glBufferSubDataARB;
extern PFNGLGETBUFFERSUBDATAARBPROC		glGetBufferSubDataARB;
extern PFNGLMAPBUFFERARBPROC			glMapBufferARB;
extern PFNGLUNMAPBUFFERARBPROC			glUnmapBufferARB;
extern PFNGLGETBUFFERPARAMETERIVARBPROC	glGetBufferParameterivARB;
extern PFNGLGETBUFFERPOINTERVARBPROC	glGetBufferPointervARB;

// GL_ARB_occlusion_query
extern PFNGLGENQUERIESARBPROC			glGenQueriesARB;
extern PFNGLDELETEQUERIESARBPROC		glDeleteQueriesARB;
extern PFNGLISQUERYARBPROC				glIsQueryARB;
extern PFNGLBEGINQUERYARBPROC			glBeginQueryARB;
extern PFNGLENDQUERYARBPROC				glEndQueryARB;
extern PFNGLGETQUERYIVARBPROC			glGetQueryivARB;
extern PFNGLGETQUERYOBJECTIVARBPROC		glGetQueryObjectivARB;
extern PFNGLGETQUERYOBJECTUIVARBPROC	glGetQueryObjectuivARB;

// GL_ARB_texture_compression
extern PFNGLCOMPRESSEDTEXIMAGE3DARBPROC		glCompressedTexImage3DARB;
extern PFNGLCOMPRESSEDTEXIMAGE2DARBPROC		glCompressedTexImage2DARB;
extern PFNGLCOMPRESSEDTEXIMAGE1DARBPROC		glCompressedTexImage1DARB;
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC	glCompressedTexSubImage3DARB;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC	glCompressedTexSubImage2DARB;
extern PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC	glCompressedTexSubImage1DARB;
extern PFNGLGETCOMPRESSEDTEXIMAGEARBPROC	glGetCompressedTexImageARB;


// GL_NV_texture_rectangle & GL_EXT_texture_rectangle
#ifdef GL_NV_texture_rectangle
#define GL_TEXTURE_RECTANGLE_EXT GL_TEXTURE_RECTANGLE_NV
#endif

// GL_NV_occlusion_query
extern PFNGLGENOCCLUSIONQUERIESNVPROC		glGenOcclusionQueriesNV;
extern PFNGLDELETEOCCLUSIONQUERIESNVPROC	glDeleteOcclusionQueriesNV;
extern PFNGLISOCCLUSIONQUERYNVPROC			glIsOcclusionQueryNV;
extern PFNGLBEGINOCCLUSIONQUERYNVPROC		glBeginOcclusionQueryNV;
extern PFNGLENDOCCLUSIONQUERYNVPROC			glEndOcclusionQueryNV;
extern PFNGLGETOCCLUSIONQUERYIVNVPROC		glGetOcclusionQueryivNV;
extern PFNGLGETOCCLUSIONQUERYUIVNVPROC		glGetOcclusionQueryuivNV;


// GL_ARB_point_parameters
extern PFNGLPOINTPARAMETERFARBPROC	glPointParameterfARB;
extern PFNGLPOINTPARAMETERFVARBPROC	glPointParameterfvARB;

// GL_ARB_point_sprite [TODO] Find correct OpenGL header!
#define GL_POINT_SPRITE_ARB		0x8861
#define GL_COORD_REPLACE_ARB	0x8862

// GL_ARB_vertex_program
extern PFNGLVERTEXATTRIBPOINTERARBPROC		glVertexAttribPointerARB;
extern PFNGLENABLEVERTEXATTRIBARRAYARBPROC	glEnableVertexAttribArrayARB;
extern PFNGLDISABLEVERTEXATTRIBARRAYARBPROC	glDisableVertexAttribArrayARB;
extern PFNGLGETPROGRAMIVARBPROC				glGetProgramivARB;

// GL_ARB_draw_buffers
extern PFNGLDRAWBUFFERSARBPROC	glDrawBuffersARB;

// GL_ARB_shader_objects
extern PFNGLDELETEOBJECTARBPROC			glDeleteObjectARB;
extern PFNGLGETHANDLEARBPROC			glGetHandleARB;
extern PFNGLDETACHOBJECTARBPROC			glDetachObjectARB;
extern PFNGLCREATESHADEROBJECTARBPROC	glCreateShaderObjectARB;
extern PFNGLSHADERSOURCEARBPROC			glShaderSourceARB;
extern PFNGLCOMPILESHADERARBPROC		glCompileShaderARB;
extern PFNGLCREATEPROGRAMOBJECTARBPROC	glCreateProgramObjectARB;
extern PFNGLATTACHOBJECTARBPROC			glAttachObjectARB;
extern PFNGLLINKPROGRAMARBPROC			glLinkProgramARB;
extern PFNGLUSEPROGRAMOBJECTARBPROC		glUseProgramObjectARB;
extern PFNGLVALIDATEPROGRAMARBPROC		glValidateProgramARB;
extern PFNGLUNIFORM1FARBPROC			glUniform1fARB;
extern PFNGLUNIFORM2FARBPROC			glUniform2fARB;
extern PFNGLUNIFORM3FARBPROC			glUniform3fARB;
extern PFNGLUNIFORM4FARBPROC			glUniform4fARB;
extern PFNGLUNIFORM1IARBPROC			glUniform1iARB;
extern PFNGLUNIFORM2IARBPROC			glUniform2iARB;
extern PFNGLUNIFORM3IARBPROC			glUniform3iARB;
extern PFNGLUNIFORM4IARBPROC			glUniform4iARB;
extern PFNGLUNIFORM1FVARBPROC			glUniform1fvARB;
extern PFNGLUNIFORM2FVARBPROC			glUniform2fvARB;
extern PFNGLUNIFORM3FVARBPROC			glUniform3fvARB;
extern PFNGLUNIFORM4FVARBPROC			glUniform4fvARB;
extern PFNGLUNIFORM1IVARBPROC			glUniform1ivARB;
extern PFNGLUNIFORM2IVARBPROC			glUniform2ivARB;
extern PFNGLUNIFORM3IVARBPROC			glUniform3ivARB;
extern PFNGLUNIFORM4IVARBPROC			glUniform4ivARB;
extern PFNGLUNIFORMMATRIX2FVARBPROC		glUniformMatrix2fvARB;
extern PFNGLUNIFORMMATRIX3FVARBPROC		glUniformMatrix3fvARB;
extern PFNGLUNIFORMMATRIX4FVARBPROC		glUniformMatrix4fvARB;
extern PFNGLGETOBJECTPARAMETERFVARBPROC	glGetObjectParameterfvARB;
extern PFNGLGETOBJECTPARAMETERIVARBPROC	glGetObjectParameterivARB;
extern PFNGLGETINFOLOGARBPROC			glGetInfoLogARB;
extern PFNGLGETATTACHEDOBJECTSARBPROC	glGetAttachedObjectsARB;
extern PFNGLGETUNIFORMLOCATIONARBPROC	glGetUniformLocationARB;
extern PFNGLGETACTIVEUNIFORMARBPROC		glGetActiveUniformARB;
extern PFNGLGETUNIFORMFVARBPROC			glGetUniformfvARB;
extern PFNGLGETUNIFORMIVARBPROC			glGetUniformivARB;
extern PFNGLGETSHADERSOURCEARBPROC		glGetShaderSourceARB;

// GL_ARB_vertex_shader
extern PFNGLBINDATTRIBLOCATIONARBPROC	glBindAttribLocationARB;
extern PFNGLGETACTIVEATTRIBARBPROC		glGetActiveAttribARB;
extern PFNGLGETATTRIBLOCATIONARBPROC	glGetAttribLocationARB;

// GL_ATI_separate_stencil
extern PFNGLSTENCILOPSEPARATEATIPROC	glStencilOpSeparateATI;
extern PFNGLSTENCILFUNCSEPARATEATIPROC	glStencilFuncSeparateATI;

// GL_ATI_draw_buffers
extern PFNGLDRAWBUFFERSATIPROC	glDrawBuffersATI;

// GL_AMD_vertex_shader_tessellator
extern PFNGLTESSELLATIONFACTORAMDPROC	glTessellationFactorAMD;
extern PFNGLTESSELLATIONMODEAMDPROC		glTessellationModeAMD;


// GLX (Linux only)
#ifdef LINUX
	extern PFNGLXCREATEPBUFFERPROC	glXCreatePbuffer;
	extern PFNGLXDESTROYPBUFFERPROC	glXDestroyPbuffer;
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PL_RENDERER_OPENGL_EXTENSION_DEFINITIONS_H__
