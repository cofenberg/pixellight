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
		// EXT
		virtual bool IsGL_EXT_texture_compression_s3tc() const override;
		virtual bool IsGL_EXT_texture_compression_dxt1() const override;
		virtual bool IsGL_EXT_texture_compression_latc() const override;
		virtual bool IsGL_EXT_texture_filter_anisotropic() const override;
		virtual bool IsGL_EXT_Cg_shader() const override;
		// AMD
		virtual bool IsGL_AMD_compressed_3DC_texture() const override;
		// NV
		virtual bool IsGL_NV_get_tex_image() const override;
		// OES
		virtual bool IsGL_OES_mapbuffer() const override;
		virtual bool IsGL_OES_element_index_uint() const override;
		virtual bool IsGL_OES_texture_3D() const override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// EXT
		bool m_bGL_EXT_texture_compression_s3tc;
		bool m_bGL_EXT_texture_compression_dxt1;
		bool m_bGL_EXT_texture_compression_latc;
		bool m_bGL_EXT_texture_filter_anisotropic;
		bool m_bGL_EXT_Cg_shader;
		// AMD
		bool m_bGL_AMD_compressed_3DC_texture;
		// NV
		bool m_bGL_NV_get_tex_image;
		// OES
		bool m_bGL_OES_mapbuffer;
		bool m_bGL_OES_element_index_uint;
		bool m_bGL_OES_texture_3D;


};


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#ifdef EXTENSIONS_DEFINERUNTIMELINKING
	#define FNDEF_EX(retType, funcName, args) retType (GL_APIENTRY *funcPtr_##funcName) args
#else
	#define FNDEF_EX(retType, funcName, args) extern retType (GL_APIENTRY *funcPtr_##funcName) args
#endif
#ifndef FNPTR
	#define FNPTR(name) funcPtr_##name
#endif


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


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef FNDEF_EX


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2


#endif // __PLRENDEREROPENGLES2_EXTENSIONSRUNTIMELINKING_H__
