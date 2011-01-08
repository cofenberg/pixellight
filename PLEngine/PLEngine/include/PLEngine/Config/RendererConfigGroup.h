/*********************************************************\
 *  File: RendererConfigGroup.h                          *
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


#ifndef __PLENGINE_CONFIGGROUP_H__
#define __PLENGINE_CONFIGGROUP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Config/Config.h>
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
*    Renderer configuration 'collection' class
*
*  @remarks
*    ALL renderer configuration classes are derived from this class.
*    Use cConfig.Save("Config/Renderer.cfg", "RendererConfigGroup") to save
*    ONLY all renderer configuration classes.
*/
class RendererConfigGroup : public PLCore::ConfigGroup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, RendererConfigGroup, "PLEngine", PLCore::ConfigGroup, "Renderer configuration 'collection' class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PL_API RendererConfigGroup();

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~RendererConfigGroup();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		RendererConfigGroup(const RendererConfigGroup &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		RendererConfigGroup &operator =(const RendererConfigGroup &cSource);


};

/**
*  @brief
*    Renderer configuration class
*/
class RendererConfig : public RendererConfigGroup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, RendererConfig, "PLEngine", PLEngine::RendererConfigGroup, "Renderer configuration class")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		// General
		pl_attribute(Fullscreen,						bool,				false,	ReadWrite,	DirectValue,	"Fullscreen mode?",																																															"")
		pl_attribute(ZBufferBits,						PLGeneral::uint32,	24,		ReadWrite,	DirectValue,	"Z buffer bits (just a hint)",																																												"")
		pl_attribute(StencilBits,						PLGeneral::uint32,	8,		ReadWrite,	DirectValue,	"Stencil buffer bits (just a hint)",																																										"")
		pl_attribute(MultisampleAntialiasingSamples,	PLGeneral::uint32,	4,		ReadWrite,	DirectValue,	"Number of multisample antialiasing samples per pixel (just a hint)",																																		"")
		pl_attribute(DefaultShaderLanguage,				PLGeneral::String,	"",		ReadWrite,	DirectValue,	"The name of the default shader language of the renderer (for example \"GLSL\" or \"Cg\"), if the string is empty, the default is chosen by the renderer implementation, this information is just a hint",	"")
		// Display mode
		pl_attribute(DisplayWidth,						PLGeneral::uint32,	800,	ReadWrite,	DirectValue,	"Display width",																																															"")
		pl_attribute(DisplayHeight,						PLGeneral::uint32,	600,	ReadWrite,	DirectValue,	"Display height",																																															"")
		pl_attribute(DisplayColorBits,					PLGeneral::uint32,	32,		ReadWrite,	DirectValue,	"Color bits",																																																"")
		pl_attribute(DisplayFrequency,					PLGeneral::uint32,	0,		ReadWrite,	DirectValue,	"Display frequency",																																														"")
		// Misc
		pl_attribute(VSync,								bool,				false,	ReadWrite,	DirectValue,	"Use vertical synchronization?",																																											"")
		pl_attribute(UseExtensions,						bool,				true,	ReadWrite,	DirectValue,	"Use extensions?",																																															"")
		pl_attribute(TextureQuality,					float,				1.0f,	ReadWrite,	DirectValue,	"Texture quality",																																															"Min='0.0' Max='1.0'")
		pl_attribute(TextureMipmaps,					bool,				true,	ReadWrite,	DirectValue,	"Use texture mipmaps by default?",																																											"")
		pl_attribute(TextureCompression,				bool,				true,	ReadWrite,	DirectValue,	"Use texture compression by default?",																																										"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PL_API RendererConfig();

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~RendererConfig();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		RendererConfig(const RendererConfig &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		RendererConfig &operator =(const RendererConfig &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_CONFIGGROUP_H__
