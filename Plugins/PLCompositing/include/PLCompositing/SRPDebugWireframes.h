/*********************************************************\
 *  File: SRPDebugWireframes.h                           *
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


#ifndef __PLCOMPOSITING_DEBUG_WIREFRAMES_H__
#define __PLCOMPOSITING_DEBUG_WIREFRAMES_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color4.h>
#include "PLCompositing/SRPDebug.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract scene renderer pass drawing just simple wireframes
*/
class SRPDebugWireframes : public SRPDebug {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene renderer pass flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			UseDepth = 1<<1	/**< Take the depth buffer into account (lines can be hidden by objects) */
		};
		pl_enum(EFlags)
			pl_enum_base(SRPDebug::EFlags)
			pl_enum_value(UseDepth, "Take the depth buffer into account (lines can be hidden by objects)")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDebugWireframes, "PLCompositing", PLCompositing::SRPDebug, "Abstract scene renderer pass drawing just simple wireframes")
		// Attributes
		pl_attribute(LineWidth,			float,					1.0f,										ReadWrite,	DirectValue,	"Line width (if supported by the the used renderer API)",										"Min='1.0'")
		pl_attribute(LineColor,			PLGraphics::Color4,		PLGraphics::Color4(1.0f, 1.0f, 1.0f, 0.4f),	ReadWrite,	DirectValue,	"Line color",																					"")
		pl_attribute(MaxDrawDistance,	float,					20.0f,										ReadWrite,	DirectValue,	"Maximum draw distance of wireframes to the camera, if less or equal 0, there's no limitation",	"")
			// Overwritten PLScene::SceneRendererPass attributes
		pl_attribute(Flags,				pl_flag_type(EFlags),	0,											ReadWrite,	GetSet,			"Flags",																						"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPDebugWireframes();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDebugWireframes();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_DEBUG_WIREFRAMES_H__
