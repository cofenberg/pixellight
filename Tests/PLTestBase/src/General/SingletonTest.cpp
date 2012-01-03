/*********************************************************\
 *  File: SingletonTest.cpp                              *
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
#include <stdio.h>
#include <PLCore/Core/Singleton.h>
#include "PLTestBase/General/SingletonTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Test singleton class
*/
class Singleton1 : public Singleton<Singleton1> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Singleton<Singleton1>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		Singleton1();
		virtual ~Singleton1();
		void Test();


};


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
Singleton1::Singleton1()
{
	printf("Singleton1 created\n");
}

Singleton1::~Singleton1()
{
	printf("Singleton1 deleted\n");
}

void Singleton1::Test()
{
	printf("Hello from Singleton1\n");
}


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *SingletonTest::GetName() const
{
	return "Singleton";
}

//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void SingletonTest::Test()
{
	StartTask("Get instance");
	EndTask(Singleton1::GetInstance() != nullptr);
}
