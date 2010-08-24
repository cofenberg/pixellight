/*********************************************************\
 *  File: Resource.cpp                                   *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLRenderer/Renderer/ResourceHandler.h"
#include "PLRenderer/Renderer/Renderer.h"
#include "PLRenderer/Renderer/Resource.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
Resource::~Resource()
{
	// Remove resource from renderer
	m_pRenderer->RemoveResource(*this);
	ClearHandlers();
}

/**
*  @brief
*    Returns the owner renderer
*/
Renderer &Resource::GetRenderer() const
{
	return *m_pRenderer;
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
uint32 Resource::GetNumOfHandlers() const
{
	return m_lstHandlers.GetNumOfElements();
}

/**
*  @brief
*    Returns whether a resource handler is using this resource
*/
bool Resource::IsHandler(ResourceHandler &cHandler) const
{
	return m_lstHandlers.IsElement(&cHandler);
}

/**
*  @brief
*    Adds a resource handler
*/
bool Resource::AddHandler(ResourceHandler &cHandler)
{
	// Is this handler already registered?
	if (!m_lstHandlers.IsElement(&cHandler)) {
		if (m_lstHandlers.Add(&cHandler)) {
			if (cHandler.GetResource() != this)
				cHandler.SetResource(this);
		} else {
			// Error!
			return false;
		}
	}

	// Done
	return true;
}

/**
*  @brief
*    Removes a resource handler
*/
bool Resource::RemoveHandler(ResourceHandler &cHandler)
{
	if (m_lstHandlers.Remove(&cHandler)) {
		cHandler.SetResource();

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
void Resource::ClearHandlers()
{
	while (m_lstHandlers.GetNumOfElements())
		RemoveHandler(*m_lstHandlers[0]);
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Resource::Resource(Renderer &cRenderer, EType nType) :
	m_pRenderer(&cRenderer),
	m_nType(nType)
{
	// Add resource to renderer
	m_pRenderer->AddResource(*this);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Resource::Resource(const Resource &cSource) :
	m_pRenderer(&cSource.GetRenderer()),
	m_nType(cSource.GetType())
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Resource &Resource::operator =(const Resource &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Protected virtual functions                           ]
//[-------------------------------------------------------]
/**
*  @brief
*    Backups the resource device data
*/
void Resource::BackupDeviceData(uint8 **ppBackup)
{
	// Nothing to do by default
}

/**
*  @brief
*    Restores the resource device data
*/
void Resource::RestoreDeviceData(uint8 **ppBackup)
{
	// Nothing to do by default
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
