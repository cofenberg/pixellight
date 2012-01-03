/*********************************************************\
 *  File: ButtonGroup.h                                  *
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


#ifndef __PLGUI_BUTTONGROUP_H__
#define __PLGUI_BUTTONGROUP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/Event.h>
#include "PLGui/PLGui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declaration                                   ]
//[-------------------------------------------------------]
class AbstractToggleButton;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Manages a button group
*/
class ButtonGroup {


	//[-------------------------------------------------------]
	//[ Public events                                         ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<AbstractToggleButton*> EventActivate;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGUI_API ButtonGroup();

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~ButtonGroup();

		/**
		*  @brief
		*    Check if the button activation is exclusive
		*
		*  @return
		*    'true', if the button activation is exclusive, else 'false'
		*
		*  @remarks
		*    If the button activation is exclusive, only one button can be active at the same time
		*/
		PLGUI_API bool IsExclusive() const;

		/**
		*  @brief
		*    Set if the button activation is exclusive
		*
		*  @param[in] bExclusive
		*    'true', if the button activation is exclusive, else 'false'
		*/
		PLGUI_API void SetExclusive(bool bExclusive);

		/**
		*  @brief
		*    Activates a certain button
		*
		*  @param[in] cButton
		*    Button that is being activated
		*/
		PLGUI_API void Activate(AbstractToggleButton &cButton);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		bool				  m_bExclusive;	/**< If 'true', only one button can be activated at the same time */
		AbstractToggleButton *m_pButton;	/**< Button that is currently activated */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_BUTTONGROUP_H__
