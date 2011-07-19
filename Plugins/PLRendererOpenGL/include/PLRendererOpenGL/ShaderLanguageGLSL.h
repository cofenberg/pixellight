/*********************************************************\
 *  File: ShaderLanguageGLSL.h                           *
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


#ifndef __PLRENDEREROPENGL_SHADERLANGUAGEGLSL_H__
#define __PLRENDEREROPENGL_SHADERLANGUAGEGLSL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRendererOpenGL/ShaderLanguage.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Renderer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Build in OpenGL GLSL shader language class
*/
class ShaderLanguageGLSL : public ShaderLanguage {


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		static const PLCore::String GLSL;	/**< 'GLSL' string */


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDEREROPENGL_RTTI_EXPORT, ShaderLanguageGLSL, "PLRendererOpenGL", PLRendererOpenGL::ShaderLanguage, "Build in OpenGL GLSL shader language class")
		// Properties
		pl_properties
			pl_property("ShaderLanguage",	"GLSL")
		pl_properties_end
		// Constructors
		pl_constructor_1(DefaultConstructor,	PLRenderer::Renderer&,	"Constructor with used renderer as parameter",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::ShaderLanguage functions   ]
	//[-------------------------------------------------------]
	public:
		virtual PLCore::String GetShaderLanguage() const;
		virtual PLRenderer::VertexShader *CreateVertexShader();
		virtual PLRenderer::GeometryShader *CreateGeometryShader();
		virtual PLRenderer::FragmentShader *CreateFragmentShader();
		virtual PLRenderer::Program *CreateProgram();
		virtual PLRenderer::UniformBuffer *CreateUniformBuffer();


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
		ShaderLanguageGLSL(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ShaderLanguageGLSL();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::Renderer *m_pRenderer;	/**< The used renderer, always valid! */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_SHADERLANGUAGEGLSL_H__
