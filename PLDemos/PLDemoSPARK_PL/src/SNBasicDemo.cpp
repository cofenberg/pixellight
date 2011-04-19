/*********************************************************\
 *  File: SNBasicDemo.cpp                                *
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
#include <SPARK_PL/RenderingAPIs/PixelLight/SPK_PLPointRendererFixedFunctions.h>
#include <SPARK_PL/RenderingAPIs/PixelLight/SPK_PLQuadRendererFixedFunctions.h>
#include <SPARK_PL/SPK.h>
#include "SNBasicDemo.h"


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
pl_implement_class(SNBasicDemo)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNBasicDemo::SNBasicDemo() :
	m_pParticleGroup(nullptr),
	m_pParticleModel(nullptr),
	m_fStep(0.0f)
{
}

/**
*  @brief
*    Destructor
*/
SNBasicDemo::~SNBasicDemo()
{
	// Cleanup
	if (m_pParticleGroup)
		delete m_pParticleGroup;
}


//[-------------------------------------------------------]
//[ Protected virtual SNSystem functions                  ]
//[-------------------------------------------------------]
void SNBasicDemo::Update()
{
	// Get the current time difference
	const float fTimeDiff = Timing::GetInstance()->GetTimeDifference();

	// Changes the color of the model over time
	m_fStep += fTimeDiff*5;
	m_pParticleModel->setParam(SPK::PARAM_RED,   0.6f + 0.4f*Math::Sin(m_fStep));
	m_pParticleModel->setParam(SPK::PARAM_GREEN, 0.6f + 0.4f*Math::Sin(m_fStep + static_cast<float>(Math::Pi*2.0f/3.0f)));
	m_pParticleModel->setParam(SPK::PARAM_BLUE,  0.6f + 0.4f*Math::Sin(m_fStep + static_cast<float>(Math::Pi*4.0f/3.0f)));
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void SNBasicDemo::InitFunction()
{
	// Call base implementation
	SNSystem::InitFunction();

	// Get the instance of the used renderer
	Renderer &cRenderer = GetSceneContext()->GetRendererContext().GetRenderer();

	// Inits Particle Engine
	SPK::Vector3D vGravity(0.0f, -0.8f, 0.0f);

	// Renderers
	SPARK_PL::SPK_PLRenderer *pParticleRenderer = nullptr;

	// We use point sprites only if it is available and if point parameters are available as well
	if (cRenderer.GetCapabilities().bPointSprite && cRenderer.GetCapabilities().bPointParameters) {
		SPARK_PL::SPK_PLPointRenderer *pPointRenderer = SPARK_PL::SPK_PLPointRendererFixedFunctions::Create(cRenderer);
		pPointRenderer->setType(SPK::POINT_SPRITE);
		pPointRenderer->SetTexture(GetSceneContext()->GetRendererContext().GetTextureManager().LoadResource("Data/Textures/SPARK/Point.dds"));
		pPointRenderer->EnableWorldSize(true);
		pPointRenderer->setSize(0.05f);
		pParticleRenderer = pPointRenderer;

	// We use quads
	} else {
		SPARK_PL::SPK_PLQuadRenderer *pQuadRenderer = SPARK_PL::SPK_PLQuadRendererFixedFunctions::Create(cRenderer);
		pQuadRenderer->setTexturingMode(SPK::TEXTURE_2D);
		pQuadRenderer->SetTexture(GetSceneContext()->GetRendererContext().GetTextureManager().LoadResource("Data/Textures/SPARK/Point.dds"));
		pQuadRenderer->setScale(0.05f, 0.05f);
		pParticleRenderer = pQuadRenderer;
	}

	pParticleRenderer->setBlending(SPK::BLENDING_ADD);
	pParticleRenderer->enableRenderingHint(SPK::DEPTH_WRITE, false);

	// Create the SPARK particle model
	m_pParticleModel = SPK::Model::create(SPK::FLAG_RED | SPK::FLAG_GREEN | SPK::FLAG_BLUE | SPK::FLAG_ALPHA);
	m_pParticleModel->setParam(SPK::PARAM_ALPHA, 0.8f); // Constant alpha
	m_pParticleModel->setLifeTime(8.0f, 8.0f);

	// Create the SPARK particle emitter
	SPK::SphericEmitter *pParticleEmitter = SPK::SphericEmitter::create(SPK::Vector3D(0.0f, 1.0f, 0.0f), static_cast<float>(0.1f*Math::Pi), static_cast<float>(0.1f*Math::Pi));
	pParticleEmitter->setZone(SPK::Point::create(SPK::Vector3D(0.0f, 0.015f, 0.0f)));
	pParticleEmitter->setFlow(250);
	pParticleEmitter->setForce(1.5f, 1.5f);

	// Create the SPARK particle obstacle
	SPK::Plane *pGroundPlane = SPK::Plane::create();
	SPK::Obstacle *pObstacle = SPK::Obstacle::create(pGroundPlane, SPK::INTERSECT_ZONE, 0.6f, 1.0f);

	// Create the SPARK particle group
	m_pParticleGroup = SPK::Group::create(m_pParticleModel, 2100);
	m_pParticleGroup->addEmitter(pParticleEmitter);
	m_pParticleGroup->addModifier(pObstacle);
	m_pParticleGroup->setRenderer(pParticleRenderer);
	m_pParticleGroup->setGravity(vGravity);
	m_pParticleGroup->enableAABBComputing(true);

	// Create the SPARK particle system
	m_pParticleSystem = SPK::System::create();
	m_pParticleSystem->addGroup(m_pParticleGroup);
	m_pParticleSystem->enableAABBComputing(true);
}
