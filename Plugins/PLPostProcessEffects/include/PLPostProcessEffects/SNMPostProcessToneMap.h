/*********************************************************\
 *  File: SNMPostProcessToneMap.h                        *
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


#ifndef __PLPOSTPROCESSEFFECTS_TONEMAP_H__
#define __PLPOSTPROCESSEFFECTS_TONEMAP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
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
*    Tone map camera scene node post process modifier class
*
*  @remarks
*    Tone mapping.
*/
class SNMPostProcessToneMap : public PLCompositing::SNMPostProcess {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SNMPostProcessToneMap, "PLPostProcessEffects", PLCompositing::SNMPostProcess, "")
		// Attributes
		pl_attribute(ExposureLevel,	float,				1.0f,									ReadWrite,	DirectValue,	"Exposure level",						"")
		pl_attribute(GammaLevel,	float,				1.0f,									ReadWrite,	DirectValue,	"Gamma level",							"")
		pl_attribute(DeFogLevel,	float,				0.0f,									ReadWrite,	DirectValue,	"De-fog level",							"")
		pl_attribute(FogColor,		PLGraphics::Color3,	PLGraphics::Color3(1.0f, 1.0f, 1.0f),	ReadWrite,	DirectValue,	"Fog color",							"")
			// Overloaded SNMPostProcess attributes
		pl_attribute(Filename,		PLGeneral::String,	"Data/PostProcesses/ToneMap.pp",		ReadWrite,	ModifyAttr,		"Filename of the post process to use",	"Type='PostProcess'")
		// Constructors
		pl_constructor_1(ParameterConstructor,	PLScene::SceneNode&,	"Parameter constructor",	"")
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
		SNMPostProcessToneMap(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SNMPostProcessToneMap();


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


#endif // __PLPOSTPROCESSEFFECTS_TONEMAP_H__
