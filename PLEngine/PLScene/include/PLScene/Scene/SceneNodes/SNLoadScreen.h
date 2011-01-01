/*********************************************************\
 *  File: SNLoadScreen.h                                 *
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


#ifndef __PLSCENE_SCENENODE_LOADSCREEN_H__
#define __PLSCENE_SCENENODE_LOADSCREEN_H__
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
*    Load screen scene node
*/
class SNLoadScreen : public SNLoadScreenBase {


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

		/**
		*  @brief
		*    Scene node flags (SceneNode flags extension)
		*/
		enum EFlags {
			NoImageBlend = 1<<10	/**< Do not blend the images */
		};
		pl_enum(EFlags)
			pl_enum_base(SNLoadScreenBase::EFlags)
			pl_enum_value(NoImageBlend,	"Do not blend the images")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNLoadScreen, "PLScene", PLScene::SNLoadScreenBase, "Load screen scene node")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(ClearFlags,	pl_flag_type(EClearFlags),	Color|Depth,									ReadWrite,	DirectValue,	"Clear flags",											"")
		pl_attribute(ClearColor,	PLGraphics::Color4,			PLGraphics::Color4(0.0f, 0.0f, 0.0f, 0.0f),		ReadWrite,	DirectValue,	"Clear color (r/g/b/a)",								"")
		pl_attribute(Images,		PLGeneral::uint8,			4,												ReadWrite,	DirectValue,	"Number of images (1-4)",								"Min='1' Max='4'")

		// [TODO] New RTTI usage
//		DEFINE_VAR(PL_VAR_FILENAME,	m_sScreenMaterial[0],	"ScreenMaterial[0]",	"Data/Materials/LoadScreen/0.mat",			"Screen 0 material filename",							"Type='Material Effect Image TextureAni'",	"")
//		DEFINE_VAR(PL_VAR_FILENAME,	m_sScreenMaterial[1],	"ScreenMaterial[1]",	"Data/Materials/LoadScreen/1.mat",			"Screen 1 material filename",							"Type='Material Effect Image TextureAni'",	"")
//		DEFINE_VAR(PL_VAR_FILENAME,	m_sScreenMaterial[2],	"ScreenMaterial[2]",	"Data/Materials/LoadScreen/2.mat",			"Screen 2 material filename",							"Type='Material Effect Image TextureAni'",	"")
//		DEFINE_VAR(PL_VAR_FILENAME,	m_sScreenMaterial[3],	"ScreenMaterial[3]",	"Data/Materials/LoadScreen/3.mat",			"Screen 3 material filename",							"Type='Material Effect Image TextureAni'",	"")
//		DEFINE_VAR(PL_VAR_FILENAME,	m_sBarBackMaterial,		"BarBackMaterial",		"Data/Materials/LoadScreen/BarBack.mat",	"Bar back material filename",							"Type='Material Effect Image TextureAni'",	"")
//		DEFINE_VAR(PL_VAR_FILENAME,	m_sBarMaterial[0],		"BarMaterial[0]",		"Data/Materials/LoadScreen/Bar0.mat",		"Bar 0 material filename",								"Type='Material Effect Image TextureAni'",	"")
//		DEFINE_VAR(PL_VAR_FILENAME,	m_sBarMaterial[1],		"BarMaterial[1]",		"Data/Materials/LoadScreen/Bar1.mat",		"Bar 1 material filename",								"Type='Material Effect Image TextureAni'",	"")

		pl_attribute(ImageX,		float,						0.175f,											ReadWrite,	DirectValue,	"Image x position 'screen space' between 0.0 and 1.0",	"")
		pl_attribute(ImageY,		float,						0.133f,											ReadWrite,	DirectValue,	"Image y position 'screen space' between 0.0 and 1.0",	"")
		pl_attribute(ImageWidth,	float,						0.64f,											ReadWrite,	DirectValue,	"Image width 'screen space' between 0.0 and 1.0",		"")
		pl_attribute(ImageHeight,	float,						0.853f,											ReadWrite,	DirectValue,	"Image height 'screen space' between 0.0 and 1.0",		"")
		pl_attribute(ImageColor,	PLGraphics::Color4,			PLGraphics::Color4(1.0f, 1.0f, 1.0f, 1.0f),		ReadWrite,	DirectValue,	"Image color",											"")
		pl_attribute(BarX,			float,						0.025f,											ReadWrite,	DirectValue,	"Bar x position 'screen space' between 0.0 and 1.0",	"")
		pl_attribute(BarY,			float,						0.083f,											ReadWrite,	DirectValue,	"Bar y position 'screen space' between 0.0 and 1.0",	"")
		pl_attribute(BarWidth,		float,						0.95f,											ReadWrite,	DirectValue,	"Bar width 'screen space' between 0.0 and 1.0",			"")
		pl_attribute(BarHeight,		float,						0.066f,											ReadWrite,	DirectValue,	"Bar height 'screen space' between 0.0 and 1.0",		"")
		pl_attribute(BarColor,		PLGraphics::Color4,			PLGraphics::Color4(1.0f, 1.0f, 1.0f, 1.0f),		ReadWrite,	DirectValue,	"Bar color",											"")
		// Overwritten SceneNode variables
		pl_attribute(Flags,			pl_flag_type(EFlags),		NoCulling,										ReadWrite,	GetSet,			"Flags",												"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		SNLoadScreen();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SNLoadScreen();


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
		PLGeneral::String			m_sScreenMaterial[4];
		PLGeneral::String			m_sBarBackMaterial;
		PLGeneral::String			m_sBarMaterial[2];
		PLRenderer::MaterialHandler	m_cScreenMaterial[4];
		PLRenderer::MaterialHandler	m_cBarBackMaterial;
		PLRenderer::MaterialHandler	m_cBarMaterial[2];
		float						m_fAlpha[4];
		float						m_fBarBackAlpha;
		float						m_fBarAlpha[2];


	//[-------------------------------------------------------]
	//[ Public virtual SceneNode functions                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void DrawPost(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = NULL);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_LOADSCREEN_H__
