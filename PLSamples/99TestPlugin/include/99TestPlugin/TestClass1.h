/*********************************************************\
 *  File: TestClass1.h                                   *
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
