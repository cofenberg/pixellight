/*********************************************************\
 *  File: AnimationInfo.cpp                              *
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
#include "PLRenderer/Animation/AnimationInfo.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
AnimationInfo::AnimationInfo() :
	m_nType(0),
	m_nStart(0),
	m_nEnd(0),
	m_fSpeed(24.0f),
	m_nFlags(0)
{
}

/**
*  @brief
*    Destructor
*/
AnimationInfo::~AnimationInfo()
{
}

/**
*  @brief
*    Returns the type of the animation
*/
uint32 AnimationInfo::GetType() const
{
	return m_nType;
}

/**
*  @brief
*    Sets the animation type
*/
void AnimationInfo::SetType(uint32 nType)
{
	m_nType = nType;
}

/**
*  @brief
*    Returns the animation start frame
*/
uint32 AnimationInfo::GetStartFrame() const
{
	return m_nStart;
}

/**
*  @brief
*    Sets the animation start frame
*/
void AnimationInfo::SetStartFrame(uint32 nStartFrame)
{
	// Set the start frame
	m_nStart = nStartFrame;

	// Resize frame information
	int i = m_nEnd-m_nStart;
	if (i < 0) i = -i;
	m_lstFrameInfos.Resize(i+1);
}

/**
*  @brief
*    Returns the animation end frame
*/
uint32 AnimationInfo::GetEndFrame() const
{
	return m_nEnd;
}

/**
*  @brief
*    Sets the animation end frame
*/
void AnimationInfo::SetEndFrame(uint32 nEndFrame)
{
	// Set the end frame
	m_nEnd = nEndFrame;

	// Resize frame information
	int i = m_nEnd-m_nStart;
	if (i < 0) i = -i;
	m_lstFrameInfos.Resize(i+1);
}

/**
*  @brief
*    Returns the number of animation frames
*/
uint32 AnimationInfo::GetNumOfFrames() const
{
	return m_nEnd > m_nStart ? m_nEnd-m_nStart+1 : m_nStart-m_nEnd+1;
}

/**
*  @brief
*    Get the animation speed
*/
float AnimationInfo::GetSpeed() const
{
	return m_fSpeed;
}

/**
*  @brief
*    Set the animation speed
*/
void AnimationInfo::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

/**
*  @brief
*    Get the animation information flags
*/
uint32 AnimationInfo::GetFlags() const
{
	return m_nFlags;
}

/**
*  @brief
*    Sets the animation information flags
*/
void AnimationInfo::SetFlags(uint32 nFlags)
{
	m_nFlags = nFlags;
}

/**
*  @brief
*    Returns information about a frame
*/
AnimationFrameInfo *AnimationInfo::GetFrameInfo(uint32 nIndex) const
{
	AnimationFrameInfo &cAnimationFrameInfo = m_lstFrameInfos[nIndex];
	return (&cAnimationFrameInfo != &Array<AnimationFrameInfo>::Null) ? &cAnimationFrameInfo : nullptr;
}

/**
*  @brief
*    Returns the event manager
*/
AnimationEventManager &AnimationInfo::GetEventManager()
{
	return m_cEventManager;
}

const AnimationEventManager &AnimationInfo::GetEventManager() const
{
	return m_cEventManager;
}


//[-------------------------------------------------------]
//[ Public virtual AnimationInfo functions                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy operator
*/
AnimationInfo &AnimationInfo::operator =(const AnimationInfo &cSource)
{
	// Copy data
	m_nType  = cSource.GetType();
	m_nStart = cSource.GetStartFrame();
	m_nEnd   = cSource.GetEndFrame();
	m_fSpeed = cSource.GetSpeed();
	m_nFlags = cSource.GetFlags();

	// Copy frame information
	m_lstFrameInfos = cSource.m_lstFrameInfos;

	// Copy events
	m_cEventManager.Clear();
	for (uint32 i=0; i<m_cEventManager.GetNumOfElements(); i++) {
		const AnimationEvent *pAnimationEvent = m_cEventManager.GetByIndex(i);

		// Added into a manager automatically
		new AnimationEvent(pAnimationEvent->GetID(), pAnimationEvent->GetFrame(),
						   &m_cEventManager, pAnimationEvent->GetName());
	}

	// Return a reference to this instance
	return *this;
}

/**
*  @brief
*    Get the animation source name
*/
String AnimationInfo::GetSourceName() const
{
	// To implement in derived classes
	return "";
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
