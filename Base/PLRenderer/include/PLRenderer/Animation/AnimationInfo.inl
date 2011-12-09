/*********************************************************\
 *  File: AnimationInfo.inl                              *
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
*    Returns the type of the animation
*/
inline PLCore::uint32 AnimationInfo::GetType() const
{
	return m_nType;
}

/**
*  @brief
*    Sets the animation type
*/
inline void AnimationInfo::SetType(PLCore::uint32 nType)
{
	m_nType = nType;
}

/**
*  @brief
*    Returns the animation start frame
*/
inline PLCore::uint32 AnimationInfo::GetStartFrame() const
{
	return m_nStart;
}

/**
*  @brief
*    Returns the animation end frame
*/
inline PLCore::uint32 AnimationInfo::GetEndFrame() const
{
	return m_nEnd;
}

/**
*  @brief
*    Returns the number of animation frames
*/
inline PLCore::uint32 AnimationInfo::GetNumOfFrames() const
{
	return (m_nEnd > m_nStart) ? m_nEnd-m_nStart+1 : m_nStart-m_nEnd+1;
}

/**
*  @brief
*    Get the animation speed
*/
inline float AnimationInfo::GetSpeed() const
{
	return m_fSpeed;
}

/**
*  @brief
*    Set the animation speed
*/
inline void AnimationInfo::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

/**
*  @brief
*    Get the animation information flags
*/
inline PLCore::uint32 AnimationInfo::GetFlags() const
{
	return m_nFlags;
}

/**
*  @brief
*    Sets the animation information flags
*/
inline void AnimationInfo::SetFlags(PLCore::uint32 nFlags)
{
	m_nFlags = nFlags;
}

/**
*  @brief
*    Returns information about a frame
*/
inline AnimationFrameInfo *AnimationInfo::GetFrameInfo(PLCore::uint32 nIndex) const
{
	AnimationFrameInfo &cAnimationFrameInfo = m_lstFrameInfos[nIndex];
	return (&cAnimationFrameInfo != &PLCore::Array<AnimationFrameInfo>::Null) ? &cAnimationFrameInfo : nullptr;
}

/**
*  @brief
*    Returns the event manager
*/
inline AnimationEventManager &AnimationInfo::GetEventManager()
{
	return m_cEventManager;
}

inline const AnimationEventManager &AnimationInfo::GetEventManager() const
{
	return m_cEventManager;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
