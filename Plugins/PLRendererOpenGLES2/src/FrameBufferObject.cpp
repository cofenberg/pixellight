/*********************************************************\
 *  File: FrameBufferObject.cpp                          *
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
#include <PLCore/Log/Log.h>
#include "PLRendererOpenGLES2/Renderer.h"
#include "PLRendererOpenGLES2/TextureBuffer2D.h"
#include "PLRendererOpenGLES2/TextureBuffer3D.h"
#include "PLRendererOpenGLES2/TextureBufferCube.h"
#include "PLRendererOpenGLES2/FrameBufferObject.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FrameBufferObject::FrameBufferObject() :
	m_nFrameBufferIndex(0),
	m_nColorBufferIndex(0),
	m_nDepthBufferIndex(0),
	m_nStencilBufferIndex(0),
	m_nDepthBufferAttachment(GL_DEPTH_ATTACHMENT)
{
}

/**
*  @brief
*    Destructor
*/
FrameBufferObject::~FrameBufferObject()
{
	// Destroy buffers
	if (m_nColorBufferIndex)
		glDeleteRenderbuffers(1, &m_nColorBufferIndex);
	if (m_nDepthBufferIndex)
		glDeleteRenderbuffers(1, &m_nDepthBufferIndex);
	if (m_nStencilBufferIndex)
		glDeleteRenderbuffers(1, &m_nStencilBufferIndex);
	if (m_nFrameBufferIndex)
		glDeleteFramebuffers(1, &m_nFrameBufferIndex);
}

/**
*  @brief
*    Initializes the frame buffer object
*/
bool FrameBufferObject::Initialize(Renderer &cRenderer, const Vector2i &vSize, uint32 nFormat, PLRenderer::TextureBuffer::EPixelFormat nTextureFormat)
{
	// Check parameters
	if (vSize.x != 0 && vSize.y != 0) {
		// Save size
		m_vSize = vSize;

		// Get current bound FBO
		GLint nFrameBufferT;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &nFrameBufferT);

		// Create color buffer?
		if (!PLRenderer::TextureBuffer::IsDepthFormat(nTextureFormat)) {
			// Get API pixel format
			const uint32 *pAPIPixelFormat = cRenderer.GetAPIPixelFormat(nTextureFormat);

			// Create color buffer
			glGenRenderbuffers(1, &m_nColorBufferIndex);
			glBindRenderbuffer(GL_RENDERBUFFER, m_nColorBufferIndex);
			glRenderbufferStorage(GL_RENDERBUFFER, *pAPIPixelFormat, m_vSize.x, m_vSize.y);
		}

		// Create depth&stencil buffer
		GLuint nDepth = 0;
		bool bDepthStencil = false;
		// [TODO] Check me
		/*
		if ((nFormat & Depth24) && (nFormat & Stencil) && cRenderer.IsGL_EXT_packed_depth_stencil()) {
			nDepth        = GL_DEPTH24_STENCIL8;
			bDepthStencil = true;
		} else {
		*/
//			if (nFormat & Depth16)
				nDepth = GL_DEPTH_COMPONENT16;
			// [TODO] Check me
			/*
			else if (nFormat & Depth24)
				nDepth = GL_DEPTH_COMPONENT24;
			else if (nFormat & Depth32)
				nDepth = GL_DEPTH_COMPONENT32;
			*/
	//	}
		if (nDepth) {
			glGenRenderbuffers(1, &m_nDepthBufferIndex);
			glBindRenderbuffer(GL_RENDERBUFFER, m_nDepthBufferIndex);
			glRenderbufferStorage(GL_RENDERBUFFER, nDepth, m_vSize.x, m_vSize.y);
		}

		// Create stencil buffer
		if (!bDepthStencil && (nFormat & Stencil)) {
			// [TODO] Stencil buffer support currently not working?! (but at least GL_EXT_packed_depth_stencil works)
//				glGenRenderbuffersEXT(1, &m_nStencilBufferIndex);
//				glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_nStencilBufferIndex);
//				glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_STENCIL_INDEX8_EXT, m_vSize.x, m_vSize.y);
		}

		// Create final FBO we will attach textures to
		glGenFramebuffers(1, &m_nFrameBufferIndex);

		// Create FBO used for rendering
		glBindFramebuffer(GL_FRAMEBUFFER, m_nFrameBufferIndex);

		// Bind frame buffer
		if (m_nColorBufferIndex)
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_nColorBufferIndex);
		if (m_nDepthBufferIndex) {
			// Get depth buffer attachment
			// [TODO] Check me
			m_nDepthBufferAttachment = GL_DEPTH_ATTACHMENT;
//			m_nDepthBufferAttachment = ((nFormat & Stencil) && !m_nStencilBufferIndex) ? GL_DEPTH_STENCIL_ATTACHMENT : GL_DEPTH_ATTACHMENT;

			// Attach depth buffer
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, m_nDepthBufferAttachment, GL_RENDERBUFFER, m_nDepthBufferIndex);
		}
		if (m_nStencilBufferIndex)
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_nStencilBufferIndex);

		// Check frame buffer
		const bool bResult = CheckFrameBufferStatus();

		// Reset current bound FBO
		glBindFramebuffer(GL_FRAMEBUFFER, nFrameBufferT);

		// Done
		// [TODO] Check me
		return true;
//		return bResult;
	} else {
		PL_LOG(Error, "Width and height of FBO must be none zero!")
	}

	// Error!
	return false;
}

/**
*  @brief
*    Switches the texture buffer target
*/
void FrameBufferObject::SwitchTarget(PLRenderer::TextureBuffer &cTextureBuffer, uint32 nAttachIndex, uint8 nFace)
{
	// Valid frame buffer object?
	if (m_nFrameBufferIndex) {
		// Get target format and OpenGL texture ID
		int nTarget = -1;
		GLuint nOpenGLID = 0;
		switch (cTextureBuffer.GetType()) {
			case PLRenderer::Resource::TypeTextureBuffer2D:
				nTarget = GL_TEXTURE_2D;
				nOpenGLID = static_cast<TextureBuffer2D&>(cTextureBuffer).GetOpenGLESTexture();
				break;

			// [TODO] Check me
			/*
			case PLRenderer::Resource::TypeTextureBuffer3D:
				nTarget = GL_TEXTURE_3D;
				nOpenGLID = static_cast<TextureBuffer3D&>(cTextureBuffer).GetOpenGLESTexture();
				break;
				*/

			case PLRenderer::Resource::TypeTextureBufferCube:
				nTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_X+nFace;
				nOpenGLID = static_cast<TextureBufferCube&>(cTextureBuffer).GetOpenGLESTexture();
				break;
		}
		if (nTarget >= 0 && nOpenGLID) {
			// Check/clamp attach index
			if (nAttachIndex > 15)
				nAttachIndex = 15;

			// Bind
			glBindFramebuffer(GL_FRAMEBUFFER, m_nFrameBufferIndex);
			PLRenderer::TextureBuffer::EPixelFormat nFormat = cTextureBuffer.GetFormat();
			if (nFormat == PLRenderer::TextureBuffer::D16 || nFormat == PLRenderer::TextureBuffer::D24 || nFormat == PLRenderer::TextureBuffer::D32) {
				glFramebufferTexture2D(GL_FRAMEBUFFER, m_nDepthBufferAttachment, nTarget, nOpenGLID, 0);
			} else {
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+nAttachIndex, nTarget, nOpenGLID, 0);
			}
		}
	}
}

/**
*  @brief
*    Binds the frame buffer
*/
void FrameBufferObject::Bind()
{
	if (m_nFrameBufferIndex)
		glBindFramebuffer(GL_FRAMEBUFFER, m_nFrameBufferIndex);
}

/**
*  @brief
*    Unbinds the frame buffer
*/
void FrameBufferObject::Unbind()
{
	// Unbind FBO
	if (m_nFrameBufferIndex)
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/**
*  @brief
*    Returns the size of the frame buffer
*/
const Vector2i &FrameBufferObject::GetSize() const
{
	return m_vSize;
}

/**
*  @brief
*    Takes over the control of the depth buffer of the given FBO
*/
void FrameBufferObject::TakeDepthBufferFromFBO(FrameBufferObject &cFBO)
{
	// Has the other FBO a depth buffer?
	if (cFBO.m_nDepthBufferIndex) {
		// Get current bound FBO
		GLint nFrameBufferT;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &nFrameBufferT);

		// If we have a depth buffer, we destroy it because the depth buffer of the other FBO is much better *g*
		if (m_nDepthBufferIndex) {
			glBindFramebuffer(GL_FRAMEBUFFER, m_nFrameBufferIndex);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
			glDeleteRenderbuffers(1, &m_nDepthBufferIndex);
		}

		// Take away the ownership of the depth buffer
		m_nDepthBufferIndex = cFBO.m_nDepthBufferIndex;
		glBindFramebuffer(GL_FRAMEBUFFER, cFBO.m_nFrameBufferIndex);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
		cFBO.m_nDepthBufferIndex = 0;
		glBindFramebuffer(GL_FRAMEBUFFER, m_nFrameBufferIndex);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_nDepthBufferIndex);

		// Reset current bound FBO
		glBindFramebuffer(GL_FRAMEBUFFER, nFrameBufferT);
	}
}

/**
*  @brief
*    Checks the frame buffer
*/
bool FrameBufferObject::CheckFrameBufferStatus() const
{
	bool bResult = true; // No error by default

	// Backup current draw and read buffer, then set them to none - else
	// 'glCheckFramebufferStatus' will always return an error :(
	// [TODO] Check me
	/*
	GLint nDrawBufferT;
	glGetIntegerv(GL_DRAW_BUFFER, &nDrawBufferT);
	glDrawBuffer(GL_NONE);
	GLint nReadBufferT;
	glGetIntegerv(GL_READ_BUFFER, &nReadBufferT);
	glReadBuffer(GL_NONE);
	*/

	// Check FBO status
	GLenum nStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	switch (nStatus) {
		case GL_FRAMEBUFFER_COMPLETE:
			PL_LOG(Debug, String::Format("Successfully created the frame buffer object (%dx%d)", m_vSize.x, m_vSize.y))
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			PL_LOG(Error, "Incomplete attachment frame buffer object")
			bResult = false;
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			PL_LOG(Error, "Incomplete missing attachment frame buffer object")
			bResult = false;
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
			PL_LOG(Error, "Incomplete dimensions frame buffer object")
			bResult = false;
			break;

		// [TODO] Check me
		/*
		case GL_FRAMEBUFFER_INCOMPLETE_FORMATS:
			PL_LOG(Error, "Incomplete formats frame buffer object")
			bResult = false;
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			PL_LOG(Error, "Incomplete draw buffer frame buffer object")
			bResult = false;
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			PL_LOG(Error, "Incomplete read buffer frame buffer object")
			bResult = false;
			break;
		*/

		case GL_FRAMEBUFFER_UNSUPPORTED:
			PL_LOG(Error, "Failed to create the frame buffer object, please verify your format")
			bResult = false;
			break;
	}

	// Restore current draw and read buffer
	// [TODO] Check me
	/*
	glDrawBuffer(nDrawBufferT);
	glReadBuffer(nReadBufferT);
	*/

	// Done
	return bResult;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
