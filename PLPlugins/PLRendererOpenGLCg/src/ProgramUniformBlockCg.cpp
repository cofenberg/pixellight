/*********************************************************\
 *  File: ProgramUniformBlockCg.cpp                      *
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
#include <PLGeneral/String/String.h>
#include "PLRendererOpenGLCg/UniformBufferCg.h"
#include "PLRendererOpenGLCg/ProgramUniformBlockCg.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRendererOpenGLCg {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ProgramUniformBlockCg::ProgramUniformBlockCg(CGparameter pCgParameter, const String &sShaderLanguage) :
	m_sShaderLanguage(sShaderLanguage),
	m_pCgParameter(pCgParameter)
{
}

/**
*  @brief
*    Destructor
*/
ProgramUniformBlockCg::~ProgramUniformBlockCg()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::ProgramUniformBlock functions ]
//[-------------------------------------------------------]
bool ProgramUniformBlockCg::SetUniformBuffer(PLRenderer::UniformBuffer *pUniformBuffer, uint32 nBindingPoint)
{
	// Cg hides the binding point internally, so the given binding point is ignored in here...

	// Is there an uniform buffer given?
	if (pUniformBuffer) {
		// The given uniform buffer must have at least the same number of bytes as this uniform block and the shader language must match!
		if (cgGetParameterResourceSize(m_pCgParameter) <= static_cast<long>(pUniformBuffer->GetSize()) && m_sShaderLanguage == pUniformBuffer->GetShaderLanguage()) {
			cgSetProgramBuffer(cgGetParameterProgram(m_pCgParameter), cgGetParameterBufferIndex(m_pCgParameter), static_cast<UniformBufferCg*>(pUniformBuffer)->GetCgBuffer());
		} else {
			// Error!
			return false;
		}
	} else {
		cgSetProgramBuffer(cgGetParameterProgram(m_pCgParameter), cgGetParameterBufferIndex(m_pCgParameter), nullptr);
	}

	// Done
	return true;
}

uint32 ProgramUniformBlockCg::GetIndex() const
{
	// Cg returns -1 if the parameter does not belong to a buffer or an error occurs... but in here, this shouldn't happen...
	const int nIndex = cgGetParameterBufferIndex(m_pCgParameter);
	return (nIndex > -1) ? nIndex : 0;
}

uint32 ProgramUniformBlockCg::GetSize() const
{
	return cgGetParameterResourceSize(m_pCgParameter);
}

uint32 ProgramUniformBlockCg::GetUniformOffset(const String &sUniformName) const
{
	CGparameter pCgParameter = cgGetNamedStructParameter(m_pCgParameter, sUniformName);
	return pCgParameter ? cgGetParameterBufferOffset(pCgParameter) : 0;
}

uint32 ProgramUniformBlockCg::GetUniformSize(const String &sUniformName) const
{
	CGparameter pCgParameter = cgGetNamedStructParameter(m_pCgParameter, sUniformName);
	return pCgParameter ? cgGetParameterResourceSize(pCgParameter) : 0;
}

uint32 ProgramUniformBlockCg::GetUniformNumOfArrayElements(const String &sUniformName) const
{
	CGparameter pCgParameter = cgGetNamedStructParameter(m_pCgParameter, sUniformName);
	return (pCgParameter && cgGetParameterClass(pCgParameter) == CG_PARAMETERCLASS_ARRAY) ? cgGetArraySize(pCgParameter, 0) : 1;	// We currently only support one dimension...
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLCg
