/*********************************************************\
 *  File: ElementHandler.inl                             *
 *      Element handler template implementation
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
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Container/ElementManager.h"


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
ElementHandler<AType>::ElementHandler() :
	m_pElement(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
template <class AType>
ElementHandler<AType>::~ElementHandler()
{
	SetElement();
}

/**
*  @brief
*    Returns a pointer to the handlers element
*/
template <class AType>
AType *ElementHandler<AType>::GetElement() const
{
	return m_pElement;
}

/**
*  @brief
*    Sets the handlers element
*/
template <class AType>
bool ElementHandler<AType>::SetElement(AType *pElement)
{
	// Check whether this is the current set source
	if (m_pElement != pElement) {
		// If currently a element is set...
		if (m_pElement) {
			// Remove this handler from the old element
			if (!m_pElement->m_lstHandlers.Remove(this))
				return false; // Error!

			// If unused elements should be destroyed, check whether the previous element
			// is now unused and not protected
			if (!m_pElement->IsProtected() && !m_pElement->m_lstHandlers.GetNumOfElements()) {
				ElementManager<AType> *pManager = m_pElement->GetManager();
				if (pManager && pManager->GetUnloadUnused() && pManager->GetStandard() != m_pElement)
					m_pElement->Delete(); // Kill this element
			}
		}

		// Set new element
		m_pElement = pElement;

		// Add this handler to the new element
		if (m_pElement && !m_pElement->m_lstHandlers.Add(this))
			return false; // Error!
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
