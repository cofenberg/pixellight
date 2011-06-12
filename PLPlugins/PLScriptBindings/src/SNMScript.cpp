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
	if (m_sScript != sValue) {
		m_sScript = sValue;

		// Destroy the used script
		if (m_pScript)
			delete m_pScript;

		// Create the script instance
		m_pScript = ScriptManager::GetInstance()->CreateFromFile(m_sScript);
		if (m_pScript) {
			// Add the global variable "this" to the script so that it's able to access "this" RTTI class instance
			m_pScript->SetGlobalVariable("this", Var<Object*>(this));
		}
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
	UpdateFunction(this),
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
	if (m_pScript)
		delete m_pScript;
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
			pSceneContext->EventUpdate.Connect(&SlotOnUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(&SlotOnUpdate);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node modifier needs to be updated
*/
void SNMScript::OnUpdate()
{
	// Is there a script and script function?
	if (m_pScript && UpdateFunction.Get().GetLength()) {
		// Call the update script function
		FuncScriptPtr<void>(m_pScript, UpdateFunction.Get()).Call(Params<void>());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptBindings
