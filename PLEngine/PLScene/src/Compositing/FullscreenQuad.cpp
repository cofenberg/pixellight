/*********************************************************\
 *  File: FullscreenQuad.cpp                             *
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
#include <PLGeneral/File/File.h>
#include <PLGeneral/Tools/Wrapper.h>
#include <PLMath/Vector4.h>
#include <PLMath/Vector2i.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/ShaderProgram.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include "PLScene/Compositing/FullscreenQuad.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FullscreenQuad::FullscreenQuad(Renderer &cRenderer) :
	m_pRenderer(&cRenderer),
	m_pVertexBuffer(NULL)
{
	// Init shader handler data
	MemoryManager::Set(m_bVertexShader, 0, sizeof(m_bVertexShader));
}

/**
*  @brief
*    Destructor
*/
FullscreenQuad::~FullscreenQuad()
{
	// Destroy the vertex buffer
	if (m_pVertexBuffer)
		delete m_pVertexBuffer;

	// Destroy the vertex shader
	if (m_cVertexShader[0].GetResource())
		delete m_cVertexShader[0].GetResource();
	if (m_cVertexShader[1].GetResource())
		delete m_cVertexShader[1].GetResource();
}

/**
*  @brief
*    Returns the vertex buffer of this fullscreen quad
*/
VertexBuffer *FullscreenQuad::GetVertexBuffer()
{
	// Initialize vertex buffer
	if (!m_pVertexBuffer) {
		// Create the vertex buffer
		m_pVertexBuffer = m_pRenderer->CreateVertexBuffer();

		// Add vertex position attribute to the vertex buffer, zw stores the texture coordinate
		m_pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float4);

		// Allocate
		m_pVertexBuffer->Allocate(4);

		// Fill
		if (m_pVertexBuffer->Lock(Lock::WriteOnly)) {
		// Vertex 0 - lower/left corner
			// Position
			float *pfVertex = (float*)m_pVertexBuffer->GetData(0, VertexBuffer::Position);
			pfVertex[Vector4::X] = -1.0f;
			pfVertex[Vector4::Y] = -1.0f;
			// Texture coordinate
			pfVertex[Vector4::Z] =  0.0f;
			pfVertex[Vector4::W] =  0.0f;

		// Vertex 1 - lower/right corner
			// Position
			pfVertex = (float*)m_pVertexBuffer->GetData(1, VertexBuffer::Position);
			pfVertex[Vector4::X] =  1.0f;
			pfVertex[Vector4::Y] = -1.0f;
			// Texture coordinate
			pfVertex[Vector4::Z] =  1.0f;
			pfVertex[Vector4::W] =  0.0f;

		// Vertex 2 - upper/left corner
			// Position
			pfVertex = (float*)m_pVertexBuffer->GetData(2, VertexBuffer::Position);
			pfVertex[Vector4::X] = -1.0f;
			pfVertex[Vector4::Y] =  1.0f;
			// Texture coordinate
			pfVertex[Vector4::Z] =  0.0f;
			pfVertex[Vector4::W] =  1.0f;

		// Vertex 3 - upper/right corner
			// Position
			pfVertex = (float*)m_pVertexBuffer->GetData(3, VertexBuffer::Position);
			pfVertex[Vector4::X] = 1.0f;
			pfVertex[Vector4::Y] = 1.0f;
			// Texture coordinate
			pfVertex[Vector4::Z] = 1.0f;
			pfVertex[Vector4::W] = 1.0f;

			// Unlock the vertex buffer
			m_pVertexBuffer->Unlock();
		}
	}

	// Return the vertex buffer
	return m_pVertexBuffer;
}

/**
*  @brief
*    Returns the vertex shader of this fullscreen quad
*/
Shader *FullscreenQuad::GetVertexShader(bool bSizeContol)
{
	// Get/construct the shader
	Shader *pShader = m_cVertexShader[bSizeContol].GetResource();
	if (!pShader && !m_bVertexShader[bSizeContol]) {
		const static String ShaderFilename = "Vertex/FullscreenQuad.cg";

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		if (bSizeContol) {
			sDefines += "#define SIZE_CONTROL\n";
			sName    += "[SizeContol]";
		}

		{ // Load the shader
			#include "FullscreenQuad_VertexShader.h"
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszFullscreenQuad_VertexShader) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszFullscreenQuad_VertexShader, nNumOfBytes, false, ".cg");
			pShader = m_pRenderer->GetRendererContext().GetShaderManager().Load(sName, cFile, false, "arbvp1", sDefines);
		}
		m_cVertexShader[bSizeContol].SetResource(pShader);
		m_bVertexShader[bSizeContol] = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Draws the fullscreen quad
*/
void FullscreenQuad::Draw(const Vector2i &vTextureSize, const Vector2i &vSize)
{
	// Make the vertex buffer of this fullscreen quad to the current one
	VertexBuffer *pVertexBuffer = GetVertexBuffer();
	if (pVertexBuffer) {
		// [TODO] Remove FixedFunctions usage by using the new shader interface
		FixedFunctions *pFixedFunctions = m_pRenderer->GetFixedFunctions();
		if (pFixedFunctions)
			pFixedFunctions->SetVertexBuffer(pVertexBuffer);

		// Size control?
		const bool bSizeContol = (vSize.x > 0 && vSize.y > 0);

		// Get and set the vertex shader
		Shader *pVertexShader = GetVertexShader(bSizeContol);
		if (pVertexShader && pVertexShader->GetShaderProgram()) {
			// Get and set the vertex shader program
			ShaderProgram *pVertexShaderProgram = pVertexShader->GetShaderProgram();
			m_pRenderer->SetVertexShaderProgram(pVertexShaderProgram);

			// Set the "Size" vertex shader parameter
			if (bSizeContol) {
				// Calculate the size [0..1]
				float fSizeX = float(vSize.x)/m_pRenderer->GetRenderTarget()->GetSize().x;
				float fSizeY = float(vSize.y)/m_pRenderer->GetRenderTarget()->GetSize().y;

				// Set the parameter
				static const String sSize = "Size";
				pVertexShaderProgram->SetParameter2f(sSize, fSizeX, fSizeY);
			}

			{ // Set the "TextureSize" vertex shader parameter
				static const String sTextureSize = "TextureSize";
				pVertexShaderProgram->SetParameter2iv(sTextureSize, vTextureSize);
			}

			// Setup renderer
			const uint32 nFixedFillModeBackup = m_pRenderer->GetRenderState(RenderState::FixedFillMode);
			m_pRenderer->SetRenderState(RenderState::ScissorTestEnable,	false);
			m_pRenderer->SetRenderState(RenderState::FixedFillMode,		Fill::Solid);
			m_pRenderer->SetRenderState(RenderState::CullMode,			Cull::None);
			m_pRenderer->SetRenderState(RenderState::ZEnable,			false);
			m_pRenderer->SetRenderState(RenderState::ZWriteEnable,		false);

			// Draw the fullscreen quad
			m_pRenderer->DrawPrimitives(Primitive::TriangleStrip, 0, 4);

			// Restore fixed fill mode render state
			m_pRenderer->SetRenderState(RenderState::FixedFillMode, nFixedFillModeBackup);
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
