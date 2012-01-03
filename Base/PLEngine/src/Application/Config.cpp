/*********************************************************\
 *  File: Config.cpp                                     *
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
#include <PLCore/Tools/Timing.h>
#include "PLEngine/Application/Config.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(ConfigGroup)
pl_implement_class(Config)
pl_implement_class(DebugConfig)


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
	ConsoleActivated(this),
	MaxTimeDifference(this),
	FPSLimit(this)
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
//[ Public Config RTTI get/set functions                  ]
//[-------------------------------------------------------]
float Config::GetMaxTimeDifference() const
{
	return PLCore::Timing::GetInstance()->GetMaxTimeDifference();
}

void Config::SetMaxTimeDifference(float fValue) const
{
	PLCore::Timing::GetInstance()->SetMaxTimeDifference(fValue);
}

float Config::GetFPSLimit() const
{
	return PLCore::Timing::GetInstance()->GetFPSLimit();
}

void Config::SetFPSLimit(float fValue) const
{
	PLCore::Timing::GetInstance()->SetFPSLimit(fValue);
}




//[-------------------------------------------------------]
//[ Public DebugConfig functions                          ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
DebugConfig::DebugConfig() :
	ShowFPS(this),
	ShowCoordinateAxis(this),
	ShowXZPlane(this),
	ShowXYPlane(this),
	ShowYZPlane(this)
{
}

/**
*  @brief
*    Destructor
*/
DebugConfig::~DebugConfig()
{
}




//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
