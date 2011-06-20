/*********************************************************\
 *  File: SNMScript.cpp                                  *
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
#include <PLCore/Script/Script.h>
#include <PLCore/Script/FuncScriptPtr.h>
#include <PLCore/Script/ScriptManager.h>
#include <PLScene/Scene/SceneContext.h>
#include "PLScriptBindings/SNMScript.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLScene;
namespace PLScriptBindings {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMScript)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String SNMScript::GetScript() const
{
	return m_sScript;
}

void SNMScript::SetScript(const String &sValue)
{
	// Backup the given string
	m_sScript = sValue;

	// Destroy the used script
	DestroyScript();

	// Create the script instance
	m_pScript = ScriptManager::GetInstance()->CreateFromFile(m_sScript);
	if (m_pScript) {
		// Add the global variable "this" to the script so that it's able to access "this" RTTI class instance
		m_pScript->SetGlobalVariable("this", Var<Object*>(this));

		// Call the initialize script function, but only when it's really there because it's optional
		if (m_pScript->IsGlobalFunction(OnInitFunction.Get()))
			FuncScriptPtr<void>(m_pScript, OnInitFunction.Get()).Call(Params<void>());
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMScript::SNMScript(SceneNode &cSceneNode) : SceneNodeModifier(cSceneNode),
	Script(this),
	OnInitFunction(this),
	OnUpdateFunction(this),
	OnDeInitFunction(this),
	SlotOnUpdate(this),
	m_pScript(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
SNMScript::~SNMScript()
{
	// Destroy the used script
	DestroyScript();
}

/**
*  @brief
*    Returns the instance of the used script
*/
Script *SNMScript::GetScriptInstance() const
{
	return m_pScript;
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
void SNMScript::OnActivate(bool bActivate)
{
	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate)
			pSceneContext->EventUpdate.Connect(SlotOnUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(SlotOnUpdate);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destroys the script
*/
void SNMScript::DestroyScript()
{
	// Is there a script?
	if (m_pScript) {
		// Call the de-initialize script function, but only when it's really there because it's optional
		if (m_pScript->IsGlobalFunction(OnDeInitFunction.Get()))
			FuncScriptPtr<void>(m_pScript, OnDeInitFunction.Get()).Call(Params<void>());

		// Destroy the used script instance
		delete m_pScript;
		m_pScript = nullptr;
	}
}

/**
*  @brief
*    Called when the scene node modifier needs to be updated
*/
void SNMScript::OnUpdate()
{
	// Is there a script? If so, do also check whether or not our optional global script function is there.
	if (m_pScript && m_pScript->IsGlobalFunction(OnUpdateFunction.Get())) {
		// Call the update script function
		FuncScriptPtr<void>(m_pScript, OnUpdateFunction.Get()).Call(Params<void>());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptBindings
