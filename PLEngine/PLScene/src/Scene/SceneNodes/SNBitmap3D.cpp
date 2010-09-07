/*********************************************************\
 *  File: SNBitmap3D.cpp                                 *
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
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include "PLScene/Visibility/VisNode.h"
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNodes/SNBitmap3D.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNBitmap3D)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
const Vector3 &SNBitmap3D::GetPositionOffset() const
{
	return m_vPositionOffset;
}

void SNBitmap3D::SetPositionOffset(const Vector3 &vValue)
{
	if (m_vPositionOffset != vValue) {
		m_vPositionOffset = vValue;
		m_bUpdatePositionOffset = true;

		// We have to recalculate the current axis align bounding box in 'scene node space'
		DirtyAABoundingBox();
	}
}

void SNBitmap3D::SetColor(const Color4 &cValue)
{
	if (GetColor() != cValue) {
		// Call base implementation
		SNBitmap::SetColor(cValue);

		m_bUpdateColor = true;
	}
}

void SNBitmap3D::SetTexelStart(const Vector2 &vValue)
{
	if (GetTexelStart() != vValue) {
		// Call base implementation
		SNBitmap::SetTexelStart(vValue);

		m_bUpdateTextureCoordinates = true;
	}
}

void SNBitmap3D::SetTexelEnd(const Vector2 &vValue)
{
	if (GetTexelEnd() != vValue) {
		// Call base implementation
		SNBitmap::SetTexelEnd(vValue);

		m_bUpdateTextureCoordinates = true;
	}
}

void SNBitmap3D::SetFlags(uint32 nValue)
{
	if (GetFlags() != nValue) {
		// Call base implementation
		SNBitmap::SetFlags(nValue);

		// Destroy the old vertex buffer because the 'IgnoreColor'-flag may have changed
		if (m_pVertexBuffer) {
			delete m_pVertexBuffer;
			m_pVertexBuffer = NULL;
		}
		m_bUpdatePositionOffset		= true;
		m_bUpdateTextureCoordinates	= true;
		m_bUpdateColor				= true;
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNBitmap3D::SNBitmap3D() :
	PositionOffset(this),
	m_pIndexBuffer(NULL),
	m_pVertexBuffer(NULL),
	m_bUpdatePositionOffset(true),
	m_bUpdateTextureCoordinates(true),
	m_bUpdateColor(true)
{
	// Set draw function flags
	SetDrawFunctionFlags(uint8(GetDrawFunctionFlags() | UseDrawSolid | UseDrawTransparent));

	// We have to recalculate the current axis align bounding box in 'scene node space'
	DirtyAABoundingBox();
}

/**
*  @brief
*    Destructor
*/
SNBitmap3D::~SNBitmap3D()
{
	// Destroy index and vertex buffer
	if (m_pIndexBuffer)
		delete m_pIndexBuffer;
	if (m_pVertexBuffer)
		delete m_pVertexBuffer;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Create the bitmap shape
*/
void SNBitmap3D::CreateShape()
{
	// Setup the index buffer
	if (!m_pIndexBuffer) {
		m_pIndexBuffer = GetSceneContext()->GetRendererContext().GetRenderer().CreateIndexBuffer();
		if (m_pIndexBuffer) {
			m_pIndexBuffer->Allocate(6, Usage::Static, false);
			if (m_pIndexBuffer->Lock(Lock::WriteOnly)) {
				// Triangle 1
				m_pIndexBuffer->SetData(0, 2);
				m_pIndexBuffer->SetData(1, 1);
				m_pIndexBuffer->SetData(2, 0);

				// Triangle 2
				m_pIndexBuffer->SetData(3, 3);
				m_pIndexBuffer->SetData(4, 2);
				m_pIndexBuffer->SetData(5, 0);

				// Unlock the index buffer
				m_pIndexBuffer->Unlock();
			}
		}
	}

	// Setup the vertex buffer
	if (!m_pVertexBuffer) {
		m_pVertexBuffer = GetSceneContext()->GetRendererContext().GetRenderer().CreateVertexBuffer();
		if (m_pVertexBuffer) {
			m_pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
			m_pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
			if (!(GetFlags() & IgnoreColor))
				m_pVertexBuffer->AddVertexAttribute(VertexBuffer::Color, 0, VertexBuffer::RGBA);
			m_pVertexBuffer->Allocate(4, Usage::WriteOnly);
		}
	}
}

/**
*  @brief
*    Updates texture coordinates and color of the vertex buffer
*/
void SNBitmap3D::UpdateTextureCoordinatesAndColor()
{
	// Lock the vertex buffer
	if ((m_bUpdatePositionOffset || m_bUpdateTextureCoordinates || m_bUpdateColor) && m_pVertexBuffer->Lock(Lock::WriteOnly)) {
		// Update position offset?
		if (m_bUpdatePositionOffset) {
			// Fill position data
			float *pfVertex = (float*)m_pVertexBuffer->GetData(0, VertexBuffer::Position);
			if (pfVertex) {
				const uint32 nVertexSize = m_pVertexBuffer->GetVertexSize();

				// Top left
				pfVertex[0] = -0.5f + m_vPositionOffset.x;
				pfVertex[1] = -0.5f + m_vPositionOffset.y;
				pfVertex[2] =         m_vPositionOffset.z;
				pfVertex = (float*)((char*)pfVertex + nVertexSize);

				// Bottom left
				pfVertex[0] = -0.5f + m_vPositionOffset.x;
				pfVertex[1] =  0.5f + m_vPositionOffset.y;
				pfVertex[2] =         m_vPositionOffset.z;
				pfVertex = (float*)((char*)pfVertex + nVertexSize);

				// Bottom right
				pfVertex[0] =  0.5f + m_vPositionOffset.x;
				pfVertex[1] =  0.5f + m_vPositionOffset.y;
				pfVertex[2] =         m_vPositionOffset.z;
				pfVertex = (float*)((char*)pfVertex + nVertexSize);

				// Top right
				pfVertex[0] =  0.5f + m_vPositionOffset.x;
				pfVertex[1] = -0.5f + m_vPositionOffset.y;
				pfVertex[2] =         m_vPositionOffset.z;
			}

			// Done
			m_bUpdatePositionOffset = false;
		}

		// Update texture coordinates?
		if (m_bUpdateTextureCoordinates) {
			// Top left
			float *pfVertex = (float*)m_pVertexBuffer->GetData(0, VertexBuffer::TexCoord);
			pfVertex[0] = GetTexelStart().x;
			pfVertex[1] = GetTexelEnd().y;

			// Top right
			pfVertex = (float*)m_pVertexBuffer->GetData(1, VertexBuffer::TexCoord);
			pfVertex[0] = GetTexelStart().x;
			pfVertex[1] = GetTexelStart().y;

			// Bottom right
			pfVertex = (float*)m_pVertexBuffer->GetData(2, VertexBuffer::TexCoord);
			pfVertex[0] = GetTexelEnd().x;
			pfVertex[1] = GetTexelStart().y;

			// Bottom left
			pfVertex = (float*)m_pVertexBuffer->GetData(3, VertexBuffer::TexCoord);
			pfVertex[0] = GetTexelEnd().x;
			pfVertex[1] = GetTexelEnd().y;

			// Done
			m_bUpdateTextureCoordinates = false;
		}

		// Update color?
		if (m_bUpdateColor) {
			if (!(GetFlags() & IgnoreColor)) {
				m_pVertexBuffer->SetColor(0, GetColor());
				m_pVertexBuffer->SetColor(1, GetColor());
				m_pVertexBuffer->SetColor(2, GetColor());
				m_pVertexBuffer->SetColor(3, GetColor());
			}

			// Done
			m_bUpdateColor = false;
		}

		// Unlock the vertex buffer
		m_pVertexBuffer->Unlock();
	}
}

/**
*  @brief
*    Draws the bitmap shape
*/
void SNBitmap3D::DrawShape(Renderer &cRenderer, const VisNode &cVisNode)
{
	// Get material
	PLRenderer::Material *pMaterial = GetMaterialHandler().GetResource();
	if (pMaterial) {
		// Create shape - we have to recreate it each time because it's camera dependent
		CreateShape();

		// Check index and vertex buffer
		if (m_pIndexBuffer && m_pVertexBuffer) {
			// Update texture coordinates and color of the vertex buffer (if required)
			UpdateTextureCoordinatesAndColor();

			// Bind buffers
			cRenderer.SetIndexBuffer(m_pIndexBuffer);

			// Draw primitives
			for (uint32 nPass=0; nPass<pMaterial->GetNumOfPasses(); nPass++) {
				pMaterial->SetupPass(nPass);
				// [TODO] Remove FixedFunctions usage by using the new shader interface
				FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
				if (pFixedFunctions) {
					pFixedFunctions->SetVertexBuffer(m_pVertexBuffer);

					// Set world matrix
					pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, cVisNode.GetWorldMatrix());
				}
				cRenderer.DrawIndexedPrimitives(Primitive::TriangleList, 0, 3, 0, 6);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Public virtual SceneNode functions                    ]
//[-------------------------------------------------------]
void SNBitmap3D::DrawSolid(Renderer &cRenderer, const VisNode *pVisNode)
{
	if (pVisNode) {
		// Check if the bitmap material is transparent or not
		PLRenderer::Material *pMaterial = GetMaterialHandler().GetResource();
		if (pMaterial && !pMaterial->GetBlend()) {
			// Call base implementation
			SNBitmap::DrawSolid(cRenderer, pVisNode);

			// Mark this scene node as drawn
			SetDrawn();

			// Draw the bitmap shape
			DrawShape(cRenderer, *pVisNode);
		}
	}
}

void SNBitmap3D::DrawTransparent(Renderer &cRenderer, const VisNode *pVisNode)
{
	if (pVisNode) {
		// Check if the bitmap material is transparent or not
		PLRenderer::Material *pMaterial = GetMaterialHandler().GetResource();
		if (pMaterial && pMaterial->GetBlend()) {
			// Call base implementation
			SNBitmap::DrawTransparent(cRenderer, pVisNode);

			// Mark this scene node as drawn
			SetDrawn();

			// Draw the bitmap shape
			DrawShape(cRenderer, *pVisNode);
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual SceneNode functions                   ]
//[-------------------------------------------------------]
void SNBitmap3D::UpdateAABoundingBox()
{
	SetAABoundingBox(AABoundingBox(-0.5f+m_vPositionOffset.x, -0.5f+m_vPositionOffset.y, -0.5f+m_vPositionOffset.z,
									0.5f+m_vPositionOffset.x,  0.5f+m_vPositionOffset.y,  0.5f+m_vPositionOffset.z));
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
