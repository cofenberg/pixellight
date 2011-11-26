/*********************************************************\
 *  File: ExtensionsRuntimeLinking.h                     *
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


#ifndef __PLRENDEREROPENGLES2_EXTENSIONSRUNTIMELINKING_H__
#define __PLRENDEREROPENGLES2_EXTENSIONSRUNTIMELINKING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
#include "PLRendererOpenGLES2/Context.h"
#include "PLRendererOpenGLES2/Extensions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL ES 2.0 extensions runtime linking
*/
class ExtensionsRuntimeLinking : public Extensions {


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		ExtensionsRuntimeLinking();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ExtensionsRuntimeLinking();

		/**
		*  @brief
		*    Initialize the supported extensions
		*
		*  @note
		*    - Do only call this method if the EGL functions initialization was successful ("glGetString()" is used)
		*      and there's an active render context
		*/
		void Init();


	//[-------------------------------------------------------]
	//[ Public virtual Extensions functions                   ]
	//[-------------------------------------------------------]
	public:
		///////////////////////////////////////////////////////////
		// Returns whether an extension is supported or not
		///////////////////////////////////////////////////////////
		// ARB
		virtual bool IsGL_ARB_draw_buffers() const override;
		// EXT
		virtual bool IsGL_EXT_texture_compression_s3tc() const override;
		virtual bool IsGL_EXT_texture_compression_dxt1() const override;
		virtual bool IsGL_EXT_texture_compression_latc() const override;
		virtual bool IsGL_EXT_texture_filter_anisotropic() const override;
		virtual bool IsGL_EXT_texture_array() const override;
		virtual bool IsGL_EXT_Cg_shader() const override;
		// AMD
		virtual bool IsGL_AMD_compressed_3DC_texture() const override;
		// NV
		virtual bool IsGL_NV_get_tex_image() const override;
		virtual bool IsGL_NV_fbo_color_attachments() const override;
		virtual bool IsGL_NV_read_buffer() const override;
		// OES
		virtual bool IsGL_OES_mapbuffer() const override;
		virtual bool IsGL_OES_element_index_uint() const override;
		virtual bool IsGL_OES_texture_3D() const override;
		virtual bool IsGL_OES_packed_depth_stencil() const override;
		virtual bool IsGL_OES_depth24() const override;
		virtual bool IsGL_OES_depth32() const override;
		// ANGLE
		virtual bool IsGL_ANGLE_framebuffer_blit() const override;
		virtual bool IsGL_ANGLE_framebuffer_multisample() const override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// ARB
		bool m_bGL_ARB_draw_buffers;
		// EXT
		bool m_bGL_EXT_texture_compression_s3tc;
		bool m_bGL_EXT_texture_compression_dxt1;
		bool m_bGL_EXT_texture_compression_latc;
		bool m_bGL_EXT_texture_filter_anisotropic;
		bool m_bGL_EXT_texture_array;
		bool m_bGL_EXT_Cg_shader;
		// AMD
		bool m_bGL_AMD_compressed_3DC_texture;
		// NV
		bool m_bGL_NV_get_tex_image;
		bool m_bGL_NV_fbo_color_attachments;
		bool m_bGL_NV_read_buffer;
		// OES
		bool m_bGL_OES_mapbuffer;
		bool m_bGL_OES_element_index_uint;
		bool m_bGL_OES_texture_3D;
		bool m_bGL_OES_packed_depth_stencil;
		bool m_bGL_OES_depth24;
		bool m_bGL_OES_depth32;
		// ANGLE
		bool m_bGL_ANGLE_framebuffer_blit;
		bool m_bGL_ANGLE_framebuffer_multisample;


};


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#ifdef EXTENSIONS_DEFINERUNTIMELINKING
	#define FNDEF_EX(retType, funcName, args) retType (GL_APIENTRY *funcPtr_##funcName) args = nullptr
#else
	#define FNDEF_EX(retType, funcName, args) extern retType (GL_APIENTRY *funcPtr_##funcName) args
#endif
#ifndef FNPTR
	#define FNPTR(name) funcPtr_##name
#endif


//[-------------------------------------------------------]
//[ ARB definitions                                       ]
//[-------------------------------------------------------]
// GL_ARB_draw_buffers
#define GL_MAX_DRAW_BUFFERS_ARB	0x8824
#define GL_DRAW_BUFFER0_ARB		0x8825
#define GL_DRAW_BUFFER1_ARB		0x8826
#define GL_DRAW_BUFFER2_ARB		0x8827
#define GL_DRAW_BUFFER3_ARB		0x8828
#define GL_DRAW_BUFFER4_ARB		0x8829
#define GL_DRAW_BUFFER5_ARB		0x882A
#define GL_DRAW_BUFFER6_ARB		0x882B
#define GL_DRAW_BUFFER7_ARB		0x882C
#define GL_DRAW_BUFFER8_ARB		0x882D
#define GL_DRAW_BUFFER9_ARB		0x882E
#define GL_DRAW_BUFFER10_ARB	0x882F
#define GL_DRAW_BUFFER11_ARB	0x8830
#define GL_DRAW_BUFFER12_ARB	0x8831
#define GL_DRAW_BUFFER13_ARB	0x8832
#define GL_DRAW_BUFFER14_ARB	0x8833
#define GL_DRAW_BUFFER15_ARB	0x8834
FNDEF_EX(void,	glDrawBuffersARB,	(GLsizei n, const GLenum *bufs));
#define glDrawBuffersARB	FNPTR(glDrawBuffersARB)


//[-------------------------------------------------------]
//[ EXT definitions                                       ]
//[-------------------------------------------------------]
// GL_EXT_texture_compression_s3tc
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT		0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT	0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT	0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT	0x83F3

// GL_EXT_texture_compression_dxt1
// #define GL_COMPRESSED_RGB_S3TC_DXT1_EXT	0x83F0	// Already defined for GL_EXT_texture_compression_s3tc

// GL_EXT_texture_compression_latc
#define GL_COMPRESSED_LUMINANCE_LATC1_EXT				0x8C70
#define GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT		0x8C71
#define GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT			0x8C72
#define GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT	0x8C73

// GL_EXT_texture_filter_anisotropic
#define GL_TEXTURE_MAX_ANISOTROPY_EXT		0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT	0x84FF

// GL_EXT_texture_array
#define GL_TEXTURE_1D_ARRAY_EXT						0x8C18
#define GL_TEXTURE_2D_ARRAY_EXT						0x8C1A
#define GL_PROXY_TEXTURE_2D_ARRAY_EXT				0x8C1B
#define GL_PROXY_TEXTURE_1D_ARRAY_EXT				0x8C19
#define GL_TEXTURE_BINDING_1D_ARRAY_EXT				0x8C1C
#define GL_TEXTURE_BINDING_2D_ARRAY_EXT				0x8C1D
#define GL_MAX_ARRAY_TEXTURE_LAYERS_EXT				0x88FF
#define GL_COMPARE_REF_DEPTH_TO_TEXTURE_EXT			0x884E
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER_EXT	0x8CD4
#define GL_SAMPLER_1D_ARRAY_EXT						0x8DC0
#define GL_SAMPLER_2D_ARRAY_EXT						0x8DC1
#define GL_SAMPLER_1D_ARRAY_SHADOW_EXT				0x8DC3
#define GL_SAMPLER_2D_ARRAY_SHADOW_EXT				0x8DC4

// GL_EXT_Cg_shader
#define GL_CG_VERTEX_SHADER_EXT		0x890E
#define GL_CG_FRAGMENT_SHADER_EXT	0x890F


//[-------------------------------------------------------]
//[ AMD definitions                                       ]
//[-------------------------------------------------------]
// GL_AMD_compressed_3DC_texture
#define GL_3DC_X_AMD	0x87F9
#define GL_3DC_XY_AMD	0x87FA


