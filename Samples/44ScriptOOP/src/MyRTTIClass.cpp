/*********************************************************\
 *  File: MyRTTIClass.cpp                                *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLCore/System/System.h>
#include <PLCore/System/Console.h>
#include "MyRTTIClass.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(MyRTTIClass)


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
	Name(this),
	Level(this),
	SlotOnMyEvent(this),
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

/**
*  @brief
*    Returns 42
*/
int MyRTTIClass::Return42() const
{
	return 42;
}

/**
*  @brief
*    Ignores the provided parameter
*/
void MyRTTIClass::IgnoreTheParameter(float fValue) const
{
	System::GetInstance()->GetConsole().Print(String("Ignoring \"") + fValue + "\" ... D'OH!\n");
}

/**
*  @brief
*    Says something wise
*/
void MyRTTIClass::SaySomethingWise() const
{
	System::GetInstance()->GetConsole().Print(String(Return42()) + " - wise enough?\n");
}

/**
*  @brief
*    Returns a pointer to this instance
*/
MyRTTIClass *MyRTTIClass::GetSelf()
{
	return this;
}

/**
*  @brief
*    Called when my event was emitted
*/
void MyRTTIClass::OnMyEvent(String sMessage)
{
	// Increase the level
	Level = Level + 1;

	// If there's a message, write it into the console
	if (sMessage.GetLength())
		System::GetInstance()->GetConsole().Print("\"MyRTTIClass::OnMyEvent\" message: \"" + sMessage + "\"\n");
}
