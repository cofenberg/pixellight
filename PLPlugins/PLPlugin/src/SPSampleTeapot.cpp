/*********************************************************\
 *  File: SPSampleTeapot.cpp                             *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLMath/Rectangle.h>
#include <PLMath/Matrix4x4.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLRenderer/Effect/EffectTechnique.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLMesh/MeshManager.h>
#include "PLPlugin/SPSampleTeapot.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLMesh;
namespace PLPlugin {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SPSampleTeapot)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SPSampleTeapot::SPSampleTeapot(Renderer &cRenderer) : SurfacePainter(cRenderer),
	m_fRotation(0.0f),
	m_pMeshManager(new MeshManager(GetRenderer())),
	m_pMeshHandler(new MeshHandler())
{
	// Get/create the 'teapot' mesh
	Mesh *pMesh = m_pMeshManager->Get("MyTeapot");
	if (!pMesh) {
		pMesh = m_pMeshManager->CreateMesh("PLMesh::MeshCreatorTeapot", true, "");
		if (pMesh) {
			// Create mesh
			pMesh->SetName("MyTeapot");

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
						pTechnique->AddPass();
					}
					pMaterial->SetEffect(pFX);
				}
				pMesh->SetMaterial(0, pMaterial);
			}
		}
	}
	m_pMeshHandler->SetMesh(pMesh);
}

/**
*  @brief
*    Destructor
*/
SPSampleTeapot::~SPSampleTeapot()
{
	// Destroy our mesh handler
	delete m_pMeshHandler;

	// Destroy our mesh manager
	delete m_pMeshManager;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::SurfacePainter functions  ]
//[-------------------------------------------------------]
void SPSampleTeapot::OnPaint(Surface &cSurface)
{
	// Get the used renderer
	Renderer &cRenderer = GetRenderer();

	// Fixed functions support required
	FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
	if (pFixedFunctions) {
		// Clear the content of the current used render target
		cRenderer.Clear(Clear::Color | Clear::ZBuffer, Color4::Gray);

		{ // Setup projection matrix
			// Calculate projection matrix
			Matrix4x4 mProj;
			float fAspect      = 1.0f;
			float fAspectRadio = cRenderer.GetViewport().GetWidth()/(cRenderer.GetViewport().GetHeight()*fAspect);
			mProj.PerspectiveFov(float(45.0f*Math::DegToRad), fAspectRadio, 0.001f, 1000.0f);

			// Set the current projection matrix
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::Projection, mProj);
		}

		{ // Setup view matrix
			Matrix4x4 mView;
			mView.SetTranslation(0.0f, -0.1f, -0.5f);
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::View, mView);
		}

		// Setup light
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

		{ // Setup world matrix
			Matrix4x4 mWorld;
			mWorld.FromEulerAngleY(float(m_fRotation*Math::DegToRad));
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, mWorld);

			// Increase the rotation by the current time difference (time past since the last frame)
			// -> Normally, such work should NOT be performed within the rendering step, but we want
			//    to keep the implementation simple in here...
			m_fRotation += Timing::GetInstance()->GetTimeDifference()*50;
		}

		// Draw the mesh handlers mesh
		m_pMeshHandler->Draw();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPlugin
