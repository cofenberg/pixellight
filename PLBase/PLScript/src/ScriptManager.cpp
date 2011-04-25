/*********************************************************\
 *  File: ScriptManager.cpp                              *
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
#include <PLCore/Base/Class.h>
#include <PLCore/Base/ClassManager.h>
#include "PLScript/ScriptManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLScript {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns a list of supported script languages
*/
const Array<String> &ScriptManager::GetScriptLanguages()
{
	RegisterClasses();
	return m_lstScriptLanguages;
}

/**
*  @brief
*    Checks whether or not a given script language is supported
*/
bool ScriptManager::IsSupported(const String &sScriptLanguage)
{
	RegisterClasses();
	return (m_mapScriptLanguages.Get(sScriptLanguage) != nullptr);
}

/**
*  @brief
*    Creates a script instance
*/
Script *ScriptManager::Create(const String &sScriptLanguage)
{
	// Get the proper script class and create an instance of it
	RegisterClasses();
	const Class *pClass = m_mapScriptLanguages.Get(sScriptLanguage);
	if (pClass)
		return reinterpret_cast<Script*>(pClass->Create());

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ScriptManager::ScriptManager() :
	SlotClassLoaded(&ScriptManager::OnClassLoaded, this)
{
	// The script manager MUST be informed if new classes are registered in order to register new script languages!
	ClassManager::GetInstance()->EventClassLoaded.Connect(&SlotClassLoaded);

	// Register all script languages
	List<const Class*> lstClasses;
	ClassManager::GetInstance()->GetClasses(lstClasses, "PLScript::Script", Recursive, NoBase, NoAbstract);
	Iterator<const Class*> cIterator = lstClasses.GetIterator();
	while (cIterator.HasNext())
		m_lstNewClasses.Add(cIterator.Next());
}

/**
*  @brief
*    Destructor
*/
ScriptManager::~ScriptManager()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Register a class
*/
void ScriptManager::OnClassLoaded(const Class *pClass)
{
	// Just put the new class on the queue - because we can't assume that this class is or can be initialized
	// already, we can't even excpect "IsDerivedFrom" to work, so, just REALLY note this class in here!
	m_lstNewClasses.Add(pClass);
}

/**
*  @brief
*    Registers queued classes
*/
void ScriptManager::RegisterClasses()
{
	// Is there anything on the register queue?
	if (m_lstNewClasses.GetNumOfElements()) {
		Iterator<const Class*> cIterator = m_lstNewClasses.GetIterator();
		while (cIterator.HasNext()) {
			// Get the class
			const Class *pClass = cIterator.Next();

			// Check parameter and base class
			static const String sClassString = "PLScript::Script";
			if (pClass->IsDerivedFrom(sClassString)) {
				// Register script language
				const String sLanguage = pClass->GetProperties().Get("Language");
				if (sLanguage.GetLength() && !m_mapScriptLanguages.Get(sLanguage)) {
					m_lstScriptLanguages.Add(sLanguage);
					m_mapScriptLanguages.Add(sLanguage, pClass);
				}
			}
		}
		m_lstNewClasses.Clear();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScript
