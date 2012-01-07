/*********************************************************\
 *  File: SceneCreatorLoadableType.cpp                   *
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
#include "PLEngine/SceneCreator/SceneCreatorLoadableType.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
namespace PLEngine {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SceneCreatorLoadableType)


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Configures a scene by using a given loadable type in order to determine the scene creator to use
*/
SNCamera *SceneCreatorLoadableType::ConfigureSceneByLoadableType(SceneContainer &cSceneContainer, const String &sType, const String &sFilename, const String &sParameters)
{
	// Get a list of RTTI classes derived from the loadable type scene creator
	List<const Class*> lstClasses;
	ClassManager::GetInstance()->GetClasses(lstClasses, "PLEngine::SceneCreatorLoadableType", Recursive, NoBase, NoAbstract);

	// Iterate over the received class list
	ConstIterator<const Class*> cIterator = lstClasses.GetConstIterator();
	while (cIterator.HasNext()) {
		// Get the current RTTI class
		const Class *pClass = cIterator.Next();

		// Check loadable type
		if (pClass->GetProperties().Get("Type") == sType) {
			// We've found a match - Configure a scene and return the preferred camera scene node
			return ConfigureScene(cSceneContainer, pClass->GetClassName(), "Filename=\"" + sFilename + "\" " + sParameters);
		}
	}

	// Error!
	return nullptr;
}

/**
*  @brief
*    Returns a list of loadable types were it's possible to use a scene creator in order to configure a scene
*/
void SceneCreatorLoadableType::GetLoadableTypes(Array<String> &lstLoadableTypes)
{
	// Get a list of RTTI classes derived from the loadable type scene creator
	List<const Class*> lstClasses;
	ClassManager::GetInstance()->GetClasses(lstClasses, "PLEngine::SceneCreatorLoadableType", Recursive, NoBase, NoAbstract);

	// Iterate over the received class list
	HashMap<String, bool> mapTypes;
	ConstIterator<const Class*> cIterator = lstClasses.GetConstIterator();
	while (cIterator.HasNext()) {
		// Get the current RTTI class
		const Class *pClass = cIterator.Next();

		// Get loadable type
		const String &sType = pClass->GetProperties().Get("Type");

		// Add the loadable type to the given list... but only if the type string is not empty or was already added
		if (sType.GetLength() && !mapTypes.Get(sType)) {
			lstLoadableTypes.Add(sType);
			mapTypes.Add(sType, true);
		}
	}
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SceneCreatorLoadableType::SceneCreatorLoadableType() :
	Filename(this)
{
}

/**
*  @brief
*    Destructor
*/
SceneCreatorLoadableType::~SceneCreatorLoadableType()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
