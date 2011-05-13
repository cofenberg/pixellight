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
//[ Public virtual PLScript::Script functions             ]
//[-------------------------------------------------------]
bool Script::AddDynamicFunction(const String &sFunction, const DynFunc &cDynFunc, const String &sNamespace)
{
	// Nothing to do in here

	// Done
	return true;
}

bool Script::RemoveAllDynamicFunctions()
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

bool Script::IsGlobalVariable(const String &sName)
{
	// Nothing to do in here
	return false;
}

ETypeID Script::GetGlobalVariableType(const String &sName)
{
	// Nothing to do in here
	return TypeInvalid;
}

String Script::GetGlobalVariable(const String &sName)
{
	// Nothing to do in here
	return "";
}

void Script::SetGlobalVariable(const String &sName, const String &sValue)
{
	// Nothing to do in here
}

bool Script::BeginCall(const String &sFunctionName, const String &sFunctionSignature)
{
	// Nothing to do in here

	// Done
	return true;
}

void Script::PushArgument(int nValue)
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

void Script::PushArgument(float fValue)
{
	// Nothing to do in here
}

void Script::PushArgument(double fValue)
{
	// Nothing to do in here
}

void Script::PushArgument(const String &sString)
{
	// Nothing to do in here
}

bool Script::EndCall()
{
	// Nothing to do in here

	// Done
	return true;
}

void Script::GetReturn(int &nValue)
{
	// Nothing to do in here
	nValue = 0;
}

void Script::GetReturn(uint8 &nValue)
{
	// Nothing to do in here
	nValue = 0;
}

void Script::GetReturn(uint16 &nValue)
{
	// Nothing to do in here
	nValue = 0;
}

void Script::GetReturn(uint32 &nValue)
{
	// Nothing to do in here
	nValue = 0;
}

void Script::GetReturn(float &fValue)
{
	// Nothing to do in here
	fValue = 0.0f;
}

void Script::GetReturn(double &fValue)
{
	// Nothing to do in here
	fValue = 0.0;
}

void Script::GetReturn(String &sValue)
{
	// Nothing to do in here
	sValue = "";
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
