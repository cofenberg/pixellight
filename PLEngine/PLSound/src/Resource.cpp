/*********************************************************\
 *  File: Resource.cpp                                   *
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
#include "PLSound/SoundManager.h"
#include "PLSound/ResourceHandler.h"
#include "PLSound/Resource.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLSound {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
Resource::~Resource()
{
	// Remove resource from sound manager
	m_pSoundManager->RemoveResource(*this);

	// Inform all handlers using this resource
	ClearResourceHandlers();
}

/**
*  @brief
*    Returns the owner sound manager
*/
SoundManager &Resource::GetSoundManager() const
{
	return *m_pSoundManager;
}

/**
*  @brief
*    Returns the resource type
*/
Resource::EType Resource::GetType() const
{
	return m_nType;
}

/**
*  @brief
*    Returns the number of resource handlers
*/
uint32 Resource::GetNumOfResourceHandlers() const
{
	return m_lstSoundHandlers.GetNumOfElements();
}

/**
*  @brief
*    Returns whether a resource handler is using this resource
*/
bool Resource::IsResourceHandler(ResourceHandler &cHandler) const
{
	return m_lstSoundHandlers.IsElement(&cHandler);
}

/**
*  @brief
*    Adds a resource handler
*/
bool Resource::AddResourceHandler(ResourceHandler &cHandler)
{
	// Was this handler already added?
	if (!m_lstSoundHandlers.IsElement(&cHandler)) {
		// Add the handler
		if (m_lstSoundHandlers.Add(&cHandler))
			return false; // Error!
		else {
			if (cHandler.GetResource() != this)
				cHandler.SetResource(this);
		}
	}

	// Done
	return true;
}

/**
*  @brief
*    Removes a resource handler
*/
bool Resource::RemoveResourceHandler(ResourceHandler &cHandler)
{
	if (m_lstSoundHandlers.Remove(&cHandler)) {
		cHandler.SetResource(nullptr);

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

/**
*  @brief
*    Clears the list of handlers
*/
void Resource::ClearResourceHandlers()
{
	while (m_lstSoundHandlers.GetNumOfElements())
		RemoveResourceHandler(*m_lstSoundHandlers[0]);
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Resource::Resource(SoundManager &cSoundManager, EType nType) :
	m_pSoundManager(&cSoundManager),
	m_nType(nType)
{
	// Add resource to sound manager
	m_pSoundManager->AddResource(*this);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Resource::Resource(const Resource &cSource) :
	m_pSoundManager(&cSource.GetSoundManager()),
	m_nType(cSource.GetType())
{
	// No implementation because the copy constructor is never used
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSound
