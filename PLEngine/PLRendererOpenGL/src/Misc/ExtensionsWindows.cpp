/*********************************************************\
 *  File: ExtensionsWindows.cpp                          *
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initialize the supported extensions
*/
bool OpenGLExtensions::Init()
{
	// Should the extensions be used?
	// [TODO] Update this configuration related stuff?
//	if (!Config::GetInstance()->GetVar("PLScene::RendererConfig", "UseExtensions").GetBool()) {
	if (false) {
		ResetExtensions();
		m_bInitialized = true;
		PL_LOG(Info, "Use no hardware supported extensions")

		// Done
		return true;
	} else m_bInitialized = true;

	{ // Print a list af all available extensions into the log
		PL_LOG(Info, "Extensions info:")
		WriteExtensionStringIntoLog((const char*)glGetString(GL_EXTENSIONS));

		// WGL_ARB_extensions_string
		wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC) wglGetProcAddress("wglGetExtensionsStringARB");
		m_bWGL_ARB_extensions_string = wglGetExtensionsStringARB != nullptr;

		if (m_bWGL_ARB_extensions_string)
			WriteExtensionStringIntoLog((const char*)wglGetExtensionsStringARB(wglGetCurrentDC()));
	}


// WGL
	// WGL_EXT_swap_control
	if (IsSupported("WGL_EXT_swap_control")) {
		wglSwapIntervalEXT	  = (PFNWGLSWAPINTERVALEXTPROC)	  wglGetProcAddress("wglSwapIntervalEXT");
		wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wglGetProcAddress("wglGetSwapIntervalEXT");
		if (!wglSwapIntervalEXT || !wglGetSwapIntervalEXT) {
			PL_LOG(Info, "Couldn't use extension 'WGL_EXT_swap_control'!")
			m_bWGL_EXT_swap_control = false;
		} else m_bWGL_EXT_swap_control = true;
	} else m_bWGL_EXT_swap_control = false;

	// WGL_ARB_pbuffer
	if (IsSupported("WGL_ARB_pbuffer")) {
		wglCreatePbufferARB	     = (PFNWGLCREATEPBUFFERARBPROC)		 wglGetProcAddress("wglCreatePbufferARB");
		wglGetPbufferDCARB	     = (PFNWGLGETPBUFFERDCARBPROC)		 wglGetProcAddress("wglGetPbufferDCARB");
		wglReleasePbufferDCARB   = (PFNWGLRELEASEPBUFFERDCARBPROC)	 wglGetProcAddress("wglReleasePbufferDCARB");
		wglDestroyPbufferARB     = (PFNWGLDESTROYPBUFFERARBPROC)	 wglGetProcAddress("wglDestroyPbufferARB");
		wglQueryPbufferARB	     = (PFNWGLQUERYPBUFFERARBPROC)		 wglGetProcAddress("wglQueryPbufferARB");
		if (!wglCreatePbufferARB || !wglGetPbufferDCARB || !wglReleasePbufferDCARB || !wglDestroyPbufferARB ||
			!wglQueryPbufferARB) {
			PL_LOG(Info, "Couldn't use extension 'WGL_ARB_pbuffer'!")
			m_bWGL_ARB_pbuffer = false;
		} else m_bWGL_ARB_pbuffer = true;
	} else m_bWGL_ARB_pbuffer = false;

	// WGL_ARB_pixel_format
	if (IsSupported("WGL_ARB_pixel_format")) {
		wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC) wglGetProcAddress("wglGetPixelFormatAttribivARB");
		wglGetPixelFormatAttribfvARB = (PFNWGLGETPIXELFORMATATTRIBFVARBPROC) wglGetProcAddress("wglGetPixelFormatAttribfvARB");
		wglChoosePixelFormatARB		 = (PFNWGLCHOOSEPIXELFORMATARBPROC)		 wglGetProcAddress("wglChoosePixelFormatARB");
		if (!wglGetPixelFormatAttribivARB || !wglGetPixelFormatAttribfvARB || !wglChoosePixelFormatARB) {
			PL_LOG(Info, "Couldn't use extension 'WGL_ARB_pixel_format'!")
			m_bWGL_ARB_pixel_format = false;
		} else m_bWGL_ARB_pixel_format = true;
	} else m_bWGL_ARB_pixel_format = false;

	// WGL_ARB_render_texture
	if (IsSupported("WGL_ARB_render_texture")) {
		wglBindTexImageARB	   = (PFNWGLBINDTEXIMAGEARBPROC)	 wglGetProcAddress("wglBindTexImageARB");
		wglReleaseTexImageARB  = (PFNWGLRELEASETEXIMAGEARBPROC)  wglGetProcAddress("wglReleaseTexImageARB");
		wglSetPbufferAttribARB = (PFNWGLSETPBUFFERATTRIBARBPROC) wglGetProcAddress("wglSetPbufferAttribARB");
		if (!wglBindTexImageARB || !wglReleaseTexImageARB || !wglSetPbufferAttribARB) {
			PL_LOG(Info, "Couldn't use extension 'WGL_ARB_render_texture'!")
			m_bWGL_ARB_render_texture = false;
		} else m_bWGL_ARB_render_texture = true;
	} else m_bWGL_ARB_render_texture = false;

	// WGL_ARB_make_current_read
	if (IsSupported("WGL_ARB_make_current_read")) {
		wglMakeContextCurrentARB = (PFNWGLMAKECONTEXTCURRENTARBPROC) wglGetProcAddress("wglMakeContextCurrentARB");
		wglGetCurrentReadDCARB   = (PFNWGLGETCURRENTREADDCARBPROC)   wglGetProcAddress("wglGetCurrentReadDCARB");
		if (!wglMakeContextCurrentARB || !wglGetCurrentReadDCARB) {
			PL_LOG(Info, "Couldn't use extension 'WGL_ARB_make_current_read'!")
			m_bWGL_ARB_make_current_read = false;
		} else m_bWGL_ARB_make_current_read = true;
	} else m_bWGL_ARB_make_current_read = false;

	// WGL_ARB_multisample
	m_bWGL_ARB_multisample = IsSupported("WGL_ARB_multisample");

	// WGL_ATI_pixel_format_float
	m_bWGL_ATI_pixel_format_float = IsSupported("WGL_ATI_pixel_format_float");

	// WGL_NV_float_buffer
	m_bWGL_NV_float_buffer = IsSupported("WGL_NV_float_buffer");


