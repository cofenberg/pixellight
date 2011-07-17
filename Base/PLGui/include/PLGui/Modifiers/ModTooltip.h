/*********************************************************\
 *  File: ModTooltip.h                                   *
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


#ifndef __PLGUI_MODTOOLTIP_H__
#define __PLGUI_MODTOOLTIP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Modifiers/Modifier.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Modifier that displays a tooltip for a widget
*/
class ModTooltip : public Modifier {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, ModTooltip, "PLGui", PLGui::Modifier, "Modifier that displays a tooltip for a widget")
		// Attributes
		pl_attribute(Tooltip,	PLGeneral::String,	"",	ReadWrite,	GetSet,	"Tooltip text",	"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGUI_API ModTooltip();

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~ModTooltip();

		/**
		*  @brief
		*    Get tooltip text
		*
		*  @return
		*    Tooltip text
		*/
		PLGUI_API PLGeneral::String GetTooltip() const;

		/**
		*  @brief
		*    Set tooltip text
		*
		*  @param[in] sTooltip
		*    Tooltip text
		*/
		PLGUI_API void SetTooltip(const PLGeneral::String &sTooltip);


	//[-------------------------------------------------------]
	//[ Protected virtual ModTooltip functions                ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called when a tooltip shall be displayed
		*/
		virtual void OnShowTooltip();


	//[-------------------------------------------------------]
	//[ Protected virtual Modifier functions                  ]
	//[-------------------------------------------------------]
	protected:
		virtual void OnAttach(Widget &cWidget);
		virtual void OnDetach(Widget &cWidget);


	//[-------------------------------------------------------]
	//[ Protected virtual WidgetFunctions functions           ]
	//[-------------------------------------------------------]
	protected:
		void OnMouseHover();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::String m_sTooltip;	/**< Tooltip text */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_MODTOOLTIP_H__
