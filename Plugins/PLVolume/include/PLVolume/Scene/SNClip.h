/*********************************************************\
 *  File: SNClip.h                                       *
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


#ifndef __PLVOLUME_SNCLIP_H__
#define __PLVOLUME_SNCLIP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color4.h>
#include <PLScene/Scene/SceneNode.h>
#include "PLVolume/PLVolume.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolume {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract clip scene node base class
*/
class SNClip : public PLScene::SceneNode {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node flags (PLScene::SceneNode flags extension)
		*/
		enum EFlags {
			InvertClipping = 1<<10	/**< Invert clipping */
		};
		pl_enum(EFlags)
			pl_enum_base(PLScene::SceneNode::EFlags)
			pl_enum_value(InvertClipping, "Invert clipping")
		pl_enum_end

		/**
		*  @brief
		*    Scene node debug flags (PLScene::SceneNode debug flags extension)
		*/
		enum EDebugFlags {
			DebugNoVisualization = 1<<8	/**< Do not draw the visualization */
		};
		pl_enum(EDebugFlags)
			pl_enum_base(PLScene::SceneNode::EDebugFlags)
			pl_enum_value(DebugNoVisualization, "Do not draw the visualization")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUME_RTTI_EXPORT, SNClip, "PLVolume", PLScene::SceneNode, "Abstract clip scene node base class")
		// Attributes
		pl_attribute(DebugColorPositive,	PLGraphics::Color4,			PLGraphics::Color4(0.0f, 1.0f, 0.0f, 0.1f),	ReadWrite,	DirectValue,	"Debug color for the view side allowing to see the non-clipped rest",	"")
		pl_attribute(DebugColorNegative,	PLGraphics::Color4,			PLGraphics::Color4(1.0f, 0.0f, 0.0f, 0.1f),	ReadWrite,	DirectValue,	"Debug color for the view side allowing to see the clipped part",		"")
			// Overwritten PLScene::SceneNode attributes
		pl_attribute(Flags,					pl_flag_type(EFlags),		0,											ReadWrite,	GetSet,			"Flags",																"")
		pl_attribute(DebugFlags,			pl_flag_type(EDebugFlags),	0,											ReadWrite,	GetSet,			"Debug flags",															"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLVOLUME_API SNClip();

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUME_API virtual ~SNClip();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume


#endif // __PLVOLUME_SNCLIP_H__
