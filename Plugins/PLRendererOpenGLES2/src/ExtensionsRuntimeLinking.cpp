/*********************************************************\
 *  File: ExtensionsRuntimeLinking.cpp                   *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Log/Log.h>
#define EXTENSIONS_DEFINERUNTIMELINKING
#include "PLRendererOpenGLES2/Context.h"
#include "PLRendererOpenGLES2/ExtensionsRuntimeLinking.h"


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
ExtensionsRuntimeLinking::ExtensionsRuntimeLinking() :
	// ARB
	m_bGL_ARB_draw_buffers(false),
	// EXT
	m_bGL_EXT_texture_compression_s3tc(false),
	m_bGL_EXT_texture_compression_dxt1(false),
	m_bGL_EXT_texture_compression_latc(false),
	m_bGL_EXT_texture_filter_anisotropic(false),
	m_bGL_EXT_texture_array(false),
	m_bGL_EXT_Cg_shader(false),
	// AMD
	m_bGL_AMD_compressed_3DC_texture(false),
	// NV
	m_bGL_NV_get_tex_image(false),
	m_bGL_NV_fbo_color_attachments(false),
	m_bGL_NV_read_buffer(false),
	// OES
	m_bGL_OES_mapbuffer(false),
	m_bGL_OES_element_index_uint(false),
	m_bGL_OES_texture_3D(false),
	m_bGL_OES_packed_depth_stencil(false),
	m_bGL_OES_depth24(false),
	m_bGL_OES_depth32(false),
	m_bGL_OES_vertex_half_float(false),
	// ANGLE
	m_bGL_ANGLE_framebuffer_blit(false),
	m_bGL_ANGLE_framebuffer_multisample(false)
{
}

/**
*  @brief
*    Destructor
*/
ExtensionsRuntimeLinking::~ExtensionsRuntimeLinking()
{
}

