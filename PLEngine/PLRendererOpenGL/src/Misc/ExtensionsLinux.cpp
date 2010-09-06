/*********************************************************\
 *  File: ExtensionsLinux.cpp                            *
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
#include "PLRendererOpenGL/ContextLinux.h"
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
		PL_LOG(Info, (const char*)glGetString(GL_EXTENSIONS))

		WriteExtensionStringIntoLog((const char*)glGetString(GL_EXTENSIONS));

		// Get the Linux context implementation
		ContextLinux *pContextLinux = (ContextLinux*)m_pRenderer->GetContext();
		if (pContextLinux) {
			// Get the X server display connection
			Display *pDisplay = pContextLinux->GetDisplay();
			if (pDisplay) {
				// glXQueryExtensionsString
				PL_LOG(Info, "glx Extensions info:")
				WriteExtensionStringIntoLog((const char*)glXQueryExtensionsString(pDisplay, XDefaultScreen(pDisplay)));

				// glXGetClientString
				PL_LOG(Info, "glx client extensions info:")
				WriteExtensionStringIntoLog((const char*)glXGetClientString(pDisplay, GLX_EXTENSIONS));
			}
		}
	}


// WGL / GLX
	// WGL_ARB_pbuffer
	if (IsSupported("GLX_SGIX_pbuffer")) {
		glXCreatePbuffer = (PFNGLXCREATEPBUFFERPROC) glXGetProcAddressARB((GLubyte*)"glXCreatePbuffer");
		glXDestroyPbuffer = (PFNGLXDESTROYPBUFFERPROC) glXGetProcAddressARB((GLubyte*)"glXDestroyPbuffer");
		if (!glXCreatePbuffer || !glXDestroyPbuffer) {
			PL_LOG(Info, "Couldn't use extension 'GLX_SGIX_pbuffer'!")
			m_bWGL_ARB_pbuffer = false;
		} else m_bWGL_ARB_pbuffer = true;
	} else m_bWGL_ARB_pbuffer = false;

	// WGL_ARB_multisample
	m_bWGL_ARB_multisample = IsSupported("GLX_ARB_multisample");

	// WGL_ATI_pixel_format_float
	m_bWGL_ATI_pixel_format_float = IsSupported("GLX_ATI_pixel_format_float");

	// WGL_NV_float_buffer
	m_bWGL_NV_float_buffer = IsSupported("GLX_NV_float_buffer");

// EXT
	// GL_EXT_compiled_vertex_array
	if (IsSupported("GL_EXT_compiled_vertex_array")) {
		glLockArraysEXT   = (PFNGLLOCKARRAYSEXTPROC)   glXGetProcAddressARB((GLubyte*)"glLockArraysEXT");
		glUnlockArraysEXT = (PFNGLUNLOCKARRAYSEXTPROC) glXGetProcAddressARB((GLubyte*)"glUnlockArraysEXT");
		if (!glLockArraysEXT || !glUnlockArraysEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_compiled_vertex_array'!")
			m_bGL_EXT_compiled_vertex_array = false;
		} else m_bGL_EXT_compiled_vertex_array = true;
	} else m_bGL_EXT_compiled_vertex_array = false;

	// GL_EXT_draw_range_elements
	if (IsSupported("GL_EXT_draw_range_elements")) {
		glDrawRangeElementsEXT = (PFNGLDRAWRANGEELEMENTSEXTPROC) glXGetProcAddressARB((GLubyte*)"glDrawRangeElementsEXT");
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
		glFogCoordfEXT		 = (PFNGLFOGCOORDFEXTPROC)		 glXGetProcAddressARB((GLubyte*)"glFogCoordfEXT");
		glFogCoordfvEXT		 = (PFNGLFOGCOORDFVEXTPROC)		 glXGetProcAddressARB((GLubyte*)"glFogCoordfvEXT");
		glFogCoorddEXT		 = (PFNGLFOGCOORDDEXTPROC)		 glXGetProcAddressARB((GLubyte*)"glFogCoorddEXT");
		glFogCoorddvEXT		 = (PFNGLFOGCOORDDVEXTPROC)		 glXGetProcAddressARB((GLubyte*)"glFogCoorddvEXT");
		glFogCoordPointerEXT = (PFNGLFOGCOORDPOINTEREXTPROC) glXGetProcAddressARB((GLubyte*)"glFogCoordPointerEXT");
		if (!glFogCoordfEXT || !glFogCoordfvEXT || !glFogCoorddEXT || !glFogCoorddvEXT || !glFogCoordPointerEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_fog_coord'!")
			m_bGL_EXT_fog_coord = false;
		} else m_bGL_EXT_fog_coord = true;
	} else m_bGL_EXT_fog_coord = false;

	// GL_EXT_secondary_color
	if (IsSupported("GL_EXT_secondary_color")) {
		glSecondaryColor3bEXT	   = (PFNGLSECONDARYCOLOR3BEXTPROC)		 glXGetProcAddressARB((GLubyte*)"glSecondaryColor3bEXT");
		glSecondaryColor3bvEXT	   = (PFNGLSECONDARYCOLOR3BVEXTPROC)	 glXGetProcAddressARB((GLubyte*)"glSecondaryColor3bvEXT");
		glSecondaryColor3dEXT	   = (PFNGLSECONDARYCOLOR3DEXTPROC)		 glXGetProcAddressARB((GLubyte*)"glSecondaryColor3dEXT");
		glSecondaryColor3dvEXT	   = (PFNGLSECONDARYCOLOR3DVEXTPROC)	 glXGetProcAddressARB((GLubyte*)"glSecondaryColor3dvEXT");
		glSecondaryColor3fEXT	   = (PFNGLSECONDARYCOLOR3FEXTPROC)		 glXGetProcAddressARB((GLubyte*)"glSecondaryColor3fEXT");
		glSecondaryColor3fvEXT	   = (PFNGLSECONDARYCOLOR3FVEXTPROC)	 glXGetProcAddressARB((GLubyte*)"glSecondaryColor3fvEXT");
		glSecondaryColor3iEXT	   = (PFNGLSECONDARYCOLOR3IEXTPROC)		 glXGetProcAddressARB((GLubyte*)"glSecondaryColor3iEXT");
		glSecondaryColor3ivEXT	   = (PFNGLSECONDARYCOLOR3IVEXTPROC)	 glXGetProcAddressARB((GLubyte*)"glSecondaryColor3ivEXT");
		glSecondaryColor3sEXT      = (PFNGLSECONDARYCOLOR3SEXTPROC)		 glXGetProcAddressARB((GLubyte*)"glSecondaryColor3sEXT");
		glSecondaryColor3svEXT     = (PFNGLSECONDARYCOLOR3SVEXTPROC)	 glXGetProcAddressARB((GLubyte*)"glSecondaryColor3svEXT");
		glSecondaryColor3ubEXT     = (PFNGLSECONDARYCOLOR3UBEXTPROC)	 glXGetProcAddressARB((GLubyte*)"glSecondaryColor3ubEXT");
		glSecondaryColor3ubvEXT    = (PFNGLSECONDARYCOLOR3UBVEXTPROC)	 glXGetProcAddressARB((GLubyte*)"glSecondaryColor3ubvEXT");
		glSecondaryColor3uiEXT     = (PFNGLSECONDARYCOLOR3UIEXTPROC)	 glXGetProcAddressARB((GLubyte*)"glSecondaryColor3uiEXT");
		glSecondaryColor3uivEXT    = (PFNGLSECONDARYCOLOR3UIVEXTPROC)	 glXGetProcAddressARB((GLubyte*)"glSecondaryColor3uivEXT");
		glSecondaryColor3usEXT     = (PFNGLSECONDARYCOLOR3USEXTPROC)	 glXGetProcAddressARB((GLubyte*)"glSecondaryColor3usEXT");
		glSecondaryColor3usvEXT	   = (PFNGLSECONDARYCOLOR3USVEXTPROC)	 glXGetProcAddressARB((GLubyte*)"glSecondaryColor3usvEXT");
		glSecondaryColorPointerEXT = (PFNGLSECONDARYCOLORPOINTEREXTPROC) glXGetProcAddressARB((GLubyte*)"glSecondaryColorPointerEXT");
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
		glTexImage3DEXT	   = (PFNGLTEXIMAGE3DEXTPROC)	 glXGetProcAddressARB((GLubyte*)"glTexImage3DEXT");
		glTexSubImage3DEXT = (PFNGLTEXSUBIMAGE3DEXTPROC) glXGetProcAddressARB((GLubyte*)"glTexSubImage3DEXT");
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
		glActiveStencilFaceEXT = (PFNGLACTIVESTENCILFACEEXTPROC) glXGetProcAddressARB((GLubyte*)"glActiveStencilFaceEXT");
		if (!glActiveStencilFaceEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_stencil_two_side'!")
			m_bGL_EXT_stencil_two_side = false;
		} else m_bGL_EXT_stencil_two_side = true;
	} else m_bGL_EXT_stencil_two_side = false;

	// GL_EXT_packed_depth_stencil
	m_bGL_EXT_packed_depth_stencil = IsSupported("GL_EXT_packed_depth_stencil");

	// GL_EXT_depth_bounds_test
	if (IsSupported("GL_EXT_depth_bounds_test")) {
		glDepthBoundsEXT = (PFNGLDEPTHBOUNDSEXTPROC) glXGetProcAddressARB((GLubyte*)"glDepthBoundsEXT");
		if (!glDepthBoundsEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_depth_bounds_test'!")
			m_bGL_EXT_depth_bounds_test = false;
		} else m_bGL_EXT_depth_bounds_test = true;
	} else m_bGL_EXT_depth_bounds_test = false;

	// GL_EXT_framebuffer_object
	if (IsSupported("GL_EXT_framebuffer_object")) {
		glIsRenderbufferEXT						 = (PFNGLISRENDERBUFFEREXTPROC)						 glXGetProcAddressARB((GLubyte*)"glIsRenderbufferEXT");
		glBindRenderbufferEXT					 = (PFNGLBINDRENDERBUFFEREXTPROC)					 glXGetProcAddressARB((GLubyte*)"glBindRenderbufferEXT");
		glDeleteRenderbuffersEXT				 = (PFNGLDELETERENDERBUFFERSEXTPROC)				 glXGetProcAddressARB((GLubyte*)"glDeleteRenderbuffersEXT");
		glGenRenderbuffersEXT					 = (PFNGLGENRENDERBUFFERSEXTPROC)					 glXGetProcAddressARB((GLubyte*)"glGenRenderbuffersEXT");
		glRenderbufferStorageEXT				 = (PFNGLRENDERBUFFERSTORAGEEXTPROC)				 glXGetProcAddressARB((GLubyte*)"glRenderbufferStorageEXT");
		glGetRenderbufferParameterivEXT			 = (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC)			 glXGetProcAddressARB((GLubyte*)"glGetRenderbufferParameterivEXT");
		glIsFramebufferEXT						 = (PFNGLISFRAMEBUFFEREXTPROC)						 glXGetProcAddressARB((GLubyte*)"glIsFramebufferEXT");
		glBindFramebufferEXT					 = (PFNGLBINDFRAMEBUFFEREXTPROC)					 glXGetProcAddressARB((GLubyte*)"glBindFramebufferEXT");
		glDeleteFramebuffersEXT					 = (PFNGLDELETEFRAMEBUFFERSEXTPROC)					 glXGetProcAddressARB((GLubyte*)"glDeleteFramebuffersEXT");
		glGenFramebuffersEXT					 = (PFNGLGENFRAMEBUFFERSEXTPROC)					 glXGetProcAddressARB((GLubyte*)"glGenFramebuffersEXT");
		glCheckFramebufferStatusEXT				 = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)				 glXGetProcAddressARB((GLubyte*)"glCheckFramebufferStatusEXT");
		glFramebufferTexture1DEXT				 = (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC)				 glXGetProcAddressARB((GLubyte*)"glFramebufferTexture1DEXT");
		glFramebufferTexture2DEXT				 = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)				 glXGetProcAddressARB((GLubyte*)"glFramebufferTexture2DEXT");
		glFramebufferTexture3DEXT				 = (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC)				 glXGetProcAddressARB((GLubyte*)"glFramebufferTexture3DEXT");
		glFramebufferRenderbufferEXT			 = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)			 glXGetProcAddressARB((GLubyte*)"glFramebufferRenderbufferEXT");
		glGetFramebufferAttachmentParameterivEXT = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC) glXGetProcAddressARB((GLubyte*)"glGetFramebufferAttachmentParameterivEXT");
		glGenerateMipmapEXT						 = (PFNGLGENERATEMIPMAPEXTPROC)						 glXGetProcAddressARB((GLubyte*)"glGenerateMipmapEXT");
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
		glRenderbufferStorageMultisampleEXT = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)glXGetProcAddressARB((GLubyte*)"glRenderbufferStorageMultisampleEXT");
		if (!glRenderbufferStorageMultisampleEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_framebuffer_multisample'!")
			m_bGL_EXT_framebuffer_multisample = false;
		} else m_bGL_EXT_framebuffer_multisample = true;
	} else m_bGL_EXT_framebuffer_multisample = false;

	// GL_EXT_framebuffer_blit
	if (IsSupported("GL_EXT_framebuffer_blit")) {
		glBlitFramebufferEXT = (PFNGLBLITFRAMEBUFFEREXTPROC)glXGetProcAddressARB((GLubyte*)"glBlitFramebufferEXT");
		if (!glBlitFramebufferEXT) {
			PL_LOG(Info, "Couldn't use extension 'GL_EXT_framebuffer_blit'!")
			m_bGL_EXT_framebuffer_blit = false;
		} else m_bGL_EXT_framebuffer_blit = true;
	} else m_bGL_EXT_framebuffer_blit = false;

	// GL_EXT_geometry_shader4
	if (IsSupported("GL_EXT_geometry_shader4")) {
		glProgramParameteriEXT = (PFNGLPROGRAMPARAMETERIEXTPROC)glXGetProcAddressARB((GLubyte*)"glProgramParameteriEXT");
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
		glClampColorARB = (PFNGLCLAMPCOLORARBPROC)glXGetProcAddressARB((GLubyte*)(GLubyte*)"glClampColorARB");
		if (!glClampColorARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_color_buffer_float'!")
			m_bGL_ARB_color_buffer_float = false;
		} else m_bGL_ARB_color_buffer_float = true;
	} else m_bGL_ARB_color_buffer_float = false;

	// GL_ARB_multitexture
	if (IsSupported("GL_ARB_multitexture")) {
		glActiveTextureARB		 = (PFNGLACTIVETEXTUREARBPROC) 		 glXGetProcAddressARB((GLubyte*)(GLubyte*)"glActiveTextureARB");
		glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC) glXGetProcAddressARB((GLubyte*)"glClientActiveTextureARB");
		glMultiTexCoord1dARB	 = (PFNGLMULTITEXCOORD1DARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord1dARB");
		glMultiTexCoord1dvARB	 = (PFNGLMULTITEXCOORD1DVARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord1dvARB");
		glMultiTexCoord1fARB	 = (PFNGLMULTITEXCOORD1FARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord1fARB");
		glMultiTexCoord1fvARB	 = (PFNGLMULTITEXCOORD1FVARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord1fvARB");
		glMultiTexCoord1iARB	 = (PFNGLMULTITEXCOORD1IARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord1iARB");
		glMultiTexCoord1ivARB	 = (PFNGLMULTITEXCOORD1IVARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord1ivARB");
		glMultiTexCoord1sARB	 = (PFNGLMULTITEXCOORD1SARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord1sARB");
		glMultiTexCoord1svARB	 = (PFNGLMULTITEXCOORD1SVARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord1svARB");
		glMultiTexCoord2dARB	 = (PFNGLMULTITEXCOORD2DARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord2dARB");
		glMultiTexCoord2dvARB	 = (PFNGLMULTITEXCOORD2DVARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord2dvARB");
		glMultiTexCoord2fARB	 = (PFNGLMULTITEXCOORD2FARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord2fARB");
		glMultiTexCoord2fvARB	 = (PFNGLMULTITEXCOORD2FVARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord2fvARB");
		glMultiTexCoord2iARB	 = (PFNGLMULTITEXCOORD2IARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord2iARB");
		glMultiTexCoord2ivARB	 = (PFNGLMULTITEXCOORD2IVARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord2ivARB");
		glMultiTexCoord2sARB	 = (PFNGLMULTITEXCOORD2SARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord2sARB");
		glMultiTexCoord2svARB	 = (PFNGLMULTITEXCOORD2SVARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord2svARB");
		glMultiTexCoord3dARB	 = (PFNGLMULTITEXCOORD3DARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord3dARB");
		glMultiTexCoord3dvARB	 = (PFNGLMULTITEXCOORD3DVARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord3dvARB");
		glMultiTexCoord3fARB	 = (PFNGLMULTITEXCOORD3FARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord3fARB");
		glMultiTexCoord3fvARB	 = (PFNGLMULTITEXCOORD3FVARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord3fvARB");
		glMultiTexCoord3iARB	 = (PFNGLMULTITEXCOORD3IARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord3iARB");
		glMultiTexCoord3ivARB	 = (PFNGLMULTITEXCOORD3IVARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord3ivARB");
		glMultiTexCoord3sARB	 = (PFNGLMULTITEXCOORD3SARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord3sARB");
		glMultiTexCoord3svARB	 = (PFNGLMULTITEXCOORD3SVARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord3svARB");
		glMultiTexCoord4dARB	 = (PFNGLMULTITEXCOORD4DARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord4dARB");
		glMultiTexCoord4dvARB	 = (PFNGLMULTITEXCOORD4DVARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord4dvARB");
		glMultiTexCoord4fARB	 = (PFNGLMULTITEXCOORD4FARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord4fARB");
		glMultiTexCoord4fvARB	 = (PFNGLMULTITEXCOORD4FVARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord4fvARB");
		glMultiTexCoord4iARB	 = (PFNGLMULTITEXCOORD4IARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord4iARB");
		glMultiTexCoord4ivARB	 = (PFNGLMULTITEXCOORD4IVARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord4ivARB");
		glMultiTexCoord4sARB	 = (PFNGLMULTITEXCOORD4SARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord4sARB");
		glMultiTexCoord4svARB	 = (PFNGLMULTITEXCOORD4SVARBPROC) 	 glXGetProcAddressARB((GLubyte*)"glMultiTexCoord4svARB");
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
		glBindBufferARB			  = (PFNGLBINDBUFFERARBPROC)		   glXGetProcAddressARB((GLubyte*)"glBindBufferARB");
		glDeleteBuffersARB		  = (PFNGLDELETEBUFFERSARBPROC)		   glXGetProcAddressARB((GLubyte*)"glDeleteBuffersARB");
		glGenBuffersARB			  = (PFNGLGENBUFFERSARBPROC)		   glXGetProcAddressARB((GLubyte*)"glGenBuffersARB");
		glBufferDataARB			  = (PFNGLBUFFERDATAARBPROC)		   glXGetProcAddressARB((GLubyte*)"glBufferDataARB");
		glBufferSubDataARB		  = (PFNGLBUFFERSUBDATAARBPROC)		   glXGetProcAddressARB((GLubyte*)"glBufferSubDataARB");
		glGetBufferSubDataARB	  = (PFNGLGETBUFFERSUBDATAARBPROC)	   glXGetProcAddressARB((GLubyte*)"glGetBufferSubDataARB");
		glMapBufferARB			  = (PFNGLMAPBUFFERARBPROC)			   glXGetProcAddressARB((GLubyte*)"glMapBufferARB");
		glUnmapBufferARB		  = (PFNGLUNMAPBUFFERARBPROC)		   glXGetProcAddressARB((GLubyte*)"glUnmapBufferARB");
		glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC) glXGetProcAddressARB((GLubyte*)"glGetBufferParameterivARB");
		glGetBufferPointervARB	  = (PFNGLGETBUFFERPOINTERVARBPROC)	   glXGetProcAddressARB((GLubyte*)"glGetBufferPointervARB");
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
		glGenQueriesARB	       = (PFNGLGENQUERIESARBPROC)		 glXGetProcAddressARB((GLubyte*)"glGenQueriesARB");
		glDeleteQueriesARB     = (PFNGLDELETEQUERIESARBPROC)	 glXGetProcAddressARB((GLubyte*)"glDeleteQueriesARB");
		glIsQueryARB	       = (PFNGLISQUERYARBPROC)			 glXGetProcAddressARB((GLubyte*)"glIsQueryARB");
		glBeginQueryARB	       = (PFNGLBEGINQUERYARBPROC)		 glXGetProcAddressARB((GLubyte*)"glBeginQueryARB");
		glEndQueryARB	       = (PFNGLENDQUERYARBPROC)			 glXGetProcAddressARB((GLubyte*)"glEndQueryARB");
		glGetQueryivARB		   = (PFNGLGETQUERYIVARBPROC)		 glXGetProcAddressARB((GLubyte*)"glGetQueryivARB");
		glGetQueryObjectivARB  = (PFNGLGETQUERYOBJECTIVARBPROC)	 glXGetProcAddressARB((GLubyte*)"glGetQueryObjectivARB");
		glGetQueryObjectuivARB = (PFNGLGETQUERYOBJECTUIVARBPROC) glXGetProcAddressARB((GLubyte*)"glGetQueryObjectuivARB");
		if (!glGenQueriesARB || !glDeleteQueriesARB || !glIsQueryARB || !glBeginQueryARB ||
			!glEndQueryARB || !glGetQueryivARB || !glGetQueryObjectivARB || !glGetQueryObjectuivARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_occlusion_query'!")
			m_bGL_ARB_occlusion_query = false;
		} else m_bGL_ARB_occlusion_query = true;
	} else m_bGL_ARB_occlusion_query = false;

	// GL_ARB_texture_compression
	if (IsSupported("GL_ARB_texture_compression")) {
		glCompressedTexImage3DARB    = (PFNGLCOMPRESSEDTEXIMAGE3DARBPROC)    glXGetProcAddressARB((GLubyte*)"glCompressedTexImage3DARB");
		glCompressedTexImage2DARB    = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)    glXGetProcAddressARB((GLubyte*)"glCompressedTexImage2DARB");
		glCompressedTexImage1DARB    = (PFNGLCOMPRESSEDTEXIMAGE1DARBPROC)    glXGetProcAddressARB((GLubyte*)"glCompressedTexImage1DARB");
		glCompressedTexSubImage3DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC) glXGetProcAddressARB((GLubyte*)"glCompressedTexSubImage3DARB");
		glCompressedTexSubImage2DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC) glXGetProcAddressARB((GLubyte*)"glCompressedTexSubImage2DARB");
		glCompressedTexSubImage1DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC) glXGetProcAddressARB((GLubyte*)"glCompressedTexSubImage1DARB");
		glGetCompressedTexImageARB   = (PFNGLGETCOMPRESSEDTEXIMAGEARBPROC)   glXGetProcAddressARB((GLubyte*)"glGetCompressedTexImageARB");
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
		glPointParameterfARB  = (PFNGLPOINTPARAMETERFARBPROC)  glXGetProcAddressARB((GLubyte*)"glPointParameterfARB");
		glPointParameterfvARB = (PFNGLPOINTPARAMETERFVARBPROC) glXGetProcAddressARB((GLubyte*)"glPointParameterfvARB");
		if (!glPointParameterfARB || !glPointParameterfvARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_point_parameters'!")
			m_bGL_ARB_point_parameters = false;
		} else m_bGL_ARB_point_parameters = true;
	} else m_bGL_ARB_point_parameters = false;

	// GL_ARB_shading_language_100
	m_bGL_ARB_shading_language_100 = IsSupported("GL_ARB_shading_language_100");

	// GL_ARB_vertex_program
	if (IsSupported("GL_ARB_vertex_program")) {
		glVertexAttribPointerARB      = (PFNGLVERTEXATTRIBPOINTERARBPROC)      glXGetProcAddressARB((GLubyte*)"glVertexAttribPointerARB");
		glEnableVertexAttribArrayARB  = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC)  glXGetProcAddressARB((GLubyte*)"glEnableVertexAttribArrayARB");
		glDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC) glXGetProcAddressARB((GLubyte*)"glDisableVertexAttribArrayARB");
		glGetProgramivARB             = (PFNGLGETPROGRAMIVARBPROC)             glXGetProcAddressARB((GLubyte*)"glGetProgramivARB");
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
		glDrawBuffersARB = (PFNGLDRAWBUFFERSARBPROC) glXGetProcAddressARB((GLubyte*)"glDrawBuffersARB");
		if (!glDrawBuffersARB) {
			PL_LOG(Info, "Couldn't use extension 'GL_ARB_draw_buffers'!")
			m_bGL_ARB_draw_buffers = false;
		} else m_bGL_ARB_draw_buffers = true;
	} else m_bGL_ARB_draw_buffers = false;

	// GL_ARB_shader_objects
	if (IsSupported("GL_ARB_shader_objects")) {
		glDeleteObjectARB			= (PFNGLDELETEOBJECTARBPROC)			glXGetProcAddressARB((GLubyte*)"glDeleteObjectARB");
		glGetHandleARB				= (PFNGLGETHANDLEARBPROC)				glXGetProcAddressARB((GLubyte*)"glGetHandleARB");
		glDetachObjectARB			= (PFNGLDETACHOBJECTARBPROC)			glXGetProcAddressARB((GLubyte*)"glDetachObjectARB");
		glCreateShaderObjectARB		= (PFNGLCREATESHADEROBJECTARBPROC)		glXGetProcAddressARB((GLubyte*)"glCreateShaderObjectARB");
		glShaderSourceARB			= (PFNGLSHADERSOURCEARBPROC)			glXGetProcAddressARB((GLubyte*)"glShaderSourceARB");
		glCompileShaderARB			= (PFNGLCOMPILESHADERARBPROC)			glXGetProcAddressARB((GLubyte*)"glCompileShaderARB");
		glCreateProgramObjectARB	= (PFNGLCREATEPROGRAMOBJECTARBPROC)		glXGetProcAddressARB((GLubyte*)"glCreateProgramObjectARB");
		glAttachObjectARB			= (PFNGLATTACHOBJECTARBPROC)			glXGetProcAddressARB((GLubyte*)"glAttachObjectARB");
		glLinkProgramARB			= (PFNGLLINKPROGRAMARBPROC)				glXGetProcAddressARB((GLubyte*)"glLinkProgramARB");
		glUseProgramObjectARB		= (PFNGLUSEPROGRAMOBJECTARBPROC)		glXGetProcAddressARB((GLubyte*)"glUseProgramObjectARB");
		glValidateProgramARB		= (PFNGLVALIDATEPROGRAMARBPROC)			glXGetProcAddressARB((GLubyte*)"glValidateProgramARB");
		glUniform1fARB				= (PFNGLUNIFORM1FARBPROC)				glXGetProcAddressARB((GLubyte*)"glUniform1fARB");
		glUniform2fARB				= (PFNGLUNIFORM2FARBPROC)				glXGetProcAddressARB((GLubyte*)"glUniform2fARB");
		glUniform3fARB				= (PFNGLUNIFORM3FARBPROC)				glXGetProcAddressARB((GLubyte*)"glUniform3fARB");
		glUniform4fARB				= (PFNGLUNIFORM4FARBPROC)				glXGetProcAddressARB((GLubyte*)"glUniform4fARB");
		glUniform1iARB				= (PFNGLUNIFORM1IARBPROC)				glXGetProcAddressARB((GLubyte*)"glUniform1iARB");
		glUniform2iARB				= (PFNGLUNIFORM2IARBPROC)				glXGetProcAddressARB((GLubyte*)"glUniform2iARB");
		glUniform3iARB				= (PFNGLUNIFORM3IARBPROC)				glXGetProcAddressARB((GLubyte*)"glUniform3iARB");
		glUniform4iARB				= (PFNGLUNIFORM4IARBPROC)				glXGetProcAddressARB((GLubyte*)"glUniform4iARB");
		glUniform1fvARB				= (PFNGLUNIFORM1FVARBPROC)				glXGetProcAddressARB((GLubyte*)"glUniform1fvARB");
		glUniform2fvARB				= (PFNGLUNIFORM2FVARBPROC)				glXGetProcAddressARB((GLubyte*)"glUniform2fvARB");
		glUniform3fvARB				= (PFNGLUNIFORM3FVARBPROC)				glXGetProcAddressARB((GLubyte*)"glUniform3fvARB");
		glUniform4fvARB				= (PFNGLUNIFORM4FVARBPROC)				glXGetProcAddressARB((GLubyte*)"glUniform4fvARB");
		glUniform1ivARB				= (PFNGLUNIFORM1IVARBPROC)				glXGetProcAddressARB((GLubyte*)"glUniform1ivARB");
		glUniform2ivARB				= (PFNGLUNIFORM2IVARBPROC)				glXGetProcAddressARB((GLubyte*)"glUniform2ivARB");
		glUniform3ivARB				= (PFNGLUNIFORM3IVARBPROC)				glXGetProcAddressARB((GLubyte*)"glUniform3ivARB");
		glUniform4ivARB				= (PFNGLUNIFORM4IVARBPROC)				glXGetProcAddressARB((GLubyte*)"glUniform4ivARB");
		glUniformMatrix2fvARB		= (PFNGLUNIFORMMATRIX2FVARBPROC)		glXGetProcAddressARB((GLubyte*)"glUniformMatrix2fvARB");
		glUniformMatrix3fvARB		= (PFNGLUNIFORMMATRIX3FVARBPROC)		glXGetProcAddressARB((GLubyte*)"glUniformMatrix3fvARB");
		glUniformMatrix4fvARB		= (PFNGLUNIFORMMATRIX4FVARBPROC)		glXGetProcAddressARB((GLubyte*)"glUniformMatrix4fvARB");
		glGetObjectParameterfvARB	= (PFNGLGETOBJECTPARAMETERFVARBPROC)	glXGetProcAddressARB((GLubyte*)"glGetObjectParameterfvARB");
		glGetObjectParameterivARB	= (PFNGLGETOBJECTPARAMETERIVARBPROC)	glXGetProcAddressARB((GLubyte*)"glGetObjectParameterivARB");
		glGetInfoLogARB				= (PFNGLGETINFOLOGARBPROC)				glXGetProcAddressARB((GLubyte*)"glGetInfoLogARB");
		glGetAttachedObjectsARB		= (PFNGLGETATTACHEDOBJECTSARBPROC)		glXGetProcAddressARB((GLubyte*)"glGetAttachedObjectsARB");
		glGetUniformLocationARB		= (PFNGLGETUNIFORMLOCATIONARBPROC)		glXGetProcAddressARB((GLubyte*)"glGetUniformLocationARB");
		glGetActiveUniformARB		= (PFNGLGETACTIVEUNIFORMARBPROC)		glXGetProcAddressARB((GLubyte*)"glGetActiveUniformARB");
		glGetUniformfvARB			= (PFNGLGETUNIFORMFVARBPROC)			glXGetProcAddressARB((GLubyte*)"glGetUniformfvARB");
		glGetUniformivARB			= (PFNGLGETUNIFORMIVARBPROC)			glXGetProcAddressARB((GLubyte*)"glGetUniformivARB");
		glGetShaderSourceARB		= (PFNGLGETSHADERSOURCEARBPROC)			glXGetProcAddressARB((GLubyte*)"glGetShaderSourceARB");
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
		glBindAttribLocationARB = (PFNGLBINDATTRIBLOCATIONARBPROC) glXGetProcAddressARB((GLubyte*)"glBindAttribLocationARB");
		glGetActiveAttribARB    = (PFNGLGETACTIVEATTRIBARBPROC)    glXGetProcAddressARB((GLubyte*)"glGetActiveAttribARB");
		glGetAttribLocationARB  = (PFNGLGETATTRIBLOCATIONARBPROC)  glXGetProcAddressARB((GLubyte*)"glGetAttribLocationARB");
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
		glStencilOpSeparateATI   = (PFNGLSTENCILOPSEPARATEATIPROC)	 glXGetProcAddressARB((GLubyte*)"glStencilOpSeparateATI");
		glStencilFuncSeparateATI = (PFNGLSTENCILFUNCSEPARATEATIPROC) glXGetProcAddressARB((GLubyte*)"glStencilFuncSeparateATI");
		if (!glStencilOpSeparateATI || !glStencilFuncSeparateATI) {
			PL_LOG(Info, "Couldn't use extension 'GL_ATI_separate_stencil'!")
			m_bGL_ATI_separate_stencil = false;
		} else m_bGL_ATI_separate_stencil = true;
	} else m_bGL_ATI_separate_stencil = false;

	// GL_ATI_draw_buffers
	if (IsSupported("GL_ATI_draw_buffers")) {
		glDrawBuffersATI = (PFNGLDRAWBUFFERSATIPROC) glXGetProcAddressARB((GLubyte*)"glDrawBuffersATI");
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
		glTessellationFactorAMD = (PFNGLTESSELLATIONFACTORAMDPROC) glXGetProcAddressARB((GLubyte*)"glTessellationFactorAMD");
		glTessellationModeAMD   = (PFNGLTESSELLATIONMODEAMDPROC)   glXGetProcAddressARB((GLubyte*)"glTessellationModeAMD");
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
		glGenOcclusionQueriesNV	   = (PFNGLGENOCCLUSIONQUERIESNVPROC)	 glXGetProcAddressARB((GLubyte*)"glGenOcclusionQueriesNV");
		glDeleteOcclusionQueriesNV = (PFNGLDELETEOCCLUSIONQUERIESNVPROC) glXGetProcAddressARB((GLubyte*)"glDeleteOcclusionQueriesNV");
		glIsOcclusionQueryNV	   = (PFNGLISOCCLUSIONQUERYNVPROC)		 glXGetProcAddressARB((GLubyte*)"glIsOcclusionQueryNV");
		glBeginOcclusionQueryNV	   = (PFNGLBEGINOCCLUSIONQUERYNVPROC)	 glXGetProcAddressARB((GLubyte*)"glBeginOcclusionQueryNV");
		glEndOcclusionQueryNV	   = (PFNGLENDOCCLUSIONQUERYNVPROC)		 glXGetProcAddressARB((GLubyte*)"glEndOcclusionQueryNV");
		glGetOcclusionQueryivNV	   = (PFNGLGETOCCLUSIONQUERYIVNVPROC)	 glXGetProcAddressARB((GLubyte*)"glGetOcclusionQueryivNV");
		glGetOcclusionQueryuivNV   = (PFNGLGETOCCLUSIONQUERYUIVNVPROC)	 glXGetProcAddressARB((GLubyte*)"glGetOcclusionQueryuivNV");
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
