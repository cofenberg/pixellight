/*********************************************************\
 *  File: AniInfo.cpp                                    *
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
#include "PLRenderer/Texture/AniInfo.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
AniInfo::AniInfo(const String &sName, ElementManager<AniInfo> *pManager) : Element<AniInfo>(sName, pManager)
{
}

/**
*  @brief
*    Destructor
*/
AniInfo::~AniInfo()
{
}

/**
*  @brief
*    Copy operator
*/
AniInfo &AniInfo::operator =(const AniInfo &cSource)
{
	// Call base functions
	*((Element<AniInfo>*)this) = cSource;
	*(AnimationInfo*)this = cSource;

	// Return a reference to this instance
	return *this;
}



//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
