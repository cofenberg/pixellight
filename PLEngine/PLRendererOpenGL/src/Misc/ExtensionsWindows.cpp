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
	} else {
		m_bInitialized = true;
	}

	{ // Print a list af all available extensions into the log
		PL_LOG(Info, "Extensions info:")
		WriteExtensionStringIntoLog(reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS)));

		// WGL_ARB_extensions_string
		wglGetExtensionsStringARB = reinterpret_cast<PFNWGLGETEXTENSIONSSTRINGARBPROC>(wglGetProcAddress("wglGetExtensionsStringARB"));
		m_bWGL_ARB_extensions_string = (wglGetExtensionsStringARB != nullptr);

		if (m_bWGL_ARB_extensions_string)
			WriteExtensionStringIntoLog(reinterpret_cast<const char*>(wglGetExtensionsStringARB(wglGetCurrentDC())));
	}


// WGL
	// WGL_EXT_swap_control
	if (IsSupported("WGL_EXT_swap_control")) {
		wglSwapIntervalEXT	  = reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>	  (wglGetProcAddress("wglSwapIntervalEXT"));
		wglGetSwapIntervalEXT = reinterpret_cast<PFNWGLGETSWAPINTERVALEXTPROC>(wglGetProcAddress("wglGetSwapIntervalEXT"));
		if (!wglSwapIntervalEXT || !wglGetSwapIntervalEXT) {
			PL_LOG(Info, "Couldn't use extension 'WGL_EXT_swap_control'!")
			m_bWGL_EXT_swap_control = false;
		} else {
			m_bWGL_EXT_swap_control = true;
		}
	} else {
		m_bWGL_EXT_swap_control = false;
	}

	// WGL_ARB_pbuffer
	if (IsSupported("WGL_ARB_pbuffer")) {
		wglCreatePbufferARB	     = reinterpret_cast<PFNWGLCREATEPBUFFERARBPROC>		(wglGetProcAddress("wglCreatePbufferARB"));
		wglGetPbufferDCARB	     = reinterpret_cast<PFNWGLGETPBUFFERDCARBPROC>		(wglGetProcAddress("wglGetPbufferDCARB"));
		wglReleasePbufferDCARB   = reinterpret_cast<PFNWGLRELEASEPBUFFERDCARBPROC>	(wglGetProcAddress("wglReleasePbufferDCARB"));
		wglDestroyPbufferARB     = reinterpret_cast<PFNWGLDESTROYPBUFFERARBPROC>	(wglGetProcAddress("wglDestroyPbufferARB"));
		wglQueryPbufferARB	     = reinterpret_cast<PFNWGLQUERYPBUFFERARBPROC>		(wglGetProcAddress("wglQueryPbufferARB"));
		if (!wglCreatePbufferARB || !wglGetPbufferDCARB || !wglReleasePbufferDCARB || !wglDestroyPbufferARB ||
			!wglQueryPbufferARB) {
			PL_LOG(Info, "Couldn't use extension 'WGL_ARB_pbuffer'!")
			m_bWGL_ARB_pbuffer = false;
		} else {
			m_bWGL_ARB_pbuffer = true;
		}
	} else {
		m_bWGL_ARB_pbuffer = false;
	}

	// WGL_ARB_pixel_format
	if (IsSupported("WGL_ARB_pixel_format")) {
		wglGetPixelFormatAttribivARB = reinterpret_cast<PFNWGLGETPIXELFORMATATTRIBIVARBPROC>(wglGetProcAddress("wglGetPixelFormatAttribivARB"));
		wglGetPixelFormatAttribfvARB = reinterpret_cast<PFNWGLGETPIXELFORMATATTRIBFVARBPROC>(wglGetProcAddress("wglGetPixelFormatAttribfvARB"));
		wglChoosePixelFormatARB		 = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>		(wglGetProcAddress("wglChoosePixelFormatARB"));
		if (!wglGetPixelFormatAttribivARB || !wglGetPixelFormatAttribfvARB || !wglChoosePixelFormatARB) {
			PL_LOG(Info, "Couldn't use extension 'WGL_ARB_pixel_format'!")
			m_bWGL_ARB_pixel_format = false;
		} else {
			m_bWGL_ARB_pixel_format = true;
		}
	} else {
		m_bWGL_ARB_pixel_format = false;
	}

	// WGL_ARB_render_texture
	if (IsSupported("WGL_ARB_render_texture")) {
		wglBindTexImageARB	   = reinterpret_cast<PFNWGLBINDTEXIMAGEARBPROC>	(wglGetProcAddress("wglBindTexImageARB"));
		wglReleaseTexImageARB  = reinterpret_cast<PFNWGLRELEASETEXIMAGEARBPROC> (wglGetProcAddress("wglReleaseTexImageARB"));
		wglSetPbufferAttribARB = reinterpret_cast<PFNWGLSETPBUFFERATTRIBARBPROC>(wglGetProcAddress("wglSetPbufferAttribARB"));
		if (!wglBindTexImageARB || !wglReleaseTexImageARB || !wglSetPbufferAttribARB) {
			PL_LOG(Info, "Couldn't use extension 'WGL_ARB_render_texture'!")
			m_bWGL_ARB_render_texture = false;
		} else {
			m_bWGL_ARB_render_texture = true;
		}
	} else {
		m_bWGL_ARB_render_texture = false;
	}

	// WGL_ARB_make_current_read
	if (IsSupported("WGL_ARB_make_current_read")) {
		wglMakeContextCurrentARB = reinterpret_cast<PFNWGLMAKECONTEXTCURRENTARBPROC>(wglGetProcAddress("wglMakeContextCurrentARB"));
		wglGetCurrentReadDCARB   = reinterpret_cast<PFNWGLGETCURRENTREADDCARBPROC>  (wglGetProcAddress("wglGetCurrentReadDCARB"));
		if (!wglMakeContextCurrentARB || !wglGetCurrentReadDCARB) {
			PL_LOG(Info, "Couldn't use extension 'WGL_ARB_make_current_read'!")
			m_bWGL_ARB_make_current_read = false;
		} else {
			m_bWGL_ARB_make_current_read = true;
		}
	} else {
		m_bWGL_ARB_make_current_read = false;
	}

	// WGL_ARB_multisample
	m_bWGL_ARB_multisample = IsSupported("WGL_ARB_multisample");

	// WGL_ATI_pixel_format_float
	m_bWGL_ATI_pixel_format_float = IsSupported("WGL_ATI_pixel_format_float");

	// WGL_NV_float_buffer
	m_bWGL_NV_float_buffer = IsSupported("WGL_NV_float_buffer");


