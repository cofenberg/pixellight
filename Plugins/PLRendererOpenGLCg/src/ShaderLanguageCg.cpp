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
#include "PLRendererOpenGLCg/ProgramCg.h"
#include "PLRendererOpenGLCg/VertexShaderCg.h"
#include "PLRendererOpenGLCg/UniformBufferCg.h"
#include "PLRendererOpenGLCg/GeometryShaderCg.h"
#include "PLRendererOpenGLCg/FragmentShaderCg.h"
#include "PLRendererOpenGLCg/TessellationControlShaderCg.h"
#include "PLRendererOpenGLCg/TessellationEvaluationShaderCg.h"
#include "PLRendererOpenGLCg/ShaderLanguageCg.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGLCg {


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

PLRenderer::TessellationControlShader *ShaderLanguageCg::CreateTessellationControlShader()
{
	return new TessellationControlShaderCg(*m_pRenderer);
}

PLRenderer::TessellationEvaluationShader *ShaderLanguageCg::CreateTessellationEvaluationShader()
{
	return new TessellationEvaluationShaderCg(*m_pRenderer);
}

PLRenderer::GeometryShader *ShaderLanguageCg::CreateGeometryShader()
{
	return new GeometryShaderCg(*m_pRenderer);
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
	return new UniformBufferCg(*m_pRenderer, Cg);
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
} // PLRendererOpenGLCg
