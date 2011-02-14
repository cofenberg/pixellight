/*********************************************************\
 *  File: RendererConfigGroup.cpp                        *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLEngine/Config/RendererConfigGroup.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(RendererConfigGroup)
pl_implement_class(RendererConfig)


//[-------------------------------------------------------]
//[ Protected RendererConfigGroup functions               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
RendererConfigGroup::RendererConfigGroup()
{
}

/**
*  @brief
*    Destructor
*/
RendererConfigGroup::~RendererConfigGroup()
{
}


//[-------------------------------------------------------]
//[ Private RendererConfigGroup functions                 ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
RendererConfigGroup::RendererConfigGroup(const RendererConfigGroup &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
RendererConfigGroup &RendererConfigGroup::operator =(const RendererConfigGroup &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}




//[-------------------------------------------------------]
//[ Public RendererConfig functions                       ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
RendererConfig::RendererConfig() :
	// General
	Fullscreen(this),
	ZBufferBits(this),
	StencilBits(this),
	MultisampleAntialiasingSamples(this),
	DefaultShaderLanguage(this),
	// Display mode
	DisplayWidth(this),
	DisplayHeight(this),
	DisplayColorBits(this),
	DisplayFrequency(this),
	// Misc
	VSync(this),
	UseExtensions(this),
	TextureQuality(this),
	TextureMipmaps(this),
	TextureCompression(this)
{
}

/**
*  @brief
*    Destructor
*/
RendererConfig::~RendererConfig()
{
}


//[-------------------------------------------------------]
//[ Private RendererConfig functions                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
RendererConfig::RendererConfig(const RendererConfig &cSource) :
	Fullscreen(this),
	ZBufferBits(this),
	StencilBits(this),
	MultisampleAntialiasingSamples(this),
	DefaultShaderLanguage(this),
	// Display mode
	DisplayWidth(this),
	DisplayHeight(this),
	DisplayColorBits(this),
	DisplayFrequency(this),
	// Misc
	VSync(this),
	UseExtensions(this),
	TextureQuality(this),
	TextureMipmaps(this),
	TextureCompression(this)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
RendererConfig &RendererConfig::operator =(const RendererConfig &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