// EXT
	// GL_EXT_compiled_vertex_array
	if (IsSupported("GL_EXT_compiled_vertex_array")) {
		glLockArraysEXT   = reinterpret_cast<PFNGLLOCKARRAYSEXTPROC>  (wglGetProcAddress("glLockArraysEXT"));
		glUnlockArraysEXT = reinterpret_cast<PFNGLUNLOCKARRAYSEXTPROC>(wglGetProcAddress("glUnlockArraysEXT"));
		if (!glLockArraysEXT || !glUnlockArraysEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_compiled_vertex_array'!")
			m_bGL_EXT_compiled_vertex_array = false;
		} else {
			m_bGL_EXT_compiled_vertex_array = true;
		}
	} else {
		m_bGL_EXT_compiled_vertex_array = false;
	}

	// GL_EXT_draw_range_elements
	if (IsSupported("GL_EXT_draw_range_elements")) {
		glDrawRangeElementsEXT = reinterpret_cast<PFNGLDRAWRANGEELEMENTSEXTPROC>(wglGetProcAddress("glDrawRangeElementsEXT"));
		if (!glDrawRangeElementsEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_draw_range_elements'!")
			m_bGL_EXT_draw_range_elements = false;
		} else {
			m_bGL_EXT_draw_range_elements = true;
		}
	} else {
		m_bGL_EXT_draw_range_elements = false;
	}
	if (m_bGL_EXT_draw_range_elements) {	
		glGetIntegerv(GL_MAX_ELEMENTS_VERTICES_EXT, &m_nGL_MAX_ELEMENTS_VERTICES_EXT);
		glGetIntegerv(GL_MAX_ELEMENTS_INDICES_EXT,	&m_nGL_MAX_ELEMENTS_INDICES_EXT);
	} else {
		m_nGL_MAX_ELEMENTS_VERTICES_EXT = m_nGL_MAX_ELEMENTS_INDICES_EXT = 0;
	}

	// GL_EXT_fog_coord
	if (IsSupported("GL_EXT_fog_coord")) {
		glFogCoordfEXT		 = reinterpret_cast<PFNGLFOGCOORDFEXTPROC>		(wglGetProcAddress("glFogCoordfEXT"));
		glFogCoordfvEXT		 = reinterpret_cast<PFNGLFOGCOORDFVEXTPROC>		(wglGetProcAddress("glFogCoordfvEXT"));
		glFogCoorddEXT		 = reinterpret_cast<PFNGLFOGCOORDDEXTPROC>		(wglGetProcAddress("glFogCoorddEXT"));
		glFogCoorddvEXT		 = reinterpret_cast<PFNGLFOGCOORDDVEXTPROC>		(wglGetProcAddress("glFogCoorddvEXT"));
		glFogCoordPointerEXT = reinterpret_cast<PFNGLFOGCOORDPOINTEREXTPROC>(wglGetProcAddress("glFogCoordPointerEXT"));
		if (!glFogCoordfEXT || !glFogCoordfvEXT || !glFogCoorddEXT || !glFogCoorddvEXT || !glFogCoordPointerEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_fog_coord'!")
			m_bGL_EXT_fog_coord = false;
		} else {
			m_bGL_EXT_fog_coord = true;
		}
	} else {
		m_bGL_EXT_fog_coord = false;
	}

	// GL_EXT_secondary_color
	if (IsSupported("GL_EXT_secondary_color")) {
		glSecondaryColor3bEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3BEXTPROC>		(wglGetProcAddress("glSecondaryColor3bEXT"));
		glSecondaryColor3bvEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3BVEXTPROC>	(wglGetProcAddress("glSecondaryColor3bvEXT"));
		glSecondaryColor3dEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3DEXTPROC>		(wglGetProcAddress("glSecondaryColor3dEXT"));
		glSecondaryColor3dvEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3DVEXTPROC>	(wglGetProcAddress("glSecondaryColor3dvEXT"));
		glSecondaryColor3fEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3FEXTPROC>		(wglGetProcAddress("glSecondaryColor3fEXT"));
		glSecondaryColor3fvEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3FVEXTPROC>	(wglGetProcAddress("glSecondaryColor3fvEXT"));
		glSecondaryColor3iEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3IEXTPROC>		(wglGetProcAddress("glSecondaryColor3iEXT"));
		glSecondaryColor3ivEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3IVEXTPROC>	(wglGetProcAddress("glSecondaryColor3ivEXT"));
		glSecondaryColor3sEXT      = reinterpret_cast<PFNGLSECONDARYCOLOR3SEXTPROC>		(wglGetProcAddress("glSecondaryColor3sEXT"));
		glSecondaryColor3svEXT     = reinterpret_cast<PFNGLSECONDARYCOLOR3SVEXTPROC>	(wglGetProcAddress("glSecondaryColor3svEXT"));
		glSecondaryColor3ubEXT     = reinterpret_cast<PFNGLSECONDARYCOLOR3UBEXTPROC>	(wglGetProcAddress("glSecondaryColor3ubEXT"));
		glSecondaryColor3ubvEXT    = reinterpret_cast<PFNGLSECONDARYCOLOR3UBVEXTPROC>	(wglGetProcAddress("glSecondaryColor3ubvEXT"));
		glSecondaryColor3uiEXT     = reinterpret_cast<PFNGLSECONDARYCOLOR3UIEXTPROC>	(wglGetProcAddress("glSecondaryColor3uiEXT"));
		glSecondaryColor3uivEXT    = reinterpret_cast<PFNGLSECONDARYCOLOR3UIVEXTPROC>	(wglGetProcAddress("glSecondaryColor3uivEXT"));
		glSecondaryColor3usEXT     = reinterpret_cast<PFNGLSECONDARYCOLOR3USEXTPROC>	(wglGetProcAddress("glSecondaryColor3usEXT"));
		glSecondaryColor3usvEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3USVEXTPROC>	(wglGetProcAddress("glSecondaryColor3usvEXT"));
		glSecondaryColorPointerEXT = reinterpret_cast<PFNGLSECONDARYCOLORPOINTEREXTPROC>(wglGetProcAddress("glSecondaryColorPointerEXT"));
		if (!glSecondaryColor3bEXT || !glSecondaryColor3bvEXT || !glSecondaryColor3dEXT ||
			!glSecondaryColor3dvEXT || !glSecondaryColor3fEXT || !glSecondaryColor3fvEXT ||
			!glSecondaryColor3iEXT || !glSecondaryColor3ivEXT || !glSecondaryColor3sEXT ||
			!glSecondaryColor3svEXT || !glSecondaryColor3ubEXT || !glSecondaryColor3ubvEXT ||
			!glSecondaryColor3uiEXT || !glSecondaryColor3uivEXT || !glSecondaryColor3usEXT ||
			!glSecondaryColor3usvEXT || !glSecondaryColorPointerEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_secondary_color'!")
			m_bGL_EXT_secondary_color = false;
		} else {
			m_bGL_EXT_secondary_color = true;
		}
	} else {
		m_bGL_EXT_secondary_color = false;
	}

	// GL_EXT_texture_compression_s3tc
	m_bGL_EXT_texture_compression_s3tc = IsSupported("GL_EXT_texture_compression_s3tc");

	// GL_EXT_texture_compression_latc
	if (IsSupported("GL_EXT_texture_compression_latc"))
		m_bGL_EXT_texture_compression_latc = true;
	else
		m_bGL_EXT_texture_compression_latc = false;

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
		glTexImage3DEXT	   = reinterpret_cast<PFNGLTEXIMAGE3DEXTPROC>	(wglGetProcAddress("glTexImage3DEXT"));
		glTexSubImage3DEXT = reinterpret_cast<PFNGLTEXSUBIMAGE3DEXTPROC>(wglGetProcAddress("glTexSubImage3DEXT"));
		if (!glTexImage3DEXT || !glTexSubImage3DEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_texture3D'!")
			m_bGL_EXT_texture3D = false;
		} else {
			m_bGL_EXT_texture3D = true;
		}
	} else {
		m_bGL_EXT_texture3D = false;
	}

	// GL_EXT_texture_cube_map
	m_bGL_EXT_texture_cube_map = IsSupported("GL_EXT_texture_cube_map");

	// GL_EXT_stencil_wrap
	m_bGL_EXT_stencil_wrap = IsSupported("GL_EXT_stencil_wrap");

	// GL_EXT_stencil_two_side
	if (IsSupported("GL_EXT_stencil_two_side")) {
		glActiveStencilFaceEXT = reinterpret_cast<PFNGLACTIVESTENCILFACEEXTPROC>(wglGetProcAddress("glActiveStencilFaceEXT"));
		if (!glActiveStencilFaceEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_stencil_two_side'!")
			m_bGL_EXT_stencil_two_side = false;
		} else {
			m_bGL_EXT_stencil_two_side = true;
		}
	} else {
		m_bGL_EXT_stencil_two_side = false;
	}

	// GL_EXT_packed_depth_stencil
	m_bGL_EXT_packed_depth_stencil = IsSupported("GL_EXT_packed_depth_stencil");

	// GL_EXT_depth_bounds_test
	if (IsSupported("GL_EXT_depth_bounds_test")) {
		glDepthBoundsEXT = reinterpret_cast<PFNGLDEPTHBOUNDSEXTPROC>(wglGetProcAddress("glDepthBoundsEXT"));
		if (!glDepthBoundsEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_depth_bounds_test'!")
			m_bGL_EXT_depth_bounds_test = false;
		} else {
			m_bGL_EXT_depth_bounds_test = true;
		}
	} else {
		m_bGL_EXT_depth_bounds_test = false;
	}

	// GL_EXT_framebuffer_object
	if (IsSupported("GL_EXT_framebuffer_object")) {
		glIsRenderbufferEXT						 = reinterpret_cast<PFNGLISRENDERBUFFEREXTPROC>						(wglGetProcAddress("glIsRenderbufferEXT"));
		glBindRenderbufferEXT					 = reinterpret_cast<PFNGLBINDRENDERBUFFEREXTPROC>					(wglGetProcAddress("glBindRenderbufferEXT"));
		glDeleteRenderbuffersEXT				 = reinterpret_cast<PFNGLDELETERENDERBUFFERSEXTPROC>				(wglGetProcAddress("glDeleteRenderbuffersEXT"));
		glGenRenderbuffersEXT					 = reinterpret_cast<PFNGLGENRENDERBUFFERSEXTPROC>					(wglGetProcAddress("glGenRenderbuffersEXT"));
		glRenderbufferStorageEXT				 = reinterpret_cast<PFNGLRENDERBUFFERSTORAGEEXTPROC>				(wglGetProcAddress("glRenderbufferStorageEXT"));
		glGetRenderbufferParameterivEXT			 = reinterpret_cast<PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC>			(wglGetProcAddress("glGetRenderbufferParameterivEXT"));
		glIsFramebufferEXT						 = reinterpret_cast<PFNGLISFRAMEBUFFEREXTPROC>						(wglGetProcAddress("glIsFramebufferEXT"));
		glBindFramebufferEXT					 = reinterpret_cast<PFNGLBINDFRAMEBUFFEREXTPROC>					(wglGetProcAddress("glBindFramebufferEXT"));
		glDeleteFramebuffersEXT					 = reinterpret_cast<PFNGLDELETEFRAMEBUFFERSEXTPROC>					(wglGetProcAddress("glDeleteFramebuffersEXT"));
		glGenFramebuffersEXT					 = reinterpret_cast<PFNGLGENFRAMEBUFFERSEXTPROC>					(wglGetProcAddress("glGenFramebuffersEXT"));
		glCheckFramebufferStatusEXT				 = reinterpret_cast<PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC>				(wglGetProcAddress("glCheckFramebufferStatusEXT"));
		glFramebufferTexture1DEXT				 = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE1DEXTPROC>				(wglGetProcAddress("glFramebufferTexture1DEXT"));
		glFramebufferTexture2DEXT				 = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE2DEXTPROC>				(wglGetProcAddress("glFramebufferTexture2DEXT"));
		glFramebufferTexture3DEXT				 = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE3DEXTPROC>				(wglGetProcAddress("glFramebufferTexture3DEXT"));
		glFramebufferRenderbufferEXT			 = reinterpret_cast<PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC>			(wglGetProcAddress("glFramebufferRenderbufferEXT"));
		glGetFramebufferAttachmentParameterivEXT = reinterpret_cast<PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC>(wglGetProcAddress("glGetFramebufferAttachmentParameterivEXT"));
		glGenerateMipmapEXT						 = reinterpret_cast<PFNGLGENERATEMIPMAPEXTPROC>						(wglGetProcAddress("glGenerateMipmapEXT"));
		if (!glIsRenderbufferEXT || !glBindRenderbufferEXT || !glDeleteRenderbuffersEXT || !glGenRenderbuffersEXT ||
			!glRenderbufferStorageEXT || !glGetRenderbufferParameterivEXT || !glIsFramebufferEXT ||
			!glBindFramebufferEXT || !glDeleteFramebuffersEXT || !glGenFramebuffersEXT || !glCheckFramebufferStatusEXT ||
			!glFramebufferTexture1DEXT || !glFramebufferTexture2DEXT || !glFramebufferTexture3DEXT ||
			!glFramebufferRenderbufferEXT || !glGetFramebufferAttachmentParameterivEXT || !glGenerateMipmapEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_framebuffer_object'!")
			m_bGL_EXT_framebuffer_object = false;
		} else {
			m_bGL_EXT_framebuffer_object = true;
		}
	} else {
		m_bGL_EXT_framebuffer_object = false;
	}

	// GL_EXT_framebuffer_multisample
	if (IsSupported("GL_EXT_framebuffer_multisample")) {
		glRenderbufferStorageMultisampleEXT = reinterpret_cast<PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC>(wglGetProcAddress("glRenderbufferStorageMultisampleEXT"));
		if (!glRenderbufferStorageMultisampleEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_framebuffer_multisample'!")
			m_bGL_EXT_framebuffer_multisample = false;
		} else {
			m_bGL_EXT_framebuffer_multisample = true;
		}
	} else {
		m_bGL_EXT_framebuffer_multisample = false;
	}

	// GL_EXT_framebuffer_blit
	if (IsSupported("GL_EXT_framebuffer_blit")) {
		glBlitFramebufferEXT = reinterpret_cast<PFNGLBLITFRAMEBUFFEREXTPROC>(wglGetProcAddress("glBlitFramebufferEXT"));
		if (!glBlitFramebufferEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_framebuffer_blit'!")
			m_bGL_EXT_framebuffer_blit = false;
		} else {
			m_bGL_EXT_framebuffer_blit = true;
		}
	} else {
		m_bGL_EXT_framebuffer_blit = false;
	}

	// GL_EXT_geometry_shader4
	if (IsSupported("GL_EXT_geometry_shader4")) {
		glProgramParameteriEXT = reinterpret_cast<PFNGLPROGRAMPARAMETERIEXTPROC>(wglGetProcAddress("glProgramParameteriEXT"));
		if (!glProgramParameteriEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_geometry_shader4'!")
			m_bGL_EXT_geometry_shader4 = false;
		} else {
			m_bGL_EXT_geometry_shader4 = true;
		}
	} else {
		m_bGL_EXT_geometry_shader4 = false;
	}


