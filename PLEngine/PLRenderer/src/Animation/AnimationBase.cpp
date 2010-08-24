/*********************************************************\
 *  File: AnimationBase.cpp                              *
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
#include "PLRenderer/Animation/AnimationBase.h"


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
AnimationBase::AnimationBase() :
	m_fFrameRate(24.0f)
{
}

/**
*  @brief
*    Destructor
*/
AnimationBase::~AnimationBase()
{
}

/**
*  @brief
*    Returns the frame rate
*/
float AnimationBase::GetFrameRate() const
{
	return m_fFrameRate;
}

/**
*  @brief
*    Sets the frame rate
*/
void AnimationBase::SetFrameRate(float fFrameRate)
{
	m_fFrameRate = fFrameRate;
}

/**
*  @brief
*    Returns the frame keys
*/
Array<AnimationBase::FrameKeys> &AnimationBase::GetFrameKeys()
{
	return m_lstFrameKeys;
}


//[-------------------------------------------------------]
//[ Public virtual AnimationInfo functions                ]
//[-------------------------------------------------------]
AnimationBase &AnimationBase::operator =(const AnimationBase &cSource)
{
	*((AnimationInfo*)this) = *((const AnimationInfo*)&cSource);

	// Copy data
	m_fFrameRate   = cSource.m_fFrameRate;
	m_lstFrameKeys = cSource.m_lstFrameKeys;

	// Return pointer
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
