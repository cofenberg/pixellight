/*********************************************************\
 *  File: MathClassTest.cpp                              *
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
#include <PLCore/Base/Class.h>
#include <PLCore/Base/Object.h>
#include <PLCore/Base/ClassManager.h>
#include <PLMath/Vector2.h>
#include <PLMath/Vector4.h>
#include <PLGraphics/Color/Color3.h>
#include <PLGraphics/Color/Color4.h>
#include "PLTestBase/Math/MathClassTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Test class demonstrating the math features
*/
class MathTestClass1 : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, MathTestClass1, "", PLCore::Object, "Test class demonstrating the math features")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(Vector2,	PLMath::Vector2,	PLMath::Vector2(0.0f, 1.0f),				ReadWrite,	DirectValue,	"2D vector",	"")
		pl_attribute(Vector3,	PLMath::Vector3,	PLMath::Vector3(0.0f, 1.0f, 2.0f),			ReadWrite,	DirectValue,	"3D vector",	"")
		pl_attribute(Vector4,	PLMath::Vector4,	PLMath::Vector4(0.0f, 1.0f, 2.0f, 3.0f),	ReadWrite,	DirectValue,	"4D vector",	"")
		pl_attribute(Color3,	PLGraphics::Color3,	PLGraphics::Color3(0.0f, 1.0f, 2.0f),		ReadWrite,	DirectValue,	"RGB color",	"")
		pl_attribute(Color4,	PLGraphics::Color4,	PLGraphics::Color4(0.0f, 1.0f, 2.0f, 3.0f),	ReadWrite,	DirectValue,	"RGBA color",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		MathTestClass1() :
			Vector2(this),
			Vector3(this),
			Vector4(this),
			Color3(this),
			Color4(this)
		{
		}

		virtual ~MathTestClass1()
		{
		}


};


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(MathTestClass1)


//[-------------------------------------------------------]
//[ MathClassTest implementation                          ]
//[-------------------------------------------------------]
const char *MathClassTest::GetName() const
{
	return "MathClass";
}

void MathClassTest::Test()
{
	// Test class with math stuff
	const PLCore::Class *pClass = PLCore::ClassManager::GetInstance()->GetClass("MathTestClass1");
	PLCore::Object *pTest = nullptr;
	if (pClass) pTest = pClass->Create();
	if (pTest) {
		Print("cTest = '%s'\n",											pTest->GetValues(PLCore::WithDefault).GetASCII());
		Print("cTest.SetAttribute(Vector2D='-1.0 -2.0')\n");			pTest->SetAttribute("Vector2D", "-1.0 -2.0");
		Print("cTest = '%s'\n", pTest->GetValues(PLCore::WithDefault).GetASCII());
		Print("cTest.SetAttribute(Vector3D='-1.0 -2.0 -3.0')\n");	 	pTest->SetAttribute("Vector3D", "-1.0 -2.0 -3.0");
		Print("cTest = '%s'\n", pTest->GetValues(PLCore::WithDefault).GetASCII());
		Print("cTest.SetAttribute(Vector4D='-1.0 -2.0 -3.0 -4.0')\n");	pTest->SetAttribute("Vector4D", "-1.0 -2.0, -3.0 -4.0");
		Print("cTest = '%s'\n", pTest->GetValues(PLCore::WithDefault).GetASCII());
		Print("cTest.SetAttribute(Color3='1.0 2.0 3.0')\n");	 		pTest->SetAttribute("Color3", "1.0 2.0 3.0");
		Print("cTest = '%s'\n", pTest->GetValues(PLCore::WithDefault).GetASCII());
		Print("cTest.SetAttribute(Color4='1.0 2.0 3.0 4.0')\n");		pTest->SetAttribute("Color4", "1.0 2.0, 3.0 4.0");
		Print("cTest = '%s'\n", pTest->GetValues(PLCore::WithDefault).GetASCII());
	}
}
