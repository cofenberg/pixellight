/*********************************************************\
 *  File: SurfaceTextureBuffer.cpp                       *
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
#include "PLRendererOpenGLES2/Renderer.h"
#include <PLRenderer/Renderer/TextureBuffer2D.h>
#include <PLRenderer/Renderer/TextureBufferCube.h>
#include "PLRendererOpenGLES2/FrameBufferObject.h"
#include "PLRendererOpenGLES2/SurfaceTextureBuffer.h"


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
*    Destructor
*/
SurfaceTextureBuffer::~SurfaceTextureBuffer()
{
	// De-initialize the OpenGL surface window
	DeInit();

	// Delete texture buffer
	if (m_cTextureBufferHandler.GetResource())
		delete m_cTextureBufferHandler.GetResource();
}

/**
*  @brief
*    Returns whether FBO is used or not
*/
bool SurfaceTextureBuffer::IsFBOUsed() const
{
	return (m_pFrameBufferObject != nullptr);
}

/**
*  @brief
*    Sets a color render target
*/
void SurfaceTextureBuffer::SetColorRenderTarget(uint8 nColorIndex, PLRenderer::TextureBuffer *pTextureBuffer)
{
	// Check color index
	if (nColorIndex < m_nMaxColorTargets) {
		// Set color render target
		while (!m_lstTextureBufferHandler[nColorIndex]) {
			PLRenderer::ResourceHandler *pTextureBufferHandler = new PLRenderer::ResourceHandler();
			m_lstTextureBufferHandler.Add(pTextureBufferHandler);
		}
		PLRenderer::ResourceHandler *pTextureBufferHandler = m_lstTextureBufferHandler[nColorIndex];
		pTextureBufferHandler->SetResource(pTextureBuffer);

		// Check FBO
		if (m_pFrameBufferObject && pTextureBuffer) {
			m_pFrameBufferObject->Bind();
			m_pFrameBufferObject->SwitchTarget(*pTextureBuffer, nColorIndex);

			// [TODO] Check me
			/*
			// Set draw buffers
			static const GLuint db[16] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3,
										   GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7,
										   GL_COLOR_ATTACHMENT8, GL_COLOR_ATTACHMENT9, GL_COLOR_ATTACHMENT10, GL_COLOR_ATTACHMENT11,
										   GL_COLOR_ATTACHMENT12, GL_COLOR_ATTACHMENT13, GL_COLOR_ATTACHMENT14, GL_COLOR_ATTACHMENT15};
			if (static_cast<Renderer&>(GetRenderer()).IsGL_ARB_draw_buffers())
				glDrawBuffersARB(m_nMaxColorTargets, db);
			else if (static_cast<Renderer&>(GetRenderer()).IsGL_ATI_draw_buffers())
				glDrawBuffersATI(m_nMaxColorTargets, db);
				*/
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SurfaceTextureBuffer::SurfaceTextureBuffer(PLRenderer::Renderer &cRenderer, PLRenderer::TextureBuffer &cTextureBuffer, uint32 nFlags, uint8 nMaxColorTargets) :
	PLRenderer::SurfaceTextureBuffer(cRenderer, nFlags, nMaxColorTargets),
	m_pFrameBufferObject(nullptr),
	m_nFace(0)
{
	// Init data
	m_cTextureBufferHandler.SetResource(&cTextureBuffer);

	// Initialize the OpenGL surface window
	Init();
}

/*
*  @brief
*    Create FBO
*/
bool SurfaceTextureBuffer::CreateFBO()
{
	// Get renderer
	Renderer &cRenderer = static_cast<Renderer&>(GetRenderer());

	// Get the depending of the texture buffer type
	PLRenderer::TextureBuffer *pTextureBuffer = static_cast<PLRenderer::TextureBuffer*>(m_cTextureBufferHandler.GetResource());
	if (pTextureBuffer) {
		// Get size
		Vector2i vSize(-1, -1);
		switch (pTextureBuffer->GetType()) {
			case PLRenderer::Resource::TypeTextureBuffer2D:
			{
				PLRenderer::TextureBuffer2D *pTextureBuffer2D = static_cast<PLRenderer::TextureBuffer2D*>(pTextureBuffer);
				vSize = pTextureBuffer2D->GetSize();
				break;
			}

			case PLRenderer::Resource::TypeTextureBufferCube:
			{
				PLRenderer::TextureBufferCube *pTextureBufferCube = static_cast<PLRenderer::TextureBufferCube*>(pTextureBuffer);
				const uint32 nSize = pTextureBufferCube->GetSize();
				vSize.x = vSize.y = nSize;
				break;
			}
		}
		if (vSize.x > 0 && vSize.y > 0) {
			// Initialize frame buffer
			m_pFrameBufferObject = new FrameBufferObject();
			uint32 nFormat = 0;
			// Depth buffer requested?
			if (m_nFlags & Depth)
				nFormat |= FrameBufferObject::Depth24;
			// Depth buffer only? (for instance for depth shadow mapping)
			if (pTextureBuffer->GetFormat() != PLRenderer::TextureBuffer::D16 && pTextureBuffer->GetFormat() != PLRenderer::TextureBuffer::D24 && pTextureBuffer->GetFormat() != PLRenderer::TextureBuffer::D32)
				nFormat |= FrameBufferObject::Color;
			// Stencil buffer requested?
			if (m_nFlags & Stencil)
				nFormat |= FrameBufferObject::Stencil;
			if (m_pFrameBufferObject->Initialize(cRenderer, vSize, nFormat, pTextureBuffer->GetFormat())) {
				// Jipi, all went fine and we are still here! :)
				return true;
			} else {
				// D'OH!!
				delete m_pFrameBufferObject;
				m_pFrameBufferObject = nullptr;
			}
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::SurfaceTexture functions   ]
//[-------------------------------------------------------]
PLRenderer::TextureBuffer *SurfaceTextureBuffer::GetTextureBuffer() const
{
	return static_cast<PLRenderer::TextureBuffer*>(m_cTextureBufferHandler.GetResource());
}

uint8 SurfaceTextureBuffer::GetTextureBufferFace() const
{
	return m_nFace;
}

void SurfaceTextureBuffer::TakeDepthBufferFromSurfaceTextureBuffer(PLRenderer::SurfaceTextureBuffer &cSurfaceTextureBuffer)
{
	// Cast to OpenGL implementation
	SurfaceTextureBuffer &cSurfaceTextureBufferOpenGL = static_cast<SurfaceTextureBuffer&>(cSurfaceTextureBuffer);

	// Both must use FBO
	if (m_pFrameBufferObject && cSurfaceTextureBufferOpenGL.m_pFrameBufferObject)
		m_pFrameBufferObject->TakeDepthBufferFromFBO(*cSurfaceTextureBufferOpenGL.m_pFrameBufferObject);
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Surface functions          ]
//[-------------------------------------------------------]
Vector2i SurfaceTextureBuffer::GetSize() const
{
	// Return the size depending of the texture buffer type
	PLRenderer::TextureBuffer *pTextureBuffer = static_cast<PLRenderer::TextureBuffer*>(m_cTextureBufferHandler.GetResource());
	if (pTextureBuffer) {
		switch (pTextureBuffer->GetType()) {
			case PLRenderer::Resource::TypeTextureBuffer2D:
				return static_cast<PLRenderer::TextureBuffer2D*>(pTextureBuffer)->GetSize();

			case PLRenderer::Resource::TypeTextureBufferCube:
			{
				const uint32 nSize = static_cast<PLRenderer::TextureBufferCube*>(pTextureBuffer)->GetSize();
				return Vector2i(nSize, nSize);
			}
		}
	}

	// Error!
	return Vector2i::Zero;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Surface functions         ]
//[-------------------------------------------------------]
bool SurfaceTextureBuffer::Init()
{
	// First, de-initialize old PBuffer
	DeInit();

	// Can we use a nice frame buffer object?
	return CreateFBO();
}

void SurfaceTextureBuffer::DeInit()
{
	// If this is the current render target, make the main window to the new current one
	Renderer &cRenderer = static_cast<Renderer&>(GetRenderer());
	if (cRenderer.GetRenderTarget() == this)
		cRenderer.SetRenderTarget(nullptr);

	// Destroy frame buffer object
	if (m_pFrameBufferObject) {
		delete m_pFrameBufferObject;
		m_pFrameBufferObject = nullptr;
	}

	// Cleanup texture buffer handlers
	for (uint32 i=0; i<m_lstTextureBufferHandler.GetNumOfElements(); i++)
		delete m_lstTextureBufferHandler[i];
	m_lstTextureBufferHandler.Clear();
}

bool SurfaceTextureBuffer::MakeCurrent(uint8 nFace)
{
	// Check whether the data is valid and whether there's a texture buffer
	if (m_cTextureBufferHandler.GetResource() && GetTextureBuffer()) {
		// Set target face
		if (GetTextureBuffer()->GetType() == PLRenderer::Resource::TypeTextureBufferCube)
			m_nFace = nFace;
		else
			m_nFace = 0;

		// Cleanup texture buffer handlers
		for (uint32 i=0; i<m_lstTextureBufferHandler.GetNumOfElements(); i++)
			delete m_lstTextureBufferHandler[i];
		m_lstTextureBufferHandler.Clear();

		// Add primary texture buffer handler
		PLRenderer::ResourceHandler *pTextureBufferHandler = new PLRenderer::ResourceHandler();
		pTextureBufferHandler->SetResource(m_cTextureBufferHandler.GetResource());
		m_lstTextureBufferHandler.Add(pTextureBufferHandler);

		// Frame buffer object used?
		if (m_pFrameBufferObject && m_cTextureBufferHandler.GetResource()) {
			m_pFrameBufferObject->SwitchTarget(static_cast<PLRenderer::TextureBuffer&>(*m_cTextureBufferHandler.GetResource()), 0, nFace);
			m_pFrameBufferObject->Bind();

			// Need rendering to depth only
			PLRenderer::TextureBuffer::EPixelFormat nFormat = GetTextureBuffer()->GetFormat();
			if (nFormat == PLRenderer::TextureBuffer::D16 || nFormat == PLRenderer::TextureBuffer::D24 || nFormat == PLRenderer::TextureBuffer::D32) {
				// [TODO] Check me
				/*
				glDrawBuffer(GL_NONE);
				glReadBuffer(GL_NONE);
				*/
			} else {
				// [TODO] Check me
				/*
				// Set draw buffers
				GLuint db[4] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT,
								 GL_COLOR_ATTACHMENT2_EXT, GL_COLOR_ATTACHMENT3_EXT };
				if (static_cast<Renderer&>(GetRenderer()).IsGL_ARB_draw_buffers())
					glDrawBuffersARB(m_nMaxColorTargets, db);
				else if (static_cast<Renderer&>(GetRenderer()).IsGL_ATI_draw_buffers())
					glDrawBuffersATI(m_nMaxColorTargets, db);
					*/
			}
		}

		// Enable/disable multisample - "shouldn't" have an effect when render to texture, but safe is safe :D
		GetRenderer().SetRenderState(PLRenderer::RenderState::MultisampleEnable, !(GetFlags() & NoMultisampleAntialiasing));

		// Done
		return true;
	}

	// Error!
	return false;
}

bool SurfaceTextureBuffer::UnmakeCurrent()
{
	// Check whether the data is valid
	if (!m_cTextureBufferHandler.GetResource())
		return false; // Error!
	Renderer &cRenderer = static_cast<Renderer&>(GetRenderer());

	// Frame buffer object used?
	if (m_pFrameBufferObject) {
		m_pFrameBufferObject->Unbind();

		// Try to build mipmaps automatically on the GPU?
		if (GetFlags() & Mipmaps) {
			PLRenderer::TextureBuffer *pTextureBuffer = cRenderer.GetTextureBuffer(0);
			cRenderer.SetTextureBuffer(0, static_cast<PLRenderer::TextureBuffer*>(m_cTextureBufferHandler.GetResource()));
			switch (m_cTextureBufferHandler.GetResource()->GetType()) {
				case PLRenderer::Resource::TypeTextureBuffer2D:
					glGenerateMipmap(GL_TEXTURE_2D);
					break;

				case PLRenderer::Resource::TypeTextureBufferCube:
					glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
					break;
			}
			cRenderer.SetTextureBuffer(0, pTextureBuffer);
		}

		// [TODO] Check me
		/*
		PLRenderer::TextureBuffer::EPixelFormat nFormat = GetTextureBuffer()->GetFormat();
		if (nFormat == PLRenderer::TextureBuffer::D16 || nFormat == PLRenderer::TextureBuffer::D24 || nFormat == PLRenderer::TextureBuffer::D32) {
			glDrawBuffer(GL_BACK);
			glReadBuffer(GL_BACK);
		}*/

	// Do only use glCopyTexSubImage2D()
	} else if (m_lstTextureBufferHandler.GetNumOfElements()) {
		PLRenderer::TextureBuffer *pTextureBuffer = static_cast<PLRenderer::TextureBuffer*>(m_lstTextureBufferHandler[0]->GetResource());
		if (pTextureBuffer) {
			cRenderer.MakeTextureBufferCurrent(*pTextureBuffer, 0);
			switch (pTextureBuffer->GetType()) {
				case PLRenderer::Resource::TypeTextureBuffer2D:
					glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, GetSize().x, GetSize().y);
					break;

				case PLRenderer::Resource::TypeTextureBufferCube:
					glCopyTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+m_nFace, 0, 0, 0, 0, 0, GetSize().x, GetSize().y);
					break;
			}
		}
	}

	// Cleanup texture buffer handlers
	for (uint32 i=0; i<m_lstTextureBufferHandler.GetNumOfElements(); i++)
		delete m_lstTextureBufferHandler[i];
	m_lstTextureBufferHandler.Clear();

	// Reset target face
	m_nFace = 0;

	// Done
	return true;
}

bool SurfaceTextureBuffer::Present()
{
	// Nothing to do here...
	return true;
}

void SurfaceTextureBuffer::BackupDeviceData()
{
	DeInit();
}

void SurfaceTextureBuffer::RestoreDeviceData()
{
	Init();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
