/*********************************************************\
 *  File: SPTexturingFixedFunctions.cpp                   *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLMath/Matrix4x4.h>
#include <PLMath/Rectangle.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include "SPTexturingFixedFunctions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SPTexturingFixedFunctions)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SPTexturingFixedFunctions::SPTexturingFixedFunctions(Renderer &cRenderer) : SPTexturing(cRenderer)
{
}

/**
*  @brief
*    Destructor
*/
SPTexturingFixedFunctions::~SPTexturingFixedFunctions()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::SurfacePainter functions  ]
//[-------------------------------------------------------]
void SPTexturingFixedFunctions::OnPaint(Surface &cSurface)
{
	// Get the used renderer
	Renderer &cRenderer = GetRenderer();

	// Clear the content of the current used render target (color to black and depth to 1.0 by default)
	cRenderer.Clear();

	// Fixed functions support required
	FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
	if (pFixedFunctions) {
		{ // Set the world matrix
			// Build a rotation matrix by using a given euler angle around the y-axis
			Matrix4x4 mWorld;
			mWorld.FromEulerAngleY(float(m_fRotation*Math::DegToRad));
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, mWorld);

			// Increase the rotation by the current time difference (time past since the last frame)
			// -> Normally, such work should NOT be performed within the rendering step, but we want
			//    to keep the implementation simple in here...
			m_fRotation += Timing::GetInstance()->GetTimeDifference()*50;
		}

		{ // Set the view matrix
			Matrix4x4 mView;
			mView.SetTranslation(0.0f, 0.0f, -5.0f);
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::View, mView);
		}

		{ // Set the projection matrix
			const float fAspect      = 1.0f;
			const float fAspectRadio = cRenderer.GetViewport().GetWidth()/(cRenderer.GetViewport().GetHeight()*fAspect);
			Matrix4x4 mProj;
			mProj.PerspectiveFov(float(45.0f*Math::DegToRad), fAspectRadio, 0.001f, 1000.0f);
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::Projection, mProj);
		}

		// Normally this vertex buffer we created is NEVER a null pointer, but in this demo
		// we want to go for sure
		if (m_pVertexBuffer) {
			// Bind our vertex buffer
			pFixedFunctions->SetVertexBuffer(m_pVertexBuffer);

			// Bind our texture buffer at texture unit 0
			cRenderer.SetTextureBuffer(0, m_pTextureBuffer);

			// No back face culling, please. Else we can only see one 'side' of the quad
			cRenderer.SetRenderState(RenderState::CullMode, Cull::None);

			// Now draw the primitives of our cool quad.
			// The primitive type is 'triangle strip', we start at vertex 0 and draw '4' vertices.
			cRenderer.DrawPrimitives(Primitive::TriangleStrip, 0, 4);
		}
	}
}
