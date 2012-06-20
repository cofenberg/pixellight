/*********************************************************\
 *  File: VolumeManager.cpp                              *
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
#include <PLCore/Log/Log.h>
#include "PLVolume/VolumeManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLVolume {


//[-------------------------------------------------------]
//[ Template instance                                     ]
//[-------------------------------------------------------]
template class Singleton<VolumeManager>;


//[-------------------------------------------------------]
//[ Public static PLCore::Singleton functions             ]
//[-------------------------------------------------------]
VolumeManager *VolumeManager::GetInstance()
{
	// The compiler should be able to optimize this extra call (inlining)
	return Singleton<VolumeManager>::GetInstance();
}

bool VolumeManager::HasInstance()
{
	// The compiler should be able to optimize this extra call (inlining)
	return Singleton<VolumeManager>::HasInstance();
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
VolumeManager::VolumeManager()
{
	PL_LOG(Debug, "Create volume manager")
	SetManagerName("Volume manager");

	// Unload unused resources, please
	// [TODO] Think about this... when playing within a Lua script and therefore quickly reloading the script, it should
	// not be required to reload the volume as well *time*
//	SetUnloadUnused(true);
	SetUnloadUnused(false);
}

/**
*  @brief
*    Destructor
*/
VolumeManager::~VolumeManager()
{
	PL_LOG(Debug, "Destroy volume manager")
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ResourceManager functions     ]
//[-------------------------------------------------------]
Volume *VolumeManager::CreateResource(const String &sName)
{
	return new Volume(sName, this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
