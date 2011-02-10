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
#include "PLRendererOpenGL/Renderer.h"
#include <PLRenderer/Renderer/TextureBuffer1D.h>
#include <PLRenderer/Renderer/TextureBuffer2D.h>
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include <PLRenderer/Renderer/TextureBufferCube.h>
#include "PLRendererOpenGL/Misc/pbuffer.h"
#include "PLRendererOpenGL/Misc/FrameBufferObject.h"
#include "PLRendererOpenGL/SurfaceTextureBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLRendererOpenGL {


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
*    Returns whether a PBuffer is used or not
*/
bool SurfaceTextureBuffer::IsPBufferUsed() const
{
	return (m_pPBuffer != nullptr);
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

			// Set draw buffers
			static const GLuint db[16] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT, GL_COLOR_ATTACHMENT3_EXT,
										   GL_COLOR_ATTACHMENT4_EXT, GL_COLOR_ATTACHMENT5_EXT, GL_COLOR_ATTACHMENT6_EXT, GL_COLOR_ATTACHMENT7_EXT,
										   GL_COLOR_ATTACHMENT8_EXT, GL_COLOR_ATTACHMENT9_EXT, GL_COLOR_ATTACHMENT10_EXT, GL_COLOR_ATTACHMENT11_EXT,
										   GL_COLOR_ATTACHMENT12_EXT, GL_COLOR_ATTACHMENT13_EXT, GL_COLOR_ATTACHMENT14_EXT, GL_COLOR_ATTACHMENT15_EXT};
			if (static_cast<Renderer&>(GetRenderer()).IsGL_ARB_draw_buffers())
				glDrawBuffersARB(m_nMaxColorTargets, db);
			else if (static_cast<Renderer&>(GetRenderer()).IsGL_ATI_draw_buffers())
				glDrawBuffersATI(m_nMaxColorTargets, db);
		}
	}
}

/**
*  @brief
*    Finishes the process
*/
void SurfaceTextureBuffer::Finish()
{
	// Check whether the data is valid and whether frame buffer object used
	if (m_cTextureBufferHandler.GetResource() && m_pFrameBufferObject)
		m_pFrameBufferObject->Finish();
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
	m_pPBuffer(nullptr),
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

	// FBO supported?
	if (cRenderer.IsGL_EXT_framebuffer_object()) {
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

				case PLRenderer::Resource::TypeTextureBufferRectangle:
				{
					PLRenderer::TextureBufferRectangle *pTextureBufferRectangle = static_cast<PLRenderer::TextureBufferRectangle*>(pTextureBuffer);
					vSize = pTextureBufferRectangle->GetSize();
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
				if (m_pFrameBufferObject->Initialize(cRenderer, vSize, nFormat, pTextureBuffer->GetFormat(), (m_nFlags & NoMultisampleAntialiasing) != 0)) {
					// Jipi, all went fine and we are still here! :)
					return true;
				} else {
					// DAMN!
					delete m_pFrameBufferObject;
					m_pFrameBufferObject = nullptr;
				}
			}
		}
	}

	// Error!
	return false;
}

