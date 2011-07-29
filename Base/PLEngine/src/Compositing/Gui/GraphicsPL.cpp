/*********************************************************\
 *  File: GraphicsPL.cpp                                 *
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
#include <PLGui/Gui/Resources/Font.h>
#include <PLGui/Gui/Resources/Image.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Renderer/SamplerStates.h>
#include "PLEngine/Compositing/Gui/FontPL.h"
#include "PLEngine/Compositing/Gui/ImagePL.h"
#include "PLEngine/Compositing/Gui/GraphicsPL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLGui;
using namespace PLRenderer;
namespace PLEngine {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
GraphicsPL::GraphicsPL(Renderer &cRenderer, const Vector2i &vAbsPos, const Vector2i &vScreenSize, ETransparency nTransparency, const Color4 &cTransparencyColor) : GraphicsImpl(),
	m_pRenderer(&cRenderer),
	m_vAbsPos(vAbsPos),
	m_vScreenSize(vScreenSize),
	m_nTransparency(nTransparency),
	m_cTransparencyColor(cTransparencyColor)
{
}

/**
*  @brief
*    Constructor
*/
GraphicsPL::GraphicsPL(Graphics &cGraphics, Renderer &cRenderer, const Vector2i &vAbsPos, ETransparency nTransparency, const Color4 &cTransparencyColor) : GraphicsImpl(cGraphics),
	m_pRenderer(&cRenderer),
	m_vAbsPos(vAbsPos),
	m_nTransparency(nTransparency),
	m_cTransparencyColor(cTransparencyColor)
{
}

/**
*  @brief
*    Destructor
*/
GraphicsPL::~GraphicsPL()
{
}


//[-------------------------------------------------------]
//[ Public virtual GraphicsImpl functions                 ]
//[-------------------------------------------------------]
void GraphicsPL::DrawLine(const Color4 &cColor, const Vector2i &vPos1, const Vector2i &vPos2, uint32 nWidth)
{
	// Get final color to use
	Color4 cFinalColor = cColor;
	if (m_nTransparency == AlphaTransparency)
		cFinalColor.a *= m_cTransparencyColor.a;

	// Setup renderer
	m_pRenderer->SetTextureBuffer();
	const bool bBlendEnable = (cFinalColor.a < 1.0f);
	m_pRenderer->SetRenderState(RenderState::BlendEnable, bBlendEnable);
	if (bBlendEnable) {
		m_pRenderer->SetRenderState(RenderState::SrcBlendFunc, BlendFunc::SrcAlpha);
		m_pRenderer->SetRenderState(RenderState::DstBlendFunc, BlendFunc::InvSrcAlpha);
	}

	// Draw line
	m_pRenderer->GetDrawHelpers().DrawLine(cFinalColor, Vector2(static_cast<float>(vPos1.x) + m_vAbsPos.x, static_cast<float>(vPos1.y) + m_vAbsPos.y),
														Vector2(static_cast<float>(vPos2.x) + m_vAbsPos.x, static_cast<float>(vPos2.y) + m_vAbsPos.y), static_cast<float>(nWidth));
}

void GraphicsPL::DrawRect(const Color4 &cColor, const Vector2i &vPos1, const Vector2i &vPos2, uint32 nRoundX, uint32 nRoundY, uint32 nWidth)
{
	// Get final color to use
	Color4 cFinalColor = cColor;
	if (m_nTransparency == AlphaTransparency)
		cFinalColor.a *= m_cTransparencyColor.a;

	// nRoundX and nRoundY are not supported

	// Setup renderer
	m_pRenderer->SetTextureBuffer();
	const bool bBlendEnable = (cFinalColor.a < 1.0f);
	m_pRenderer->SetRenderState(RenderState::BlendEnable, bBlendEnable);
	if (bBlendEnable) {
		m_pRenderer->SetRenderState(RenderState::SrcBlendFunc, BlendFunc::SrcAlpha);
		m_pRenderer->SetRenderState(RenderState::DstBlendFunc, BlendFunc::InvSrcAlpha);
	}

	// Draw line
	m_pRenderer->GetDrawHelpers().DrawQuad(cFinalColor, Vector2(static_cast<float>(vPos1.x) + m_vAbsPos.x, static_cast<float>(vPos1.y) + m_vAbsPos.y),
														Vector2(static_cast<float>(vPos2.x - vPos1.x), static_cast<float>(vPos2.y - vPos1.y)), static_cast<float>(nWidth));
}

void GraphicsPL::DrawBox(const Color4 &cColor, const Vector2i &vPos1, const Vector2i &vPos2, uint32 nRoundX, uint32 nRoundY)
{
	// Get final color to use
	Color4 cFinalColor = cColor;
	if (m_nTransparency == AlphaTransparency)
		cFinalColor.a *= m_cTransparencyColor.a;

	// nRoundX and nRoundY are not supported

	// Setup renderer
	m_pRenderer->SetTextureBuffer();
	const bool bBlendEnable = (cFinalColor.a < 1.0f);
	m_pRenderer->SetRenderState(RenderState::BlendEnable, bBlendEnable);
	if (bBlendEnable) {
		m_pRenderer->SetRenderState(RenderState::SrcBlendFunc, BlendFunc::SrcAlpha);
		m_pRenderer->SetRenderState(RenderState::DstBlendFunc, BlendFunc::InvSrcAlpha);
	}

	// Draw line
	m_pRenderer->GetDrawHelpers().DrawQuad(cFinalColor, Vector2(static_cast<float>(vPos1.x) + m_vAbsPos.x, static_cast<float>(vPos1.y) + m_vAbsPos.y),
														Vector2(static_cast<float>(vPos2.x - vPos1.x), static_cast<float>(vPos2.y - vPos1.y)), 0.0f);
}

