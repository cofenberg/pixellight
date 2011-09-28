/*********************************************************\
 *  File: ProgramCg.cpp                                  *
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
#include "PLRendererOpenGLES2/ShaderLanguageCg.h"
#include "PLRendererOpenGLES2/FragmentShaderCg.h"
#include "PLRendererOpenGLES2/VertexShaderCg.h"
#include "PLRendererOpenGLES2/ProgramCg.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
ProgramCg::~ProgramCg()
{
	// Nothing to do in here
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ProgramCg::ProgramCg(PLRenderer::Renderer &cRenderer) : ProgramGLSL(cRenderer)
{
	// Nothing to do in here
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Program functions          ]
//[-------------------------------------------------------]
String ProgramCg::GetShaderLanguage() const
{
	return ShaderLanguageCg::Cg;
}

bool ProgramCg::SetVertexShader(PLRenderer::VertexShader *pVertexShader)
{
	// Is the new vertex shader the same one as the current one?
	PLRenderer::VertexShader *pCurrentVertexShader = static_cast<PLRenderer::VertexShader*>(m_cVertexShaderHandler.GetResource());
	if (pCurrentVertexShader != pVertexShader) {
		// The shader language of the program and the vertex shader must match
		if (pVertexShader && pVertexShader->GetShaderLanguage() != ShaderLanguageCg::Cg)
			return false; // Error, shader language mismatch!

		// Detach the current vertex shader from the program
		if (pCurrentVertexShader)
			glDetachShader(m_nOpenGLESProgram, static_cast<VertexShaderCg*>(pCurrentVertexShader)->GetOpenGLESVertexShader());

		// Update the vertex shader resource handler
		m_cVertexShaderHandler.SetResource(pVertexShader);

		// Attach the new vertex shader to the program
		if (pVertexShader)
			glAttachShader(m_nOpenGLESProgram, static_cast<VertexShaderCg*>(pVertexShader)->GetOpenGLESVertexShader());

		// Denote that a program relink is required
		RelinkRequired();
	}

	// Done
	return true;
}

bool ProgramCg::SetFragmentShader(PLRenderer::FragmentShader *pFragmentShader)
{
	// Is the new fragment shader the same one as the current one?
	PLRenderer::FragmentShader *pCurrentFragmentShader = static_cast<PLRenderer::FragmentShader*>(m_cFragmentShaderHandler.GetResource());
	if (pCurrentFragmentShader != pFragmentShader) {
		// The shader language of the program and the fragment shader must match
		if (pFragmentShader && pFragmentShader->GetShaderLanguage() != ShaderLanguageCg::Cg)
			return false; // Error, shader language mismatch!

		// Detach the current fragment shader from the program
		if (pCurrentFragmentShader)
			glDetachShader(m_nOpenGLESProgram, static_cast<FragmentShaderCg*>(pCurrentFragmentShader)->GetOpenGLESFragmentShader());

		// Update the fragment shader resource handler
		m_cFragmentShaderHandler.SetResource(pFragmentShader);

		// Attach the new fragment shader to the program
		if (pFragmentShader)
			glAttachShader(m_nOpenGLESProgram, static_cast<FragmentShaderCg*>(pFragmentShader)->GetOpenGLESFragmentShader());

		// Denote that a program relink is required
		RelinkRequired();
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
