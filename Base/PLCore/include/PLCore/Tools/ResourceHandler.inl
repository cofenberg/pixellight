/*********************************************************\
 *  File: ResourceHandler.inl                            *
 *      Resource handler template implementation
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
ResourceHandler<AType>::ResourceHandler() :
	m_pResource(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
template <class AType>
ResourceHandler<AType>::~ResourceHandler()
{
	SetResource();
}

/**
*  @brief
*    Returns a pointer to the handlers resource
*/
template <class AType>
AType *ResourceHandler<AType>::GetResource() const
{
	return m_pResource;
}

/**
*  @brief
*    Sets the handlers resource
*/
template <class AType>
bool ResourceHandler<AType>::SetResource(AType *pResource)
{
	// Check whether this is the current set source
	if (m_pResource != pResource) {
		// If currently a resource is set...
		if (m_pResource) {
			// Remove this handler from the old resource
			if (!m_pResource->m_lstHandlers.Remove(this))
				return false; // Error!

			// If unused resources should be destroyed, check whether the previous resource
			// is now unused and not protected
			if (!m_pResource->IsProtected() && !m_pResource->m_lstHandlers.GetNumOfElements()) {
				ResourceManager<AType> *pManager = m_pResource->GetManager();
				if (pManager && pManager->GetUnloadUnused() && pManager->GetStandard() != m_pResource)
					m_pResource->Delete(); // Kill this resource
			}
		}

		// Set new resource
		m_pResource = pResource;

		// Add this handler to the new resource
		if (m_pResource && !m_pResource->m_lstHandlers.Add(this))
			return false; // Error!
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
