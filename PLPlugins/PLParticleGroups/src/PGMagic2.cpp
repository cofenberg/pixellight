/*********************************************************\
 *  File: PGMagic2.cpp                                   *
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
#include "PLParticleGroups/PGMagic2.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLScene;
namespace PLParticleGroups {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(PGMagic2)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PGMagic2::PGMagic2() :
	SmallParticles(this),
	TexAni(this),
	Size(this),
	Material(this),
	Particles(this),
	TextureAnimationColumns(this),
	TextureAnimationRows(this)
{
	// Overwritten PLScene::SNParticleGroup variables
	m_sMaterial				   = "Data/Textures/PGMagic2.dds";
	m_nParticles			   = 100;
	m_nTextureAnimationColumns = 2;
	m_nTextureAnimationRows    = 1;
}

/**
*  @brief
*    Destructor
*/
PGMagic2::~PGMagic2()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void PGMagic2::InitFunction()
{
	// Call base implementation
	SNParticleGroup::InitFunction();

	// If there are free particles, create new particles
	Particle *pParticle = AddParticle();
	while (pParticle) {
		pParticle->fSize	 = 2.0f*Size;
		pParticle->vColor.r  = 0.8f+Math::GetRandFloat()*0.2f;
		pParticle->vColor.g  = 0.8f+Math::GetRandFloat()*0.2f;
		pParticle->vColor.b  = 0.8f+Math::GetRandFloat()*0.2f;
		pParticle->vColor.a  = Math::Max(0.8f, Math::GetRandFloat());
		pParticle->fEnergy   = 1.0f;
		pParticle->fCustom2	 = 0.5f+Math::GetRandFloat()*2.0f;
		if (Math::GetRandFloat() > 0.5f)
			pParticle->fCustom2 = -pParticle->fCustom2;
		if (!SmallParticles || (Math::GetRand() % 10) == 5) {
			pParticle->nAnimationStep = 0;
			pParticle->nCustom1 = 1;
			pParticle->fSize = (8.0f+((float)(Math::GetRand() % 800)/200))*Size;
			pParticle->vPos = pParticle->vFixPos = pParticle->vDistortion = GetTransform().GetPosition();
		} else {
			pParticle->nAnimationStep = 1;
			pParticle->nCustom1 = 0;
			pParticle->fSize = (1.0f+((float)(Math::GetRand() % 1000)/500))*Size;
			for (int i=0; i<3; i++) {
				if ((Math::GetRand() % 2))
					pParticle->vPos[i] = pParticle->vFixPos[i] = pParticle->vDistortion[i] = (float)(Math::GetRand() % 200)/100+GetTransform().GetPosition()[i];
				else
					pParticle->vPos[i] = pParticle->vFixPos[i] = pParticle->vDistortion[i] = -(float)(Math::GetRand() % 200)/100+GetTransform().GetPosition()[i];
			}
		}
		pParticle->fCustom1 = pParticle->fSize;
		pParticle->fCustom2 *= 2;

		// Next particle, please
		pParticle = AddParticle();
	}
}

