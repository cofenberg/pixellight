/*********************************************************\
 *  File: ShadowMapping.h                                *
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


#ifndef __PLCOMPOSITING_SHADOWMAPPING_H__
#define __PLCOMPOSITING_SHADOWMAPPING_H__
#pragma once


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class Matrix4x4;
}
namespace PLScene {
	class SNLight;
}


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include "PLCompositing/PLCompositing.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract shadow mapping algorithm base class
*/
class ShadowMapping : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, ShadowMapping, "PLCompositing", PLCore::Object, "Abstract shadow mapping algorithm base class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~ShadowMapping();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API ShadowMapping();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLCOM_API ShadowMapping(const ShadowMapping &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		PLCOM_API ShadowMapping &operator =(const ShadowMapping &cSource);


	//[-------------------------------------------------------]
	//[ Public virtual ShadowMapping functions                ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Calculates the view matrix and projection matrix for the given light
		*
		*  @param[in]  cLight
		*    Light scene node to render the shadow map for
		*  @param[out] mLightView
		*    Receives the calculated view matrix for the given light
		*  @param[out] mLightProjection
		*    Receives the calculated projection matrix for the given light, in case of spot light it's the spot light
		*    perspective transformation, in the case of a directional light a identity matrix
		*/
		virtual void CalculateLightMatrices(PLScene::SNLight &cLight, PLMath::Matrix4x4 &mLightView, PLMath::Matrix4x4 &mLightProjection) = 0;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_SHADOWMAPPING_H__
