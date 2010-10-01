/*********************************************************\
 *  File: SceneNodeModifier.cpp                          *
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
#include "PLScene/Scene/SceneNodeModifier.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLInput;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SceneNodeModifier)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
uint32 SceneNodeModifier::GetFlags() const
{
	return m_nFlags;
}

void SceneNodeModifier::SetFlags(uint32 nValue)
{
	m_nFlags = nValue;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the owner scene node
*/
SceneNode &SceneNodeModifier::GetSceneNode() const
{
	return *m_pSceneNode;
}

/**
*  @brief
*    Returns the scene node class this modifier operates on
*/
String SceneNodeModifier::GetSceneNodeClass() const
{
	const Class *pClass = GetClass();
	return (pClass != NULL) ? pClass->GetProperties().Get("SceneNodeClass") : "PLScene::SceneNode";
}

/**
*  @brief
*    Is the scene node modifier active?
*/
bool SceneNodeModifier::IsActive() const
{
	return !(m_nFlags & Inactive);
}

/**
*  @brief
*    Sets whether the scene node modifier is active or not
*/
void SceneNodeModifier::SetActive(bool bActive)
{
	// State change?
	if (!(m_nFlags & Inactive) != bActive) {
		// Get new flags
		uint32 nNewFlags = m_nFlags;
		if (bActive)
			nNewFlags &= ~Inactive;
		else
			nNewFlags |=  Inactive;

		// Set new flags
		Flags = nNewFlags;
	}
}


//[-------------------------------------------------------]
//[ Public virtual SceneNodeModifier functions            ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get input controller
*/
Controller *SceneNodeModifier::GetInputController() const
{
	// The default implementation is empty
	return NULL;
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
/**
*  @brief
*    Informed on scene node modifier initialization
*/
void SceneNodeModifier::InformedOnInit()
{
	SetFlags(GetFlags());
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SceneNodeModifier::SceneNodeModifier(SceneNode &cSceneNode) :
	Flags(this),
	m_nFlags(0),
	m_pSceneNode(&cSceneNode)
{
}

/**
*  @brief
*    Destructor
*/
SceneNodeModifier::~SceneNodeModifier()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
