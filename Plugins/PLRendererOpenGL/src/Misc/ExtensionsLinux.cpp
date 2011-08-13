/*********************************************************\
 *  File: ExtensionsLinux.cpp                            *
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
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/ContextLinux.h"
#include "PLRendererOpenGL/Misc/Extensions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initialize the supported extensions
*/
bool OpenGLExtensions::Init(bool bUseExtensions)
{
	// Should the extensions be used?
	if (bUseExtensions) {
		m_bInitialized = true;
	} else {
		ResetExtensions();
		m_bInitialized = true;
		PL_LOG(Info, "Use no hardware supported extensions")

		// Done
		return true;
	}

	{ // Print a list af all available extensions into the log
		PL_LOG(Info, "Extensions info:")
		PL_LOG(Info, reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS)))

		WriteExtensionStringIntoLog(reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS)));

		// Get the Linux context implementation
		ContextLinux *pContextLinux = static_cast<ContextLinux*>(m_pRenderer->GetContext());
		if (pContextLinux) {
			// Get the X server display connection
			Display *pDisplay = pContextLinux->GetDisplay();
			if (pDisplay) {
				// glXQueryExtensionsString
				PL_LOG(Info, "glx Extensions info:")
				WriteExtensionStringIntoLog(static_cast<const char*>(glXQueryExtensionsString(pDisplay, XDefaultScreen(pDisplay))));

				// glXGetClientString
				PL_LOG(Info, "glx client extensions info:")
				WriteExtensionStringIntoLog(static_cast<const char*>(glXGetClientString(pDisplay, GLX_EXTENSIONS)));
			}
		}
	}


// WGL / GLX
	// WGL_ARB_pbuffer
	if (IsSupported("GLX_SGIX_pbuffer")) {
		glXCreatePbuffer  = reinterpret_cast<PFNGLXCREATEPBUFFERPROC> (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glXCreatePbuffer")));
		glXDestroyPbuffer = reinterpret_cast<PFNGLXDESTROYPBUFFERPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glXDestroyPbuffer")));
		if (!glXCreatePbuffer || !glXDestroyPbuffer) {
			PL_LOG(Info, "Couldn't use extension 'GLX_SGIX_pbuffer'!")
			m_bWGL_ARB_pbuffer = false;
		} else {
			m_bWGL_ARB_pbuffer = true;
		}
	} else {
		m_bWGL_ARB_pbuffer = false;
	}

	// WGL_ARB_multisample
	m_bWGL_ARB_multisample = IsSupported("GLX_ARB_multisample");

	// GL_ARB_uniform_buffer_object
	if (IsSupported("GL_ARB_uniform_buffer_object")) {
		glGetUniformIndices         = reinterpret_cast<PFNGLGETUNIFORMINDICESPROC>        (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetUniformIndices")));
		glGetActiveUniformsiv       = reinterpret_cast<PFNGLGETACTIVEUNIFORMSIVPROC>      (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetActiveUniformsiv")));
		glGetUniformBlockIndex      = reinterpret_cast<PFNGLGETUNIFORMBLOCKINDEXPROC>     (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetUniformBlockIndex")));
		glGetActiveUniformBlockiv   = reinterpret_cast<PFNGLGETACTIVEUNIFORMBLOCKIVPROC>  (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetActiveUniformBlockiv")));
		glGetActiveUniformBlockName = reinterpret_cast<PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetActiveUniformBlockName")));
		glUniformBlockBinding       = reinterpret_cast<PFNGLUNIFORMBLOCKBINDINGPROC>      (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniformBlockBinding")));
		if (!glGetUniformIndices || !glGetActiveUniformsiv || !glGetUniformBlockIndex || !glGetActiveUniformBlockiv || !glGetActiveUniformBlockName || !glUniformBlockBinding) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_uniform_buffer_object'!")
			m_bGL_ARB_uniform_buffer_object = false;
		} else {
			m_bGL_ARB_uniform_buffer_object = true;
		}
	} else {
		m_bGL_ARB_uniform_buffer_object = false;
	}

	// WGL_ATI_pixel_format_float
	m_bWGL_ATI_pixel_format_float = IsSupported("GLX_ATI_pixel_format_float");

	// WGL_NV_float_buffer
	m_bWGL_NV_float_buffer = IsSupported("GLX_NV_float_buffer");

// GLX (Linux only)
	// GLX_SGI_swap_control
	if (IsSupported("GLX_SGI_swap_control")) {
		glXSwapIntervalSGI = reinterpret_cast<PFNGLXSWAPINTERVALSGIPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glXSwapIntervalSGI")));
		if (!glXSwapIntervalSGI) {
			PL_LOG(Info, "Couldn't use extension 'GLX_SGI_swap_control'!")
			m_bGLX_SGI_swap_control = false;
		} else {
			m_bGLX_SGI_swap_control = true;
		}
	} else {
		m_bGLX_SGI_swap_control = false;
	}

// EXT
	// GL_EXT_compiled_vertex_array
	if (IsSupported("GL_EXT_compiled_vertex_array")) {
		glLockArraysEXT   = reinterpret_cast<PFNGLLOCKARRAYSEXTPROC>  (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glLockArraysEXT")));
		glUnlockArraysEXT = reinterpret_cast<PFNGLUNLOCKARRAYSEXTPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUnlockArraysEXT")));
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
		glDrawRangeElementsEXT = reinterpret_cast<PFNGLDRAWRANGEELEMENTSEXTPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glDrawRangeElementsEXT")));
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
		glFogCoordfEXT		 = reinterpret_cast<PFNGLFOGCOORDFEXTPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glFogCoordfEXT")));
		glFogCoordfvEXT		 = reinterpret_cast<PFNGLFOGCOORDFVEXTPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glFogCoordfvEXT")));
		glFogCoorddEXT		 = reinterpret_cast<PFNGLFOGCOORDDEXTPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glFogCoorddEXT")));
		glFogCoorddvEXT		 = reinterpret_cast<PFNGLFOGCOORDDVEXTPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glFogCoorddvEXT")));
		glFogCoordPointerEXT = reinterpret_cast<PFNGLFOGCOORDPOINTEREXTPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glFogCoordPointerEXT")));
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
		glSecondaryColor3bEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3BEXTPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColor3bEXT")));
		glSecondaryColor3bvEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3BVEXTPROC>	(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColor3bvEXT")));
		glSecondaryColor3dEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3DEXTPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColor3dEXT")));
		glSecondaryColor3dvEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3DVEXTPROC>	(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColor3dvEXT")));
		glSecondaryColor3fEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3FEXTPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColor3fEXT")));
		glSecondaryColor3fvEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3FVEXTPROC>	(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColor3fvEXT")));
		glSecondaryColor3iEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3IEXTPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColor3iEXT")));
		glSecondaryColor3ivEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3IVEXTPROC>	(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColor3ivEXT")));
		glSecondaryColor3sEXT      = reinterpret_cast<PFNGLSECONDARYCOLOR3SEXTPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColor3sEXT")));
		glSecondaryColor3svEXT     = reinterpret_cast<PFNGLSECONDARYCOLOR3SVEXTPROC>	(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColor3svEXT")));
		glSecondaryColor3ubEXT     = reinterpret_cast<PFNGLSECONDARYCOLOR3UBEXTPROC>	(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColor3ubEXT")));
		glSecondaryColor3ubvEXT    = reinterpret_cast<PFNGLSECONDARYCOLOR3UBVEXTPROC>	(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColor3ubvEXT")));
		glSecondaryColor3uiEXT     = reinterpret_cast<PFNGLSECONDARYCOLOR3UIEXTPROC>	(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColor3uiEXT")));
		glSecondaryColor3uivEXT    = reinterpret_cast<PFNGLSECONDARYCOLOR3UIVEXTPROC>	(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColor3uivEXT")));
		glSecondaryColor3usEXT     = reinterpret_cast<PFNGLSECONDARYCOLOR3USEXTPROC>	(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColor3usEXT")));
		glSecondaryColor3usvEXT	   = reinterpret_cast<PFNGLSECONDARYCOLOR3USVEXTPROC>	(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColor3usvEXT")));
		glSecondaryColorPointerEXT = reinterpret_cast<PFNGLSECONDARYCOLORPOINTEREXTPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glSecondaryColorPointerEXT")));
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
		glTexImage3DEXT	   = reinterpret_cast<PFNGLTEXIMAGE3DEXTPROC>	(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glTexImage3DEXT")));
		glTexSubImage3DEXT = reinterpret_cast<PFNGLTEXSUBIMAGE3DEXTPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glTexSubImage3DEXT")));
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
		glActiveStencilFaceEXT = reinterpret_cast<PFNGLACTIVESTENCILFACEEXTPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glActiveStencilFaceEXT")));
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
		glDepthBoundsEXT = reinterpret_cast<PFNGLDEPTHBOUNDSEXTPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glDepthBoundsEXT")));
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
		glIsRenderbufferEXT						 = reinterpret_cast<PFNGLISRENDERBUFFEREXTPROC>						 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glIsRenderbufferEXT")));
		glBindRenderbufferEXT					 = reinterpret_cast<PFNGLBINDRENDERBUFFEREXTPROC>					 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glBindRenderbufferEXT")));
		glDeleteRenderbuffersEXT				 = reinterpret_cast<PFNGLDELETERENDERBUFFERSEXTPROC>				 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glDeleteRenderbuffersEXT")));
		glGenRenderbuffersEXT					 = reinterpret_cast<PFNGLGENRENDERBUFFERSEXTPROC>					 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGenRenderbuffersEXT")));
		glRenderbufferStorageEXT				 = reinterpret_cast<PFNGLRENDERBUFFERSTORAGEEXTPROC>				 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glRenderbufferStorageEXT")));
		glGetRenderbufferParameterivEXT			 = reinterpret_cast<PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC>			 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetRenderbufferParameterivEXT")));
		glIsFramebufferEXT						 = reinterpret_cast<PFNGLISFRAMEBUFFEREXTPROC>						 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glIsFramebufferEXT")));
		glBindFramebufferEXT					 = reinterpret_cast<PFNGLBINDFRAMEBUFFEREXTPROC>					 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glBindFramebufferEXT")));
		glDeleteFramebuffersEXT					 = reinterpret_cast<PFNGLDELETEFRAMEBUFFERSEXTPROC>					 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glDeleteFramebuffersEXT")));
		glGenFramebuffersEXT					 = reinterpret_cast<PFNGLGENFRAMEBUFFERSEXTPROC>					 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGenFramebuffersEXT")));
		glCheckFramebufferStatusEXT				 = reinterpret_cast<PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC>				 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glCheckFramebufferStatusEXT")));
		glFramebufferTexture1DEXT				 = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE1DEXTPROC>				 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glFramebufferTexture1DEXT")));
		glFramebufferTexture2DEXT				 = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE2DEXTPROC>				 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glFramebufferTexture2DEXT")));
		glFramebufferTexture3DEXT				 = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE3DEXTPROC>				 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glFramebufferTexture3DEXT")));
		glFramebufferRenderbufferEXT			 = reinterpret_cast<PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC>			 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glFramebufferRenderbufferEXT")));
		glGetFramebufferAttachmentParameterivEXT = reinterpret_cast<PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC> (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetFramebufferAttachmentParameterivEXT")));
		glGenerateMipmapEXT						 = reinterpret_cast<PFNGLGENERATEMIPMAPEXTPROC>						 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGenerateMipmapEXT")));
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
		glRenderbufferStorageMultisampleEXT = reinterpret_cast<PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glRenderbufferStorageMultisampleEXT")));
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
		glBlitFramebufferEXT = reinterpret_cast<PFNGLBLITFRAMEBUFFEREXTPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glBlitFramebufferEXT")));
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
		glProgramParameteriEXT = reinterpret_cast<PFNGLPROGRAMPARAMETERIEXTPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glProgramParameteriEXT")));
		if (!glProgramParameteriEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_geometry_shader4'!")
			m_bGL_EXT_geometry_shader4 = false;
		} else {
			m_bGL_EXT_geometry_shader4 = true;
		}
	} else {
		m_bGL_EXT_geometry_shader4 = false;
	}

	// GL_EXT_transform_feedback
	if (IsSupported("GL_EXT_transform_feedback")) {
		glBeginTransformFeedbackEXT		 = reinterpret_cast<PFNGLBEGINTRANSFORMFEEDBACKEXTPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glBeginTransformFeedbackEXT")));
		glEndTransformFeedbackEXT		 = reinterpret_cast<PFNGLENDTRANSFORMFEEDBACKEXTPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glEndTransformFeedbackEXT")));
		glBindBufferRangeEXT			 = reinterpret_cast<PFNGLBINDBUFFERRANGEEXTPROC>			(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glBindBufferRangeEXT")));
		glBindBufferOffsetEXT			 = reinterpret_cast<PFNGLBINDBUFFEROFFSETEXTPROC>			(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glBindBufferOffsetEXT")));
		glBindBufferBaseEXT				 = reinterpret_cast<PFNGLBINDBUFFERBASEEXTPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glBindBufferBaseEXT")));
		glTransformFeedbackVaryingsEXT	 = reinterpret_cast<PFNGLTRANSFORMFEEDBACKVARYINGSEXTPROC>	(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glTransformFeedbackVaryingsEXT")));
		glGetTransformFeedbackVaryingEXT = reinterpret_cast<PFNGLGETTRANSFORMFEEDBACKVARYINGEXTPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetTransformFeedbackVaryingEXT")));
		if (!glBeginTransformFeedbackEXT || !glEndTransformFeedbackEXT || !glBindBufferRangeEXT || !glBindBufferOffsetEXT || !glBindBufferBaseEXT || !glTransformFeedbackVaryingsEXT || !glGetTransformFeedbackVaryingEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_transform_feedback'!")
			m_bGL_EXT_transform_feedback = false;
		} else {
			m_bGL_EXT_transform_feedback = true;
		}
	} else {
		m_bGL_EXT_transform_feedback = false;
	}


// ARB
	// GL_ARB_texture_float
	m_bGL_ARB_texture_float = IsSupported("GL_ARB_texture_float");

	// GL_ARB_color_buffer_float
	if (IsSupported("GL_ARB_color_buffer_float")) {
		glClampColorARB = reinterpret_cast<PFNGLCLAMPCOLORARBPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glClampColorARB")));
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
		glActiveTextureARB		 = reinterpret_cast<PFNGLACTIVETEXTUREARBPROC> 		 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glActiveTextureARB")));
		glClientActiveTextureARB = reinterpret_cast<PFNGLCLIENTACTIVETEXTUREARBPROC> (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glClientActiveTextureARB")));
		glMultiTexCoord1dARB	 = reinterpret_cast<PFNGLMULTITEXCOORD1DARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord1dARB")));
		glMultiTexCoord1dvARB	 = reinterpret_cast<PFNGLMULTITEXCOORD1DVARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord1dvARB")));
		glMultiTexCoord1fARB	 = reinterpret_cast<PFNGLMULTITEXCOORD1FARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord1fARB")));
		glMultiTexCoord1fvARB	 = reinterpret_cast<PFNGLMULTITEXCOORD1FVARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord1fvARB")));
		glMultiTexCoord1iARB	 = reinterpret_cast<PFNGLMULTITEXCOORD1IARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord1iARB")));
		glMultiTexCoord1ivARB	 = reinterpret_cast<PFNGLMULTITEXCOORD1IVARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord1ivARB")));
		glMultiTexCoord1sARB	 = reinterpret_cast<PFNGLMULTITEXCOORD1SARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord1sARB")));
		glMultiTexCoord1svARB	 = reinterpret_cast<PFNGLMULTITEXCOORD1SVARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord1svARB")));
		glMultiTexCoord2dARB	 = reinterpret_cast<PFNGLMULTITEXCOORD2DARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord2dARB")));
		glMultiTexCoord2dvARB	 = reinterpret_cast<PFNGLMULTITEXCOORD2DVARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord2dvARB")));
		glMultiTexCoord2fARB	 = reinterpret_cast<PFNGLMULTITEXCOORD2FARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord2fARB")));
		glMultiTexCoord2fvARB	 = reinterpret_cast<PFNGLMULTITEXCOORD2FVARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord2fvARB")));
		glMultiTexCoord2iARB	 = reinterpret_cast<PFNGLMULTITEXCOORD2IARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord2iARB")));
		glMultiTexCoord2ivARB	 = reinterpret_cast<PFNGLMULTITEXCOORD2IVARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord2ivARB")));
		glMultiTexCoord2sARB	 = reinterpret_cast<PFNGLMULTITEXCOORD2SARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord2sARB")));
		glMultiTexCoord2svARB	 = reinterpret_cast<PFNGLMULTITEXCOORD2SVARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord2svARB")));
		glMultiTexCoord3dARB	 = reinterpret_cast<PFNGLMULTITEXCOORD3DARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord3dARB")));
		glMultiTexCoord3dvARB	 = reinterpret_cast<PFNGLMULTITEXCOORD3DVARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord3dvARB")));
		glMultiTexCoord3fARB	 = reinterpret_cast<PFNGLMULTITEXCOORD3FARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord3fARB")));
		glMultiTexCoord3fvARB	 = reinterpret_cast<PFNGLMULTITEXCOORD3FVARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord3fvARB")));
		glMultiTexCoord3iARB	 = reinterpret_cast<PFNGLMULTITEXCOORD3IARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord3iARB")));
		glMultiTexCoord3ivARB	 = reinterpret_cast<PFNGLMULTITEXCOORD3IVARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord3ivARB")));
		glMultiTexCoord3sARB	 = reinterpret_cast<PFNGLMULTITEXCOORD3SARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord3sARB")));
		glMultiTexCoord3svARB	 = reinterpret_cast<PFNGLMULTITEXCOORD3SVARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord3svARB")));
		glMultiTexCoord4dARB	 = reinterpret_cast<PFNGLMULTITEXCOORD4DARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord4dARB")));
		glMultiTexCoord4dvARB	 = reinterpret_cast<PFNGLMULTITEXCOORD4DVARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord4dvARB")));
		glMultiTexCoord4fARB	 = reinterpret_cast<PFNGLMULTITEXCOORD4FARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord4fARB")));
		glMultiTexCoord4fvARB	 = reinterpret_cast<PFNGLMULTITEXCOORD4FVARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord4fvARB")));
		glMultiTexCoord4iARB	 = reinterpret_cast<PFNGLMULTITEXCOORD4IARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord4iARB")));
		glMultiTexCoord4ivARB	 = reinterpret_cast<PFNGLMULTITEXCOORD4IVARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord4ivARB")));
		glMultiTexCoord4sARB	 = reinterpret_cast<PFNGLMULTITEXCOORD4SARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord4sARB")));
		glMultiTexCoord4svARB	 = reinterpret_cast<PFNGLMULTITEXCOORD4SVARBPROC> 	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMultiTexCoord4svARB")));
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
		glBindBufferARB			  = reinterpret_cast<PFNGLBINDBUFFERARBPROC>		   (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glBindBufferARB")));
		glDeleteBuffersARB		  = reinterpret_cast<PFNGLDELETEBUFFERSARBPROC>		   (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glDeleteBuffersARB")));
		glGenBuffersARB			  = reinterpret_cast<PFNGLGENBUFFERSARBPROC>		   (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGenBuffersARB")));
		glBufferDataARB			  = reinterpret_cast<PFNGLBUFFERDATAARBPROC>		   (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glBufferDataARB")));
		glBufferSubDataARB		  = reinterpret_cast<PFNGLBUFFERSUBDATAARBPROC>		   (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glBufferSubDataARB")));
		glGetBufferSubDataARB	  = reinterpret_cast<PFNGLGETBUFFERSUBDATAARBPROC>	   (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetBufferSubDataARB")));
		glMapBufferARB			  = reinterpret_cast<PFNGLMAPBUFFERARBPROC>			   (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glMapBufferARB")));
		glUnmapBufferARB		  = reinterpret_cast<PFNGLUNMAPBUFFERARBPROC>		   (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUnmapBufferARB")));
		glGetBufferParameterivARB = reinterpret_cast<PFNGLGETBUFFERPARAMETERIVARBPROC> (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetBufferParameterivARB")));
		glGetBufferPointervARB	  = reinterpret_cast<PFNGLGETBUFFERPOINTERVARBPROC>	   (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetBufferPointervARB")));
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
		glGenQueriesARB	       = reinterpret_cast<PFNGLGENQUERIESARBPROC>		 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGenQueriesARB")));
		glDeleteQueriesARB     = reinterpret_cast<PFNGLDELETEQUERIESARBPROC>	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glDeleteQueriesARB")));
		glIsQueryARB	       = reinterpret_cast<PFNGLISQUERYARBPROC>			 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glIsQueryARB")));
		glBeginQueryARB	       = reinterpret_cast<PFNGLBEGINQUERYARBPROC>		 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glBeginQueryARB")));
		glEndQueryARB	       = reinterpret_cast<PFNGLENDQUERYARBPROC>			 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glEndQueryARB")));
		glGetQueryivARB		   = reinterpret_cast<PFNGLGETQUERYIVARBPROC>		 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetQueryivARB")));
		glGetQueryObjectivARB  = reinterpret_cast<PFNGLGETQUERYOBJECTIVARBPROC>	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetQueryObjectivARB")));
		glGetQueryObjectuivARB = reinterpret_cast<PFNGLGETQUERYOBJECTUIVARBPROC> (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetQueryObjectuivARB")));
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
		glCompressedTexImage3DARB    = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE3DARBPROC>    (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glCompressedTexImage3DARB")));
		glCompressedTexImage2DARB    = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE2DARBPROC>    (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glCompressedTexImage2DARB")));
		glCompressedTexImage1DARB    = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE1DARBPROC>    (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glCompressedTexImage1DARB")));
		glCompressedTexSubImage3DARB = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC> (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glCompressedTexSubImage3DARB")));
		glCompressedTexSubImage2DARB = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC> (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glCompressedTexSubImage2DARB")));
		glCompressedTexSubImage1DARB = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC> (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glCompressedTexSubImage1DARB")));
		glGetCompressedTexImageARB   = reinterpret_cast<PFNGLGETCOMPRESSEDTEXIMAGEARBPROC>   (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetCompressedTexImageARB")));
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
		glPointParameterfARB  = reinterpret_cast<PFNGLPOINTPARAMETERFARBPROC>  (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glPointParameterfARB")));
		glPointParameterfvARB = reinterpret_cast<PFNGLPOINTPARAMETERFVARBPROC> (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glPointParameterfvARB")));
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
		glVertexAttribPointerARB      = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERARBPROC>      (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glVertexAttribPointerARB")));
		glEnableVertexAttribArrayARB  = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYARBPROC>  (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glEnableVertexAttribArrayARB")));
		glDisableVertexAttribArrayARB = reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYARBPROC> (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glDisableVertexAttribArrayARB")));
		glGetProgramivARB             = reinterpret_cast<PFNGLGETPROGRAMIVARBPROC>             (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetProgramivARB")));
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
		glDrawBuffersARB = reinterpret_cast<PFNGLDRAWBUFFERSARBPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glDrawBuffersARB")));
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
		glDeleteObjectARB			= reinterpret_cast<PFNGLDELETEOBJECTARBPROC>			(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glDeleteObjectARB")));
		glGetHandleARB				= reinterpret_cast<PFNGLGETHANDLEARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetHandleARB")));
		glDetachObjectARB			= reinterpret_cast<PFNGLDETACHOBJECTARBPROC>			(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glDetachObjectARB")));
		glCreateShaderObjectARB		= reinterpret_cast<PFNGLCREATESHADEROBJECTARBPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glCreateShaderObjectARB")));
		glShaderSourceARB			= reinterpret_cast<PFNGLSHADERSOURCEARBPROC>			(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glShaderSourceARB")));
		glCompileShaderARB			= reinterpret_cast<PFNGLCOMPILESHADERARBPROC>			(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glCompileShaderARB")));
		glCreateProgramObjectARB	= reinterpret_cast<PFNGLCREATEPROGRAMOBJECTARBPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glCreateProgramObjectARB")));
		glAttachObjectARB			= reinterpret_cast<PFNGLATTACHOBJECTARBPROC>			(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glAttachObjectARB")));
		glLinkProgramARB			= reinterpret_cast<PFNGLLINKPROGRAMARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glLinkProgramARB")));
		glUseProgramObjectARB		= reinterpret_cast<PFNGLUSEPROGRAMOBJECTARBPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUseProgramObjectARB")));
		glValidateProgramARB		= reinterpret_cast<PFNGLVALIDATEPROGRAMARBPROC>			(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glValidateProgramARB")));
		glUniform1fARB				= reinterpret_cast<PFNGLUNIFORM1FARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniform1fARB")));
		glUniform2fARB				= reinterpret_cast<PFNGLUNIFORM2FARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniform2fARB")));
		glUniform3fARB				= reinterpret_cast<PFNGLUNIFORM3FARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniform3fARB")));
		glUniform4fARB				= reinterpret_cast<PFNGLUNIFORM4FARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniform4fARB")));
		glUniform1iARB				= reinterpret_cast<PFNGLUNIFORM1IARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniform1iARB")));
		glUniform2iARB				= reinterpret_cast<PFNGLUNIFORM2IARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniform2iARB")));
		glUniform3iARB				= reinterpret_cast<PFNGLUNIFORM3IARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniform3iARB")));
		glUniform4iARB				= reinterpret_cast<PFNGLUNIFORM4IARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniform4iARB")));
		glUniform1fvARB				= reinterpret_cast<PFNGLUNIFORM1FVARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniform1fvARB")));
		glUniform2fvARB				= reinterpret_cast<PFNGLUNIFORM2FVARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniform2fvARB")));
		glUniform3fvARB				= reinterpret_cast<PFNGLUNIFORM3FVARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniform3fvARB")));
		glUniform4fvARB				= reinterpret_cast<PFNGLUNIFORM4FVARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniform4fvARB")));
		glUniform1ivARB				= reinterpret_cast<PFNGLUNIFORM1IVARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniform1ivARB")));
		glUniform2ivARB				= reinterpret_cast<PFNGLUNIFORM2IVARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniform2ivARB")));
		glUniform3ivARB				= reinterpret_cast<PFNGLUNIFORM3IVARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniform3ivARB")));
		glUniform4ivARB				= reinterpret_cast<PFNGLUNIFORM4IVARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniform4ivARB")));
		glUniformMatrix2fvARB		= reinterpret_cast<PFNGLUNIFORMMATRIX2FVARBPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniformMatrix2fvARB")));
		glUniformMatrix3fvARB		= reinterpret_cast<PFNGLUNIFORMMATRIX3FVARBPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniformMatrix3fvARB")));
		glUniformMatrix4fvARB		= reinterpret_cast<PFNGLUNIFORMMATRIX4FVARBPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glUniformMatrix4fvARB")));
		glGetObjectParameterfvARB	= reinterpret_cast<PFNGLGETOBJECTPARAMETERFVARBPROC>	(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetObjectParameterfvARB")));
		glGetObjectParameterivARB	= reinterpret_cast<PFNGLGETOBJECTPARAMETERIVARBPROC>	(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetObjectParameterivARB")));
		glGetInfoLogARB				= reinterpret_cast<PFNGLGETINFOLOGARBPROC>				(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetInfoLogARB")));
		glGetAttachedObjectsARB		= reinterpret_cast<PFNGLGETATTACHEDOBJECTSARBPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetAttachedObjectsARB")));
		glGetUniformLocationARB		= reinterpret_cast<PFNGLGETUNIFORMLOCATIONARBPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetUniformLocationARB")));
		glGetActiveUniformARB		= reinterpret_cast<PFNGLGETACTIVEUNIFORMARBPROC>		(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetActiveUniformARB")));
		glGetUniformfvARB			= reinterpret_cast<PFNGLGETUNIFORMFVARBPROC>			(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetUniformfvARB")));
		glGetUniformivARB			= reinterpret_cast<PFNGLGETUNIFORMIVARBPROC>			(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetUniformivARB")));
		glGetShaderSourceARB		= reinterpret_cast<PFNGLGETSHADERSOURCEARBPROC>			(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetShaderSourceARB")));
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
		glBindAttribLocationARB = reinterpret_cast<PFNGLBINDATTRIBLOCATIONARBPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glBindAttribLocationARB")));
		glGetActiveAttribARB    = reinterpret_cast<PFNGLGETACTIVEATTRIBARBPROC>   (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetActiveAttribARB")));
		glGetAttribLocationARB  = reinterpret_cast<PFNGLGETATTRIBLOCATIONARBPROC> (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetAttribLocationARB")));
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
		glGetProgramBinary  = reinterpret_cast<PFNGLGETPROGRAMBINARYPROC> (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetProgramBinary")));
		glProgramBinary     = reinterpret_cast<PFNGLPROGRAMBINARYPROC>    (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glProgramBinary")));
		glProgramParameteri = reinterpret_cast<PFNGLPROGRAMPARAMETERIPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glProgramParameteri")));
		if (!glGetProgramBinary || !glProgramBinary || !glProgramParameteri) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_get_program_binary'!")
			m_bGL_ARB_get_program_binary = false;
		} else {
			m_bGL_ARB_get_program_binary = true;
		}
	} else {
		m_bGL_ARB_get_program_binary = false;
	}

	// GL_ARB_texture_non_power_of_two
	m_bGL_ARB_texture_non_power_of_two = IsSupported("GL_ARB_texture_non_power_of_two");

	// GL_ARB_texture_rectangle
	m_bGL_ARB_texture_rectangle = IsSupported("GL_ARB_texture_rectangle");

	// GL_ARB_multisample
	m_bGL_ARB_multisample = IsSupported("GL_ARB_multisample");


// ATI
	// GL_ATI_separate_stencil 
	if (IsSupported("GL_ATI_separate_stencil")) {
		glStencilOpSeparateATI   = reinterpret_cast<PFNGLSTENCILOPSEPARATEATIPROC>	(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glStencilOpSeparateATI")));
		glStencilFuncSeparateATI = reinterpret_cast<PFNGLSTENCILFUNCSEPARATEATIPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glStencilFuncSeparateATI")));
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
		glDrawBuffersATI = reinterpret_cast<PFNGLDRAWBUFFERSATIPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glDrawBuffersATI")));
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
	if (IsSupported("GL_ATI_texture_compression_3dc"))
		m_bGL_ATI_texture_compression_3dc = true;
	else
		m_bGL_ATI_texture_compression_3dc = false;


// AMD
	// GL_AMD_vertex_shader_tessellator
	if (IsSupported("GL_AMD_vertex_shader_tessellator")) {
		glTessellationFactorAMD = reinterpret_cast<PFNGLTESSELLATIONFACTORAMDPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glTessellationFactorAMD")));
		glTessellationModeAMD   = reinterpret_cast<PFNGLTESSELLATIONMODEAMDPROC>  (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glTessellationModeAMD")));
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
		glGenOcclusionQueriesNV	   = reinterpret_cast<PFNGLGENOCCLUSIONQUERIESNVPROC>	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGenOcclusionQueriesNV")));
		glDeleteOcclusionQueriesNV = reinterpret_cast<PFNGLDELETEOCCLUSIONQUERIESNVPROC> (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glDeleteOcclusionQueriesNV")));
		glIsOcclusionQueryNV	   = reinterpret_cast<PFNGLISOCCLUSIONQUERYNVPROC>		 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glIsOcclusionQueryNV")));
		glBeginOcclusionQueryNV	   = reinterpret_cast<PFNGLBEGINOCCLUSIONQUERYNVPROC>	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glBeginOcclusionQueryNV")));
		glEndOcclusionQueryNV	   = reinterpret_cast<PFNGLENDOCCLUSIONQUERYNVPROC>		 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glEndOcclusionQueryNV")));
		glGetOcclusionQueryivNV	   = reinterpret_cast<PFNGLGETOCCLUSIONQUERYIVNVPROC>	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetOcclusionQueryivNV")));
		glGetOcclusionQueryuivNV   = reinterpret_cast<PFNGLGETOCCLUSIONQUERYUIVNVPROC>	 (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glGetOcclusionQueryuivNV")));
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