//[-------------------------------------------------------]
//[ NV definitions                                        ]
//[-------------------------------------------------------]
// GL_NV_get_tex_image
#define GL_TEXTURE_WIDTH_NV					0x1000
#define GL_TEXTURE_HEIGHT_NV				0x1001
#define GL_TEXTURE_INTERNAL_FORMAT_NV		0x1003
#define GL_TEXTURE_COMPONENTS_NV			GL_TEXTURE_INTERNAL_FORMAT_NV
#define GL_TEXTURE_BORDER_NV				0x1005
#define GL_TEXTURE_RED_SIZE_NV				0x805C
#define GL_TEXTURE_GREEN_SIZE_NV			0x805D
#define GL_TEXTURE_BLUE_SIZE_NV				0x805E
#define GL_TEXTURE_ALPHA_SIZE_NV			0x805F
#define GL_TEXTURE_LUMINANCE_SIZE_NV		0x8060
#define GL_TEXTURE_INTENSITY_SIZE_NV		0x8061
#define GL_TEXTURE_DEPTH_NV					0x8071
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE_NV	0x86A0
#define GL_TEXTURE_COMPRESSED_NV			0x86A1
#define GL_TEXTURE_DEPTH_SIZE_NV			0x884A
FNDEF_EX(void,	glGetTexImageNV,			(GLenum target, GLint level, GLenum format, GLenum type, GLvoid *img));
FNDEF_EX(void,	glGetCompressedTexImageNV,	(GLenum target, GLint level, GLvoid *img));
FNDEF_EX(void,	glGetTexLevelParameterfvNV,	(GLenum target, GLint level, GLenum pname, GLfloat *params));
FNDEF_EX(void,	glGetTexLevelParameterivNV,	(GLenum target, GLint level, GLenum pname, GLint *params));
#define glGetTexImageNV				FNPTR(glGetTexImageNV)
#define glGetCompressedTexImageNV	FNPTR(glGetCompressedTexImageNV)
#define glGetTexLevelParameterfvNV	FNPTR(glGetTexLevelParameterfvNV)
#define glGetTexLevelParameterivNV	FNPTR(glGetTexLevelParameterivNV)

// GL_NV_fbo_color_attachments
#define GL_COLOR_ATTACHMENT0_NV		0x8CE0	// Same value as GL_COLOR_ATTACHMENT0
#define GL_COLOR_ATTACHMENT1_NV		0x8CE1
#define GL_COLOR_ATTACHMENT2_NV		0x8CE2
#define GL_COLOR_ATTACHMENT3_NV		0x8CE3
#define GL_COLOR_ATTACHMENT4_NV		0x8CE4
#define GL_COLOR_ATTACHMENT5_NV		0x8CE5
#define GL_COLOR_ATTACHMENT6_NV		0x8CE6
#define GL_COLOR_ATTACHMENT7_NV		0x8CE7
#define GL_COLOR_ATTACHMENT8_NV		0x8CE8
#define GL_COLOR_ATTACHMENT9_NV		0x8CE9
#define GL_COLOR_ATTACHMENT10_NV	0x8CEA
#define GL_COLOR_ATTACHMENT11_NV	0x8CEB
#define GL_COLOR_ATTACHMENT12_NV	0x8CEC
#define GL_COLOR_ATTACHMENT13_NV	0x8CED
#define GL_COLOR_ATTACHMENT14_NV	0x8CEE
#define GL_COLOR_ATTACHMENT15_NV	0x8CEF

// GL_NV_read_buffer
#define GL_READ_BUFFER_NV	0x0C02
FNDEF_EX(void,	glReadBufferNV,	(GLenum src));
#define glReadBufferNV	FNPTR(glReadBufferNV)


