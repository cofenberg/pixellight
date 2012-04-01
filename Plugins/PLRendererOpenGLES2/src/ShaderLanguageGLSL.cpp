/*********************************************************\
 *  File: ShaderLanguageGLSL.cpp                         *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLRendererOpenGLES2/ProgramGLSL.h"
#include "PLRendererOpenGLES2/VertexShaderGLSL.h"
#include "PLRendererOpenGLES2/FragmentShaderGLSL.h"
#include "PLRendererOpenGLES2/ShaderLanguageGLSL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const String ShaderLanguageGLSL::GLSL = "GLSL";


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ShaderLanguageGLSL)


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::ShaderLanguage functions   ]
//[-------------------------------------------------------]
String ShaderLanguageGLSL::GetShaderLanguage() const
{
	return GLSL;
}

PLRenderer::VertexShader *ShaderLanguageGLSL::CreateVertexShader()
{
	return new VertexShaderGLSL(*m_pRenderer);
}

PLRenderer::TessellationControlShader *ShaderLanguageGLSL::CreateTessellationControlShader()
{
	// OpenGL ES 2.0 has no support for tessellation control shaders
	return nullptr;
}

PLRenderer::TessellationEvaluationShader *ShaderLanguageGLSL::CreateTessellationEvaluationShader()
{
	// OpenGL ES 2.0 has no support for tessellation evaluation shaders
	return nullptr;
}

PLRenderer::GeometryShader *ShaderLanguageGLSL::CreateGeometryShader()
{
	// OpenGL ES 2.0 has no support for geometry shaders
	return nullptr;
}

PLRenderer::FragmentShader *ShaderLanguageGLSL::CreateFragmentShader()
{
	return new FragmentShaderGLSL(*m_pRenderer);
}

PLRenderer::Program *ShaderLanguageGLSL::CreateProgram()
{
	return new ProgramGLSL(*m_pRenderer);
}

PLRenderer::UniformBuffer *ShaderLanguageGLSL::CreateUniformBuffer()
{
	// OpenGL ES 2.0 has no support for uniform buffers
	return nullptr;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ShaderLanguageGLSL::ShaderLanguageGLSL(PLRenderer::Renderer &cRenderer) :
	m_pRenderer(&cRenderer)
{
}

/**
*  @brief
*    Destructor
*/
ShaderLanguageGLSL::~ShaderLanguageGLSL()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
