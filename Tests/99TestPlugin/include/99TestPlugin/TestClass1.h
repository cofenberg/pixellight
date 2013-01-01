/*********************************************************\
 *  File: TestClass1.h                                   *
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


#ifndef __99TESTPLUGIN_TESTCLASS1_H__
#define __99TESTPLUGIN_TESTCLASS1_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include "99TestPlugin/99TestPlugin.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace TestPlugin {


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
// Test enumeration
enum TestEnum {
	Alpha,
	Beta,
	Gamma,
	Delta
};

// Test flags
enum TestFlags {
	Flag1 = 1,
	Flag2 = 2,
	Flag4 = 4,
	Flag8 = 8
};

// Define enum in RTTI
pl_enum(TestEnum)
	pl_enum_value(Alpha, "First letter in the greek alphabet")
	pl_enum_value(Beta,  "Second letter in the greek alphabet")
	pl_enum_value(Gamma, "Third letter in the greek alphabet")
	pl_enum_value(Delta, "Fourth letter in the greek alphabet")
pl_enum_end

// Define enum in RTTI
pl_enum(TestFlags)
	pl_enum_value(Flag1, "Bit at position #0")
	pl_enum_value(Flag2, "Bit at position #1")
	pl_enum_value(Flag4, "Bit at position #2")
	pl_enum_value(Flag8, "Bit at position #3")
pl_enum_end


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Test class demonstrating the RTTI features
*/
class TestClass1 : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(TESTPLUGIN_RTTI_EXPORT, TestClass1, "TestPlugin", PLCore::Object, "Test class demonstrating the RTTI features")
		// Properties
		pl_properties
			pl_property("TestInfo",	"This is class TestClass1")
		pl_properties_end
		// Attributes
		pl_attribute(Int,	int,					10,			ReadWrite,	DirectValue,	"Simple integer",	"")
		pl_attribute(Float,	float,					3.1415f,	ReadWrite,	GetSet,			"PI",				"")
		pl_attribute(Enum,	pl_enum_type(TestEnum),	Beta,		ReadWrite,	DirectValue,	"Enumeration test",	"")
		pl_attribute(Flags,	pl_flag_type(TestFlags),	0,		ReadWrite,	DirectValue,	"Flags test",		"")
		// Constructors
		pl_constructor_0(Create,	"Default constructor",	"")
		// Methods
		pl_method_0(PrintFloat,	pl_ret_type(void),	"Print value of attribute Float",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		TESTPLUGIN_API TestClass1();
		TESTPLUGIN_API virtual ~TestClass1();
		TESTPLUGIN_API void PrintFloat();
		TESTPLUGIN_API float GetFloat() const;
		TESTPLUGIN_API void SetFloat(float fFloat);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float m_fFloat;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // TestPlugin


#endif // __99TESTPLUGIN_TESTCLASS1_H__
