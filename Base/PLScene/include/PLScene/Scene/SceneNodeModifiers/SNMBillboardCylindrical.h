/*********************************************************\
 *  File: SNMBillboardCylindrical.h                      *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLSCENE_SCENENODEMODIFIER_BILLBOARDCYLINDRICAL_H__
#define __PLSCENE_SCENENODEMODIFIER_BILLBOARDCYLINDRICAL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include "PLScene/Scene/SceneNodeModifiers/SNMBillboard.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLScene {
	class VisNode;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Cylindrical (axis aligned) billboard scene node modifier class
*
*  @note
*    - The scale of the owner scene node is taken into account
*/
class SNMBillboardCylindrical : public SNMBillboard {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMBillboardCylindrical, "PLScene", PLScene::SNMBillboard, "Cylindrical (axis aligned) billboard scene node modifier class")
		// Attributes
		pl_attribute(UpVector,	PLMath::Vector3,	PLMath::Vector3::UnitY,	ReadWrite,	DirectValue,	"Up vector",	"")
		// Constructors
		pl_constructor_1(ParameterConstructor,	SceneNode&,	"Parameter constructor",	"")
		// Slots
		pl_slot_1(OnAddedToVisibilityTree,	VisNode&,	"Called when the owner scene node was added to a visibility tree, visibility node which is representing the owner scene node within the visibility tree as first parameter",	"")
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
		PLS_API SNMBillboardCylindrical(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMBillboardCylindrical();


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNodeModifier functions         ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual void OnActivate(bool bActivate) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Builds a transform matrix
		*
		*  @param[in]  mView
		*    View matrix
		*  @param[in]  mWorld
		*    World matrix
		*  @param[out] mTransform
		*    Receives the new world transform matrix
		*/
		void BuildTransformMatrix(const PLMath::Matrix4x4 &mView, const PLMath::Matrix4x4 &mWorld, PLMath::Matrix3x4 &mTransform);

		/**
		*  @brief
		*    Called when the owner scene node was added to a visibility tree
		*
		*  @param[in] cVisNode
		*    Visibility node which is representing the owner scene node within the visibility tree
		*/
		void OnAddedToVisibilityTree(VisNode &cVisNode);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_BILLBOARDCYLINDRICAL_H__
