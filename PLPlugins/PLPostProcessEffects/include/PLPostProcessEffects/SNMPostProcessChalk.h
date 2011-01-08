/*********************************************************\
 *  File: SNMPostProcessChalk.h                          *
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


#ifndef __PLPOSTPROCESSEFFECTS_CHALK_H__
#define __PLPOSTPROCESSEFFECTS_CHALK_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
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
*    Chalk camera scene node post process modifier class
*
*  @remarks
*    Chalk colors.
*/
class SNMPostProcessChalk : public PLCompositing::SNMPostProcess {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SNMPostProcessChalk, "PLPostProcessEffects", PLCompositing::SNMPostProcess, "")
		pl_constructor_1(ParameterConstructor, PLScene::SceneNode&, "Parameter constructor", "")
		pl_attribute(ColorScale,	PLMath::Vector2,	PLMath::Vector2(10.0f, 10.0f),	ReadWrite, DirectValue,	"Color scale (for pixel kernel 0 and 1)",	"")
		pl_attribute(PixelKernel0,	PLMath::Vector2,	PLMath::Vector2( 1.0f,  1.0f),	ReadWrite, DirectValue,	"Pixel kernel 0",							"")
		pl_attribute(PixelKernel1,	PLMath::Vector2,	PLMath::Vector2(-1.0f, -1.0f),	ReadWrite, DirectValue,	"Pixel kernel 1",							"")
		// Overloaded SNMPostProcess variables
		pl_attribute(Filename,		PLGeneral::String,	"Data/PostProcesses/Chalk.pp",	ReadWrite, ModifyAttr,	"Filename of the post process to use",		"Type='PostProcess'")
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
		SNMPostProcessChalk(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SNMPostProcessChalk();


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


#endif // __PLPOSTPROCESSEFFECTS_CHALK_H__
