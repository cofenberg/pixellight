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
#include <PLCore/Log/Log.h>
#define EXTENSIONS_DEFINE
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/Extensions.h"
#ifdef APPLE
	#include <string.h>	// For strstr
	// [TODO] Implement Mac OS X implementation
#elif defined(LINUX)
	#include <string.h>	// For strstr
	#include "PLRendererOpenGL/Linux/ContextLinux.h"
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGL {


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
bool OpenGLExtensions::IsGL_ARB_texture_non_power_of_two()		const { return m_bGL_ARB_texture_non_power_of_two;	 }
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
			// Extension is supported!
			PL_LOG(Info, String("Use extension: ") + pszExtension)
			return true;
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
				#ifdef APPLE
					// [TODO] Implement Mac OS X implementation
				#elif defined(LINUX)
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
	m_bGL_ARB_texture_non_power_of_two		= false;
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
