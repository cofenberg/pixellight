/*********************************************************\
 *  File: PostProcessor.cpp                              *
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
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/Program.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/SamplerStates.h>
#include <PLRenderer/Renderer/ProgramUniform.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLRenderer/Renderer/ProgramAttribute.h>
#include <PLRenderer/Renderer/SurfaceTextureBuffer.h>
#include <PLRenderer/Material/Material.h>
#include <PLRenderer/Material/Parameter.h>
#include <PLRenderer/Material/ParameterManager.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLRenderer/Texture/TextureManager.h>
#include "PLCompositing/Shaders/PostProcessing/PostProcess.h"
#include "PLCompositing/Shaders/PostProcessing/PostProcessLoader.h"
#include "PLCompositing/Shaders/PostProcessing/PostProcessor.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PostProcessor::PostProcessor() :
	m_nTextureFormat(TextureBuffer::R8G8B8A8),
	m_pColorSurface(nullptr),
	m_pVertexBuffer(nullptr),
	m_bProcessing(false),
	m_bFirstPostProcess(true),
	m_fExtentX(1.0f),
	m_fExtentY(1.0f),
	m_nFixedFillModeBackup(0),
	m_bCurrentRenderTarget(false)
{
	m_pRenderTarget[0] = m_pRenderTarget[1] = nullptr;
	m_bClearRenderTarget[0] = m_bClearRenderTarget[1] = false;
}

/**
*  @brief
*    Destructor
*/
PostProcessor::~PostProcessor()
{
	if (m_pVertexBuffer)
		delete m_pVertexBuffer;
}

/**
*  @brief
*    Returns the texture format
*/
TextureBuffer::EPixelFormat PostProcessor::GetTextureFormat() const
{
	return m_nTextureFormat;
}

/**
*  @brief
*    Sets the texture format
*/
void PostProcessor::SetTextureFormat(TextureBuffer::EPixelFormat nFormat)
{
	m_nTextureFormat = nFormat;
}

/**
*  @brief
*    Returns whether or not processing is currently active
*/
bool PostProcessor::IsProcessing() const
{
	return m_bProcessing;
}

/**
*  @brief
*    Begins the processing
*/
bool PostProcessor::BeginProcessing(Renderer &cRenderer, SurfaceTextureBuffer &cColorSurface)
{
	// Processing already active?
	if (m_bProcessing)
		return false; // Error!
	else {
		// Initialize
		m_bProcessing          = true;
		m_bFirstPostProcess    = true;
		m_bCurrentRenderTarget = false;
		m_fExtentX             = 1.0f;
		m_fExtentY             = 1.0f;

		// Get surface dimension
		m_pColorSurface = &cColorSurface;
		const Vector2i vSize = cColorSurface.GetSize();

		// Create render targets or recreate them if required
		for (int i=0; i<2; i++) {
			SurfaceTextureBuffer *pRenderTarget = m_pRenderTarget[i];
			if (pRenderTarget) {
				if (pRenderTarget->GetFormat() == m_pColorSurface->GetFormat() &&
					pRenderTarget->GetSize()   == vSize)
					continue; // We don't have to recreate this render target

				// Dam'n we have to recreate this render target :(
				delete pRenderTarget;
			}

			// Create render target - we do not need a depth and/or stencil buffer here :)
			if (m_pColorSurface->GetTextureBuffer()->GetType() == PLRenderer::Resource::TypeTextureBufferRectangle)
				m_pRenderTarget[i] = cRenderer.CreateSurfaceTextureBufferRectangle(vSize, m_pColorSurface->GetFormat(), SurfaceTextureBuffer::NoMultisampleAntialiasing);
			else
				m_pRenderTarget[i] = cRenderer.CreateSurfaceTextureBuffer2D(vSize, m_pColorSurface->GetFormat(), SurfaceTextureBuffer::NoMultisampleAntialiasing);
		}

		// Initialize vertex buffer
		if (!m_pVertexBuffer) {
			m_pVertexBuffer = cRenderer.CreateVertexBuffer();
			// Position
			m_pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float4);
			// Texture coordinate for post-process source
			m_pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
			// Texture coordinate for the original scene
			m_pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 1, VertexBuffer::Float2);
			// Allocate
			m_pVertexBuffer->Allocate(4);
		}
		if (m_pVertexBuffer->Lock(Lock::WriteOnly)) {
		// Vertex 0
			// Position
			float *pfVertex = (float*)m_pVertexBuffer->GetData(0, VertexBuffer::Position);
			pfVertex[Vector4::X] = 0.0f;
			pfVertex[Vector4::Y] = 0.0f;
			pfVertex[Vector4::Z] = 1.0f;
			pfVertex[Vector4::W] = 1.0f;
			// Texture coordinate 0
			pfVertex = (float*)m_pVertexBuffer->GetData(0, VertexBuffer::TexCoord, 0);
			pfVertex[Vector2::X] = 0.0f;
			pfVertex[Vector2::Y] = 0.0f;
			// Texture coordinate 1
			pfVertex = (float*)m_pVertexBuffer->GetData(0, VertexBuffer::TexCoord, 1);
			pfVertex[Vector2::X] = 0.0f;
			pfVertex[Vector2::Y] = 0.0f;

		// Vertex 1
			// Position
			pfVertex = (float*)m_pVertexBuffer->GetData(1, VertexBuffer::Position);
			pfVertex[Vector4::X] = (float)vSize.x;
			pfVertex[Vector4::Y] = 0.0f;
			pfVertex[Vector4::Z] = 1.0f;
			pfVertex[Vector4::W] = 1.0f;
			// Texture coordinate 0
			pfVertex = (float*)m_pVertexBuffer->GetData(1, VertexBuffer::TexCoord, 0);
			pfVertex[Vector2::X] = 1.0f;
			pfVertex[Vector2::Y] = 0.0f;
			// Texture coordinate 1
			pfVertex = (float*)m_pVertexBuffer->GetData(1, VertexBuffer::TexCoord, 1);
			pfVertex[Vector2::X] = 1.0f;
			pfVertex[Vector2::Y] = 0.0f;

		// Vertex 2
			// Position
			pfVertex = (float*)m_pVertexBuffer->GetData(2, VertexBuffer::Position);
			pfVertex[Vector4::X] = 0.0f;
			pfVertex[Vector4::Y] = (float)vSize.y;
			pfVertex[Vector4::Z] = 1.0f;
			pfVertex[Vector4::W] = 1.0f;
			// Texture coordinate 0
			pfVertex = (float*)m_pVertexBuffer->GetData(2, VertexBuffer::TexCoord, 0);
			pfVertex[Vector2::X] = 0.0f;
			pfVertex[Vector2::Y] = 1.0f;
			// Texture coordinate 1
			pfVertex = (float*)m_pVertexBuffer->GetData(2, VertexBuffer::TexCoord, 1);
			pfVertex[Vector2::X] = 0.0f;
			pfVertex[Vector2::Y] = 1.0f;

		// Vertex 3
			// Position
			pfVertex = (float*)m_pVertexBuffer->GetData(3, VertexBuffer::Position);
			pfVertex[Vector4::X] = (float)vSize.x;
			pfVertex[Vector4::Y] = (float)vSize.y;
			pfVertex[Vector4::Z] = 1.0f;
			pfVertex[Vector4::W] = 1.0f;
			// Texture coordinate 0
			pfVertex = (float*)m_pVertexBuffer->GetData(3, VertexBuffer::TexCoord, 0);
			pfVertex[Vector2::X] = 1.0f;
			pfVertex[Vector2::Y] = 1.0f;
			// Texture coordinate 1
			pfVertex = (float*)m_pVertexBuffer->GetData(3, VertexBuffer::TexCoord, 1);
			pfVertex[Vector2::X] = 1.0f;
			pfVertex[Vector2::Y] = 1.0f;

			// Unlock the vertex buffer
			m_pVertexBuffer->Unlock();
		}

		// Begin 2D mode
		m_nFixedFillModeBackup = cRenderer.GetRenderState(RenderState::FixedFillMode);
		cRenderer.SetRenderState(RenderState::FixedFillMode, Fill::Solid);
		FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
		if (pFixedFunctions)
			pFixedFunctions->ResetTransformStates();
		cRenderer.GetDrawHelpers().Begin2DMode(0.0f, (float)vSize.y, (float)vSize.x, 0.0f);

		// Done
		return true;
	}
}

