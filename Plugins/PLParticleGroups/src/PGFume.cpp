/*********************************************************\
 *  File: PGFume.cpp                                     *
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
#include <PLScene/Scene/SceneContext.h>
#include "PLParticleGroups/PGFume.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLScene;
namespace PLParticleGroups {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(PGFume)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PGFume::PGFume() :
	Size(this),
	SizeTimeScale(this),
	Energie(this),
	Color(this),
	PositionScale(this),
	Material(this),
	Particles(this),
	TextureAnimationColumns(this),
	TextureAnimationRows(this),
	EventHandlerUpdate(&PGFume::OnUpdate, this),
	m_bUpdate(false),
	m_fParticleTime(0.0f),
	m_bCreateNewParticles(true)
{
	// Overwritten SNParticleGroup variables
	m_sMaterial				   = "Data/Effects/PGFume.plfx";
	m_nParticles			   = 20;
	m_nTextureAnimationColumns = 4;
	m_nTextureAnimationRows    = 4;

	// Init data
	m_SData.fSize         = 0.0f;
	m_SData.fEnergy       = 0.0f;
	m_SData.fParticleTime = 0.0f;
}

/**
*  @brief
*    Destructor
*/
PGFume::~PGFume()
{
}

/**
*  @brief
*    Returns the default settings of the particle group
*/
void PGFume::GetDefaultSettings(PGFume::InitData &cData) const
{
	// Set default settings
	cData.fSize         = Size;
	cData.fEnergy       = Energie;
	cData.fParticleTime = 0.01f;
}

/**
*  @brief
*    Returns whether new particles should be created or not
*/
bool PGFume::GetCreateNewParticles() const
{
	return m_bCreateNewParticles;
}

/**
*  @brief
*    Sets whether new particles should be created or not
*/
void PGFume::CreateNewParticles(bool bCreate)
{
	m_bCreateNewParticles = bCreate;
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void PGFume::OnActivate(bool bActivate)
{
	// Call the base implementation
	SNParticleGroup::OnActivate(bActivate);

	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate)
			pSceneContext->EventUpdate.Connect(EventHandlerUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(EventHandlerUpdate);
	}
}

void PGFume::OnAddedToVisibilityTree(VisNode &cVisNode)
{
	m_bUpdate = true;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initializes a particle
*/
void PGFume::InitParticle(Particle &cParticle) const
{
	float vColor = static_cast<float>(200 + Math::GetRand()%56)/255;
	cParticle.vColor[0]     = vColor*Color.Get().r;
	cParticle.vColor[1]     = vColor*Color.Get().g;
	cParticle.vColor[2]     = vColor*Color.Get().b;
	cParticle.vColor[3]     = 1.0f;
	cParticle.vPos.x        = GetTransform().GetPosition().x + Math::GetRandNegFloat()*PositionScale;
	cParticle.vPos.y        = GetTransform().GetPosition().y + Math::GetRandNegFloat()*PositionScale;
	cParticle.vPos.z        = GetTransform().GetPosition().z + Math::GetRandNegFloat()*PositionScale;
	cParticle.fSize         = m_SData.fSize*2;
	cParticle.fRot          = Math::GetRandNegFloat()*180;
	cParticle.fEnergy       = 255*m_SData.fEnergy;
	cParticle.vVelocity.x   = 5.0f  + 6.0f  * Math::GetRandFloat();	// Lifetime
	cParticle.vVelocity.y   = 1.0f  + 4.0f  * Math::GetRandFloat();	// Frequency
	cParticle.vVelocity.z   = 20.0f + 30.0f * Math::GetRandFloat();	// Intensity
	cParticle.vDistortion.x = 0.0f;
	cParticle.vDistortion.y = 0.0f;
	cParticle.vDistortion.z = 0.0f;
	cParticle.fCustom1      = Math::GetRandNegFloat()*0.5f;
}

/**
*  @brief
*    Called when the scene node needs to be updated
*/
void PGFume::OnUpdate()
{
	// If this scene node wasn't drawn at the last frame, we can skip some update stuff
	if ((GetFlags() & ForceUpdate) || m_bUpdate) {
		m_bUpdate = false;

		// Check new particle generation
		float fTimeDiff = Timing::GetInstance()->GetTimeDifference();
		if (!GetRemoveAutomatically() && m_bCreateNewParticles) {
			m_fParticleTime -= fTimeDiff;
			if (m_fParticleTime < 0.0f) {
				// Create a new particle
				m_fParticleTime = m_SData.fParticleTime;
				Particle *pParticle = AddParticle();
				if (pParticle)
					InitParticle(*pParticle);
			}
		}

		uint32 nActive = 0;
		{ // Update particles
			float fFriction = static_cast<float>(Math::Pow(0.3f, fTimeDiff));
			Iterator<Particle> cIterator = GetParticleIterator();
			while (cIterator.HasNext()) {
				Particle &cParticle = cIterator.Next();

				nActive++;

				cParticle.fSize			+= 0.8f*fTimeDiff*SizeTimeScale;
				cParticle.vVelocity.x	-= fTimeDiff;								// Lifetime
				cParticle.vVelocity.z	-= fTimeDiff*20.0f*Math::GetRandFloat();	// Intensity
				cParticle.vPos.x		+= cParticle.vDistortion.x*fTimeDiff;		// Velocity
				cParticle.vPos.y		+= cParticle.vDistortion.y*fTimeDiff;
				cParticle.vPos.z		+= cParticle.vDistortion.z*fTimeDiff;
				cParticle.vDistortion.x	*= fFriction;
				cParticle.vDistortion.y	*= fFriction;
				cParticle.vDistortion.z	*= fFriction;
				cParticle.fRot			+= fTimeDiff*cParticle.fCustom1;

				float vColor = (cParticle.vVelocity.z + 30.0f*Math::Sin(cParticle.vVelocity.x*cParticle.vVelocity.y))/255;
				if (vColor < 0.0f)  {
					vColor = 0.0f;
					if (cParticle.vVelocity.x <= 0.0f) {
						RemoveParticle(cParticle);
						continue;
					}
				}
				cParticle.vColor[3] = vColor*Color.Get().a;

				// Texture animation
				cParticle.fAnimationTimer += fTimeDiff;
				if (cParticle.fAnimationTimer > 0.08f) {
					cParticle.fAnimationTimer = 0.0f;
					cParticle.nAnimationStep++;
					if (cParticle.nAnimationStep >= GetTextureAnimationSteps())
						cParticle.nAnimationStep = 0;
				}
			}
		}

		// Remove particle group?
		if (GetRemoveAutomatically() && !nActive)
			Delete();
		else {
			// We have to recalculate the current axis align bounding box in 'scene node space'
			DirtyAABoundingBox();
		}
	}
}


//[-------------------------------------------------------]
//[ Public virtual SNParticleGroup functions              ]
//[-------------------------------------------------------]
bool PGFume::InitParticleGroup(uint32 nMaxNumOfParticles, const String &sMaterial, const void *pData)
{
	if (pData) {
		const InitData &cData = *static_cast<const InitData*>(pData);
		m_SData.fSize		  = cData.fSize;
		m_SData.fEnergy		  = cData.fEnergy;
		m_SData.fParticleTime = cData.fParticleTime;
	} else {
		GetDefaultSettings(m_SData);
	}

	// Initialize the particles
	if (!InitParticles(nMaxNumOfParticles, sMaterial))
		return false; // Error!

	// Init data
	m_fParticleTime = m_SData.fParticleTime;

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLParticleGroups
