/*********************************************************\
 *  File: ConfigTest.cpp                                 *
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
#include <PLCore/Base/Class.h>
#include <PLCore/Config/Config.h>
#include "PLTestBase/Core/ConfigTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Configuration test class
*/
class TestConfigTest : public ConfigGroup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, TestConfigTest, "", PLCore::ConfigGroup, "Configuration test class")
		// Attributes
		pl_attribute(Detail,	float,	1.0f,	ReadWrite,	DirectValue,	"Detail",					"")
		pl_attribute(ShowFPS,	bool,	false,	ReadWrite,	DirectValue,	"Show Frames Per Second?",	"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		TestConfigTest() :
			Detail(this),
			ShowFPS(this)
		{
		}

		virtual ~TestConfigTest()
		{
		}


};

/**
*  @brief
*    Configuration user class
*/
class TestConfigUser : public ConfigGroup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, TestConfigUser, "", PLCore::ConfigGroup, "Configuration user class")
		// Attributes
		pl_attribute(Players,	int,	1,	ReadWrite,	DirectValue,	"Number of players",	"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		TestConfigUser() :
			Players(this)
		{
		}

		virtual ~TestConfigUser()
		{
		}


};


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(TestConfigTest)
pl_implement_class(TestConfigUser)


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *ConfigTest::GetName() const
{
	return "Config";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void ConfigTest::Test()
{
	// Create a configuration instance
	Config cConfig;

	// Show current settings
	Print("\nCurrent Config settings:\n");
	List<const PLCore::Class*> lstClasses;
	PLCore::ClassManager::GetInstance()->GetClasses(lstClasses, "PLCore::ConfigGroup", Recursive, NoBase, NoAbstract);
	for (uint32 i=0; i<lstClasses.GetNumOfElements(); i++) {
		const Class *pClass  = lstClasses[i];
		Object      *pObject = cConfig.GetClass(pClass->GetClassName());
		if (pObject)
			Print("%s = '%s'\n", pClass->GetClassName().GetASCII(), pObject->GetValues(WithDefault).GetASCII());
	}

	// Set TestConfigTest variables
	cConfig.SetVar("TestConfigTest", "Detail",  "0.5");
	cConfig.SetVar("TestConfigTest", "ShowFPS", "true");

	// Set TestConfigUser variables
	cConfig.SetVar("TestConfigUser", "Players", "2");

	// Get TestConfigTest variable value
	float fDetail  = cConfig.GetVar("TestConfigTest", "Detail").GetFloat();
	bool  bShowFPS = cConfig.GetVar("TestConfigTest", "ShowFPS").GetBool();

	// Get TestConfigUser variable value
	int nPlayers = cConfig.GetVarInt("TestConfigUser", "Players");

	// Show current settings
	for (uint32 i=0; i<lstClasses.GetNumOfElements(); i++) {
		const Class *pClass  = lstClasses[i];
		Object      *pObject = cConfig.GetClass(pClass->GetClassName());
		if (pObject)
			Print("%s = '%s'\n", pClass->GetClassName().GetASCII(), pObject->GetValues(WithDefault).GetASCII());
	}

	// Reset all to default
	cConfig.SetDefault();

	// Show current settings
	for (uint32 i=0; i<lstClasses.GetNumOfElements(); i++) {
		const Class *pClass  = lstClasses[i];
		Object      *pObject = cConfig.GetClass(pClass->GetClassName());
		if (pObject)
			Print("%s = '%s'\n", pClass->GetClassName().GetASCII(), pObject->GetValues(WithDefault).GetASCII());
	}
}
