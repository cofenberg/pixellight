/*********************************************************\
 *  File: Script.cpp                                     *
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
#include "PLCore/Log/Log.h"
#include "PLCore/Base/Class.h"
#include "PLCore/Script/ScriptManager.h"
#include "PLCore/Script/Script.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Script)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
Script::~Script()
{
}

/**
*  @brief
*    Returns the name of the script language the script is using
*/
String Script::GetScriptLanguage() const
{
	return GetClass() ? GetClass()->GetProperties().Get("Language") : "";
}

/**
*  @brief
*    Returns a list of file formats this script supports
*/
void Script::GetFormats(Array<String> &lstFormats) const
{
	const String sFormats = GetClass()->GetProperties().Get("Formats");
	if (sFormats.GetLength()) {
		Tokenizer cTokenizer;
		cTokenizer.Start(sFormats);
		cTokenizer.SetDelimiters(" ,\t\r\n");
		cTokenizer.SetSingleChars("");
		String sToken = cTokenizer.GetNextToken();
		while (sToken.GetLength()) {
			lstFormats.Add(sToken);
			sToken = cTokenizer.GetNextToken();
		}
		cTokenizer.Stop();
	}
}

/**
*  @brief
*    Adds a script binding to connect the given RTTI class instance with this script
*/
void Script::AddBinding(Object &cObject, const String &sNamespace)
{
	// Get a list of all callable RTTI methods of the given RTTI class instance
	List<DynFuncPtr> lstMethods;
	cObject.GetMethods(lstMethods);

	// Add all methods to this script
	Iterator<DynFuncPtr> cIterator = lstMethods.GetIterator();
	while (cIterator.HasNext()) {
		// Get the dynamic function
		DynFunc *pDynFunc = cIterator.Next();

		// Get the function descriptor
		const FuncDesc *pFuncDesc = pDynFunc->GetDesc();
		if (pFuncDesc)
			AddGlobalFunction(pFuncDesc->GetName(), *pDynFunc, sNamespace);
	}
}

/**
*  @brief
*    Add all script bindings to this script
*/
void Script::AddBindings()
{
	// Get a list of all script binding instances
	const Array<ScriptBinding*> &lstScriptBindings = ScriptManager::GetInstance()->GetScriptBindings();
	for (uint32 i=0; i<lstScriptBindings.GetNumOfElements(); i++) {
		Object *pScriptBinding = reinterpret_cast<Object*>(lstScriptBindings[i]);
		AddBinding(*pScriptBinding, pScriptBinding->GetClass()->GetProperties().Get("Namespace"));
	}
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Script::Script() :
	Name(this)
{
}

/**
*  @brief
*    Write a string into the log
*/
bool Script::LogOutput(uint8 nLogLevel, const String &sText)
{
	return Log::GetInstance()->Output(nLogLevel, (Name.Get().GetLength() ? ("Script '" + Name.Get() + "': ") : "Script: ") + sText);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Script::Script(const Script &cSource) :
	Name(this)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Script &Script::operator =(const Script &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
