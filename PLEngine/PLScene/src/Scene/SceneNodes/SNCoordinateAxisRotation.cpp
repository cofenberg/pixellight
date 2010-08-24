/*********************************************************\
 *  File: SNCoordinateAxisRotation.cpp                   *
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
#include <PLMath/Matrix4x4.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/Font.h>
#include <PLRenderer/Renderer/FontManager.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Effect/EffectManager.h>
#include "PLScene/Visibility/VisNode.h"
#include "PLScene/Scene/SNCamera.h"
#include "PLScene/Scene/SceneNodes/SNCoordinateAxisRotation.h"


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
pl_implement_class(SNCoordinateAxisRotation)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNCoordinateAxisRotation::SNCoordinateAxisRotation() :
	Flags(this)
{
	// Overwrite the default setting of the flags
	SetFlags(GetFlags()|NoCulling);

	// Set draw function flags, we ONLY want to use the post draw function!
	SetDrawFunctionFlags(uint8(UseDrawPost));
}

/**
*  @brief
*    Destructor
*/
SNCoordinateAxisRotation::~SNCoordinateAxisRotation()
{
}


//[-------------------------------------------------------]
//[ Public virtual SceneNode functions                    ]
//[-------------------------------------------------------]
void SNCoordinateAxisRotation::DrawPost(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Call base implementation
	SNCoordinateAxis::DrawPost(cRenderer, pVisNode);

	if (pVisNode) {
		// Get position and scale
		const Vector3 &vPosition = GetTransform().GetPosition();
		const Vector3 &vScale    = GetTransform().GetScale();

		// Get the projection matrix
		Matrix4x4 mProjection;
		{
			SNCamera *pCamera = SNCamera::GetCamera();
			if (pCamera)
				mProjection = pCamera->GetProjectionMatrix(cRenderer.GetViewport());
		}

		// Get the view matrix
		Matrix4x4 mView;
		mView.SetTranslation(-4.0f, -2.5f);

		// Get the current view matrix
		Matrix4x4 mCurrentView = mProjection.GetInverted()*pVisNode->GetWorldViewProjectionMatrix();

		// Get the world matrix
		Matrix4x4 mWorld = mCurrentView;
		mWorld.SetTranslation(vPosition.x, vPosition.y, -10.0f+vPosition.z);

		// Calculate the world view projection matrix
		Matrix4x4 mWorldViewProjection = mProjection;
		mWorldViewProjection *= mView;
		mWorldViewProjection *= mWorld;

		// Setup render states
		cRenderer.GetRendererContext().GetEffectManager().Use();
		if (!(GetFlags() & DepthTest)) {
			cRenderer.SetRenderState(RenderState::ZEnable,      false);
			cRenderer.SetRenderState(RenderState::ZWriteEnable, false);
		}

		// Draw axis
		DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
		cDrawHelpers.DrawLine(XColor.Get(), Vector3::Zero, Vector3(vScale.x, 0.0f,     0.0f),     mWorldViewProjection, Width);
		cDrawHelpers.DrawLine(YColor.Get(), Vector3::Zero, Vector3(0.0f,     vScale.y, 0.0f),     mWorldViewProjection, Width);
		cDrawHelpers.DrawLine(ZColor.Get(), Vector3::Zero, Vector3(0.0f,     0.0f,     vScale.z), mWorldViewProjection, Width);

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
				cDrawHelpers.DrawText(*pFont, (vScale.x >= 0.0f) ? "X" : "-X", XColor.Get(), Vector3(vScale.x, 0.0f, 0.0f), mWorldViewProjection, Font::CenterText);
			// Y-axis
			if (!(GetFlags() & NoYText))
				cDrawHelpers.DrawText(*pFont, (vScale.y >= 0.0f) ? "Y" : "-Y", YColor.Get(), Vector3(0.0f, vScale.y, 0.0f), mWorldViewProjection, Font::CenterText);
			// Z-axis
			if (!(GetFlags() & NoZText))
				cDrawHelpers.DrawText(*pFont, (vScale.z >= 0.0f) ? "Z" : "-Z", ZColor.Get(), Vector3(0.0f, 0.0f, vScale.z), mWorldViewProjection, Font::CenterText);
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
