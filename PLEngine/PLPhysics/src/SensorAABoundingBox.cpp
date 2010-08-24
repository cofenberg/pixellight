/*********************************************************\
 *  File: SensorAABoundingBox.cpp                        *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLPhysics/SensorAABoundingBox.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
SensorAABoundingBox::~SensorAABoundingBox()
{
}

/**
*  @brief
*    Returns the minimum point
*/
const Vector3 &SensorAABoundingBox::GetMin() const
{
	return m_vMin;
}

/**
*  @brief
*    Sets the minimum point
*/
void SensorAABoundingBox::SetMin(const Vector3 &vMin)
{
	m_vMin = vMin;
}

/**
*  @brief
*    Returns the maximum point
*/
const Vector3 &SensorAABoundingBox::GetMax() const
{
	return m_vMax;
}

/**
*  @brief
*    Sets the maximum point
*/
void SensorAABoundingBox::SetMax(const Vector3 &vMax)
{
	m_vMax = vMax;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SensorAABoundingBox::SensorAABoundingBox(World &cWorld, const Vector3 &vMin, const Vector3 &vMax, uint32 nFlags) : Sensor(cWorld, nFlags),
	m_vMin(vMin),
	m_vMax(vMax)
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
