/*********************************************************\
 *  File: SNMPositionLinearAnimation.h                   *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_POSITIONLINEARANIMATION_H__
#define __PLSCENE_SCENENODEMODIFIER_POSITIONLINEARANIMATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include <PLMath/Vector3.h>
#include "PLScene/Scene/SceneNodeModifiers/SNMTransform.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linear position animation scene node modifier class
*
*  @remarks
*    Animates the position of the scene nodes over time.
*/
class SNMPositionLinearAnimation : public SNMTransform {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Automatic vector type
		*/
		enum EAutoVector {
			None  = 0,	/**< No automatic movement vector */
			XAxis = 1,	/**< Use the current x (left) axis vector automatically as movement vector */
			YAxis = 2,	/**< Use the current y (up) axis vector automatically as movement vector */
			ZAxis = 3	/**< Use the current z (view) axis vector automatically as movement vector */
		};
		pl_enum(EAutoVector)
			pl_enum_value(None,		"No automatic movement vector")
			pl_enum_value(XAxis,	"Use the current x (left) axis vector automatically as movement vector")
			pl_enum_value(YAxis,	"Use the current y (up) axis vector automatically as movement vector")
			pl_enum_value(ZAxis,	"Use the current z (view) axis vector automatically as movement vector")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMPositionLinearAnimation, "PLScene", PLScene::SNMTransform, "Linear position animation scene node modifier class")
		pl_constructor_1(ParameterConstructor, SceneNode&, "Parameter constructor", "")
		pl_attribute(AutoVector,	pl_enum_type(EAutoVector),	None,								ReadWrite,	DirectValue,	"Automatic vector type",	"")
		pl_attribute(Vector,		PLMath::Vector3,			PLMath::Vector3(1.0f, 1.0f, 1.0f),	ReadWrite,	DirectValue,	"Movement vector",			"")
		pl_attribute(Speed,			float,						1.0f,								ReadWrite,	DirectValue,	"Movement speed",			"")
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
		PLS_API SNMPositionLinearAnimation(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMPositionLinearAnimation();


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNodeModifier functions         ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual void OnActivate(bool bActivate);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node modifier needs to be updated
		*/
		void NotifyUpdate();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerUpdate;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_POSITIONLINEARANIMATION_H__
