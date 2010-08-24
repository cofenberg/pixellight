/*********************************************************\
 *  File: ProgramAttributeGLSL.cpp                       *
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
#include "PLRendererOpenGL/PLRendererOpenGL.h"
#include "PLRendererOpenGL/VertexBuffer.h"
#include "PLRendererOpenGL/Misc/ExtensionDefinitions.h"
#include "PLRendererOpenGL/ProgramAttributeGLSL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ProgramAttributeGLSL::ProgramAttributeGLSL(int nOpenGLAttributeLocation) :
	m_nOpenGLAttributeLocation(nOpenGLAttributeLocation)
{
}

/**
*  @brief
*    Destructor
*/
ProgramAttributeGLSL::~ProgramAttributeGLSL()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::ProgramAttribute functions ]
//[-------------------------------------------------------]
bool ProgramAttributeGLSL::Set(PLRenderer::VertexBuffer *pVertexBuffer, uint32 nIndex)
{
	// Enable or disable the vertex attribute array?
	if (pVertexBuffer) {
		// Get the vertex buffer attribute
		const PLRenderer::VertexBuffer::Attribute *pVertexAttribute = pVertexBuffer->GetVertexAttribute(nIndex);
		if (pVertexAttribute) {
			// Make the given vertex buffer to the current one
			((PLRendererOpenGL::VertexBuffer*)pVertexBuffer)->MakeCurrent(0);

			// Create the connection between "vertex program attribute" and "vertex buffer attribute"
			glVertexAttribPointerARB(m_nOpenGLAttributeLocation, pVertexAttribute->nComponentsAPI, pVertexAttribute->nTypeAPI, GL_FALSE, pVertexBuffer->GetVertexSize(), (const void*)pVertexAttribute->nOffset);

			// Enable vertex attribute array (OpenGL program independent, so we don't need to call glUseProgram first!)
			glEnableVertexAttribArrayARB(m_nOpenGLAttributeLocation);
		}
	} else {
		// Disable vertex attribute array (OpenGL program independent, so we don't need to call glUseProgram first!)
		glDisableVertexAttribArrayARB(m_nOpenGLAttributeLocation);
	}

	// Done
	return true;
}

bool ProgramAttributeGLSL::Set(PLRenderer::VertexBuffer *pVertexBuffer, PLRenderer::VertexBuffer::ESemantic nSemantic, uint32 nChannel)
{
	// Enable or disable the vertex attribute array?
	if (pVertexBuffer) {
		// Get the vertex buffer attribute
		const PLRenderer::VertexBuffer::Attribute *pVertexAttribute = pVertexBuffer->GetVertexAttribute(nSemantic, nChannel);
		if (pVertexAttribute) {
			// Make the given vertex buffer to the current one
			((PLRendererOpenGL::VertexBuffer*)pVertexBuffer)->MakeCurrent(0);

			// Create the connection between "vertex program attribute" and "vertex buffer attribute"
			glVertexAttribPointerARB(m_nOpenGLAttributeLocation, pVertexAttribute->nComponentsAPI, pVertexAttribute->nTypeAPI, GL_FALSE, pVertexBuffer->GetVertexSize(), (const void*)pVertexAttribute->nOffset);

			// Enable vertex attribute array (OpenGL program independent, so we don't need to call glUseProgram first!)
			glEnableVertexAttribArrayARB(m_nOpenGLAttributeLocation);
		}
	} else {
		// Disable vertex attribute array (OpenGL program independent, so we don't need to call glUseProgram first!)
		glDisableVertexAttribArrayARB(m_nOpenGLAttributeLocation);
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
