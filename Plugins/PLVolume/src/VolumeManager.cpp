/*********************************************************\
 *  File: VolumeManager.cpp                              *
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
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