// EXT
	// GL_EXT_compiled_vertex_array
	if (IsSupported("GL_EXT_compiled_vertex_array")) {
		glLockArraysEXT   = (PFNGLLOCKARRAYSEXTPROC)   wglGetProcAddress("glLockArraysEXT");
		glUnlockArraysEXT = (PFNGLUNLOCKARRAYSEXTPROC) wglGetProcAddress("glUnlockArraysEXT");
		if (!glLockArraysEXT || !glUnlockArraysEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_compiled_vertex_array'!")
			m_bGL_EXT_compiled_vertex_array = false;
		} else m_bGL_EXT_compiled_vertex_array = true;
	} else m_bGL_EXT_compiled_vertex_array = false;

	// GL_EXT_draw_range_elements
	if (IsSupported("GL_EXT_draw_range_elements")) {
		glDrawRangeElementsEXT = (PFNGLDRAWRANGEELEMENTSEXTPROC) wglGetProcAddress("glDrawRangeElementsEXT");
		if (!glDrawRangeElementsEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_draw_range_elements'!")
			m_bGL_EXT_draw_range_elements = false;
		} else m_bGL_EXT_draw_range_elements = true;
	} else m_bGL_EXT_draw_range_elements = false;
	if (m_bGL_EXT_draw_range_elements) {	
		glGetIntegerv(GL_MAX_ELEMENTS_VERTICES_EXT, &m_nGL_MAX_ELEMENTS_VERTICES_EXT);
		glGetIntegerv(GL_MAX_ELEMENTS_INDICES_EXT,	&m_nGL_MAX_ELEMENTS_INDICES_EXT);
	} else m_nGL_MAX_ELEMENTS_VERTICES_EXT = m_nGL_MAX_ELEMENTS_INDICES_EXT = 0;

	// GL_EXT_fog_coord
	if (IsSupported("GL_EXT_fog_coord")) {
		glFogCoordfEXT		 = (PFNGLFOGCOORDFEXTPROC)		 wglGetProcAddress("glFogCoordfEXT");
		glFogCoordfvEXT		 = (PFNGLFOGCOORDFVEXTPROC)		 wglGetProcAddress("glFogCoordfvEXT");
		glFogCoorddEXT		 = (PFNGLFOGCOORDDEXTPROC)		 wglGetProcAddress("glFogCoorddEXT");
		glFogCoorddvEXT		 = (PFNGLFOGCOORDDVEXTPROC)		 wglGetProcAddress("glFogCoorddvEXT");
		glFogCoordPointerEXT = (PFNGLFOGCOORDPOINTEREXTPROC) wglGetProcAddress("glFogCoordPointerEXT");
		if (!glFogCoordfEXT || !glFogCoordfvEXT || !glFogCoorddEXT || !glFogCoorddvEXT || !glFogCoordPointerEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_fog_coord'!")
			m_bGL_EXT_fog_coord = false;
		} else m_bGL_EXT_fog_coord = true;
	} else m_bGL_EXT_fog_coord = false;

	// GL_EXT_secondary_color
	if (IsSupported("GL_EXT_secondary_color")) {
		glSecondaryColor3bEXT	   = (PFNGLSECONDARYCOLOR3BEXTPROC)		 wglGetProcAddress("glSecondaryColor3bEXT");
		glSecondaryColor3bvEXT	   = (PFNGLSECONDARYCOLOR3BVEXTPROC)	 wglGetProcAddress("glSecondaryColor3bvEXT");
		glSecondaryColor3dEXT	   = (PFNGLSECONDARYCOLOR3DEXTPROC)		 wglGetProcAddress("glSecondaryColor3dEXT");
		glSecondaryColor3dvEXT	   = (PFNGLSECONDARYCOLOR3DVEXTPROC)	 wglGetProcAddress("glSecondaryColor3dvEXT");
		glSecondaryColor3fEXT	   = (PFNGLSECONDARYCOLOR3FEXTPROC)		 wglGetProcAddress("glSecondaryColor3fEXT");
		glSecondaryColor3fvEXT	   = (PFNGLSECONDARYCOLOR3FVEXTPROC)	 wglGetProcAddress("glSecondaryColor3fvEXT");
		glSecondaryColor3iEXT	   = (PFNGLSECONDARYCOLOR3IEXTPROC)		 wglGetProcAddress("glSecondaryColor3iEXT");
		glSecondaryColor3ivEXT	   = (PFNGLSECONDARYCOLOR3IVEXTPROC)	 wglGetProcAddress("glSecondaryColor3ivEXT");
		glSecondaryColor3sEXT      = (PFNGLSECONDARYCOLOR3SEXTPROC)		 wglGetProcAddress("glSecondaryColor3sEXT");
		glSecondaryColor3svEXT     = (PFNGLSECONDARYCOLOR3SVEXTPROC)	 wglGetProcAddress("glSecondaryColor3svEXT");
		glSecondaryColor3ubEXT     = (PFNGLSECONDARYCOLOR3UBEXTPROC)	 wglGetProcAddress("glSecondaryColor3ubEXT");
		glSecondaryColor3ubvEXT    = (PFNGLSECONDARYCOLOR3UBVEXTPROC)	 wglGetProcAddress("glSecondaryColor3ubvEXT");
		glSecondaryColor3uiEXT     = (PFNGLSECONDARYCOLOR3UIEXTPROC)	 wglGetProcAddress("glSecondaryColor3uiEXT");
		glSecondaryColor3uivEXT    = (PFNGLSECONDARYCOLOR3UIVEXTPROC)	 wglGetProcAddress("glSecondaryColor3uivEXT");
		glSecondaryColor3usEXT     = (PFNGLSECONDARYCOLOR3USEXTPROC)	 wglGetProcAddress("glSecondaryColor3usEXT");
		glSecondaryColor3usvEXT	   = (PFNGLSECONDARYCOLOR3USVEXTPROC)	 wglGetProcAddress("glSecondaryColor3usvEXT");
		glSecondaryColorPointerEXT = (PFNGLSECONDARYCOLORPOINTEREXTPROC) wglGetProcAddress("glSecondaryColorPointerEXT");
		if (!glSecondaryColor3bEXT || !glSecondaryColor3bvEXT || !glSecondaryColor3dEXT ||
			!glSecondaryColor3dvEXT || !glSecondaryColor3fEXT || !glSecondaryColor3fvEXT ||
			!glSecondaryColor3iEXT || !glSecondaryColor3ivEXT || !glSecondaryColor3sEXT ||
			!glSecondaryColor3svEXT || !glSecondaryColor3ubEXT || !glSecondaryColor3ubvEXT ||
			!glSecondaryColor3uiEXT || !glSecondaryColor3uivEXT || !glSecondaryColor3usEXT ||
			!glSecondaryColor3usvEXT || !glSecondaryColorPointerEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_secondary_color'!")
			m_bGL_EXT_secondary_color = false;
		} else m_bGL_EXT_secondary_color = true;
	} else m_bGL_EXT_secondary_color = false;

	// GL_EXT_texture_compression_s3tc
	m_bGL_EXT_texture_compression_s3tc = IsSupported("GL_EXT_texture_compression_s3tc");

	// GL_EXT_texture_compression_latc
	if (IsSupported("GL_EXT_texture_compression_latc")) {
		m_bGL_EXT_texture_compression_latc = true;
	} else m_bGL_EXT_texture_compression_latc = false;

	// GL_EXT_texture_lod_bias
	m_bGL_EXT_texture_lod_bias = IsSupported("GL_EXT_texture_lod_bias");

	// GL_EXT_texture_filter_anisotropic
	m_bGL_EXT_texture_filter_anisotropic = IsSupported("GL_EXT_texture_filter_anisotropic");

	// GL_EXT_separate_specular_color
	m_bGL_EXT_separate_specular_color = IsSupported("GL_EXT_separate_specular_color");

	// GL_EXT_texture_edge_clamp
	m_bGL_EXT_texture_edge_clamp = IsSupported("GL_EXT_texture_edge_clamp");

	// GL_EXT_texture_rectangle
	m_bGL_EXT_texture_rectangle = IsSupported("GL_EXT_texture_rectangle");

	// GL_EXT_texture3D
	if (IsSupported("GL_EXT_texture3D")) {
		glTexImage3DEXT	   = (PFNGLTEXIMAGE3DEXTPROC)	 wglGetProcAddress("glTexImage3DEXT");
		glTexSubImage3DEXT = (PFNGLTEXSUBIMAGE3DEXTPROC) wglGetProcAddress("glTexSubImage3DEXT");
		if (!glTexImage3DEXT || !glTexSubImage3DEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_texture3D'!")
			m_bGL_EXT_texture3D = false;
		} else m_bGL_EXT_texture3D = true;
	} else m_bGL_EXT_texture3D = false;

	// GL_EXT_texture_cube_map
	m_bGL_EXT_texture_cube_map = IsSupported("GL_EXT_texture_cube_map");

	// GL_EXT_stencil_wrap
	m_bGL_EXT_stencil_wrap = IsSupported("GL_EXT_stencil_wrap");

	// GL_EXT_stencil_two_side
	if (IsSupported("GL_EXT_stencil_two_side")) {
		glActiveStencilFaceEXT = (PFNGLACTIVESTENCILFACEEXTPROC) wglGetProcAddress("glActiveStencilFaceEXT");
		if (!glActiveStencilFaceEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_stencil_two_side'!")
			m_bGL_EXT_stencil_two_side = false;
		} else m_bGL_EXT_stencil_two_side = true;
	} else m_bGL_EXT_stencil_two_side = false;

	// GL_EXT_packed_depth_stencil
	m_bGL_EXT_packed_depth_stencil = IsSupported("GL_EXT_packed_depth_stencil");

	// GL_EXT_depth_bounds_test
	if (IsSupported("GL_EXT_depth_bounds_test")) {
		glDepthBoundsEXT = (PFNGLDEPTHBOUNDSEXTPROC) wglGetProcAddress("glDepthBoundsEXT");
		if (!glDepthBoundsEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_depth_bounds_test'!")
			m_bGL_EXT_depth_bounds_test = false;
		} else m_bGL_EXT_depth_bounds_test = true;
	} else m_bGL_EXT_depth_bounds_test = false;

	// GL_EXT_framebuffer_object
	if (IsSupported("GL_EXT_framebuffer_object")) {
		glIsRenderbufferEXT						 = (PFNGLISRENDERBUFFEREXTPROC)						 wglGetProcAddress("glIsRenderbufferEXT");
		glBindRenderbufferEXT					 = (PFNGLBINDRENDERBUFFEREXTPROC)					 wglGetProcAddress("glBindRenderbufferEXT");
		glDeleteRenderbuffersEXT				 = (PFNGLDELETERENDERBUFFERSEXTPROC)				 wglGetProcAddress("glDeleteRenderbuffersEXT");
		glGenRenderbuffersEXT					 = (PFNGLGENRENDERBUFFERSEXTPROC)					 wglGetProcAddress("glGenRenderbuffersEXT");
		glRenderbufferStorageEXT				 = (PFNGLRENDERBUFFERSTORAGEEXTPROC)				 wglGetProcAddress("glRenderbufferStorageEXT");
		glGetRenderbufferParameterivEXT			 = (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC)			 wglGetProcAddress("glGetRenderbufferParameterivEXT");
		glIsFramebufferEXT						 = (PFNGLISFRAMEBUFFEREXTPROC)						 wglGetProcAddress("glIsFramebufferEXT");
		glBindFramebufferEXT					 = (PFNGLBINDFRAMEBUFFEREXTPROC)					 wglGetProcAddress("glBindFramebufferEXT");
		glDeleteFramebuffersEXT					 = (PFNGLDELETEFRAMEBUFFERSEXTPROC)					 wglGetProcAddress("glDeleteFramebuffersEXT");
		glGenFramebuffersEXT					 = (PFNGLGENFRAMEBUFFERSEXTPROC)					 wglGetProcAddress("glGenFramebuffersEXT");
		glCheckFramebufferStatusEXT				 = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)				 wglGetProcAddress("glCheckFramebufferStatusEXT");
		glFramebufferTexture1DEXT				 = (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC)				 wglGetProcAddress("glFramebufferTexture1DEXT");
		glFramebufferTexture2DEXT				 = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)				 wglGetProcAddress("glFramebufferTexture2DEXT");
		glFramebufferTexture3DEXT				 = (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC)				 wglGetProcAddress("glFramebufferTexture3DEXT");
		glFramebufferRenderbufferEXT			 = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)			 wglGetProcAddress("glFramebufferRenderbufferEXT");
		glGetFramebufferAttachmentParameterivEXT = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC) wglGetProcAddress("glGetFramebufferAttachmentParameterivEXT");
		glGenerateMipmapEXT						 = (PFNGLGENERATEMIPMAPEXTPROC)						 wglGetProcAddress("glGenerateMipmapEXT");
		if (!glIsRenderbufferEXT || !glBindRenderbufferEXT || !glDeleteRenderbuffersEXT || !glGenRenderbuffersEXT ||
			!glRenderbufferStorageEXT || !glGetRenderbufferParameterivEXT || !glIsFramebufferEXT ||
			!glBindFramebufferEXT || !glDeleteFramebuffersEXT || !glGenFramebuffersEXT || !glCheckFramebufferStatusEXT ||
			!glFramebufferTexture1DEXT || !glFramebufferTexture2DEXT || !glFramebufferTexture3DEXT ||
			!glFramebufferRenderbufferEXT || !glGetFramebufferAttachmentParameterivEXT || !glGenerateMipmapEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_framebuffer_object'!")
			m_bGL_EXT_framebuffer_object = false;
		} else m_bGL_EXT_framebuffer_object = true;
	} else m_bGL_EXT_framebuffer_object = false;

	// GL_EXT_framebuffer_multisample
	if (IsSupported("GL_EXT_framebuffer_multisample")) {
		glRenderbufferStorageMultisampleEXT = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)wglGetProcAddress("glRenderbufferStorageMultisampleEXT");
		if (!glRenderbufferStorageMultisampleEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_framebuffer_multisample'!")
			m_bGL_EXT_framebuffer_multisample = false;
		} else m_bGL_EXT_framebuffer_multisample = true;
	} else m_bGL_EXT_framebuffer_multisample = false;

	// GL_EXT_framebuffer_blit
	if (IsSupported("GL_EXT_framebuffer_blit")) {
		glBlitFramebufferEXT = (PFNGLBLITFRAMEBUFFEREXTPROC)wglGetProcAddress("glBlitFramebufferEXT");
		if (!glBlitFramebufferEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_framebuffer_blit'!")
			m_bGL_EXT_framebuffer_blit = false;
		} else m_bGL_EXT_framebuffer_blit = true;
	} else m_bGL_EXT_framebuffer_blit = false;

	// GL_EXT_geometry_shader4
	if (IsSupported("GL_EXT_geometry_shader4")) {
		glProgramParameteriEXT = (PFNGLPROGRAMPARAMETERIEXTPROC)wglGetProcAddress("glProgramParameteriEXT");
		if (!glProgramParameteriEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_geometry_shader4'!")
			m_bGL_EXT_geometry_shader4 = false;
		} else m_bGL_EXT_geometry_shader4 = true;
	} else m_bGL_EXT_geometry_shader4 = false;


// ARB
	// GL_ARB_texture_float
	m_bGL_ARB_texture_float = IsSupported("GL_ARB_texture_float");

	// GL_ARB_color_buffer_float
	if (IsSupported("GL_ARB_color_buffer_float")) {
		glClampColorARB = (PFNGLCLAMPCOLORARBPROC)wglGetProcAddress("glClampColorARB");
		if (!glClampColorARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_color_buffer_float'!")
			m_bGL_ARB_color_buffer_float = false;
		} else m_bGL_ARB_color_buffer_float = true;
	} else m_bGL_ARB_color_buffer_float = false;

	// GL_ARB_multitexture
	if (IsSupported("GL_ARB_multitexture")) {
		glActiveTextureARB		 = (PFNGLACTIVETEXTUREARBPROC) 		 wglGetProcAddress("glActiveTextureARB");
		glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC) wglGetProcAddress("glClientActiveTextureARB");
		glMultiTexCoord1dARB	 = (PFNGLMULTITEXCOORD1DARBPROC) 	 wglGetProcAddress("glMultiTexCoord1dARB");
		glMultiTexCoord1dvARB	 = (PFNGLMULTITEXCOORD1DVARBPROC) 	 wglGetProcAddress("glMultiTexCoord1dvARB");
		glMultiTexCoord1fARB	 = (PFNGLMULTITEXCOORD1FARBPROC) 	 wglGetProcAddress("glMultiTexCoord1fARB");
		glMultiTexCoord1fvARB	 = (PFNGLMULTITEXCOORD1FVARBPROC) 	 wglGetProcAddress("glMultiTexCoord1fvARB");
		glMultiTexCoord1iARB	 = (PFNGLMULTITEXCOORD1IARBPROC) 	 wglGetProcAddress("glMultiTexCoord1iARB");
		glMultiTexCoord1ivARB	 = (PFNGLMULTITEXCOORD1IVARBPROC) 	 wglGetProcAddress("glMultiTexCoord1ivARB");
		glMultiTexCoord1sARB	 = (PFNGLMULTITEXCOORD1SARBPROC) 	 wglGetProcAddress("glMultiTexCoord1sARB");
		glMultiTexCoord1svARB	 = (PFNGLMULTITEXCOORD1SVARBPROC) 	 wglGetProcAddress("glMultiTexCoord1svARB");
		glMultiTexCoord2dARB	 = (PFNGLMULTITEXCOORD2DARBPROC) 	 wglGetProcAddress("glMultiTexCoord2dARB");
		glMultiTexCoord2dvARB	 = (PFNGLMULTITEXCOORD2DVARBPROC) 	 wglGetProcAddress("glMultiTexCoord2dvARB");
		glMultiTexCoord2fARB	 = (PFNGLMULTITEXCOORD2FARBPROC) 	 wglGetProcAddress("glMultiTexCoord2fARB");
		glMultiTexCoord2fvARB	 = (PFNGLMULTITEXCOORD2FVARBPROC) 	 wglGetProcAddress("glMultiTexCoord2fvARB");
		glMultiTexCoord2iARB	 = (PFNGLMULTITEXCOORD2IARBPROC) 	 wglGetProcAddress("glMultiTexCoord2iARB");
		glMultiTexCoord2ivARB	 = (PFNGLMULTITEXCOORD2IVARBPROC) 	 wglGetProcAddress("glMultiTexCoord2ivARB");
		glMultiTexCoord2sARB	 = (PFNGLMULTITEXCOORD2SARBPROC) 	 wglGetProcAddress("glMultiTexCoord2sARB");
		glMultiTexCoord2svARB	 = (PFNGLMULTITEXCOORD2SVARBPROC) 	 wglGetProcAddress("glMultiTexCoord2svARB");
		glMultiTexCoord3dARB	 = (PFNGLMULTITEXCOORD3DARBPROC) 	 wglGetProcAddress("glMultiTexCoord3dARB");
		glMultiTexCoord3dvARB	 = (PFNGLMULTITEXCOORD3DVARBPROC) 	 wglGetProcAddress("glMultiTexCoord3dvARB");
		glMultiTexCoord3fARB	 = (PFNGLMULTITEXCOORD3FARBPROC) 	 wglGetProcAddress("glMultiTexCoord3fARB");
		glMultiTexCoord3fvARB	 = (PFNGLMULTITEXCOORD3FVARBPROC) 	 wglGetProcAddress("glMultiTexCoord3fvARB");
		glMultiTexCoord3iARB	 = (PFNGLMULTITEXCOORD3IARBPROC) 	 wglGetProcAddress("glMultiTexCoord3iARB");
		glMultiTexCoord3ivARB	 = (PFNGLMULTITEXCOORD3IVARBPROC) 	 wglGetProcAddress("glMultiTexCoord3ivARB");
		glMultiTexCoord3sARB	 = (PFNGLMULTITEXCOORD3SARBPROC) 	 wglGetProcAddress("glMultiTexCoord3sARB");
		glMultiTexCoord3svARB	 = (PFNGLMULTITEXCOORD3SVARBPROC) 	 wglGetProcAddress("glMultiTexCoord3svARB");
		glMultiTexCoord4dARB	 = (PFNGLMULTITEXCOORD4DARBPROC) 	 wglGetProcAddress("glMultiTexCoord4dARB");
		glMultiTexCoord4dvARB	 = (PFNGLMULTITEXCOORD4DVARBPROC) 	 wglGetProcAddress("glMultiTexCoord4dvARB");
		glMultiTexCoord4fARB	 = (PFNGLMULTITEXCOORD4FARBPROC) 	 wglGetProcAddress("glMultiTexCoord4fARB");
		glMultiTexCoord4fvARB	 = (PFNGLMULTITEXCOORD4FVARBPROC) 	 wglGetProcAddress("glMultiTexCoord4fvARB");
		glMultiTexCoord4iARB	 = (PFNGLMULTITEXCOORD4IARBPROC) 	 wglGetProcAddress("glMultiTexCoord4iARB");
		glMultiTexCoord4ivARB	 = (PFNGLMULTITEXCOORD4IVARBPROC) 	 wglGetProcAddress("glMultiTexCoord4ivARB");
		glMultiTexCoord4sARB	 = (PFNGLMULTITEXCOORD4SARBPROC) 	 wglGetProcAddress("glMultiTexCoord4sARB");
		glMultiTexCoord4svARB	 = (PFNGLMULTITEXCOORD4SVARBPROC) 	 wglGetProcAddress("glMultiTexCoord4svARB");
		if (!glActiveTextureARB || !glClientActiveTextureARB || 
			!glMultiTexCoord1dARB || !glMultiTexCoord1dvARB || !glMultiTexCoord1fARB || !glMultiTexCoord1fvARB || 
			!glMultiTexCoord1iARB || !glMultiTexCoord1ivARB || !glMultiTexCoord1sARB || !glMultiTexCoord1svARB || 
			!glMultiTexCoord2dARB || !glMultiTexCoord2dvARB || !glMultiTexCoord2fARB || !glMultiTexCoord2fvARB || 
			!glMultiTexCoord2iARB || !glMultiTexCoord2ivARB || !glMultiTexCoord2sARB || !glMultiTexCoord2svARB || 
			!glMultiTexCoord3dARB || !glMultiTexCoord3dvARB || !glMultiTexCoord3fARB || !glMultiTexCoord3fvARB || 
			!glMultiTexCoord3iARB || !glMultiTexCoord3ivARB || !glMultiTexCoord3sARB || !glMultiTexCoord3svARB || 
			!glMultiTexCoord4dARB || !glMultiTexCoord4dvARB || !glMultiTexCoord4fARB || !glMultiTexCoord4fvARB || 
			!glMultiTexCoord4iARB || !glMultiTexCoord4ivARB || !glMultiTexCoord4sARB || !glMultiTexCoord4svARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_multitexture'!")
			m_bGL_ARB_multitexture = false;
		} else m_bGL_ARB_multitexture = true;
	} else m_bGL_ARB_multitexture = false;

	// GL_ARB_vertex_buffer_object
	if (IsSupported("GL_ARB_vertex_buffer_object")) {
		glBindBufferARB			  = (PFNGLBINDBUFFERARBPROC)		   wglGetProcAddress("glBindBufferARB");
		glDeleteBuffersARB		  = (PFNGLDELETEBUFFERSARBPROC)		   wglGetProcAddress("glDeleteBuffersARB");
		glGenBuffersARB			  = (PFNGLGENBUFFERSARBPROC)		   wglGetProcAddress("glGenBuffersARB");
		glBufferDataARB			  = (PFNGLBUFFERDATAARBPROC)		   wglGetProcAddress("glBufferDataARB");
		glBufferSubDataARB		  = (PFNGLBUFFERSUBDATAARBPROC)		   wglGetProcAddress("glBufferSubDataARB");
		glGetBufferSubDataARB	  = (PFNGLGETBUFFERSUBDATAARBPROC)	   wglGetProcAddress("glGetBufferSubDataARB");
		glMapBufferARB			  = (PFNGLMAPBUFFERARBPROC)			   wglGetProcAddress("glMapBufferARB");
		glUnmapBufferARB		  = (PFNGLUNMAPBUFFERARBPROC)		   wglGetProcAddress("glUnmapBufferARB");
		glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC) wglGetProcAddress("glGetBufferParameterivARB");
		glGetBufferPointervARB	  = (PFNGLGETBUFFERPOINTERVARBPROC)	   wglGetProcAddress("glGetBufferPointervARB");
		if (!glBindBufferARB || !glDeleteBuffersARB || !glGenBuffersARB ||
			!glBufferDataARB || !glBufferSubDataARB || !glGetBufferSubDataARB || !glMapBufferARB ||
			!glUnmapBufferARB || !glGetBufferParameterivARB || !glGetBufferPointervARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_vertex_buffer_object'!")
			m_bGL_ARB_vertex_buffer_object = false;
		} else m_bGL_ARB_vertex_buffer_object = true;
	} else m_bGL_ARB_vertex_buffer_object = false;

	// GL_ARB_texture_border_clamp
	m_bGL_ARB_texture_border_clamp = IsSupported("GL_ARB_texture_border_clamp");

	// GL_ARB_texture_mirrored_repeat 
	m_bGL_ARB_texture_mirrored_repeat = IsSupported("GL_ARB_texture_mirrored_repeat");

	// GL_ARB_texture_cube_map
	m_bGL_ARB_texture_cube_map = IsSupported("GL_ARB_texture_cube_map");

	// GL_ARB_texture_env_combine
	m_bGL_ARB_texture_env_combine = IsSupported("GL_ARB_texture_env_combine");

	// GL_ARB_texture_env_dot3
	m_bGL_ARB_texture_env_dot3 = IsSupported("GL_ARB_texture_env_dot3");

	// GL_ARB_occlusion_query
	if (IsSupported("GL_ARB_occlusion_query")) {
		glGenQueriesARB	       = (PFNGLGENQUERIESARBPROC)		 wglGetProcAddress("glGenQueriesARB");
		glDeleteQueriesARB     = (PFNGLDELETEQUERIESARBPROC)	 wglGetProcAddress("glDeleteQueriesARB");
		glIsQueryARB	       = (PFNGLISQUERYARBPROC)			 wglGetProcAddress("glIsQueryARB");
		glBeginQueryARB	       = (PFNGLBEGINQUERYARBPROC)		 wglGetProcAddress("glBeginQueryARB");
		glEndQueryARB	       = (PFNGLENDQUERYARBPROC)			 wglGetProcAddress("glEndQueryARB");
		glGetQueryivARB		   = (PFNGLGETQUERYIVARBPROC)		 wglGetProcAddress("glGetQueryivARB");
		glGetQueryObjectivARB  = (PFNGLGETQUERYOBJECTIVARBPROC)	 wglGetProcAddress("glGetQueryObjectivARB");
		glGetQueryObjectuivARB = (PFNGLGETQUERYOBJECTUIVARBPROC) wglGetProcAddress("glGetQueryObjectuivARB");
		if (!glGenQueriesARB || !glDeleteQueriesARB || !glIsQueryARB || !glBeginQueryARB ||
			!glEndQueryARB || !glGetQueryivARB || !glGetQueryObjectivARB || !glGetQueryObjectuivARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_occlusion_query'!")
			m_bGL_ARB_occlusion_query = false;
		} else m_bGL_ARB_occlusion_query = true;
	} else m_bGL_ARB_occlusion_query = false;

	// GL_ARB_texture_compression
	if (IsSupported("GL_ARB_texture_compression")) {
		glCompressedTexImage3DARB    = (PFNGLCOMPRESSEDTEXIMAGE3DARBPROC)    wglGetProcAddress("glCompressedTexImage3DARB");
		glCompressedTexImage2DARB    = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)    wglGetProcAddress("glCompressedTexImage2DARB");
		glCompressedTexImage1DARB    = (PFNGLCOMPRESSEDTEXIMAGE1DARBPROC)    wglGetProcAddress("glCompressedTexImage1DARB");
		glCompressedTexSubImage3DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC) wglGetProcAddress("glCompressedTexSubImage3DARB");
		glCompressedTexSubImage2DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC) wglGetProcAddress("glCompressedTexSubImage2DARB");
		glCompressedTexSubImage1DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC) wglGetProcAddress("glCompressedTexSubImage1DARB");
		glGetCompressedTexImageARB   = (PFNGLGETCOMPRESSEDTEXIMAGEARBPROC)   wglGetProcAddress("glGetCompressedTexImageARB");
		if (!glCompressedTexImage3DARB || !glCompressedTexImage2DARB || !glCompressedTexImage1DARB ||
			!glCompressedTexSubImage3DARB || !glCompressedTexSubImage2DARB ||
			!glCompressedTexSubImage1DARB || !glGetCompressedTexImageARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_texture_compression'!")
			m_bGL_ARB_texture_compression = false;
		} else m_bGL_ARB_texture_compression = true;
	} else m_bGL_ARB_texture_compression = false;

	// GL_ARB_depth_texture
	m_bGL_ARB_depth_texture = IsSupported("GL_ARB_depth_texture");

	// GL_ARB_point_sprite
	m_bGL_ARB_point_sprite = IsSupported("GL_ARB_point_sprite");

	// GL_ARB_point_parameters
	if (IsSupported("GL_ARB_point_parameters")) {
		glPointParameterfARB  = (PFNGLPOINTPARAMETERFARBPROC)  wglGetProcAddress("glPointParameterfARB");
		glPointParameterfvARB = (PFNGLPOINTPARAMETERFVARBPROC) wglGetProcAddress("glPointParameterfvARB");
		if (!glPointParameterfARB || !glPointParameterfvARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_point_parameters'!")
			m_bGL_ARB_point_parameters = false;
		} else m_bGL_ARB_point_parameters = true;
	} else m_bGL_ARB_point_parameters = false;

	// GL_ARB_shading_language_100
	m_bGL_ARB_shading_language_100 = IsSupported("GL_ARB_shading_language_100");

	// GL_ARB_vertex_program
	if (IsSupported("GL_ARB_vertex_program")) {
		glVertexAttribPointerARB      = (PFNGLVERTEXATTRIBPOINTERARBPROC)      wglGetProcAddress("glVertexAttribPointerARB");
		glEnableVertexAttribArrayARB  = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC)  wglGetProcAddress("glEnableVertexAttribArrayARB");
		glDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC) wglGetProcAddress("glDisableVertexAttribArrayARB");
		glGetProgramivARB			  = (PFNGLGETPROGRAMIVARBPROC)			   wglGetProcAddress("glGetProgramivARB");
		if (!glVertexAttribPointerARB || !glEnableVertexAttribArrayARB || !glDisableVertexAttribArrayARB ||
			!glGetProgramivARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_vertex_program'!")
			m_bGL_ARB_vertex_program = false;
		} else m_bGL_ARB_vertex_program = true;
	} else m_bGL_ARB_vertex_program = false;

	// GL_ARB_fragment_program
	if (IsSupported("GL_ARB_fragment_program")) {
		// At the moment we do not need any of the functions this extension provides
		m_bGL_ARB_fragment_program = true;
	} else m_bGL_ARB_fragment_program = false;

	// GL_ARB_draw_buffers
	if (IsSupported("GL_ARB_draw_buffers")) {
		glDrawBuffersARB = (PFNGLDRAWBUFFERSARBPROC) wglGetProcAddress("glDrawBuffersARB");
		if (!glDrawBuffersARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_draw_buffers'!")
			m_bGL_ARB_draw_buffers = false;
		} else m_bGL_ARB_draw_buffers = true;
	} else m_bGL_ARB_draw_buffers = false;

	// GL_ARB_shader_objects
	if (IsSupported("GL_ARB_shader_objects")) {
		glDeleteObjectARB			= (PFNGLDELETEOBJECTARBPROC)			wglGetProcAddress("glDeleteObjectARB");
		glGetHandleARB				= (PFNGLGETHANDLEARBPROC)				wglGetProcAddress("glGetHandleARB");
		glDetachObjectARB			= (PFNGLDETACHOBJECTARBPROC)			wglGetProcAddress("glDetachObjectARB");
		glCreateShaderObjectARB		= (PFNGLCREATESHADEROBJECTARBPROC)		wglGetProcAddress("glCreateShaderObjectARB");
		glShaderSourceARB			= (PFNGLSHADERSOURCEARBPROC)			wglGetProcAddress("glShaderSourceARB");
		glCompileShaderARB			= (PFNGLCOMPILESHADERARBPROC)			wglGetProcAddress("glCompileShaderARB");
		glCreateProgramObjectARB	= (PFNGLCREATEPROGRAMOBJECTARBPROC)		wglGetProcAddress("glCreateProgramObjectARB");
		glAttachObjectARB			= (PFNGLATTACHOBJECTARBPROC)			wglGetProcAddress("glAttachObjectARB");
		glLinkProgramARB			= (PFNGLLINKPROGRAMARBPROC)				wglGetProcAddress("glLinkProgramARB");
		glUseProgramObjectARB		= (PFNGLUSEPROGRAMOBJECTARBPROC)		wglGetProcAddress("glUseProgramObjectARB");
		glValidateProgramARB		= (PFNGLVALIDATEPROGRAMARBPROC)			wglGetProcAddress("glValidateProgramARB");
		glUniform1fARB				= (PFNGLUNIFORM1FARBPROC)				wglGetProcAddress("glUniform1fARB");
		glUniform2fARB				= (PFNGLUNIFORM2FARBPROC)				wglGetProcAddress("glUniform2fARB");
		glUniform3fARB				= (PFNGLUNIFORM3FARBPROC)				wglGetProcAddress("glUniform3fARB");
		glUniform4fARB				= (PFNGLUNIFORM4FARBPROC)				wglGetProcAddress("glUniform4fARB");
		glUniform1iARB				= (PFNGLUNIFORM1IARBPROC)				wglGetProcAddress("glUniform1iARB");
		glUniform2iARB				= (PFNGLUNIFORM2IARBPROC)				wglGetProcAddress("glUniform2iARB");
		glUniform3iARB				= (PFNGLUNIFORM3IARBPROC)				wglGetProcAddress("glUniform3iARB");
		glUniform4iARB				= (PFNGLUNIFORM4IARBPROC)				wglGetProcAddress("glUniform4iARB");
		glUniform1fvARB				= (PFNGLUNIFORM1FVARBPROC)				wglGetProcAddress("glUniform1fvARB");
		glUniform2fvARB				= (PFNGLUNIFORM2FVARBPROC)				wglGetProcAddress("glUniform2fvARB");
		glUniform3fvARB				= (PFNGLUNIFORM3FVARBPROC)				wglGetProcAddress("glUniform3fvARB");
		glUniform4fvARB				= (PFNGLUNIFORM4FVARBPROC)				wglGetProcAddress("glUniform4fvARB");
		glUniform1ivARB				= (PFNGLUNIFORM1IVARBPROC)				wglGetProcAddress("glUniform1ivARB");
		glUniform2ivARB				= (PFNGLUNIFORM2IVARBPROC)				wglGetProcAddress("glUniform2ivARB");
		glUniform3ivARB				= (PFNGLUNIFORM3IVARBPROC)				wglGetProcAddress("glUniform3ivARB");
		glUniform4ivARB				= (PFNGLUNIFORM4IVARBPROC)				wglGetProcAddress("glUniform4ivARB");
		glUniformMatrix2fvARB		= (PFNGLUNIFORMMATRIX2FVARBPROC)		wglGetProcAddress("glUniformMatrix2fvARB");
		glUniformMatrix3fvARB		= (PFNGLUNIFORMMATRIX3FVARBPROC)		wglGetProcAddress("glUniformMatrix3fvARB");
		glUniformMatrix4fvARB		= (PFNGLUNIFORMMATRIX4FVARBPROC)		wglGetProcAddress("glUniformMatrix4fvARB");
		glGetObjectParameterfvARB	= (PFNGLGETOBJECTPARAMETERFVARBPROC)	wglGetProcAddress("glGetObjectParameterfvARB");
		glGetObjectParameterivARB	= (PFNGLGETOBJECTPARAMETERIVARBPROC)	wglGetProcAddress("glGetObjectParameterivARB");
		glGetInfoLogARB				= (PFNGLGETINFOLOGARBPROC)				wglGetProcAddress("glGetInfoLogARB");
		glGetAttachedObjectsARB		= (PFNGLGETATTACHEDOBJECTSARBPROC)		wglGetProcAddress("glGetAttachedObjectsARB");
		glGetUniformLocationARB		= (PFNGLGETUNIFORMLOCATIONARBPROC)		wglGetProcAddress("glGetUniformLocationARB");
		glGetActiveUniformARB		= (PFNGLGETACTIVEUNIFORMARBPROC)		wglGetProcAddress("glGetActiveUniformARB");
		glGetUniformfvARB			= (PFNGLGETUNIFORMFVARBPROC)			wglGetProcAddress("glGetUniformfvARB");
		glGetUniformivARB			= (PFNGLGETUNIFORMIVARBPROC)			wglGetProcAddress("glGetUniformivARB");
		glGetShaderSourceARB		= (PFNGLGETSHADERSOURCEARBPROC)			wglGetProcAddress("glGetShaderSourceARB");
		if (!glDeleteObjectARB || !glGetHandleARB || !glDetachObjectARB || !glCreateShaderObjectARB || !glShaderSourceARB || !glCompileShaderARB ||
			!glCreateProgramObjectARB || !glAttachObjectARB || !glLinkProgramARB || !glUseProgramObjectARB || !glValidateProgramARB || !glUniform1fARB ||
			!glUniform2fARB || !glUniform3fARB || !glUniform4fARB || !glUniform1iARB || !glUniform2iARB || !glUniform3iARB || !glUniform4iARB || !glUniform1fvARB ||
			!glUniform2fvARB || !glUniform3fvARB || !glUniform4fvARB || !glUniform1ivARB || !glUniform2ivARB || !glUniform3ivARB || !glUniform4ivARB || !glUniformMatrix2fvARB ||
			!glUniformMatrix3fvARB || !glUniformMatrix4fvARB || !glGetObjectParameterfvARB || !glGetObjectParameterivARB || !glGetInfoLogARB || !glGetAttachedObjectsARB ||
			!glGetUniformLocationARB || !glGetActiveUniformARB || !glGetUniformfvARB || !glGetUniformivARB || !glGetShaderSourceARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_shader_objects'!")
			m_bGL_ARB_shader_objects = false;
		} else m_bGL_ARB_shader_objects = true;
	} else m_bGL_ARB_shader_objects = false;

	// GL_ARB_vertex_shader
	if (IsSupported("GL_ARB_vertex_shader")) {
		glBindAttribLocationARB = (PFNGLBINDATTRIBLOCATIONARBPROC) wglGetProcAddress("glBindAttribLocationARB");
		glGetActiveAttribARB    = (PFNGLGETACTIVEATTRIBARBPROC)    wglGetProcAddress("glGetActiveAttribARB");
		glGetAttribLocationARB  = (PFNGLGETATTRIBLOCATIONARBPROC)  wglGetProcAddress("glGetAttribLocationARB");
		if (!glBindAttribLocationARB || !glGetActiveAttribARB || !glGetAttribLocationARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_vertex_shader'!")
			m_bGL_ARB_vertex_shader = false;
		} else m_bGL_ARB_vertex_shader = true;
	} else m_bGL_ARB_vertex_shader = false;

	// GL_ARB_texture_rectangle
	m_bGL_ARB_texture_rectangle = IsSupported("GL_ARB_texture_rectangle");

	// GL_ARB_multisample
	m_bGL_ARB_multisample = IsSupported("GL_ARB_multisample");


