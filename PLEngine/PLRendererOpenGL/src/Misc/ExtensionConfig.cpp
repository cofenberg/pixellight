/*********************************************************\
 *  File: ExtensionConfig.cpp                            *
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
#include "PLRendererOpenGL/Misc/ExtensionConfig.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(RendererOpenGLExtensionConfig)


//[-------------------------------------------------------]
//[ Public functions                                       ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
RendererOpenGLExtensionConfig::RendererOpenGLExtensionConfig() :
	// WGL (Windows only)
	WGL_EXT_swap_control(this),
	WGL_ARB_extensions_string(this),
	WGL_ARB_pbuffer(this),
	WGL_ARB_pixel_format(this),
	WGL_ARB_render_texture(this),
	WGL_ARB_make_current_read(this),
	WGL_ARB_multisample(this),
	WGL_ATI_pixel_format_float(this),
	WGL_NV_float_buffer(this),
	// EXT
	GL_EXT_compiled_vertex_array(this),
	GL_EXT_draw_range_elements(this),
	GL_EXT_fog_coord(this),
	GL_EXT_secondary_color(this),
	GL_EXT_texture_compression_s3tc(this),
	GL_EXT_texture_compression_latc(this),
	GL_EXT_texture_lod_bias(this),
	GL_EXT_texture_filter_anisotropic(this),
	GL_EXT_separate_specular_color(this),
	GL_EXT_texture_edge_clamp(this),
	GL_EXT_texture_rectangle(this),
	GL_EXT_texture3D(this),
	GL_EXT_texture_cube_map(this),
	GL_EXT_stencil_wrap(this),
	GL_EXT_stencil_two_side(this),
	GL_EXT_packed_depth_stencil(this),
	GL_EXT_depth_bounds_test(this),
	GL_EXT_framebuffer_object(this),
	GL_EXT_framebuffer_multisample(this),
	GL_EXT_framebuffer_blit(this),
	GL_EXT_geometry_shader4(this),
	GL_EXT_transform_feedback(this),
	// ARB
	GL_ARB_texture_float(this),
	GL_ARB_color_buffer_float(this),
	GL_ARB_multitexture(this),
	GL_ARB_vertex_buffer_object(this),
	GL_ARB_texture_border_clamp(this),
	GL_ARB_texture_mirrored_repeat(this),
	GL_ARB_texture_cube_map(this),
	GL_ARB_texture_env_combine(this),
	GL_ARB_texture_env_dot3(this),
	GL_ARB_occlusion_query(this),
	GL_ARB_texture_compression(this),
	GL_ARB_depth_texture(this),
	GL_ARB_point_sprite(this),
	GL_ARB_point_parameters(this),
	GL_ARB_vertex_program(this),
	GL_ARB_fragment_program(this),
	GL_ARB_draw_buffers(this),
	GL_ARB_shader_objects(this),
	GL_ARB_vertex_shader(this),
	GL_ARB_get_program_binary(this),
	GL_ARB_texture_non_power_of_two(this),
	GL_ARB_texture_rectangle(this),
	GL_ARB_multisample(this),
	GL_ARB_uniform_buffer_object(this),
	// ATI
	GL_ATI_separate_stencil(this),
	GL_ATI_draw_buffers(this),
	// AMD
	GL_AMD_vertex_shader_tessellator(this),
	// NV
	GL_NV_texture_rectangle(this),
	GL_NV_occlusion_query(this),
	// SGIS
	GL_SGIS_generate_mipmap(this),
	// HP
	GL_HP_occlusion_test(this),
	// GLX (Linux only)
	GLX_SGIX_pbuffer(this),
	GLX_ARB_multisample(this),
	GLX_ATI_pixel_format_float(this),
	GLX_NV_float_buffer(this)
{
}

/**
*  @brief
*    Destructor
*/
RendererOpenGLExtensionConfig::~RendererOpenGLExtensionConfig()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