// ARB
	// GL_ARB_texture_float
	m_bGL_ARB_texture_float = IsSupported("GL_ARB_texture_float");

	// GL_ARB_color_buffer_float
	if (IsSupported("GL_ARB_color_buffer_float")) {
		glClampColorARB = reinterpret_cast<PFNGLCLAMPCOLORARBPROC>(wglGetProcAddress("glClampColorARB"));
		if (!glClampColorARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_color_buffer_float'!")
			m_bGL_ARB_color_buffer_float = false;
		} else {
			m_bGL_ARB_color_buffer_float = true;
		}
	} else {
		m_bGL_ARB_color_buffer_float = false;
	}

	// GL_ARB_multitexture
	if (IsSupported("GL_ARB_multitexture")) {
		glActiveTextureARB		 = reinterpret_cast<PFNGLACTIVETEXTUREARBPROC> 		(wglGetProcAddress("glActiveTextureARB"));
		glClientActiveTextureARB = reinterpret_cast<PFNGLCLIENTACTIVETEXTUREARBPROC>(wglGetProcAddress("glClientActiveTextureARB"));
		glMultiTexCoord1dARB	 = reinterpret_cast<PFNGLMULTITEXCOORD1DARBPROC> 	(wglGetProcAddress("glMultiTexCoord1dARB"));
		glMultiTexCoord1dvARB	 = reinterpret_cast<PFNGLMULTITEXCOORD1DVARBPROC> 	(wglGetProcAddress("glMultiTexCoord1dvARB"));
		glMultiTexCoord1fARB	 = reinterpret_cast<PFNGLMULTITEXCOORD1FARBPROC> 	(wglGetProcAddress("glMultiTexCoord1fARB"));
		glMultiTexCoord1fvARB	 = reinterpret_cast<PFNGLMULTITEXCOORD1FVARBPROC> 	(wglGetProcAddress("glMultiTexCoord1fvARB"));
		glMultiTexCoord1iARB	 = reinterpret_cast<PFNGLMULTITEXCOORD1IARBPROC> 	(wglGetProcAddress("glMultiTexCoord1iARB"));
		glMultiTexCoord1ivARB	 = reinterpret_cast<PFNGLMULTITEXCOORD1IVARBPROC> 	(wglGetProcAddress("glMultiTexCoord1ivARB"));
		glMultiTexCoord1sARB	 = reinterpret_cast<PFNGLMULTITEXCOORD1SARBPROC> 	(wglGetProcAddress("glMultiTexCoord1sARB"));
		glMultiTexCoord1svARB	 = reinterpret_cast<PFNGLMULTITEXCOORD1SVARBPROC> 	(wglGetProcAddress("glMultiTexCoord1svARB"));
		glMultiTexCoord2dARB	 = reinterpret_cast<PFNGLMULTITEXCOORD2DARBPROC> 	(wglGetProcAddress("glMultiTexCoord2dARB"));
		glMultiTexCoord2dvARB	 = reinterpret_cast<PFNGLMULTITEXCOORD2DVARBPROC> 	(wglGetProcAddress("glMultiTexCoord2dvARB"));
		glMultiTexCoord2fARB	 = reinterpret_cast<PFNGLMULTITEXCOORD2FARBPROC> 	(wglGetProcAddress("glMultiTexCoord2fARB"));
		glMultiTexCoord2fvARB	 = reinterpret_cast<PFNGLMULTITEXCOORD2FVARBPROC> 	(wglGetProcAddress("glMultiTexCoord2fvARB"));
		glMultiTexCoord2iARB	 = reinterpret_cast<PFNGLMULTITEXCOORD2IARBPROC> 	(wglGetProcAddress("glMultiTexCoord2iARB"));
		glMultiTexCoord2ivARB	 = reinterpret_cast<PFNGLMULTITEXCOORD2IVARBPROC> 	(wglGetProcAddress("glMultiTexCoord2ivARB"));
		glMultiTexCoord2sARB	 = reinterpret_cast<PFNGLMULTITEXCOORD2SARBPROC> 	(wglGetProcAddress("glMultiTexCoord2sARB"));
		glMultiTexCoord2svARB	 = reinterpret_cast<PFNGLMULTITEXCOORD2SVARBPROC> 	(wglGetProcAddress("glMultiTexCoord2svARB"));
		glMultiTexCoord3dARB	 = reinterpret_cast<PFNGLMULTITEXCOORD3DARBPROC> 	(wglGetProcAddress("glMultiTexCoord3dARB"));
		glMultiTexCoord3dvARB	 = reinterpret_cast<PFNGLMULTITEXCOORD3DVARBPROC> 	(wglGetProcAddress("glMultiTexCoord3dvARB"));
		glMultiTexCoord3fARB	 = reinterpret_cast<PFNGLMULTITEXCOORD3FARBPROC> 	(wglGetProcAddress("glMultiTexCoord3fARB"));
		glMultiTexCoord3fvARB	 = reinterpret_cast<PFNGLMULTITEXCOORD3FVARBPROC> 	(wglGetProcAddress("glMultiTexCoord3fvARB"));
		glMultiTexCoord3iARB	 = reinterpret_cast<PFNGLMULTITEXCOORD3IARBPROC> 	(wglGetProcAddress("glMultiTexCoord3iARB"));
		glMultiTexCoord3ivARB	 = reinterpret_cast<PFNGLMULTITEXCOORD3IVARBPROC> 	(wglGetProcAddress("glMultiTexCoord3ivARB"));
		glMultiTexCoord3sARB	 = reinterpret_cast<PFNGLMULTITEXCOORD3SARBPROC> 	(wglGetProcAddress("glMultiTexCoord3sARB"));
		glMultiTexCoord3svARB	 = reinterpret_cast<PFNGLMULTITEXCOORD3SVARBPROC> 	(wglGetProcAddress("glMultiTexCoord3svARB"));
		glMultiTexCoord4dARB	 = reinterpret_cast<PFNGLMULTITEXCOORD4DARBPROC> 	(wglGetProcAddress("glMultiTexCoord4dARB"));
		glMultiTexCoord4dvARB	 = reinterpret_cast<PFNGLMULTITEXCOORD4DVARBPROC> 	(wglGetProcAddress("glMultiTexCoord4dvARB"));
		glMultiTexCoord4fARB	 = reinterpret_cast<PFNGLMULTITEXCOORD4FARBPROC> 	(wglGetProcAddress("glMultiTexCoord4fARB"));
		glMultiTexCoord4fvARB	 = reinterpret_cast<PFNGLMULTITEXCOORD4FVARBPROC> 	(wglGetProcAddress("glMultiTexCoord4fvARB"));
		glMultiTexCoord4iARB	 = reinterpret_cast<PFNGLMULTITEXCOORD4IARBPROC> 	(wglGetProcAddress("glMultiTexCoord4iARB"));
		glMultiTexCoord4ivARB	 = reinterpret_cast<PFNGLMULTITEXCOORD4IVARBPROC> 	(wglGetProcAddress("glMultiTexCoord4ivARB"));
		glMultiTexCoord4sARB	 = reinterpret_cast<PFNGLMULTITEXCOORD4SARBPROC> 	(wglGetProcAddress("glMultiTexCoord4sARB"));
		glMultiTexCoord4svARB	 = reinterpret_cast<PFNGLMULTITEXCOORD4SVARBPROC> 	(wglGetProcAddress("glMultiTexCoord4svARB"));
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
		} else {
			m_bGL_ARB_multitexture = true;
		}
	} else {
		m_bGL_ARB_multitexture = false;
	}

	// GL_ARB_vertex_buffer_object
	if (IsSupported("GL_ARB_vertex_buffer_object")) {
		glBindBufferARB			  = reinterpret_cast<PFNGLBINDBUFFERARBPROC>		  (wglGetProcAddress("glBindBufferARB"));
		glDeleteBuffersARB		  = reinterpret_cast<PFNGLDELETEBUFFERSARBPROC>		  (wglGetProcAddress("glDeleteBuffersARB"));
		glGenBuffersARB			  = reinterpret_cast<PFNGLGENBUFFERSARBPROC>		  (wglGetProcAddress("glGenBuffersARB"));
		glBufferDataARB			  = reinterpret_cast<PFNGLBUFFERDATAARBPROC>		  (wglGetProcAddress("glBufferDataARB"));
		glBufferSubDataARB		  = reinterpret_cast<PFNGLBUFFERSUBDATAARBPROC>		  (wglGetProcAddress("glBufferSubDataARB"));
		glGetBufferSubDataARB	  = reinterpret_cast<PFNGLGETBUFFERSUBDATAARBPROC>	  (wglGetProcAddress("glGetBufferSubDataARB"));
		glMapBufferARB			  = reinterpret_cast<PFNGLMAPBUFFERARBPROC>			  (wglGetProcAddress("glMapBufferARB"));
		glUnmapBufferARB		  = reinterpret_cast<PFNGLUNMAPBUFFERARBPROC>		  (wglGetProcAddress("glUnmapBufferARB"));
		glGetBufferParameterivARB = reinterpret_cast<PFNGLGETBUFFERPARAMETERIVARBPROC>(wglGetProcAddress("glGetBufferParameterivARB"));
		glGetBufferPointervARB	  = reinterpret_cast<PFNGLGETBUFFERPOINTERVARBPROC>	  (wglGetProcAddress("glGetBufferPointervARB"));
		if (!glBindBufferARB || !glDeleteBuffersARB || !glGenBuffersARB ||
			!glBufferDataARB || !glBufferSubDataARB || !glGetBufferSubDataARB || !glMapBufferARB ||
			!glUnmapBufferARB || !glGetBufferParameterivARB || !glGetBufferPointervARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_vertex_buffer_object'!")
			m_bGL_ARB_vertex_buffer_object = false;
		} else {
			m_bGL_ARB_vertex_buffer_object = true;
		}
	} else {
		m_bGL_ARB_vertex_buffer_object = false;
	}

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
		glGenQueriesARB	       = reinterpret_cast<PFNGLGENQUERIESARBPROC>		(wglGetProcAddress("glGenQueriesARB"));
		glDeleteQueriesARB     = reinterpret_cast<PFNGLDELETEQUERIESARBPROC>	(wglGetProcAddress("glDeleteQueriesARB"));
		glIsQueryARB	       = reinterpret_cast<PFNGLISQUERYARBPROC>			(wglGetProcAddress("glIsQueryARB"));
		glBeginQueryARB	       = reinterpret_cast<PFNGLBEGINQUERYARBPROC>		(wglGetProcAddress("glBeginQueryARB"));
		glEndQueryARB	       = reinterpret_cast<PFNGLENDQUERYARBPROC>			(wglGetProcAddress("glEndQueryARB"));
		glGetQueryivARB		   = reinterpret_cast<PFNGLGETQUERYIVARBPROC>		(wglGetProcAddress("glGetQueryivARB"));
		glGetQueryObjectivARB  = reinterpret_cast<PFNGLGETQUERYOBJECTIVARBPROC>	(wglGetProcAddress("glGetQueryObjectivARB"));
		glGetQueryObjectuivARB = reinterpret_cast<PFNGLGETQUERYOBJECTUIVARBPROC>(wglGetProcAddress("glGetQueryObjectuivARB"));
		if (!glGenQueriesARB || !glDeleteQueriesARB || !glIsQueryARB || !glBeginQueryARB ||
			!glEndQueryARB || !glGetQueryivARB || !glGetQueryObjectivARB || !glGetQueryObjectuivARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_occlusion_query'!")
			m_bGL_ARB_occlusion_query = false;
		} else {
			m_bGL_ARB_occlusion_query = true;
		}
	} else {
		m_bGL_ARB_occlusion_query = false;
	}

	// GL_ARB_texture_compression
	if (IsSupported("GL_ARB_texture_compression")) {
		glCompressedTexImage3DARB    = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE3DARBPROC>    (wglGetProcAddress("glCompressedTexImage3DARB"));
		glCompressedTexImage2DARB    = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE2DARBPROC>    (wglGetProcAddress("glCompressedTexImage2DARB"));
		glCompressedTexImage1DARB    = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE1DARBPROC>    (wglGetProcAddress("glCompressedTexImage1DARB"));
		glCompressedTexSubImage3DARB = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC> (wglGetProcAddress("glCompressedTexSubImage3DARB"));
		glCompressedTexSubImage2DARB = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC> (wglGetProcAddress("glCompressedTexSubImage2DARB"));
		glCompressedTexSubImage1DARB = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC> (wglGetProcAddress("glCompressedTexSubImage1DARB"));
		glGetCompressedTexImageARB   = reinterpret_cast<PFNGLGETCOMPRESSEDTEXIMAGEARBPROC>   (wglGetProcAddress("glGetCompressedTexImageARB"));
		if (!glCompressedTexImage3DARB || !glCompressedTexImage2DARB || !glCompressedTexImage1DARB ||
			!glCompressedTexSubImage3DARB || !glCompressedTexSubImage2DARB ||
			!glCompressedTexSubImage1DARB || !glGetCompressedTexImageARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_texture_compression'!")
			m_bGL_ARB_texture_compression = false;
		} else {
			m_bGL_ARB_texture_compression = true;
		}
	} else {
		m_bGL_ARB_texture_compression = false;
	}

	// GL_ARB_depth_texture
	m_bGL_ARB_depth_texture = IsSupported("GL_ARB_depth_texture");

	// GL_ARB_point_sprite
	m_bGL_ARB_point_sprite = IsSupported("GL_ARB_point_sprite");

	// GL_ARB_point_parameters
	if (IsSupported("GL_ARB_point_parameters")) {
		glPointParameterfARB  = reinterpret_cast<PFNGLPOINTPARAMETERFARBPROC> (wglGetProcAddress("glPointParameterfARB"));
		glPointParameterfvARB = reinterpret_cast<PFNGLPOINTPARAMETERFVARBPROC>(wglGetProcAddress("glPointParameterfvARB"));
		if (!glPointParameterfARB || !glPointParameterfvARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_point_parameters'!")
			m_bGL_ARB_point_parameters = false;
		} else {
			m_bGL_ARB_point_parameters = true;
		}
	} else {
		m_bGL_ARB_point_parameters = false;
	}

	// GL_ARB_shading_language_100
	m_bGL_ARB_shading_language_100 = IsSupported("GL_ARB_shading_language_100");

	// GL_ARB_vertex_program
	if (IsSupported("GL_ARB_vertex_program")) {
		glVertexAttribPointerARB      = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERARBPROC>      (wglGetProcAddress("glVertexAttribPointerARB"));
		glEnableVertexAttribArrayARB  = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYARBPROC>  (wglGetProcAddress("glEnableVertexAttribArrayARB"));
		glDisableVertexAttribArrayARB = reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYARBPROC> (wglGetProcAddress("glDisableVertexAttribArrayARB"));
		glGetProgramivARB			  = reinterpret_cast<PFNGLGETPROGRAMIVARBPROC>			   (wglGetProcAddress("glGetProgramivARB"));
		if (!glVertexAttribPointerARB || !glEnableVertexAttribArrayARB || !glDisableVertexAttribArrayARB ||
			!glGetProgramivARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_vertex_program'!")
			m_bGL_ARB_vertex_program = false;
		} else {
			m_bGL_ARB_vertex_program = true;
		}
	} else {
		m_bGL_ARB_vertex_program = false;
	}

	// GL_ARB_fragment_program
	if (IsSupported("GL_ARB_fragment_program")) {
		// At the moment we do not need any of the functions this extension provides
		m_bGL_ARB_fragment_program = true;
	} else {
		m_bGL_ARB_fragment_program = false;
	}

	// GL_ARB_draw_buffers
	if (IsSupported("GL_ARB_draw_buffers")) {
		glDrawBuffersARB = reinterpret_cast<PFNGLDRAWBUFFERSARBPROC>(wglGetProcAddress("glDrawBuffersARB"));
		if (!glDrawBuffersARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_draw_buffers'!")
			m_bGL_ARB_draw_buffers = false;
		} else {
			m_bGL_ARB_draw_buffers = true;
		}
	} else {
		m_bGL_ARB_draw_buffers = false;
	}

	// GL_ARB_shader_objects
	if (IsSupported("GL_ARB_shader_objects")) {
		glDeleteObjectARB			= reinterpret_cast<PFNGLDELETEOBJECTARBPROC>			(wglGetProcAddress("glDeleteObjectARB"));
		glGetHandleARB				= reinterpret_cast<PFNGLGETHANDLEARBPROC>				(wglGetProcAddress("glGetHandleARB"));
		glDetachObjectARB			= reinterpret_cast<PFNGLDETACHOBJECTARBPROC>			(wglGetProcAddress("glDetachObjectARB"));
		glCreateShaderObjectARB		= reinterpret_cast<PFNGLCREATESHADEROBJECTARBPROC>		(wglGetProcAddress("glCreateShaderObjectARB"));
		glShaderSourceARB			= reinterpret_cast<PFNGLSHADERSOURCEARBPROC>			(wglGetProcAddress("glShaderSourceARB"));
		glCompileShaderARB			= reinterpret_cast<PFNGLCOMPILESHADERARBPROC>			(wglGetProcAddress("glCompileShaderARB"));
		glCreateProgramObjectARB	= reinterpret_cast<PFNGLCREATEPROGRAMOBJECTARBPROC>		(wglGetProcAddress("glCreateProgramObjectARB"));
		glAttachObjectARB			= reinterpret_cast<PFNGLATTACHOBJECTARBPROC>			(wglGetProcAddress("glAttachObjectARB"));
		glLinkProgramARB			= reinterpret_cast<PFNGLLINKPROGRAMARBPROC>				(wglGetProcAddress("glLinkProgramARB"));
		glUseProgramObjectARB		= reinterpret_cast<PFNGLUSEPROGRAMOBJECTARBPROC>		(wglGetProcAddress("glUseProgramObjectARB"));
		glValidateProgramARB		= reinterpret_cast<PFNGLVALIDATEPROGRAMARBPROC>			(wglGetProcAddress("glValidateProgramARB"));
		glUniform1fARB				= reinterpret_cast<PFNGLUNIFORM1FARBPROC>				(wglGetProcAddress("glUniform1fARB"));
		glUniform2fARB				= reinterpret_cast<PFNGLUNIFORM2FARBPROC>				(wglGetProcAddress("glUniform2fARB"));
		glUniform3fARB				= reinterpret_cast<PFNGLUNIFORM3FARBPROC>				(wglGetProcAddress("glUniform3fARB"));
		glUniform4fARB				= reinterpret_cast<PFNGLUNIFORM4FARBPROC>				(wglGetProcAddress("glUniform4fARB"));
		glUniform1iARB				= reinterpret_cast<PFNGLUNIFORM1IARBPROC>				(wglGetProcAddress("glUniform1iARB"));
		glUniform2iARB				= reinterpret_cast<PFNGLUNIFORM2IARBPROC>				(wglGetProcAddress("glUniform2iARB"));
		glUniform3iARB				= reinterpret_cast<PFNGLUNIFORM3IARBPROC>				(wglGetProcAddress("glUniform3iARB"));
		glUniform4iARB				= reinterpret_cast<PFNGLUNIFORM4IARBPROC>				(wglGetProcAddress("glUniform4iARB"));
		glUniform1fvARB				= reinterpret_cast<PFNGLUNIFORM1FVARBPROC>				(wglGetProcAddress("glUniform1fvARB"));
		glUniform2fvARB				= reinterpret_cast<PFNGLUNIFORM2FVARBPROC>				(wglGetProcAddress("glUniform2fvARB"));
		glUniform3fvARB				= reinterpret_cast<PFNGLUNIFORM3FVARBPROC>				(wglGetProcAddress("glUniform3fvARB"));
		glUniform4fvARB				= reinterpret_cast<PFNGLUNIFORM4FVARBPROC>				(wglGetProcAddress("glUniform4fvARB"));
		glUniform1ivARB				= reinterpret_cast<PFNGLUNIFORM1IVARBPROC>				(wglGetProcAddress("glUniform1ivARB"));
		glUniform2ivARB				= reinterpret_cast<PFNGLUNIFORM2IVARBPROC>				(wglGetProcAddress("glUniform2ivARB"));
		glUniform3ivARB				= reinterpret_cast<PFNGLUNIFORM3IVARBPROC>				(wglGetProcAddress("glUniform3ivARB"));
		glUniform4ivARB				= reinterpret_cast<PFNGLUNIFORM4IVARBPROC>				(wglGetProcAddress("glUniform4ivARB"));
		glUniformMatrix2fvARB		= reinterpret_cast<PFNGLUNIFORMMATRIX2FVARBPROC>		(wglGetProcAddress("glUniformMatrix2fvARB"));
		glUniformMatrix3fvARB		= reinterpret_cast<PFNGLUNIFORMMATRIX3FVARBPROC>		(wglGetProcAddress("glUniformMatrix3fvARB"));
		glUniformMatrix4fvARB		= reinterpret_cast<PFNGLUNIFORMMATRIX4FVARBPROC>		(wglGetProcAddress("glUniformMatrix4fvARB"));
		glGetObjectParameterfvARB	= reinterpret_cast<PFNGLGETOBJECTPARAMETERFVARBPROC>	(wglGetProcAddress("glGetObjectParameterfvARB"));
		glGetObjectParameterivARB	= reinterpret_cast<PFNGLGETOBJECTPARAMETERIVARBPROC>	(wglGetProcAddress("glGetObjectParameterivARB"));
		glGetInfoLogARB				= reinterpret_cast<PFNGLGETINFOLOGARBPROC>				(wglGetProcAddress("glGetInfoLogARB"));
		glGetAttachedObjectsARB		= reinterpret_cast<PFNGLGETATTACHEDOBJECTSARBPROC>		(wglGetProcAddress("glGetAttachedObjectsARB"));
		glGetUniformLocationARB		= reinterpret_cast<PFNGLGETUNIFORMLOCATIONARBPROC>		(wglGetProcAddress("glGetUniformLocationARB"));
		glGetActiveUniformARB		= reinterpret_cast<PFNGLGETACTIVEUNIFORMARBPROC>		(wglGetProcAddress("glGetActiveUniformARB"));
		glGetUniformfvARB			= reinterpret_cast<PFNGLGETUNIFORMFVARBPROC>			(wglGetProcAddress("glGetUniformfvARB"));
		glGetUniformivARB			= reinterpret_cast<PFNGLGETUNIFORMIVARBPROC>			(wglGetProcAddress("glGetUniformivARB"));
		glGetShaderSourceARB		= reinterpret_cast<PFNGLGETSHADERSOURCEARBPROC>			(wglGetProcAddress("glGetShaderSourceARB"));
		if (!glDeleteObjectARB || !glGetHandleARB || !glDetachObjectARB || !glCreateShaderObjectARB || !glShaderSourceARB || !glCompileShaderARB ||
			!glCreateProgramObjectARB || !glAttachObjectARB || !glLinkProgramARB || !glUseProgramObjectARB || !glValidateProgramARB || !glUniform1fARB ||
			!glUniform2fARB || !glUniform3fARB || !glUniform4fARB || !glUniform1iARB || !glUniform2iARB || !glUniform3iARB || !glUniform4iARB || !glUniform1fvARB ||
			!glUniform2fvARB || !glUniform3fvARB || !glUniform4fvARB || !glUniform1ivARB || !glUniform2ivARB || !glUniform3ivARB || !glUniform4ivARB || !glUniformMatrix2fvARB ||
			!glUniformMatrix3fvARB || !glUniformMatrix4fvARB || !glGetObjectParameterfvARB || !glGetObjectParameterivARB || !glGetInfoLogARB || !glGetAttachedObjectsARB ||
			!glGetUniformLocationARB || !glGetActiveUniformARB || !glGetUniformfvARB || !glGetUniformivARB || !glGetShaderSourceARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_shader_objects'!")
			m_bGL_ARB_shader_objects = false;
		} else {
			m_bGL_ARB_shader_objects = true;
		}
	} else {
		m_bGL_ARB_shader_objects = false;
	}

	// GL_ARB_vertex_shader
	if (IsSupported("GL_ARB_vertex_shader")) {
		glBindAttribLocationARB = reinterpret_cast<PFNGLBINDATTRIBLOCATIONARBPROC> (wglGetProcAddress("glBindAttribLocationARB"));
		glGetActiveAttribARB    = reinterpret_cast<PFNGLGETACTIVEATTRIBARBPROC>    (wglGetProcAddress("glGetActiveAttribARB"));
		glGetAttribLocationARB  = reinterpret_cast<PFNGLGETATTRIBLOCATIONARBPROC>  (wglGetProcAddress("glGetAttribLocationARB"));
		if (!glBindAttribLocationARB || !glGetActiveAttribARB || !glGetAttribLocationARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_vertex_shader'!")
			m_bGL_ARB_vertex_shader = false;
		} else {
			m_bGL_ARB_vertex_shader = true;
		}
	} else {
		m_bGL_ARB_vertex_shader = false;
	}

	// GL_ARB_get_program_binary
	if (IsSupported("GL_ARB_get_program_binary")) {
		glGetProgramBinary  = reinterpret_cast<PFNGLGETPROGRAMBINARYPROC> (wglGetProcAddress("glGetProgramBinary"));
		glProgramBinary     = reinterpret_cast<PFNGLPROGRAMBINARYPROC>    (wglGetProcAddress("glProgramBinary"));
		glProgramParameteri = reinterpret_cast<PFNGLPROGRAMPARAMETERIPROC>(wglGetProcAddress("glProgramParameteri"));
		if (!glGetProgramBinary || !glProgramBinary || !glProgramParameteri) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_get_program_binary'!")
			m_bGL_ARB_get_program_binary = false;
		} else {
			m_bGL_ARB_get_program_binary = true;
		}
	} else {
		m_bGL_ARB_get_program_binary = false;
	}

	// GL_ARB_texture_rectangle
	m_bGL_ARB_texture_rectangle = IsSupported("GL_ARB_texture_rectangle");

	// GL_ARB_multisample
	m_bGL_ARB_multisample = IsSupported("GL_ARB_multisample");


