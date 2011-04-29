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
#include <v8.h>
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
	// [TODO] This is just a very first test code so we're linking against the V8 library
	// Create a stack-allocated handle scope
	v8::HandleScope cHandleScope;

	// Create a new context
	v8::Persistent<v8::Context> cContext = v8::Context::New();

	// Enter the created context for compiling and running the hello world script
	v8::Context::Scope cContextScope(cContext);

	// Create a string containing the JavaScript source code
	v8::Handle<v8::String> cSource = v8::String::New("'Hello' + ', World!'");

	// Compile the source code
	v8::Handle<v8::Script> cScript = v8::Script::Compile(cSource);

	// Run the script to get the result
	v8::Handle<v8::Value> cResult = cScript->Run();

	// Dispose the persistent context
	cContext.Dispose();

	// Convert the result to an ASCII string and print it
	v8::String::AsciiValue cAscii(cResult);
	char *pszTest = *cAscii;
	int ii = 0;
}

/**
*  @brief
*    Destructor
*/
Script::~Script()
{
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

	// [TODO] Implement me

	// Done
	return true;
}

bool Script::BeginCall(const String &sFunctionName, const String &sFunctionSignature)
{
	// [TODO] Implement me

	// Done
	return true;
}

void Script::PushArgument(uint8 nValue)
{
	// [TODO] Implement me
}

void Script::PushArgument(uint16 nValue)
{
	// [TODO] Implement me
}

void Script::PushArgument(uint32 nValue)
{
	// [TODO] Implement me
}

void Script::PushArgument(float fValue)
{
	// [TODO] Implement me
}

void Script::PushArgument(double fValue)
{
	// [TODO] Implement me
}

bool Script::EndCall()
{
	// [TODO] Implement me

	// Done
	return true;
}

void Script::GetReturn(uint8 &nValue)
{
	// [TODO] Implement me
	nValue = 0;
}

void Script::GetReturn(uint16 &nValue)
{
	// [TODO] Implement me
	nValue = 0;
}

void Script::GetReturn(uint32 &nValue)
{
	// [TODO] Implement me
	nValue = 0;
}

void Script::GetReturn(float &fValue)
{
	// [TODO] Implement me
	fValue = 0.0f;
}

void Script::GetReturn(double &fValue)
{
	// [TODO] Implement me
	fValue = 0.0;
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptV8
