/*********************************************************\
 *  File: SNMPostProcessBloomToneMap.h                   *
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


#ifndef __PLPOSTPROCESSEFFECTS_BLOOMTONEMAP_H__
#define __PLPOSTPROCESSEFFECTS_BLOOMTONEMAP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
#include <PLGraphics/Color/Color3.h>
#include <PLCompositing/SceneNodeModifiers/SNMPostProcess.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Bloom tone map camera scene node post process modifier class
*
*  @remarks
*    Bloom effect with tone mapping.
*/
class SNMPostProcessBloomToneMap : public PLCompositing::SNMPostProcess {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SNMPostProcessBloomToneMap, "PLPostProcessEffects", PLCompositing::SNMPostProcess, "")
		pl_constructor_1(ParameterConstructor, PLScene::SceneNode&, "Parameter constructor", "")
		pl_attribute(BloomScale,	float,				0.8f,									ReadWrite, DirectValue,	"Bloom scale",							"")
		pl_attribute(Strength,		PLMath::Vector2,	PLMath::Vector2(4.0f, 4.0f),			ReadWrite, DirectValue,	"Blur strength",						"")
		pl_attribute(ExposureLevel,	float,				0.05f,									ReadWrite, DirectValue,	"Exposure level",						"")
		pl_attribute(GammaLevel,	float,				1.8f,									ReadWrite, DirectValue,	"Gamma level",							"")
		pl_attribute(DeFogLevel,	float,				0.0f,									ReadWrite, DirectValue,	"De-fog level",							"")
		pl_attribute(FogColor,		PLGraphics::Color3,	PLGraphics::Color3(1.0, 1.0, 1.0f),		ReadWrite, DirectValue,	"Fog color",							"")
		// Overloaded SNMPostProcess variables
		pl_attribute(Filename,		PLGeneral::String,	"Data/PostProcesses/BloomToneMap.pp",	ReadWrite, ModifyAttr,	"Filename of the post process to use", "Type='PostProcess'")
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
		SNMPostProcessBloomToneMap(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SNMPostProcessBloomToneMap();


	//[-------------------------------------------------------]
	//[ Public virtual PLCompositing::SNMPostProcess functions ]
	//[-------------------------------------------------------]
	public:
		virtual void SetParameters();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects


#endif // __PLPOSTPROCESSEFFECTS_BLOOMTONEMAP_H__
