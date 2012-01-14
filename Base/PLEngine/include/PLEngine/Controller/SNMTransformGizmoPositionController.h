/*********************************************************\
 *  File: SNMTransformGizmoPositionController.h          *
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


#ifndef __PLENGINE_SCENENODEMODIFIER_TRANSFORMGIZMOPOSITIONCONTROLLER_H__
#define __PLENGINE_SCENENODEMODIFIER_TRANSFORMGIZMOPOSITIONCONTROLLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneNodeModifiers/SNMTransformGizmoPosition.h>
#include "PLEngine/PLEngine.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Position transform gizmo controller scene node modifier
*/
class SNMTransformGizmoPositionController : public PLScene::SNMTransformGizmoPosition {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, SNMTransformGizmoPositionController, "PLEngine", PLScene::SNMTransformGizmoPosition, "Position transform gizmo controller scene node modifier")
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
		PL_API SNMTransformGizmoPositionController(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~SNMTransformGizmoPositionController();


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SNMTransformGizmo functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void UpdateSelection(PLRenderer::Renderer &cRenderer, const PLScene::VisNode &cVisNode) override;
		virtual void PerformTransform() override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_SCENENODEMODIFIER_TRANSFORMGIZMOPOSITIONCONTROLLER_H__
