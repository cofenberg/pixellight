/*********************************************************\
 *  File: TestClass3.h                                   *
 *      Test class demonstrating the RTTI features
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
		pl_properties
			pl_property("TestInfo", "This is class TestClass3")
		pl_properties_end
		pl_constructor_0(Create, "Default constructor", "")
		pl_attribute(DebugAttr, int, 0, ReadWrite, DirectValue, "", "")
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
