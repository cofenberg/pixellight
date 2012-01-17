/*********************************************************\
 *  File: ScriptBinding_PL_ClassManager.cpp              *
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
#include <PLCore/Base/ClassManager.h>
#include "PLScriptBindings/ScriptBinding_PL_ClassManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLScriptBindings {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ScriptBinding_PL_ClassManager)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool ScriptBinding_PL_ClassManager::ScanPlugins(String sPath, bool bRecursive, bool bDelayedPluginLoading)
{
	return ClassManager::GetInstance()->ScanPlugins(sPath, bRecursive ? Recursive : NonRecursive, bDelayedPluginLoading);
}

Object *ScriptBinding_PL_ClassManager::Create(String sClass, String sParameters)
{
	// Get the requested RTTI class
	const Class *pClass =  ClassManager::GetInstance()->GetClass(sClass);
	if (pClass) {
		// Create an instance of the requested RTTI class
		Object *pObject = pClass->Create();
		if (pObject) {
			// By default, a created RTTI class instance has an initial reference count of 1
			// -> This RTTI class instance was possibly created by a script, so, set an initial reference
			//    count of 0 so that the instance is destroyed automatically as soon as it's no longer referenced
			pObject->SoftRelease();

			// Set optional parameters
			if (pObject && sParameters.GetLength())
				pObject->SetValues(sParameters);

			// Return the created RTTI class instance
			return pObject;
		}
	}

	// Error!
	return nullptr;
}

Object *ScriptBinding_PL_ClassManager::CreateByConstructor(String sClass, String sConstructor, String sConstructorParameters, String sParameters)
{
	// Get the requested RTTI class
	const Class *pClass =  ClassManager::GetInstance()->GetClass(sClass);
	if (pClass) {
		// Create an instance of the requested RTTI class
		Object *pObject = pClass->Create(sConstructor, sConstructorParameters);
		if (pObject) {
			// By default, a created RTTI class instance has an initial reference count of 1
			// -> This RTTI class instance was possibly created by a script, so, set an initial reference
			//    count of 0 so that the instance is destroyed automatically as soon as it's no longer referenced
			pObject->SoftRelease();

			// Set optional parameters
			if (pObject && sParameters.GetLength())
				pObject->SetValues(sParameters);

			// Return the created RTTI class instance
			return pObject;
		}
	}

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ScriptBinding_PL_ClassManager::ScriptBinding_PL_ClassManager()
{
}

/**
*  @brief
*    Destructor
*/
ScriptBinding_PL_ClassManager::~ScriptBinding_PL_ClassManager()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptBindings
