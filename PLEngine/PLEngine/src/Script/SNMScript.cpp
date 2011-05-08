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
#include <PLGeneral/File/Url.h>
#include <PLGeneral/Tools/Timing.h>
#include <PLCore/Tools/LoadableManager.h>
#include <PLScript/Script.h>
#include <PLScript/FuncScriptPtr.h>
#include <PLScript/ScriptManager.h>
#include <PLScene/Scene/SceneContext.h>

// [TODO] This is just a first test
#include "PLEngine/Script/ScriptBindingTiming.h"
#include "PLEngine/Script/ScriptBindingLog.h"

#include "PLEngine/Script/SNMScript.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLScript;
using namespace PLScene;
namespace PLEngine {


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
		if (m_pScript) {
			delete m_pScript;
			m_pScript = nullptr;
		}

		// Get the script source code
		const String sSourceCode = LoadableManager::GetInstance()->LoadStringFromFile(m_sScript);
		if (sSourceCode.GetLength()) {
			// Create the script instance by using the extension of the given filename to detect the script language
			m_pScript = ScriptManager::GetInstance()->Create(ScriptManager::GetInstance()->GetScriptLanguageByExtension(Url(m_sScript).GetExtension()));
			if (m_pScript) {

				// [TODO] This is just a first test
				m_pScript->AddBinding(*m_pScriptBindingTiming, "PL.Timing");
				m_pScript->AddBinding(*m_pScriptBindingLog, "PL.Log");

				// Set the script source code
				if (m_pScript->SetSourceCode(sSourceCode)) {
					// Done
				}
			}
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
	EventHandlerUpdate(&SNMScript::NotifyUpdate, this),
	m_pScript(nullptr)
{
	// [TODO] This is just a first test
	m_pScriptBindingTiming = new ScriptBindingTiming();
	m_pScriptBindingLog = new ScriptBindingLog();
}

/**
*  @brief
*    Destructor
*/
SNMScript::~SNMScript()
{
	// [TODO] This is just a first test
	delete m_pScriptBindingTiming;
	delete m_pScriptBindingLog;

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
			pSceneContext->EventUpdate.Connect(&EventHandlerUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(&EventHandlerUpdate);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node modifier needs to be updated
*/
void SNMScript::NotifyUpdate()
{
	// Is there a script and script function?
	if (m_pScript && UpdateFunction.Get().GetLength()) {
		// Call the update script function
		FuncScriptPtr<void>(m_pScript, UpdateFunction.Get()).Call(Params<void>());

		// [TODO] This is just a first test
		{ // Call the script function "getFactor"
			// Get the typed dynamic parameters
			Params<float> cParams;

			// Call the script function
			FuncScriptPtr<float>(m_pScript, "getFactor").Call(cParams);

			// Get the result
			float fFactor = cParams.Return;
			float td = Timing::GetInstance()->GetTimeDifference();
			float t = 0;
		}

	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
