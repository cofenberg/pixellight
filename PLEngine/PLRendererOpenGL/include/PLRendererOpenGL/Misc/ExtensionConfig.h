/*********************************************************\
 *  File: ExtensionConfig.h                              *
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


#ifndef __PLRENDEREROPENGL_EXTENSIONCONFIG_H__
#define __PLRENDEREROPENGL_EXTENSIONCONFIG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Config/Config.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Renderer OpenGL extension configuration class
*/
class RendererOpenGLExtensionConfig : public PLCore::ConfigGroup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, RendererOpenGLExtensionConfig, "PLRendererOpenGL", PLCore::ConfigGroup, "Renderer OpenGL extension configuration class")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		// WGL (Windows only)
		pl_attribute(WGL_EXT_swap_control,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(WGL_ARB_extensions_string,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(WGL_ARB_pbuffer,					bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(WGL_ARB_pixel_format,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(WGL_ARB_render_texture,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(WGL_ARB_make_current_read,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(WGL_ARB_multisample,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(WGL_ATI_pixel_format_float,		bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(WGL_NV_float_buffer,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		// EXT
		pl_attribute(GL_EXT_compiled_vertex_array,		bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_draw_range_elements,		bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_fog_coord,					bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_secondary_color,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_texture_compression_s3tc,	bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_texture_compression_latc,	bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_texture_lod_bias,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_texture_filter_anisotropic,	bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_separate_specular_color,	bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_texture_edge_clamp,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_texture_rectangle,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_texture3D,					bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_texture_cube_map,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_stencil_wrap,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_stencil_two_side,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_packed_depth_stencil,		bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_depth_bounds_test,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_framebuffer_object,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_framebuffer_multisample,	bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_framebuffer_blit,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_geometry_shader4,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_EXT_transform_feedback,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		// ARB
		pl_attribute(GL_ARB_texture_float,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_color_buffer_float,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_multitexture,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_vertex_buffer_object,		bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_texture_border_clamp,		bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_texture_mirrored_repeat,	bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_texture_cube_map,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_texture_env_combine,		bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_texture_env_dot3,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_occlusion_query,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_texture_compression,		bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_depth_texture,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_point_sprite,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_point_parameters,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_vertex_program,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_fragment_program,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_draw_buffers,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_shader_objects,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_vertex_shader,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_get_program_binary,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_texture_rectangle,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_multisample,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ARB_uniform_buffer_object,		bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		// ATI
		pl_attribute(GL_ATI_separate_stencil,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_ATI_draw_buffers,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		// AMD
		pl_attribute(GL_AMD_vertex_shader_tessellator,	bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		// NV
		pl_attribute(GL_NV_texture_rectangle,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GL_NV_occlusion_query,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		// SGIS
		pl_attribute(GL_SGIS_generate_mipmap,			bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		// HP
		pl_attribute(GL_HP_occlusion_test,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		// GLX (Linux only)
		pl_attribute(GLX_SGIX_pbuffer,					bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GLX_ARB_multisample,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GLX_ATI_pixel_format_float,		bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
		pl_attribute(GLX_NV_float_buffer,				bool,	true,	ReadWrite,	DirectValue,	"Use extension?",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		RendererOpenGLExtensionConfig();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~RendererOpenGLExtensionConfig();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_EXTENSIONCONFIG_H__
