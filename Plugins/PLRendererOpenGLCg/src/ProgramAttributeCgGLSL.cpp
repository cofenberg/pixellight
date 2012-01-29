/*********************************************************\
 *  File: ProgramAttributeCgGLSL.cpp                     *
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
#include <PLRendererOpenGL/VertexBuffer.h>
#include "PLRendererOpenGLCg/ProgramAttributeCgGLSL.h"
#include "../../../../External/Recommended/OpenGL/gl.h"
#ifdef LINUX
	#include "../../../../External/Recommended/OpenGL/glx.h"	// For "glXGetProcAddressARB"
#endif
#include "../../../../External/Recommended/OpenGL/glext.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGLCg {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ProgramAttributeCgGLSL::ProgramAttributeCgGLSL(CGparameter pCgParameter) : ProgramAttributeCg(pCgParameter),
	m_nOpenGLAttributeLocation(cgGetParameterOrdinalNumber(pCgParameter))
{
}

/**
*  @brief
*    Destructor
*/
ProgramAttributeCgGLSL::~ProgramAttributeCgGLSL()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::ProgramAttribute functions ]
//[-------------------------------------------------------]
bool ProgramAttributeCgGLSL::Set(PLRenderer::VertexBuffer *pVertexBuffer, uint32 nIndex)
{
	// We're going to need "glEnableVertexAttribArrayARB", "glDisableVertexAttribArrayARB" and "glVertexAttribPointerARB" from "GL_ARB_vertex_program"
	#ifdef WIN32
		static PFNGLENABLEVERTEXATTRIBARRAYARBPROC  glEnableVertexAttribArrayARB  = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYARBPROC> (wglGetProcAddress("glEnableVertexAttribArrayARB"));
		static PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB = reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYARBPROC>(wglGetProcAddress("glDisableVertexAttribArrayARB"));
		static PFNGLVERTEXATTRIBPOINTERARBPROC      glVertexAttribPointerARB      = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERARBPROC>     (wglGetProcAddress("glVertexAttribPointerARB"));
	#elif LINUX
		static PFNGLENABLEVERTEXATTRIBARRAYARBPROC  glEnableVertexAttribArrayARB  = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYARBPROC> (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glEnableVertexAttribArrayARB")));
		static PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB = reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYARBPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glDisableVertexAttribArrayARB")));
		static PFNGLVERTEXATTRIBPOINTERARBPROC      glVertexAttribPointerARB      = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERARBPROC>     (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glVertexAttribPointerARB")));
	#endif
	if (glEnableVertexAttribArrayARB && glDisableVertexAttribArrayARB && glVertexAttribPointerARB) {
		// Enable or disable the vertex attribute array?
		if (pVertexBuffer) {
			// Get the vertex buffer attribute
			const PLRenderer::VertexBuffer::Attribute *pVertexAttribute = pVertexBuffer->GetVertexAttribute(nIndex);
			if (pVertexAttribute) {
				// Bind and update the vertex buffer if required
				static_cast<PLRendererOpenGL::VertexBuffer*>(pVertexBuffer)->BindAndUpdate();

				// Create the connection between "vertex program attribute" and "vertex buffer attribute"
				glVertexAttribPointerARB(m_nOpenGLAttributeLocation, pVertexAttribute->nComponentsAPI, pVertexAttribute->nTypeAPI, GL_FALSE, pVertexBuffer->GetVertexSize(), reinterpret_cast<const void*>(pVertexAttribute->nOffset));

				// Enable vertex attribute array (OpenGL program independent, so we don't need to call glUseProgram first!)
				glEnableVertexAttribArrayARB(m_nOpenGLAttributeLocation);
			} else {
				// Disable vertex attribute array (OpenGL program independent, so we don't need to call glUseProgram first!)
				glDisableVertexAttribArrayARB(m_nOpenGLAttributeLocation);
			}
		} else {
			// Disable vertex attribute array (OpenGL program independent, so we don't need to call glUseProgram first!)
			glDisableVertexAttribArrayARB(m_nOpenGLAttributeLocation);
		}
	}

	// Done
	return true;
}

bool ProgramAttributeCgGLSL::Set(PLRenderer::VertexBuffer *pVertexBuffer, PLRenderer::VertexBuffer::ESemantic nSemantic, uint32 nChannel)
{
	// We're going to need "glEnableVertexAttribArrayARB", "glDisableVertexAttribArrayARB" and "glVertexAttribPointerARB" from "GL_ARB_vertex_program"
	#ifdef WIN32
		static PFNGLENABLEVERTEXATTRIBARRAYARBPROC  glEnableVertexAttribArrayARB  = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYARBPROC> (wglGetProcAddress("glEnableVertexAttribArrayARB"));
		static PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB = reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYARBPROC>(wglGetProcAddress("glDisableVertexAttribArrayARB"));
		static PFNGLVERTEXATTRIBPOINTERARBPROC      glVertexAttribPointerARB      = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERARBPROC>     (wglGetProcAddress("glVertexAttribPointerARB"));
	#elif LINUX
		static PFNGLENABLEVERTEXATTRIBARRAYARBPROC  glEnableVertexAttribArrayARB  = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYARBPROC> (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glEnableVertexAttribArrayARB")));
		static PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB = reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYARBPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glDisableVertexAttribArrayARB")));
		static PFNGLVERTEXATTRIBPOINTERARBPROC      glVertexAttribPointerARB      = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERARBPROC>     (glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glVertexAttribPointerARB")));
	#endif
	if (glEnableVertexAttribArrayARB && glDisableVertexAttribArrayARB && glVertexAttribPointerARB) {
		// Enable or disable the vertex attribute array?
		if (pVertexBuffer) {
			// Get the vertex buffer attribute
			const PLRenderer::VertexBuffer::Attribute *pVertexAttribute = pVertexBuffer->GetVertexAttribute(nSemantic, nChannel);
			if (pVertexAttribute) {
				// Bind and update the vertex buffer if required
				static_cast<PLRendererOpenGL::VertexBuffer*>(pVertexBuffer)->BindAndUpdate();

				// Create the connection between "vertex program attribute" and "vertex buffer attribute"
				glVertexAttribPointerARB(m_nOpenGLAttributeLocation, pVertexAttribute->nComponentsAPI, pVertexAttribute->nTypeAPI, GL_FALSE, pVertexBuffer->GetVertexSize(), reinterpret_cast<const void*>(pVertexAttribute->nOffset));

				// Enable vertex attribute array (OpenGL program independent, so we don't need to call glUseProgram first!)
				glEnableVertexAttribArrayARB(m_nOpenGLAttributeLocation);
			} else {
				// Disable vertex attribute array (OpenGL program independent, so we don't need to call glUseProgram first!)
				glDisableVertexAttribArrayARB(m_nOpenGLAttributeLocation);
			}
		} else {
			// Disable vertex attribute array (OpenGL program independent, so we don't need to call glUseProgram first!)
			glDisableVertexAttribArrayARB(m_nOpenGLAttributeLocation);
		}
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLCg
