/*********************************************************\
 *  File: AbstractToggleButton.cpp                       *
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
#include "PLGui/Gui/Data/ButtonGroup.h"
#include "PLGui/Widgets/Base/AbstractToggleButton.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLGui {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(AbstractToggleButton)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
AbstractToggleButton::AbstractToggleButton(Widget *pParent) : AbstractButton(pParent),
	PartiallyAllowed(this),
	State(this),
	SlotOnGroupActivate(this),
	m_pGroup(nullptr),
	m_bPartiallyAllowed(false),
	m_nState(NotChecked)
{
}

/**
*  @brief
*    Destructor
*/
AbstractToggleButton::~AbstractToggleButton()
{
}

/**
*  @brief
*    Get group that the radio button belongs to
*/
ButtonGroup *AbstractToggleButton::GetGroup() const
{
	// Return group
	return m_pGroup;
}

/**
*  @brief
*    Set group that the radio button belongs to
*/
void AbstractToggleButton::SetGroup(ButtonGroup *pGroup)
{
	// Remove event handler from old group
	if (m_pGroup) {
		m_pGroup->EventActivate.Disconnect(&SlotOnGroupActivate);
	}

	// Set group
	m_pGroup = pGroup;

	// Connect event handler to new group
	if (m_pGroup) {
		m_pGroup->EventActivate.Connect(&SlotOnGroupActivate);
	}
}

/**
*  @brief
*    Check if the toggle button can be checked partially (third state)
*/
bool AbstractToggleButton::GetPartiallyAllowed() const
{
	// Return flag
	return m_bPartiallyAllowed;
}

/**
*  @brief
*    Set if the toggle button can be checked partially (third state)
*/
void AbstractToggleButton::SetPartiallyAllowed(bool bPartiallyAllowed)
{
	// Set flag
	m_bPartiallyAllowed = bPartiallyAllowed;
}

/**
*  @brief
*    Get if the button is checked
*/
ECheckState AbstractToggleButton::GetState() const
{
	// Return checked-state
	return m_nState;
}

/**
*  @brief
*    Set if the button is checked
*/
void AbstractToggleButton::SetState(ECheckState nState)
{
	// New checked-state?
	if (m_nState != nState && (m_bPartiallyAllowed || nState != PartiallyChecked)) {
		// Set checked-state
		m_nState = nState;

		// Call virtual function
		OnButtonToggled(m_nState);

		// Inform group
		if (m_pGroup && m_nState == Checked) {
			m_pGroup->Activate(*this);
		}

		// Redraw, please
		Redraw();
	}
}

/**
*  @brief
*    Toggle button
*/
void AbstractToggleButton::Toggle()
{
	// Toggle state
	if (m_nState == NotChecked || m_nState == PartiallyChecked)
		SetState(Checked);
	else if (!m_pGroup || !m_pGroup->IsExclusive())
		SetState(NotChecked);
}


//[-------------------------------------------------------]
//[ Protected virtual AbstractToggleButton functions      ]
//[-------------------------------------------------------]
void AbstractToggleButton::OnButtonToggled(ECheckState nChecked)
{
	// Send toggled-event
	EventToggled.Emit(nChecked);
}


//[-------------------------------------------------------]
//[ Protected virtual AbstractButton functions            ]
//[-------------------------------------------------------]
void AbstractToggleButton::OnButtonClicked()
{
	// Call base implementation
	AbstractButton::OnButtonClicked();

	// Toggle button
	Toggle();
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    This function is called when a button of the group is activated
*/
void AbstractToggleButton::OnGroupActivate(AbstractToggleButton *pButton)
{
	if (m_pGroup) {
		if (m_pGroup->IsExclusive() && pButton != this) {
			// [TODO] This could be a problem (infinite loop), but let's try
			SetState(NotChecked);
//			m_nChecked = NotChecked;
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
