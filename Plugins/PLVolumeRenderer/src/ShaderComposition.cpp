/*********************************************************\
 *  File: ShaderComposition.cpp                          *
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
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexShader.h>
#include <PLRenderer/Renderer/ProgramWrapper.h>
#include <PLRenderer/Renderer/FragmentShader.h>
#include <PLRenderer/Renderer/TextureBuffer3D.h>
#include <PLRenderer/Renderer/TextureBuffer2DArray.h>
#include <PLScene/Visibility/SQCull.h>
#include <PLScene/Visibility/VisNode.h>
#include <PLScene/Visibility/VisContainer.h>
#include <PLVolume/Volume.h>
#include <PLVolume/Scene/SNVolume.h>
#include "PLVolumeRenderer/SRPVolume.h"
#include "PLVolumeRenderer/ShaderFunction.h"
#include "PLVolumeRenderer/ShaderComposition.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLScene;
namespace PLVolumeRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Check for equality
*/
bool ShaderComposition::operator ==(const ShaderComposition &cOther) const
{
	return (m_cShaderCompositionID == cOther.m_cShaderCompositionID);
}

/**
*  @brief
*    Returns the shader composition ID
*/
const ShaderCompositionID &ShaderComposition::GetShaderCompositionID() const
{
	return m_cShaderCompositionID;
}

/**
*  @brief
*    Returns direct access to shader function instances this shader composition consists of
*/
const ShaderComposition::SShaderFunction &ShaderComposition::GetShaderFunctions() const
{
	return m_sShaderFunction;
}

/**
*  @brief
*    Returns a list of shader function instances this shader composition consists of
*/
const Array<ShaderFunction*> &ShaderComposition::GetShaderFunctionsList() const
{
	return m_lstShaderFunction;
}

/**
*  @brief
*    Returns the GPU program of this shader composition
*/
Program &ShaderComposition::GetProgram() const
{
	return *m_pProgram;
}

// [TODO] Just a test
void ShaderComposition::SetProgram(Renderer &cRenderer, const SQCull &cCullQuery, const VisNode &cVisNode, SRPVolume &cSRPVolume)
{
	// Make our GPU program to the current one
	if (cRenderer.SetProgram(m_pProgram)) {
		// Let the shader functions do their job (e.g. setting program uniforms)
		for (uint32 i=0; i<m_lstShaderFunction.GetNumOfElements(); i++)
			m_lstShaderFunction[i]->SetProgram(*m_pProgram, cCullQuery, cVisNode, cSRPVolume);
	}
}

/**
*  @brief
*    Returns a human readable representation of this shader composition
*/
String ShaderComposition::ToString() const
{
	// Get a human readable representation of this shader composition ID
	String sString = "// " + m_cShaderCompositionID.ToString() + "\n\n";

	// Append the compiled program
	if (m_pProgram) {
		const String sCompiledProgram = m_pProgram->GetCompiledProgram();
		sString += sCompiledProgram.GetLength() ? sCompiledProgram : "Failed to get the compiled program";
	} else {
		sString += "There's no compiled GPU program";
	}

	// Done
	return sString;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ShaderComposition::ShaderComposition(const ShaderCompositionID &cShaderCompositionID, Program &cProgram, const Array<ShaderFunction*> &lstShaderFunction) :
	m_cShaderCompositionID(cShaderCompositionID),
	m_pProgram(&cProgram),
	m_lstShaderFunction(lstShaderFunction)
{
}

/**
*  @brief
*    Destructor
*/
ShaderComposition::~ShaderComposition()
{
	// Destroy the GPU program of this shader composition
	if (m_pProgram) {
		// Get the used vertex shader and fragment shader instance
		VertexShader   *pVertexShader   = m_pProgram->GetVertexShader();
		FragmentShader *pFragmentShader = m_pProgram->GetFragmentShader();

		// Destroy the GPU program of this shader composition
		delete m_pProgram;
		m_pProgram = nullptr;

		// Destroy the used vertex shader instance
		if (pVertexShader)
			delete pVertexShader;

		// Destroy the used fragment shader instance
		if (pFragmentShader)
			delete pFragmentShader;
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
ShaderComposition::ShaderComposition(const ShaderComposition &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
ShaderComposition &ShaderComposition::operator =(const ShaderComposition &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer
