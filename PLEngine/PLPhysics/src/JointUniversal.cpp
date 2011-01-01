/*********************************************************\
 *  File: JointUniversal.cpp                             *
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
#include "PLPhysics/JointUniversal.h"


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
JointUniversal::~JointUniversal()
{
}

/**
*  @brief
*    Returns the origin of the universal in world space
*/
const Vector3 &JointUniversal::GetPivotPoint() const
{
	return m_vPivotPoint;
}

/**
*  @brief
*    Returns the first axis of rotation fixed on THIS body and perpendicular to 'PinDir2' in world space
*/
const Vector3 &JointUniversal::GetPinDir1() const
{
	return m_vPinDir1;
}

/**
*  @brief
*    Returns the second axis of rotation fixed on 'Parent' body and perpendicular to 'PinDir1' in world space
*/
const Vector3 &JointUniversal::GetPinDir2() const
{
	return m_vPinDir2;
}

/**
*  @brief
*    Returns the low range of the first axis
*/
float JointUniversal::GetLowRange1() const
{
	return m_fLowRange1;
}

/**
*  @brief
*    Sets the low range of the first axis
*/
void JointUniversal::SetLowRange1(float fLowRange)
{
	m_fLowRange1 = fLowRange;
}

/**
*  @brief
*    Returns the high range of the first axis
*/
float JointUniversal::GetHighRange1() const
{
	return m_fHighRange1;
}

/**
*  @brief
*    Sets the high range of the first axis
*/
void JointUniversal::SetHighRange1(float fHighRange)
{
	m_fHighRange1 = fHighRange;
}

/**
*  @brief
*    Returns the low range of the second axis
*/
float JointUniversal::GetLowRange2() const
{
	return m_fLowRange2;
}

/**
*  @brief
*    Sets the low range of the second axis
*/
void JointUniversal::SetLowRange2(float fLowRange)
{
	m_fLowRange2 = fLowRange;
}

/**
*  @brief
*    Returns the high range of the second axis
*/
float JointUniversal::GetHighRange2() const
{
	return m_fHighRange2;
}

/**
*  @brief
*    Sets the high range of the secondaxis
*/
void JointUniversal::SetHighRange2(float fHighRange)
{
	m_fHighRange2 = fHighRange;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
JointUniversal::JointUniversal(World &cWorld, JointImpl &cJointImpl, Body *pParentBody, Body *pChildBody, const Vector3 &vPivotPoint,
							   const Vector3 &vPinDir1, const Vector3 &vPinDir2) :
	Joint(cWorld, cJointImpl, pParentBody, pChildBody),
	m_vPivotPoint(vPivotPoint),
	m_vPinDir1(vPinDir1),
	m_vPinDir2(vPinDir2),
	m_fLowRange1(-180.0f),
	m_fHighRange1(180.0f),
	m_fLowRange2(-180.0f),
	m_fHighRange2(180.0f)
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
