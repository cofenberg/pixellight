/*********************************************************\
 *  File: Profiling.cpp                                  *
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
#include "PLGeneral/Tools/Profiling.h"


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
ProfileGroupElement::ProfileGroupElement(const String &sName, ElementManager<ProfileGroupElement> *pManager) :
	Element<ProfileGroupElement>(sName, pManager)
{
}

/**
*  @brief
*    Destructor
*/
ProfileGroupElement::~ProfileGroupElement()
{
}

/**
*  @brief
*    Returns the text of the element
*/
String ProfileGroupElement::GetText() const
{
	return m_sText;
}

/**
*  @brief
*    Sets the element text
*/
bool ProfileGroupElement::SetText(const String &sText)
{
	// Set text
	m_sText = sText;

	// Done
	return true;
}

/**
*  @brief
*    Copy operator
*/
ProfileGroupElement &ProfileGroupElement::operator =(const ProfileGroupElement &cSource)
{
	// Copy text
	m_sText = cSource.m_sText;

	// Return this implementation
	return *this;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
ProfileGroupElement::ProfileGroupElement(const ProfileGroupElement &cSource)
{
	// No implementation because the copy constructor is never used
}




//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ProfileGroup::ProfileGroup(const String &sName, ElementManager<ProfileGroup> *pManager) :
	Element<ProfileGroup>(sName, pManager)
{
}

/**
*  @brief
*    Destructor
*/
ProfileGroup::~ProfileGroup()
{
}

/**
*  @brief
*    Returns the text of the element group
*/
String ProfileGroup::GetText() const
{
	return m_sText;
}

/**
*  @brief
*    Sets the element group text
*/
bool ProfileGroup::SetText(const String &sText)
{
	// Set text
	m_sText = sText;

	// Done
	return true;
}

/**
*  @brief
*    Copy operator
*/
ProfileGroup &ProfileGroup::operator =(const ProfileGroup &cSource)
{
	// Copy text
	m_sText = cSource.m_sText;

	// Call base implementation

	// Return this implementation
	return *this;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
ProfileGroup::ProfileGroup(const ProfileGroup &cSource)
{
	// No implementation because the copy constructor is never used
}


//[-------------------------------------------------------]
//[ Private virtual ElementManager functions              ]
//[-------------------------------------------------------]
ProfileGroupElement *ProfileGroup::CreateElement(const String &sName)
{
	return new ProfileGroupElement(sName, this);
}




//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns whether the profiling system is active or not
*/
bool Profiling::IsActive() const
{
	return m_bActive;
}

/**
*  @brief
*    Sets whether the profiling system is active or not
*/
void Profiling::SetActive(bool bActive)
{
	m_bActive = bActive;
}

/**
*  @brief
*    Returns the name of the current selected profile group
*/
String Profiling::GetSelectedGroup() const
{
	return m_sGroupName;
}

/**
*  @brief
*    Selects a profile group
*/
bool Profiling::SelectGroup(const String &sName)
{
	// Check given group name and check if there's a group with this name
	if (sName.GetLength() && Get(sName)) {
		// Select group
		m_sGroupName = sName;

		// Done
		return true;
	} else return false; // Error!
}

/**
*  @brief
*    Selects the next profile group
*/
String Profiling::SelectNextGroup()
{
	// Get current group
	const ProfileGroup *pGroup = Get(m_sGroupName);
	if (pGroup) {
		// Select the next group
		uint32 i = pGroup->GetID()+1;
		m_sGroupName = i < GetNumOfElements() ? Get(i)->GetName() : "";
	} else {
		// Select first group
		pGroup = Get((uint32)0);
		if (pGroup) m_sGroupName = pGroup->GetName();
	}

	// Return the group name
	return m_sGroupName;
}

/**
*  @brief
*    Selects the previous profile group
*/
String Profiling::SelectPreviousGroup()
{
	// Get current group
	const ProfileGroup *pGroup = Get(m_sGroupName);
	if (pGroup) {
		// Select the previous group
		uint32 i = pGroup->GetID();
		m_sGroupName = i ? Get(i-1)->GetName() : "";
	} else {
		// Select first group
		pGroup = Get(GetNumOfElements()-1);
		if (pGroup) m_sGroupName = pGroup->GetName();
	}

	// Return the group name
	return m_sGroupName;
}

/**
*  @brief
*    Sets the element text
*/
bool Profiling::Set(const String &sGroup, const String &sElement, const String &sText)
{
	// Is the profiling system active and are the parameters ok?
	if (m_bActive && sGroup.GetLength() && sElement.GetLength()) {
		// Check if there's a group with this name
		ProfileGroup *pGroup = Get(sGroup);
		if (!pGroup) pGroup = Create(sGroup);
		if (pGroup) {
			// Check if there's an element with this name
			ProfileGroupElement *pGroupElement = pGroup->Get(sElement);
			if (!pGroupElement) pGroupElement = pGroup->Create(sElement);
			if (pGroupElement) {
				// Set element text
				pGroupElement->SetText(sText);

				// Done
				return true;
			}
		}
	}

	// Error!
	return false;
}

/**
*  @brief
*    Returns the element text
*/
String Profiling::GetText(const String &sGroup, const String &sElement) const
{
	// Get group
	const ProfileGroup *pGroup = Get(sGroup);
	if (pGroup) {
		// Get element
		const ProfileGroupElement *pGroupElement = pGroup->Get(sElement);
		if (pGroupElement) return pGroupElement->GetText(); // Return text
	}

	// Error!
	return "";
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Profiling::Profiling() :
	m_bActive(false)
{
}

/**
*  @brief
*    Copy constructor
*/
Profiling::Profiling(const Profiling &cSource) :
	m_bActive(false)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Destructor
*/
Profiling::~Profiling()
{
}

/**
*  @brief
*    Copy operator
*/
Profiling &Profiling::operator =(const Profiling &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Private virtual ElementManager functions              ]
//[-------------------------------------------------------]
ProfileGroup *Profiling::CreateElement(const String &sName)
{
	return new ProfileGroup(sName, this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
