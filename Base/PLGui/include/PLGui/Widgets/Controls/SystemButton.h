/*********************************************************\
 *  File: SystemButton.h                                 *
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


#ifndef __PLGUI_SYSTEMBUTTON_H__
#define __PLGUI_SYSTEMBUTTON_H__
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
class Timer;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Button that represents a system button in a title bar (minimize, maximize, ...)
*/
class SystemButton: public AbstractButton {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, SystemButton, "PLGui", PLGui::AbstractButton, "Button that represents a system button in a title bar (minimize, maximize, ...)")
		// Attributes
		pl_attribute(SystemCommand,	pl_enum_type(ESystemCommand),	CommandRestore,	ReadWrite,	GetSet,	"System command that is emitted by the button",	"")
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
		*
		*  @param[in] pParent
		*    Pointer to the parent widget
		*/
		PLGUI_API SystemButton(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~SystemButton();

		/**
		*  @brief
		*    Get widget state
		*
		*  @return
		*    Widget states as flags (see EWidgetState)
		*/
		PLGUI_API virtual PLCore::uint32 GetWidgetState() const;

		/**
		*  @brief
		*    Get system command that the button represents
		*
		*  @return
		*    System command
		*/
		PLGUI_API ESystemCommand GetSystemCommand() const;

		/**
		*  @brief
		*    Set system command that the button represents
		*
		*  @param[in] nSystemCommand
		*    System command
		*/
		PLGUI_API void SetSystemCommand(ESystemCommand nSystemCommand);


	//[-------------------------------------------------------]
	//[ Private virtual AbstractButton functions              ]
	//[-------------------------------------------------------]
	private:
		PLGUI_API virtual void OnButtonClicked() override;


	//[-------------------------------------------------------]
	//[ Private virtual WidgetFunctions functions             ]
	//[-------------------------------------------------------]
	private:
		PLGUI_API virtual void OnDraw(Graphics &cGraphics) override;
		PLGUI_API virtual PLMath::Vector2i OnPreferredSize(const PLMath::Vector2i &vRefSize) const override;
		PLGUI_API virtual void OnMouseEnter() override;
		PLGUI_API virtual void OnMouseLeave() override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		ESystemCommand m_nSystemCommand;	/**< System command that is emitted by the button */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_SYSTEMBUTTON_H__
