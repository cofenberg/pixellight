/*********************************************************\
 *  File: SNMLightRandomAnimation.cpp                    *
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
#include <PLGeneral/Tools/Timing.h>
#include "PLScene/Scene/SNLight.h"
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMLightRandomAnimation.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMLightRandomAnimation)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMLightRandomAnimation::SNMLightRandomAnimation(SceneNode &cSceneNode) : SceneNodeModifier(cSceneNode),
	Speed(this),
	Radius(this),
	FixColor(this),
	Color(this),
	Flags(this),
	EventHandlerUpdate(&SNMLightRandomAnimation::OnUpdate, this),
	m_fTimer(0.0f)
{
}

/**
*  @brief
*    Destructor
*/
SNMLightRandomAnimation::~SNMLightRandomAnimation()
{
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
void SNMLightRandomAnimation::OnActivate(bool bActivate)
{
	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate)
			pSceneContext->EventUpdate.Connect(EventHandlerUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(EventHandlerUpdate);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node modifier needs to be updated
*/
void SNMLightRandomAnimation::OnUpdate()
{
	// Update timer
	m_fTimer += Timing::GetInstance()->GetTimeDifference()*Speed;

	// Set current scene node scale
	SNLight &cLight = static_cast<SNLight&>(GetSceneNode());

	// Animate color
		  Color3 cColor  = cLight.Color.Get();
	const Color3 cColorT = Color.Get()*((Math::Cos(m_fTimer)+1)/2)*Radius;
	if (GetFlags() & Multiply) {
		// Red
		cColor.r = (GetFlags() & NR) ? FixColor.Get().r : FixColor.Get().r*cColorT.r;
		// Green
		cColor.g = (GetFlags() & NG) ? FixColor.Get().g : FixColor.Get().g*cColorT.g;
		// Blue
		cColor.b = (GetFlags() & NB) ? FixColor.Get().b : FixColor.Get().b*cColorT.b;
	} else {
		// Red
		cColor.r = (GetFlags() & NR) ? FixColor.Get().r : FixColor.Get().r+cColorT.r;
		// Green
		cColor.g = (GetFlags() & NG) ? FixColor.Get().g : FixColor.Get().g+cColorT.g;
		// Blue
		cColor.b = (GetFlags() & NB) ? FixColor.Get().b : FixColor.Get().b+cColorT.b;
	}

	// Clamp the color values between 0.0 and 1.0
	cColor.Saturate();

	// Finally, set the new color of the light
	cLight.Color.Set(cColor);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
