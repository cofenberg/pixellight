/*********************************************************\
 *  File: AnimationFrameInfo.inl                         *
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
inline AnimationFrameInfo::AnimationFrameInfo() :
	m_fSpeed(1.0f)
{
}

/**
*  @brief
*    Destructor
*/
inline AnimationFrameInfo::~AnimationFrameInfo()
{
}

/**
*  @brief
*    Returns the speed of an animation frame
*/
float AnimationFrameInfo::GetSpeed() const
{
	return m_fSpeed;
}

/**
*  @brief
*    Sets the animation frame speed
*/
inline void AnimationFrameInfo::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

/**
*  @brief
*    Copy operator
*/
inline AnimationFrameInfo &AnimationFrameInfo::operator =(const AnimationFrameInfo &cSource)
{
	// Copy data
	m_fSpeed = cSource.m_fSpeed;

	// Return pointer
	return *this;
}

/**
*  @brief
*    Compare operator
*/
inline bool AnimationFrameInfo::operator ==(const AnimationFrameInfo &cSource) const
{
	return (m_fSpeed == cSource.m_fSpeed);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
