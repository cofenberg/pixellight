/*********************************************************\
 *  File: RttiObject.cpp                                 *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "RttiObject.h"

// [DEBUG]
#include <PLCore/System/System.h>
#include <PLCore/System/Console.h>


//[-------------------------------------------------------]
//[ Disable warnings                                      ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
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
