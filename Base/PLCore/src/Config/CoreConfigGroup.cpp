/*********************************************************\
 *  File: CoreConfigGroup.cpp                            *
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
#include "PLCore/Config/CoreConfigGroup.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(CoreConfigGroup)
pl_implement_class(CoreConfig)
pl_implement_class(FrontendConfig)


// CoreConfigGroup
//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
CoreConfigGroup::CoreConfigGroup()
{
}

/**
*  @brief
*    Destructor
*/
CoreConfigGroup::~CoreConfigGroup()
{
}




// CoreConfig
//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
CoreConfig::CoreConfig() :
	FirstRun(this),
	Language(this)
{
}

/**
*  @brief
*    Destructor
*/
CoreConfig::~CoreConfig()
{
}




// FrontendConfig
//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
FrontendConfig::FrontendConfig() :
	X(this),
	Y(this),
	Width(this),
	Height(this)
{
}

/**
*  @brief
*    Destructor
*/
FrontendConfig::~FrontendConfig()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
