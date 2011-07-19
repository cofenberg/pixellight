/*********************************************************\
 *  File: ResourceManagerTest.cpp                        *
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
#include <PLCore/Container/ResourceManager.h>
#include "PLTestBase/Core/ResourceManagerTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
class MiniClass : public Resource<MiniClass> {
	public:
		int i;
		MiniClass(const String &sName, ResourceManager<MiniClass> *pManager) :
			Resource<MiniClass>(sName, pManager)
		{
			i = 0;
		}
};

class MyManager : public ResourceManager<MiniClass> {
	private:
		virtual MiniClass *CreateResource(const String &sName)
		{
			return new MiniClass(sName, this);
		}
};


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *ResourceManagerTest::GetName() const
{
	return "ResourceManager";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void ResourceManagerTest::Test()
{
	MyManager lstManager;

	// Create resources
	StartTask("Create resources");
	MiniClass *pMini0 = lstManager.Create("Mini 0");
	MiniClass *pMini1 = lstManager.Create("Mini 1");
	MiniClass *pMini2 = lstManager.Create("Mini 2");
	EndTask(pMini0 && pMini1 && pMini2);

	// Check number resources
	StartTask("Check number of resources");
	EndTask(lstManager.GetNumOfElements() == 3);

	// Get resources
	StartTask("Get resources");
	EndTask(lstManager.GetByIndex(0) == pMini0 && lstManager.GetByName("Mini 0") == pMini0 &&
			lstManager.GetByIndex(1) == pMini1 && lstManager.GetByName("Mini 1") == pMini1 &&
			lstManager.GetByIndex(2) == pMini2 && lstManager.GetByName("Mini 2") == pMini2);

	// Clear
	StartTask("Clear");
	EndTask(lstManager.Clear() && !lstManager.GetNumOfElements());
}
