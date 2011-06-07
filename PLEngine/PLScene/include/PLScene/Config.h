/*********************************************************\
 *  File: Config.h                                       *
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


#ifndef __PLSCENE_CONFIG_H__
#define __PLSCENE_CONFIG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Config/Config.h>
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Engine general configuration 'collection' class
*
*  @remarks
*    ALL engine configuration classes are derived from this class.
*    Use PLGeneral::Config::GetInstance()->Save("Config/Engine.cfg", "EngineConfigGroup") to save
*    ONLY all engine configuration classes.
*/
class EngineConfigGroup : public PLCore::ConfigGroup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, EngineConfigGroup, "PLScene", PLCore::ConfigGroup, "Engine general configuration 'collection' class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		EngineConfigGroup();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~EngineConfigGroup();


};

/**
*  @brief
*    Engine general configuration classes
*/
class EngineGeneralConfig : public EngineConfigGroup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, EngineGeneralConfig, "PLScene", PLScene::EngineConfigGroup, "Engine general configuration classes")
		// Attributes
		pl_attribute(ConsoleActivated,		bool,				true,	ReadWrite,	DirectValue,	"Is the console active?",																				"")
		pl_attribute(MaxTimeDifference,		float,				0.15f,	ReadWrite,	GetSet,			"The maximum time difference since the last frame in seconds",											"Min='0.0001'")
		pl_attribute(FPSLimit,				float,				0.0f,	ReadWrite,	GetSet,			"FPS limit, 0 if there's no FPS limitation",															"Min='0.0'")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API EngineGeneralConfig();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~EngineGeneralConfig();


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API float GetMaxTimeDifference() const;
		PLS_API void SetMaxTimeDifference(float fValue) const;
		PLS_API float GetFPSLimit() const;
		PLS_API void SetFPSLimit(float fValue) const;


};

/**
*  @brief
*    Engine debug configuration classes
*/
class EngineDebugConfig : public EngineConfigGroup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, EngineDebugConfig, "PLScene", PLScene::EngineConfigGroup, "Engine debug configuration classes")
		// Attributes
		pl_attribute(ShowFPS,				bool,	false,	ReadWrite,	DirectValue,	"Show FPS?",						"")
		pl_attribute(ShowCoordinateAxis,	bool,	false,	ReadWrite,	DirectValue,	"Show coordinate axis?",			"")
		pl_attribute(ShowXZPlane,			bool,	false,	ReadWrite,	DirectValue,	"Show x/z plane?",					"")
		pl_attribute(ShowXYPlane,			bool,	false,	ReadWrite,	DirectValue,	"Show x/y plane?",					"")
		pl_attribute(ShowYZPlane,			bool,	false,	ReadWrite,	DirectValue,	"Show y/z plane?",					"")
		pl_attribute(NormalScale,			float,	0.1f,	ReadWrite,	DirectValue,	"Scale of normals when visualized",	"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API EngineDebugConfig();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~EngineDebugConfig();


};

/**
*  @brief
*    Engine graphics configuration classes
*/
class EngineGraphicConfig : public EngineConfigGroup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, EngineGraphicConfig, "PLScene", PLScene::EngineConfigGroup, "Engine graphics configuration classes")
		// Attributes
		pl_attribute(RendererAPI,				PLGeneral::String,							"PLRendererOpenGL::Renderer",				ReadWrite,	DirectValue,	"The used renderer API",													"")
		pl_attribute(RendererMode,				pl_enum_type(PLRenderer::Renderer::EMode),	PLRenderer::Renderer::ModeBoth,				ReadWrite,	DirectValue,	"The mode the renderer should run in (fixed functions, shaders or both)",	"")
		pl_attribute(DefaultFontTexture,		PLGeneral::String,							"Data/Fonts/LinLibertine_Re-2.7.9.9.otf",	ReadWrite,	DirectValue,	"The default texture font",													"")
		pl_attribute(DefaultFontTextureSize,	PLGeneral::uint32,							15,											ReadWrite,	DirectValue,	"The default texture font size",											"Max='100'")

		// [DEBUG] Remove this later!
		pl_attribute(SlopeScaleDepthBias,		float,										-0.1f,										ReadWrite,	DirectValue,	"[DEBUG] Slope scale depth bias",											"")
		pl_attribute(DepthBias,					float,										-0.1f,										ReadWrite,	DirectValue,	"[DEBUG] Depth bias",														"")

		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API EngineGraphicConfig();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~EngineGraphicConfig();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_CONFIG_H__
