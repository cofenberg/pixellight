/*********************************************************\
 *  File: Timing.cpp                                     *
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
#include "PLCore/System/System.h"
#include "PLCore/Tools/Timing.h"


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
bool Timing::IsActive() const
{
	return m_bActive;
}

/**
*  @brief
*    Sets whether the timing is active or not
*/
void Timing::SetActive(bool bActive)
{
	m_bActive = bActive;
}

/**
*  @brief
*    Resets the timing
*/
void Timing::Reset()
{
	m_nLastFPSUpdateTime = m_nTimeLast = m_nTimeNow = m_nFPSLimitLastTime = System::GetInstance()->GetMilliseconds();
}

/**
*  @brief
*    Checks whether the timing has to be updated or not
*/
bool Timing::CheckUpdate(uint64 *pnTimeToWait) const
{
	// By default we don't need to wait
	if (pnTimeToWait)
		*pnTimeToWait = 0;

	// Is there a FPS limitation?
	if (m_fFPSLimit) {
		const uint64 nPastTime     = System::GetInstance()->GetMilliseconds()-m_nFPSLimitLastTime;
		const uint32 nTimePerFrame = static_cast<uint32>(1000/m_fFPSLimit);
		if (nPastTime < nTimePerFrame) {
			if (pnTimeToWait)
				*pnTimeToWait = nTimePerFrame-nPastTime;

			// It's not time for an update!
			return false;
		}
	}

	// Done
	return true;
}

