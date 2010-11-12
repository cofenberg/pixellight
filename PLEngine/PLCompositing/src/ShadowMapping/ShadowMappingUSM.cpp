/*********************************************************\
 *  File: ShadowMappingUSM.cpp                           *
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
#include <PLScene/Scene/SNSpotLight.h>
#include "PLCompositing/ShadowMapping/ShadowMappingUSM.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ShadowMappingUSM)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
ShadowMappingUSM::ShadowMappingUSM()
{
}

/**
*  @brief
*    Destructur
*/
ShadowMappingUSM::~ShadowMappingUSM()
{
}


//[-------------------------------------------------------]
//[ Public virtual ShadowMapping functions                ]
//[-------------------------------------------------------]
void ShadowMappingUSM::CalculateLightMatrices(SNLight &cLight, Matrix4x4 &mLightView, Matrix4x4 &mLightProjection)
{
	// Spot or point light?
	if (cLight.IsSpotLight()) {
		// Cast to spot light
		SNSpotLight &cSpotLight = (SNSpotLight&)cLight;

		// We "could" just reuse the view matrix of the light, but when for example constantly rotating the light around the z-axis,
		// the shadow mapping artefacts would also constantly move resulting in an annoying noisy shadow...
		// mLightView = cSpotLight.GetViewMatrix();
		// ... therefore we calculate a new view matrix for the shadow mapping with a fixed up-vector
		const Transform3 &cTransform = cLight.GetTransform();
		mLightView.LookAt(cTransform.GetPosition(), cTransform.GetPosition() + cTransform.GetRotation().GetZAxis(), Vector3::UnitY);

		// Just copy over the light projection matrix
		mLightProjection = cSpotLight.GetProjectionMatrix();
	} else {
		// Must be a directional light

		// [TODO] Implement me
		mLightView		 = Matrix4x4::Identity;
		mLightProjection = Matrix4x4::Identity;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
