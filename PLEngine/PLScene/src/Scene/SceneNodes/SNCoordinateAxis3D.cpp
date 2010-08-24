/*********************************************************\
 *  File: SNCoordinateAxis3D.cpp                         *
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
#include <PLRenderer/Renderer/FontManager.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Effect/EffectManager.h>
#include "PLScene/Visibility/VisNode.h"
#include "PLScene/Scene/SceneNodes/SNCoordinateAxis3D.h"


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
pl_implement_class(SNCoordinateAxis3D)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNCoordinateAxis3D::SNCoordinateAxis3D() :
	AABBMax(this)
{
	// Overwritten SceneNode variables
	SetAABoundingBox(AABoundingBox(Vector3::Zero, Vector3::One));

	// Set draw function flags
	SetDrawFunctionFlags(uint8(GetDrawFunctionFlags() | UseDrawPost));
}

/**
*  @brief
*    Destructor
*/
SNCoordinateAxis3D::~SNCoordinateAxis3D()
{
}


//[-------------------------------------------------------]
//[ Public virtual SceneNode functions                    ]
//[-------------------------------------------------------]
void SNCoordinateAxis3D::DrawPost(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Call base implementation
	SNCoordinateAxis::DrawPost(cRenderer, pVisNode);

	// There must be a visibility node
	if (pVisNode) {
		// Setup render states
		cRenderer.GetRendererContext().GetEffectManager().Use();
		if (!(GetFlags() & DepthTest)) {
			cRenderer.SetRenderState(RenderState::ZEnable,      false);
			cRenderer.SetRenderState(RenderState::ZWriteEnable, false);
		}

		// Draw coordinate axis at the origin of the system
		DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
		cDrawHelpers.DrawLine(XColor.Get(), Vector3::Zero, Vector3::UnitX, pVisNode->GetWorldViewProjectionMatrix(), Width);
		cDrawHelpers.DrawLine(YColor.Get(), Vector3::Zero, Vector3::UnitY, pVisNode->GetWorldViewProjectionMatrix(), Width);
		cDrawHelpers.DrawLine(ZColor.Get(), Vector3::Zero, Vector3::UnitZ, pVisNode->GetWorldViewProjectionMatrix(), Width);

		// Draw texts
		Font *pFont = NULL;
		if (!(GetFlags() & NoXText) || !(GetFlags() & NoYText) || !(GetFlags() & NoZText)) {
			pFont = (Font*)cRenderer.GetFontManager().GetDefaultFontTexture();
			if (GetFlags() & DepthTest) {
				cRenderer.SetRenderState(RenderState::ZEnable,      true);
				cRenderer.SetRenderState(RenderState::ZWriteEnable, false);
			} else {
				cRenderer.SetRenderState(RenderState::ZEnable,      false);
				cRenderer.SetRenderState(RenderState::ZWriteEnable, false);
			}
		}
		if (pFont) {
			// X-axis
			if (!(GetFlags() & NoXText))
				cDrawHelpers.DrawText(*pFont, (GetTransform().GetScale().x >= 0.0f) ? "X" : "-X", XColor.Get(), Vector3::UnitX, pVisNode->GetWorldViewProjectionMatrix(), Font::CenterText);
			// Y-axis
			if (!(GetFlags() & NoYText))
				cDrawHelpers.DrawText(*pFont, (GetTransform().GetScale().y >= 0.0f) ? "Y" : "-Y", YColor.Get(), Vector3::UnitY, pVisNode->GetWorldViewProjectionMatrix(), Font::CenterText);
			// Z-axis
			if (!(GetFlags() & NoZText))
				cDrawHelpers.DrawText(*pFont, (GetTransform().GetScale().z >= 0.0f) ? "Z" : "-Z", ZColor.Get(), Vector3::UnitZ, pVisNode->GetWorldViewProjectionMatrix(), Font::CenterText);
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
