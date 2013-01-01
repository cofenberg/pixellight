/*********************************************************\
 *  File: TestClass3.h                                   *
 *      Test class demonstrating the RTTI features
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


#ifndef __99TESTPLUGIN_TESTCLASS3_H__
#define __99TESTPLUGIN_TESTCLASS3_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "99TestPlugin/TestClass2.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace TestPlugin {
namespace AnotherNamespace {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
class TestClass3 : public TestClass2 {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(TESTPLUGIN_RTTI_EXPORT, TestClass3, "TestPlugin::AnotherNamespace", TestPlugin::TestClass2, "Namespace in namespace")
		// Properties
		pl_properties
			pl_property("TestInfo",	"This is class TestClass3")
		pl_properties_end
		// Attributes
		pl_attribute(DebugAttr,	int,	0,	ReadWrite,	DirectValue,	"",	"")
		// Constructors
		pl_constructor_0(Create,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		TESTPLUGIN_API TestClass3();
		TESTPLUGIN_API virtual ~TestClass3();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // AnotherNamespace
} // TestPlugin


#endif // __99TESTPLUGIN_TESTCLASS3_H__
