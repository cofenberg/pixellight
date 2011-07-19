/*********************************************************\
 *  File: SNLine.cpp                                     *
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
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Effect/EffectManager.h>
#include "PLScene/Visibility/VisNode.h"
#include "PLScene/Scene/SceneNodes/SNLine.h"


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
pl_implement_class(SNLine)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
const Vector3 &SNLine::GetStartPosition() const
{
	return m_vStartPosition;
}

void SNLine::SetStartPosition(const Vector3 &vValue)
{
	if (m_vStartPosition != vValue) {
		m_vStartPosition = vValue;

		// We have to recalculate the current axis align bounding box in 'scene node space'
		DirtyAABoundingBox();
	}
}

const Vector3 &SNLine::GetEndPosition() const
{
	return m_vEndPosition;
}

void SNLine::SetEndPosition(const Vector3 &vValue)
{
	if (m_vEndPosition != vValue) {
		m_vEndPosition = vValue;

		// We have to recalculate the current axis align bounding box in 'scene node space'
		DirtyAABoundingBox();
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNLine::SNLine() :
	StartPosition(this),
	EndPosition(this),
	Width(this),
	Color(this),
	Flags(this),
	m_vEndPosition(0.0f, 0.0f, 1.0f)
{
	// Set draw function flags
	SetDrawFunctionFlags(static_cast<uint8>(GetDrawFunctionFlags() | UseDrawSolid | UseDrawTransparent));

	// We have to recalculate the current axis align bounding box in 'scene node space'
	DirtyAABoundingBox();
}

/**
*  @brief
*    Destructor
*/
SNLine::~SNLine()
{
}


//[-------------------------------------------------------]
//[ Public virtual SceneNode functions                    ]
//[-------------------------------------------------------]
void SNLine::DrawSolid(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Transparent?
	if (Color.Get().a == 1.0f) {
		// Call base implementation
		SceneNode::DrawSolid(cRenderer, pVisNode);

		// Draw the line
		cRenderer.GetRendererContext().GetEffectManager().Use();
		cRenderer.SetRenderState(RenderState::ZEnable, !(GetFlags() & NoDepthTest));

		// 3D position or screen space position?
		DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
		if (GetFlags() & No3DPosition) {
			// Begin 2D mode
			cDrawHelpers.Begin2DMode();

				// Draw the line
				cDrawHelpers.DrawLine(Color.Get(), m_vStartPosition, m_vEndPosition, Width);

			// End 2D mode
			cDrawHelpers.End2DMode();
		} else {
			// Draw the line
			cDrawHelpers.DrawLine(Color.Get(), m_vStartPosition, m_vEndPosition, pVisNode->GetWorldViewProjectionMatrix(), Width);
		}
	}
}

void SNLine::DrawTransparent(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Transparent?
	if (Color.Get().a != 1.0f) {
		// Call base implementation
		SceneNode::DrawTransparent(cRenderer, pVisNode);

		// Draw the line
		cRenderer.GetRendererContext().GetEffectManager().Use();
		cRenderer.SetRenderState(RenderState::ZEnable,      !(GetFlags() & NoDepthTest));
		cRenderer.SetRenderState(RenderState::ZWriteEnable, false);
		cRenderer.SetRenderState(RenderState::BlendEnable,  true);

		// 3D position or screen space position?
		DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
		if (GetFlags() & No3DPosition) {
			// Begin 2D mode
			cDrawHelpers.Begin2DMode();

				// Draw the line
				cDrawHelpers.DrawLine(Color.Get(), m_vStartPosition, m_vEndPosition, Width);

			// End 2D mode
			cDrawHelpers.End2DMode();
		} else {
			// Draw the line
			cDrawHelpers.DrawLine(Color.Get(), m_vStartPosition, m_vEndPosition, pVisNode->GetWorldViewProjectionMatrix(), Width);
		}
	}
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNode functions                 ]
//[-------------------------------------------------------]
void SNLine::UpdateAABoundingBox()
{
	const Vector3 vPos[2] = { m_vStartPosition, m_vEndPosition };
	Vector3 vMin = vPos[0];
	Vector3 vMax = vPos[0];
	for (int i=0; i<2; i++) {
		for (int j=0; j<3; j++) {
			const Vector3 &vT = vPos[i];
			if (vMin[j] > vT[j])
				vMin[j] = vT[j];
			if (vMax[j] < vT[j])
				vMax[j] = vT[j];
		}
	}
	SetAABoundingBox(AABoundingBox(vMin, vMax));
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
