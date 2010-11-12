/*********************************************************\
 *  File: ShadowMappingUSM.h                             *
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


#ifndef __PLCOMPOSITING_SHADOWMAPPING_USM_H__
#define __PLCOMPOSITING_SHADOWMAPPING_USM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCompositing/ShadowMapping/ShadowMapping.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Traditional Uniform Shadow Mapping (USM) class
*
*  @remarks
*    Traditional Uniform Shadow Mapping (USM).
*/
class ShadowMappingUSM : public ShadowMapping {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, ShadowMappingUSM, "PLCompositing", PLCompositing::ShadowMapping, "Traditional Uniform Shadow Mapping (USM) class")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API ShadowMappingUSM();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~ShadowMappingUSM();


	//[-------------------------------------------------------]
	//[ Public virtual ShadowMapping functions                ]
	//[-------------------------------------------------------]
	public:
		virtual void CalculateLightMatrices(PLScene::SNLight &cLight, PLMath::Matrix4x4 &mLightView, PLMath::Matrix4x4 &mLightProjection);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_SHADOWMAPPING_USM_H__
