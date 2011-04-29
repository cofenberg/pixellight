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
#include <angelscript.h>
#include <PLGeneral/Log/Log.h>
#include "PLScriptAngelScript/AngelScriptContext.h"
#include "PLScriptAngelScript/Script.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLScriptAngelScript {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Script)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
Script::Script() :
	m_pAngelScriptEngine(nullptr),
	m_pAngelScriptModule(nullptr),
	m_pAngelScriptContext(nullptr),
	m_nCurrentArgument(0)
{
}

/**
*  @brief
*    Destructor
*/
Script::~Script()
{
	// Clear the script
	Clear();

	// Release context reference
	if (m_pAngelScriptEngine)
		AngelScriptContext::ReleaseContextReference();
}


//[-------------------------------------------------------]
//[ Public virtual PLScript::Script functions             ]
//[-------------------------------------------------------]
String Script::GetSourceCode() const
{
	return m_sSourceCode;
}

bool Script::SetSourceCode(const String &sSourceCode)
{
	// Backup the given source code
	m_sSourceCode = sSourceCode;

	// Clear the previous script
	Clear();

	// Is there source code?
	if (m_sSourceCode.GetLength()) {
		// Is there already a AngelScript engine instance?
		if (!m_pAngelScriptEngine)
			m_pAngelScriptEngine = AngelScriptContext::AddContextReference();

		// Get a AngelScript module instance
		if (m_pAngelScriptEngine) {
			m_pAngelScriptModule = m_pAngelScriptEngine->GetModule(AngelScriptContext::GetUniqueName().GetASCII(), asGM_ALWAYS_CREATE);
			if (m_pAngelScriptModule) {
				// Add script section
				if (m_pAngelScriptModule->AddScriptSection(Name.Get(), sSourceCode.GetASCII(), sSourceCode.GetLength()) >= 0) {
					// Compile the script
					const int nResult = m_pAngelScriptModule->Build();
					if (nResult >= 0) {
						// Done
						return true;
					} else {
						// Error!
						String sErrorDescription;
						switch (nResult) {
							case asINVALID_CONFIGURATION:
								sErrorDescription = " (The AngelScript engine configuration is invalid)";
								break;

							case asERROR:
								sErrorDescription = " (The script failed to build)";
								break;

							case asBUILD_IN_PROGRESS:
								sErrorDescription = " (Another thread is currently building)";
								break;

							case asINIT_GLOBAL_VARS_FAILED:
								sErrorDescription = " (It was not possible to initialize at least one of the global variables)";
								break;
						}
						LogOutput(Log::Error, "Failed to compile the script" + sErrorDescription);
					}
				} else {
					// Error!
					LogOutput(Log::Error, "Failed to add script section");
				}
			}
		}
	}

	// Error!
	return false;
}

bool Script::BeginCall(const String &sFunctionName, const String &sFunctionSignature)
{
	// There must be a valid AngelScript engine and module instance
	if (m_pAngelScriptEngine && m_pAngelScriptModule) {
		// Is there already a context instance that will execute the script?
		if (!m_pAngelScriptContext) {
			m_pAngelScriptContext = m_pAngelScriptEngine->CreateContext();
			if (!m_pAngelScriptContext)
				LogOutput(Log::Error, "Failed to create the context");

			// [TODO] Add SetLineCallback
			//		cout << "Failed to set the line callback function." << endl;
		}
		if (m_pAngelScriptContext) {
			// Construct the function declaration
			String sFunctionDeclaration = sFunctionSignature;	// Get the signature of the given dynamic parameters (e.g. "void(int,float)")
			const int nIndex = sFunctionDeclaration.IndexOf("(");
			if (nIndex > -1)
				sFunctionDeclaration.Insert(' ' + sFunctionName, nIndex);

			// Find the function ID for the function we want to execute
			const int nFunctionID = m_pAngelScriptModule->GetFunctionIdByDecl(sFunctionDeclaration);
			if (nFunctionID >= 0) {
				// Prepare the script context with the function we wish to execute
				int nResult = m_pAngelScriptContext->Prepare(nFunctionID);
				if (nResult >= 0) {
					// Current argument is 0
					m_nCurrentArgument = 0;

					// Done
					return true;
				} else {
					// Error!
					LogOutput(Log::Error, "Failed to prepare the context");
				}
			} else {
				// Error!
				LogOutput(Log::Error, "The function '" + sFunctionDeclaration + "' was not found");
			}
		}
	}

	// Error!
	return false;
}

