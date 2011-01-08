/*********************************************************\
 *  File: SNMDrawRectangle.h                             *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_DRAWRECTANGLE_H__
#define __PLSCENE_SCENENODEMODIFIER_DRAWRECTANGLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include <PLGraphics/Color/Color4.h>
#include "PLScene/Scene/SceneNodeModifiers/SNMDraw.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Renderer;
}
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
*    Scene node modifier class drawing a 2D rectangle around the owner scene node
*/
class SNMDrawRectangle : public SNMDraw {


	//[-------------------------------------------------------]
	//[ Public definition                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node modifier flags (SceneNodeModifier flags extension)
		*/
		enum EFlags {
			DepthTest = 1<<2	/**< Perform a depth test */
		};
		pl_enum(EFlags)
			pl_enum_base(SNMDraw::EFlags)
			pl_enum_value(DepthTest, "Perform a depth test")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMDrawRectangle, "PLScene", PLScene::SNMDraw, "Scene node modifier class drawing a 2D rectangle around the owner scene node")
		pl_constructor_1(ParameterConstructor, SceneNode&, "Parameter constructor", "")
		pl_attribute(Width,	float,					1.0f,										ReadWrite,	DirectValue,	"Rectangle width (if supported by the the used renderer API, if not may have no effect)",	"Min='1.0'")
		pl_attribute(Color,	PLGraphics::Color4,		PLGraphics::Color4(1.0f, 1.0f, 1.0f, 1.0f),	ReadWrite,	DirectValue,	"Rectangle color (r/g/b/a)",																"")
		// Overwritten SceneNodeModifier variables
		pl_attribute(Flags,	pl_flag_type(EFlags),	0,											ReadWrite,	GetSet,			"Flags",																					"")
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
		PLS_API SNMDrawRectangle(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMDrawRectangle();


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
		*    Called on scene node transparent draw
		*
		*  @param[in] cRenderer
		*    The used renderer
		*  @param[in] pVisNode
		*    The current visibility node of this scene node, can be a null pointer
		*/
		void NotifyDrawTransparent(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<PLRenderer::Renderer &, const VisNode *> EventHandlerDrawTransparent;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_DRAWRECTANGLE_H__
