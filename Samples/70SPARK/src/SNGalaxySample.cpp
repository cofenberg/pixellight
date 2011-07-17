/*********************************************************\
 *  File: SNGalaxySample.cpp                             *
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
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Texture/TextureManager.h>
#include <PLScene/Scene/SceneContext.h>
#include <SPARK_PL/RenderingAPIs/PixelLight/SPK_PLQuadRenderer.h>
#include <SPARK_PL/SPK.h>
#include "SNGalaxySample.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLScene;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNGalaxySample)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNGalaxySample::SNGalaxySample()
{
}

/**
*  @brief
*    Destructor
*/
SNGalaxySample::~SNGalaxySample()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void SNGalaxySample::InitFunction()
{
	// Call base implementation
	SNSystem::InitFunction();

	// Get the instance of the used renderer
	Renderer &cRenderer = GetSceneContext()->GetRendererContext().GetRenderer();

	// Renderers
	SPARK_PL::SPK_PLQuadRenderer *pParticleRenderer = CreateSPK_PLQuadRenderer(cRenderer);
	pParticleRenderer->setTexturingMode(SPK::TEXTURE_2D);
	pParticleRenderer->SetTexture(GetSceneContext()->GetRendererContext().GetTextureManager().LoadResource("Data/Textures/SPARK/Flare.dds"));
	pParticleRenderer->setScale(0.05f, 0.05f);
	pParticleRenderer->setBlending(SPK::BLENDING_ADD);
	pParticleRenderer->enableRenderingHint(SPK::DEPTH_WRITE, false);

	// Create the SPARK particle model
	SPK::Model *pGalaxyModel = SPK::Model::create(SPK::FLAG_RED | SPK::FLAG_GREEN | SPK::FLAG_BLUE | SPK::FLAG_ALPHA | SPK::FLAG_SIZE,	// Enable
		SPK::FLAG_RED | SPK::FLAG_GREEN | SPK::FLAG_BLUE,	// Mutable
		SPK::FLAG_RED | SPK::FLAG_GREEN | SPK::FLAG_SIZE,	// Random
		SPK::FLAG_ALPHA);	// Interpolated
	pGalaxyModel->setParam(SPK::PARAM_RED,0.0f, 0.3f, 0.5f, 0.5f);
	pGalaxyModel->setParam(SPK::PARAM_GREEN, 0.0f, 0.3f, 0.5f, 0.5f);
	pGalaxyModel->setParam(SPK::PARAM_BLUE, 1.0f, 0.1f);
	pGalaxyModel->setParam(SPK::PARAM_SIZE, 0.1f, 5.0f);
	pGalaxyModel->setLifeTime(35.0f, 40.0f);

	SPK::Interpolator *pAlphaInterpolator = pGalaxyModel->getInterpolator(SPK::PARAM_ALPHA);
	pAlphaInterpolator->addEntry(0.0f, 0.0f);			// First the alpha is at 0
	pAlphaInterpolator->addEntry(0.95f, 0.6f, 1.0f);	// Then ot reaches its values between 0.6 and 1 (slow fade in)
	pAlphaInterpolator->addEntry(1.0f, 0.0f);			// At the end of the particle life, it quickly fades out

	// Create the SPARK particle emitter
	SPK::RandomEmitter *pLineEmitter1 = SPK::RandomEmitter::create();
	pLineEmitter1->setZone(SPK::Line::create(SPK::Vector3D(-2.5f, 0.0f, -2.5f), SPK::Vector3D(2.5f, 0.0f, 2.5f)));
	pLineEmitter1->setFlow(100);
	pLineEmitter1->setForce(0.0f, 0.01f);

	SPK::RandomEmitter *pLineEmitter2 = SPK::RandomEmitter::create();
	pLineEmitter2->setZone(SPK::Line::create(SPK::Vector3D(-2.5f, 0.0f, 2.5f), SPK::Vector3D(2.5f, 0.0f, -2.5f)));
	pLineEmitter2->setFlow(100);
	pLineEmitter2->setForce(0.0f, 0.01f);

	SPK::Vortex *pVortex = SPK::Vortex::create();
	pVortex->setRotationSpeed(0.4f, false);
	pVortex->setAttractionSpeed(0.04f, true);
	pVortex->setEyeRadius(0.05f);
	pVortex->enableParticleKilling(true);

	// Create the SPARK particle groups
	SPK::Group *pGalaxyGroup = SPK::Group::create(pGalaxyModel, 8000);
	pGalaxyGroup->addEmitter(pLineEmitter1);
	pGalaxyGroup->addEmitter(pLineEmitter2);
	pGalaxyGroup->setRenderer(pParticleRenderer);
	pGalaxyGroup->addModifier(pVortex);
	pGalaxyGroup->enableAABBComputing(true);

	// Create the SPARK particle system
	m_pParticleSystem = SPK::System::create();
	m_pParticleSystem->addGroup(pGalaxyGroup);
	m_pParticleSystem->enableAABBComputing(true);
}