//[-------------------------------------------------------]
//[ OES definitions                                       ]
//[-------------------------------------------------------]
// GL_OES_mapbuffer
#define GL_WRITE_ONLY_OES			0x88B9
#define GL_BUFFER_ACCESS_OES		0x88BB
#define GL_BUFFER_MAPPED_OES		0x88BC
#define GL_BUFFER_MAP_POINTER_OES	0x88BD
FNDEF_EX(void,		glGetBufferPointervOES,	(GLenum target, GLenum pname, void **params));
FNDEF_EX(void *,	glMapBufferOES,			(GLenum target, GLenum access));
FNDEF_EX(GLboolean,	glUnmapBufferOES,		(GLenum target));
#define glGetBufferPointervOES	FNPTR(glGetBufferPointervOES)
#define glMapBufferOES			FNPTR(glMapBufferOES)
#define glUnmapBufferOES		FNPTR(glUnmapBufferOES)

// GL_OES_element_index_uint
#define GL_UNSIGNED_INT	0x1405

// GL_OES_texture_3D
#define GL_TEXTURE_3D_OES			0x806F
#define GL_TEXTURE_WRAP_R_OES		0x8072
#define GL_MAX_3D_TEXTURE_SIZE_OES	0x8073
#define GL_TEXTURE_BINDING_3D_OES	0x806A
FNDEF_EX(void,	glTexImage3DOES,				(GLenum target, int level, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, int border, GLenum format, GLenum type, const void *pixels));
FNDEF_EX(void,	glTexSubImage3DOES,				(GLenum target, int level, int xoffset, int yoffset, int zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels));
FNDEF_EX(void,	glCopyTexSubImage3DOES,			(GLenum target, int level, int xoffset, int yoffset, int zoffset, int x, int y, GLsizei width, GLsizei height));
FNDEF_EX(void,	glCompressedTexImage3DOES,		(GLenum target, int level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, int border, GLsizei imageSize, const void *data));
FNDEF_EX(void,	glCompressedTexSubImage3DOES,	(GLenum target, int level, int xoffset, int yoffset, int zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data));
FNDEF_EX(void,	glFramebufferTexture3DOES,		(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, int level, int zoffset));
#define glTexImage3DOES					FNPTR(glTexImage3DOES)
#define glTexSubImage3DOES				FNPTR(glTexSubImage3DOES)
#define glCopyTexSubImage3DOES			FNPTR(glCopyTexSubImage3DOES)
#define glCompressedTexImage3DOES		FNPTR(glCompressedTexImage3DOES)
#define glCompressedTexSubImage3DOES	FNPTR(glCompressedTexSubImage3DOES)
#define glFramebufferTexture3DOES		FNPTR(glFramebufferTexture3DOES)

// GL_OES_packed_depth_stencil
#define GL_DEPTH_STENCIL_OES		0x84F9
#define GL_UNSIGNED_INT_24_8_OES	0x84FA
#define GL_DEPTH24_STENCIL8_OES		0x88F0

// GL_OES_depth24
#define GL_DEPTH_COMPONENT24_OES	0x81A6

// GL_OES_depth32
#define GL_DEPTH_COMPONENT32_OES	0x81A7 


//[-------------------------------------------------------]
//[ ANGLE definitions                                     ]
//[-------------------------------------------------------]
// GL_ANGLE_framebuffer_blit
#define GL_READ_FRAMEBUFFER_EXT			0x8CA8
#define GL_DRAW_FRAMEBUFFER_EXT			0x8CA9
#define GL_DRAW_FRAMEBUFFER_BINDING_EXT	0x8CA6
#define GL_READ_FRAMEBUFFER_BINDING_EXT	0x8CAA
FNDEF_EX(void,	glBlitFramebufferEXT,	(int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, GLbitfield mask, GLenum filter));
#define glBlitFramebufferEXT	FNPTR(glBlitFramebufferEXT)

// GL_ANGLE_framebuffer_multisample
#define GL_RENDERBUFFER_SAMPLES_ANGLE				0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_ANGLE	0x8D56
#define GL_MAX_SAMPLES_ANGLE						0x8D57
FNDEF_EX(void,	glRenderbufferStorageMultisampleANGLE,	(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height));
#define glRenderbufferStorageMultisampleANGLE	FNPTR(glRenderbufferStorageMultisampleANGLE)


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef FNDEF_EX


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2


#endif // __PLRENDEREROPENGLES2_EXTENSIONSRUNTIMELINKING_H__
