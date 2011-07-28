/*********************************************************\
 *  File: SNSphereFog.h                                  *
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


#ifndef __PLSCENE_SPHEREFOG_H__
#define __PLSCENE_SPHEREFOG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SNFog.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Spherical volumetric fog scene node
*/
class SNSphereFog : public SNFog {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API static const float MinRange;	/**< Minimum fog range (0.0001) */


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNSphereFog, "PLScene", PLScene::SNFog, "Spherical volumetric fog scene node")
		// Attributes
		pl_attribute(Range,			float,	1.0f,	ReadWrite,	GetSet,			"Fog range",		"Min='0.0001'")
		pl_attribute(Volumetricy,	float,	1.0f,	ReadWrite,	DirectValue,	"Fog volumetricy",	"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API float GetRange() const;
		PLS_API void SetRange(float fValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNSphereFog();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNSphereFog();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float m_fRange;	/**< Fog range */


	//[-------------------------------------------------------]
	//[ Public virtual SNFog functions                        ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual bool IsSphereFog() const override;


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNode functions                 ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual void UpdateAABoundingBox() override;
		PLS_API virtual void GetBoundingSphere(PLMath::Sphere &cSphere) override;
		PLS_API virtual void GetContainerBoundingSphere(PLMath::Sphere &cSphere) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SPHEREFOG_H__
