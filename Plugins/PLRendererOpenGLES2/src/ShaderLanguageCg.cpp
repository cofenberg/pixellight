/*********************************************************\
 *  File: ShaderLanguageCg.cpp                           *
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
#include "PLRendererOpenGLES2/ProgramCg.h"
#include "PLRendererOpenGLES2/VertexShaderCg.h"
#include "PLRendererOpenGLES2/FragmentShaderCg.h"
#include "PLRendererOpenGLES2/ShaderLanguageCg.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const String ShaderLanguageCg::Cg = "Cg";


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ShaderLanguageCg)


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::ShaderLanguage functions   ]
//[-------------------------------------------------------]
String ShaderLanguageCg::GetShaderLanguage() const
{
	return Cg;
}

PLRenderer::VertexShader *ShaderLanguageCg::CreateVertexShader()
{
	return new VertexShaderCg(*m_pRenderer);
}

PLRenderer::GeometryShader *ShaderLanguageCg::CreateGeometryShader()
{
	// OpenGL ES 2.0 has no support for geometry shaders
	return nullptr;
}

PLRenderer::FragmentShader *ShaderLanguageCg::CreateFragmentShader()
{
	return new FragmentShaderCg(*m_pRenderer);
}

PLRenderer::Program *ShaderLanguageCg::CreateProgram()
{
	return new ProgramCg(*m_pRenderer);
}

PLRenderer::UniformBuffer *ShaderLanguageCg::CreateUniformBuffer()
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
ShaderLanguageCg::ShaderLanguageCg(PLRenderer::Renderer &cRenderer) :
	m_pRenderer(&cRenderer)
{
}

/**
*  @brief
*    Destructor
*/
ShaderLanguageCg::~ShaderLanguageCg()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
