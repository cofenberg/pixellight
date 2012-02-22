/*********************************************************\
 *  File: SceneNodeModifier.cpp                          *
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Class.h>
#include "PLScene/Scene/SceneNodeModifier.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
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
	// We now have to reevaluate the active state of this scene node modifier (similar procedure as in "SceneNode::SetFlags()")
	// -> But don't call "SetActive(!(nValue & Inactive));" in here or we will end up in an endless recursion
	if ((m_nFlags & Inactive) != (nValue & Inactive)) {
		// Set new flags
		m_nFlags = nValue;

		// Call the "OnActivate()"-method, please note that we also have to take the global active state of the owner scene node into account
		OnActivate(!(m_nFlags & Inactive) && m_pSceneNode->EvaluateGlobalActiveState());
	} else {
		// Set the new flags
		m_nFlags = nValue;
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Creates a clone of this scene node modifier within the owner scene node
*/
SceneNodeModifier *SceneNodeModifier::Clone()
{
	return m_pSceneNode->AddModifier(GetClass()->GetClassName(), GetValues());
}

/**
*  @brief
*    Creates a clone of this scene node modifier within the owner scene node at a certain index inside the scene node modifier list
*/
SceneNodeModifier *SceneNodeModifier::CloneAtIndex(int nPosition)
{
	return m_pSceneNode->AddModifierAtIndex(GetClass()->GetClassName(), GetValues(), nPosition);
}

/**
*  @brief
*    Returns the scene node class this modifier operates on
*/
String SceneNodeModifier::GetSceneNodeClass() const
{
	const Class *pClass = GetClass();
	return (pClass != nullptr) ? pClass->GetProperties().Get("SceneNodeClass") : "PLScene::SceneNode";
}

/**
*  @brief
*    Returns an unique absolute name for the scene node modifier
*/
String SceneNodeModifier::GetAbsoluteName() const
{
	// Get the scene node modifier class name
	const Class *pClass = GetClass();
	const String sClass = pClass ? pClass->GetClassName() : "";
	if (sClass.GetLength()) {
		// Find a decent scene node modifier index
		int nIndex = -1;
		SceneNodeModifier *pFoundSceneNodeModifier = nullptr;
		do {
			nIndex++;
			pFoundSceneNodeModifier = m_pSceneNode->GetModifier(sClass, static_cast<uint32>(nIndex));
		} while (pFoundSceneNodeModifier && pFoundSceneNodeModifier != this);

		// Return an constructed unique absolute name for the scene node modifier
		return m_pSceneNode->GetAbsoluteName() + ':' + sClass + '.' + nIndex;
	} else {
		// This should never ever happen... but anyway, deal with it...

		// Return a constructed unique absolute name for the scene node modifier
		return m_pSceneNode->GetAbsoluteName() + ":?.42";	// ... as good as any fallback name...
	}
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
		// -> "Flags" is an RTTI get/set attribute calling the virtual method "SetFlags()"
		// -> If required, "SetFlags()" calls "OnActivate()"
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
PLInput::Controller *SceneNodeModifier::GetInputController() const
{
	// The default implementation is empty
	return nullptr;
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
	// The default implementation is empty
}

/**
*  @brief
*    Called when the scene node modifier has been activated or deactivated
*/
void SceneNodeModifier::OnActivate(bool bActivate)
{
	// The default implementation is empty
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
