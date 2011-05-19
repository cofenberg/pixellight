/*********************************************************\
 *  File: AnimationManager.cpp                           *
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
#include <PLRenderer/Animation/Animation.h>
#include "PLRenderer/Animation/AnimationManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
AnimationManager::AnimationManager() :
	EventHandlerFrameChange(&AnimationManager::NotifyFrameChange, this)
{
	// Init data
	SetManagerName("Animation manager");
}

/**
*  @brief
*    Destructor
*/
AnimationManager::~AnimationManager()
{
}


//[-------------------------------------------------------]
//[ Protected virtual PLGeneral::ElementManager functions ]
//[-------------------------------------------------------]
Animation *AnimationManager::CreateElement(const String &sName)
{
	// Create the new animation
	Animation *pAnimation = new Animation(sName, this);

	// Connect event handler
	pAnimation->EventFrameChange.Connect(&EventHandlerFrameChange);

	// Return the new animation
	return pAnimation;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the frame of an animation manager animation has been changed
*/
void AnimationManager::NotifyFrameChange()
{
	// Emit own event
	EventAnimationFrameChange();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
