/*********************************************************\
 *  File: Resource.inl                                   *
 *      Resource template implementation
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
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Tools/ResourceHandler.h"
#include "PLCore/Tools/ResourceManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
template <class AType>
Resource<AType>::Resource(const PLGeneral::String &sName, ResourceManager<AType> *pManager) :
	m_pManager(nullptr),
	m_bProtected(false)
{
	// Set unique resource name
	if (pManager)
		pManager->SetResourceName(static_cast<AType&>(*this), sName);
	else
		m_sName = sName;

	// Add this resource to the manager
	if (pManager)
		pManager->Add(static_cast<AType&>(*this));
}

/**
*  @brief
*    Returns the resource manager using this resource
*/
template <class AType>
ResourceManager<AType> *Resource<AType>::GetManager() const
{
	return m_pManager;
}

/**
*  @brief
*    Returns the unique resource name
*/
template <class AType>
PLGeneral::String Resource<AType>::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Returns whether the resource is protected or not
*/
template <class AType>
bool Resource<AType>::IsProtected() const
{
	return m_bProtected;
}

/**
*  @brief
*    Sets whether the resource is protected or not
*/
template <class AType>
void Resource<AType>::SetProtected(bool bProtected)
{
	m_bProtected = bProtected;
}

/**
*  @brief
*    Returns the ID of the resource within the resouce manager
*/
template <class AType>
int Resource<AType>::GetID() const
{
	// Is this resource managed?
	if (m_pManager) {
		// Try to find this resource within the manager
		for (PLGeneral::uint32 i=0; i<m_pManager->GetNumOfElements(); i++) {
			if (m_pManager->GetByIndex(i) == this)
				return i;
		}
	}

	// HHHhhmmmmnn, resource not found within the manager (?!!)
	return -1;
}


//[-------------------------------------------------------]
//[ Handler functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the number of resource handlers
*/
template <class AType>
PLGeneral::uint32 Resource<AType>::GetNumOfHandlers() const
{
	return m_lstHandlers.GetNumOfElements();
}

/**
*  @brief
*    Returns a resource handler
*/
template <class AType>
ResourceHandler<AType> *Resource<AType>::GetHandler(PLGeneral::uint32 nIndex) const
{
	return m_lstHandlers[nIndex];
}


//[-------------------------------------------------------]
//[ Public virtual functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destroys the resource
*/
template <class AType>
bool Resource<AType>::Delete(bool bProtectedToo)
{
	// Protected?
	if (bProtectedToo || !m_bProtected) {
		DeleteResource();

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

/**
*  @brief
*    Sets the unique resource name
*/
template <class AType>
bool Resource<AType>::SetName(const PLGeneral::String &sName)
{
	if (m_pManager)
		return m_pManager->SetResourceName(static_cast<AType&>(*this), sName);
	else {
		m_sName = sName;

		// Done
		return true;
	}
}

/**
*  @brief
*    Copy operator
*/
template <class AType>
Resource<AType> &Resource<AType>::operator =(const Resource<AType> &cSource)
{
	// Copy
	m_bProtected = cSource.m_bProtected;

	// Return pointer
	return *this;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
template <class AType>
Resource<AType>::~Resource()
{
	// Inform the handlers
	for (PLGeneral::uint32 i=0; i<m_lstHandlers.GetNumOfElements(); i++)
		m_lstHandlers[i]->m_pResource = nullptr;

	// Clear the list
	m_lstHandlers.Clear();

	// Remove from resource manager
	if (m_pManager)
		m_pManager->Remove(static_cast<AType&>(*this));
}


//[-------------------------------------------------------]
//[ Private virtual functions                             ]
//[-------------------------------------------------------]
/**
*  @brief
*    Deletes a resource
*/
template <class AType>
void Resource<AType>::DeleteResource()
{
	// Delete resource
	delete this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
