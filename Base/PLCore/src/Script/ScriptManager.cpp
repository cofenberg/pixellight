/*********************************************************\
 *  File: ScriptManager.cpp                              *
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
#include "PLCore/File/Url.h"
#include "PLCore/Base/Class.h"
#include "PLCore/Base/ClassManager.h"
#include "PLCore/Tools/LoadableManager.h"
#include "PLCore/Script/Script.h"
#include "PLCore/Script/ScriptBinding.h"
#include "PLCore/Script/ScriptManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Template instance                                     ]
//[-------------------------------------------------------]
template class Singleton<ScriptManager>;


//[-------------------------------------------------------]
//[ Public static PLCore::Singleton functions             ]
//[-------------------------------------------------------]
ScriptManager *ScriptManager::GetInstance()
{
	// The compiler should be able to optimize this extra call (inlining)
	return Singleton<ScriptManager>::GetInstance();
}

bool ScriptManager::HasInstance()
{
	// The compiler should be able to optimize this extra call (inlining)
	return Singleton<ScriptManager>::HasInstance();
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the filename extension of a given script language
*/
String ScriptManager::GetScriptLanguageExtension(const String &sScriptLanguage)
{
	RegisterClasses();

	// Get the RTTI class of the given script language
	const Class *pClass = m_mapScriptLanguages.Get(sScriptLanguage);
	if (pClass) {
		// Parse formats
		const String sFormats = pClass->GetProperties().Get("Formats");
		if (sFormats.GetLength()) {
			// Setup the tokenizer
			Tokenizer cTokenizer;
			cTokenizer.Start(sFormats);
			cTokenizer.SetDelimiters(" ,\t\r\n");
			cTokenizer.SetSingleChars("");

			// Return the first found filename extension
			return cTokenizer.GetNextToken();
		}
	}

	// Error!
	return "";
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
Script *ScriptManager::CreateFromFile(const String &sFilename, bool bAddBindings, String::EFormat nStringFormat)
{
	// Create the script instance by using the extension of the given filename to detect the script language
	Script *pScript = Create(GetScriptLanguageByExtension(Url(sFilename).GetExtension()), bAddBindings);
	if (pScript) {
		// Get the script source code
		const String sSourceCode = LoadableManager::GetInstance()->LoadStringFromFile(sFilename, nStringFormat);

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
	ClassManager::GetInstance()->EventClassLoaded.Connect(SlotClassLoaded);

	{ // Register all script languages
		List<const Class*> lstClasses;
		ClassManager::GetInstance()->GetClasses(lstClasses, "PLCore::Script", Recursive, NoBase, NoAbstract);
		Iterator<const Class*> cIterator = lstClasses.GetIterator();
		while (cIterator.HasNext())
			m_lstNewClasses.Add(cIterator.Next());
	}

	{ // Register all script bindings
		List<const Class*> lstClasses;
		ClassManager::GetInstance()->GetClasses(lstClasses, "PLCore::ScriptBinding", Recursive, NoBase, NoAbstract);
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
			static const String sScriptClassString = "PLCore::Script";
			static const String sScriptBindingClassString = "PLCore::ScriptBinding";
			if (pClass->IsDerivedFrom(sScriptClassString)) {
				// Register script language
				const String sLanguage = pClass->GetProperties().Get("Language");
				if (sLanguage.GetLength() && !m_mapScriptLanguages.Get(sLanguage)) {
					m_lstScriptLanguages.Add(sLanguage);
					m_mapScriptLanguages.Add(sLanguage, pClass);

					// Parse formats
					const String sFormats = pClass->GetProperties().Get("Formats");
					if (sFormats.GetLength()) {
						// Setup the tokenizer
						Tokenizer cTokenizer;
						cTokenizer.Start(sFormats);
						cTokenizer.SetDelimiters(" ,\t\r\n");
						cTokenizer.SetSingleChars("");

						// Register the filename extensions of this script language
						String sToken = cTokenizer.GetNextToken();
						while (sToken.GetLength()) {
							m_mapScriptLanguagesByExtension.Add(sToken, sLanguage);
							sToken = cTokenizer.GetNextToken();
						}
					}
				}
			} else if (pClass->IsDerivedFrom(sScriptBindingClassString)) {
				// Create an script binding instance
				ScriptBinding *pScriptBinding = static_cast<ScriptBinding*>(pClass->Create());
				if (pScriptBinding)
					m_lstScriptBindings.Add(pScriptBinding);
			}
		}
		m_lstNewClasses.Clear();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
