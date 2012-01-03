/*********************************************************\
 *  File: ConfigGroup.cpp                                *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Application/Config.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(ConfigGroup)
pl_implement_class(Config)


//[-------------------------------------------------------]
//[ Protected ConfigGroup functions                       ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
ConfigGroup::ConfigGroup()
{
}

/**
*  @brief
*    Destructor
*/
ConfigGroup::~ConfigGroup()
{
}


//[-------------------------------------------------------]
//[ Private ConfigGroup functions                         ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
ConfigGroup::ConfigGroup(const ConfigGroup &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
ConfigGroup &ConfigGroup::operator =(const ConfigGroup &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}




//[-------------------------------------------------------]
//[ Public Config functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
Config::Config() :
	// General
	RendererAPI(this),
	RendererMode(this),
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
	SwapInterval(this),
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
Config::~Config()
{
}


//[-------------------------------------------------------]
//[ Private Config functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Config::Config(const Config &cSource) :
	// General
	RendererAPI(this),
	RendererMode(this),
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
	SwapInterval(this),
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
Config &Config::operator =(const Config &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
