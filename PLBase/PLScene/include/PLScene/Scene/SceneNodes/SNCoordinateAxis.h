/*********************************************************\
 *  File: SNCoordinateAxis.h                             *
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


#ifndef __PLSCENE_SCENENODE_COORDINATEAXIS_H__
#define __PLSCENE_SCENENODE_COORDINATEAXIS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color4.h>
#include "PLScene/Scene/SceneNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract base scene node for coordinate axis visualisation
*/
class SNCoordinateAxis : public SceneNode {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node flags (SceneNode flags extension)
		*/
		enum EFlags {
			DepthTest = 1<<10,	/**< Perform a depth test */
			NoXText   = 1<<11,	/**< Do NOT draw the x-axis text  */
			NoYText   = 1<<12,	/**< Do NOT draw the y-axis text  */
			NoZText   = 1<<13	/**< Do NOT draw the z-axis text  */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneNode::EFlags)
			pl_enum_value(DepthTest,	"Perform a depth test")
			pl_enum_value(NoXText,		"Do NOT draw the x-axis text")
			pl_enum_value(NoYText,		"Do NOT draw the y-axis text")
			pl_enum_value(NoZText,		"Do NOT draw the z-axis text")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNCoordinateAxis, "PLScene", PLScene::SceneNode, "Abstract base scene node for coordinate axis visualisation")
		// Attributes
		pl_attribute(Width,		float,					1.0f,										ReadWrite,	DirectValue,	"Line width (if supported by the the used renderer API)",	"Min='1.0'")
		pl_attribute(XColor,	PLGraphics::Color4,		PLGraphics::Color4(1.0f, 0.0f, 0.0f, 1.0f),	ReadWrite,	DirectValue,	"Color of the x-axis",										"")
		pl_attribute(YColor,	PLGraphics::Color4,		PLGraphics::Color4(0.0f, 1.0f, 0.0f, 1.0f),	ReadWrite,	DirectValue,	"Color of the y-axis",										"")
		pl_attribute(ZColor,	PLGraphics::Color4,		PLGraphics::Color4(0.0f, 0.0f, 1.0f, 1.0f),	ReadWrite,	DirectValue,	"Color of the z-axis",										"")
			// Overwritten SceneNode attributes
		pl_attribute(Flags,		pl_flag_type(EFlags),	0,											ReadWrite,	GetSet,			"Flags",													"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default Constructor
		*/
		PLS_API SNCoordinateAxis();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNCoordinateAxis();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_COORDINATEAXIS_H__
