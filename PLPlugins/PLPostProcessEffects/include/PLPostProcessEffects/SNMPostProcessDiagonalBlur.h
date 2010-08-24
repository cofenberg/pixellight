/*********************************************************\
 *  File: SNMPostProcessDiagonalBlur.h                   *
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


#ifndef __PLPOSTPROCESSEFFECTS_DIAGONALBLUR_H__
#define __PLPOSTPROCESSEFFECTS_DIAGONALBLUR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
#include <PLScene/Scene/SceneNodeModifiers/SNMPostProcess.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Diagonal blur camera scene node post process modifier class
*
*  @remarks
*    Performs a diagonal blur.
*/
class SNMPostProcessDiagonalBlur : public PLScene::SNMPostProcess {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SNMPostProcessDiagonalBlur, "PLPostProcessEffects", PLScene::SNMPostProcess, "")
		pl_constructor_1(ParameterConstructor, PLScene::SceneNode&, "Parameter constructor", "")
		pl_attribute(ColorScale,	float,				4.0f,									ReadWrite, DirectValue,	"Color scale",							"")
		pl_attribute(PixelKernel0,	PLMath::Vector2,	PLMath::Vector2( 2.0f, 2.0f),			ReadWrite, DirectValue,	"Pixel kernel 0",						"")
		pl_attribute(PixelKernel1,	PLMath::Vector2,	PLMath::Vector2( 4.0f, 4.0f),			ReadWrite, DirectValue,	"Pixel kernel 1",						"")
		pl_attribute(PixelKernel2,	PLMath::Vector2,	PLMath::Vector2(-6.0f, 6.0f),			ReadWrite, DirectValue,	"Pixel kernel 2",						"")
		pl_attribute(PixelKernel3,	PLMath::Vector2,	PLMath::Vector2( 8.0f, 8.0f),			ReadWrite, DirectValue,	"Pixel kernel 3",						"")
		// Overloaded SNMPostProcess variables
		pl_attribute(Filename,		PLGeneral::String,	"Data/PostProcesses/DiagonalBlur.pp",	ReadWrite, ModifyAttr,	"Filename of the post process to use",	"Type='PostProcess'")
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
		SNMPostProcessDiagonalBlur(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SNMPostProcessDiagonalBlur();


	//[-------------------------------------------------------]
	//[ Public virtual PLScene::SNMPostProcess functions      ]
	//[-------------------------------------------------------]
	public:
		virtual void SetParameters();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects


#endif // __PLPOSTPROCESSEFFECTS_DIAGONALBLUR_H__
