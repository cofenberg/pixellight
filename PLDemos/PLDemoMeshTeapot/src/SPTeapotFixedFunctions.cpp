/*********************************************************\
 *  File: SPTeapotFixedFunctions.cpp                     *
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
#include <PLMath/Rectangle.h>
#include <PLMath/Matrix4x4.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLRenderer/Effect/EffectPass.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLRenderer/Effect/EffectTechnique.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLMesh/MeshManager.h>
#include "SPTeapotFixedFunctions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLMesh;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SPTeapotFixedFunctions)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SPTeapotFixedFunctions::SPTeapotFixedFunctions(Renderer &cRenderer) : SPTeapot(cRenderer)
{
	// Get the renderer context
	RendererContext &cRendererContext = GetRenderer().GetRendererContext();

	// Create and set a special material & effect
	Material *pMaterial = cRendererContext.GetMaterialManager().Create("MyTeapot");
	if (pMaterial) {
		Effect *pFX = cRendererContext.GetEffectManager().Create("MyTeapot");
		if (pFX) {
			EffectTechnique *pTechnique = pFX->AddTechnique();
			if (pTechnique) {
				pFX->SelectTechnique(0);
				EffectPass *pEffectPass = pTechnique->AddPass();
				if (pEffectPass)
					pEffectPass->GetFixedFunctionsRenderStates().SetLighting(true);
			}
			pMaterial->SetEffect(pFX);
		}
		m_pMeshHandler->SetMaterial(0, pMaterial);
	}
}

/**
*  @brief
*    Destructor
*/
SPTeapotFixedFunctions::~SPTeapotFixedFunctions()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::SurfacePainter functions  ]
//[-------------------------------------------------------]
void SPTeapotFixedFunctions::OnPaint(Surface &cSurface)
{
	// Get the used renderer
	Renderer &cRenderer = GetRenderer();

	// Clear the content of the current used render target
	cRenderer.Clear(Clear::Color | Clear::ZBuffer, Color4::Gray);

	// Fixed functions support required
	FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
	if (pFixedFunctions) {
		{ // Setup light
			FixedFunctions::Light sLight;
			pFixedFunctions->GetDefaultLightSettings(sLight);
			sLight.cAmbient.SetRGBA(0.1f, 0.1f, 0.1f, 1.0f);
			sLight.cDiffuse.SetRGBA(1.0f, 1.0f, 1.0f, 1.0f);
			sLight.nType = FixedFunctions::LightType::Point;
			sLight.vPosition.SetXYZ(0.0f, 0.0f, 1.5f);
			sLight.fLinearAttenuation = 0.3f;
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, Matrix4x4::Identity);
			pFixedFunctions->SetLightEnabled(0, false);
			pFixedFunctions->SetLight		(0, sLight);
			pFixedFunctions->SetLightEnabled(0, true);
		}

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
			mView.SetTranslation(0.0f, -0.1f, -0.5f);
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::View, mView);
		}

		{ // Set the projection matrix
			Matrix4x4 mProj;
			const float fAspect      = 1.0f;
			const float fAspectRadio = cRenderer.GetViewport().GetWidth()/(cRenderer.GetViewport().GetHeight()*fAspect);
			mProj.PerspectiveFov(float(45.0f*Math::DegToRad), fAspectRadio, 0.001f, 1000.0f);
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::Projection, mProj);
		}

		// Draw the mesh handlers mesh
		m_pMeshHandler->Draw();
	}
}
