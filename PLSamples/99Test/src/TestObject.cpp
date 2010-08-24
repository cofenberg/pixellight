/*********************************************************\
 *  File: TestObject.cpp                                 *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include "TestObject.h"


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
// Class singleton
TestObject::_Class *TestObject::_Class::Instance = NULL;
bool				TestObject::_Class::Shutdown = false;

// Creation and destruction guard
TestObject::_Guard cGuard;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TestObject::TestObject() :
	BoolValue(this),
	IntValue(this),
	IntValue2(this),
	MethodTest(this),
	Event0(this),
	EventHandler0(this)
{
}

/**
*  @brief
*    Destructor
*/
TestObject::~TestObject()
{
}

/**
*  @brief
*    Test function
*/
void TestObject::Test()
{
}

// Public virtual PLCore::Object function
Class *TestObject::GetClass() const
{
	return _Class::GetInstance();
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
