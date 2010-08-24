/*********************************************************\
 *  File: TestClass2.h                                   *
 *      Test class demonstrating the RTTI features
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


#ifndef __99TESTPLUGIN_TESTCLASS2_H__
#define __99TESTPLUGIN_TESTCLASS2_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "99TestPlugin/TestClass1.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace TestPlugin {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
class DummyClass {
	protected:
		int a, b, c, d;

		DummyClass()
		{
			a = b = 0;
			c = d = 1;
		}

		virtual ~DummyClass()
		{
			int h = a;
		}
};


class TestClass2 : public DummyClass, public TestClass1 {


	//[-------------------------------------------------------]
	//[ Public data types                                     ]
	//[-------------------------------------------------------]
	public:
		// Test flags #2
		enum TestFlags2 {
			Flag16  = 16,
			Flag32  = 32,
			Flag64  = 64,
			Flag128 = 128
		};

		// Define enum in RTTI
		pl_enum(TestFlags2)
			pl_enum_base(TestFlags)
			pl_enum_value(Flag16,  "")
			pl_enum_value(Flag32,  "")
			pl_enum_value(Flag64,  "")
			pl_enum_value(Flag128, "")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(TESTPLUGIN_RTTI_EXPORT, TestClass2, "TestPlugin", TestClass1, "Yet another test class demonstrating the RTTI features")
		pl_properties
			pl_property	 ("TestInfo",  "This is class TestClass2")
		pl_properties_end
		pl_attribute(Bool,	bool,	true,		ReadWrite, DirectValue,	"Boolean variable",	"")
		// Overwritten TestClass1 variables
		pl_attribute(Float,	float,	2.71828f,	ReadWrite, ModifyAttr,	"Euler number",		"")
		pl_attribute(Flags,	pl_flag_type(TestFlags2),	32, ReadWrite, ModifyAttr,	"Flags test (extended)", "")
		pl_constructor_0(Create, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		TESTPLUGIN_API TestClass2();
		TESTPLUGIN_API virtual ~TestClass2();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // TestPlugin


#endif // __99TESTPLUGIN_TESTCLASS2_H__
