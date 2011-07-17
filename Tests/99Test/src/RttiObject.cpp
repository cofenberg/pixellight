/*********************************************************\
 *  File: RttiObject.cpp                                 *
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
#include "RttiObject.h"

// [DEBUG]
#include <PLGeneral/System/System.h>
#include <PLGeneral/System/Console.h>


//[-------------------------------------------------------]
//[ Disable warnings                                      ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;


//[-------------------------------------------------------]
//[ Rtti interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(RttiObject)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RttiObject::RttiObject() :
	BoolValue(this),
	IntValue (this),
	IntValue2(this),
	m_nIntValue(200),
	Number(this),
	State(this),
	Float(this),
	SlotOnSomeEvent0(this)
{
	// [DEBUG]
//	System::GetInstance()->GetConsole().Print("CALLED DEFAULT CONSTRUCTOR");
}

/**
*  @brief
*    Constructor
*/
RttiObject::RttiObject(int nValue) :
	BoolValue(this),
	IntValue (this),
	IntValue2(this),
	m_nIntValue(200),
	Number(this),
	State(this),
	Float(this),
	SlotOnSomeEvent0(this)
{
	// [DEBUG]
//	System::GetInstance()->GetConsole().Print("CALLED CONSTRUCTOR (int)");
}

/**
*  @brief
*    Constructor
*/
RttiObject::RttiObject(int nValue, float fValue) :
	BoolValue(this),
	IntValue (this),
	IntValue2(this),
	m_nIntValue(200),
	Number(this),
	State(this),
	Float(this),
	SlotOnSomeEvent0(this)
{
	// [DEBUG]
//	System::GetInstance()->GetConsole().Print(String("-- CONSTRUCTOR(int, float): ") + nValue + ", " + fValue + '\n');
}

/**
*  @brief
*    Destructor
*/
RttiObject::~RttiObject()
{
	// [DEBUG]
//	System::GetInstance()->GetConsole().Print("-- DESTRUCTOR\n");
}

int RttiObject::GetIntValue()
{
	// [DEBUG]
//	System::GetInstance()->GetConsole().Print("-- GetIntValue(): " + String() + m_nIntValue + " --\n");

	// Return value
	return m_nIntValue;
}

void RttiObject::SetIntValue(int nValue)
{
	// [DEBUG]
//	System::GetInstance()->GetConsole().Print("-- SetIntValue(): " + String() + nValue + " --\n");

	// Set value
	m_nIntValue = nValue;
}

/**
*  @brief
*    Test function
*/
void RttiObject::Test(int nParam0, float fParam1)
{
	// [DEBUG]
	System::GetInstance()->GetConsole().Print(String("-- Test(") + nParam0 + ", " + fParam1 + ")\n");
}

/**
*  @brief
*    Test event handler
*/
void RttiObject::OnSomeEvent0(int nParam0)
{
	// [DEBUG]
	System::GetInstance()->GetConsole().Print(String("-- OnEventHandler0(") + nParam0 + ")\n");
}

bool RttiObject::MyMethod(String &sParam)
{
	System::GetInstance()->GetConsole().Print("MyMethod: '" + sParam + "'\n");
    return true;
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
