/*********************************************************\
 *  File: AnimationEvent.inl                             *
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
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the event ID
*/
inline int AnimationEvent::GetID() const
{
	return m_nID;
}

/**
*  @brief
*    Sets the event ID
*/
inline void AnimationEvent::SetID(int nID)
{
	m_nID = nID;
}

/**
*  @brief
*    Returns the frame which will cause this event
*/
inline PLCore::uint32 AnimationEvent::GetFrame() const
{
	return m_nFrame;
}

/**
*  @brief
*    Sets the frame causing this event
*/
inline void AnimationEvent::SetFrame(PLCore::uint32 nFrame)
{
	m_nFrame = nFrame;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
