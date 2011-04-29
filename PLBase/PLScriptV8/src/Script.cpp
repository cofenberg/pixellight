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
	// Clear the previous script
	Clear();

	// Backup the given source code
	m_sSourceCode = sSourceCode;

	// Create a stack-allocated handle scope
	v8::HandleScope cHandleScope;

	// Create a new context
	m_cV8Context = v8::Context::New();

	// Enter the created context for compiling and running the hello world script
	v8::Context::Scope cContextScope(m_cV8Context);

	// Create a string containing the JavaScript source code
	v8::Handle<v8::String> cSource = v8::String::New(sSourceCode);

	// Compile the source code
	v8::Handle<v8::Script> cScript = v8::Script::Compile(cSource);

	// Run the script to get the result
	v8::Handle<v8::Value> cResult = cScript->Run();

	// Done
	return true;
}

bool Script::BeginCall(const String &sFunctionName, const String &sFunctionSignature)
{
	// Create a stack-allocated handle scope
	v8::HandleScope cHandleScope;

	// Enter the created context for compiling and running the hello world script
	v8::Context::Scope cContextScope(m_cV8Context);

	// Get the V8 function
	v8::Handle<v8::Value> cV8Value = m_cV8Context->Global()->Get(v8::String::New(sFunctionName));
	if (cV8Value->IsFunction()) {
		// Backup the name of the current function (we may need it for error log output)
		m_sCurrentFunction = sFunctionName;

		// Clear the V8 arguments list
		m_lstArguments.Clear();
	} else {
		// Error!
		m_sCurrentFunction = "";
		LogOutput(Log::Error, "The function '" + sFunctionName + "' was not found");
	}

	// Done
	return true;
}

void Script::PushArgument(uint8 nValue)
{
	m_lstArguments.Add(nValue);
}

void Script::PushArgument(uint16 nValue)
{
	m_lstArguments.Add(nValue);
}

void Script::PushArgument(uint32 nValue)
{
	m_lstArguments.Add(nValue);
}

void Script::PushArgument(float fValue)
{
	m_lstArguments.Add(fValue);
}

void Script::PushArgument(double fValue)
{
	m_lstArguments.Add(fValue);
}

bool Script::EndCall()
{
	// Create a stack-allocated handle scope
	v8::HandleScope cHandleScope;

	// Enter the created context for compiling and running the hello world script
	v8::Context::Scope cContextScope(m_cV8Context);

	// Get the V8 function
	v8::Handle<v8::Function> cV8Function = v8::Handle<v8::Function>::Cast(m_cV8Context->Global()->Get(v8::String::New(m_sCurrentFunction)));
	if (cV8Function->IsFunction()) {
		if (m_lstArguments.GetNumOfElements()) {
			v8::Handle<v8::Value> *pcArguments = new v8::Handle<v8::Value>[m_lstArguments.GetNumOfElements()]();
			for (uint32 i=0; i<m_lstArguments.GetNumOfElements(); i++)
				pcArguments[i] = v8::Number::New(m_lstArguments[i]);
			m_cV8CurrentResult = cV8Function->Call(m_cV8Context->Global(), m_lstArguments.GetNumOfElements(), pcArguments);
			delete [] pcArguments;
		} else {
			m_cV8CurrentResult = cV8Function->Call(m_cV8Context->Global(), 0, nullptr);
		}
	}

	// Done
	return true;
}

void Script::GetReturn(uint8 &nValue)
{
	nValue = m_cV8CurrentResult->IsUint32() ? static_cast<uint8>(m_cV8CurrentResult->Uint32Value()) : 0;
}

void Script::GetReturn(uint16 &nValue)
{
	nValue = m_cV8CurrentResult->IsUint32() ? static_cast<uint16>(m_cV8CurrentResult->Uint32Value()) : 0;
}

void Script::GetReturn(uint32 &nValue)
{
	nValue = m_cV8CurrentResult->IsUint32() ? m_cV8CurrentResult->Uint32Value() : 0;
}

void Script::GetReturn(float &fValue)
{
	fValue = m_cV8CurrentResult->IsNumber() ? static_cast<float>(m_cV8CurrentResult->NumberValue()) : 0.0f;
}

void Script::GetReturn(double &fValue)
{
	fValue = m_cV8CurrentResult->IsNumber() ? m_cV8CurrentResult->NumberValue() : 0.0;
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
	// Dispose the persistent context
	if (!m_cV8Context.IsEmpty())
		m_cV8Context.Dispose();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptV8
