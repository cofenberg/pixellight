/*********************************************************\
 *  File: SNLoadScreenPL.h                               *
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


#ifndef __PLSCENE_SCENENODE_LOADSCREENPL_H__
#define __PLSCENE_SCENENODE_LOADSCREENPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Material/MaterialHandler.h>
#include "PLScene/Scene/SceneNodes/SNLoadScreenBase.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PixelLight load screen scene node
*/
class SNLoadScreenPL : public SNLoadScreenBase {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Clear flags
		*/
		enum EClearFlags {
			Color   = 1<<0,	/**< Clear color buffer */
			Depth   = 1<<1,	/**< Clear depth buffer */
			Stencil = 1<<2	/**< Clear stencil buffer */
		};
		pl_enum(EClearFlags)
			pl_enum_value(Color,	"Clear color buffer")
			pl_enum_value(Depth,	"Clear depth buffer")
			pl_enum_value(Stencil,	"Clear stencil buffer")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNLoadScreenPL, "PLScene", PLScene::SNLoadScreenBase, "Load screen scene node")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(ClearFlags,	pl_flag_type(EClearFlags),	Color|Depth,								ReadWrite,	DirectValue,	"Clear flags",				"")
		pl_attribute(ClearColor,	PLGraphics::Color4,			PLGraphics::Color4(0.0f, 0.0f, 0.0f, 0.0f),	ReadWrite,	DirectValue,	"Clear color (r/g/b/a)",	"")
		// Overwritten SceneNode variables
		pl_attribute(Flags,			pl_flag_type(EFlags),		NoCulling,									ReadWrite,	GetSet,			"Flags",					"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		SNLoadScreenPL();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SNLoadScreenPL();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Free's the used materials
		*/
		void FreeMaterials();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::MaterialHandler	m_cLogoMaterial;


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


#endif // __PLSCENE_SCENENODE_LOADSCREENPL_H__
