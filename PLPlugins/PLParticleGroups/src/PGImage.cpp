/*********************************************************\
 *  File: PGImage.cpp                                    *
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
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLScene/Scene/SceneContext.h>
#include "PLParticleGroups/PGImage.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLScene;
namespace PLParticleGroups {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(PGImage)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PGImage::PGImage() :
	ImageFilename(this),
	RedColorKey(this),
	GreenColorKey(this),
	BlueColorKey(this),
	ColorKeyTolerance(this),
	ImageScale(this),
	Material(this),
	Particles(this),
	Flags(this),
	EventHandlerUpdate(&PGImage::NotifyUpdate, this),
	m_bUpdate(false)
{
	// Overwritten PLScene::SNParticleGroup variables
	m_sMaterial  = "Data/Effects/PGImage.plfx";
	m_nParticles = 1;

	// Overwritten PLScene::SceneNode variables
	SetFlags(PointSprites | SceneNodeSpaceParticles);
}

/**
*  @brief
*    Destructor
*/
PGImage::~PGImage()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNode functions          ]
//[-------------------------------------------------------]
void PGImage::InitFunction()
{
	// Call base implementation
	SNParticleGroup::InitFunction();

	// Load image
	Image cImage;
	if (cImage.Load(ImageFilename.Get())) {
		// Get the image buffer
		ImageBuffer *pImageBuffer = cImage.GetBuffer();
		if (pImageBuffer) {
			const uint32  nWidth		   = pImageBuffer->GetSize().x;
			const uint32  nHeight		   = pImageBuffer->GetSize().y;
			const uint32  nPixels		   = nWidth*nHeight;
			const uint8  *pData			   = pImageBuffer->GetData();
			const uint32  nColorComponents = pImageBuffer->GetComponentsPerPixel();
			if (nColorComponents == 3 || nColorComponents == 4) {
				// Get total number of required particles
				uint32 nParticles = 0;
				for (uint32 i=0; i<nPixels; i++) {
					// Place particle at this image position?
					uint8 nDifR = (uint8)Math::Abs(pData[0]-RedColorKey);
					uint8 nDifG = (uint8)Math::Abs(pData[1]-GreenColorKey);
					uint8 nDifB = (uint8)Math::Abs(pData[2]-BlueColorKey);
					if (!(nDifR <= ColorKeyTolerance && nDifG <= ColorKeyTolerance && nDifB <= ColorKeyTolerance))
						nParticles++; // A particle here, please
					pData += nColorComponents;
				}
				pData = pImageBuffer->GetData();

				// Create the particles
				InitParticles(nParticles);

				// Setup the particles
				for (int nY=nHeight-1; nY>=0; nY--) {
					for (uint32 nX=0; nX<nWidth; nX++) {
						// Place particle at this image position?
						uint8 nDifR = (uint8)Math::Abs(pData[0]-RedColorKey);
						uint8 nDifG = (uint8)Math::Abs(pData[1]-GreenColorKey);
						uint8 nDifB = (uint8)Math::Abs(pData[2]-BlueColorKey);
						if (nDifR <= ColorKeyTolerance && nDifG <= ColorKeyTolerance && nDifB <= ColorKeyTolerance) {
							// No particle here, please
							pData += nColorComponents;
						} else {
							// Setup particle
							Particle *pParticle = AddParticle();
							if (pParticle) {
								pParticle->vColor.r = pData[0]/255.0f;
								pParticle->vColor.g = pData[1]/255.0f;
								pParticle->vColor.b = pData[2]/255.0f;
								pParticle->vColor.a = nColorComponents == 4 ? pData[3]/255.0f : 1.0f;
								pData += nColorComponents;
								pParticle->fEnergy  = 1.0f;
								pParticle->fCustom2 = 0.5f+Math::GetRandFloat()*2.0f;
								if (Math::GetRandFloat() > 0.5f)
									pParticle->fCustom2 = -pParticle->fCustom2;
								pParticle->fSize = (1.0f+((float)(Math::GetRand() % 1000)/500))*ImageScale;
								pParticle->vPos.x = pParticle->vFixPos.x = pParticle->vDistortion.x = float(nX*ImageScale);
								pParticle->vPos.y = pParticle->vFixPos.y = pParticle->vDistortion.y = float(nY*ImageScale);
								pParticle->vPos.z = pParticle->vFixPos.z = pParticle->vDistortion.z = 0.0f;
								pParticle->fCustom1 = pParticle->fSize;
								pParticle->fCustom2 *= 2;
							} else {
								// Error!
								nY = nHeight;
								nX = nWidth;
							}
						}
					}
				}
			}
		}
	}
}

void PGImage::OnActivate(bool bActivate)
{
	// Call the base implementation
	SNParticleGroup::OnActivate(bActivate);

	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate)
			pSceneContext->EventUpdate.Connect(&EventHandlerUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(&EventHandlerUpdate);
	}
}

void PGImage::OnAddedToVisibilityTree(VisNode &cVisNode)
{
	m_bUpdate = true;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void PGImage::NotifyUpdate()
{
	// If this scene node wasn't drawn at the last frame, we can skip some update stuff
	if ((GetFlags() & ForceUpdate) || m_bUpdate) {
		m_bUpdate = false;

		{ // Update particles
			float fTimeDiff = Timing::GetInstance()->GetTimeDifference();
			Iterator<Particle> cIterator = GetParticleIterator();
			while (cIterator.HasNext()) {
				Particle &cParticle = cIterator.Next();

				cParticle.fSize = cParticle.fCustom1;
				for (int i=0; i<3; i++) {
					if (cParticle.vPos[i] > cParticle.vDistortion[i])
						cParticle.vVelocity[i] -= fTimeDiff*10;
					else {
						if (cParticle.vPos[i] < cParticle.vDistortion[i])
							cParticle.vVelocity[i] += fTimeDiff*10;
					}
					if (cParticle.vVelocity[i] > 100.0f)
						cParticle.vVelocity[i] = 100.0f;
					if (cParticle.vVelocity[i] < -100.0f)
						cParticle.vVelocity[i] = -100.0f;

					cParticle.vPos[i] += cParticle.vVelocity[i]*fTimeDiff;

					if ((cParticle.vPos[i] <= cParticle.vDistortion[i]+0.1f &&
						cParticle.vPos[i] >= cParticle.vDistortion[i]-0.1f) ||
						cParticle.vPos[i] >= cParticle.vFixPos[i]+0.2f ||
						cParticle.vPos[i] <= cParticle.vFixPos[i]-0.2f) {
						if (cParticle.vDistortion[i] != cParticle.vFixPos[i])
							cParticle.vVelocity[i] *= 0.8f;
						if (cParticle.vPos[i] > cParticle.vFixPos[i]+0.2f ||
							cParticle.vPos[i] < cParticle.vFixPos[i]-0.2f)
							cParticle.vDistortion[i] = cParticle.vFixPos[i];
						else {
							if (Math::GetRand() % 2)
								cParticle.vDistortion[i] = (float)(Math::GetRand() % 100)/1000+cParticle.vFixPos[i];
							else cParticle.vDistortion[i] = (float)(Math::GetRand() % 100)/1000+cParticle.vFixPos[i];
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
