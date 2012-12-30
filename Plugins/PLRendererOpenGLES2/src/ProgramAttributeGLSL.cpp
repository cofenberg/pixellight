/*********************************************************\
 *  File: ProgramAttributeGLSL.cpp                       *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRendererOpenGLES2/Context.h"
#include "PLRendererOpenGLES2/VertexBuffer.h"
#include "PLRendererOpenGLES2/ProgramAttributeGLSL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ProgramAttributeGLSL::ProgramAttributeGLSL(int nOpenGLESAttributeLocation) :
	m_nOpenGLESAttributeLocation(nOpenGLESAttributeLocation)
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
			// Bind and update the vertex buffer if required
			static_cast<PLRendererOpenGLES2::VertexBuffer*>(pVertexBuffer)->BindAndUpdate();

			// Create the connection between "vertex program attribute" and "vertex buffer attribute"
			glVertexAttribPointer(m_nOpenGLESAttributeLocation, pVertexAttribute->nComponentsAPI, pVertexAttribute->nTypeAPI, GL_FALSE, pVertexBuffer->GetVertexSize(), reinterpret_cast<const void*>(pVertexAttribute->nOffset));

			// Enable vertex attribute array (OpenGL program independent, so we don't need to call glUseProgram first!)
			glEnableVertexAttribArray(m_nOpenGLESAttributeLocation);
		}
	} else {
		// Disable vertex attribute array (OpenGL program independent, so we don't need to call glUseProgram first!)
		glDisableVertexAttribArray(m_nOpenGLESAttributeLocation);
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
			// Bind and update the vertex buffer if required
			static_cast<PLRendererOpenGLES2::VertexBuffer*>(pVertexBuffer)->BindAndUpdate();

			// Create the connection between "vertex program attribute" and "vertex buffer attribute"
			glVertexAttribPointer(m_nOpenGLESAttributeLocation, pVertexAttribute->nComponentsAPI, pVertexAttribute->nTypeAPI, GL_FALSE, pVertexBuffer->GetVertexSize(), reinterpret_cast<const void*>(pVertexAttribute->nOffset));

			// Enable vertex attribute array (OpenGL program independent, so we don't need to call glUseProgram first!)
			glEnableVertexAttribArray(m_nOpenGLESAttributeLocation);
		}
	} else {
		// Disable vertex attribute array (OpenGL program independent, so we don't need to call glUseProgram first!)
		glDisableVertexAttribArray(m_nOpenGLESAttributeLocation);
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