/**
*  @brief
*    Initialize the supported extensions
*/
void ExtensionsRuntimeLinking::Init()
{
	// Define a helper macro
	#define IMPORT_FUNC(funcName)																										\
		if (bResult) {																													\
			void *pSymbol = eglGetProcAddress(#funcName);																				\
			if (pSymbol) {																												\
				*(reinterpret_cast<void**>(&(funcName))) = pSymbol;																		\
			} else {																													\
				PL_LOG(Error, String("Failed to find the entry point \"") + #funcName + "\" within the OpenGL ES 2.0 dynamic library")	\
				bResult = false;																										\
			}																															\
		}

	// Get the extensions string
	const String sExtensions = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));

	//[-------------------------------------------------------]
	//[ ARB                                                   ]
	//[-------------------------------------------------------]
	m_bGL_ARB_draw_buffers = sExtensions.IsSubstring("GL_ARB_draw_buffers");
	if (m_bGL_ARB_draw_buffers) {
		// Load the entry points
		bool bResult = true;	// Success by default
		IMPORT_FUNC(glDrawBuffersARB)
		m_bGL_ARB_draw_buffers = bResult;
	}

	//[-------------------------------------------------------]
	//[ EXT                                                   ]
	//[-------------------------------------------------------]
	m_bGL_EXT_texture_compression_s3tc   = sExtensions.IsSubstring("GL_EXT_texture_compression_s3tc");
	m_bGL_EXT_texture_compression_dxt1   = sExtensions.IsSubstring("GL_EXT_texture_compression_dxt1");
	m_bGL_EXT_texture_compression_latc   = sExtensions.IsSubstring("GL_EXT_texture_compression_latc");
	m_bGL_EXT_texture_filter_anisotropic = sExtensions.IsSubstring("GL_EXT_texture_filter_anisotropic");
	m_bGL_EXT_texture_array				 = sExtensions.IsSubstring("GL_EXT_texture_array");
	if (m_bGL_EXT_texture_array) {
		// A funny thing: Tegra 2 has support for the extension "GL_EXT_texture_array", but has no support
		// for the "GL_OES_texture_3D"-extension. At least it's not listed in the extension string.
		// "GL_EXT_texture_array" is reusing functions defined by "GL_OES_texture_3D"... and therefore we're
		// now getting the function pointers of "GL_OES_texture_3D" to be able to use "GL_EXT_texture_array".
		// Works even when "GL_OES_texture_3D" is not listed. Nice.

		// Load the entry points
		bool bResult = true;	// Success by default
		IMPORT_FUNC(glTexImage3DOES)
		IMPORT_FUNC(glTexSubImage3DOES)
		IMPORT_FUNC(glCopyTexSubImage3DOES)
		IMPORT_FUNC(glCompressedTexImage3DOES)
		IMPORT_FUNC(glCompressedTexSubImage3DOES)
		IMPORT_FUNC(glFramebufferTexture3DOES)
		m_bGL_EXT_texture_array = bResult;
	}
	m_bGL_EXT_Cg_shader = sExtensions.IsSubstring("GL_EXT_Cg_shader");

	//[-------------------------------------------------------]
	//[ AMD                                                   ]
	//[-------------------------------------------------------]
	m_bGL_AMD_compressed_3DC_texture = sExtensions.IsSubstring("GL_AMD_compressed_3DC_texture");

	//[-------------------------------------------------------]
	//[ NV                                                    ]
	//[-------------------------------------------------------]
	m_bGL_NV_get_tex_image = sExtensions.IsSubstring("GL_NV_get_tex_image");
	if (m_bGL_NV_get_tex_image) {
		// Load the entry points
		bool bResult = true;	// Success by default
		IMPORT_FUNC(glGetTexImageNV)
		IMPORT_FUNC(glGetCompressedTexImageNV)
		IMPORT_FUNC(glGetTexLevelParameterfvNV)
		IMPORT_FUNC(glGetTexLevelParameterivNV)
		m_bGL_NV_get_tex_image = bResult;
	}
	m_bGL_NV_fbo_color_attachments = sExtensions.IsSubstring("GL_NV_fbo_color_attachments");
	m_bGL_NV_read_buffer		   = sExtensions.IsSubstring("GL_NV_read_buffer");
	if (m_bGL_NV_read_buffer) {
		// Load the entry points
		bool bResult = true;	// Success by default
		IMPORT_FUNC(glReadBufferNV)
		m_bGL_NV_read_buffer = bResult;
	}

	//[-------------------------------------------------------]
	//[ OES                                                   ]
	//[-------------------------------------------------------]
	m_bGL_OES_mapbuffer = sExtensions.IsSubstring("GL_OES_mapbuffer");
	if (m_bGL_OES_mapbuffer) {
		// Load the entry points
		bool bResult = true;	// Success by default
		IMPORT_FUNC(glGetBufferPointervOES)
		IMPORT_FUNC(glMapBufferOES)
		IMPORT_FUNC(glUnmapBufferOES)
		m_bGL_OES_mapbuffer = bResult;
	}
	m_bGL_OES_element_index_uint = sExtensions.IsSubstring("GL_OES_element_index_uint");
	m_bGL_OES_texture_3D		 = sExtensions.IsSubstring("GL_OES_texture_3D");
	if (m_bGL_OES_texture_3D && !m_bGL_EXT_texture_array) {	// See "GL_EXT_texture_array"-comment above
		// Load the entry points
		bool bResult = true;	// Success by default
		IMPORT_FUNC(glTexImage3DOES)
		IMPORT_FUNC(glTexSubImage3DOES)
		IMPORT_FUNC(glCopyTexSubImage3DOES)
		IMPORT_FUNC(glCompressedTexImage3DOES)
		IMPORT_FUNC(glCompressedTexSubImage3DOES)
		IMPORT_FUNC(glFramebufferTexture3DOES)
		m_bGL_OES_texture_3D = bResult;
	}
	m_bGL_OES_packed_depth_stencil = sExtensions.IsSubstring("GL_OES_packed_depth_stencil");
	m_bGL_OES_depth24			   = sExtensions.IsSubstring("GL_OES_depth24");
	m_bGL_OES_depth32			   = sExtensions.IsSubstring("GL_OES_depth32");
	m_bGL_OES_vertex_half_float	   = sExtensions.IsSubstring("GL_OES_vertex_half_float");

	//[-------------------------------------------------------]
	//[ ANGLE                                                 ]
	//[-------------------------------------------------------]
	m_bGL_ANGLE_framebuffer_blit = sExtensions.IsSubstring("GL_ANGLE_framebuffer_blit");
	if (m_bGL_ANGLE_framebuffer_blit) {
		// Load the entry points
		bool bResult = true;	// Success by default
		IMPORT_FUNC(glBlitFramebufferEXT)
		m_bGL_ANGLE_framebuffer_blit = bResult;
	}
	m_bGL_ANGLE_framebuffer_multisample = sExtensions.IsSubstring("GL_ANGLE_framebuffer_multisample");
	if (m_bGL_ANGLE_framebuffer_multisample) {
		// Load the entry points
		bool bResult = true;	// Success by default
		IMPORT_FUNC(glRenderbufferStorageMultisampleANGLE)
		m_bGL_ANGLE_framebuffer_multisample = bResult;
	}

	// Undefine the helper macro
	#undef IMPORT_FUNC
}


//[-------------------------------------------------------]
//[ Public virtual Extensions functions                   ]
//[-------------------------------------------------------]
// ARB
bool ExtensionsRuntimeLinking::IsGL_ARB_draw_buffers() const
{
	return m_bGL_ARB_draw_buffers;
}

// EXT
bool ExtensionsRuntimeLinking::IsGL_EXT_texture_compression_s3tc() const
{
	return m_bGL_EXT_texture_compression_s3tc;
}

bool ExtensionsRuntimeLinking::IsGL_EXT_texture_compression_dxt1() const
{
	return m_bGL_EXT_texture_compression_dxt1;
}

bool ExtensionsRuntimeLinking::IsGL_EXT_texture_compression_latc() const
{
	return m_bGL_EXT_texture_compression_latc;
}

bool ExtensionsRuntimeLinking::IsGL_EXT_texture_filter_anisotropic() const
{
	return m_bGL_EXT_texture_filter_anisotropic;
}

bool ExtensionsRuntimeLinking::IsGL_EXT_texture_array() const
{
	return m_bGL_EXT_texture_array;
}

bool ExtensionsRuntimeLinking::IsGL_EXT_Cg_shader() const
{
	return m_bGL_EXT_Cg_shader;
}

// AMD
bool ExtensionsRuntimeLinking::IsGL_AMD_compressed_3DC_texture() const
{
	return m_bGL_AMD_compressed_3DC_texture;
}

// NV
bool ExtensionsRuntimeLinking::IsGL_NV_get_tex_image() const
{
	return m_bGL_NV_get_tex_image;
}

bool ExtensionsRuntimeLinking::IsGL_NV_fbo_color_attachments() const
{
	return m_bGL_NV_fbo_color_attachments;
}

bool ExtensionsRuntimeLinking::IsGL_NV_read_buffer() const
{
	return m_bGL_NV_read_buffer;
}

// OES
bool ExtensionsRuntimeLinking::IsGL_OES_mapbuffer() const
{
	return m_bGL_OES_mapbuffer;
}

bool ExtensionsRuntimeLinking::IsGL_OES_element_index_uint() const
{
	return m_bGL_OES_element_index_uint;
}

bool ExtensionsRuntimeLinking::IsGL_OES_texture_3D() const
{
	return m_bGL_OES_texture_3D;
}

bool ExtensionsRuntimeLinking::IsGL_OES_packed_depth_stencil() const
{
	return m_bGL_OES_packed_depth_stencil;
}

bool ExtensionsRuntimeLinking::IsGL_OES_depth24() const
{
	return m_bGL_OES_depth24;
}

bool ExtensionsRuntimeLinking::IsGL_OES_depth32() const
{
	return m_bGL_OES_depth32;
}

bool ExtensionsRuntimeLinking::IsGL_OES_vertex_half_float() const
{
	return m_bGL_OES_vertex_half_float;
}

// ANGLE
bool ExtensionsRuntimeLinking::IsGL_ANGLE_framebuffer_blit() const
{
	return m_bGL_ANGLE_framebuffer_blit;
}

bool ExtensionsRuntimeLinking::IsGL_ANGLE_framebuffer_multisample() const
{
	return m_bGL_ANGLE_framebuffer_multisample;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
