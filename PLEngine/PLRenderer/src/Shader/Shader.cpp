/*********************************************************\
 *  File: Shader.cpp                                     *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLGeneral/Log/Log.h>
#include "PLRenderer/RendererContext.h"
#include "PLRenderer/Renderer/ShaderProgram.h"
#include "PLRenderer/Renderer/ResourceHandler.h"
#include "PLRenderer/Shader/ShaderManager.h"
#include "PLRenderer/Shader/Shader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
Shader::~Shader()
{
	// First at all: Unload the shader
	Unload();

	// Delete shader program handler
	delete m_pShaderProgramHandler;
}

/**
*  @brief
*    Returns the shader manager this shader is in
*/
ShaderManager &Shader::GetShaderManager() const
{
	// There MUST always be a manager!
	return (ShaderManager&)*m_pManager;
}

/**
*  @brief
*    Binds the shader
*/
bool Shader::Bind() const
{
	// Get shader program
	ShaderProgram *pShaderProgram = (ShaderProgram*)m_pShaderProgramHandler->GetResource();
	if (pShaderProgram) {
		// Bind shader program
		if (pShaderProgram->GetType() == PLRenderer::Resource::TypeVertexShaderProgram)
			GetShaderManager().GetRendererContext().GetRenderer().SetVertexShaderProgram(pShaderProgram);
		else
			GetShaderManager().GetRendererContext().GetRenderer().SetFragmentShaderProgram(pShaderProgram);

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Unbinds the shader
*/
bool Shader::Unbind() const
{
	// Get renderer shader program
	ShaderProgram *pShaderProgram = (ShaderProgram*)m_pShaderProgramHandler->GetResource();
	if (pShaderProgram) {
		// Unbind shader program
		if (pShaderProgram->GetType() == PLRenderer::Resource::TypeVertexShaderProgram)
			GetShaderManager().GetRendererContext().GetRenderer().SetVertexShaderProgram();
		else
			GetShaderManager().GetRendererContext().GetRenderer().SetFragmentShaderProgram();

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Returns the shader program
*/
PLRenderer::ShaderProgram *Shader::GetShaderProgram() const
{
	return (PLRenderer::ShaderProgram*)m_pShaderProgramHandler->GetResource();
}

/**
*  @brief
*    Sets the shader program
*/
void Shader::SetShaderProgram(PLRenderer::ShaderProgram *pShaderProgram)
{
	if (m_pShaderProgramHandler->GetResource() != pShaderProgram) {
		DestroyShaderProgram();
		m_pShaderProgramHandler->SetResource(pShaderProgram);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Shader::Shader(ShaderManager &cManager, const String &sName) : PLCore::Resource<Shader>(sName, &cManager),
	m_pShaderProgramHandler(new PLRenderer::ResourceHandler())
{
}

/**
*  @brief
*    Destroys the used shader program
*/
void Shader::DestroyShaderProgram()
{
	// If this is the last handler using this shader program, kill the shader program
	PLRenderer::ShaderProgram *pShaderProgram = (PLRenderer::ShaderProgram*)m_pShaderProgramHandler->GetResource();
	if (pShaderProgram) {
		if (pShaderProgram->GetNumOfHandlers() <= 1)
			delete pShaderProgram;
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Loadable functions             ]
//[-------------------------------------------------------]
bool Shader::Unload()
{
	// Check shader program
	if (!m_pShaderProgramHandler->GetResource())
		return false; // Error!

	// Delete shader program
	PL_LOG(Debug, "Delete shader: " + GetName())
	DestroyShaderProgram();

	// Call base implementation
	return PLCore::Resource<Shader>::Unload();
}

String Shader::GetLoadableTypeName() const
{
	static const String sString = "Shader";
	return sString;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
