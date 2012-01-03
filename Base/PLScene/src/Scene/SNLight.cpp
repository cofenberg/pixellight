/*********************************************************\
 *  File: SNLight.cpp                                    *
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
#include "PLScene/Scene/SNLight.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNLight)


//[-------------------------------------------------------]
//[ Public virtual SNLight functions                      ]
//[-------------------------------------------------------]
bool SNLight::IsRenderLight() const
{
	return false;
}

bool SNLight::IsEffectLight() const
{
	return false;
}

bool SNLight::IsPointLight() const
{
	return false;
}

bool SNLight::IsProjectivePointLight() const
{
	return false;
}

bool SNLight::IsSpotLight() const
{
	return false;
}

bool SNLight::IsProjectiveSpotLight() const
{
	return false;
}

bool SNLight::IsDirectionalLight() const
{
	return false;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNLight::SNLight() :
	Color(this),
	CoronaSize(this),
	FlareSize(this),
	ScreenBrighten(this),
	Flags(this)
{
	// Set the internal flag
	m_nInternalFlags |= ClassLight;
}

/**
*  @brief
*    Destructor
*/
SNLight::~SNLight()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
