/*********************************************************\
 *  File: SNCoordinateAxisRotation.h                     *
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


#ifndef __PLSCENE_SCENENODE_COORDINATEAXISROTATION_H__
#define __PLSCENE_SCENENODE_COORDINATEAXISROTATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneNodes/SNCoordinateAxis.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene node that draws coordinate axis (on the lower right by default) of the screen showing the current rotation
*
*  @note
*    - The current view matrix us used to project the coordinate axis into the scene
*/
class SNCoordinateAxisRotation : public SNCoordinateAxis {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNCoordinateAxisRotation, "PLScene", PLScene::SNCoordinateAxis, "Scene node that draws coordinate axis (on the lower right by default) of the screen showing the current rotation")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		// Overwritten SceneNode variables
		pl_attribute(Flags,	pl_flag_type(EFlags),	NoCulling,	ReadWrite,	GetSet,	"Flags",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNCoordinateAxisRotation();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNCoordinateAxisRotation();


	//[-------------------------------------------------------]
	//[ Public virtual SceneNode functions                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void DrawPost(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = nullptr);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_COORDINATEAXISROTATION_H__
