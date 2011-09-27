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
#include <PLCore/String/String.h>
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
	// AMD
	m_bGL_AMD_compressed_3DC_texture(false),
	// OES
	m_bGL_OES_element_index_uint(false)
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
	// Get the extensions string
	const String sExtensions = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));

	// EXT
	m_bGL_EXT_texture_compression_s3tc   = sExtensions.IsSubstring("GL_EXT_texture_compression_s3tc");
	m_bGL_EXT_texture_compression_dxt1   = sExtensions.IsSubstring("GL_EXT_texture_compression_dxt1");
	m_bGL_EXT_texture_compression_latc   = sExtensions.IsSubstring("GL_EXT_texture_compression_latc");
	m_bGL_EXT_texture_filter_anisotropic = sExtensions.IsSubstring("GL_EXT_texture_filter_anisotropic");

	// AMD
	m_bGL_AMD_compressed_3DC_texture = sExtensions.IsSubstring("GL_AMD_compressed_3DC_texture");

	// OES
	m_bGL_OES_element_index_uint = sExtensions.IsSubstring("GL_OES_element_index_uint");
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

// AMD
bool ExtensionsRuntimeLinking::IsGL_AMD_compressed_3DC_texture() const
{
	return m_bGL_AMD_compressed_3DC_texture;
}

// OES
bool ExtensionsRuntimeLinking::IsGL_OES_element_index_uint() const
{
	return m_bGL_OES_element_index_uint;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
