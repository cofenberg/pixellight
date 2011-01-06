/*********************************************************\
 *  File: ResourceHandler.cpp                            *
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
#include "PLSound/ResourceHandler.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLSound {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ResourceHandler::ResourceHandler() :
	m_pResource(nullptr)
{
}

/**
*  @brief
*    Copy constructor
*/
ResourceHandler::ResourceHandler(const ResourceHandler &cSource) :
	m_pResource(nullptr)
{
	if (cSource.m_pResource) {
		m_pResource = cSource.m_pResource;
		m_pResource->AddResourceHandler(*this);
	}
}

/**
*  @brief
*    Destructor
*/
ResourceHandler::~ResourceHandler()
{
	// Inform resource
	if (m_pResource)
		m_pResource->RemoveResourceHandler(*this);
}

/**
*  @brief
*    Copy operator
*/
ResourceHandler &ResourceHandler::operator =(const ResourceHandler &cSource)
{
	// Inform the old resource
	if (m_pResource)
		m_pResource->RemoveResourceHandler(*this);

	// Set new one
	m_pResource = cSource.m_pResource;
	if (m_pResource)
		m_pResource->AddResourceHandler(*this);

	// Return this
	return *this;
}

/**
*  @brief
*    Returns the resource handlers resource
*/
Resource *ResourceHandler::GetResource() const
{
	return m_pResource;
}

/**
*  @brief
*    Sets the resource handlers resource
*/
void ResourceHandler::SetResource(Resource *pResource)
{
	// Inform the old resource
	if (m_pResource)
		m_pResource->RemoveResourceHandler(*this);

	// Set new one
	m_pResource = pResource;
	if (pResource)
		pResource->AddResourceHandler(*this);
}


//[-------------------------------------------------------]
//[ Public virtual functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Is called when the resource was lost
*/
void ResourceHandler::OnLost()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSound
