/*********************************************************\
 *  File: ShadowMappingLiSPSM.cpp                        *
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
#include "PLCompositing/Shaders/ShadowMapping/ShadowMappingLiSPSM.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ShadowMappingLiSPSM)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
ShadowMappingLiSPSM::ShadowMappingLiSPSM()
{
}

/**
*  @brief
*    Destructur
*/
ShadowMappingLiSPSM::~ShadowMappingLiSPSM()
{
}


//[-------------------------------------------------------]
//[ Public virtual ShadowMapping functions                ]
//[-------------------------------------------------------]
void ShadowMappingLiSPSM::CalculateLightMatrices(SNLight &cLight, Matrix4x4 &mLightView, Matrix4x4 &mLightProjection)
{
	// [TODO] Implement me
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
