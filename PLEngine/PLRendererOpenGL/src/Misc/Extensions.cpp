/*********************************************************\
 *  File: Extensions.cpp                                 *
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
	PFNWGLGETEXTENSIONSSTRINGARBPROC	wglGetExtensionsStringARB	= nullptr;

	// WGL_EXT_swap_control
	PFNWGLSWAPINTERVALEXTPROC		wglSwapIntervalEXT		= nullptr;
	PFNWGLGETSWAPINTERVALEXTPROC	wglGetSwapIntervalEXT	= nullptr;

	// WGL_ARB_pbuffer
	PFNWGLCREATEPBUFFERARBPROC		wglCreatePbufferARB		= nullptr;
	PFNWGLGETPBUFFERDCARBPROC		wglGetPbufferDCARB		= nullptr;
	PFNWGLRELEASEPBUFFERDCARBPROC	wglReleasePbufferDCARB	= nullptr;
	PFNWGLDESTROYPBUFFERARBPROC		wglDestroyPbufferARB	= nullptr;
	PFNWGLQUERYPBUFFERARBPROC		wglQueryPbufferARB		= nullptr;

	// WGL_ARB_pixel_format
	PFNWGLGETPIXELFORMATATTRIBIVARBPROC	wglGetPixelFormatAttribivARB	= nullptr;
	PFNWGLGETPIXELFORMATATTRIBFVARBPROC	wglGetPixelFormatAttribfvARB	= nullptr;
	PFNWGLCHOOSEPIXELFORMATARBPROC		wglChoosePixelFormatARB			= nullptr;

	// WGL_ARB_render_texture
	PFNWGLBINDTEXIMAGEARBPROC		wglBindTexImageARB		= nullptr;
	PFNWGLRELEASETEXIMAGEARBPROC	wglReleaseTexImageARB	= nullptr;
	PFNWGLSETPBUFFERATTRIBARBPROC	wglSetPbufferAttribARB	= nullptr;

	// WGL_ARB_make_current_read
	PFNWGLMAKECONTEXTCURRENTARBPROC	wglMakeContextCurrentARB	= nullptr;
	PFNWGLGETCURRENTREADDCARBPROC	wglGetCurrentReadDCARB		= nullptr;
#endif


// GLX (Linux only)
#ifdef LINUX
	PFNGLXCREATEPBUFFERPROC		glXCreatePbuffer	= nullptr;
	PFNGLXDESTROYPBUFFERPROC	glXDestroyPbuffer	= nullptr;

	// GLX_SGI_swap_control
	PFNGLXSWAPINTERVALSGIPROC	glXSwapIntervalSGI	= nullptr;
#endif


// GL_EXT_compiled_vertex_array
PFNGLLOCKARRAYSEXTPROC		glLockArraysEXT		= nullptr;
PFNGLUNLOCKARRAYSEXTPROC	glUnlockArraysEXT	= nullptr;

// GL_EXT_draw_range_elements
PFNGLDRAWRANGEELEMENTSEXTPROC	glDrawRangeElementsEXT	= nullptr;

// GL_EXT_fog_coord
PFNGLFOGCOORDFEXTPROC		glFogCoordfEXT			= nullptr;
PFNGLFOGCOORDFVEXTPROC		glFogCoordfvEXT			= nullptr;
PFNGLFOGCOORDDEXTPROC		glFogCoorddEXT			= nullptr;
PFNGLFOGCOORDDVEXTPROC		glFogCoorddvEXT			= nullptr;
PFNGLFOGCOORDPOINTEREXTPROC	glFogCoordPointerEXT	= nullptr;

// GL_EXT_secondary_color
PFNGLSECONDARYCOLOR3BEXTPROC		glSecondaryColor3bEXT		= nullptr;
PFNGLSECONDARYCOLOR3BVEXTPROC		glSecondaryColor3bvEXT		= nullptr;
PFNGLSECONDARYCOLOR3DEXTPROC		glSecondaryColor3dEXT 		= nullptr;
PFNGLSECONDARYCOLOR3DVEXTPROC		glSecondaryColor3dvEXT		= nullptr;
PFNGLSECONDARYCOLOR3FEXTPROC		glSecondaryColor3fEXT		= nullptr;
PFNGLSECONDARYCOLOR3FVEXTPROC		glSecondaryColor3fvEXT		= nullptr;
PFNGLSECONDARYCOLOR3IEXTPROC		glSecondaryColor3iEXT		= nullptr;
PFNGLSECONDARYCOLOR3IVEXTPROC		glSecondaryColor3ivEXT		= nullptr;
PFNGLSECONDARYCOLOR3SEXTPROC		glSecondaryColor3sEXT		= nullptr;
PFNGLSECONDARYCOLOR3SVEXTPROC		glSecondaryColor3svEXT		= nullptr;
PFNGLSECONDARYCOLOR3UBEXTPROC		glSecondaryColor3ubEXT		= nullptr;
PFNGLSECONDARYCOLOR3UBVEXTPROC		glSecondaryColor3ubvEXT		= nullptr;
PFNGLSECONDARYCOLOR3UIEXTPROC		glSecondaryColor3uiEXT		= nullptr;
PFNGLSECONDARYCOLOR3UIVEXTPROC		glSecondaryColor3uivEXT		= nullptr;
PFNGLSECONDARYCOLOR3USEXTPROC		glSecondaryColor3usEXT		= nullptr;
PFNGLSECONDARYCOLOR3USVEXTPROC		glSecondaryColor3usvEXT		= nullptr;
PFNGLSECONDARYCOLORPOINTEREXTPROC	glSecondaryColorPointerEXT	= nullptr;

// GL_EXT_texture3D
PFNGLTEXIMAGE3DEXTPROC		glTexImage3DEXT		= nullptr;
PFNGLTEXSUBIMAGE3DEXTPROC	glTexSubImage3DEXT	= nullptr;

// GL_EXT_stencil_two_side
PFNGLACTIVESTENCILFACEEXTPROC	glActiveStencilFaceEXT	= nullptr;

// GL_EXT_depth_bounds_test
PFNGLDEPTHBOUNDSEXTPROC	glDepthBoundsEXT	= nullptr;

// GL_EXT_framebuffer_object
PFNGLISRENDERBUFFEREXTPROC						glIsRenderbufferEXT							= nullptr;
PFNGLBINDRENDERBUFFEREXTPROC					glBindRenderbufferEXT						= nullptr;
PFNGLDELETERENDERBUFFERSEXTPROC					glDeleteRenderbuffersEXT					= nullptr;
PFNGLGENRENDERBUFFERSEXTPROC					glGenRenderbuffersEXT						= nullptr;
PFNGLRENDERBUFFERSTORAGEEXTPROC					glRenderbufferStorageEXT					= nullptr;
PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC			glGetRenderbufferParameterivEXT				= nullptr;
PFNGLISFRAMEBUFFEREXTPROC						glIsFramebufferEXT							= nullptr;
PFNGLBINDFRAMEBUFFEREXTPROC						glBindFramebufferEXT						= nullptr;
PFNGLDELETEFRAMEBUFFERSEXTPROC					glDeleteFramebuffersEXT						= nullptr;
PFNGLGENFRAMEBUFFERSEXTPROC						glGenFramebuffersEXT						= nullptr;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC				glCheckFramebufferStatusEXT					= nullptr;
PFNGLFRAMEBUFFERTEXTURE1DEXTPROC				glFramebufferTexture1DEXT					= nullptr;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC				glFramebufferTexture2DEXT					= nullptr;
PFNGLFRAMEBUFFERTEXTURE3DEXTPROC				glFramebufferTexture3DEXT					= nullptr;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC				glFramebufferRenderbufferEXT				= nullptr;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC	glGetFramebufferAttachmentParameterivEXT	= nullptr;
PFNGLGENERATEMIPMAPEXTPROC						glGenerateMipmapEXT							= nullptr;

// GL_EXT_framebuffer_multisample
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC		glRenderbufferStorageMultisampleEXT			= nullptr;

// GL_EXT_framebuffer_blit
PFNGLBLITFRAMEBUFFEREXTPROC						glBlitFramebufferEXT						= nullptr;

// GL_EXT_geometry_shader4
PFNGLPROGRAMPARAMETERIEXTPROC					glProgramParameteriEXT						= nullptr;

// GL_EXT_transform_feedback
PFNGLBEGINTRANSFORMFEEDBACKEXTPROC				glBeginTransformFeedbackEXT					= nullptr;
PFNGLENDTRANSFORMFEEDBACKEXTPROC				glEndTransformFeedbackEXT					= nullptr;
PFNGLBINDBUFFERRANGEEXTPROC						glBindBufferRangeEXT						= nullptr;
PFNGLBINDBUFFEROFFSETEXTPROC					glBindBufferOffsetEXT						= nullptr;
PFNGLBINDBUFFERBASEEXTPROC						glBindBufferBaseEXT							= nullptr;
PFNGLTRANSFORMFEEDBACKVARYINGSEXTPROC			glTransformFeedbackVaryingsEXT				= nullptr;
PFNGLGETTRANSFORMFEEDBACKVARYINGEXTPROC			glGetTransformFeedbackVaryingEXT			= nullptr;

// GL_ARB_color_buffer_float
PFNGLCLAMPCOLORARBPROC			glClampColorARB				= nullptr;

// GL_ARB_multitexture
PFNGLACTIVETEXTUREARBPROC		glActiveTextureARB			= nullptr;
PFNGLCLIENTACTIVETEXTUREARBPROC	glClientActiveTextureARB	= nullptr;
PFNGLMULTITEXCOORD1DARBPROC		glMultiTexCoord1dARB		= nullptr;
PFNGLMULTITEXCOORD1DVARBPROC	glMultiTexCoord1dvARB		= nullptr;
PFNGLMULTITEXCOORD1FARBPROC		glMultiTexCoord1fARB		= nullptr;
PFNGLMULTITEXCOORD1FVARBPROC	glMultiTexCoord1fvARB		= nullptr;
PFNGLMULTITEXCOORD1IARBPROC		glMultiTexCoord1iARB		= nullptr;
PFNGLMULTITEXCOORD1IVARBPROC	glMultiTexCoord1ivARB		= nullptr;
PFNGLMULTITEXCOORD1SARBPROC		glMultiTexCoord1sARB		= nullptr;
PFNGLMULTITEXCOORD1SVARBPROC	glMultiTexCoord1svARB		= nullptr;
PFNGLMULTITEXCOORD2DARBPROC		glMultiTexCoord2dARB		= nullptr;
PFNGLMULTITEXCOORD2DVARBPROC	glMultiTexCoord2dvARB		= nullptr;
PFNGLMULTITEXCOORD2FARBPROC		glMultiTexCoord2fARB		= nullptr;
PFNGLMULTITEXCOORD2FVARBPROC	glMultiTexCoord2fvARB		= nullptr;
PFNGLMULTITEXCOORD2IARBPROC		glMultiTexCoord2iARB		= nullptr;
PFNGLMULTITEXCOORD2IVARBPROC	glMultiTexCoord2ivARB		= nullptr;
PFNGLMULTITEXCOORD2SARBPROC		glMultiTexCoord2sARB		= nullptr;
PFNGLMULTITEXCOORD2SVARBPROC	glMultiTexCoord2svARB		= nullptr;
PFNGLMULTITEXCOORD3DARBPROC		glMultiTexCoord3dARB		= nullptr;
PFNGLMULTITEXCOORD3DVARBPROC	glMultiTexCoord3dvARB		= nullptr;
PFNGLMULTITEXCOORD3FARBPROC		glMultiTexCoord3fARB		= nullptr;
PFNGLMULTITEXCOORD3FVARBPROC	glMultiTexCoord3fvARB		= nullptr;
PFNGLMULTITEXCOORD3IARBPROC		glMultiTexCoord3iARB		= nullptr;
PFNGLMULTITEXCOORD3IVARBPROC	glMultiTexCoord3ivARB		= nullptr;
PFNGLMULTITEXCOORD3SARBPROC		glMultiTexCoord3sARB		= nullptr;
PFNGLMULTITEXCOORD3SVARBPROC	glMultiTexCoord3svARB		= nullptr;
PFNGLMULTITEXCOORD4DARBPROC		glMultiTexCoord4dARB		= nullptr;
PFNGLMULTITEXCOORD4DVARBPROC	glMultiTexCoord4dvARB		= nullptr;
PFNGLMULTITEXCOORD4FARBPROC		glMultiTexCoord4fARB		= nullptr;
PFNGLMULTITEXCOORD4FVARBPROC	glMultiTexCoord4fvARB		= nullptr;
PFNGLMULTITEXCOORD4IARBPROC		glMultiTexCoord4iARB		= nullptr;
PFNGLMULTITEXCOORD4IVARBPROC	glMultiTexCoord4ivARB		= nullptr;
PFNGLMULTITEXCOORD4SARBPROC		glMultiTexCoord4sARB		= nullptr;
PFNGLMULTITEXCOORD4SVARBPROC	glMultiTexCoord4svARB		= nullptr;

// GL_ARB_vertex_buffer_object 
PFNGLBINDBUFFERARBPROC				glBindBufferARB				= nullptr;
PFNGLDELETEBUFFERSARBPROC			glDeleteBuffersARB			= nullptr;
PFNGLGENBUFFERSARBPROC				glGenBuffersARB				= nullptr;
PFNGLBUFFERDATAARBPROC				glBufferDataARB				= nullptr;
PFNGLBUFFERSUBDATAARBPROC			glBufferSubDataARB			= nullptr;
PFNGLGETBUFFERSUBDATAARBPROC		glGetBufferSubDataARB		= nullptr;
PFNGLMAPBUFFERARBPROC				glMapBufferARB				= nullptr;
PFNGLUNMAPBUFFERARBPROC				glUnmapBufferARB			= nullptr;
PFNGLGETBUFFERPARAMETERIVARBPROC	glGetBufferParameterivARB	= nullptr;
PFNGLGETBUFFERPOINTERVARBPROC		glGetBufferPointervARB		= nullptr;

// GL_ARB_occlusion_query
PFNGLGENQUERIESARBPROC			glGenQueriesARB			= nullptr;
PFNGLDELETEQUERIESARBPROC		glDeleteQueriesARB		= nullptr;
PFNGLISQUERYARBPROC				glIsQueryARB			= nullptr;
PFNGLBEGINQUERYARBPROC			glBeginQueryARB			= nullptr;
PFNGLENDQUERYARBPROC			glEndQueryARB			= nullptr;
PFNGLGETQUERYIVARBPROC			glGetQueryivARB			= nullptr;
PFNGLGETQUERYOBJECTIVARBPROC	glGetQueryObjectivARB	= nullptr;
PFNGLGETQUERYOBJECTUIVARBPROC	glGetQueryObjectuivARB	= nullptr;

// GL_ARB_texture_compression
PFNGLCOMPRESSEDTEXIMAGE3DARBPROC	glCompressedTexImage3DARB		= nullptr;
PFNGLCOMPRESSEDTEXIMAGE2DARBPROC	glCompressedTexImage2DARB		= nullptr;
PFNGLCOMPRESSEDTEXIMAGE1DARBPROC	glCompressedTexImage1DARB		= nullptr;
PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC	glCompressedTexSubImage3DARB	= nullptr;
PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC	glCompressedTexSubImage2DARB	= nullptr;
PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC	glCompressedTexSubImage1DARB	= nullptr;
PFNGLGETCOMPRESSEDTEXIMAGEARBPROC	glGetCompressedTexImageARB		= nullptr;

// GL_ARB_point_parameters
PFNGLPOINTPARAMETERFARBPROC		glPointParameterfARB	= nullptr;
PFNGLPOINTPARAMETERFVARBPROC	glPointParameterfvARB	= nullptr;

// GL_ARB_vertex_program
PFNGLVERTEXATTRIBPOINTERARBPROC			glVertexAttribPointerARB		= nullptr;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC		glEnableVertexAttribArrayARB	= nullptr;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC	glDisableVertexAttribArrayARB	= nullptr;
PFNGLGETPROGRAMIVARBPROC				glGetProgramivARB				= nullptr;

// GL_ARB_draw_buffers
PFNGLDRAWBUFFERSARBPROC	glDrawBuffersARB	= nullptr;

// GL_ARB_shader_objects
PFNGLDELETEOBJECTARBPROC			glDeleteObjectARB			= nullptr;
PFNGLGETHANDLEARBPROC				glGetHandleARB				= nullptr;
PFNGLDETACHOBJECTARBPROC			glDetachObjectARB			= nullptr;
PFNGLCREATESHADEROBJECTARBPROC		glCreateShaderObjectARB		= nullptr;
PFNGLSHADERSOURCEARBPROC			glShaderSourceARB			= nullptr;
PFNGLCOMPILESHADERARBPROC			glCompileShaderARB			= nullptr;
PFNGLCREATEPROGRAMOBJECTARBPROC		glCreateProgramObjectARB	= nullptr;
PFNGLATTACHOBJECTARBPROC			glAttachObjectARB			= nullptr;
PFNGLLINKPROGRAMARBPROC				glLinkProgramARB			= nullptr;
PFNGLUSEPROGRAMOBJECTARBPROC		glUseProgramObjectARB		= nullptr;
PFNGLVALIDATEPROGRAMARBPROC			glValidateProgramARB		= nullptr;
PFNGLUNIFORM1FARBPROC				glUniform1fARB				= nullptr;
PFNGLUNIFORM2FARBPROC				glUniform2fARB				= nullptr;
PFNGLUNIFORM3FARBPROC				glUniform3fARB				= nullptr;
PFNGLUNIFORM4FARBPROC				glUniform4fARB				= nullptr;
PFNGLUNIFORM1IARBPROC				glUniform1iARB				= nullptr;
PFNGLUNIFORM2IARBPROC				glUniform2iARB				= nullptr;
PFNGLUNIFORM3IARBPROC				glUniform3iARB				= nullptr;
PFNGLUNIFORM4IARBPROC				glUniform4iARB				= nullptr;
PFNGLUNIFORM1FVARBPROC				glUniform1fvARB				= nullptr;
PFNGLUNIFORM2FVARBPROC				glUniform2fvARB				= nullptr;
PFNGLUNIFORM3FVARBPROC				glUniform3fvARB				= nullptr;
PFNGLUNIFORM4FVARBPROC				glUniform4fvARB				= nullptr;
PFNGLUNIFORM1IVARBPROC				glUniform1ivARB				= nullptr;
PFNGLUNIFORM2IVARBPROC				glUniform2ivARB				= nullptr;
PFNGLUNIFORM3IVARBPROC				glUniform3ivARB				= nullptr;
PFNGLUNIFORM4IVARBPROC				glUniform4ivARB				= nullptr;
PFNGLUNIFORMMATRIX2FVARBPROC		glUniformMatrix2fvARB		= nullptr;
PFNGLUNIFORMMATRIX3FVARBPROC		glUniformMatrix3fvARB		= nullptr;
PFNGLUNIFORMMATRIX4FVARBPROC		glUniformMatrix4fvARB		= nullptr;
PFNGLGETOBJECTPARAMETERFVARBPROC	glGetObjectParameterfvARB	= nullptr;
PFNGLGETOBJECTPARAMETERIVARBPROC	glGetObjectParameterivARB	= nullptr;
PFNGLGETINFOLOGARBPROC				glGetInfoLogARB				= nullptr;
PFNGLGETATTACHEDOBJECTSARBPROC		glGetAttachedObjectsARB		= nullptr;
PFNGLGETUNIFORMLOCATIONARBPROC		glGetUniformLocationARB		= nullptr;
PFNGLGETACTIVEUNIFORMARBPROC		glGetActiveUniformARB		= nullptr;
PFNGLGETUNIFORMFVARBPROC			glGetUniformfvARB			= nullptr;
PFNGLGETUNIFORMIVARBPROC			glGetUniformivARB			= nullptr;
PFNGLGETSHADERSOURCEARBPROC			glGetShaderSourceARB		= nullptr;

// GL_ARB_vertex_shader
PFNGLBINDATTRIBLOCATIONARBPROC	glBindAttribLocationARB	= nullptr;
PFNGLGETACTIVEATTRIBARBPROC		glGetActiveAttribARB	= nullptr;
PFNGLGETATTRIBLOCATIONARBPROC	glGetAttribLocationARB	= nullptr;

// GL_ARB_get_program_binary
PFNGLGETPROGRAMBINARYPROC	glGetProgramBinary	= nullptr;
PFNGLPROGRAMBINARYPROC		glProgramBinary		= nullptr;
PFNGLPROGRAMPARAMETERIPROC	glProgramParameteri	= nullptr;

// GL_ARB_uniform_buffer_object
PFNGLGETUNIFORMINDICESPROC			glGetUniformIndices			= nullptr;
PFNGLGETACTIVEUNIFORMSIVPROC		glGetActiveUniformsiv		= nullptr;
PFNGLGETACTIVEUNIFORMNAMEPROC		glGetActiveUniformName		= nullptr;
PFNGLGETUNIFORMBLOCKINDEXPROC		glGetUniformBlockIndex		= nullptr;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC	glGetActiveUniformBlockiv	= nullptr;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC	glGetActiveUniformBlockName	= nullptr;
PFNGLUNIFORMBLOCKBINDINGPROC		glUniformBlockBinding		= nullptr;

// GL_NV_occlusion_query
PFNGLGENOCCLUSIONQUERIESNVPROC		glGenOcclusionQueriesNV		= nullptr;
PFNGLDELETEOCCLUSIONQUERIESNVPROC	glDeleteOcclusionQueriesNV	= nullptr;
PFNGLISOCCLUSIONQUERYNVPROC			glIsOcclusionQueryNV		= nullptr;
PFNGLBEGINOCCLUSIONQUERYNVPROC		glBeginOcclusionQueryNV		= nullptr;
PFNGLENDOCCLUSIONQUERYNVPROC		glEndOcclusionQueryNV		= nullptr;
PFNGLGETOCCLUSIONQUERYIVNVPROC		glGetOcclusionQueryivNV		= nullptr;
PFNGLGETOCCLUSIONQUERYUIVNVPROC		glGetOcclusionQueryuivNV	= nullptr;

// GL_ATI_separate_stencil
PFNGLSTENCILOPSEPARATEATIPROC	glStencilOpSeparateATI		= nullptr;
PFNGLSTENCILFUNCSEPARATEATIPROC	glStencilFuncSeparateATI	= nullptr;

// GL_ATI_draw_buffers
PFNGLDRAWBUFFERSATIPROC	glDrawBuffersATI	= nullptr;

// GL_AMD_vertex_shader_tessellator
PFNGLTESSELLATIONFACTORAMDPROC	glTessellationFactorAMD	= nullptr;
PFNGLTESSELLATIONMODEAMDPROC	glTessellationModeAMD	= nullptr;


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
// GLX (Linux only)
bool OpenGLExtensions::IsGLX_SGI_swap_control()					const { return m_bGLX_SGI_swap_control;				 }
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
bool OpenGLExtensions::IsGL_EXT_transform_feedback()			const { return m_bGL_EXT_transform_feedback;		 }
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
bool OpenGLExtensions::IsGL_ARB_get_program_binary()			const { return m_bGL_ARB_get_program_binary;		 }
bool OpenGLExtensions::IsGL_ARB_texture_rectangle()				const { return m_bGL_ARB_texture_rectangle;			 }
bool OpenGLExtensions::IsGL_ARB_multisample()					const { return m_bGL_ARB_multisample;				 }
bool OpenGLExtensions::IsGL_ARB_uniform_buffer_object()			const { return m_bGL_ARB_uniform_buffer_object;		 }
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
				PL_LOG(Info, String("Use extension: ") + pszExtension)
				return true;
			}
		} else {
			PL_LOG(Info, String("Extension '") + pszExtension + "' not found (nothing critical)")
		}
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
		const char *pszExtensions = nullptr;
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
					pszExtensions = static_cast<const char*>(wglGetExtensionsStringARB(wglGetCurrentDC()));
				#endif
				#ifdef LINUX
					// Get the Linux context implementation
					ContextLinux *pContextLinux = static_cast<ContextLinux*>(m_pRenderer->GetContext());
					if (pContextLinux) {
						// Get the X server display connection
						Display *pDisplay = pContextLinux->GetDisplay();
						if (pDisplay) {
							if (i == 2)
								pszExtensions = static_cast<const char*>(glXQueryExtensionsString(pDisplay, XDefaultScreen(pDisplay)));
							else
								pszExtensions = static_cast<const char*>(glXGetClientString(pDisplay, GLX_EXTENSIONS));
						}
					}
				#endif

			// Normal extensions
			} else {
				pszExtensions = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
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
	m_bWGL_EXT_swap_control					= false;
	m_bWGL_ARB_extensions_string			= false;
	m_bWGL_ARB_pbuffer						= false;
	m_bWGL_ARB_pixel_format					= false;
	m_bWGL_ARB_render_texture				= false;
	m_bWGL_ARB_make_current_read			= false;
	m_bWGL_ARB_multisample					= false;
	m_bWGL_ATI_pixel_format_float			= false;
	m_bWGL_NV_float_buffer					= false;
	// GLX (Linux only)
	m_bGLX_SGI_swap_control					= false;
	// EXT
	m_bGL_EXT_compiled_vertex_array			= false;
	m_bGL_EXT_draw_range_elements			= false;
	m_bGL_EXT_fog_coord						= false;
	m_bGL_EXT_secondary_color				= false;
	m_bGL_EXT_texture_compression_s3tc		= false;
	m_bGL_EXT_texture_compression_latc		= false;
	m_bGL_EXT_texture_lod_bias				= false;
	m_bGL_EXT_texture_filter_anisotropic	= false;
	m_bGL_EXT_separate_specular_color		= false;
	m_bGL_EXT_texture_edge_clamp			= false;
	m_bGL_EXT_texture_rectangle				= false;
	m_bGL_EXT_texture3D						= false;
	m_bGL_EXT_texture_cube_map				= false;
	m_bGL_EXT_stencil_wrap					= false;
	m_bGL_EXT_stencil_two_side				= false;
	m_bGL_EXT_packed_depth_stencil			= false;
	m_bGL_EXT_depth_bounds_test				= false;
	m_bGL_EXT_framebuffer_object			= false;
	m_bGL_EXT_framebuffer_multisample		= false;
	m_bGL_EXT_framebuffer_blit				= false;
	m_bGL_EXT_geometry_shader4				= false;
	m_bGL_EXT_transform_feedback			= false;
	// ARB
	m_bGL_ARB_texture_float					= false;
	m_bGL_ARB_color_buffer_float			= false;
	m_bGL_ARB_multitexture					= false;
	m_bGL_ARB_vertex_buffer_object			= false;
	m_bGL_ARB_texture_border_clamp			= false;
	m_bGL_ARB_texture_mirrored_repeat		= false;
	m_bGL_ARB_texture_cube_map				= false;
	m_bGL_ARB_texture_env_combine			= false;
	m_bGL_ARB_texture_env_dot3				= false;
	m_bGL_ARB_occlusion_query				= false;
	m_bGL_ARB_texture_compression			= false;
	m_bGL_ARB_depth_texture					= false;
	m_bGL_ARB_point_sprite					= false;
	m_bGL_ARB_point_parameters				= false;
	m_bGL_ARB_shading_language_100			= false;
	m_bGL_ARB_vertex_program				= false;
	m_bGL_ARB_fragment_program				= false;
	m_bGL_ARB_draw_buffers					= false;
	m_bGL_ARB_shader_objects				= false;
	m_bGL_ARB_vertex_shader					= false;
	m_bGL_ARB_get_program_binary			= false;
	m_bGL_ARB_texture_rectangle				= false;
	m_bGL_ARB_multisample					= false;
	m_bGL_ARB_uniform_buffer_object			= false;
	// ATI
	m_bGL_ATI_separate_stencil				= false;
	m_bGL_ATI_draw_buffers					= false;
	m_bGL_ATI_texture_compression_3dc		= false;
	// AMD
	m_bGL_AMD_vertex_shader_tessellator		= false;
	// NV
	m_bGL_NV_texture_rectangle				= false;
	m_bGL_NV_occlusion_query				= false;
	// SGIS
	m_bGL_SGIS_generate_mipmap				= false;
	// HP
	m_bGL_HP_occlusion_test					= false;
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
		PL_LOG(Info, String::Format("OpenGL shading language version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION_ARB) ? reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION_ARB)) : "-"))

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

	if (m_bGL_ARB_uniform_buffer_object) {
		PL_LOG(Info, "GL_ARB_uniform_buffer_object information:")
		glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &nTemp);
		PL_LOG(Info, String::Format("  Maximum number of vertex uniform buffers per program = %d", nTemp))
		glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &nTemp);
		PL_LOG(Info, String::Format("  Maximum number of fragment uniform buffers per program = %d", nTemp))
		glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_BLOCKS, &nTemp);
		PL_LOG(Info, String::Format("  Maximum number of geometry uniform buffers per program = %d", nTemp))
		glGetIntegerv(GL_MAX_COMBINED_UNIFORM_BLOCKS, &nTemp);
		PL_LOG(Info, String::Format("  Maximum number of uniform buffers per program = %d", nTemp))
		glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &nTemp);
		PL_LOG(Info, String::Format("  Maximum number of uniform buffer binding points on the context = %d", nTemp))
		glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &nTemp);
		PL_LOG(Info, String::Format("  Max size in basic machine units of a uniform block = %d", nTemp))
		glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &nTemp);
		PL_LOG(Info, String::Format("  Number of words for vertex shader uniform variables in default uniform block = %d", nTemp))
		glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &nTemp);
		PL_LOG(Info, String::Format("  Number of words for fragment shader uniform variables in default uniform block = %d", nTemp))
		glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, &nTemp);
		PL_LOG(Info, String::Format("  Number of words for geometry shader uniform variables in default uniform block = %d", nTemp))
		glGetIntegerv(GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS, &nTemp);
		PL_LOG(Info, String::Format("  Number of words for vertex shader uniform variables in all uniform blocks (including default) = %d", nTemp))
		glGetIntegerv(GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS, &nTemp);
		PL_LOG(Info, String::Format("  Number of words for fragment shader uniform variables in all uniform blocks (including default) = %d", nTemp))
		glGetIntegerv(GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS, &nTemp);
		PL_LOG(Info, String::Format("  Number of words for geometry shader uniform variables in all uniform blocks (including default) = %d", nTemp))
		glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &nTemp);
		PL_LOG(Info, String::Format("  Minimum required alignment for uniform buffer sizes and offsets = %d", nTemp))
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
} // PLRendererOpenGL
