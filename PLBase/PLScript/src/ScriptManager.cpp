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
#include <PLGeneral/File/Url.h>
#include <PLCore/Base/Class.h>
#include <PLCore/Base/ClassManager.h>
#include <PLCore/Tools/LoadableManager.h>
#include "PLScript/Script.h"
#include "PLScript/ScriptBinding.h"
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
*/
String ScriptManager::GetScriptLanguageByExtension(const String &sExtension)
{
	RegisterClasses();
	return m_mapScriptLanguagesByExtension.Get(sExtension);
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
*    Returns a list of all script binding instances
*/
const Array<ScriptBinding*> &ScriptManager::GetScriptBindings()
{
	RegisterClasses();
	return m_lstScriptBindings;
}

/**
*  @brief
*    Creates a script instance
*/
Script *ScriptManager::Create(const String &sScriptLanguage, bool bAddBindings)
{
	// Get the proper script class
	RegisterClasses();
	const Class *pClass = m_mapScriptLanguages.Get(sScriptLanguage);
	if (pClass) {
		// Create an instance of the script class
		Script *pScript = reinterpret_cast<Script*>(pClass->Create());

		// Bind all available script bindings at once?
		if (bAddBindings)
			pScript->AddBindings();

		// Return the created script instance
		return pScript;
	}

	// Error!
	return nullptr;
}

/**
*  @brief
*    Creates a script instance by using a given filename
*/
Script *ScriptManager::CreateFromFile(const String &sFilename, bool bAddBindings)
{
	// Create the script instance by using the extension of the given filename to detect the script language
	Script *pScript = Create(GetScriptLanguageByExtension(Url(sFilename).GetExtension()), bAddBindings);
	if (pScript) {
		// Get the script source code
		const String sSourceCode = LoadableManager::GetInstance()->LoadStringFromFile(sFilename);

		// Set the script source code
		if (!sSourceCode.GetLength() || !pScript->SetSourceCode(sSourceCode)) {
			// Error! Destroy the created script instance...
			delete pScript;
			pScript = nullptr;
		}
	}

	// Done
	return pScript;
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

	{ // Register all script languages
		List<const Class*> lstClasses;
		ClassManager::GetInstance()->GetClasses(lstClasses, "PLScript::Script", Recursive, NoBase, NoAbstract);
		Iterator<const Class*> cIterator = lstClasses.GetIterator();
		while (cIterator.HasNext())
			m_lstNewClasses.Add(cIterator.Next());
	}

	{ // Register all script bindings
		List<const Class*> lstClasses;
		ClassManager::GetInstance()->GetClasses(lstClasses, "PLScript::ScriptBinding", Recursive, NoBase, NoAbstract);
		Iterator<const Class*> cIterator = lstClasses.GetIterator();
		while (cIterator.HasNext())
			m_lstNewClasses.Add(cIterator.Next());
	}
}

/**
*  @brief
*    Destructor
*/
ScriptManager::~ScriptManager()
{
	// Destroy all script binding instances
	for (uint32 i=0; i<m_lstScriptBindings.GetNumOfElements(); i++)
		delete m_lstScriptBindings[i];
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
			static const String sScriptClassString = "PLScript::Script";
			static const String sScriptBindingClassString = "PLScript::ScriptBinding";
			if (pClass->IsDerivedFrom(sScriptClassString)) {
				// Register script language
				const String sLanguage = pClass->GetProperties().Get("Language");
				if (sLanguage.GetLength() && !m_mapScriptLanguages.Get(sLanguage)) {
					m_lstScriptLanguages.Add(sLanguage);
					m_mapScriptLanguages.Add(sLanguage, pClass);

					// Parse formats
					const String sFormats = pClass->GetProperties().Get("Formats");
					if (sFormats.GetLength()) {
						Tokenizer cTokenizer;
						cTokenizer.Start(sFormats);
						cTokenizer.SetDelimiters(" ,\t\r\n");
						cTokenizer.SetSingleChars("");
						String sToken = cTokenizer.GetNextToken();
						while (sToken.GetLength()) {
							m_mapScriptLanguagesByExtension.Add(sToken, sLanguage);
							sToken = cTokenizer.GetNextToken();
						}
						cTokenizer.Stop();
					}
				}
			} else if (pClass->IsDerivedFrom(sScriptBindingClassString)) {
				// Create an script binding instance
				m_lstScriptBindings.Add(static_cast<ScriptBinding*>(pClass->Create()));
			}
		}
		m_lstNewClasses.Clear();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScript
