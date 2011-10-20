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
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/TextureBuffer1D.h"
#include "PLRendererOpenGL/TextureBuffer2D.h"
#include "PLRendererOpenGL/TextureBufferRectangle.h"
#include "PLRendererOpenGL/TextureBuffer3D.h"
#include "PLRendererOpenGL/TextureBufferCube.h"
#include "PLRendererOpenGL/FrameBufferObject.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FrameBufferObject::FrameBufferObject() :
	m_nFrameBufferIndex(0),
	m_nMultisampleFrameBufferIndex(0),
	m_nColorBufferIndex(0),
	m_nDepthBufferIndex(0),
	m_nStencilBufferIndex(0),
	m_nDepthBufferAttachment(GL_DEPTH_ATTACHMENT_EXT)
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
		glDeleteRenderbuffersEXT(1, &m_nColorBufferIndex);
	if (m_nDepthBufferIndex)
		glDeleteRenderbuffersEXT(1, &m_nDepthBufferIndex);
	if (m_nStencilBufferIndex)
		glDeleteRenderbuffersEXT(1, &m_nStencilBufferIndex);
	if (m_nMultisampleFrameBufferIndex)
		glDeleteFramebuffersEXT(1, &m_nMultisampleFrameBufferIndex);
	if (m_nFrameBufferIndex)
		glDeleteFramebuffersEXT(1, &m_nFrameBufferIndex);
}