/**
*  @brief
*    Performs a single post process
*/
bool PostProcessor::Process(const PostProcess &cPostProcess)
{
	// Processing currently active?
	if (m_bProcessing && m_pVertexBuffer && cPostProcess.IsActive()) {
		Renderer &cRenderer = m_pVertexBuffer->GetRenderer();

		// Get material and set current render target
		Material *pMaterial = cPostProcess.GetMaterial();
		if (pMaterial && cRenderer.SetRenderTarget(m_pRenderTarget[m_bCurrentRenderTarget])) {
			// If the extents has been modified, the texture coordinates
			// in the quad need to be updated
			if (m_pVertexBuffer->Lock()) {
				// Check extents
				float *pfVertex = (float*)m_pVertexBuffer->GetData(1, VertexBuffer::TexCoord, 0);
				if (pfVertex[Vector2::X] != m_fExtentX) {
					pfVertex[Vector2::X] = m_fExtentX;
					pfVertex = (float*)m_pVertexBuffer->GetData(3, VertexBuffer::TexCoord, 0);
					pfVertex[Vector2::X] = m_fExtentX;
				}
				pfVertex = (float*)m_pVertexBuffer->GetData(2, VertexBuffer::TexCoord, 0);
				if (pfVertex[Vector2::Y] != m_fExtentY) {
					pfVertex[Vector2::Y] = m_fExtentY;
					pfVertex = (float*)m_pVertexBuffer->GetData(3, VertexBuffer::TexCoord, 0);
					pfVertex[Vector2::Y] = m_fExtentY;
				}

				// Check if the material has annotation for extent info. Update
				// fScaleX and fScaleY if it does. Otherwise, default to 1.0f.
				float fScaleX = 1.0f, fScaleY = 1.0f;
				const Parameter *pParameter = pMaterial->GetParameter("ScaleX");
				if (pParameter)
					pParameter->GetValue1f(fScaleX);
				pParameter = pMaterial->GetParameter("ScaleY");
				if (pParameter)
					pParameter->GetValue1f(fScaleY);

				// Now modify the quad according to the scaling values specified for this material
				char nIncSize = 0;
				if (fScaleX != 1.0f) {
					if (fScaleX < 1.0f)
						m_bClearRenderTarget[0] = m_bClearRenderTarget[1] = true;
					else
						nIncSize++;
					pfVertex = (float*)m_pVertexBuffer->GetData(1, VertexBuffer::Position, 0);
					pfVertex[Vector2::X] = pfVertex[Vector2::X]*fScaleX;
					pfVertex = (float*)m_pVertexBuffer->GetData(3, VertexBuffer::Position, 0);
					pfVertex[Vector2::X] = pfVertex[Vector2::X]*fScaleX;
				}
				if (fScaleY != 1.0f) {
					if (fScaleY < 1.0f)
						m_bClearRenderTarget[0] = m_bClearRenderTarget[1] = true;
					else
						nIncSize++;
					pfVertex = (float*)m_pVertexBuffer->GetData(2, VertexBuffer::Position, 0);
					pfVertex[Vector2::Y] = pfVertex[Vector2::Y]*fScaleY;
					pfVertex = (float*)m_pVertexBuffer->GetData(3, VertexBuffer::Position, 0);
					pfVertex[Vector2::Y] = pfVertex[Vector2::Y]*fScaleY;
				}
				if (nIncSize == 2)
					m_bClearRenderTarget[0] = m_bClearRenderTarget[1] = false;

				// Update extents
				m_fExtentX *= fScaleX;
				m_fExtentY *= fScaleY;

				// Unlock the vertex buffer
				m_pVertexBuffer->Unlock();
			}

			// If one or more kernel exists, convert kernel from pixel space to texel space
			uint32 nType = PLRenderer::Resource::TypeTextureBufferRectangle;
			if (m_pColorSurface->GetTextureBuffer())
				nType = m_pColorSurface->GetTextureBuffer()->GetType();
			uint32 nKernel = 0;
			Parameter *pParameter = nullptr;
			do {
				pParameter = pMaterial->GetParameter(String::Format("PixelKernel[%d]", nKernel));
				if (pParameter) {
					// Get pixel kernel
					float fX, fY;
					pParameter->GetValue2f(fX, fY);

					// Set texel kernel
					pParameter = pMaterial->GetParameter(String::Format("TexelKernel[%d]", nKernel));
					if (pParameter) {
						// Only for none rectangle texture buffers, please
						if (nType == PLRenderer::Resource::TypeTextureBufferRectangle)
							pParameter->SetValue2f(fX, fY);

						// [TODO] For OpenGL only...
						else
							pParameter->SetValue2f(fX/m_pColorSurface->GetSize().x, fY/m_pColorSurface->GetSize().y);
					}

					// Next, please
					nKernel++;
				}
			} while (pParameter);

			// Set target dimension
			pParameter = pMaterial->GetParameter("TargetDimension");
			if (pParameter)
				pParameter->SetValue2f((float)m_pColorSurface->GetSize().x, (float)m_pColorSurface->GetSize().y);

			// Set dynamic source texture
			pParameter = pMaterial->GetParameter("SourceColor");
			if (pParameter) {
				Texture *pSourceTexture = m_cSourceColorTexture.GetResource();
				if (!pSourceTexture) {
					pSourceTexture = cRenderer.GetRendererContext().GetTextureManager().Create();
					m_cSourceColorTexture.SetResource(pSourceTexture);
				}
				if (pSourceTexture) {
					if (m_bFirstPostProcess) {
						pSourceTexture->SetTextureBuffer(m_pColorSurface->GetTextureBuffer());
						m_bFirstPostProcess = false;
					} else {
						pSourceTexture->SetTextureBuffer(m_pRenderTarget[!m_bCurrentRenderTarget]->GetTextureBuffer());
					}
					pParameter->SetValueTexture(pSourceTexture);
				}
			}

			// Set dynamic scene texture
			pParameter = pMaterial->GetParameter("SceneColor");
			if (pParameter) {
				Texture *pSceneTexture = m_cSceneColorTexture.GetResource();
				if (!pSceneTexture) {
					pSceneTexture = cRenderer.GetRendererContext().GetTextureManager().Create();
					m_cSceneColorTexture.SetResource(pSceneTexture);
				}
				if (pSceneTexture) {
					pSceneTexture->SetTextureBuffer(m_pColorSurface->GetTextureBuffer());
					pParameter->SetValueTexture(pSceneTexture);
				}
			}

			// If we scale down, clear the buffer to avoid possible artifacts at the corners
			if (m_bClearRenderTarget[m_bCurrentRenderTarget]) {
				cRenderer.Clear(Clear::Color, Color4::Black);
				m_bClearRenderTarget[m_bCurrentRenderTarget] = false;
			}

			// [TODO] For OpenGL only...
			// Set texture coordinate scale matrix
			Matrix4x4 mScale;
			if (nType == PLRenderer::Resource::TypeTextureBufferRectangle)
				mScale.SetScaleMatrix((float)m_pColorSurface->GetSize().x, (float)m_pColorSurface->GetSize().y, 1.0f);

			// Get the effect and set some general shader parameters
			Effect *pEffect = pMaterial->GetEffect();
			if (pEffect) {
				FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
				if (pFixedFunctions) {
					// WorldVP
					const Matrix4x4 &mProjection = pFixedFunctions->GetTransformState(FixedFunctions::Transform::Projection);
					const Matrix4x4 &mView		 = pFixedFunctions->GetTransformState(FixedFunctions::Transform::View);
					const Matrix4x4 &mWorld		 = pFixedFunctions->GetTransformState(FixedFunctions::Transform::World);
					pEffect->GetParameterManager().SetParameterMatrixfv("WorldVP", mProjection*mView*mWorld);
				}
			}

			// Loop through all material passes
			for (uint32 nPass=0; nPass<pMaterial->GetNumOfPasses(); nPass++) {
				// Setup pass
				pMaterial->SetupPass(nPass);

				// Set program attributes and uniforms
				Program *pProgram = cRenderer.GetProgram();
				if (pProgram) {
					// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
					// Position
					ProgramAttribute *pProgramAttribute = pProgram->GetAttribute("IN.pos");
					if (!pProgramAttribute)
						pProgramAttribute = pProgram->GetAttribute("Position");
					if (pProgramAttribute)
						pProgramAttribute->Set(m_pVertexBuffer, VertexBuffer::Position);
					// Texture coordinate 0
					pProgramAttribute = pProgram->GetAttribute("IN.texCoord0");
					if (!pProgramAttribute)
						pProgramAttribute = pProgram->GetAttribute("TexCoord0");
					if (pProgramAttribute)
						pProgramAttribute->Set(m_pVertexBuffer, VertexBuffer::TexCoord, 0);
					// Texture coordinate 1
					pProgramAttribute = pProgram->GetAttribute("IN.texCoord1");
					if (!pProgramAttribute)
						pProgramAttribute = pProgram->GetAttribute("TexCoord1");
					if (pProgramAttribute)
						pProgramAttribute->Set(m_pVertexBuffer, VertexBuffer::TexCoord, 1);

					// TextureMatrix
					ProgramUniform *pProgramUniform = pProgram->GetUniform("TextureMatrix");
					if (pProgramUniform)
						pProgramUniform->Set(mScale);
				}

				// Do NOT use mipmapping!
				for (uint32 i=0; i<cRenderer.GetCapabilities().nMaxTextureUnits; i++)
					cRenderer.SetSamplerState(i, Sampler::MipFilter, TextureFiltering::None);

				// Draw
				cRenderer.DrawPrimitives(Primitive::TriangleStrip, 0, 4);
			}

			// Swap current render target
			m_bCurrentRenderTarget = !m_bCurrentRenderTarget;

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

/**
*  @brief
*    Ends the processing
*/
bool PostProcessor::EndProcessing()
{
	// Processing currently active?
	if (m_bProcessing && m_pVertexBuffer) {
		Renderer &cRenderer = m_pVertexBuffer->GetRenderer();

		// End 2D mode
		cRenderer.GetDrawHelpers().End2DMode();

		// Restore the fixed fill mode render state
		cRenderer.SetRenderState(RenderState::FixedFillMode, m_nFixedFillModeBackup);

		// Stop processing
		m_bProcessing = false;

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

/**
*  @brief
*    Draws the result into the current render target
*/
bool PostProcessor::DrawResult(Renderer &cRenderer, float fX1, float fY1, float fX2, float fY2) const
{
	// Get the current texture buffer surface
	SurfaceTextureBuffer *pTextureBufferSurface = GetCurrentSurface();
	if (pTextureBufferSurface && pTextureBufferSurface->GetTextureBuffer()) {
		// Setup renderer
		const uint32 nFixedFillModeBackup = cRenderer.GetRenderState(RenderState::FixedFillMode);
		cRenderer.GetRendererContext().GetEffectManager().Use();
		cRenderer.SetRenderState(RenderState::FixedFillMode, Fill::Solid);
		cRenderer.SetRenderState(RenderState::CullMode,     Cull::None);
		cRenderer.SetRenderState(RenderState::ZEnable,      false);
		cRenderer.SetRenderState(RenderState::ZWriteEnable, false);

		// Begin 2D mode
		DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
		cDrawHelpers.Begin2DMode();

			// Draw the result (we have to flip the result upside-down...)
			SamplerStates cSamplerStates;
			cSamplerStates.Set(Sampler::MipFilter, TextureFiltering::None);
			cSamplerStates.Set(Sampler::MipFilter, TextureFiltering::None);
			cSamplerStates.Set(Sampler::MipFilter, TextureFiltering::None);
			cDrawHelpers.DrawImage(*pTextureBufferSurface->GetTextureBuffer(), cSamplerStates, Vector2::Zero, Vector2::One, Color4::White, 1.0f, Vector2(0.0f, 1.0f), Vector2(1.0f, -1.0f));

		// End 2D mode
		cDrawHelpers.End2DMode();

		// Restore fixed fill mode render state
		cRenderer.SetRenderState(RenderState::FixedFillMode, nFixedFillModeBackup);

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Returns the current texture buffer surface
*/
SurfaceTextureBuffer *PostProcessor::GetCurrentSurface() const
{
	return m_bFirstPostProcess ? m_pColorSurface : m_pRenderTarget[!m_bCurrentRenderTarget];
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
