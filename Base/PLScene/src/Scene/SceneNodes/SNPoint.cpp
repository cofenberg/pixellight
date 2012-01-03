/*********************************************************\
 *  File: SNPoint.cpp                                    *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Effect/EffectManager.h>
#include "PLScene/Visibility/VisNode.h"
#include "PLScene/Scene/SceneNodes/SNPoint.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNPoint)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNPoint::SNPoint() :
	Size(this),
	Color(this),
	Flags(this)
{
	// Set draw function flags
	SetDrawFunctionFlags(static_cast<uint8>(GetDrawFunctionFlags() | UseDrawSolid | UseDrawTransparent));
}

/**
*  @brief
*    Destructor
*/
SNPoint::~SNPoint()
{
}


//[-------------------------------------------------------]
//[ Public virtual SceneNode functions                    ]
//[-------------------------------------------------------]
void SNPoint::DrawSolid(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Perform depth test?
	if (!(GetFlags() & NoDepthTest)) {
		// Call base implementation
		SceneNode::DrawSolid(cRenderer, pVisNode);

		// Draw the point
		cRenderer.GetRendererContext().GetEffectManager().Use();
		cRenderer.SetRenderState(RenderState::BlendEnable, Color.Get().a != 1.0f);

		// 3D position or screen space position?
		DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
		if (GetFlags() & No3DPosition) {
			// Begin 2D mode
			cDrawHelpers.Begin2DMode();

				// Draw the point
				cDrawHelpers.DrawPoint(Color.Get(), GetTransform().GetPosition(), Size);

			// End 2D mode
			cDrawHelpers.End2DMode();
		} else {
			// Draw the point
			cDrawHelpers.DrawPoint(Color.Get(), Vector3::Zero, pVisNode->GetWorldViewProjectionMatrix(), Size);
		}
	}
}

void SNPoint::DrawTransparent(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Perform depth test?
	if (GetFlags() & NoDepthTest) {
		// Call base implementation
		SceneNode::DrawTransparent(cRenderer, pVisNode);

		// Draw the point
		cRenderer.GetRendererContext().GetEffectManager().Use();
		cRenderer.SetRenderState(RenderState::ZEnable,      false);
		cRenderer.SetRenderState(RenderState::ZWriteEnable, false);
		cRenderer.SetRenderState(RenderState::BlendEnable,  Color.Get().a != 1.0f);

		// 3D position or screen space position?
		DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
		if (GetFlags() & No3DPosition) {
			// Begin 2D mode
			cDrawHelpers.Begin2DMode();

				// Draw the point
				cDrawHelpers.DrawPoint(Color.Get(), GetTransform().GetPosition(), Size);

			// End 2D mode
			cDrawHelpers.End2DMode();
		} else {
			// Draw the point
			cDrawHelpers.DrawPoint(Color.Get(), Vector3::Zero, pVisNode->GetWorldViewProjectionMatrix(), Size);
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
