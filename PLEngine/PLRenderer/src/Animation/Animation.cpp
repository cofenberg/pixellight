/*********************************************************\
 *  File: Animation.cpp                                  *
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
#include <PLMath/Math.h>
#include "PLRenderer/Animation/AnimationInfo.h"
#include "PLRenderer/Animation/AnimationEvent.h"
#include "PLRenderer/Animation/AnimationManager.h"
#include "PLRenderer/Animation/Animation.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Animation::Animation(const String &sName, AnimationManager *pManager) : Element<Animation>(sName, pManager),
	m_bEvents(true)
{
	Reset();
}

/**
*  @brief
*    Destructor
*/
Animation::~Animation()
{
}

/**
*  @brief
*    Resets the animation
*/
void Animation::Reset()
{
	// Init animation status
	m_bActive		 = false;
	m_bRunning		 = false;
	m_nType			 = 0;
	m_nFlags		 = 0;
	m_nStart		 = 0;
	m_nEnd			 = 0;
	m_fSpeed		 = 24.0f;
	m_pAnimationInfo = NULL;
	m_fWeight		 = 1.0f;
	m_bBounced		 = false;

	// Set the current frame
	SetCurrentFrame(0.0f);
}

/**
*  @brief
*    Get the animation active status
*/
bool Animation::IsActive() const
{
	return m_bActive;
}

/**
*  @brief
*    Set the animation active status
*/
void Animation::SetActive(bool bActive)
{
	m_bActive = bActive;
}

/**
*  @brief
*    Type of animation
*/
uint32 Animation::GetType() const
{
	return m_nType;
}

/**
*  @brief
*    Sets the animation type
*/
void Animation::SetType(uint32 nType)
{
	m_nType = nType;
}

/**
*  @brief
*    Starts an animation
*/
void Animation::Start(uint32 nStart, uint32 nEnd, float fSpeed, uint32 nFlags)
{
	m_bActive		 = true;
	m_bRunning		 = true;
	m_nFlags		 = nFlags;
	m_nStart		 = nStart;
	m_nEnd			 = nEnd;
	m_fSpeed		 = fSpeed;
	m_pAnimationInfo = NULL;
	m_bBounced		 = false;

	// Set the current frame
	SetCurrentFrame((float)nStart);

	// Emit start event
	EventStart.Emit();
}

/**
*  @brief
*    Starts an animation
*/
void Animation::Start(AnimationInfo &cAnimationInfo, bool bRestart)
{
	// Is this animation already running?
	if (bRestart || !m_pAnimationInfo || (m_pAnimationInfo && m_pAnimationInfo != &cAnimationInfo)) {
		// Start/restart the animation
		m_bActive		 = true;
		m_bRunning		 = true;
		m_nType			 = cAnimationInfo.GetType();
		m_nFlags		 = cAnimationInfo.GetFlags();
		m_nStart		 = cAnimationInfo.GetStartFrame();
		m_nEnd			 = cAnimationInfo.GetEndFrame();
		m_fSpeed		 = cAnimationInfo.GetSpeed();
		m_pAnimationInfo = &cAnimationInfo;
		m_bBounced		 = false;

		// Set the current frame
		SetCurrentFrame((float)cAnimationInfo.GetStartFrame());

		// Check if a event is caused
		CheckEvent();

		// Emit start event
		EventStart.Emit();
	}
}

/**
*  @brief
*    Stops the animation
*/
void Animation::Stop()
{
	// Is the animation currently active?
	if (m_bActive) {
		// [TODO] Review this. It should be correct though, because only the running-state should be reset here,
		//        no the whole animation information.
	//	Reset();

		// Stop animation, but keep current state and options
		m_bActive		 = false;
		m_bRunning		 = false;

		// Emit stop event
		EventStop.Emit();
	}
}

/**
*  @brief
*    Pause the animation
*/
void Animation::Pause()
{
	m_bRunning = false;
}

/**
*  @brief
*    Continues the animation
*/
void Animation::Continue()
{
	if (m_nStart != m_nEnd)
		m_bRunning = true;
}

/**
*  @brief
*    Returns the animation information
*/
AnimationInfo *Animation::GetAnimation() const
{
	return m_pAnimationInfo;
}

/**
*  @brief
*    Gets the animation weight
*/
float Animation::GetWeight() const
{
	return m_fWeight;
}

/**
*  @brief
*    Sets the animation weight
*/
void Animation::SetWeight(float fWeight)
{
	m_fWeight = fWeight;
}

/**
*  @brief
*    Get the animation speed
*/
float Animation::GetSpeed() const
{
	return m_fSpeed;
}

/**
*  @brief
*    Set the animation speed
*/
void Animation::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

/**
*  @brief
*    Get the animation information flags
*/
uint32 Animation::GetFlags() const
{
	return m_nFlags;
}

/**
*  @brief
*    Sets the animation information flags
*/
void Animation::SetFlags(uint32 nFlags)
{
	m_nFlags = nFlags;
}

/**
*  @brief
*    Get the animation running status
*/
bool Animation::IsRunning() const
{
	return m_bRunning;
}

/**
*  @brief
*    Returns the start frame
*/
uint32 Animation::GetStartFrame() const
{
	return m_nStart;
}

/**
*  @brief
*    Returns the end frame
*/
uint32 Animation::GetEndFrame() const
{
	return m_nEnd;
}

/**
*  @brief
*    Returns the number of frames
*/
uint32 Animation::GetNumOfFrames() const
{
	return (m_nEnd > m_nStart) ? m_nEnd-m_nStart : m_nStart-m_nEnd;
}

/**
*  @brief
*    Get the current animation frame
*/
float Animation::GetFrame() const
{
	// Is there a more complex animation information?
	if (m_pAnimationInfo) {
		// Get the 'real' start frame
		const uint32 nStart = (m_nEnd > m_nStart) ? m_nStart : m_nEnd;

		// Use frame interpolation?
		const AnimationFrameInfo *pFrameInfo = m_pAnimationInfo->GetFrameInfo(uint32(m_fFrame-nStart));
		if (pFrameInfo && pFrameInfo->GetSpeed() < 0.0f)
			return (float)((uint32)m_fFrame); // No interpolation, please
	}

	// Just return the current frame
	return m_fFrame;
}

/**
*  @brief
*    Gets the progress from the current state to the next state (0.0-1.0)
*/
float Animation::GetProgress() const
{
	return Math::Abs(GetFrame()-GetCurrentFrame());
}

/**
*  @brief
*    Get the current animation frame as an integer
*/
uint32 Animation::GetCurrentFrame() const
{
	if (m_fSpeed >= 0.0f)
		return uint32(m_fFrame);
	else {
		// Get 'real' end frame
		const uint32 nEnd = (m_nEnd > m_nStart) ? m_nEnd : m_nStart;

		// Get the current frame
		const uint32 nFrame = uint32(m_fFrame)+1;
		return (nFrame > nEnd) ? nEnd : nFrame;
	}
}

/**
*  @brief
*    Set the current animation frame
*/
void Animation::SetCurrentFrame(float fFrame)
{
	// Clamp the given frame if required
	if (m_nEnd > m_nStart) {
		if (fFrame < m_nStart)
			fFrame = (float)m_nStart;
		else if (fFrame > m_nEnd)
			fFrame = (float)m_nEnd;
	} else {
		if (fFrame < m_nEnd)
			fFrame = (float)m_nEnd;
		else if (fFrame > m_nStart)
			fFrame = (float)m_nStart;
	}

	// Frame change?
	if (m_fFrame != fFrame) {
		// Set the current animation frame
		m_fFrame = fFrame;

		// Emit frame change event
		if (m_bEvents)
			EventFrameChange.Emit();
	}
}