void Script::PushArgument(uint8 nValue)
{
	if (m_pAngelScriptContext)
		m_pAngelScriptContext->SetArgByte(m_nCurrentArgument++, nValue);
}

void Script::PushArgument(uint16 nValue)
{
	if (m_pAngelScriptContext)
		m_pAngelScriptContext->SetArgWord(m_nCurrentArgument++, nValue);
}

void Script::PushArgument(uint32 nValue)
{
	if (m_pAngelScriptContext)
		m_pAngelScriptContext->SetArgDWord(m_nCurrentArgument++, nValue);
}

void Script::PushArgument(float fValue)
{
	if (m_pAngelScriptContext)
		m_pAngelScriptContext->SetArgFloat(m_nCurrentArgument++, fValue);
}

void Script::PushArgument(double fValue)
{
	if (m_pAngelScriptContext)
		m_pAngelScriptContext->SetArgDouble(m_nCurrentArgument++, fValue);
}

bool Script::EndCall()
{
	if (m_pAngelScriptContext) {
		// Execute the function
		const int nResult = m_pAngelScriptContext->Execute();
		if (nResult == asEXECUTION_FINISHED) {
			// Done
			return true;
		} else {
			// The execution didn't finish as we had planned. Determine why.
			if (nResult == asEXECUTION_ABORTED) {
				LogOutput(Log::Error, "The script was aborted before it could finish. Probably it timed out.");
			} else if (nResult == asEXECUTION_EXCEPTION) {
				LogOutput(Log::Error, "The script ended with an exception");

				// Write some information about the script exception
				const int nExceptionFunctionID = m_pAngelScriptContext->GetExceptionFunction();
				asIScriptFunction *pAngelScriptFunction = m_pAngelScriptEngine->GetFunctionDescriptorById(nExceptionFunctionID);
				String sErrorDescription;
				sErrorDescription += String("Function: ")	+ pAngelScriptFunction->GetDeclaration()			+ '\n';
				sErrorDescription += String("Module: ")		+ pAngelScriptFunction->GetModuleName()				+ '\n';
				sErrorDescription += String("Section: ")	+ pAngelScriptFunction->GetScriptSectionName()		+ '\n';
				sErrorDescription += String("Line: ")		+ m_pAngelScriptContext->GetExceptionLineNumber()	+ '\n';
				sErrorDescription += String("Desciption: ")	+ m_pAngelScriptContext->GetExceptionString()		+ '\n';
				LogOutput(Log::Error, sErrorDescription);
			} else {
				LogOutput(Log::Error, String("The script ended for some unforeseen reason (")  + nResult + ")");
			}
		}
	}

	// Error!
	return false;
}

void Script::GetReturn(uint8 &nValue)
{
	nValue = m_pAngelScriptContext ? m_pAngelScriptContext->GetReturnByte() : 0;
}

void Script::GetReturn(uint16 &nValue)
{
	nValue = m_pAngelScriptContext ? m_pAngelScriptContext->GetReturnWord() : 0;
}

void Script::GetReturn(uint32 &nValue)
{
	nValue = m_pAngelScriptContext ? m_pAngelScriptContext->GetReturnDWord() : 0;
}

void Script::GetReturn(float &fValue)
{
	fValue = m_pAngelScriptContext ? m_pAngelScriptContext->GetReturnFloat() : 0;
}

void Script::GetReturn(double &fValue)
{
	fValue = m_pAngelScriptContext ? m_pAngelScriptContext->GetReturnDouble() : 0;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Script::Script(const Script &cSource) :
	m_pAngelScriptEngine(nullptr),
	m_pAngelScriptModule(nullptr),
	m_pAngelScriptContext(nullptr),
	m_nCurrentArgument(0)
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

/**
*  @brief
*    Clears the script
*/
void Script::Clear()
{
	// Release the AngelScript context instance
	if (m_pAngelScriptContext) {
		m_pAngelScriptContext->Release();
		m_pAngelScriptContext = nullptr;
	}

	// Destroy the AngelScript module instance
	if (m_pAngelScriptModule) {
		m_pAngelScriptModule->GetEngine()->DiscardModule(m_pAngelScriptModule->GetName());
		m_pAngelScriptModule = nullptr;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptAngelScript
