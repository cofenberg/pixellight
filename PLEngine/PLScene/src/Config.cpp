/*********************************************************\
 *  File: Config.cpp                                     *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLGeneral/System/System.h>
#include <PLGeneral/System/Thread.h>
#include <PLRenderer/RendererContext.h>
#include "PLScene/Config.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(EngineConfigGroup)
pl_implement_class(EngineGeneralConfig)
pl_implement_class(EngineDebugConfig)
pl_implement_class(EngineGraphicConfig)


// EngineConfigGroup
//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
EngineConfigGroup::EngineConfigGroup()
{
}

/**
*  @brief
*    Destructor
*/
EngineConfigGroup::~EngineConfigGroup()
{
}




// EngineGeneralConfig
//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
EngineGeneralConfig::EngineGeneralConfig() :
	ConsoleActivated(this),
	MaxTimeDifference(this),
	FPSLimit(this)
{
}

/**
*  @brief
*    Destructor
*/
EngineGeneralConfig::~EngineGeneralConfig()
{
}


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
float EngineGeneralConfig::GetMaxTimeDifference() const
{
	return Timing::GetInstance()->GetMaxTimeDifference();
}

void EngineGeneralConfig::SetMaxTimeDifference(float fValue) const
{
	Timing::GetInstance()->SetMaxTimeDifference(fValue);
}

float EngineGeneralConfig::GetFPSLimit() const
{
	return Timing::GetInstance()->GetFPSLimit();
}

void EngineGeneralConfig::SetFPSLimit(float fValue) const
{
	Timing::GetInstance()->SetFPSLimit(fValue);
}




// EngineDebugConfig
//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
EngineDebugConfig::EngineDebugConfig() :
	ShowFPS(this),
	ShowCoordinateAxis(this),
	ShowXZPlane(this),
	ShowXYPlane(this),
	ShowYZPlane(this),
	NormalScale(this)
{
}

/**
*  @brief
*    Destructor
*/
EngineDebugConfig::~EngineDebugConfig()
{
}




// EngineGraphicConfig
//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
EngineGraphicConfig::EngineGraphicConfig() :
	RendererAPI(this),
	RendererMode(this),
	DefaultFontTexture(this),
	DefaultFontTextureSize(this),
	// [DEBUG] Remove this later!
	SlopeScaleDepthBias(this),
	DepthBias(this)
{
}

/**
*  @brief
*    Destructor
*/
EngineGraphicConfig::~EngineGraphicConfig()
{
}

// [TODO] Get a correct renderer context
// [TODO] New font system
// DefaultFontTexture, DefaultFontTextureSize
/*	if (sVar == "DefaultFontTexture" || sVar == "DefaultFontTextureSize") {
	if (PL::GetRendererContext()) {
		PLRenderer::FontManager &cFontManager = PL::GetRendererContext()->GetFontManager();
		cFontManager.SetDefaultFontTexture(cFontManager.GetFontTexture(m_sDefaultFontTexture, m_nDefaultFontTextureSize));
	}

// DefaultFont3D, DefaultFont3DSize
} else if (sVar == "DefaultFont3D" || sVar == "DefaultFont3DSize") {
	if (PL::GetRendererContext()) {
		PLRenderer::FontManager &cFontManager = PL::GetRendererContext()->GetFontManager();
		cFontManager.SetDefaultFont3D(cFontManager.GetFont3D(m_sDefaultFont3D, m_nDefaultFont3DSize));
	}
}*/


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
