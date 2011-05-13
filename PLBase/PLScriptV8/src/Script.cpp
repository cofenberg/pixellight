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
#include <PLGeneral/Log/Log.h>
#include "PLScriptV8/Script.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLScriptV8 {


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
Script::Script()
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
}


//[-------------------------------------------------------]
//[ Public virtual PLScript::Script functions             ]
//[-------------------------------------------------------]
bool Script::AddDynamicFunction(const String &sFunction, const DynFunc &cDynFunc, const String &sNamespace)
{
	// Is there a V8 context?
	if (m_cV8Context.IsEmpty()) {
		// Add the dynamic function
		DynamicFunction *psDynamicFunction = new DynamicFunction;
		psDynamicFunction->sFunction  = sFunction;
		psDynamicFunction->pDynFunc   = cDynFunc.Clone();
		psDynamicFunction->sNamespace = sNamespace;
		m_lstDynamicFunctions.Add(psDynamicFunction);

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

bool Script::RemoveAllDynamicFunctions()
{
	// Is there a V8 context?
	if (m_cV8Context.IsEmpty()) {
		// Destroy the dynamic functions
		for (uint32 i=0; i<m_lstDynamicFunctions.GetNumOfElements(); i++) {
			delete m_lstDynamicFunctions[i]->pDynFunc;
			delete m_lstDynamicFunctions[i];
		}
		m_lstDynamicFunctions.Clear();

		// Done
		return true;
	} else {
		// Error!
		return false;
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
		// Create a stack-allocated handle scope
		v8::HandleScope cHandleScope;

		// Are there any dynamic functions?
		if (m_lstDynamicFunctions.GetNumOfElements()) {
			// Global V8 namespace
			V8Namespace cV8Namespace;

			// Create a template for the global object and set the built-in global functions
			cV8Namespace.cV8ObjectTemplate = v8::ObjectTemplate::New();

			// Add the dynamic functions
			for (uint32 i=0; i<m_lstDynamicFunctions.GetNumOfElements(); i++) {
				// Get the dynamic function
				DynamicFunction *psDynamicFunction = m_lstDynamicFunctions[i];

				// Create V8 function
				v8::Local<v8::ObjectTemplate> cV8Function = v8::ObjectTemplate::New();
				cV8Function->SetCallAsFunctionHandler(V8FunctionCallback, v8::External::New(psDynamicFunction));

				// Add V8 function
				AddV8Function(cV8Namespace, psDynamicFunction->sFunction, cV8Function, psDynamicFunction->sNamespace);
			}

			// Create a new context
			m_cV8Context = v8::Context::New(nullptr, cV8Namespace.cV8ObjectTemplate);
		} else {
			// Create a new context
			m_cV8Context = v8::Context::New();
		}

		// Enter our V8 context
		v8::Context::Scope cContextScope(m_cV8Context);

		// Create a string containing the JavaScript source code
		v8::Local<v8::String> cSource = v8::String::New(sSourceCode);
		if (cSource.IsEmpty()) {
			// Error!
			LogOutput(Log::Error, "Failed to generate string source");
		} else {
			// Compile the source code
			v8::TryCatch cTryCatch;
			v8::Local<v8::Script> cScript = v8::Script::Compile(cSource);
			if (cScript.IsEmpty()) {
				// Error!
				LogOutputTryCatch(Log::Error, "Failed to compile the script", cTryCatch);
			} else {
				// Run the script to get the result
				if (cScript->Run().IsEmpty()) {
					// Error!
					LogOutputTryCatch(Log::Error, "Failed to run the script", cTryCatch);
				}
			}
		}
	} else {
		// No script at all - done
	}

	// Done
	return true;
}

bool Script::IsGlobalVariable(const String &sName)
{
	return (GetGlobalVariableType(sName) != TypeInvalid);
}

ETypeID Script::GetGlobalVariableType(const String &sName)
{
	// Is there a V8 context?
	if (!m_cV8Context.IsEmpty()) {
		// Create a stack-allocated handle scope
		v8::HandleScope cHandleScope;

		// Enter our V8 context
		v8::Context::Scope cContextScope(m_cV8Context);

		// Get the V8 object
		v8::Local<v8::Object> cV8Object = v8::Local<v8::Object>::Cast(m_cV8Context->Global()->Get(v8::String::New(sName)));
		if (!cV8Object.IsEmpty()) {
			if (cV8Object->IsBoolean())
				return TypeBool;
			else if (cV8Object->IsInt32())
				return TypeInt32;
			else if (cV8Object->IsUint32())
				return TypeUInt32;
			else if (cV8Object->IsNumber())
				return TypeDouble;
			else if (cV8Object->IsString())
				return TypeString;
		}
	}

	// Error!
	return TypeInvalid;
}

String Script::GetGlobalVariable(const String &sName)
{
	// Is there a V8 context?
	if (!m_cV8Context.IsEmpty()) {
		// Create a stack-allocated handle scope
		v8::HandleScope cHandleScope;

		// Enter our V8 context
		v8::Context::Scope cContextScope(m_cV8Context);

		// Get the V8 object
		v8::Local<v8::Object> cV8Object = v8::Local<v8::Object>::Cast(m_cV8Context->Global()->Get(v8::String::New(sName)));
		if (!cV8Object.IsEmpty())
			return *v8::String::AsciiValue(cV8Object->ToString());
	}

	// Error!
	return "";
}

void Script::SetGlobalVariable(const String &sName, const String &sValue)
{
	// Get the type of the global variable (because we don't want to change it's type)
	const ETypeID nType = GetGlobalVariableType(sName);
	if (nType != TypeInvalid) {
		// Create a stack-allocated handle scope
		v8::HandleScope cHandleScope;

		// Enter our V8 context
		v8::Context::Scope cContextScope(m_cV8Context);

		// Get the value to set
		switch (nType) {
			case TypeBool:
				m_cV8Context->Global()->Set(v8::String::New(sName), v8::Boolean::New(sValue.GetBool()));
				break;

			case TypeInt32:
				m_cV8Context->Global()->Set(v8::String::New(sName), v8::Int32::New(sValue.GetInt()));
				break;

			case TypeUInt32:
				m_cV8Context->Global()->Set(v8::String::New(sName), v8::Uint32::New(sValue.GetUInt32()));
				break;

			case TypeDouble:
				m_cV8Context->Global()->Set(v8::String::New(sName), v8::Number::New(sValue.GetDouble()));
				break;

			case TypeString:
				m_cV8Context->Global()->Set(v8::String::New(sName), v8::String::New(sValue));
				break;
		}
	}
}

bool Script::BeginCall(const String &sFunctionName, const String &sFunctionSignature)
{
	// Is there a V8 context?
	if (!m_cV8Context.IsEmpty()) {
		// Create a stack-allocated handle scope
		v8::HandleScope cHandleScope;

		// Enter our V8 context
		v8::Context::Scope cContextScope(m_cV8Context);

		// Get the V8 function
		v8::Local<v8::Value> cV8Value = m_cV8Context->Global()->Get(v8::String::New(sFunctionName));
		if (cV8Value->IsFunction()) {
			// Backup the name of the current function (we may need it for error log output)
			m_sCurrentFunction = sFunctionName;

			// Clear the V8 arguments list
			m_lstV8Arguments.Clear();
		} else {
			// Error!
			m_sCurrentFunction = "";
			LogOutput(Log::Error, "The function '" + sFunctionName + "' was not found");
		}

		// Done
		return true;
	}

	// Error!
	return false;
}

void Script::PushArgument(int nValue)
{
	// Is there currently a function to feed with arguments?
	if (m_sCurrentFunction.GetLength()) {
		// Create a stack-allocated handle scope
		v8::HandleScope cHandleScope;

		// Enter our V8 context
		v8::Context::Scope cContextScope(m_cV8Context);

		// Add argument
		m_lstV8Arguments.Add(v8::Persistent<v8::Value>::New(v8::Integer::New(nValue)));
	}
}

void Script::PushArgument(uint8 nValue)
{
	// Is there currently a function to feed with arguments?
	if (m_sCurrentFunction.GetLength()) {
		// Create a stack-allocated handle scope
		v8::HandleScope cHandleScope;

		// Enter our V8 context
		v8::Context::Scope cContextScope(m_cV8Context);

		// Add argument
		m_lstV8Arguments.Add(v8::Persistent<v8::Value>::New(v8::Integer::New(nValue)));
	}
}

void Script::PushArgument(uint16 nValue)
{
	// Is there currently a function to feed with arguments?
	if (m_sCurrentFunction.GetLength()) {
		// Create a stack-allocated handle scope
		v8::HandleScope cHandleScope;

		// Enter our V8 context
		v8::Context::Scope cContextScope(m_cV8Context);

		// Add argument
		m_lstV8Arguments.Add(v8::Persistent<v8::Value>::New(v8::Integer::New(nValue)));
	}
}

void Script::PushArgument(uint32 nValue)
{
	// Is there currently a function to feed with arguments?
	if (m_sCurrentFunction.GetLength()) {
		// Create a stack-allocated handle scope
		v8::HandleScope cHandleScope;

		// Enter our V8 context
		v8::Context::Scope cContextScope(m_cV8Context);

		// Add argument
		m_lstV8Arguments.Add(v8::Persistent<v8::Value>::New(v8::Uint32::New(nValue)));
	}
}

void Script::PushArgument(float fValue)
{
	// Is there currently a function to feed with arguments?
	if (m_sCurrentFunction.GetLength()) {
		// Create a stack-allocated handle scope
		v8::HandleScope cHandleScope;

		// Enter our V8 context
		v8::Context::Scope cContextScope(m_cV8Context);

		// Add argument
		m_lstV8Arguments.Add(v8::Persistent<v8::Value>::New(v8::Number::New(fValue)));
	}
}

void Script::PushArgument(double fValue)
{
	// Is there currently a function to feed with arguments?
	if (m_sCurrentFunction.GetLength()) {
		// Create a stack-allocated handle scope
		v8::HandleScope cHandleScope;

		// Enter our V8 context
		v8::Context::Scope cContextScope(m_cV8Context);

		// Add argument
		m_lstV8Arguments.Add(v8::Persistent<v8::Value>::New(v8::Number::New(fValue)));
	}
}

void Script::PushArgument(const String &sString)
{
	// Is there currently a function to feed with arguments?
	if (m_sCurrentFunction.GetLength()) {
		// Create a stack-allocated handle scope
		v8::HandleScope cHandleScope;

		// Enter our V8 context
		v8::Context::Scope cContextScope(m_cV8Context);

		// Add argument
		m_lstV8Arguments.Add(v8::Persistent<v8::Value>::New(v8::String::New(sString)));
	}
}

bool Script::EndCall()
{
	if (m_sCurrentFunction.GetLength()) {
		// Create a stack-allocated handle scope
		v8::HandleScope cHandleScope;

		// Enter our V8 context
		v8::Context::Scope cContextScope(m_cV8Context);

		// Clear the current result
		m_cV8CurrentResult.Clear();

		// Get the V8 function
		v8::Local<v8::Function> cV8Function = v8::Local<v8::Function>::Cast(m_cV8Context->Global()->Get(v8::String::New(m_sCurrentFunction)));
		if (cV8Function->IsFunction()) {
			v8::TryCatch cTryCatch;

			// Call the V8 function
			m_cV8CurrentResult = v8::Persistent<v8::Value>::New(cV8Function->Call(m_cV8Context->Global(), m_lstV8Arguments.GetNumOfElements(), m_lstV8Arguments.GetData()));

			// Error?
			if (m_cV8CurrentResult.IsEmpty())
				LogOutputTryCatch(Log::Error, "Failed to call the function '" + m_sCurrentFunction + '\'', cTryCatch);
		}

		// Done
		return !m_cV8CurrentResult.IsEmpty();
	}

	// Error!
	return false;
}

void Script::GetReturn(int &nValue)
{
	nValue = (!m_cV8CurrentResult.IsEmpty() && m_cV8CurrentResult->IsUint32()) ? static_cast<uint8>(m_cV8CurrentResult->Uint32Value()) : 0;
}

void Script::GetReturn(uint8 &nValue)
{
	nValue = (!m_cV8CurrentResult.IsEmpty() && m_cV8CurrentResult->IsUint32()) ? static_cast<uint8>(m_cV8CurrentResult->Uint32Value()) : 0;
}

void Script::GetReturn(uint16 &nValue)
{
	nValue = (!m_cV8CurrentResult.IsEmpty() && m_cV8CurrentResult->IsUint32()) ? static_cast<uint16>(m_cV8CurrentResult->Uint32Value()) : 0;
}

void Script::GetReturn(uint32 &nValue)
{
	nValue = (!m_cV8CurrentResult.IsEmpty() && m_cV8CurrentResult->IsUint32()) ? m_cV8CurrentResult->Uint32Value() : 0;
}

void Script::GetReturn(float &fValue)
{
	fValue = (!m_cV8CurrentResult.IsEmpty() && m_cV8CurrentResult->IsNumber()) ? static_cast<float>(m_cV8CurrentResult->NumberValue()) : 0.0f;
}

void Script::GetReturn(double &fValue)
{
	fValue = (!m_cV8CurrentResult.IsEmpty() && m_cV8CurrentResult->IsNumber()) ? m_cV8CurrentResult->NumberValue() : 0.0;
}

void Script::GetReturn(String &sValue)
{
	sValue = (!m_cV8CurrentResult.IsEmpty() && m_cV8CurrentResult->IsString()) ? *v8::String::AsciiValue(m_cV8CurrentResult->ToString()) : "";
}


//[-------------------------------------------------------]
//[ Private static V8 callback functions                  ]
//[-------------------------------------------------------]
/*
*  @brief
*    V8 function callback
*/
v8::Handle<v8::Value> Script::V8FunctionCallback(const v8::Arguments &vV8Arguments)
{
	// Get the dynamic function
	DynamicFunction *psDynamicFunction = reinterpret_cast<DynamicFunction*>(v8::External::Unwrap(vV8Arguments.Data()));
	if (psDynamicFunction) {
		// V8 arguments to parameter string
		String sParams;
		for (int i=0; i<vV8Arguments.Length(); i++)
			sParams += String("Param") + i + "=\"" + *v8::String::AsciiValue(vV8Arguments[i]->ToString()) + "\" ";

		// Call the functor
		const String sReturn = psDynamicFunction->pDynFunc->CallWithReturn(sParams);

		// Process the functor return
		switch (psDynamicFunction->pDynFunc->GetReturnTypeID()) {
			case TypeBool:		return v8::Boolean::New(sReturn.GetBool());
			case TypeDouble:	return v8::Number ::New(sReturn.GetDouble());
			case TypeFloat:		return v8::Number ::New(sReturn.GetFloat());
			case TypeInt:		return v8::Integer::New(sReturn.GetInt());
			case TypeInt16:		return v8::Integer::New(sReturn.GetInt());
			case TypeInt32:		return v8::Int32  ::New(sReturn.GetInt());
			case TypeInt64:		return v8::Integer::New(sReturn.GetInt());	// [TODO] TypeInt64 is currently handled just as int
			case TypeInt8:		return v8::Integer::New(sReturn.GetInt());
			case TypeString:	return v8::String ::New(sReturn);
			case TypeUInt16:	return v8::Integer::New(sReturn.GetUInt16());
			case TypeUInt32:	return v8::Uint32 ::New(sReturn.GetUInt32());
			case TypeUInt64:	return v8::Integer::New(static_cast<uint32>(sReturn.GetUInt64()));	// [TODO] TypeUInt64 is currently handled just as int
			case TypeUInt8:		return v8::Integer::New(sReturn.GetUInt8());
			default:			return v8::Local<v8::Value>();// TypeVoid, TypeNull, TypeObjectPtr, -1
		}
	}

	// Error!
	return v8::Local<v8::Value>();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Script::Script(const Script &cSource)
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

	// Dispose the persistent context
	if (!m_cV8Context.IsEmpty())
		m_cV8Context.Dispose();

	// Reset the name of the current function
	m_sCurrentFunction = "";

	// Clear the V8 arguments list
	m_lstV8Arguments.Clear();
}

/**
*  @brief
*    Write a string into the log
*/
bool Script::LogOutputTryCatch(uint8 nLogLevel, const String &sText, const v8::TryCatch &cTryCatch)
{
	// Get the error description
	const String sErrorDescription = cTryCatch.HasCaught() ? (String(" (Line ") + cTryCatch.Message()->GetLineNumber() + " \"" + String::FromUTF8(*v8::String::Utf8Value(cTryCatch.Exception()))) + "\")": "";

	// Call the base implementation
	return Script::LogOutput(nLogLevel, sText + sErrorDescription);
}

/**
*  @brief
*    Adds a V8 function
*/
void Script::AddV8Function(V8Namespace &cV8Namespace, const String &sFunction, v8::Local<v8::ObjectTemplate> cV8Function, const String &sNamespace) const
{
	// Is the given namespace empty?
	if (sNamespace.GetLength()) {
		// Nope, the target namespace is not yet reached...

		// Find the next "." within the given nested V8 namespace name
		int nPartEnd = sNamespace.IndexOf(".");
		if (nPartEnd < 0)
			nPartEnd = sNamespace.GetLength();

		// Get the current V8 namespace name
		const String sSubsNamespaceName = sNamespace.GetSubstring(0, nPartEnd);

		// Is there already a V8 namespace object with the given name?
		V8Namespace &cSubsV8Namespace = cV8Namespace.mapNamespaces.Get(sSubsNamespaceName);
		if (&cSubsV8Namespace == &HashMap<String, V8Namespace >::Null) {
			// New V8 namespace
			V8Namespace cNewV8Namespace;

			// Create the V8 namespace object
			cNewV8Namespace.cV8ObjectTemplate = v8::ObjectTemplate::New();

			// Add the V8 namespace object to the current V8 object
			cV8Namespace.cV8ObjectTemplate->Set(v8::String::New(sSubsNamespaceName), cNewV8Namespace.cV8ObjectTemplate, v8::ReadOnly);

			// Go down the rabbit hole...
			AddV8Function(cNewV8Namespace, sFunction, cV8Function, sNamespace.GetSubstring(nPartEnd + 1));

			// Add V8 namespace
			cV8Namespace.mapNamespaces.Add(sSubsNamespaceName, cNewV8Namespace);
		} else {
			// Go down the rabbit hole...
			AddV8Function(cSubsV8Namespace, sFunction, cV8Function, sNamespace.GetSubstring(nPartEnd + 1));
		}
	} else {
		// Jap, now add the given V8 function object to the current V8 object
		cV8Namespace.cV8ObjectTemplate->Set(v8::String::New(sFunction), cV8Function, v8::ReadOnly);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptV8