/*
*  @brief
*    Create PBuffer
*/
bool SurfaceTextureBuffer::CreatePBuffer()
{
	// Get renderer and check whether PBuffer is support
	Renderer &cRenderer = static_cast<Renderer&>(GetRenderer());
	if (cRenderer.IsWGL_ARB_pbuffer()) {
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

				case PLRenderer::Resource::TypeTextureBufferRectangle:
				{
					PLRenderer::TextureBufferRectangle *pTextureBufferRectangle = static_cast<PLRenderer::TextureBufferRectangle*>(pTextureBuffer);
					vSize = pTextureBufferRectangle->GetSize();
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
				// Get the required color components aas string
				String sColor;
				switch (pTextureBuffer->GetFormat()) {
					case PLRenderer::TextureBuffer::D16:
						sColor = "depth=16";
						break;

					case PLRenderer::TextureBuffer::D24:
						sColor = "depth=24";
						break;

					case PLRenderer::TextureBuffer::D32:
						sColor = "depth=32";
						break;

					case PLRenderer::TextureBuffer::R8G8B8:
						sColor = "rgb";
						break;

					case PLRenderer::TextureBuffer::R8G8B8A8:
						sColor = "rgba";
						break;

					case PLRenderer::TextureBuffer::R16G16B16A16:
						sColor = "rgba";
						break;

					case PLRenderer::TextureBuffer::L16F:
						sColor = cRenderer.IsWGL_ATI_pixel_format_float() ? "r ati_float=16" : "r float=16";
						break;

					case PLRenderer::TextureBuffer::L32F:
						sColor = cRenderer.IsWGL_ATI_pixel_format_float() ? "r ati_float=32" : "r float=32";
						break;

					case PLRenderer::TextureBuffer::R16G16B16A16F:
						sColor = cRenderer.IsWGL_ATI_pixel_format_float() ? "rgba ati_float=16" : "rgba float=16";
						break;

					case PLRenderer::TextureBuffer::R32G32B32A32F:
						sColor = cRenderer.IsWGL_ATI_pixel_format_float() ? "rgba ati_float=32" : "rgba float=32";
						break;
				}
				if (sColor.GetLength()) {
					// Get texture buffer type as string
					String sType;
					switch (pTextureBuffer->GetType()) {
						case PLRenderer::Resource::TypeTextureBuffer2D:
							sType = "texture2D";
							break;

						case PLRenderer::Resource::TypeTextureBufferRectangle:
							sType = "textureRECT";
							break;

						case PLRenderer::Resource::TypeTextureBufferCube:
							sType = "textureCUBE";
							break;
					}
					if (sType.GetLength()) {
						// Build mipmaps automatically on the GPU?
						if ((m_nFlags & Mipmaps) && cRenderer.IsGL_SGIS_generate_mipmap())
							sType += " mipmap";

						// Get the number of auxiliary buffers as string - but only if we need at least two color
						// render targets ('aux' may cause troubles if not support correctly...)
						String sAuxiliaryBuffers;
						if (m_nMaxColorTargets-1)
							sAuxiliaryBuffers = String::Format("aux=%d", m_nMaxColorTargets-1);

						// Initialize the PBuffer now that we have a valid context
						// that we can use during the p-buffer creation process

						// Bind the dynamic texture buffer
						cRenderer.MakeTextureBufferCurrent(*pTextureBuffer, 0);

						// First: TRY ALL!! :)
						m_pPBuffer = new PBuffer(sColor + ' ' + sType + ' ' + sAuxiliaryBuffers, true);
						if (m_pPBuffer) {
							if (m_pPBuffer->Initialize(vSize.x, vSize.y, false, true))
								return true; // Done

							// Cleanup
							delete m_pPBuffer;

							// Second: Ignore type
							m_pPBuffer = new PBuffer(sColor + ' ' + sAuxiliaryBuffers, true);
							if (m_pPBuffer) {
								if (m_pPBuffer->Initialize(vSize.x, vSize.y, false, true))
									return true; // Done

								// Cleanup
								delete m_pPBuffer;
								m_pPBuffer = nullptr;
							}
						}
					}
				}
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

			case PLRenderer::Resource::TypeTextureBufferRectangle:
				return static_cast<PLRenderer::TextureBufferRectangle*>(pTextureBuffer)->GetSize();

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
	if (!CreateFBO()) {
		// Ok, we can't use FBO, try if we can used an ugly PBuffer... :(
		// [TODO] At the moment, MRT will cause a COMPLETE (!) system hang for me, so do NOT use it for sure
		if (m_nMaxColorTargets > 1)
			return false; // Error!
		else
			return CreatePBuffer();
	}

	// Done
	return true;
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

	// Destroy PBuffer
	if (m_pPBuffer) {
		// [TODO] Check me
	#ifdef WIN32
/*		{ // Release buffers
			// Draw buffers
			GLenum nDrawBuffers[5]    = { GL_FRONT_LEFT, GL_AUX0, GL_AUX1, GL_AUX2, GL_AUX3 };
			GLenum nDrawBuffersARB[5] = { WGL_FRONT_LEFT_ARB, WGL_AUX0_ARB, WGL_AUX1_ARB, WGL_AUX2_ARB, WGL_AUX3_ARB };

			// Initialize some graphics state for the PBuffer's rendering context
			if (m_pPBuffer->IsTexture()) {
				for (uint32 i=0; i<m_nMaxColorTargets; i++)
					m_pPBuffer->Release(nDrawBuffersARB[i]);
			}
		}*/
	#endif

		// Destroy
		delete m_pPBuffer;
		m_pPBuffer = nullptr;
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
				glDrawBuffer(GL_NONE);
				glReadBuffer(GL_NONE);
			} else {
				// Set draw buffers
				GLuint db[4] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT,
								 GL_COLOR_ATTACHMENT2_EXT, GL_COLOR_ATTACHMENT3_EXT };
				if (static_cast<Renderer&>(GetRenderer()).IsGL_ARB_draw_buffers())
					glDrawBuffersARB(m_nMaxColorTargets, db);
				else if (static_cast<Renderer&>(GetRenderer()).IsGL_ATI_draw_buffers())
					glDrawBuffersATI(m_nMaxColorTargets, db);
			}

		// PBuffer used?
		} else if (m_pPBuffer) {
			// Draw buffers
			GLenum nDrawBuffers[5] = { GL_FRONT_LEFT, GL_AUX0, GL_AUX1, GL_AUX2, GL_AUX3 };
		#ifdef WIN32
			GLenum nDrawBuffersARB[5] = { WGL_FRONT_LEFT_ARB, WGL_AUX0_ARB, WGL_AUX1_ARB, WGL_AUX2_ARB, WGL_AUX3_ARB };

			// Initialize some graphics state for the PBuffer's rendering context
			if (m_pPBuffer->IsTexture()) {
				for (uint32 i=0; i<m_nMaxColorTargets; i++)
					m_pPBuffer->Release(nDrawBuffersARB[i], m_nFace);
			}

			// Handle mode switch
			m_pPBuffer->HandleModeSwitch();
		#endif

			// Activate p-buffer
			m_pPBuffer->Activate();

			// Set draw buffers
			if (static_cast<Renderer&>(GetRenderer()).IsGL_ARB_draw_buffers())
				glDrawBuffersARB(m_nMaxColorTargets, nDrawBuffers);
			else if (static_cast<Renderer&>(GetRenderer()).IsGL_ATI_draw_buffers())
				glDrawBuffersATI(m_nMaxColorTargets, nDrawBuffers);

		// Else...
		} // ... If there's no PBuffer, we can still 'render to texture' by only using glCopyTexSubImage2D() to
		  // copy the drawn stuff into a texture buffer. But this way, the current framebuffer content is 'overdrawn' and
		  // the texture buffer size we can render in is limited to the screen size.

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
					glGenerateMipmapEXT(GL_TEXTURE_2D);
					break;

//				case PLRenderer::Resource::TypeTextureBufferRectangle:
//					glGenerateMipmapEXT(GL_TEXTURE_RECTANGLE_EXT);
//					break; // Not supported...

				case PLRenderer::Resource::TypeTextureBufferCube:
					glGenerateMipmapEXT(GL_TEXTURE_CUBE_MAP_ARB);
					break;
			}
			cRenderer.SetTextureBuffer(0, pTextureBuffer);
		}

		PLRenderer::TextureBuffer::EPixelFormat nFormat = GetTextureBuffer()->GetFormat();
		if (nFormat == PLRenderer::TextureBuffer::D16 || nFormat == PLRenderer::TextureBuffer::D24 || nFormat == PLRenderer::TextureBuffer::D32) {
			glDrawBuffer(GL_BACK);
			glReadBuffer(GL_BACK);
		}

	// PBuffer used?
	} else if (m_pPBuffer) {
		// Draw buffers
		GLenum nDrawBuffers[5] = { GL_FRONT_LEFT, GL_AUX0, GL_AUX1, GL_AUX2, GL_AUX3 };

		#ifdef WIN32
			GLenum nDrawBuffersARB[5] = { WGL_FRONT_LEFT_ARB, WGL_AUX0_ARB, WGL_AUX1_ARB, WGL_AUX2_ARB, WGL_AUX3_ARB };

			// Initialize some state for the GLUT window's rendering context
			if (m_pPBuffer->IsTexture()) {
				// Deactivate p-buffer
				m_pPBuffer->Deactivate();

				// Bind texture buffers
				for (uint32 i=0; i<m_lstTextureBufferHandler.GetNumOfElements(); i++) {
					PLRenderer::TextureBuffer *pTextureBuffer = static_cast<PLRenderer::TextureBuffer*>(m_lstTextureBufferHandler[i]->GetResource());
					if (pTextureBuffer) {
						cRenderer.MakeTextureBufferCurrent(*pTextureBuffer, 0);
						m_pPBuffer->Bind(nDrawBuffersARB[i], m_nFace);
					}
				}
			} else
		#endif
		{ // Copy to texture buffer using glCopyTexSubImage2D()
			// Copy texture buffers
			for (uint32 i=0; i<m_lstTextureBufferHandler.GetNumOfElements(); i++) {
				PLRenderer::TextureBuffer *pTextureBuffer = static_cast<PLRenderer::TextureBuffer*>(m_lstTextureBufferHandler[i]->GetResource());
				if (pTextureBuffer) {
					glDrawBuffer(nDrawBuffers[i]);
					cRenderer.MakeTextureBufferCurrent(*pTextureBuffer, 0);

					// Copy sub image
					switch (pTextureBuffer->GetType()) {
						case PLRenderer::Resource::TypeTextureBuffer2D:
							glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, GetSize().x, GetSize().y);
							break;

						case PLRenderer::Resource::TypeTextureBufferRectangle:
							glCopyTexSubImage2D(GL_TEXTURE_RECTANGLE_EXT, 0, 0, 0, 0, 0, GetSize().x, GetSize().y);
							break;

						case PLRenderer::Resource::TypeTextureBufferCube:
							glCopyTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB+m_nFace, 0, 0, 0, 0, 0, GetSize().x, GetSize().y);
							break;
					}
				}
			}

			// Deactivate p-buffer
			m_pPBuffer->Deactivate();
		}

		// Reset draw buffer
		glDrawBuffer(GL_BACK);

	// Do only use glCopyTexSubImage2D()
	} else if (m_lstTextureBufferHandler.GetNumOfElements()) {
		PLRenderer::TextureBuffer *pTextureBuffer = static_cast<PLRenderer::TextureBuffer*>(m_lstTextureBufferHandler[0]->GetResource());
		if (pTextureBuffer) {
			cRenderer.MakeTextureBufferCurrent(*pTextureBuffer, 0);
			switch (pTextureBuffer->GetType()) {
				case PLRenderer::Resource::TypeTextureBuffer2D:
					glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, GetSize().x, GetSize().y);
					break;

				case PLRenderer::Resource::TypeTextureBufferRectangle:
					glCopyTexSubImage2D(GL_TEXTURE_RECTANGLE_EXT, 0, 0, 0, 0, 0, GetSize().x, GetSize().y);
					break;

				case PLRenderer::Resource::TypeTextureBufferCube:
					glCopyTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB+m_nFace, 0, 0, 0, 0, 0, GetSize().x, GetSize().y);
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
