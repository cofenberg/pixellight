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
#include "PLRendererOpenGL/Context.h"
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/Extensions.h"
#include "PLRendererOpenGL/ProgramGLSL.h"
#include "PLRendererOpenGL/UniformBuffer.h"
#include "PLRendererOpenGL/VertexShaderGLSL.h"
#include "PLRendererOpenGL/GeometryShaderGLSL.h"
#include "PLRendererOpenGL/FragmentShaderGLSL.h"
#include "PLRendererOpenGL/ShaderLanguageGLSL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGL {


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
	// Is the OpenGL extension GL_ARB_shader_objects available?
	return static_cast<Renderer*>(m_pRenderer)->GetContext().GetExtensions().IsGL_ARB_shader_objects() ? new VertexShaderGLSL(*m_pRenderer) : nullptr;
}

PLRenderer::GeometryShader *ShaderLanguageGLSL::CreateGeometryShader()
{
	// Are the OpenGL extensions GL_ARB_shader_objects and GL_EXT_geometry_shader4 available?
	const Extensions &cExtensions = static_cast<Renderer*>(m_pRenderer)->GetContext().GetExtensions();
	return (cExtensions.IsGL_ARB_shader_objects() && cExtensions.IsGL_EXT_geometry_shader4()) ? new GeometryShaderGLSL(*m_pRenderer) : nullptr;
}

PLRenderer::FragmentShader *ShaderLanguageGLSL::CreateFragmentShader()
{
	// Is the OpenGL extension GL_ARB_shader_objects available?
	return static_cast<Renderer*>(m_pRenderer)->GetContext().GetExtensions().IsGL_ARB_shader_objects() ? new FragmentShaderGLSL(*m_pRenderer) : nullptr;
}

PLRenderer::Program *ShaderLanguageGLSL::CreateProgram()
{
	// Is the OpenGL extension GL_ARB_shader_objects available?
	return static_cast<Renderer*>(m_pRenderer)->GetContext().GetExtensions().IsGL_ARB_shader_objects() ? new ProgramGLSL(*m_pRenderer) : nullptr;
}

PLRenderer::UniformBuffer *ShaderLanguageGLSL::CreateUniformBuffer()
{
	// Are the OpenGL extensions GL_ARB_uniform_buffer_object and GL_EXT_transform_feedback available?
	Renderer *pRenderer = static_cast<Renderer*>(m_pRenderer);
	const Extensions &cExtensions = pRenderer->GetContext().GetExtensions();
	return (cExtensions.IsGL_ARB_uniform_buffer_object() && cExtensions.IsGL_EXT_transform_feedback()) ? new UniformBuffer(*m_pRenderer, GLSL) : nullptr;
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
} // PLRendererOpenGL
