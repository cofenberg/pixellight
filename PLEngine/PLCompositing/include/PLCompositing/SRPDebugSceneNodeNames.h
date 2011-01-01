/*********************************************************\
 *  File: SRPDebugSceneNodeNames.h                       *
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


#ifndef __PLCOMPOSITING_DEBUG_SCENENODENAMES_H__
#define __PLCOMPOSITING_DEBUG_SCENENODENAMES_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color4.h>
#include "PLCompositing/SRPDebug.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Font;
}
namespace PLScene {
	class VisNode;
	class SceneNode;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene renderer pass drawing just simple scene node names
*/
class SRPDebugSceneNodeNames : public SRPDebug {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene renderer pass flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			AbsoluteNames = 1<<1	/**< Absolute (long) names */
		};
		pl_enum(EFlags)
			pl_enum_base(SRPDebug::EFlags)
			pl_enum_value(AbsoluteNames, "Absolute (long) names")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDebugSceneNodeNames, "PLCompositing", PLCompositing::SRPDebug, "Scene renderer pass drawing just simple scene node names")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(FontName,			PLGeneral::String,		"",											ReadWrite,	DirectValue,	"The used font, if empty the default font is used",											"")
		pl_attribute(FontSize,			PLGeneral::uint32,		0,											ReadWrite,	DirectValue,	"The font size, if null the default font size is used - use 'FontScale' for dynamic scale",	"Max='100'")
		pl_attribute(FontScale,			float,					1.0f,										ReadWrite,	DirectValue,	"The dynamic font scale",																	"Min='0' Max='100'")
		pl_attribute(FontColor,			PLGraphics::Color4,		PLGraphics::Color4(1.0f, 1.0f, 1.0f, 1.0f),	ReadWrite,	DirectValue,	"The dynamic font color",																	"")
		pl_attribute(MaxDrawDistance,	float,					20.0f,										ReadWrite,	DirectValue,	"Maximum draw distance of names to the camera, if less or equal 0, there's no limitation",	"")
		// Overwritten SceneRendererPass variables
		pl_attribute(Flags,				pl_flag_type(EFlags),	0,											ReadWrite,	GetSet,			"Flags",																					"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPDebugSceneNodeNames();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDebugSceneNodeNames();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Draws recursive
		*
		*  @param[in] cFont
		*    Font to use
		*  @param[in] cCullQuery
		*    Cull query to use
		*/
		void DrawRec(PLRenderer::Font &cFont, const PLScene::SQCull &cCullQuery) const;

		/**
		*  @brief
		*    Draws a scene node name
		*
		*  @param[in] cFont
		*    Font to use
		*  @param[in] cCullQuery
		*    Cull query to use
		*  @param[in] cVisNode
		*    Visibility node to use
		*  @param[in] cSceneNode
		*    Scene node to use
		*/
		void DrawName(PLRenderer::Font &cFont, const PLScene::SQCull &cCullQuery, const PLScene::VisNode &cVisNode, const PLScene::SceneNode &cSceneNode) const;


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneRendererPass functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void Draw(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_DEBUG_SCENENODENAMES_H__
