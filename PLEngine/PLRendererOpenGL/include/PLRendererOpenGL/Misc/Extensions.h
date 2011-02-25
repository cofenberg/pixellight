/*********************************************************\
 *  File: Extensions.h                                   *
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


#ifndef __PLRENDEREROPENGL_EXTENSIONS_H__
#define __PLRENDEREROPENGL_EXTENSIONS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRendererOpenGL/Misc/ExtensionDefinitions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Renderer;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Supported OpenGL graphic card extensions
*
*  @note
*    - You must check if the extension is supported by the current hardware before
*      you use it. If the extension isn't available you should offer an alternativ
*      technique
*    - If you add a new extension, don't forget to add it to RendererOpenGLExtensionConfig, too
*
*  @see
*    - OpenGL extension registry at http://oss.sgi.com/projects/ogl-sample/registry/ for more information about
*      the different extensions
*/
class OpenGLExtensions {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Renderer;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*/
		OpenGLExtensions(Renderer &cRenderer);

		/**
		*  @brief
		*    Returns whether the extensions are initialized or not
		*
		*  @return
		*    'true' if the extension are initialized, else 'false'
		*/
		bool IsInitialized() const;

		///////////////////////////////////////////////////////////
		// Returns whether an extension is supported or not
		///////////////////////////////////////////////////////////
		// WGL (Windows only)
		bool IsWGL_EXT_swap_control() const;
		bool IsWGL_ARB_extensions_string() const;
		bool IsWGL_ARB_pbuffer() const;
		bool IsWGL_ARB_pixel_format() const;
		bool IsWGL_ARB_render_texture() const;
		bool IsWGL_ARB_make_current_read() const;
		bool IsWGL_ARB_multisample() const;
		bool IsWGL_ATI_pixel_format_float() const;
		bool IsWGL_NV_float_buffer() const;
		// EXT
		bool IsGL_EXT_compiled_vertex_array() const;
		bool IsGL_EXT_draw_range_elements() const;
		bool IsGL_EXT_fog_coord() const;
		bool IsGL_EXT_secondary_color() const;
		bool IsGL_EXT_texture_compression_s3tc() const;
		bool IsGL_EXT_texture_compression_latc() const;
		bool IsGL_EXT_texture_lod_bias() const;
		bool IsGL_EXT_texture_filter_anisotropic() const;
		bool IsGL_EXT_separate_specular_color() const;
		bool IsGL_EXT_texture_edge_clamp() const;
		bool IsGL_EXT_texture_rectangle() const;
		bool IsGL_EXT_texture3D() const;
		bool IsGL_EXT_texture_cube_map() const;
		bool IsGL_EXT_stencil_wrap() const;
		bool IsGL_EXT_stencil_two_side() const;
		bool IsGL_EXT_packed_depth_stencil() const;
		bool IsGL_EXT_depth_bounds_test() const;
		bool IsGL_EXT_framebuffer_object() const;
		bool IsGL_EXT_framebuffer_multisample() const;
		bool IsGL_EXT_framebuffer_blit() const;
		bool IsGL_EXT_geometry_shader4() const;
		// ARB
		bool IsGL_ARB_texture_float() const;
		bool IsGL_ARB_color_buffer_float() const;
		bool IsGL_ARB_multitexture() const;
		bool IsGL_ARB_vertex_buffer_object() const;
		bool IsGL_ARB_texture_border_clamp() const;
		bool IsGL_ARB_texture_mirrored_repeat() const;
		bool IsGL_ARB_texture_cube_map() const;
		bool IsGL_ARB_texture_env_combine() const;
		bool IsGL_ARB_texture_env_dot3() const;
		bool IsGL_ARB_occlusion_query() const;
		bool IsGL_ARB_texture_compression() const;
		bool IsGL_ARB_depth_texture() const;
		bool IsGL_ARB_point_sprite() const;
		bool IsGL_ARB_point_parameters() const;
		bool IsGL_ARB_shading_language_100() const;
		bool IsGL_ARB_vertex_program() const;
		bool IsGL_ARB_fragment_program() const;
		bool IsGL_ARB_draw_buffers() const;
		bool IsGL_ARB_shader_objects() const;
		bool IsGL_ARB_vertex_shader() const;
		bool IsGL_ARB_get_program_binary() const;
		bool IsGL_ARB_texture_rectangle() const;
		bool IsGL_ARB_multisample() const;
		// ATI
		bool IsGL_ATI_separate_stencil() const;
		bool IsGL_ATI_draw_buffers() const;
		bool IsGL_ATI_texture_compression_3dc() const;
		// AMD
		bool IsGL_AMD_vertex_shader_tessellator() const;
		// NV
		bool IsGL_NV_texture_rectangle() const;
		bool IsGL_NV_occlusion_query() const;
		// SGIS
		bool IsGL_SGIS_generate_mipmap() const;
		// HP
		bool IsGL_HP_occlusion_test() const;

		///////////////////////////////////////////////////////////
		// Misc
		///////////////////////////////////////////////////////////
		GLint GetGL_MAX_ELEMENTS_VERTICES_EXT() const;
		GLint GetGL_MAX_ELEMENTS_INDICES_EXT() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Initialize the supported extensions
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool Init();

		/**
		*  @brief
		*    Checks whether an extension is supported by the given hardware or not
		*
		*  @param[in] pszExtension
		*    Name of the extension, if a null pointer, nothing happens
		*
		*  @return
		*    'true' if the extensions is supported, else 'false'
		*/
		bool IsSupported(const char *pszExtension) const;

		/**
		*  @brief
		*    Checks whether an extension is supported by the given hardware or not
		*
		*  @param[in] pszExtension
		*    Name of the extension, if a null pointer, nothing happens
		*
		*  @return
		*    'true' if the extensions is supported, else 'false'
		*/
		bool CheckExtension(const char *pszExtension) const;

		/**
		*  @brief
		*    Resets the extensions
		*/
		void ResetExtensions();

		/**
		*  @brief
		*    Shows general OpenGL information
		*/
		void ShowGeneralOpenGLInformation() const;

		/**
		*  @brief
		*    Shows OpenGL shader program information
		*
		*  @param[in] nTarget
		*    Target (vertex, fragment etc.)
		*/
		void ShowOpenGLShaderProgramInformation(PLGeneral::uint32 nTarget) const;

		/**
		*  @brief
		*    Writes the extensions within a given extension string into the log
		*
		*  @param[in] pszExtensions
		*    Extension string, if a null pointer, nothing happens
		*/
		void WriteExtensionStringIntoLog(const char *pszExtensions) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Renderer *m_pRenderer;		/**< Owner renderer, always valid! */
		bool 	  m_bInitialized;	/**< Are the extensions initialized? */

		// Supported extensions
		// WGL (Windows only)
		bool m_bWGL_EXT_swap_control;
		bool m_bWGL_ARB_extensions_string;
		bool m_bWGL_ARB_pbuffer;
		bool m_bWGL_ARB_pixel_format;
		bool m_bWGL_ARB_render_texture;
		bool m_bWGL_ARB_make_current_read;
		bool m_bWGL_ARB_multisample;
		bool m_bWGL_ATI_pixel_format_float;
		bool m_bWGL_NV_float_buffer;
		// EXT
		bool m_bGL_EXT_compiled_vertex_array;
		bool m_bGL_EXT_draw_range_elements;
		bool m_bGL_EXT_fog_coord;
		bool m_bGL_EXT_secondary_color;
		bool m_bGL_EXT_texture_compression_s3tc;
		bool m_bGL_EXT_texture_compression_latc;
		bool m_bGL_EXT_texture_lod_bias;
		bool m_bGL_EXT_texture_filter_anisotropic;
		bool m_bGL_EXT_separate_specular_color;
		bool m_bGL_EXT_texture_edge_clamp;
		bool m_bGL_EXT_texture_rectangle;
		bool m_bGL_EXT_texture3D;
		bool m_bGL_EXT_texture_cube_map;
		bool m_bGL_EXT_stencil_wrap;
		bool m_bGL_EXT_stencil_two_side;
		bool m_bGL_EXT_packed_depth_stencil;
		bool m_bGL_EXT_depth_bounds_test;
		bool m_bGL_EXT_framebuffer_object;
		bool m_bGL_EXT_framebuffer_multisample;
		bool m_bGL_EXT_framebuffer_blit;
		bool m_bGL_EXT_geometry_shader4;
		// ARB
		bool m_bGL_ARB_texture_float;
		bool m_bGL_ARB_color_buffer_float;
		bool m_bGL_ARB_multitexture;
		bool m_bGL_ARB_vertex_buffer_object;
		bool m_bGL_ARB_texture_border_clamp;
		bool m_bGL_ARB_texture_mirrored_repeat;
		bool m_bGL_ARB_texture_cube_map;
		bool m_bGL_ARB_texture_env_combine;
		bool m_bGL_ARB_texture_env_dot3;
		bool m_bGL_ARB_occlusion_query;
		bool m_bGL_ARB_texture_compression;
		bool m_bGL_ARB_depth_texture;
		bool m_bGL_ARB_point_sprite;
		bool m_bGL_ARB_point_parameters;
		bool m_bGL_ARB_shading_language_100;
		bool m_bGL_ARB_vertex_program;
		bool m_bGL_ARB_fragment_program;
		bool m_bGL_ARB_draw_buffers;
		bool m_bGL_ARB_shader_objects;
		bool m_bGL_ARB_vertex_shader;
		bool m_bGL_ARB_get_program_binary;
		bool m_bGL_ARB_texture_rectangle;
		bool m_bGL_ARB_multisample;
		// ATI
		bool m_bGL_ATI_separate_stencil;
		bool m_bGL_ATI_draw_buffers;
		bool m_bGL_ATI_texture_compression_3dc;
		// AMD
		bool m_bGL_AMD_vertex_shader_tessellator;
		// NV
		bool m_bGL_NV_texture_rectangle;
		bool m_bGL_NV_occlusion_query;
		// SGIS
		bool m_bGL_SGIS_generate_mipmap;
		// HP
		bool m_bGL_HP_occlusion_test;

		// Misc
		GLint m_nGL_MAX_ELEMENTS_VERTICES_EXT;
		GLint m_nGL_MAX_ELEMENTS_INDICES_EXT;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_EXTENSIONS_H__
