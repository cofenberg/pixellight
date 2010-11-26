/*********************************************************\
 *  File: SNMPostProcessCrazyColors.h                    *
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


#ifndef __PLPOSTPROCESSEFFECTS_CRAZYCOLORS_H__
#define __PLPOSTPROCESSEFFECTS_CRAZYCOLORS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
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
*    Crazy colors camera scene node post process modifier class
*
*  @remarks
*    Crazy colors.
*/
class SNMPostProcessCrazyColors : public PLCompositing::SNMPostProcess {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SNMPostProcessCrazyColors, "PLPostProcessEffects", PLCompositing::SNMPostProcess, "")
		pl_constructor_1(ParameterConstructor, PLScene::SceneNode&, "Parameter constructor", "")
		pl_slot_0		(OnSceneNodeUpdate,							 "Slot for SceneNode::EventUpdate", "")
		pl_attribute(ColorScaleX,	PLMath::Vector3,	PLMath::Vector3( 2.0f,  2.0f,  2.0f), ReadWrite, DirectValue,	"Color scale x",						"")
		pl_attribute(ColorSpeedX,	PLMath::Vector3,	PLMath::Vector3( 1.0f,  1.0f,  1.0f), ReadWrite, DirectValue,	"Color speed x",						"")
		pl_attribute(ColorOffsetX,	PLMath::Vector3,	PLMath::Vector3(10.0f, 20.0f, 30.0f), ReadWrite, DirectValue,	"Color offset x",						"")
		pl_attribute(ColorScaleY,	PLMath::Vector3,	PLMath::Vector3( 2.0f,  2.0f,  2.0f), ReadWrite, DirectValue,	"Color scale y",						"")
		pl_attribute(ColorSpeedY,	PLMath::Vector3,	PLMath::Vector3( 2.0f,  2.5f,  3.0f), ReadWrite, DirectValue,	"Color speed y",						"")
		pl_attribute(ColorOffsetY,	PLMath::Vector3,	PLMath::Vector3(10.0f, 20.0f, 30.0f), ReadWrite, DirectValue,	"Color offset y",						"")
		// Overloaded SNMPostProcess variables
		pl_attribute(Filename,		PLGeneral::String,	"Data/PostProcesses/CrazyColors.pp",  ReadWrite, ModifyAttr,	"Filename of the post process to use",	"Type='PostProcess'")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		virtual void SetFlags(PLGeneral::uint32 nValue);


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
		SNMPostProcessCrazyColors(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SNMPostProcessCrazyColors();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void OnSceneNodeUpdate();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Private data
		float m_fTimer;


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


#endif // __PLPOSTPROCESSEFFECTS_CRAZYCOLORS_H__
