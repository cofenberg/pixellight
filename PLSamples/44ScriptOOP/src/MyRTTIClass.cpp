/*********************************************************\
 *  File: MyRTTIClass.cpp                                *
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
#include <PLGeneral/System/System.h>
#include <PLGeneral/System/Console.h>
#include "MyRTTIClass.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(MyRTTIClass)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
int MyRTTIClass::Return42()
{
	return 42;
}

void MyRTTIClass::IgnoreTheParameter(float fValue)
{
	System::GetInstance()->GetConsole().Print(String("Ignoring \"") + fValue + "\" ... D'OH!\n");
}

void MyRTTIClass::SaySomethingWise()
{
	System::GetInstance()->GetConsole().Print(String(Return42()) + " - wise enough?\n");
}


//[-------------------------------------------------------]
//[ Public RTTI slot methods                              ]
//[-------------------------------------------------------]
void MyRTTIClass::OnMyEvent()
{
	// Increase the level
	Level = Level + 1;
}


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String MyRTTIClass::GetName()
{
	// Increase the level
	Level = Level + 1;

	// Return the name
	return m_sName;
}

void MyRTTIClass::SetName(const String &sName)
{
	// Increase the level
	Level = Level + 1;

	// Set the name
	m_sName = sName;

	// Emit the signal
	MySignal("C++");
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MyRTTIClass::MyRTTIClass() :
	MethodReturn42(this),
	MethodIgnoreTheParameter(this),
	MethodSaySomethingWise(this),
	MySignal(this),
	SlotOnMyEvent(this),
	Name(this),
	Level(this),
	m_sName("Bob")
{
}

/**
*  @brief
*    Destructor
*/
MyRTTIClass::~MyRTTIClass()
{
}