/**
*  @brief
*    Initializes the frame buffer object
*/
bool FrameBufferObject::Initialize(Renderer &cRenderer, const Vector2i &vSize, uint32 nFormat, PLRenderer::TextureBuffer::EPixelFormat nTextureFormat, bool bNoMultisampleAntialiasing)
{
	// Is the extension EXT_framebuffer_object available?
	if (cRenderer.IsGL_EXT_framebuffer_object()) {
		// Check parameters
		if (vSize.x != 0 && vSize.y != 0) {
			// Save size
			m_vSize = vSize;

			// Get multisample antialiasing samples
			const uint32 nMultisampleAntialiasingSamples = (!bNoMultisampleAntialiasing && cRenderer.IsGL_EXT_framebuffer_multisample() && cRenderer.IsGL_EXT_framebuffer_blit()) ? cRenderer.GetMultisampleAntialiasingSamples() : 0;

			// Get current bound FBO
			GLint nFrameBufferT;
			glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, &nFrameBufferT);

			// Create color buffer?
			if (!PLRenderer::TextureBuffer::IsDepthFormat(nTextureFormat)) {
				// Get API pixel format
				const uint32 *pAPIPixelFormat = cRenderer.GetAPIPixelFormat(nTextureFormat);

				// Create color buffer
				glGenRenderbuffersEXT(1, &m_nColorBufferIndex);
				glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_nColorBufferIndex);
				if (nMultisampleAntialiasingSamples)
					glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, nMultisampleAntialiasingSamples, *pAPIPixelFormat, m_vSize.x, m_vSize.y);
				else
					glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, *pAPIPixelFormat, m_vSize.x, m_vSize.y);
			}

			// Create depth&stencil buffer
			GLuint nDepth = 0;
			bool bDepthStencil = false;
			if ((nFormat & Depth24) && (nFormat & Stencil) && cRenderer.IsGL_EXT_packed_depth_stencil()) {
				nDepth        = GL_DEPTH24_STENCIL8_EXT;
				bDepthStencil = true;
			} else {
				if (nFormat & Depth16)
					nDepth = GL_DEPTH_COMPONENT16;
				else if (nFormat & Depth24)
					nDepth = GL_DEPTH_COMPONENT24;
				else if (nFormat & Depth32)
					nDepth = GL_DEPTH_COMPONENT32;
			}
			if (nDepth) {
				glGenRenderbuffersEXT(1, &m_nDepthBufferIndex);
				glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_nDepthBufferIndex);
				if (nMultisampleAntialiasingSamples)
					glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, nMultisampleAntialiasingSamples, nDepth, m_vSize.x, m_vSize.y);
				else
					glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, nDepth, m_vSize.x, m_vSize.y);
			}

			// Create stencil buffer
			if (!bDepthStencil && (nFormat & Stencil)) {
				// [TODO] Stencil buffer support currently not working?! (but at least GL_EXT_packed_depth_stencil works)
//				glGenRenderbuffersEXT(1, &m_nStencilBufferIndex);
//				glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_nStencilBufferIndex);
//				glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_STENCIL_INDEX8_EXT, m_vSize.x, m_vSize.y);
			}

			// Create final FBO we will attach textures to
			glGenFramebuffersEXT(1, &m_nFrameBufferIndex);

			// Create multisample FBO used for rendering
			if (nMultisampleAntialiasingSamples) {
				glGenFramebuffersEXT(1, &m_nMultisampleFrameBufferIndex);
				glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_nMultisampleFrameBufferIndex);
			} else {
				glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_nFrameBufferIndex);
			}

			// Bind frame buffer
			if (m_nColorBufferIndex)
				glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, m_nColorBufferIndex);
			if (m_nDepthBufferIndex) {
				// Get depth buffer attachment
				m_nDepthBufferAttachment = ((nFormat & Stencil) && !m_nStencilBufferIndex) ? GL_DEPTH_STENCIL_ATTACHMENT : GL_DEPTH_ATTACHMENT_EXT;

				// Attach depth buffer
				glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, m_nDepthBufferAttachment, GL_RENDERBUFFER_EXT, m_nDepthBufferIndex);
			}
			if (m_nStencilBufferIndex)
				glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_nStencilBufferIndex);

			// Check frame buffer
			const bool bResult = CheckFrameBufferStatus();

			// Reset current bound FBO
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, nFrameBufferT);

			// Done
			return bResult;
		} else {
			PL_LOG(Error, "Width and height of FBO must be none zero!")
		}
	} else {
		PL_LOG(Error, "GL_EXT_framebuffer_object not supported!")
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
			case PLRenderer::Resource::TypeTextureBuffer1D:
				nTarget = GL_TEXTURE_1D;
				nOpenGLID = static_cast<TextureBuffer1D&>(cTextureBuffer).GetOpenGLTexture();
				break;

			case PLRenderer::Resource::TypeTextureBuffer2D:
				nTarget = GL_TEXTURE_2D;
				nOpenGLID = static_cast<TextureBuffer2D&>(cTextureBuffer).GetOpenGLTexture();
				break;

			case PLRenderer::Resource::TypeTextureBufferRectangle:
				nTarget = GL_TEXTURE_RECTANGLE_EXT;
				nOpenGLID = static_cast<TextureBufferRectangle&>(cTextureBuffer).GetOpenGLTexture();
				break;

			case PLRenderer::Resource::TypeTextureBuffer3D:
				nTarget = GL_TEXTURE_3D_EXT;
				nOpenGLID = static_cast<TextureBuffer3D&>(cTextureBuffer).GetOpenGLTexture();
				break;

			case PLRenderer::Resource::TypeTextureBufferCube:
				nTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB+nFace;
				nOpenGLID = static_cast<TextureBufferCube&>(cTextureBuffer).GetOpenGLTexture();
				break;
		}
		if (nTarget >= 0 && nOpenGLID) {
			// Check/clamp attach index
			if (nAttachIndex > 15)
				nAttachIndex = 15;

			// Bind
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_nFrameBufferIndex);
			PLRenderer::TextureBuffer::EPixelFormat nFormat = cTextureBuffer.GetFormat();
			if (nFormat == PLRenderer::TextureBuffer::D16 || nFormat == PLRenderer::TextureBuffer::D24 || nFormat == PLRenderer::TextureBuffer::D32) {
				glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, m_nDepthBufferAttachment, nTarget, nOpenGLID, 0);
			} else {
				glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT+nAttachIndex, nTarget, nOpenGLID, 0);
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
	// Use multisample?
	if (m_nMultisampleFrameBufferIndex) 
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_nMultisampleFrameBufferIndex);
	else {
		if (m_nFrameBufferIndex)
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_nFrameBufferIndex);
	}
}

