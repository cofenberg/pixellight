/*********************************************************\
 *  File: JointHinge.cpp                                 *
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
#include "PLPhysics/JointHinge.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
JointHinge::~JointHinge()
{
}

/**
*  @brief
*    Returns the origin of the hinge in world space
*/
const Vector3 &JointHinge::GetPivotPoint() const
{
	return m_vPivotPoint;
}

/**
*  @brief
*    Returns the line of action of the hinge in world space
*/
const Vector3 &JointHinge::GetPinDir() const
{
	return m_vPinDir;
}

/**
*  @brief
*    Returns the low range
*/
float JointHinge::GetLowRange() const
{
	return m_fLowRange;
}

/**
*  @brief
*    Sets the low range
*/
void JointHinge::SetLowRange(float fLowRange)
{
	m_fLowRange = fLowRange;
}

/**
*  @brief
*    Returns the high range
*/
float JointHinge::GetHighRange() const
{
	return m_fHighRange;
}

/**
*  @brief
*    Sets the high range
*/
void JointHinge::SetHighRange(float fHighRange)
{
	m_fHighRange = fHighRange;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
JointHinge::JointHinge(World &cWorld, JointImpl &cJointImpl, Body *pParentBody, Body *pChildBody,
					   const Vector3 &vPivotPoint, const Vector3 &vPinDir) :
	Joint(cWorld, cJointImpl, pParentBody, pChildBody),
	m_vPivotPoint(vPivotPoint),
	m_vPinDir(vPinDir),
	m_fLowRange(-180.0f),
	m_fHighRange(180.0f)
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
