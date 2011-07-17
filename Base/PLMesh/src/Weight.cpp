/*********************************************************\
 *  File: Weight.cpp                                     *
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
#include "PLMesh/Weight.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Weight::Weight() :
	m_nJoint(-1),
	m_fBias(0.0f)
{
}

/**
*  @brief
*    Destructor
*/
Weight::~Weight()
{
}

/**
*  @brief
*    Get the weight joint number
*/
int Weight::GetJoint() const
{
	return m_nJoint;
}

/**
*  @brief
*    Sets the weight joint number
*/
void Weight::SetJoint(int nJoint)
{
	m_nJoint = nJoint;
}

/**
*  @brief
*    Get the weight bias
*/
float Weight::GetBias() const
{
	return m_fBias;
}

/**
*  @brief
*    Sets the weight bias
*/
void Weight::SetBias(float fBias)
{
	m_fBias = fBias;
}

/**
*  @brief
*    Copy operator
*/
Weight &Weight::operator =(const Weight &cSource)
{
	// Copy data
	m_nJoint = cSource.m_nJoint;
	m_fBias  = cSource.m_fBias;

	// Return pointer
	return *this;
}

/**
*  @brief
*    Compares two weights
*/
bool Weight::operator ==(const Weight &cWeight) const
{
	return (m_nJoint == cWeight.m_nJoint && m_fBias  == cWeight.m_fBias);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh
