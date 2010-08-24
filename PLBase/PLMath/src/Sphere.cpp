/*********************************************************\
 *  File: Sphere.cpp                                     *
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
#include "PLMath/Sphere.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor setting all position components and the radius to 0
*/
Sphere::Sphere() :
	m_fRadius(0.0f)
{
}

/**
*  @brief
*    Copy constructor
*/
Sphere::Sphere(const Sphere &cSource) :
	m_fRadius(cSource.m_fRadius),
	m_vPos(cSource.m_vPos)
{
}

/**
*  @brief
*    Destructor
*/
Sphere::~Sphere()
{
}

/**
*  @brief
*    Copy operator
*/
Sphere &Sphere::operator =(const Sphere &cSource)
{
	// Copy data
	m_fRadius = cSource.m_fRadius;
	m_vPos    = cSource.m_vPos;

	// Return this
	return *this;
}

/**
*  @brief
*    Returns the radius of the sphere
*/
float Sphere::GetRadius() const
{
	return m_fRadius;
}

/**
*  @brief
*    Sets the radius of the sphere
*/
void Sphere::SetRadius(float fRadius)
{
	m_fRadius = fRadius;
}

/**
*  @brief
*    Returns the current position
*/
const Vector3 &Sphere::GetPos() const
{
	// Return position
	return m_vPos;
}

/**
*  @brief
*    Set the current position
*/
void Sphere::SetPos(float fX, float fY, float fZ)
{
	// Set new position
	m_vPos.SetXYZ(fX, fY, fZ);
}

/**
*  @brief
*    Set the current position
*/
void Sphere::SetPos(const Vector3 &vPos)
{
	// Set new position
	m_vPos = vPos;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
