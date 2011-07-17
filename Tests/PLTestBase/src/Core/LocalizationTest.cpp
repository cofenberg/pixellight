/*********************************************************\
 *  File: LocalizationTest.cpp                           *
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
#include <PLCore/Tools/Localization.h>
#include <PLCore/Tools/LocalizationText.h>
#include <PLCore/Tools/LocalizationGroup.h>
#include "PLTestBase/Core/LocalizationTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *LocalizationTest::GetName() const
{
	return "Localization";
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Tests some get functions
*/
void LocalizationTest::TestGetFunctions(const String &sInfo)
{
	Localization *pLoc = Localization::GetInstance();
	bool bResult;

	// GetGroup(const String &sName)
	StartTask("GetGroup(const String &sName)");
	LocalizationGroup *pGroup = pLoc->GetGroup("LocalizationTest");
	EndTask(pLoc->GetNumOfGroups() == 1 && pGroup && pGroup->GetName() == "LocalizationTest");

	// Get(const String &sText, const String &sGroup)
	StartTask(sInfo + " Get(const String &sText, const String &sGroup)");
	bResult = true;
	if (pLoc->Get("Test") != "Test") bResult = false;
	if (pLoc->Get("Hello") != "Hello") bResult = false;
	if (pLoc->Get("Test", "LocalizationTest") != "Test") bResult = false;
	if (pLoc->Get("Hello", "LocalizationTest") != "Hallo") bResult = false;
	if (pLoc->Get("World", "LocalizationTest") != "Welt") bResult = false;
	EndTask(bResult);

	// PLT(Text)
	StartTask(sInfo + " PLT(Text)");
	bResult = true;
	if (PLT("Test") != "Test") bResult = false;
	if (PLT("Hello") != "Hello") bResult = false;
	if (PLT("Nr.%d, The name: %s") != "Nr.%d, The name: %s") bResult = false;
	String sFormatTest = String::Format(PLT("Nr.%d, The name: %s").GetUnicode(), 1, L"Bob");
	if (sFormatTest != "Nr.1, The name: Bob") bResult = false;
	EndTask(bResult);

	// PL_TEXT(Text, Group)
	StartTask(sInfo + " PL_TEXT(Text, Group)");
	bResult = true;
	if (PL_TEXT("Test", "HeHo") != "Test") bResult = false;
	if (PL_TEXT("Hello", "HeHo") != "Hello") bResult = false;
	if (PL_TEXT("Test", "LocalizationTest") != "Test") bResult = false;
	if (PL_TEXT("Hello", "LocalizationTest") != "Hallo") bResult = false;
	if (PL_TEXT("World", "LocalizationTest") != "Welt") bResult = false;
	EndTask(bResult);
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void LocalizationTest::Test()
{
	Localization *pLoc = Localization::GetInstance();

	// AddGroup(const String &sName)
	StartTask("AddGroup(const String &sName)");
	LocalizationGroup *pGroup = pLoc->AddGroup("LocalizationTest");
	LocalizationGroup *pGroupT = pLoc->AddGroup("LocalizationTest");
	EndTask(pLoc->GetNumOfGroups() == 1 && pGroup && pGroup->GetName() == "LocalizationTest" && !pGroupT);

	// Set from & to group language
	StartTask("Set from & to group language");
	pGroup->SetFromLanguage("English");
	pGroup->SetToLanguage("Deutsch");
	EndTask(pGroup->GetFromLanguage() == "English" && pGroup->GetToLanguage() == "Deutsch");

	// LocalizationGroup::AddText(const String &sName, const String &sTranslation)
	StartTask("LocalizationGroup::AddText(const String &sName, const String &sTranslation)");
	LocalizationText *pText1 = pGroup->AddText("Hello", "Hallo");
	LocalizationText *pText2 = pGroup->AddText("World", "Welt");
	LocalizationText *pText3 = pGroup->AddText("Nr.%d, The name: %s", "Nr.%d, Der Name: %s");
	LocalizationText *pTextT = pGroup->AddText("World", "Welt");
	EndTask(pGroup->GetNumOfTexts() == 3 && !pTextT &&
			pText1 && pText1->GetName() == "Hello" && pText1->GetTranslation() == "Hallo" &&
			pText2 && pText2->GetName() == "World" && pText2->GetTranslation() == "Welt" &&
			pText3 && pText3->GetName() == "Nr.%d, The name: %s" && pText3->GetTranslation() == "Nr.%d, Der Name: %s");

	// Test get functions
	TestGetFunctions("");

	// LocalizationGroup::Save(const String &sFilename)
	StartTask("LocalizationGroup::Save(const String &sFilename)");
	EndTask(pGroup->Save(pGroup->GetName() + ".loc"));

	// LocalizationGroup::Load(const String &sFilename)
	StartTask("LocalizationGroup::Load(const String &sFilename)");
	EndTask(pGroup->Load(pGroup->GetName() + ".loc"));

	// Test get functions, again :)
	TestGetFunctions("Loaded: ");
}
