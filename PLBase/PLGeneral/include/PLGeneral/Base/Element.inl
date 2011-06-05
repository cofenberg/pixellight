/*********************************************************\
 *  File: Element.inl                                    *
 *      Element template implementation
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
#include "PLGeneral/Base/ElementHandler.h"
#include "PLGeneral/Base/ElementManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
template <class AType>
Element<AType>::Element(const String &sName, ElementManager<AType> *pManager) :
	m_pManager(nullptr),
	m_bProtected(false)
{
	// Set unique element name
	if (pManager)
		pManager->SetElementName(static_cast<AType&>(*this), sName);
	else
		m_sName = sName;

	// Add this element to the manager
	if (pManager)
		pManager->Add(static_cast<AType&>(*this));
}

/**
*  @brief
*    Returns the element manager using this element
*/
template <class AType>
ElementManager<AType> *Element<AType>::GetManager() const
{
	return m_pManager;
}

/**
*  @brief
*    Returns the unique element name
*/
template <class AType>
String Element<AType>::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Returns whether the element is protected or not
*/
template <class AType>
bool Element<AType>::IsProtected() const
{
	return m_bProtected;
}

/**
*  @brief
*    Sets whether the element is protected or not
*/
template <class AType>
void Element<AType>::SetProtected(bool bProtected)
{
	m_bProtected = bProtected;
}

/**
*  @brief
*    Returns the ID of the element within the resouce manager
*/
template <class AType>
int Element<AType>::GetID() const
{
	// Is this element managed?
	if (m_pManager) {
		// Try to find this element within the manager
		for (uint32 i=0; i<m_pManager->GetNumOfElements(); i++) {
			if (m_pManager->GetByIndex(i) == this)
				return i;
		}
	}

	// HHHhhmmmmnn, element not found within the manager (?!!)
	return -1;
}


//[-------------------------------------------------------]
//[ Handler functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the number of element handlers
*/
template <class AType>
uint32 Element<AType>::GetNumOfHandlers() const
{
	return m_lstHandlers.GetNumOfElements();
}

/**
*  @brief
*    Returns a element handler
*/
template <class AType>
ElementHandler<AType> *Element<AType>::GetHandler(uint32 nIndex) const
{
	return m_lstHandlers[nIndex];
}


//[-------------------------------------------------------]
//[ Public virtual functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destroys the element
*/
template <class AType>
bool Element<AType>::Delete(bool bProtectedToo)
{
	// Protected?
	if (bProtectedToo || !m_bProtected) {
		DeleteElement();

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

/**
*  @brief
*    Sets the unique element name
*/
template <class AType>
bool Element<AType>::SetName(const String &sName)
{
	if (m_pManager)
		return m_pManager->SetElementName(static_cast<AType&>(*this), sName);
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
Element<AType> &Element<AType>::operator =(const Element<AType> &cSource)
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
Element<AType>::~Element()
{
	// Inform the handlers
	for (uint32 i=0; i<m_lstHandlers.GetNumOfElements(); i++)
		m_lstHandlers[i]->m_pElement = nullptr;

	// Clear the list
	m_lstHandlers.Clear();

	// Remove from element manager
	if (m_pManager)
		m_pManager->Remove(static_cast<AType&>(*this));
}


//[-------------------------------------------------------]
//[ Private virtual functions                             ]
//[-------------------------------------------------------]
/**
*  @brief
*    Deletes a element
*/
template <class AType>
void Element<AType>::DeleteElement()
{
	// Delete element
	delete this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