// ATI
	// GL_ATI_separate_stencil 
	if (IsSupported("GL_ATI_separate_stencil")) {
		glStencilOpSeparateATI   = (PFNGLSTENCILOPSEPARATEATIPROC)	 wglGetProcAddress("glStencilOpSeparateATI");
		glStencilFuncSeparateATI = (PFNGLSTENCILFUNCSEPARATEATIPROC) wglGetProcAddress("glStencilFuncSeparateATI");
		if (!glStencilOpSeparateATI || !glStencilFuncSeparateATI) {
			PL_LOG(Info, "Couldn't use extension 'GL_ATI_separate_stencil'!")
			m_bGL_ATI_separate_stencil = false;
		} else m_bGL_ATI_separate_stencil = true;
	} else m_bGL_ATI_separate_stencil = false;

	// GL_ATI_draw_buffers
	if (IsSupported("GL_ATI_draw_buffers")) {
		glDrawBuffersATI = (PFNGLDRAWBUFFERSATIPROC) wglGetProcAddress("glDrawBuffersATI");
		if (!glDrawBuffersATI) {
			PL_LOG(Info, "Couldn't use extension 'GL_ATI_draw_buffers'!")
			m_bGL_ATI_draw_buffers = false;
		} else m_bGL_ATI_draw_buffers = true;
	} else m_bGL_ATI_draw_buffers = false;

	// GL_ATI_texture_compression_3dc
	if (IsSupported("GL_ATI_texture_compression_3dc")) {
		m_bGL_ATI_texture_compression_3dc = true;
	} else m_bGL_ATI_texture_compression_3dc = false;


