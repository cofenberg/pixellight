/*********************************************************\
 *  File: AbstractToggleButton.h                         *
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


#ifndef __PLGUI_ABSTRACTTOGGLEBUTTON_H__
#define __PLGUI_ABSTRACTTOGGLEBUTTON_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Widgets/Base/AbstractButton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class ButtonGroup;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract base class for toggle buttons (two or three states)
*/
class AbstractToggleButton : public AbstractButton {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, AbstractToggleButton, "PLGui", PLGui::AbstractButton, "Abstract base class for toggle buttons (two or three states)")
		pl_attribute	(PartiallyAllowed,	bool,						false,		ReadWrite, GetSet,	"Is the third state (PartiallyChecked) allowed?",	"")
		pl_attribute	(State,				pl_enum_type(ECheckState),	NotChecked,	ReadWrite, GetSet,	"Current check state",								"")
		pl_slot_1		(OnGroupActivate,	AbstractToggleButton*,										"Group callback",									"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public events                                         ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<ECheckState> EventToggled;	/**< The button has been toggled */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pParent
		*    Pointer to the parent widget
		*/
		PLGUI_API AbstractToggleButton(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~AbstractToggleButton();

		/**
		*  @brief
		*    Get group that the toggle button belongs to
		*
		*  @return
		*    Pointer to button group (can be a null pointer)
		*/
		PLGUI_API ButtonGroup *GetGroup() const;

		/**
		*  @brief
		*    Set group that the toggle button belongs to
		*
		*  @param[in] pGroup
		*    Pointer to button group
		*/
		PLGUI_API void SetGroup(ButtonGroup *pGroup);

		/**
		*  @brief
		*    Check if the toggle button can be checked partially (third state)
		*
		*  @return
		*    'true', if the state PartiallyChecked is allowed, else 'false'
		*/
		PLGUI_API bool GetPartiallyAllowed() const;

		/**
		*  @brief
		*    Set if the toggle button can be checked partially (third state)
		*
		*  @param[in] bPartiallyAllowed
		*    'true', if the state PartiallyChecked is allowed, else 'false'
		*/
		PLGUI_API void SetPartiallyAllowed(bool bPartiallyAllowed);

		/**
		*  @brief
		*    Get checked-state of button
		*
		*  @return
		*    Check state
		*/
		PLGUI_API ECheckState GetState() const;

		/**
		*  @brief
		*    Set checked-state of button
		*
		*  @param[in] nState
		*    Check state
		*
		*  @remarks
		*    This function also emits a checked-event when called.
		*/
		PLGUI_API void SetState(ECheckState nState);

		/**
		*  @brief
		*    Toggle button
		*
		*  @remarks
		*    Toggles the state of the button in the following way:
		*      NotChecked     -> Checked
		*      PartialChecked -> Checked
		*      Checked        -> NotChecked
		*    This function also emits a checked-event when called.
		*/
		PLGUI_API void Toggle();


	//[-------------------------------------------------------]
	//[ Protected virtual AbstractToggleButton functions      ]
	//[-------------------------------------------------------]
	protected:
		virtual void OnButtonToggled(ECheckState nChecked);


	//[-------------------------------------------------------]
	//[ Protected virtual AbstractButton functions            ]
	//[-------------------------------------------------------]
	protected:
		virtual void OnButtonClicked();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    This function is called when a button of the group is activated
		*
		*  @param[in] pButton
		*    Pointer to button that is being activated
		*/
		void OnGroupActivate(AbstractToggleButton *pButton);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		ButtonGroup	*m_pGroup;				/**< Pointer to button group, can be a null pointer */
		bool		 m_bPartiallyAllowed;	/**< Is the third state (PartiallyChecked) allowed? */
		ECheckState  m_nState;				/**< Current check state */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_ABSTRACTTOGGLEBUTTON_H__
