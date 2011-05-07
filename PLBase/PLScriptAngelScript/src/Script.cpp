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

	// Remove all dynamic functions
	RemoveAllDynamicFunctions();

	// Release context reference
	if (m_pAngelScriptEngine)
		AngelScriptContext::ReleaseContextReference();
}


//[-------------------------------------------------------]
//[ Public virtual PLScript::Script functions             ]
//[-------------------------------------------------------]
bool Script::AddDynamicFunction(const String &sFunction, const DynFunc &cDynFunc, const String &sNamespace)
{
	// Is there already a AngelScript engine instance?
	if (m_pAngelScriptEngine) {
		// Error!
		return false;
	} else {
		// Add the dynamic function
		DynamicFunction *psDynamicFunction = new DynamicFunction;
		psDynamicFunction->sFunction  = sFunction;
		psDynamicFunction->pDynFunc   = cDynFunc.Clone();
		psDynamicFunction->sNamespace = sNamespace;
		m_lstDynamicFunctions.Add(psDynamicFunction);

		// Done
		return true;
	}
}

bool Script::RemoveAllDynamicFunctions()
{
	// Is there already a AngelScript engine instance?
	if (m_pAngelScriptEngine) {
		// Error!
		return false;
	} else {
		// Destroy the dynamic functions
		for (uint32 i=0; i<m_lstDynamicFunctions.GetNumOfElements(); i++) {
			delete m_lstDynamicFunctions[i]->pDynFunc;
			delete m_lstDynamicFunctions[i];
		}
		m_lstDynamicFunctions.Clear();

		// Done
		return true;
	}
}

String Script::GetSourceCode() const
{
	return m_sSourceCode;
}

bool Script::SetSourceCode(const String &sSourceCode)
{
	// Clear the previous script
	Clear();

	// Backup the given source code
	m_sSourceCode = sSourceCode;

	// Is there source code?
	if (m_sSourceCode.GetLength()) {
		// Is there already a AngelScript engine instance?
		if (!m_pAngelScriptEngine)
			m_pAngelScriptEngine = AngelScriptContext::AddContextReference();

		// Get a AngelScript module instance
		if (m_pAngelScriptEngine) {
			// Add the dynamic functions
			for (uint32 i=0; i<m_lstDynamicFunctions.GetNumOfElements(); i++) {
				// Get the dynamic function
				DynamicFunction *psDynamicFunction = m_lstDynamicFunctions[i];

				// [TODO] It looks like that AngelScript (2.20.2) has currently no support for namespaces... so right now I'am doing
				// an ugly hack: e.g. "PL.Timing.GetTimeDifference()" is written within scripts as "PL_Timing_GetTimeDifference()"
				String sFunction;
				if (psDynamicFunction->sNamespace.GetLength()) {
					sFunction = psDynamicFunction->sNamespace;
					sFunction.Replace('.', '_');
					sFunction += '_';
					sFunction += psDynamicFunction->sFunction;
				} else {
					sFunction = psDynamicFunction->sFunction;
				}

				// Get the AngelScript function declaration
				String sFunctionDeclaration = GetAngelScriptFunctionDeclaration(sFunction, psDynamicFunction->pDynFunc->GetSignature());

				// Register global AngelScript function
				const int nFunctionID = m_pAngelScriptEngine->RegisterGlobalFunction(sFunctionDeclaration, asFUNCTION(AngelScriptFunctionCallback), asCALL_GENERIC);
				if (nFunctionID < 0) {
					// Error!
					String sErrorDescription;
					switch (nFunctionID) {
						case asNOT_SUPPORTED:
							sErrorDescription = " (The calling convention is not supported)";
							break;

						case asWRONG_CALLING_CONV:
							sErrorDescription = " (The function's calling convention doesn't match callConv)";
							break;

						case asINVALID_DECLARATION:
							sErrorDescription = " (The function declaration is invalid)";
							break;

						case asNAME_TAKEN:
							sErrorDescription = " (The function name is already used elsewhere)";
							break;
					}
					LogOutput(Log::Error, "Failed to register the global AngelScript function '" + sFunctionDeclaration + '\'');
				} else {
					// Put a pointer to the dynamic function into the user data of the registered AngelScript function
					asIScriptFunction *pAngelScriptFunction = m_pAngelScriptEngine->GetFunctionDescriptorById(nFunctionID);
					if (pAngelScriptFunction)
						pAngelScriptFunction->SetUserData(psDynamicFunction);
				}
			}

			// Get the AngelScript module
			m_pAngelScriptModule = m_pAngelScriptEngine->GetModule(AngelScriptContext::GetUniqueName(), asGM_ALWAYS_CREATE);
			if (m_pAngelScriptModule) {
				// Add script section
				if (m_pAngelScriptModule->AddScriptSection(Name.Get(), sSourceCode, sSourceCode.GetLength()) >= 0) {
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
	} else {
		// No script at all - done
		return true;
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
			// Get the AngelScript function declaration
			const String sFunctionDeclaration = GetAngelScriptFunctionDeclaration(sFunctionName, sFunctionSignature);

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
					String sErrorDescription;
					switch (nResult) {
						case asCONTEXT_ACTIVE:
							// If your're here, you may have tried to call a script function by using PixelLights functors,
							// AngelScript can only run one function per script context call...
							sErrorDescription = " (The context is still active or suspended)";
							break;

						case asNO_FUNCTION:
							sErrorDescription = " (The function id doesn't exist)";
							break;
					}
					LogOutput(Log::Error, "Failed to prepare the context for the function '" + sFunctionDeclaration + "'" + sErrorDescription);
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

void Script::PushArgument(int nValue)
{
	if (m_pAngelScriptContext)
		m_pAngelScriptContext->SetArgDWord(m_nCurrentArgument++, nValue);
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

void Script::GetReturn(int &nValue)
{
	nValue = m_pAngelScriptContext ? m_pAngelScriptContext->GetReturnDWord() : 0;
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
//[ Private static AngelScript callback functions         ]
//[-------------------------------------------------------]
/*
*  @brief
*    AngelScript function callback
*/
void Script::AngelScriptFunctionCallback(asIScriptGeneric *pAngelScriptGeneric)
{
	// Get the dynamic function
	DynamicFunction *psDynamicFunction = reinterpret_cast<DynamicFunction*>(pAngelScriptGeneric->GetFunctionUserData());

	// Get the number of arguments AngelScript gave to us and transform the arguments into a functor parameters string
	String sParams;
	const int nNumOfArguments = pAngelScriptGeneric->GetArgCount();
	for (int i=0; i<nNumOfArguments; i++) {
		String sValue;
		switch (pAngelScriptGeneric->GetArgTypeId(i)) {
			case asTYPEID_BOOL:		sValue = pAngelScriptGeneric->GetArgByte(i);						break;
			case asTYPEID_INT8:		sValue = pAngelScriptGeneric->GetArgByte(i);						break;
			case asTYPEID_INT16:	sValue = pAngelScriptGeneric->GetArgWord(i);						break;
			case asTYPEID_INT32:	sValue = static_cast<uint32>(pAngelScriptGeneric->GetArgDWord(i));	break;
			case asTYPEID_INT64:	sValue = pAngelScriptGeneric->GetArgQWord(i);						break;
			case asTYPEID_UINT8:	sValue = pAngelScriptGeneric->GetArgByte(i);						break;
			case asTYPEID_UINT16:	sValue = pAngelScriptGeneric->GetArgWord(i);						break;
			case asTYPEID_UINT32:	sValue = static_cast<uint32>(pAngelScriptGeneric->GetArgDWord(i));	break;
			case asTYPEID_UINT64:	sValue = pAngelScriptGeneric->GetArgQWord(i);						break;
			case asTYPEID_FLOAT:	sValue = pAngelScriptGeneric->GetArgFloat(i);						break;
			case asTYPEID_DOUBLE:	sValue = pAngelScriptGeneric->GetArgDouble(i);						break;

			/*
			// [TODO] Support the following?
			virtual void   *GetArgAddress(asUINT arg) = 0;
			virtual void   *GetArgObject(asUINT arg) = 0;
			enum asETypeIdFlags
			{
				asTYPEID_OBJHANDLE      = 0x40000000,
				asTYPEID_HANDLETOCONST  = 0x20000000,
				asTYPEID_MASK_OBJECT    = 0x1C000000,
				asTYPEID_APPOBJECT      = 0x04000000,
				asTYPEID_SCRIPTOBJECT   = 0x08000000,
			*/

			default:
				// Do nothing
				break;
		}

		// Add to functor parameters
		sParams += String("Param") + i + "=\"" + sValue + "\" ";
	}

	// Call the functor
	const String sReturn = psDynamicFunction->pDynFunc->CallWithReturn(sParams);

	// Process the functor return
	if (sReturn.GetLength()) {
		switch (pAngelScriptGeneric->GetReturnTypeId()) {
			case asTYPEID_BOOL:		pAngelScriptGeneric->SetReturnByte(sReturn.GetBool());		break;
			case asTYPEID_INT8:		pAngelScriptGeneric->SetReturnByte(sReturn.GetInt());		break;
			case asTYPEID_INT16:	pAngelScriptGeneric->SetReturnWord(sReturn.GetInt());		break;
			case asTYPEID_INT32:	pAngelScriptGeneric->SetReturnDWord(sReturn.GetInt());		break;
			case asTYPEID_INT64:	pAngelScriptGeneric->SetReturnQWord(sReturn.GetInt());		break;
			case asTYPEID_UINT8:	pAngelScriptGeneric->SetReturnByte(sReturn.GetUInt8());		break;
			case asTYPEID_UINT16:	pAngelScriptGeneric->SetReturnWord(sReturn.GetUInt16());	break;
			case asTYPEID_UINT32:	pAngelScriptGeneric->SetReturnDWord(sReturn.GetUInt32());	break;
			case asTYPEID_UINT64:	pAngelScriptGeneric->SetReturnQWord(sReturn.GetUInt64());	break;
			case asTYPEID_FLOAT:	pAngelScriptGeneric->SetReturnFloat(sReturn.GetFloat());	break;
			case asTYPEID_DOUBLE:	pAngelScriptGeneric->SetReturnDouble(sReturn.GetDouble());	break;

			/*
			// [TODO] Support the following?
			virtual int     SetReturnAddress(void *addr) = 0;
			virtual int     SetReturnObject(void *obj) = 0;
			enum asETypeIdFlags
			{
				asTYPEID_OBJHANDLE      = 0x40000000,
				asTYPEID_HANDLETOCONST  = 0x20000000,
				asTYPEID_MASK_OBJECT    = 0x1C000000,
				asTYPEID_APPOBJECT      = 0x04000000,
				asTYPEID_SCRIPTOBJECT   = 0x08000000,
			*/

			default:
				// Do nothing
				break;
		}
	}
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
	// Reset the source code
	m_sSourceCode = "";

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

	// Reset the current argument
	m_nCurrentArgument = 0;
}

/**
*  @brief
*    Gets a AngelScript function declaration
*/
String Script::GetAngelScriptFunctionDeclaration(const String &sFunctionName, const String &sFunctionSignature) const
{
	String sFunctionDeclaration = sFunctionSignature;
	const int nIndex = sFunctionDeclaration.IndexOf("(");
	if (nIndex > -1)
		sFunctionDeclaration.Insert(' ' + sFunctionName, nIndex);
	return sFunctionDeclaration;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptAngelScript
