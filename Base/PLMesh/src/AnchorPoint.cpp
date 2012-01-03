/*********************************************************\
 *  File: AnchorPoint.cpp                                *
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
#include "PLMesh/AnchorPoint.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLMesh {


//[-------------------------------------------------------]
//[ Public AnchorPoint functions                          ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
AnchorPoint::AnchorPoint(const String &sName, bool bType, uint32 nID, AnchorPointManager *pManager) :
	Element<AnchorPoint>(sName, pManager),
	m_bType(bType),
	m_nID(nID)
{
}

/**
*  @brief
*    Destructor
*/
AnchorPoint::~AnchorPoint()
{
}

/**
*  @brief
*    Returns the anchor type
*/
bool AnchorPoint::GetType() const
{
	return m_bType;
}

/**
*  @brief
*    Sets the anchor type
*/
void AnchorPoint::SetType(bool bType)
{
	m_bType = bType;
}

/**
*  @brief
*    Returns the anchors vertex/bone ID
*/
uint32 AnchorPoint::GetID() const
{
	return m_nID;
}

/**
*  @brief
*    Sets the anchors vertex/bone ID
*/
void AnchorPoint::SetID(uint32 nID)
{
	m_nID = nID;
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Element functions              ]
//[-------------------------------------------------------]
AnchorPoint &AnchorPoint::operator =(const AnchorPoint &cSource)
{
	// Call base function
	*static_cast<Element<AnchorPoint>*>(this) = cSource;

	// Copy data
	m_bType = cSource.m_bType;
	m_nID   = cSource.m_nID;

	// Return pointer
	return *this;
}




//[-------------------------------------------------------]
//[ Public AnchorPointManager functions                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
AnchorPointManager::AnchorPointManager()
{
}

/**
*  @brief
*    Destructor
*/
AnchorPointManager::~AnchorPointManager()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ElementManager functions      ]
//[-------------------------------------------------------]
AnchorPoint *AnchorPointManager::CreateElement(const String &sName)
{
	return new AnchorPoint(sName, 0, 0, this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh
