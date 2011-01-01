/*********************************************************\
 *  File: SNMPostProcessGlow.h                           *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_GLOW_H__
#define __PLSCENE_SCENENODEMODIFIER_GLOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
#include "PLCompositing/SceneNodeModifiers/SNMPostProcess.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Glow camera scene node post process modifier class
*
*  @remarks
*    Glow effect.
*/
class SNMPostProcessGlow : public SNMPostProcess {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SNMPostProcessGlow, "PLCompositing", PLCompositing::SNMPostProcess, "Glow camera scene node post process modifier class")
		pl_constructor_1(ParameterConstructor, PLScene::SceneNode&, "Parameter constructor", "")
		pl_attribute(Strength,		PLMath::Vector2,	PLMath::Vector2(8.0f, 8.0f),	ReadWrite,	DirectValue,	"Blur strength",						"")
		pl_attribute(Luminance,		float,				0.08f,							ReadWrite,	DirectValue,	"Luminance",							"")
		pl_attribute(MiddleGray,	float,				0.18f,							ReadWrite,	DirectValue,	"Middle gray",							"")
		pl_attribute(WhiteCutoff,	float,				0.99f,							ReadWrite,	DirectValue,	"White cutoff",							"")
		pl_attribute(BloomScale,	float,				1.5f,							ReadWrite,	DirectValue,	"Bloom scale",							"")
		// Overloaded SNMPostProcess variables
		pl_attribute(Filename,		PLGeneral::String,	"Data/PostProcesses/Glow.pp",	ReadWrite,	ModifyAttr,		"Filename of the post process to use",	"Type='PostProcess'")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		PLCOM_API SNMPostProcessGlow(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLCOM_API virtual ~SNMPostProcessGlow();


	//[-------------------------------------------------------]
	//[ Public virtual SNMPostProcess functions               ]
	//[-------------------------------------------------------]
	public:
		PLCOM_API virtual void SetParameters();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLSCENE_SCENENODEMODIFIER_GLOW_H__