// AMD
	// GL_AMD_vertex_shader_tessellator
	if (IsSupported("GL_AMD_vertex_shader_tessellator")) {
		glTessellationFactorAMD = (PFNGLTESSELLATIONFACTORAMDPROC) wglGetProcAddress("glTessellationFactorAMD");
		glTessellationModeAMD   = (PFNGLTESSELLATIONMODEAMDPROC)   wglGetProcAddress("glTessellationModeAMD");
		if (!glTessellationFactorAMD || !glTessellationModeAMD) {
			PL_LOG(Info, "Couldn't use extension 'GL_AMD_vertex_shader_tessellator'!")
			m_bGL_AMD_vertex_shader_tessellator = false;
		} else m_bGL_AMD_vertex_shader_tessellator = true;
	} else m_bGL_AMD_vertex_shader_tessellator = false;


// NV
	// GL_NV_texture_rectangle
	m_bGL_NV_texture_rectangle = IsSupported("GL_NV_texture_rectangle");

	// GL_NV_occlusion_query
	if (IsSupported("GL_NV_occlusion_query")) {
		glGenOcclusionQueriesNV	   = (PFNGLGENOCCLUSIONQUERIESNVPROC)	 wglGetProcAddress("glGenOcclusionQueriesNV");
		glDeleteOcclusionQueriesNV = (PFNGLDELETEOCCLUSIONQUERIESNVPROC) wglGetProcAddress("glDeleteOcclusionQueriesNV");
		glIsOcclusionQueryNV	   = (PFNGLISOCCLUSIONQUERYNVPROC)		 wglGetProcAddress("glIsOcclusionQueryNV");
		glBeginOcclusionQueryNV	   = (PFNGLBEGINOCCLUSIONQUERYNVPROC)	 wglGetProcAddress("glBeginOcclusionQueryNV");
		glEndOcclusionQueryNV	   = (PFNGLENDOCCLUSIONQUERYNVPROC)		 wglGetProcAddress("glEndOcclusionQueryNV");
		glGetOcclusionQueryivNV	   = (PFNGLGETOCCLUSIONQUERYIVNVPROC)	 wglGetProcAddress("glGetOcclusionQueryivNV");
		glGetOcclusionQueryuivNV   = (PFNGLGETOCCLUSIONQUERYUIVNVPROC)	 wglGetProcAddress("glGetOcclusionQueryuivNV");
		if (!glGenOcclusionQueriesNV || !glDeleteOcclusionQueriesNV || !glIsOcclusionQueryNV || !glBeginOcclusionQueryNV ||
			!glEndOcclusionQueryNV || !glGetOcclusionQueryivNV || !glGetOcclusionQueryuivNV) {
			m_bGL_NV_occlusion_query = false;
		} else m_bGL_NV_occlusion_query = true;
	} else m_bGL_NV_occlusion_query = false;


// SGIS
	// GL_SGIS_generate_mipmap
	m_bGL_SGIS_generate_mipmap = IsSupported("GL_SGIS_generate_mipmap");


// HP
	// GL_HP_occlusion_test
	m_bGL_HP_occlusion_test = IsSupported("GL_HP_occlusion_test");


	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