// ATI
	// GL_ATI_separate_stencil 
	if (IsSupported("GL_ATI_separate_stencil")) {
		glStencilOpSeparateATI   = reinterpret_cast<PFNGLSTENCILOPSEPARATEATIPROC>	(wglGetProcAddress("glStencilOpSeparateATI"));
		glStencilFuncSeparateATI = reinterpret_cast<PFNGLSTENCILFUNCSEPARATEATIPROC>(wglGetProcAddress("glStencilFuncSeparateATI"));
		if (!glStencilOpSeparateATI || !glStencilFuncSeparateATI) {
			PL_LOG(Info, "Couldn't use extension 'GL_ATI_separate_stencil'!")
			m_bGL_ATI_separate_stencil = false;
		} else {
			m_bGL_ATI_separate_stencil = true;
		}
	} else {
		m_bGL_ATI_separate_stencil = false;
	}

	// GL_ATI_draw_buffers
	if (IsSupported("GL_ATI_draw_buffers")) {
		glDrawBuffersATI = reinterpret_cast<PFNGLDRAWBUFFERSATIPROC>(wglGetProcAddress("glDrawBuffersATI"));
		if (!glDrawBuffersATI) {
			PL_LOG(Info, "Couldn't use extension 'GL_ATI_draw_buffers'!")
			m_bGL_ATI_draw_buffers = false;
		} else {
			m_bGL_ATI_draw_buffers = true;
		}
	} else {
		m_bGL_ATI_draw_buffers = false;
	}

	// GL_ATI_texture_compression_3dc
	if (IsSupported("GL_ATI_texture_compression_3dc")) {
		m_bGL_ATI_texture_compression_3dc = true;
	} else {
		m_bGL_ATI_texture_compression_3dc = false;
	}


