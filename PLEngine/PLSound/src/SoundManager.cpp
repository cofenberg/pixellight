/*********************************************************\
 *  File: SoundManager.cpp                               *
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
#include "PLSound/Resource.h"
#include "PLSound/SoundManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLSound {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SoundManager)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
SoundManager::~SoundManager()
{
	// Destroy all resources - the resources unregister automatically from the list, so, this while loop will terminate!
	while (m_lstResources.GetNumOfElements())
		delete m_lstResources[0];
}

/**
*  @brief
*    Returns the sound statistics
*/
const SoundManager::Statistics &SoundManager::GetStatistics() const
{
	return m_sStatistics;
}


//[-------------------------------------------------------]
//[ Resources                                             ]
//[-------------------------------------------------------]
uint32 SoundManager::GetNumOfResources() const
{
	return m_lstResources.GetNumOfElements();
}

Resource *SoundManager::GetResource(uint32 nIndex) const
{
	return m_lstResources[nIndex];
}

bool SoundManager::AddResource(Resource &cResource)
{
	// Add the resource
	if (m_lstResources.Add(&cResource)) {
		// Update statistics
		switch (cResource.GetType()) {
			case Resource::TypeBuffer:
				m_sStatistics.nNumOfBuffers++;
				break;

			case Resource::TypeSource:
				m_sStatistics.nNumOfSources++;
				break;
		}

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

bool SoundManager::RemoveResource(Resource &cResource)
{
	// Remove the resource
	if (m_lstResources.Remove(&cResource)) {
		// Update statistics
		switch (cResource.GetType()) {
			case Resource::TypeBuffer:
				m_sStatistics.nNumOfBuffers--;
				break;

			case Resource::TypeSource:
				m_sStatistics.nNumOfSources--;
				break;
		}

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SoundManager::SoundManager()
{
	// Init data
	MemoryManager::Set(&m_sStatistics, 0, sizeof(Statistics));
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
SoundManager::SoundManager(const SoundManager &cSource)
{
	// Init data
	MemoryManager::Set(&m_sStatistics, 0, sizeof(Statistics));

	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
SoundManager &SoundManager::operator =(const SoundManager &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ResourceManager function      ]
//[-------------------------------------------------------]
Buffer *SoundManager::CreateResource(const String &sName)
{
	// This function MUST be overwritten within the concrete sound backend
	return nullptr; // Error!
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSound
