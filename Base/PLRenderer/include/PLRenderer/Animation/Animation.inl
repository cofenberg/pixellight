/*********************************************************\
 *  File: Animation.inl                                  *
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
*    Get the animation active status
*/
inline bool Animation::IsActive() const
{
	return m_bActive;
}

/**
*  @brief
*    Set the animation active status
*/
inline void Animation::SetActive(bool bActive)
{
	m_bActive = bActive;
}

/**
*  @brief
*    Type of animation
*/
inline PLCore::uint32 Animation::GetType() const
{
	return m_nType;
}

/**
*  @brief
*    Sets the animation type
*/
inline void Animation::SetType(PLCore::uint32 nType)
{
	m_nType = nType;
}

/**
*  @brief
*    Pause the animation
*/
inline void Animation::Pause()
{
	m_bRunning = false;
}

/**
*  @brief
*    Continues the animation
*/
inline void Animation::Continue()
{
	if (m_nStart != m_nEnd)
		m_bRunning = true;
}

/**
*  @brief
*    Returns the animation information
*/
inline AnimationInfo *Animation::GetAnimation() const
{
	return m_pAnimationInfo;
}

/**
*  @brief
*    Gets the animation weight
*/
inline float Animation::GetWeight() const
{
	return m_fWeight;
}

/**
*  @brief
*    Sets the animation weight
*/
inline void Animation::SetWeight(float fWeight)
{
	m_fWeight = fWeight;
}

/**
*  @brief
*    Get the animation speed
*/
inline float Animation::GetSpeed() const
{
	return m_fSpeed;
}

/**
*  @brief
*    Set the animation speed
*/
inline void Animation::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

/**
*  @brief
*    Get the animation information flags
*/
inline PLCore::uint32 Animation::GetFlags() const
{
	return m_nFlags;
}

/**
*  @brief
*    Sets the animation information flags
*/
inline void Animation::SetFlags(PLCore::uint32 nFlags)
{
	m_nFlags = nFlags;
}

/**
*  @brief
*    Get the animation running status
*/
inline bool Animation::IsRunning() const
{
	return m_bRunning;
}

/**
*  @brief
*    Returns the start frame
*/
inline PLCore::uint32 Animation::GetStartFrame() const
{
	return m_nStart;
}

/**
*  @brief
*    Returns the end frame
*/
inline PLCore::uint32 Animation::GetEndFrame() const
{
	return m_nEnd;
}

/**
*  @brief
*    Returns the number of frames
*/
inline PLCore::uint32 Animation::GetNumOfFrames() const
{
	return (m_nEnd > m_nStart) ? m_nEnd-m_nStart : m_nStart-m_nEnd;
}


//[-------------------------------------------------------]
//[ Events                                                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns whether animation events are enabled or not
*/
inline bool Animation::GetEvents() const
{
	return m_bEvents;
}

/**
*  @brief
*    Sets whether animation events are enabled or not
*/
inline void Animation::SetEvents(bool bEvents)
{
	m_bEvents = bEvents;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
