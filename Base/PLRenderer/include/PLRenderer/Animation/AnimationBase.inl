/*********************************************************\
 *  File: AnimationBase.inl                              *
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
*    Returns the frame rate
*/
inline float AnimationBase::GetFrameRate() const
{
	return m_fFrameRate;
}

/**
*  @brief
*    Sets the frame rate
*/
inline void AnimationBase::SetFrameRate(float fFrameRate)
{
	m_fFrameRate = fFrameRate;
}

/**
*  @brief
*    Returns the frame keys
*/
inline PLCore::Array<AnimationBase::FrameKeys> &AnimationBase::GetFrameKeys()
{
	return m_lstFrameKeys;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
