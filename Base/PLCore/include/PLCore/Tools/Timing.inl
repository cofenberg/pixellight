/*********************************************************\
 *  File: Timing.inl                                     *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ General                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns whether the timing is active or not
*/
inline bool Timing::IsActive() const
{
	return m_bActive;
}

/**
*  @brief
*    Sets whether the timing is active or not
*/
inline void Timing::SetActive(bool bActive)
{
	m_bActive = bActive;
}


//[-------------------------------------------------------]
//[ Past time                                             ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the past time since last frame (in seconds)
*/
inline float Timing::GetTimeDifference() const
{
	return m_bFreezed ? 0.0f : m_fTimeDifference;
}

/**
*  @brief
*    Returns the past time since last frame without any clamping (seconds)
*/
inline float Timing::GetTimeDifferenceNoCompensating() const
{
	return m_bFreezed ? 0.0f : m_fTimeDifferenceNoCompensating;
}

/**
*  @brief
*    Returns the maximum time difference
*/
inline float Timing::GetMaxTimeDifference() const
{
	return m_fMaxTimeDifference;
}

/**
*  @brief
*    Sets the maximum time difference
*/
inline void Timing::SetMaxTimeDifference(float fMaxTimeDifference)
{
	m_fMaxTimeDifference = (fMaxTimeDifference > 0.0f) ? fMaxTimeDifference : 0.0001f;
}

/**
*  @brief
*    Returns a general timing
*/
inline float Timing::GetTimer() const
{
	return m_fTimer;
}


//[-------------------------------------------------------]
//[ Frames                                                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the current frames per second (FPS)
*/
inline float Timing::GetFramesPerSecond() const
{
	return m_fFramesPerSecond;
}

/**
*  @brief
*    Returns the number of past frames since timing start
*/
inline uint32 Timing::GetPastFrames() const
{
	return m_nPastFrames;
}

/**
*  @brief
*    Returns the FPS limit
*/
inline float Timing::GetFPSLimit() const
{
	return m_fFPSLimit;
}

/**
*  @brief
*    Sets the FPS limit
*/
inline void Timing::SetFPSLimit(float fFPSLimit)
{
	m_fFPSLimit = (fFPSLimit >= 0.0f) ? fFPSLimit : 0.0f;
}


//[-------------------------------------------------------]
//[ Time scale                                            ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns if the timing is currently freezed or not
*/
inline bool Timing::IsFreezed() const
{
	return m_bFreezed;
}

/**
*  @brief
*    Returns whether the timing is paused of not
*/
inline bool Timing::IsPaused() const
{
	return m_bPause;
}

/**
*  @brief
*    Set pause mode
*/
inline void Timing::Pause(bool bPause)
{
	m_bPause = bPause;
}

/**
*  @brief
*    Returns the time scale factor
*/
inline float Timing::GetTimeScaleFactor() const
{
	return m_fTimeScaleFactor;
}

/**
*  @brief
*    Sets the time scale factor
*/
inline bool Timing::SetTimeScaleFactor(float fFactor)
{
	if (fFactor > 0.0f) {
		// Set the new factor
		m_fTimeScaleFactor = fFactor;

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Returns if the slow motion is activated or not
*/
inline bool Timing::IsSlowMotion() const
{
	return m_bSlowMotion;
}

/**
*  @brief
*    Activates/deactivates the slow motion mode
*/
inline void Timing::SetSlowMotion(bool bSlowMotion)
{
	m_bSlowMotion = bSlowMotion;
}

/**
*  @brief
*    Sets the custom slow motion factor
*/
inline float Timing::GetSlowMotionFactor(bool bRealUsed) const
{
	return (bRealUsed && !m_bSlowMotion) ? 1.0f : m_fSlowMotionFactor;
}

/**
*  @brief
*    Sets the slow motion factor
*/
inline bool Timing::SetSlowMotionFactor(float fSlowMotionFactor)
{
	if (fSlowMotionFactor > 0.0f) {
		// Set the new factor
		m_fSlowMotionFactor = fSlowMotionFactor;

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Returns the custom slow motion factor
*/
inline float Timing::GetCustomSlowMotionFactor(bool bRealUsed) const
{
	return (bRealUsed && !m_bSlowMotion) ? 1.0f : m_fCustomSlowMotionFactor;
}

/**
*  @brief
*    Sets the custom slow motion factor
*/
inline bool Timing::SetCustomSlowMotionFactor(float fSlowMotionFactor)
{
	if (fSlowMotionFactor > 0.0f) {
		// Set the new factor
		m_fCustomSlowMotionFactor = fSlowMotionFactor;

		// Done
		return true;
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