/**
*  @brief
*    Get the next animation frame as an integer
*/
uint32 Animation::GetNextFrame() const
{
	// Start frame = end frame?
	if (m_nStart == m_nEnd)
		return m_nStart; // That was pretty easy :)

	// Get 'real' start and end frames
	int nStart, nEnd;
	if (m_nEnd > m_nStart) {
		nStart = m_nStart;
		nEnd   = m_nEnd;
	} else {
		nStart = m_nEnd;
		nEnd   = m_nStart;
	}

	// Next frame please
	int nNextFrame = nStart;
	if (m_fSpeed >= 0.0f) {
		nNextFrame = int(m_fFrame)+1;

		// Ping pong (with or without loop)
		if (m_nFlags & PingPong) {
			if (m_nFlags & Loop) {
				// End reached?
				if (nNextFrame > nEnd)
					nNextFrame = nEnd-1;
			} else {
				// End reached?
				if (nNextFrame > nEnd)
					nNextFrame = m_bBounced ? nEnd : nEnd-1;
			}

		// Loop
		} else if (m_nFlags & Loop) {
			// End reached?
			if (nNextFrame > nEnd)
				nNextFrame = nStart;

		// Normal
		} else {
			// End reached?
			if (nNextFrame > nEnd)
				nNextFrame = nEnd;
		}

	// Reversed playback
	} else {
		nNextFrame = int(m_fFrame);

		// Ping pong (with or without loop)
		if (m_nFlags & PingPong) {
			if (m_nFlags & Loop) {
				// Start reached?
				if (nNextFrame < nStart)
					nNextFrame = nStart+1;
			} else {
				// Start reached?
				if (nNextFrame < nStart)
					nNextFrame = m_bBounced ? nStart : nStart+1;
			}

		// Loop
		} else if (m_nFlags & Loop) {
			// Start reached?
			if (nNextFrame < nStart)
				nNextFrame = nEnd;

		// Normal
		} else {
			// Start reached?
			if (nNextFrame < nStart)
				nNextFrame = nStart;
		}
	}

	// Return the next frame
	return (uint32)nNextFrame;
}

/**
*  @brief
*    Updates the animation
*/
void Animation::Update(float fTimeDifference)
{
	// Update animation
	if (m_bRunning && m_nStart != m_nEnd && m_fSpeed) {
		// Backup the current frame as previous frame
		const float fPreviousFrame = m_fFrame;

		// Get 'real' start and end frames
		uint32 nStart, nEnd;
		if (m_nEnd > m_nStart) {
			nStart = m_nStart;
			nEnd   = m_nEnd;
		} else {
			nStart = m_nEnd;
			nEnd   = m_nStart;
		}

		// Get step size
		float fStep = 0.0;
		if (m_pAnimationInfo) {
			// Is there an advanced frame information?
			const AnimationFrameInfo *pFrameInfo = m_pAnimationInfo->GetFrameInfo(uint32(m_fFrame-nStart));
			if (pFrameInfo) {
				// Get frame speed
				float fFrameSpeed = pFrameInfo->GetSpeed();

				// Skip the frame?
				if (fFrameSpeed) {
					// Ignore the sign in here
					if (fFrameSpeed < 0.0f)
						fFrameSpeed = -fFrameSpeed;

					// Get step size
					fStep = fTimeDifference*fFrameSpeed;
				} else {
					fStep = 1.0f;
				}
			} else {
				fStep = fTimeDifference;
			}
		} else {
			fStep = fTimeDifference;
		}

		// Update the current frame
		m_fFrame += fStep*m_fSpeed;

		// Check bounds
		if (m_fSpeed >= 0.0f) {
			// Ping pong (with or without loop)
			if (m_nFlags & PingPong) {
				if (m_nFlags & Loop) {
					// End reached?
					if (m_fFrame >= (float)nEnd) {
						m_fFrame   = (float)nEnd;
						m_fSpeed   = -m_fSpeed;
						m_bBounced = true;
					}
				} else {
					// End reached?
					if (m_fFrame >= (float)nEnd) {
						m_fFrame = (float)nEnd;
						if (m_bBounced)
							Stop();
						else {
							m_fSpeed   = -m_fSpeed;
							m_bBounced = true;
						}
					}
				}

			// Loop
			} else if (m_nFlags & Loop) {
				// End reached?
				if (m_fFrame >= (float)nEnd)
					m_fFrame = nStart+(m_fFrame-nEnd);

			// Normal
			} else {
				// End reached?
				if (m_fFrame >= (float)nEnd) {
					m_fFrame = (float)nEnd;
					Stop();
				}
			}

		// Reversed playback
		} else {
			// Ping pong (with or without loop)
			if (m_nFlags & PingPong) {
				if (m_nFlags & Loop) {
					// Start reached?
					if (m_fFrame <= (float)nStart) {
						m_fFrame   = (float)nStart;
						m_fSpeed   = -m_fSpeed;
						m_bBounced = true;
					}
				} else {
					// Start reached?
					if (m_fFrame <= (float)nStart) {
						m_fFrame = (float)nStart;
						if (m_bBounced)
							Stop();
						else {
							m_fSpeed   = -m_fSpeed;
							m_bBounced = true;
						}
					}
				}

			// Loop
			} else if (m_nFlags & Loop) {
				// Start reached?
				if (m_fFrame <= (float)nStart)
					m_fFrame = nEnd+(m_fFrame-nStart);

			// Normal
			} else {
				// Start reached?
				if (m_fFrame <= (float)nStart) {
					m_fFrame = (float)nStart;
					Stop();
				}
			}
		}

		// Frame change?
		if (fPreviousFrame != m_fFrame && m_bEvents) {
			// Emit frame change event
			EventFrameChange.Emit();
		}

		// Check if a event is caused
		CheckEvent((int)fPreviousFrame);
	}
}


//[-------------------------------------------------------]
//[ Events                                                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns whether animation events are enabled or not
*/
bool Animation::GetEvents() const
{
	return m_bEvents;
}

/**
*  @brief
*    Sets whether animation events are enabled or not
*/
void Animation::SetEvents(bool bEvents)
{
	m_bEvents = bEvents;
}


//[-------------------------------------------------------]
//[ Operators                                             ]
//[-------------------------------------------------------]
Animation &Animation::operator =(const Animation &cSource)
{
	// Copy data
	m_bActive			= cSource.m_bActive;
	m_bRunning			= cSource.m_bRunning;
	m_nType				= cSource.m_nType;
	m_nFlags			= cSource.m_nFlags;
	m_nStart			= cSource.m_nStart;
	m_nEnd				= cSource.m_nEnd;
	m_fSpeed			= cSource.m_fSpeed;
	m_bEvents			= cSource.m_bEvents;
	m_pAnimationInfo	= cSource.m_pAnimationInfo;
	m_fWeight			= cSource.m_fWeight;
	m_bBounced			= cSource.m_bBounced;

	// Set the current frame
	SetCurrentFrame(cSource.m_fFrame);

	// Done
	return *this;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Check if events should be caused
*/
void Animation::CheckEvent(int nPreviousFrame) const
{
	// Are events enabled?
	if (m_bEvents && m_pAnimationInfo && (int)m_fFrame != nPreviousFrame) {
		for (uint32 i=0; i<m_pAnimationInfo->GetEventManager().GetNumOfElements(); i++) {
			const AnimationEvent *pAnimationEvent = m_pAnimationInfo->GetEventManager().Get(i);
			if (pAnimationEvent->GetFrame() == (uint32)m_fFrame) {
				// Emit event
				EventSpecialFrame.Emit(pAnimationEvent->GetID());
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
