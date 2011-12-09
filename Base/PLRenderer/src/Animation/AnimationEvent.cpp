/*********************************************************\
 *  File: AnimationEvent.cpp                             *
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
#include "PLRenderer/Animation/AnimationEvent.h"


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
AnimationEvent::AnimationEvent(int nID, uint32 nFrame, AnimationEventManager *pManager, const String &sName) :
	Element<AnimationEvent>(sName, pManager),
	m_nID(nID),
	m_nFrame(nFrame)
{
	if (pManager && !sName.GetLength())
		SetName(String("Event ") + pManager->GetNumOfElements());
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Element functions              ]
//[-------------------------------------------------------]
AnimationEvent &AnimationEvent::operator =(const AnimationEvent &cSource)
{
	// Call base function
	*static_cast<Element<AnimationEvent>*>(this) = cSource;

	// Copy data
	m_nID    = cSource.m_nID;
	m_nFrame = cSource.m_nFrame;

	// Return pointer
	return *this;
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ElementManager functions      ]
//[-------------------------------------------------------]
AnimationEvent *AnimationEventManager::CreateElement(const String &sName)
{
	return new AnimationEvent(0, 0, this, sName);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
