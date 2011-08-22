/*********************************************************\
 *  File: SNGravitationSample.cpp                        *
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
#include <PLCore/Tools/Timing.h>
#include <PLRenderer/RendererContext.h>
#include <PLScene/Scene/SceneContext.h>
#include <SPARK_PL/RenderingAPIs/PixelLight/SPK_PLLineTrailRenderer.h>
#include <SPARK_PL/SPK.h>
#include "SNGravitationSample.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLScene;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNGravitationSample)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNGravitationSample::SNGravitationSample() :
	m_pParticleGroup(nullptr),
	m_pMassGroup(nullptr),
	m_pParticleModel(nullptr),
	m_fStep(0.0f)
{
}

/**
*  @brief
*    Destructor
*/
SNGravitationSample::~SNGravitationSample()
{
	// Cleanup
	if (m_pParticleGroup)
		delete m_pParticleGroup;
	if (m_pMassGroup)
		delete m_pMassGroup;
}


//[-------------------------------------------------------]
//[ Protected virtual SNSystem functions                  ]
//[-------------------------------------------------------]
void SNGravitationSample::Update()
{
	// Get the current time difference
	const float fTimeDiff = Timing::GetInstance()->GetTimeDifference();

	// Changes the color of the model over time
	m_fStep += fTimeDiff*2;
	const SPK::Vector3D vColor(0.6f + 0.4f*Math::Sin(m_fStep), 0.6f + 0.4f*Math::Sin(m_fStep + static_cast<float>(Math::Pi*2.0f/3.0f)), 0.6f + 0.4f*Math::Sin(m_fStep + static_cast<float>(Math::Pi*4.0f/3.0f)));
	m_pParticleModel->setParam(SPK::PARAM_RED,   Math::Max(0.0f, vColor.x - 0.25f), Math::Min(1.0f, vColor.x + 0.25f));
	m_pParticleModel->setParam(SPK::PARAM_GREEN, Math::Max(0.0f, vColor.y - 0.25f), Math::Min(1.0f, vColor.y + 0.25f));
	m_pParticleModel->setParam(SPK::PARAM_BLUE,  Math::Max(0.0f, vColor.z - 0.25f), Math::Min(1.0f, vColor.z + 0.25f));

	if (m_pMassGroup) {
		// If the number of particles in the mass group is 0 (at init or when the system is reinitialized),
		// a number of particles equal to NumOfPointMasses is added
		if (!m_pMassGroup->getNbParticles()) {
			for (uint32 i=0; i<NumOfPointMasses; i++)
				m_pMassGroup->addParticles(1, SPK::Vector3D(2.0f, 0.0f, 0.0f), SPK::Vector3D(Math::GetRandMinMaxFloat(-1.0f, 0.0f), Math::GetRandMinMaxFloat(-0.5f, 0.5f), Math::GetRandMinMaxFloat(-0.5f, 0.5f)));
			m_pMassGroup->flushAddedParticles(); // to ensure particles are added
		}
	
		// The point masses are attached one by one to the particles in the m_pMassGroup so that they follow their moves
		for (uint32 i=0; i<NumOfPointMasses; i++)
			m_pPointMasses[i]->setPosition(m_pMassGroup->getParticle(i).position());
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void SNGravitationSample::InitFunction()
{
	// Call base implementation
	SNSystem::InitFunction();

	// Get the instance of the used renderer
	Renderer &cRenderer = GetSceneContext()->GetRendererContext().GetRenderer();

	// Renderers
	static const uint32 NumberOfSegments = 32;
	SPARK_PL::SPK_PLLineTrailRenderer *pSPK_PLLineTrailRenderer = CreateSPK_PLLineTrailRenderer(cRenderer);
	pSPK_PLLineTrailRenderer->setBlending(SPK::BLENDING_ADD);
	pSPK_PLLineTrailRenderer->SetDuration(2.0f);
	pSPK_PLLineTrailRenderer->SetNumOfSamples(NumberOfSegments);
	pSPK_PLLineTrailRenderer->enableRenderingHint(SPK::DEPTH_WRITE, false);

	// Create the SPARK particle models
	SPK::Model *pMassModel = SPK::Model::create();
	pMassModel->setImmortal(true);

	m_pParticleModel = SPK::Model::create(SPK::FLAG_RED | SPK::FLAG_GREEN | SPK::FLAG_BLUE | SPK::FLAG_ALPHA,
		SPK::FLAG_ALPHA, SPK::FLAG_RED | SPK::FLAG_GREEN | SPK::FLAG_BLUE);
	m_pParticleModel->setParam(SPK::PARAM_ALPHA, 0.1f, 0.0f);
	m_pParticleModel->setLifeTime(5.0f, 8.0f);

	// Create the SPARK particle emitter
	SPK::RandomEmitter *pParticleEmitter = SPK::RandomEmitter::create();
	pParticleEmitter->setFlow(400);
	pParticleEmitter->setForce(0.0f, 0.1f);

	// This is the point mass that will attract the other point masses to make them move
	SPK::PointMass *pCenterPointMass = SPK::PointMass::create();
	pCenterPointMass->setMass(0.6f);
	pCenterPointMass->setMinDistance(0.01f);

	// Create the SPARK particle groups
	m_pParticleGroup = SPK::Group::create(m_pParticleModel, 4100);
	m_pParticleGroup->addEmitter(pParticleEmitter);
	m_pParticleGroup->setRenderer(pSPK_PLLineTrailRenderer);
	m_pParticleGroup->enableAABBComputing(true);

	m_pMassGroup = SPK::Group::create(pMassModel, NumOfPointMasses);
	m_pMassGroup->addModifier(pCenterPointMass);
	m_pMassGroup->setRenderer(nullptr);
	m_pMassGroup->enableAABBComputing(true);

	// Creates the point masses that will attract the particles
	for (uint32 i=0; i<NumOfPointMasses; i++) {
		m_pPointMasses[i] = SPK::PointMass::create();
		m_pPointMasses[i]->setMass(3.0f);
		m_pPointMasses[i]->setMinDistance(0.05f);
		m_pParticleGroup->addModifier(m_pPointMasses[i]);
	}

	// Create the SPARK particle system
	m_pParticleSystem = SPK::System::create();
	m_pParticleSystem->addGroup(m_pMassGroup);
	m_pParticleSystem->addGroup(m_pParticleGroup);
	m_pParticleSystem->enableAABBComputing(true);
}