/**
*  @brief
*    Finishes the process
*/
void FrameBufferObject::Finish()
{
	// Use multisample?
	if (m_nMultisampleFrameBufferIndex && m_nFrameBufferIndex) {
		glDrawBuffer(GL_NONE);
		glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, m_nMultisampleFrameBufferIndex);
		glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, m_nFrameBufferIndex);
		glBlitFramebufferEXT(0, 0, m_vSize.x, m_vSize.y, 0, 0, m_vSize.x, m_vSize.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_nFrameBufferIndex);
	}
}

/**
*  @brief
*    Unbinds the frame buffer
*/
void FrameBufferObject::Unbind()
{
	// Use multisample?
	if (m_nMultisampleFrameBufferIndex) {
		if (m_nFrameBufferIndex) {
			// Finish the process
			Finish();

			// Unbind FBO
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		}
	} else {
		// Unbind FBO
		if (m_nFrameBufferIndex)
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}
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
		glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, &nFrameBufferT);

		// [TODO] Test this/clean this up: May flicker on NVIDIA systems if we just attach to GL_DEPTH_ATTACHMENT
		GLuint nDepthBufferAttachment = GL_DEPTH_STENCIL_ATTACHMENT;

		// If we have a depth buffer, we destroy it because the depth buffer of the other FBO is much better *g*
		if (m_nDepthBufferIndex) {
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_nMultisampleFrameBufferIndex ? m_nMultisampleFrameBufferIndex : m_nFrameBufferIndex);
			glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, nDepthBufferAttachment, GL_RENDERBUFFER_EXT, 0);
			glDeleteRenderbuffersEXT(1, &m_nDepthBufferIndex);
		}

		// Take away the ownership of the depth buffer
		m_nDepthBufferIndex = cFBO.m_nDepthBufferIndex;
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, cFBO.m_nMultisampleFrameBufferIndex ? cFBO.m_nMultisampleFrameBufferIndex : cFBO.m_nFrameBufferIndex);
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, nDepthBufferAttachment, GL_RENDERBUFFER_EXT, 0);
		cFBO.m_nDepthBufferIndex = 0;
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_nMultisampleFrameBufferIndex ? m_nMultisampleFrameBufferIndex : m_nFrameBufferIndex);
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, nDepthBufferAttachment, GL_RENDERBUFFER_EXT, m_nDepthBufferIndex);

		// Reset current bound FBO
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, nFrameBufferT);
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
	// 'glCheckFramebufferStatusEXT' will always return an error :(
	GLint nDrawBufferT;
	glGetIntegerv(GL_DRAW_BUFFER, &nDrawBufferT);
	glDrawBuffer(GL_NONE);
	GLint nReadBufferT;
	glGetIntegerv(GL_READ_BUFFER, &nReadBufferT);
	glReadBuffer(GL_NONE);

	// Check FBO status
	GLenum nStatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	switch (nStatus) {
		case GL_FRAMEBUFFER_COMPLETE_EXT:
			PL_LOG(Debug, String::Format("Successfully created the frame buffer object (%dx%d)", m_vSize.x, m_vSize.y))
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
			PL_LOG(Error, "Incomplete attachment frame buffer object")
			bResult = false;
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
			PL_LOG(Error, "Incomplete missing attachment frame buffer object")
			bResult = false;
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
			PL_LOG(Error, "Incomplete dimensions frame buffer object")
			bResult = false;
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
			PL_LOG(Error, "Incomplete formats frame buffer object")
			bResult = false;
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
			PL_LOG(Error, "Incomplete draw buffer frame buffer object")
			bResult = false;
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
			PL_LOG(Error, "Incomplete read buffer frame buffer object")
			bResult = false;
			break;

		case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
			PL_LOG(Error, "Failed to create the frame buffer object, please verify your format")
			bResult = false;
			break;
	}

	// Restore current draw and read buffer
	glDrawBuffer(nDrawBufferT);
	glReadBuffer(nReadBufferT);

	// Done
	return bResult;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