/**
*  @brief
*    Updates all time relevant stuff
*/
bool Timing::Update(uint64 *pnTimeToWait)
{
	// Is the timing currently freezed?
	if (m_bFreezed)
		m_fTimeDifference = 0.0f;

	// Check FPS limitation
	if (m_fFPSLimit) {
		// Time for an update?
		if (CheckUpdate(pnTimeToWait))
			m_nFPSLimitLastTime = System::GetInstance()->GetMilliseconds();
		else
			return false; // Error - it's not time for an update
	} else {
		if (pnTimeToWait)
			pnTimeToWait = 0;
	}

	// Is the timing currently freezed?
	if (!m_bFreezed) {
		// Get time difference
		float fPrevTimeDifference = m_fTimeDifference;
		m_nTimeNow = System::GetInstance()->GetMilliseconds();
		m_fTimeDifference = m_fTimeDifferenceNoCompensating = (m_nTimeNow-m_nTimeLast)/1000.0f;
		if (!m_bActive || m_fTimeDifference > m_fMaxTimeDifference)
			m_fTimeDifference = m_fMaxTimeDifference;
		m_nTimeLast = m_nTimeNow;

		// Calculate the current FPS
		m_nPastFrames++;
		m_nFramesSinceCheck++;
		m_fFPSUpdateTimer += m_fTimeDifference;
		if (m_fFPSUpdateTimer > 1.0f) {
			m_fFPSUpdateTimer = 0.0f;
			m_fFramesPerSecond = static_cast<float>(m_nFramesSinceCheck/((m_nTimeNow-m_nLastFPSUpdateTime)/1000.0f));
			if (m_fFramesPerSecond < 0.0f)
				m_fFramesPerSecond = 0.0f;
			m_nFramesSinceCheck   = 0;
			m_nLastFPSUpdateTime = m_nTimeNow;
		}

		// Perform time scale
		m_fTimeDifference               *= m_fTimeScaleFactor;
		m_fTimeDifferenceNoCompensating *= m_fTimeScaleFactor;

		// Perform slow motion
		if (m_bSlowMotion) {
			m_fTimeDifference               *= m_fSlowMotionFactor*m_fCustomSlowMotionFactor;
			m_fTimeDifferenceNoCompensating *= m_fSlowMotionFactor*m_fCustomSlowMotionFactor;
		}

		// Try to compensate to abrupt timing slowdowns that may cause several problems
		float fDiff        = m_fTimeDifference-fPrevTimeDifference;
		float fMaxStepDiff = m_fMaxTimeDifference/3;
		if (fDiff > fMaxStepDiff)
			m_fTimeDifference = fMaxStepDiff+(fDiff-fMaxStepDiff)*0.1f;

		// Update the general timing
		m_fTimer += m_fTimeDifference;
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Past time                                             ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the past time since last frame (in seconds)
*/
float Timing::GetTimeDifference() const
{
	return m_bFreezed ? 0.0f : m_fTimeDifference;
}

/**
*  @brief
*    Returns the past time since last frame without any clamping (seconds)
*/
float Timing::GetTimeDifferenceNoCompensating() const
{
	return m_bFreezed ? 0.0f : m_fTimeDifferenceNoCompensating;
}

/**
*  @brief
*    Returns the maximum time difference
*/
float Timing::GetMaxTimeDifference() const
{
	return m_fMaxTimeDifference;
}

/**
*  @brief
*    Sets the maximum time difference
*/
void Timing::SetMaxTimeDifference(float fMaxTimeDifference)
{
	m_fMaxTimeDifference = (fMaxTimeDifference > 0.0f) ? fMaxTimeDifference : 0.0001f;
}

/**
*  @brief
*    Returns the past time in milliseconds since the application start
*/
uint64 Timing::GetPastTime() const
{
	return System::GetInstance()->GetMilliseconds() - m_nTimeStart;
}

/**
*  @brief
*    Returns a general timing
*/
float Timing::GetTimer() const
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
float Timing::GetFramesPerSecond() const
{
	return m_fFramesPerSecond;
}

/**
*  @brief
*    Returns the number of past frames since timing start
*/
uint32 Timing::GetPastFrames() const
{
	return m_nPastFrames;
}

/**
*  @brief
*    Returns the FPS limit
*/
float Timing::GetFPSLimit() const
{
	return m_fFPSLimit;
}

/**
*  @brief
*    Sets the FPS limit
*/
void Timing::SetFPSLimit(float fFPSLimit)
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
bool Timing::IsFreezed() const
{
	return m_bFreezed;
}

/**
*  @brief
*    Set freezed mode
*/
void Timing::Freeze(bool bFreeze)
{
	if (bFreeze) {
		if (!m_bFreezed) {
			m_bFreezed    = true;
			m_nFreezeTime = m_nTimeNow;
		}
	} else {
		if (m_bFreezed) { // Update timing
			const uint64 nTimeDifference = System::GetInstance()->GetMilliseconds() - m_nFreezeTime;
			m_nTimeLast			 += nTimeDifference;
			m_nLastFPSUpdateTime += nTimeDifference;
		}
		m_bFreezed = false;
	}
}

/**
*  @brief
*    Returns whether the timing is paused of not
*/
bool Timing::IsPaused() const
{
	return m_bPause;
}

/**
*  @brief
*    Set pause mode
*/
void Timing::Pause(bool bPause)
{
	m_bPause = bPause;
}

/**
*  @brief
*    Returns the time scale factor
*/
float Timing::GetTimeScaleFactor() const
{
	return m_fTimeScaleFactor;
}

/**
*  @brief
*    Sets the time scale factor
*/
bool Timing::SetTimeScaleFactor(float fFactor)
{
	if (fFactor > 0.0f) {
		// Set the new factor
		m_fTimeScaleFactor = fFactor;

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

/**
*  @brief
*    Returns if the slow motion is activated or not
*/
bool Timing::IsSlowMotion() const
{
	return m_bSlowMotion;
}

/**
*  @brief
*    Activates/deactivates the slow motion mode
*/
void Timing::SetSlowMotion(bool bSlowMotion)
{
	m_bSlowMotion = bSlowMotion;
}

/**
*  @brief
*    Sets the custom slow motion factor
*/
float Timing::GetSlowMotionFactor(bool bRealUsed) const
{
	return bRealUsed && !m_bSlowMotion ? 1.0f : m_fSlowMotionFactor;
}

/**
*  @brief
*    Sets the slow motion factor
*/
bool Timing::SetSlowMotionFactor(float fSlowMotionFactor)
{
	if (fSlowMotionFactor > 0.0f) {
		// Set the new factor
		m_fSlowMotionFactor = fSlowMotionFactor;

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

/**
*  @brief
*    Returns the custom slow motion factor
*/
float Timing::GetCustomSlowMotionFactor(bool bRealUsed) const
{
	return bRealUsed && !m_bSlowMotion ? 1.0f : m_fCustomSlowMotionFactor;
}

/**
*  @brief
*    Sets the custom slow motion factor
*/
bool Timing::SetCustomSlowMotionFactor(float fSlowMotionFactor)
{
	if (fSlowMotionFactor > 0.0f) {
		// Set the new factor
		m_fCustomSlowMotionFactor = fSlowMotionFactor;

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Timing::Timing() :
	m_bActive(true),
	m_nTimeStart(System::GetInstance()->GetMilliseconds()),
	m_nTimeNow(m_nTimeStart),
	m_nTimeLast(m_nTimeStart),
	m_fTimeDifference(0.0f),
	m_fTimeDifferenceNoCompensating(0.0f),
	m_fMaxTimeDifference(0.15f),
	m_fFramesPerSecond(0.0f),
	m_nFramesSinceCheck(0),
	m_nPastFrames(0),
	m_nLastFPSUpdateTime(m_nTimeStart),
	m_fFPSUpdateTimer(0.0f),
	m_bFreezed(false),
	m_nFreezeTime(0),
	m_bPause(false),
	m_fTimeScaleFactor(1.0f),
	m_bSlowMotion(true),
	m_fSlowMotionFactor(1.0f),
	m_fCustomSlowMotionFactor(1.0f),
	m_nFPSLimitLastTime(m_nTimeStart),
	m_fFPSLimit(0.0f),
	m_fTimer(0.0f)
{
}

/**
*  @brief
*    Copy constructor
*/
Timing::Timing(const Timing &cSource) :
	m_bActive(true),
	m_nTimeStart(System::GetInstance()->GetMilliseconds()),
	m_nTimeNow(m_nTimeStart),
	m_nTimeLast(m_nTimeStart),
	m_fTimeDifference(0.0f),
	m_fTimeDifferenceNoCompensating(0.0f),
	m_fMaxTimeDifference(0.15f),
	m_fFramesPerSecond(0.0f),
	m_nFramesSinceCheck(0),
	m_nPastFrames(0),
	m_nLastFPSUpdateTime(m_nTimeStart),
	m_fFPSUpdateTimer(0.0f),
	m_bFreezed(false),
	m_nFreezeTime(0),
	m_bPause(false),
	m_fTimeScaleFactor(1.0f),
	m_bSlowMotion(true),
	m_fSlowMotionFactor(1.0f),
	m_fCustomSlowMotionFactor(1.0f),
	m_nFPSLimitLastTime(m_nTimeStart),
	m_fFPSLimit(0.0f),
	m_fTimer(0.0f)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Destructor
*/
Timing::~Timing()
{
}

/**
*  @brief
*    Copy operator
*/
Timing &Timing::operator =(const Timing &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
