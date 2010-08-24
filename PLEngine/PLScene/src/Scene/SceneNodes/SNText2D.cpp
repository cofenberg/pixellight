/*********************************************************\
 *  File: SNText2D.cpp                                   *
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
#include <PLRenderer/Renderer/Font.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Renderer/FontManager.h>
#include <PLRenderer/Effect/EffectManager.h>
#include "PLScene/Visibility/VisNode.h"
#include "PLScene/Scene/SceneNodes/SNText2D.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNText2D)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNText2D::SNText2D() :
	Flags(this)
{
	// Set draw function flags
	SetDrawFunctionFlags(uint8(GetDrawFunctionFlags() | UseDrawPost));
}

/**
*  @brief
*    Destructor
*/
SNText2D::~SNText2D()
{
}


//[-------------------------------------------------------]
//[ Public virtual SceneNode functions                    ]
//[-------------------------------------------------------]
void SNText2D::DrawPost(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Call base implementation
	SNText::DrawPost(cRenderer, pVisNode);

	// Is there any text to draw?
	if (((GetFlags() & No3DPosition) || pVisNode) && Text.Get().GetLength()) {
		// Get the font
		const PLRenderer::Font *pDefaultFont = (PLRenderer::Font*)cRenderer.GetFontManager().GetDefaultFontTexture();
		const String			sFont        = (GetFont().GetLength() || !pDefaultFont) ? GetFont() : pDefaultFont->GetFilename();
		const uint32			nFontSize    = (FontSize || !pDefaultFont) ? FontSize : pDefaultFont->GetSize();
			  PLRenderer::Font *pFont        = (PLRenderer::Font*)cRenderer.GetFontManager().GetFontTexture(sFont, nFontSize);
		if (pFont) {
			// Get the full dynamic scale
			const Vector3 &vScale = GetTransform().GetScale();
			const float fScale = vScale.x*vScale.y*vScale.z;

			// Setup render states
			cRenderer.GetRendererContext().GetEffectManager().Use();
			cRenderer.SetRenderState(RenderState::ZEnable,      false);
			cRenderer.SetRenderState(RenderState::ZWriteEnable, false);

			// Get font draw flags
			uint32 nFlags = 0;
			if (!(GetFlags() & NoCenter))
				nFlags |= Font::CenterText;
			// [TODO] Update SNText flags
			// UnderlineText = 1<<1,	/**< Underline the text */
			// CrossoutText  = 1<<2	/**< Cross out the text */

			// 3D position or screen space position?
			if (GetFlags() & No3DPosition) {
				// Begin 2D mode
				DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
				cDrawHelpers.Begin2DMode();

					// Draw the text
					cDrawHelpers.DrawText(*pFont, Text.Get(), Color.Get(), GetTransform().GetPosition(), nFlags, Vector2(fScale, fScale));

				// End 2D mode
				cDrawHelpers.End2DMode();
			} else {
				// Draw the text
				cRenderer.GetDrawHelpers().DrawText(*pFont, Text.Get(), Color.Get(), Vector3::Zero, pVisNode->GetWorldViewProjectionMatrix(), (GetFlags() & NoCenter) ? 0 : Font::CenterText, Vector2(fScale, fScale));
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
