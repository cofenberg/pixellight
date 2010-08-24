/*********************************************************\
 *  File: SNMDeactivationOnTimeout.cpp                   *
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
#include <PLGeneral/Tools/Timing.h>
#include "PLScene/Scene/SceneNode.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMDeactivationOnTimeout.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMDeactivationOnTimeout)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SNMDeactivationOnTimeout::SetFlags(uint32 nValue)
{
	// Call base implementation
	SceneNodeModifier::SetFlags(nValue);

	// Connect/disconnect event handler
	if (IsActive())
		GetSceneNode().EventUpdate.Connect(&EventHandlerUpdate);
	else
		GetSceneNode().EventUpdate.Disconnect(&EventHandlerUpdate);
}


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
float SNMDeactivationOnTimeout::GetTimeout() const
{
	return m_fTimeout;
}

void SNMDeactivationOnTimeout::SetTimeout(float fValue)
{
	m_fTimeout = fValue;
	m_fTimer   = 0.0f;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMDeactivationOnTimeout::SNMDeactivationOnTimeout(SceneNode &cSceneNode) : SceneNodeModifier(cSceneNode),
	Timeout(this),
	EventHandlerUpdate(&SNMDeactivationOnTimeout::NotifyUpdate, this),
	m_fTimeout(5.0f),
	m_fTimer(0.0f)
{
}

/**
*  @brief
*    Destructor
*/
SNMDeactivationOnTimeout::~SNMDeactivationOnTimeout()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNMDeactivationOnTimeout::NotifyUpdate()
{
	// Still active?
	if (m_fTimer < m_fTimeout) {
		// Update the timer
		m_fTimer += Timing::GetInstance()->GetTimeDifference();

		// Timeout?
		if (m_fTimer >= m_fTimeout) {
			m_fTimer = m_fTimeout;
			GetSceneNode().SetActive(false);
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