void GraphicsPL::DrawGradientBox(const Color4 &cColor1, const Color4 &cColor2, float fAngle, const Vector2i &vPos1, const Vector2i &vPos2)
{
	// [TODO] Implement me
}

void GraphicsPL::DrawImage(const PLGui::Image &cImage, const Vector2i &vPos, const Vector2i &vSize)
{
	// cImage must be an instance of PLEngine::ImagePL!
	ImagePL *pImagePL = static_cast<ImagePL*>(cImage.GetImpl());
	if (pImagePL) {
		// Get the texture buffer
		TextureBuffer *pTextureBuffer = pImagePL->GetTextureBuffer();
		if (pTextureBuffer) {
			// Get final color to use
			Color4 cFinalColor = Color4::White;
			if (m_nTransparency == AlphaTransparency)
				cFinalColor.a *= m_cTransparencyColor.a;

			// Setup renderer
			const bool bBlendEnable = ((pTextureBuffer->GetComponentsPerPixel() == 4) || (m_nTransparency == AlphaTransparency));
			m_pRenderer->SetRenderState(RenderState::BlendEnable, bBlendEnable);
			if (bBlendEnable) {
				m_pRenderer->SetRenderState(RenderState::SrcBlendFunc, BlendFunc::SrcAlpha);
				m_pRenderer->SetRenderState(RenderState::DstBlendFunc, BlendFunc::InvSrcAlpha);
			}

			// Draw
			SamplerStates cSamplerStates;
			m_pRenderer->GetDrawHelpers().DrawImage(*pTextureBuffer, cSamplerStates, Vector2(static_cast<float>(vPos.x) + m_vAbsPos.x, static_cast<float>(vPos.y) + m_vAbsPos.y),
													 Vector2(static_cast<float>(vSize.x), static_cast<float>(vSize.y)), cFinalColor);
		}
	}
}

void GraphicsPL::DrawText(const PLGui::Font &cFont, const Color4 &cTextColor, const Color4 &cBkColor, const Vector2i &vPos, const String &sText)
{
	// cFont must be an instance of PLEngine::FontPL!
	FontPL *pFontPL = static_cast<FontPL*>(cFont.GetImpl());
	if (pFontPL) {
		// Get the renderer font
		PLRenderer::Font *pRendererFont = pFontPL->GetRendererFont();
		if (pRendererFont) {
			// Draw background?
			if (!cBkColor.IsTransparent()) {
				// Get final background color to use
				Color4 cFinalBkColor = cBkColor;
				if (m_nTransparency == AlphaTransparency)
					cFinalBkColor.a *= m_cTransparencyColor.a;

				// Draw
				const uint32 nTextWidth  = GetTextWidth (cFont, sText);
				const uint32 nTextHeight = GetTextHeight(cFont, sText);
				DrawBox(cFinalBkColor, vPos, Vector2i(vPos.x + nTextWidth, vPos.y + nTextHeight));
			}

			// Get final text color to use
			Color4 cFinalTextColor = cTextColor;
			if (m_nTransparency == AlphaTransparency)
				cFinalTextColor.a *= m_cTransparencyColor.a;

			// Draw text
			m_pRenderer->GetDrawHelpers().DrawText(*pRendererFont, sText, cFinalTextColor, Vector2(static_cast<float>(vPos.x) + m_vAbsPos.x, static_cast<float>(vPos.y) + m_vAbsPos.y));
		}
	}
}

uint32 GraphicsPL::GetTextWidth(const PLGui::Font &cFont, const String &sText)
{
	// cFont must be an instance of PLEngine::FontPL!
	FontPL *pFontPL = static_cast<FontPL*>(cFont.GetImpl());
	if (pFontPL) {
		// Get the renderer font
		PLRenderer::Font *pRendererFont = pFontPL->GetRendererFont();
		if (pRendererFont)
			return static_cast<uint32>(m_pRenderer->GetDrawHelpers().GetTextWidth(*pRendererFont, sText)*m_vScreenSize.x);
	}

	// Error!
	return 0;
}

uint32 GraphicsPL::GetTextHeight(const PLGui::Font &cFont, const String &sText)
{
	// cFont must be an instance of PLEngine::FontPL!
	FontPL *pFontPL = static_cast<FontPL*>(cFont.GetImpl());
	if (pFontPL) {
		// Get the renderer font
		PLRenderer::Font *pRendererFont = pFontPL->GetRendererFont();
		if (pRendererFont)
			return static_cast<uint32>(m_pRenderer->GetDrawHelpers().GetTextHeight(*pRendererFont)*m_vScreenSize.y);	// sText is not required
	}

	// Error!
	return 0;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
