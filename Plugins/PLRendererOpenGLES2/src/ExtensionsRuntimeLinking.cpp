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
	// EXT
	m_bGL_EXT_texture_compression_s3tc(false),
	m_bGL_EXT_texture_compression_dxt1(false),
	m_bGL_EXT_texture_compression_latc(false),
	m_bGL_EXT_texture_filter_anisotropic(false),
	m_bGL_EXT_Cg_shader(false),
	// AMD
	m_bGL_AMD_compressed_3DC_texture(false),
	// NV
	m_bGL_NV_get_tex_image(false),
	// OES
	m_bGL_OES_mapbuffer(false),
	m_bGL_OES_element_index_uint(false),
	m_bGL_OES_texture_3D(false)
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

	// EXT
	m_bGL_EXT_texture_compression_s3tc   = sExtensions.IsSubstring("GL_EXT_texture_compression_s3tc");
	m_bGL_EXT_texture_compression_dxt1   = sExtensions.IsSubstring("GL_EXT_texture_compression_dxt1");
	m_bGL_EXT_texture_compression_latc   = sExtensions.IsSubstring("GL_EXT_texture_compression_latc");
	m_bGL_EXT_texture_filter_anisotropic = sExtensions.IsSubstring("GL_EXT_texture_filter_anisotropic");
	m_bGL_EXT_Cg_shader					 = sExtensions.IsSubstring("GL_EXT_Cg_shader");

	// AMD
	m_bGL_AMD_compressed_3DC_texture = sExtensions.IsSubstring("GL_AMD_compressed_3DC_texture");

	// NV
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

	// OES
	m_bGL_OES_mapbuffer			 = sExtensions.IsSubstring("GL_OES_mapbuffer");
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
	if (m_bGL_OES_texture_3D) {
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

	// Undefine the helper macro
	#undef IMPORT_FUNC
}


//[-------------------------------------------------------]
//[ Public virtual Extensions functions                   ]
//[-------------------------------------------------------]
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
