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
#include "PLScriptNull/Script.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLScriptNull {


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
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Script functions               ]
//[-------------------------------------------------------]
bool Script::IsGlobalFunction(const String &sName)
{
	// The global script function does not exist
	return false;
}

bool Script::AddGlobalFunction(const String &sFunction, const DynFunc &cDynFunc, const String &sNamespace)
{
	// Nothing to do in here

	// Done
	return true;
}

bool Script::RemoveAllGlobalFunctions()
{
	// Nothing to do in here

	// Done
	return true;
}

String Script::GetSourceCode() const
{
	return m_sSourceCode;
}

bool Script::SetSourceCode(const String &sSourceCode)
{
	// Backup the given source code
	m_sSourceCode = sSourceCode;

	// Nothing to do in here

	// Done
	return true;
}

const Array<String> &Script::GetGlobalVariables()
{
	// Return a reference to the list of all global variables - we never fill the list
	return m_lstGlobalVariables;
}

bool Script::IsGlobalVariable(const String &sName)
{
	// Nothing to do in here
	return false;
}

ETypeID Script::GetGlobalVariableTypeID(const String &sName)
{
	// Nothing to do in here
	return TypeInvalid;
}

String Script::GetGlobalVariable(const String &sName)
{
	// Nothing to do in here
	return "";
}

void Script::SetGlobalVariable(const String &sName, const DynVar &cValue)
{
	// Nothing to do in here
}

bool Script::BeginCall(const String &sFunctionName, const String &sFunctionSignature)
{
	// Nothing to do in here

	// Done
	return true;
}

void Script::PushArgument(bool bValue)
{
	// Nothing to do in here
}

void Script::PushArgument(float fValue)
{
	// Nothing to do in here
}

void Script::PushArgument(double fValue)
{
	// Nothing to do in here
}

void Script::PushArgument(int8 nValue)
{
	// Nothing to do in here
}

void Script::PushArgument(int16 nValue)
{
	// Nothing to do in here
}

void Script::PushArgument(int32 nValue)
{
	// Nothing to do in here
}

void Script::PushArgument(int64 nValue)
{
	// Nothing to do in here
}

void Script::PushArgument(uint8 nValue)
{
	// Nothing to do in here
}

void Script::PushArgument(uint16 nValue)
{
	// Nothing to do in here
}

void Script::PushArgument(uint32 nValue)
{
	// Nothing to do in here
}

void Script::PushArgument(uint64 nValue)
{
	// Nothing to do in here
}

void Script::PushArgument(const String &sString)
{
	// Nothing to do in here
}

void Script::PushArgument(Object *pObject)
{
	// Nothing to do in here
}

void Script::PushArgument(Object &cObject)
{
	// Nothing to do in here
}

bool Script::EndCall()
{
	// Nothing to do in here

	// Done
	return true;
}

bool Script::GetReturn(bool nValue)
{
	// Nothing to do in here
	return false;
}

float Script::GetReturn(float nValue)
{
	// Nothing to do in here
	return 0.0f;
}

double Script::GetReturn(double nValue)
{
	// Nothing to do in here
	return 0.0;
}

int8 Script::GetReturn(int8 nValue)
{
	// Nothing to do in here
	return 0;
}

int16 Script::GetReturn(int16 nValue)
{
	// Nothing to do in here
	return 0;
}

int32 Script::GetReturn(int32 nValue)
{
	// Nothing to do in here
	return 0;
}

int64 Script::GetReturn(int64 nValue)
{
	// Nothing to do in here
	return 0;
}

uint8 Script::GetReturn(uint8 nValue)
{
	// Nothing to do in here
	return 0;
}

uint16 Script::GetReturn(uint16 nValue)
{
	// Nothing to do in here
	return 0;
}

uint32 Script::GetReturn(uint32 nValue)
{
	// Nothing to do in here
	return 0;
}

uint64 Script::GetReturn(uint64 nValue)
{
	// Nothing to do in here
	return 0;
}

String Script::GetReturn(String sValue)
{
	// Nothing to do in here
	return "";
}

Object *Script::GetReturn(Object *nValue)
{
	// Nothing to do in here
	return nullptr;
}

Object &Script::GetReturn(Object &nValue)
{
	// ... please note that in here, we can't return a null pointer...
	Object *pObject = GetReturn(&nValue);
	return pObject ? *pObject : nValue;
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
} // PLScriptNull