void PGMagic2::UpdateFunction()
{
	// If this scene node wasn't drawn at the last frame, we can skip some update stuff
	if ((GetFlags() & ForceUpdate) || GetDrawn()) {
		// Call base implementation
		SNParticleGroup::UpdateFunction();

		{ // Update particles
			float fTimeDiff = Timing::GetInstance()->GetTimeDifference();
			Iterator<Particle> cIterator = GetParticleIterator();
			while (cIterator.HasNext()) {
				Particle &cParticle = cIterator.Next();

				cParticle.fSize  = cParticle.fCustom1*Math::Sin(cParticle.vVelocity.GetLength()/10);
				cParticle.fRot  += fTimeDiff*cParticle.fCustom2;

				// Texture animation
				if (TexAni) {
					cParticle.fAnimationTimer += fTimeDiff;
					if (cParticle.fAnimationTimer > 0.2f) {
						cParticle.fAnimationTimer = 0.0f;
						cParticle.nAnimationStep++;
						if (cParticle.nAnimationStep >= GetTextureAnimationSteps())
							cParticle.nAnimationStep = 0;
					}
				}

				for (int i=0; i<3; i++) {
					if (cParticle.nCustom1) {
						if (cParticle.vPos[i] > cParticle.vDistortion[i])
							cParticle.vVelocity[i] -= fTimeDiff*15;
						else {
							if (cParticle.vPos[i] < cParticle.vDistortion[i])
								cParticle.vVelocity[i] += fTimeDiff*15;
						}
						if (cParticle.vVelocity[i] > 100.0f)
							cParticle.vVelocity[i] = 100.0f;
						if (cParticle.vVelocity[i] < -100.0f)
							cParticle.vVelocity[i] = -100.0f;
					} else {
						if (cParticle.vPos[i] > cParticle.vDistortion[i])
							cParticle.vVelocity[i] -= fTimeDiff*20;
						else {
							if (cParticle.vPos[i] < cParticle.vDistortion[i])
								cParticle.vVelocity[i] += fTimeDiff*20;
						}
						if (cParticle.vVelocity[i] > 200.0f)
							cParticle.vVelocity[i] = 200.0f;
						if (cParticle.vVelocity[i] < -200.0f)
							cParticle.vVelocity[i] = -200.0f;
					}

					cParticle.vPos[i] += cParticle.vVelocity[i]*fTimeDiff;

					if (cParticle.nCustom1) {
						if ((cParticle.vPos[i] <= cParticle.vDistortion[i]+0.1f &&
							 cParticle.vPos[i] >= cParticle.vDistortion[i]-0.1f) ||
							 cParticle.vPos[i] >= cParticle.vFixPos[i]+2.0f ||
							 cParticle.vPos[i] <= cParticle.vFixPos[i]-2.0) {
							if (cParticle.vDistortion[i] != cParticle.vFixPos[i])
								cParticle.vVelocity[i] *= 0.4f;
							if (cParticle.vPos[i] > cParticle.vFixPos[i]+1.0f ||
								cParticle.vPos[i] < cParticle.vFixPos[i]-1.0f)
								cParticle.vDistortion[i] = cParticle.vFixPos[i];
							else {
								if (Math::GetRand() % 2)
									cParticle.vDistortion[i] -= (float)1+(Math::GetRand() % 200)/100+GetTransform().GetPosition()[i];
								else cParticle.vDistortion[i] += (float)1+(Math::GetRand() % 200)/100+GetTransform().GetPosition()[i];
							}
						}
					} else {
						if ((cParticle.vPos[i] <= cParticle.vDistortion[i]+0.1f &&
							 cParticle.vPos[i] >= cParticle.vDistortion[i]-0.1f) ||
							 cParticle.vPos[i] >= cParticle.vFixPos[i]+4.0f ||
							 cParticle.vPos[i] <= cParticle.vFixPos[i]-4.0f) {
							if (cParticle.vDistortion[i] != cParticle.vFixPos[i])
								cParticle.vVelocity[i] *= 0.8f;
							if (cParticle.vPos[i] > cParticle.vFixPos[i]+1.0f ||
								cParticle.vPos[i] < cParticle.vFixPos[i]-1.0f)
								cParticle.vDistortion[i] = cParticle.vFixPos[i];
							else {
								if (Math::GetRand() % 2)
									cParticle.vDistortion[i] -= (float)1+(Math::GetRand() % 200)/100+GetTransform().GetPosition()[i];
								else cParticle.vDistortion[i] += (float)1+(Math::GetRand() % 200)/100+GetTransform().GetPosition()[i];
							}
						}
					}
				}
			}
		}

		// We have to recalculate the current axis align bounding box in 'scene node space'
		DirtyAABoundingBox();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLParticleGroups
