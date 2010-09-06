/*********************************************************\
 *  File: Extensions.cpp                                 *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Log/Log.h>
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/Misc/Extensions.h"
#ifdef LINUX
	#include <string.h>	// For strstr
	#include "PLRendererOpenGL/ContextLinux.h"
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Extension functions                                   ]
//[-------------------------------------------------------]
// WGL (Windows only)
#ifdef WIN32
	// WGL_ARB_extensions_string
	PFNWGLGETEXTENSIONSSTRINGARBPROC	wglGetExtensionsStringARB	= NULL;

	// WGL_EXT_swap_control
	PFNWGLSWAPINTERVALEXTPROC		wglSwapIntervalEXT		= NULL;
	PFNWGLGETSWAPINTERVALEXTPROC	wglGetSwapIntervalEXT	= NULL;

	// WGL_ARB_pbuffer
	PFNWGLCREATEPBUFFERARBPROC		wglCreatePbufferARB		= NULL;
	PFNWGLGETPBUFFERDCARBPROC		wglGetPbufferDCARB		= NULL;
	PFNWGLRELEASEPBUFFERDCARBPROC	wglReleasePbufferDCARB	= NULL;
	PFNWGLDESTROYPBUFFERARBPROC		wglDestroyPbufferARB	= NULL;
	PFNWGLQUERYPBUFFERARBPROC		wglQueryPbufferARB		= NULL;

	// WGL_ARB_pixel_format
	PFNWGLGETPIXELFORMATATTRIBIVARBPROC	wglGetPixelFormatAttribivARB	= NULL;
	PFNWGLGETPIXELFORMATATTRIBFVARBPROC	wglGetPixelFormatAttribfvARB	= NULL;
	PFNWGLCHOOSEPIXELFORMATARBPROC		wglChoosePixelFormatARB			= NULL;

	// WGL_ARB_render_texture
	PFNWGLBINDTEXIMAGEARBPROC		wglBindTexImageARB		= NULL;
	PFNWGLRELEASETEXIMAGEARBPROC	wglReleaseTexImageARB	= NULL;
	PFNWGLSETPBUFFERATTRIBARBPROC	wglSetPbufferAttribARB	= NULL;

	// WGL_ARB_make_current_read
	PFNWGLMAKECONTEXTCURRENTARBPROC	wglMakeContextCurrentARB	= NULL;
	PFNWGLGETCURRENTREADDCARBPROC	wglGetCurrentReadDCARB		= NULL;
#endif


// GL_EXT_compiled_vertex_array
PFNGLLOCKARRAYSEXTPROC		glLockArraysEXT		= NULL;
PFNGLUNLOCKARRAYSEXTPROC	glUnlockArraysEXT	= NULL;

// GL_EXT_draw_range_elements
PFNGLDRAWRANGEELEMENTSEXTPROC	glDrawRangeElementsEXT	= NULL;

// GL_EXT_fog_coord
PFNGLFOGCOORDFEXTPROC		glFogCoordfEXT			= NULL;
PFNGLFOGCOORDFVEXTPROC		glFogCoordfvEXT			= NULL;
PFNGLFOGCOORDDEXTPROC		glFogCoorddEXT			= NULL;
PFNGLFOGCOORDDVEXTPROC		glFogCoorddvEXT			= NULL;
PFNGLFOGCOORDPOINTEREXTPROC	glFogCoordPointerEXT	= NULL;

// GL_EXT_secondary_color
PFNGLSECONDARYCOLOR3BEXTPROC		glSecondaryColor3bEXT		= NULL;
PFNGLSECONDARYCOLOR3BVEXTPROC		glSecondaryColor3bvEXT		= NULL;
PFNGLSECONDARYCOLOR3DEXTPROC		glSecondaryColor3dEXT 		= NULL;
PFNGLSECONDARYCOLOR3DVEXTPROC		glSecondaryColor3dvEXT		= NULL;
PFNGLSECONDARYCOLOR3FEXTPROC		glSecondaryColor3fEXT		= NULL;
PFNGLSECONDARYCOLOR3FVEXTPROC		glSecondaryColor3fvEXT		= NULL;
PFNGLSECONDARYCOLOR3IEXTPROC		glSecondaryColor3iEXT		= NULL;
PFNGLSECONDARYCOLOR3IVEXTPROC		glSecondaryColor3ivEXT		= NULL;
PFNGLSECONDARYCOLOR3SEXTPROC		glSecondaryColor3sEXT		= NULL;
PFNGLSECONDARYCOLOR3SVEXTPROC		glSecondaryColor3svEXT		= NULL;
PFNGLSECONDARYCOLOR3UBEXTPROC		glSecondaryColor3ubEXT		= NULL;
PFNGLSECONDARYCOLOR3UBVEXTPROC		glSecondaryColor3ubvEXT		= NULL;
PFNGLSECONDARYCOLOR3UIEXTPROC		glSecondaryColor3uiEXT		= NULL;
PFNGLSECONDARYCOLOR3UIVEXTPROC		glSecondaryColor3uivEXT		= NULL;
PFNGLSECONDARYCOLOR3USEXTPROC		glSecondaryColor3usEXT		= NULL;
PFNGLSECONDARYCOLOR3USVEXTPROC		glSecondaryColor3usvEXT		= NULL;
PFNGLSECONDARYCOLORPOINTEREXTPROC	glSecondaryColorPointerEXT	= NULL;

// GL_EXT_texture3D
PFNGLTEXIMAGE3DEXTPROC		glTexImage3DEXT		= NULL;
PFNGLTEXSUBIMAGE3DEXTPROC	glTexSubImage3DEXT	= NULL;

// GL_EXT_stencil_two_side
PFNGLACTIVESTENCILFACEEXTPROC	glActiveStencilFaceEXT	= NULL;

// GL_EXT_depth_bounds_test
PFNGLDEPTHBOUNDSEXTPROC	glDepthBoundsEXT	= NULL;

// GL_EXT_framebuffer_object
PFNGLISRENDERBUFFEREXTPROC						glIsRenderbufferEXT							= NULL;
PFNGLBINDRENDERBUFFEREXTPROC					glBindRenderbufferEXT						= NULL;
PFNGLDELETERENDERBUFFERSEXTPROC					glDeleteRenderbuffersEXT					= NULL;
PFNGLGENRENDERBUFFERSEXTPROC					glGenRenderbuffersEXT						= NULL;
PFNGLRENDERBUFFERSTORAGEEXTPROC					glRenderbufferStorageEXT					= NULL;
PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC			glGetRenderbufferParameterivEXT				= NULL;
PFNGLISFRAMEBUFFEREXTPROC						glIsFramebufferEXT							= NULL;
PFNGLBINDFRAMEBUFFEREXTPROC						glBindFramebufferEXT						= NULL;
PFNGLDELETEFRAMEBUFFERSEXTPROC					glDeleteFramebuffersEXT						= NULL;
PFNGLGENFRAMEBUFFERSEXTPROC						glGenFramebuffersEXT						= NULL;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC				glCheckFramebufferStatusEXT					= NULL;
PFNGLFRAMEBUFFERTEXTURE1DEXTPROC				glFramebufferTexture1DEXT					= NULL;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC				glFramebufferTexture2DEXT					= NULL;
PFNGLFRAMEBUFFERTEXTURE3DEXTPROC				glFramebufferTexture3DEXT					= NULL;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC				glFramebufferRenderbufferEXT				= NULL;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC	glGetFramebufferAttachmentParameterivEXT	= NULL;
PFNGLGENERATEMIPMAPEXTPROC						glGenerateMipmapEXT							= NULL;

// GL_EXT_framebuffer_multisample
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC		glRenderbufferStorageMultisampleEXT			= NULL;

// GL_EXT_framebuffer_blit
PFNGLBLITFRAMEBUFFEREXTPROC						glBlitFramebufferEXT						= NULL;

// GL_EXT_geometry_shader4
PFNGLPROGRAMPARAMETERIEXTPROC					glProgramParameteriEXT						= NULL;

// GL_ARB_color_buffer_float
PFNGLCLAMPCOLORARBPROC			glClampColorARB				= NULL;

// GL_ARB_multitexture
PFNGLACTIVETEXTUREARBPROC		glActiveTextureARB			= NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC	glClientActiveTextureARB	= NULL;
PFNGLMULTITEXCOORD1DARBPROC		glMultiTexCoord1dARB		= NULL;
PFNGLMULTITEXCOORD1DVARBPROC	glMultiTexCoord1dvARB		= NULL;
PFNGLMULTITEXCOORD1FARBPROC		glMultiTexCoord1fARB		= NULL;
PFNGLMULTITEXCOORD1FVARBPROC	glMultiTexCoord1fvARB		= NULL;
PFNGLMULTITEXCOORD1IARBPROC		glMultiTexCoord1iARB		= NULL;
PFNGLMULTITEXCOORD1IVARBPROC	glMultiTexCoord1ivARB		= NULL;
PFNGLMULTITEXCOORD1SARBPROC		glMultiTexCoord1sARB		= NULL;
PFNGLMULTITEXCOORD1SVARBPROC	glMultiTexCoord1svARB		= NULL;
PFNGLMULTITEXCOORD2DARBPROC		glMultiTexCoord2dARB		= NULL;
PFNGLMULTITEXCOORD2DVARBPROC	glMultiTexCoord2dvARB		= NULL;
PFNGLMULTITEXCOORD2FARBPROC		glMultiTexCoord2fARB		= NULL;
PFNGLMULTITEXCOORD2FVARBPROC	glMultiTexCoord2fvARB		= NULL;
PFNGLMULTITEXCOORD2IARBPROC		glMultiTexCoord2iARB		= NULL;
PFNGLMULTITEXCOORD2IVARBPROC	glMultiTexCoord2ivARB		= NULL;
PFNGLMULTITEXCOORD2SARBPROC		glMultiTexCoord2sARB		= NULL;
PFNGLMULTITEXCOORD2SVARBPROC	glMultiTexCoord2svARB		= NULL;
PFNGLMULTITEXCOORD3DARBPROC		glMultiTexCoord3dARB		= NULL;
PFNGLMULTITEXCOORD3DVARBPROC	glMultiTexCoord3dvARB		= NULL;
PFNGLMULTITEXCOORD3FARBPROC		glMultiTexCoord3fARB		= NULL;
PFNGLMULTITEXCOORD3FVARBPROC	glMultiTexCoord3fvARB		= NULL;
PFNGLMULTITEXCOORD3IARBPROC		glMultiTexCoord3iARB		= NULL;
PFNGLMULTITEXCOORD3IVARBPROC	glMultiTexCoord3ivARB		= NULL;
PFNGLMULTITEXCOORD3SARBPROC		glMultiTexCoord3sARB		= NULL;
PFNGLMULTITEXCOORD3SVARBPROC	glMultiTexCoord3svARB		= NULL;
PFNGLMULTITEXCOORD4DARBPROC		glMultiTexCoord4dARB		= NULL;
PFNGLMULTITEXCOORD4DVARBPROC	glMultiTexCoord4dvARB		= NULL;
PFNGLMULTITEXCOORD4FARBPROC		glMultiTexCoord4fARB		= NULL;
PFNGLMULTITEXCOORD4FVARBPROC	glMultiTexCoord4fvARB		= NULL;
PFNGLMULTITEXCOORD4IARBPROC		glMultiTexCoord4iARB		= NULL;
PFNGLMULTITEXCOORD4IVARBPROC	glMultiTexCoord4ivARB		= NULL;
PFNGLMULTITEXCOORD4SARBPROC		glMultiTexCoord4sARB		= NULL;
PFNGLMULTITEXCOORD4SVARBPROC	glMultiTexCoord4svARB		= NULL;

// GL_ARB_vertex_buffer_object 
PFNGLBINDBUFFERARBPROC				glBindBufferARB				= NULL;
PFNGLDELETEBUFFERSARBPROC			glDeleteBuffersARB			= NULL;
PFNGLGENBUFFERSARBPROC				glGenBuffersARB				= NULL;
PFNGLBUFFERDATAARBPROC				glBufferDataARB				= NULL;
PFNGLBUFFERSUBDATAARBPROC			glBufferSubDataARB			= NULL;
PFNGLGETBUFFERSUBDATAARBPROC		glGetBufferSubDataARB		= NULL;
PFNGLMAPBUFFERARBPROC				glMapBufferARB				= NULL;
PFNGLUNMAPBUFFERARBPROC				glUnmapBufferARB			= NULL;
PFNGLGETBUFFERPARAMETERIVARBPROC	glGetBufferParameterivARB	= NULL;
PFNGLGETBUFFERPOINTERVARBPROC		glGetBufferPointervARB		= NULL;

// GL_ARB_occlusion_query
PFNGLGENQUERIESARBPROC			glGenQueriesARB			= NULL;
PFNGLDELETEQUERIESARBPROC		glDeleteQueriesARB		= NULL;
PFNGLISQUERYARBPROC				glIsQueryARB			= NULL;
PFNGLBEGINQUERYARBPROC			glBeginQueryARB			= NULL;
PFNGLENDQUERYARBPROC			glEndQueryARB			= NULL;
PFNGLGETQUERYIVARBPROC			glGetQueryivARB			= NULL;
PFNGLGETQUERYOBJECTIVARBPROC	glGetQueryObjectivARB	= NULL;
PFNGLGETQUERYOBJECTUIVARBPROC	glGetQueryObjectuivARB	= NULL;

// GL_ARB_texture_compression
PFNGLCOMPRESSEDTEXIMAGE3DARBPROC	glCompressedTexImage3DARB		= NULL;
PFNGLCOMPRESSEDTEXIMAGE2DARBPROC	glCompressedTexImage2DARB		= NULL;
PFNGLCOMPRESSEDTEXIMAGE1DARBPROC	glCompressedTexImage1DARB		= NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC	glCompressedTexSubImage3DARB	= NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC	glCompressedTexSubImage2DARB	= NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC	glCompressedTexSubImage1DARB	= NULL;
PFNGLGETCOMPRESSEDTEXIMAGEARBPROC	glGetCompressedTexImageARB		= NULL;

// GL_ARB_point_parameters
PFNGLPOINTPARAMETERFARBPROC		glPointParameterfARB	= NULL;
PFNGLPOINTPARAMETERFVARBPROC	glPointParameterfvARB	= NULL;

// GL_ARB_vertex_program
PFNGLVERTEXATTRIBPOINTERARBPROC			glVertexAttribPointerARB		= NULL;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC		glEnableVertexAttribArrayARB	= NULL;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC	glDisableVertexAttribArrayARB	= NULL;
PFNGLGETPROGRAMIVARBPROC				glGetProgramivARB				= NULL;

// GL_ARB_draw_buffers
PFNGLDRAWBUFFERSARBPROC	glDrawBuffersARB	= NULL;

// GL_ARB_shader_objects
PFNGLDELETEOBJECTARBPROC			glDeleteObjectARB			= NULL;
PFNGLGETHANDLEARBPROC				glGetHandleARB				= NULL;
PFNGLDETACHOBJECTARBPROC			glDetachObjectARB			= NULL;
PFNGLCREATESHADEROBJECTARBPROC		glCreateShaderObjectARB		= NULL;
PFNGLSHADERSOURCEARBPROC			glShaderSourceARB			= NULL;
PFNGLCOMPILESHADERARBPROC			glCompileShaderARB			= NULL;
PFNGLCREATEPROGRAMOBJECTARBPROC		glCreateProgramObjectARB	= NULL;
PFNGLATTACHOBJECTARBPROC			glAttachObjectARB			= NULL;
PFNGLLINKPROGRAMARBPROC				glLinkProgramARB			= NULL;
PFNGLUSEPROGRAMOBJECTARBPROC		glUseProgramObjectARB		= NULL;
PFNGLVALIDATEPROGRAMARBPROC			glValidateProgramARB		= NULL;
PFNGLUNIFORM1FARBPROC				glUniform1fARB				= NULL;
PFNGLUNIFORM2FARBPROC				glUniform2fARB				= NULL;
PFNGLUNIFORM3FARBPROC				glUniform3fARB				= NULL;
PFNGLUNIFORM4FARBPROC				glUniform4fARB				= NULL;
PFNGLUNIFORM1IARBPROC				glUniform1iARB				= NULL;
PFNGLUNIFORM2IARBPROC				glUniform2iARB				= NULL;
PFNGLUNIFORM3IARBPROC				glUniform3iARB				= NULL;
PFNGLUNIFORM4IARBPROC				glUniform4iARB				= NULL;
PFNGLUNIFORM1FVARBPROC				glUniform1fvARB				= NULL;
PFNGLUNIFORM2FVARBPROC				glUniform2fvARB				= NULL;
PFNGLUNIFORM3FVARBPROC				glUniform3fvARB				= NULL;
PFNGLUNIFORM4FVARBPROC				glUniform4fvARB				= NULL;
PFNGLUNIFORM1IVARBPROC				glUniform1ivARB				= NULL;
PFNGLUNIFORM2IVARBPROC				glUniform2ivARB				= NULL;
PFNGLUNIFORM3IVARBPROC				glUniform3ivARB				= NULL;
PFNGLUNIFORM4IVARBPROC				glUniform4ivARB				= NULL;
PFNGLUNIFORMMATRIX2FVARBPROC		glUniformMatrix2fvARB		= NULL;
PFNGLUNIFORMMATRIX3FVARBPROC		glUniformMatrix3fvARB		= NULL;
PFNGLUNIFORMMATRIX4FVARBPROC		glUniformMatrix4fvARB		= NULL;
PFNGLGETOBJECTPARAMETERFVARBPROC	glGetObjectParameterfvARB	= NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC	glGetObjectParameterivARB	= NULL;
PFNGLGETINFOLOGARBPROC				glGetInfoLogARB				= NULL;
PFNGLGETATTACHEDOBJECTSARBPROC		glGetAttachedObjectsARB		= NULL;
PFNGLGETUNIFORMLOCATIONARBPROC		glGetUniformLocationARB		= NULL;
PFNGLGETACTIVEUNIFORMARBPROC		glGetActiveUniformARB		= NULL;
PFNGLGETUNIFORMFVARBPROC			glGetUniformfvARB			= NULL;
PFNGLGETUNIFORMIVARBPROC			glGetUniformivARB			= NULL;
PFNGLGETSHADERSOURCEARBPROC			glGetShaderSourceARB		= NULL;

// GL_ARB_vertex_shader
PFNGLBINDATTRIBLOCATIONARBPROC	glBindAttribLocationARB	= NULL;
PFNGLGETACTIVEATTRIBARBPROC		glGetActiveAttribARB	= NULL;
PFNGLGETATTRIBLOCATIONARBPROC	glGetAttribLocationARB	= NULL;

// GL_NV_occlusion_query
PFNGLGENOCCLUSIONQUERIESNVPROC		glGenOcclusionQueriesNV		= NULL;
PFNGLDELETEOCCLUSIONQUERIESNVPROC	glDeleteOcclusionQueriesNV	= NULL;
PFNGLISOCCLUSIONQUERYNVPROC			glIsOcclusionQueryNV		= NULL;
PFNGLBEGINOCCLUSIONQUERYNVPROC		glBeginOcclusionQueryNV		= NULL;
PFNGLENDOCCLUSIONQUERYNVPROC		glEndOcclusionQueryNV		= NULL;
PFNGLGETOCCLUSIONQUERYIVNVPROC		glGetOcclusionQueryivNV		= NULL;
PFNGLGETOCCLUSIONQUERYUIVNVPROC		glGetOcclusionQueryuivNV	= NULL;


// GL_ATI_separate_stencil
PFNGLSTENCILOPSEPARATEATIPROC	glStencilOpSeparateATI		= NULL;
PFNGLSTENCILFUNCSEPARATEATIPROC	glStencilFuncSeparateATI	= NULL;

// GL_ATI_draw_buffers
PFNGLDRAWBUFFERSATIPROC	glDrawBuffersATI	= NULL;

// GL_AMD_vertex_shader_tessellator
PFNGLTESSELLATIONFACTORAMDPROC	glTessellationFactorAMD	= NULL;
PFNGLTESSELLATIONMODEAMDPROC	glTessellationModeAMD	= NULL;


// GLX (Linux only)
#ifdef LINUX
	PFNGLXCREATEPBUFFERPROC		glXCreatePbuffer	= NULL;
	PFNGLXDESTROYPBUFFERPROC	glXDestroyPbuffer	= NULL;
#endif


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
OpenGLExtensions::OpenGLExtensions(Renderer &cRenderer) :
	m_pRenderer(&cRenderer)
{
	// [TODO] Update this configuration related stuff?
	// Create 'RendererOpenGLExtensionConfig'
	// Config::GetInstance()->GetClass("PLRendererOpenGL::RendererOpenGLExtensionConfig");

	// Reset extensions
	ResetExtensions();
}

/**
*  @brief
*    Returns whether the extensions are initialized or not
*/
bool OpenGLExtensions::IsInitialized() const
{
	return m_bInitialized;
}

///////////////////////////////////////////////////////////
// Returns whether an extension is supported or not
///////////////////////////////////////////////////////////
// WGL (Windows only)
bool OpenGLExtensions::IsWGL_EXT_swap_control()					const { return m_bWGL_EXT_swap_control;				 }
bool OpenGLExtensions::IsWGL_ARB_extensions_string()			const { return m_bWGL_ARB_extensions_string;		 }
bool OpenGLExtensions::IsWGL_ARB_pbuffer()						const { return m_bWGL_ARB_pbuffer;					 }
bool OpenGLExtensions::IsWGL_ARB_pixel_format()					const { return m_bWGL_ARB_pixel_format;				 }
bool OpenGLExtensions::IsWGL_ARB_render_texture()				const { return m_bWGL_ARB_render_texture;			 }
bool OpenGLExtensions::IsWGL_ARB_make_current_read()			const { return m_bWGL_ARB_make_current_read;		 }
bool OpenGLExtensions::IsWGL_ARB_multisample()					const { return m_bWGL_ARB_multisample;				 }
bool OpenGLExtensions::IsWGL_ATI_pixel_format_float()			const { return m_bWGL_ATI_pixel_format_float;		 }
bool OpenGLExtensions::IsWGL_NV_float_buffer()					const { return m_bWGL_NV_float_buffer;				 }
// EXT
bool OpenGLExtensions::IsGL_EXT_compiled_vertex_array()			const { return m_bGL_EXT_compiled_vertex_array;		 }
bool OpenGLExtensions::IsGL_EXT_draw_range_elements()			const { return m_bGL_EXT_draw_range_elements;		 }
bool OpenGLExtensions::IsGL_EXT_fog_coord()						const { return m_bGL_EXT_fog_coord;					 }
bool OpenGLExtensions::IsGL_EXT_secondary_color()				const { return m_bGL_EXT_secondary_color;			 }
bool OpenGLExtensions::IsGL_EXT_texture_compression_s3tc()		const { return m_bGL_EXT_texture_compression_s3tc;	 }
bool OpenGLExtensions::IsGL_EXT_texture_compression_latc()		const { return m_bGL_EXT_texture_compression_latc;	 }
bool OpenGLExtensions::IsGL_EXT_texture_lod_bias()				const { return m_bGL_EXT_texture_lod_bias;			 }
bool OpenGLExtensions::IsGL_EXT_texture_filter_anisotropic()	const { return m_bGL_EXT_texture_filter_anisotropic; }
bool OpenGLExtensions::IsGL_EXT_separate_specular_color()		const { return m_bGL_EXT_separate_specular_color;	 }
bool OpenGLExtensions::IsGL_EXT_texture_edge_clamp()			const { return m_bGL_EXT_texture_edge_clamp;		 }
bool OpenGLExtensions::IsGL_EXT_texture_rectangle()				const { return m_bGL_EXT_texture_rectangle;			 }
bool OpenGLExtensions::IsGL_EXT_texture3D()						const { return m_bGL_EXT_texture3D;					 }
bool OpenGLExtensions::IsGL_EXT_texture_cube_map()				const { return m_bGL_EXT_texture_cube_map;			 }
bool OpenGLExtensions::IsGL_EXT_stencil_wrap()					const { return m_bGL_EXT_stencil_wrap;				 }
bool OpenGLExtensions::IsGL_EXT_stencil_two_side()				const { return m_bGL_EXT_stencil_two_side;			 }
bool OpenGLExtensions::IsGL_EXT_packed_depth_stencil()			const { return m_bGL_EXT_packed_depth_stencil;		 }
bool OpenGLExtensions::IsGL_EXT_depth_bounds_test()				const { return m_bGL_EXT_depth_bounds_test;			 }
bool OpenGLExtensions::IsGL_EXT_framebuffer_object()			const { return m_bGL_EXT_framebuffer_object;		 }
bool OpenGLExtensions::IsGL_EXT_framebuffer_multisample()		const { return m_bGL_EXT_framebuffer_multisample;	 }
bool OpenGLExtensions::IsGL_EXT_framebuffer_blit()				const { return m_bGL_EXT_framebuffer_blit;			 }
bool OpenGLExtensions::IsGL_EXT_geometry_shader4()				const { return m_bGL_EXT_geometry_shader4;			 }
// ARB
bool OpenGLExtensions::IsGL_ARB_texture_float()					const { return m_bGL_ARB_texture_float;				 }
bool OpenGLExtensions::IsGL_ARB_color_buffer_float()			const { return m_bGL_ARB_color_buffer_float;		 }
bool OpenGLExtensions::IsGL_ARB_multitexture()					const { return m_bGL_ARB_multitexture;				 }
bool OpenGLExtensions::IsGL_ARB_vertex_buffer_object()			const { return m_bGL_ARB_vertex_buffer_object;		 }
bool OpenGLExtensions::IsGL_ARB_texture_border_clamp()			const { return m_bGL_ARB_texture_border_clamp;		 }
bool OpenGLExtensions::IsGL_ARB_texture_mirrored_repeat()		const { return m_bGL_ARB_texture_mirrored_repeat;	 }
bool OpenGLExtensions::IsGL_ARB_texture_cube_map()				const { return m_bGL_ARB_texture_cube_map;			 }
bool OpenGLExtensions::IsGL_ARB_texture_env_combine()			const { return m_bGL_ARB_texture_env_combine;		 }
bool OpenGLExtensions::IsGL_ARB_texture_env_dot3()				const { return m_bGL_ARB_texture_env_dot3;			 }
bool OpenGLExtensions::IsGL_ARB_occlusion_query()				const { return m_bGL_ARB_occlusion_query;			 }
bool OpenGLExtensions::IsGL_ARB_texture_compression()			const { return m_bGL_ARB_texture_compression;		 }
bool OpenGLExtensions::IsGL_ARB_depth_texture()					const { return m_bGL_ARB_depth_texture;				 }
bool OpenGLExtensions::IsGL_ARB_point_sprite()					const { return m_bGL_ARB_point_sprite;				 }
bool OpenGLExtensions::IsGL_ARB_point_parameters()				const { return m_bGL_ARB_point_parameters;			 }
bool OpenGLExtensions::IsGL_ARB_shading_language_100()			const { return m_bGL_ARB_shading_language_100;		 }
bool OpenGLExtensions::IsGL_ARB_vertex_program()				const { return m_bGL_ARB_vertex_program;			 }
bool OpenGLExtensions::IsGL_ARB_fragment_program()				const { return m_bGL_ARB_fragment_program;			 }
bool OpenGLExtensions::IsGL_ARB_draw_buffers()					const { return m_bGL_ARB_draw_buffers;				 }
bool OpenGLExtensions::IsGL_ARB_shader_objects()				const { return m_bGL_ARB_shader_objects;			 }
bool OpenGLExtensions::IsGL_ARB_vertex_shader()					const { return m_bGL_ARB_vertex_shader;				 }
bool OpenGLExtensions::IsGL_ARB_texture_rectangle()				const { return m_bGL_ARB_texture_rectangle;			 }
bool OpenGLExtensions::IsGL_ARB_multisample()					const { return m_bGL_ARB_multisample;				 }
// ATI
bool OpenGLExtensions::IsGL_ATI_separate_stencil()				const { return m_bGL_ATI_separate_stencil;			 }
bool OpenGLExtensions::IsGL_ATI_draw_buffers()					const { return m_bGL_ATI_draw_buffers;				 }
bool OpenGLExtensions::IsGL_ATI_texture_compression_3dc()		const { return m_bGL_ATI_texture_compression_3dc;	 }
// AMD
bool OpenGLExtensions::IsGL_AMD_vertex_shader_tessellator()		const { return m_bGL_AMD_vertex_shader_tessellator;	 }
// NV
bool OpenGLExtensions::IsGL_NV_texture_rectangle()				const { return m_bGL_NV_texture_rectangle;			 }
bool OpenGLExtensions::IsGL_NV_occlusion_query()				const { return m_bGL_NV_occlusion_query;			 }
// SGIS
bool OpenGLExtensions::IsGL_SGIS_generate_mipmap()				const { return m_bGL_SGIS_generate_mipmap;			 }
// HP
bool OpenGLExtensions::IsGL_HP_occlusion_test()					const { return m_bGL_HP_occlusion_test;				 }


///////////////////////////////////////////////////////////
// Misc
///////////////////////////////////////////////////////////
GLint OpenGLExtensions::GetGL_MAX_ELEMENTS_VERTICES_EXT() const	{ return m_nGL_MAX_ELEMENTS_VERTICES_EXT; }
GLint OpenGLExtensions::GetGL_MAX_ELEMENTS_INDICES_EXT() const	{ return m_nGL_MAX_ELEMENTS_INDICES_EXT; }


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Checks whether an extension is supported by the given hardware or not
*/
bool OpenGLExtensions::IsSupported(const char *pszExtension) const
{
	// Check whether or not the given extension string pointer is valid
	if (pszExtension) {
		// Is the extension supported by the hardware?
		if (CheckExtension(pszExtension)) {
			// Is the support active?
			// [TODO] Update this configuration related stuff?
			// String sConfig = Config::GetInstance()->GetVar("PLRendererOpenGL::RendererOpenGLExtensionConfig", pszExtension);
			String sConfig = "true";
			if (!sConfig.GetLength() || sConfig.GetBool()) {
				// Extension is supported!
				PL_LOG(Info, String::Format("Use extension '%s'", pszExtension))
				return true;
			}
		} else PL_LOG(Info, String::Format("Extension '%s' not found (nothing critical)", pszExtension))
	}

	// Extension isn't supported!
	return false;
}

/**
*  @brief
*    Checks whether an extension is supported by the given hardware or not
*/
bool OpenGLExtensions::CheckExtension(const char *pszExtension) const
{
	// Check whether or not the given extension string pointer is valid
	if (pszExtension) {
		// Under Windows all available extensions can be received via one additional function
		// but under Linux there are two additional functions for this
		int nLoopMax = 2;
		#ifdef LINUX
			nLoopMax = 3;
		#endif
		const char *pszExtensions = NULL;
		for (int i=0; i<nLoopMax; i++) {
			// Extension names should not have spaces
			const char *pszWhere = strchr(pszExtension, ' ');
			if (pszWhere || *pszExtension == '\0')
				return false; // Extension not found

			// Advanced extensions
			if (i) {
				#ifdef WIN32
					// WGL extensions
					if (!m_bWGL_ARB_extensions_string)
						return false; // Extension not found
					pszExtensions = (const char*)wglGetExtensionsStringARB(wglGetCurrentDC());
				#endif
				#ifdef LINUX
					// Get the Linux context implementation
					ContextLinux *pContextLinux = (ContextLinux*)m_pRenderer->GetContext();
					if (pContextLinux) {
						// Get the X server display connection
						Display *pDisplay = pContextLinux->GetDisplay();
						if (pDisplay) {
							if (i == 2)
								pszExtensions = (const char*)glXQueryExtensionsString(pDisplay, XDefaultScreen(pDisplay));
							else
								pszExtensions = (const char*)glXGetClientString(pDisplay, GLX_EXTENSIONS);
						}
					}
				#endif

			// Normal extensions
			} else {
				pszExtensions = (const char*)glGetString(GL_EXTENSIONS);
			}
			if (!pszExtensions)
			  return false; // Extension not found

			// It takes a bit of care to be fool-proof about parsing the
			// OpenGL extensions string. Don't be fooled by substrings,
			// etc:
			const char *pszStart = pszExtensions;
			pszWhere = strstr(pszStart, pszExtension);
			while (pszWhere)  {
				const char *pszTerminator = pszWhere + strlen(pszExtension);
				if (pszWhere == pszStart || *(pszWhere - 1) == ' ' || *pszTerminator == ' ' || *pszTerminator == '\0')
					return true; // Extension found
				pszStart = pszTerminator;
				pszWhere = strstr(pszStart, pszExtension);
			}
		}
	}

	// Extension not found
	return false;
}

/**
*  @brief
*    Resets the extensions
*/
void OpenGLExtensions::ResetExtensions()
{
	m_bInitialized = false;

	// Extensions
	// WGL (Windows only)
	m_bWGL_EXT_swap_control				 = false;
	m_bWGL_ARB_extensions_string		 = false;
	m_bWGL_ARB_pbuffer					 = false;
	m_bWGL_ARB_pixel_format				 = false;
	m_bWGL_ARB_render_texture			 = false;
	m_bWGL_ARB_make_current_read		 = false;
	m_bWGL_ARB_multisample				 = false;
	m_bWGL_ATI_pixel_format_float		 = false;
	m_bWGL_NV_float_buffer				 = false;
	// EXT
	m_bGL_EXT_compiled_vertex_array		 = false;
	m_bGL_EXT_draw_range_elements		 = false;
	m_bGL_EXT_fog_coord					 = false;
	m_bGL_EXT_secondary_color			 = false;
	m_bGL_EXT_texture_compression_s3tc   = false;
	m_bGL_EXT_texture_compression_latc	 = false;
	m_bGL_EXT_texture_lod_bias			 = false;
	m_bGL_EXT_texture_filter_anisotropic = false;
	m_bGL_EXT_separate_specular_color    = false;
	m_bGL_EXT_texture_edge_clamp		 = false;
	m_bGL_EXT_texture_rectangle			 = false;
	m_bGL_EXT_texture3D					 = false;
	m_bGL_EXT_stencil_wrap				 = false;
	m_bGL_EXT_stencil_two_side			 = false;
	m_bGL_EXT_packed_depth_stencil		 = false;
	m_bGL_EXT_depth_bounds_test			 = false;
	m_bGL_EXT_framebuffer_object		 = false;
	m_bGL_EXT_framebuffer_multisample	 = false;
	m_bGL_EXT_framebuffer_blit			 = false;
	m_bGL_EXT_geometry_shader4			 = false;
	// ARB
	m_bGL_ARB_multitexture				 = false;
	m_bGL_ARB_vertex_buffer_object		 = false;
	m_bGL_ARB_texture_border_clamp		 = false;
	m_bGL_ARB_texture_mirrored_repeat	 = false;
	m_bGL_ARB_texture_cube_map			 = false;
	m_bGL_ARB_texture_env_combine		 = false;
	m_bGL_ARB_texture_env_dot3			 = false;
	m_bGL_ARB_occlusion_query			 = false;
	m_bGL_ARB_texture_compression		 = false;
	m_bGL_ARB_depth_texture				 = false;
	m_bGL_ARB_point_sprite				 = false;
	m_bGL_ARB_point_parameters			 = false;
	m_bGL_ARB_shading_language_100		 = false;
	m_bGL_ARB_vertex_program			 = false;
	m_bGL_ARB_fragment_program			 = false;
	m_bGL_ARB_texture_rectangle			 = false;
	m_bGL_ARB_multisample				 = false;
	// ATI
	m_bGL_ATI_separate_stencil			 = false;
	m_bGL_ATI_draw_buffers				 = false;
	m_bGL_ATI_texture_compression_3dc	 = false;
	// AMD
	m_bGL_AMD_vertex_shader_tessellator  = false;
	// NV
	m_bGL_NV_texture_rectangle			 = false;
	m_bGL_NV_occlusion_query			 = false;
	// SGIS
	m_bGL_SGIS_generate_mipmap			 = false;
	// HP
	m_bGL_HP_occlusion_test				 = false;

	// Misc
	m_nGL_MAX_ELEMENTS_VERTICES_EXT = m_nGL_MAX_ELEMENTS_INDICES_EXT = 0;
}

/**
*  @brief
*    Shows general OpenGL information
*/
void OpenGLExtensions::ShowGeneralOpenGLInformation() const
{
	GLint nTemp;

	PL_LOG(Info, "General OpenGL information:")

	if (m_bGL_ARB_shading_language_100)
		PL_LOG(Info, String::Format("OpenGL shading language version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION_ARB) ? (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION_ARB) : "-"))

	if (m_bGL_ARB_multitexture) {
		glGetIntegerv(GL_MAX_TEXTURE_COORDS_ARB, &nTemp);
		PL_LOG(Info, String::Format("  GL_MAX_TEXTURE_COORDS_ARB: %d", nTemp))

		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS_ARB, &nTemp);
		PL_LOG(Info, String::Format("  GL_MAX_TEXTURE_IMAGE_UNITS_ARB: %d", nTemp))
	}

	if (glDrawRangeElementsEXT) {
		PL_LOG(Info, "glDrawRangeElementsEXT information:")
		glGetIntegerv(GL_MAX_ELEMENTS_VERTICES_EXT, &nTemp);
		PL_LOG(Info, String::Format("  Max elements vertices = %d", nTemp))
		glGetIntegerv(GL_MAX_ELEMENTS_INDICES_EXT, &nTemp);
		PL_LOG(Info, String::Format("  Max elements indices = %d", nTemp))
	}

	if (m_bGL_ARB_vertex_program || m_bGL_ARB_fragment_program) {
		PL_LOG(Info, "OpenGL vertex & fragment shader program information:")

		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS_ARB, &nTemp);
		PL_LOG(Info, String::Format("  GL_MAX_VERTEX_ATTRIBS_ARB: %d", nTemp))

		glGetIntegerv(GL_MAX_PROGRAM_MATRICES_ARB, &nTemp);
		PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_MATRICES_ARB: %d", nTemp))

		glGetIntegerv(GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB, &nTemp);
		PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB: %d", nTemp))
	}

	if (m_bGL_ARB_vertex_program) {
		PL_LOG(Info, "OpenGL vertex shader program information:")
		ShowOpenGLShaderProgramInformation(GL_VERTEX_PROGRAM_ARB);
	}

	if (m_bGL_ARB_fragment_program) {
		PL_LOG(Info, "OpenGL fragment shader program information:")

		glGetIntegerv(GL_MAX_TEXTURE_COORDS_ARB, &nTemp);
		PL_LOG(Info, String::Format("  GL_MAX_TEXTURE_COORDS_ARB: %d", nTemp))

		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS_ARB, &nTemp);
		PL_LOG(Info, String::Format("  GL_MAX_TEXTURE_IMAGE_UNITS_ARB: %d", nTemp))

		ShowOpenGLShaderProgramInformation(GL_FRAGMENT_PROGRAM_ARB);
	}

	if (m_bGL_ARB_draw_buffers) {
		PL_LOG(Info, "GL_ARB_draw_buffers information:")
		glGetIntegerv(GL_MAX_DRAW_BUFFERS_ARB, &nTemp);
		PL_LOG(Info, String::Format("  Max draw buffers = %d", nTemp))
		glGetIntegerv(GL_AUX_BUFFERS, &nTemp);
		PL_LOG(Info, String::Format("  Aux buffers = %d", nTemp))
	}

	if (m_bGL_ATI_draw_buffers) {
		PL_LOG(Info, "GL_ATI_draw_buffers information:")
		glGetIntegerv(GL_MAX_DRAW_BUFFERS_ATI, &nTemp);
		PL_LOG(Info, String::Format("  Max draw buffers = %d", nTemp))
		glGetIntegerv(GL_AUX_BUFFERS, &nTemp);
		PL_LOG(Info, String::Format("  Aux buffers = %d", nTemp))
	}

	if (m_bGL_EXT_framebuffer_object) {
		PL_LOG(Info, "GL_EXT_framebuffer_object information:")
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &nTemp);
		PL_LOG(Info, String::Format("  Max color attachments = %d", nTemp))
		glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE_EXT, &nTemp);
		PL_LOG(Info, String::Format("  Max renderbuffer size = %d", nTemp))
	}

	if (m_bGL_EXT_framebuffer_multisample) {
		PL_LOG(Info, "GL_EXT_framebuffer_multisample information:")
		glGetIntegerv(GL_MAX_SAMPLES_EXT, &nTemp);
		PL_LOG(Info, String::Format("  Max framebuffer samples = %d", nTemp))
	}

	if (m_bGL_ARB_texture_compression) {
		// Get the number of compressed formats
		GLint nNumOfCompressedFormats;
		glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB, &nNumOfCompressedFormats);
		if (nNumOfCompressedFormats) {
			// Get the compressed formats
			GLint *pCompressedFormat = new GLint[nNumOfCompressedFormats];
			glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS_ARB, pCompressedFormat);

			// Log output
			PL_LOG(Info, String("GL_ARB_texture_compression: Number of compressed formats: ") + nNumOfCompressedFormats)
			for (GLint i=0; i<nNumOfCompressedFormats; i++) {
				switch (pCompressedFormat[i]) {
					case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:  PL_LOG(Info, "  GL_COMPRESSED_RGB_S3TC_DXT1_EXT")					 break;
					case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT: PL_LOG(Info, "  GL_COMPRESSED_RGBA_S3TC_DXT1_EXT")					 break;
					case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT: PL_LOG(Info, "  GL_COMPRESSED_RGBA_S3TC_DXT3_EXT")					 break;
					case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT: PL_LOG(Info, "  GL_COMPRESSED_RGBA_S3TC_DXT5_EXT")					 break;
					default:							   PL_LOG(Info, String("  ") + pCompressedFormat[i] + " (unknown name)") break;
				}
			}

			// Cleanup
			delete [] pCompressedFormat;
		}
	}
}

/**
*  @brief
*    Shows OpenGL shader program information
*/
void OpenGLExtensions::ShowOpenGLShaderProgramInformation(uint32 nTarget) const
{
	GLint i;

// Vertex and fragment
	glGetProgramivARB(nTarget, GL_MAX_PROGRAM_INSTRUCTIONS_ARB, &i);
	PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_INSTRUCTIONS_ARB: %d", i))

	glGetProgramivARB(nTarget, GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB, &i);
	PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB: %d", i))

	glGetProgramivARB(nTarget, GL_MAX_PROGRAM_TEMPORARIES_ARB, &i);
	PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_TEMPORARIES_ARB: %d", i))

	glGetProgramivARB(nTarget, GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB, &i);
	PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB: %d", i))

	glGetProgramivARB(nTarget, GL_MAX_PROGRAM_PARAMETERS_ARB, &i);
	PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_PARAMETERS_ARB: %d", i))

	glGetProgramivARB(nTarget, GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB, &i);
	PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB: %d", i))

	glGetProgramivARB(nTarget, GL_MAX_PROGRAM_ATTRIBS_ARB, &i);
	PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_ATTRIBS_ARB: %d", i))

	glGetProgramivARB(nTarget, GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB, &i);
	PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB: %d", i))

	glGetProgramivARB(nTarget, GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB, &i);
	PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB: %d", i))

	glGetProgramivARB(nTarget, GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB, &i);
	PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB: %d", i))

	glGetProgramivARB(nTarget, GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB, &i);
	PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB: %d", i))

	glGetProgramivARB(nTarget, GL_MAX_PROGRAM_ENV_PARAMETERS_ARB, &i);
	PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_ENV_PARAMETERS_ARB: %d", i))

// Fragment only
	if (nTarget == GL_FRAGMENT_PROGRAM_ARB) {
		glGetProgramivARB(nTarget, GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB, &i);
		PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB: %d", i))

		glGetProgramivARB(nTarget, GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB, &i);
		PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB: %d", i))

		glGetProgramivARB(nTarget, GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB, &i);
		PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB: %d", i))

		glGetProgramivARB(nTarget, GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB, &i);
		PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB: %d", i))

		glGetProgramivARB(nTarget, GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB, &i);
		PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB: %d", i))

		glGetProgramivARB(nTarget, GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB, &i);
		PL_LOG(Info, String::Format("  GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB: %d", i))
	}
}

/**
*  @brief
*    Writes the extensions within a given extension string into the log
*/
void OpenGLExtensions::WriteExtensionStringIntoLog(const char *pszExtensions) const
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
				sExtension.Copy(pszExtensions, uint32(pszSpace-pszExtensions));
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
} // PLRendererOpenGL