// AMD
	// GL_AMD_vertex_shader_tessellator
	if (IsSupported("GL_AMD_vertex_shader_tessellator")) {
		glTessellationFactorAMD = reinterpret_cast<PFNGLTESSELLATIONFACTORAMDPROC>(wglGetProcAddress("glTessellationFactorAMD"));
		glTessellationModeAMD   = reinterpret_cast<PFNGLTESSELLATIONMODEAMDPROC>  (wglGetProcAddress("glTessellationModeAMD"));
		if (!glTessellationFactorAMD || !glTessellationModeAMD) {
			PL_LOG(Info, "Couldn't use extension 'GL_AMD_vertex_shader_tessellator'!")
			m_bGL_AMD_vertex_shader_tessellator = false;
		} else {
			m_bGL_AMD_vertex_shader_tessellator = true;
		}
	} else {
		m_bGL_AMD_vertex_shader_tessellator = false;
	}


// NV
	// GL_NV_texture_rectangle
	m_bGL_NV_texture_rectangle = IsSupported("GL_NV_texture_rectangle");

	// GL_NV_occlusion_query
	if (IsSupported("GL_NV_occlusion_query")) {
		glGenOcclusionQueriesNV	   = reinterpret_cast<PFNGLGENOCCLUSIONQUERIESNVPROC>	 (wglGetProcAddress("glGenOcclusionQueriesNV"));
		glDeleteOcclusionQueriesNV = reinterpret_cast<PFNGLDELETEOCCLUSIONQUERIESNVPROC> (wglGetProcAddress("glDeleteOcclusionQueriesNV"));
		glIsOcclusionQueryNV	   = reinterpret_cast<PFNGLISOCCLUSIONQUERYNVPROC>		 (wglGetProcAddress("glIsOcclusionQueryNV"));
		glBeginOcclusionQueryNV	   = reinterpret_cast<PFNGLBEGINOCCLUSIONQUERYNVPROC>	 (wglGetProcAddress("glBeginOcclusionQueryNV"));
		glEndOcclusionQueryNV	   = reinterpret_cast<PFNGLENDOCCLUSIONQUERYNVPROC>		 (wglGetProcAddress("glEndOcclusionQueryNV"));
		glGetOcclusionQueryivNV	   = reinterpret_cast<PFNGLGETOCCLUSIONQUERYIVNVPROC>	 (wglGetProcAddress("glGetOcclusionQueryivNV"));
		glGetOcclusionQueryuivNV   = reinterpret_cast<PFNGLGETOCCLUSIONQUERYUIVNVPROC>	 (wglGetProcAddress("glGetOcclusionQueryuivNV"));
		if (!glGenOcclusionQueriesNV || !glDeleteOcclusionQueriesNV || !glIsOcclusionQueryNV || !glBeginOcclusionQueryNV ||
			!glEndOcclusionQueryNV || !glGetOcclusionQueryivNV || !glGetOcclusionQueryuivNV) {
			m_bGL_NV_occlusion_query = false;
		} else {
			m_bGL_NV_occlusion_query = true;
		}
	} else {
		m_bGL_NV_occlusion_query = false;
	}


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
