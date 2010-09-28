/*********************************************************\
 *  File: ProgramAttributeCg.cpp                         *
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
#include <PLRendererOpenGL/VertexBuffer.h>
#include "PLRendererOpenGLCg/ProgramAttributeCg.h"


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
ProgramAttributeCg::ProgramAttributeCg(CGparameter pCgParameter) :
	m_pCgParameter(pCgParameter)
{
}

/**
*  @brief
*    Destructor
*/
ProgramAttributeCg::~ProgramAttributeCg()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::ProgramAttribute functions ]
//[-------------------------------------------------------]
bool ProgramAttributeCg::Set(PLRenderer::VertexBuffer *pVertexBuffer, uint32 nIndex)
{
	// Enable or disable the vertex attribute array?
	if (pVertexBuffer) {
		// Get the vertex buffer attribute
		const PLRenderer::VertexBuffer::Attribute *pVertexAttribute = pVertexBuffer->GetVertexAttribute(nIndex);
		if (pVertexAttribute) {
			// Bind and update the vertex buffer if required
			((PLRendererOpenGL::VertexBuffer*)pVertexBuffer)->BindAndUpdate();

			// Create the connection between "vertex program attribute" and "vertex buffer attribute"
			cgGLSetParameterPointer(m_pCgParameter, pVertexAttribute->nComponentsAPI, pVertexAttribute->nTypeAPI, pVertexBuffer->GetVertexSize(), (const void*)pVertexAttribute->nOffset);

			// Enable vertex attribute array
			cgGLEnableClientState(m_pCgParameter);
		} else {
			// Disable vertex attribute array
			cgGLDisableClientState(m_pCgParameter);
		}
	} else {
		// Disable vertex attribute array
		cgGLDisableClientState(m_pCgParameter);
	}

	// Done
	return true;
}

bool ProgramAttributeCg::Set(PLRenderer::VertexBuffer *pVertexBuffer, PLRenderer::VertexBuffer::ESemantic nSemantic, uint32 nChannel)
{
	// Enable or disable the vertex attribute array?
	if (pVertexBuffer) {
		// Get the vertex buffer attribute
		const PLRenderer::VertexBuffer::Attribute *pVertexAttribute = pVertexBuffer->GetVertexAttribute(nSemantic, nChannel);
		if (pVertexAttribute) {
			// Bind and update the vertex buffer if required
			((PLRendererOpenGL::VertexBuffer*)pVertexBuffer)->BindAndUpdate();

			// Create the connection between "vertex program attribute" and "vertex buffer attribute"
			cgGLSetParameterPointer(m_pCgParameter, pVertexAttribute->nComponentsAPI, pVertexAttribute->nTypeAPI, pVertexBuffer->GetVertexSize(), (const void*)pVertexAttribute->nOffset);

			// Enable vertex attribute array
			cgGLEnableClientState(m_pCgParameter);
		} else {
			// Disable vertex attribute array
			cgGLDisableClientState(m_pCgParameter);
		}
	} else {
		// Disable vertex attribute array
		cgGLDisableClientState(m_pCgParameter);
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLCg
