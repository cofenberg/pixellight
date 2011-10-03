/*********************************************************\
 *  File: ShaderLanguageCg.h                             *
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


#ifndef __PLRENDEREROPENGLES2_SHADERLANGUAGECG_H__
#define __PLRENDEREROPENGLES2_SHADERLANGUAGECG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/ShaderLanguage.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Renderer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Build in OpenGL ES Cg shader language using the "GL_EXT_Cg_shader"-extension
*
*  @note
*    - See "GLSL Release Notes for Release 60.pdf" ftp://download.nvidia.com/developer/GLSL/GLSL%20Release%20Notes%20for%20Release%2060.pdf
*      page 13 for information about this extension
*/
class ShaderLanguageCg : public PLRenderer::ShaderLanguage {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Renderer;


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		static const PLCore::String Cg;	/**< 'Cg' string */


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, ShaderLanguageCg, "PLRendererOpenGLES2", PLRenderer::ShaderLanguage, "OpenGL ES Cg shader language class using the \"GL_EXT_Cg_shader\"-extension")
		// Properties
		pl_properties
			pl_property("ShaderLanguage",	"Cg")
		pl_properties_end
		// Constructors
		pl_constructor_1(DefaultConstructor,	PLRenderer::Renderer&,	"Constructor with used renderer as parameter",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::ShaderLanguage functions   ]
	//[-------------------------------------------------------]
	public:
		virtual PLCore::String GetShaderLanguage() const override;
		virtual PLRenderer::VertexShader *CreateVertexShader() override;
		virtual PLRenderer::GeometryShader *CreateGeometryShader() override;
		virtual PLRenderer::FragmentShader *CreateFragmentShader() override;
		virtual PLRenderer::Program *CreateProgram() override;
		virtual PLRenderer::UniformBuffer *CreateUniformBuffer() override;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    The used renderer
		*/
		ShaderLanguageCg(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ShaderLanguageCg();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::Renderer *m_pRenderer;	/**< The used renderer, always valid! */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2


#endif // __PLRENDEREROPENGLES2_SHADERLANGUAGECG_H__
