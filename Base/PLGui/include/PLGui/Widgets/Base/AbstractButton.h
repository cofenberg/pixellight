/*********************************************************\
 *  File: AbstractButton.h                               *
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


#ifndef __PLGUI_ABSTRACTBUTTON_H__
#define __PLGUI_ABSTRACTBUTTON_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>
#include "PLGui/Gui/Resources/Image.h"
#include "PLGui/Gui/Resources/Timer.h"
#include "PLGui/Widgets/Widget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract base class for all kind of buttons
*/
class AbstractButton : public Widget {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, AbstractButton, "PLGui", PLGui::Widget, "Abstract base class for all kind of buttons")
		// Attributes
		pl_attribute(Text,				PLCore::String,		"",							ReadWrite,	GetSet,	"Text that is displayed on the button",					"")
		pl_attribute(ImageName,			PLCore::String,		"",							ReadWrite,	GetSet,	"Image filename",										"")
		pl_attribute(ImageSize,			PLMath::Vector2i,	PLMath::Vector2i(16, 16),	ReadWrite,	GetSet,	"Image size",											"")
		pl_attribute(Repeat,			bool,				false,						ReadWrite,	GetSet,	"If the button is hold down, emit clicks repeatedly",	"")
		pl_attribute(RepeatDelay,		PLCore::uint64,		500,						ReadWrite,	GetSet,	"Initial delay (in ms) for repeated clicks",			"")
		pl_attribute(RepeatInterval,	PLCore::uint64,		500,						ReadWrite,	GetSet,	"Interval (in ms) between repeated clicks",				"")
		// Signals
		pl_signal_0(SignalPressed,	"The button has been pressed down",						"")
		pl_signal_0(SignalReleased,	"The button has been released",							"")
		pl_signal_0(SignalClicked,	"The button has been clicked (pressed and released)",	"")
		// Slots
		pl_slot_0(OnTimer,	"Timer callback",	"")
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
		PLGUI_API AbstractButton(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~AbstractButton();

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
		*    Get button text
		*
		*  @return
		*    Text that is displayed on the button
		*/
		PLGUI_API PLCore::String GetText() const;

		/**
		*  @brief
		*    Set button text
		*
		*  @param[in] sText
		*    Text that is displayed on the button
		*/
		PLGUI_API void SetText(const PLCore::String &sText);

		/**
		*  @brief
		*    Get image
		*
		*  @return
		*    Image that is displayed on the button
		*/
		PLGUI_API const Image &GetImage() const;

		/**
		*  @brief
		*    Set image
		*
		*  @param[in] cImage
		*    Image that is displayed on the button
		*/
		PLGUI_API void SetImage(const Image &cImage);

		/**
		*  @brief
		*    Get image filename
		*
		*  @return
		*    Image that is displayed on the button
		*/
		PLGUI_API PLCore::String GetImageName() const;

		/**
		*  @brief
		*    Set image filename
		*
		*  @param[in] sImage
		*    Image that is displayed on the button
		*/
		PLGUI_API void SetImageName(const PLCore::String &sImage);

		/**
		*  @brief
		*    Get image size
		*
		*  @return
		*    Size of image
		*/
		PLGUI_API const PLMath::Vector2i &GetImageSize() const;

		/**
		*  @brief
		*    Set image size
		*
		*  @param[in] vSize
		*    Size of image
		*/
		PLGUI_API void SetImageSize(const PLMath::Vector2i &vSize);

		/**
		*  @brief
		*    Get repeat-mode
		*
		*  @return
		*    'true' if repeat-mode is enabled, else 'false'
		*/
		PLGUI_API bool GetRepeat() const;

		/**
		*  @brief
		*    Set repeat-mode
		*
		*  @param[in] bRepeat
		*    'true' if repeat-mode is enabled, else 'false'
		*/
		PLGUI_API void SetRepeat(bool bRepeat);

		/**
		*  @brief
		*    Get repeat delay
		*
		*  @return
		*    Initial delay (in ms) before auto-repeat
		*/
		PLGUI_API PLCore::uint64 GetRepeatDelay() const;

		/**
		*  @brief
		*    Set repeat delay
		*
		*  @param[in] nDelay
		*    Initial delay (in ms) before auto-repeat
		*/
		PLGUI_API void SetRepeatDelay(PLCore::uint64 nDelay);

		/**
		*  @brief
		*    Get repeat interval
		*
		*  @return
		*    Interval (in ms) between auto-repeated clicks
		*/
		PLGUI_API PLCore::uint64 GetRepeatInterval() const;

		/**
		*  @brief
		*    Set repeat interval
		*
		*  @param[in] nInterval
		*    Interval (in ms) between auto-repeated clicks
		*/
		PLGUI_API void SetRepeatInterval(PLCore::uint64 nInterval);

		/**
		*  @brief
		*    Returns whether the button is currently pressed or not
		*
		*  @return
		*    'true' if the button is currently pressed, else 'false'
		*/
		PLGUI_API bool IsPressed() const;


	//[-------------------------------------------------------]
	//[ Protected virtual AbstractButton functions            ]
	//[-------------------------------------------------------]
	protected:
		PLGUI_API virtual void OnButtonPressed();
		PLGUI_API virtual void OnButtonReleased();
		PLGUI_API virtual void OnButtonClicked();


	//[-------------------------------------------------------]
	//[ Protected virtual Widget functions                    ]
	//[-------------------------------------------------------]
	protected:
		PLGUI_API virtual void OnDisable() override;
		PLGUI_API virtual void OnGetFocus() override;
		PLGUI_API virtual void OnLooseFocus() override;
		PLGUI_API virtual void OnMouseEnter() override;
		PLGUI_API virtual void OnMouseLeave() override;
		PLGUI_API virtual void OnMouseMove(const PLMath::Vector2i &vPos) override;
		PLGUI_API virtual void OnMouseButtonDown(PLCore::uint32 nButton, const PLMath::Vector2i &vPos) override;
		PLGUI_API virtual void OnMouseButtonUp(PLCore::uint32 nButton, const PLMath::Vector2i &vPos) override;
		PLGUI_API virtual void OnKeyDown(PLCore::uint32 nKey, PLCore::uint32 nModifiers) override;
		PLGUI_API virtual void OnKeyUp(PLCore::uint32 nKey, PLCore::uint32 nModifiers) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Press button down
		*/
		void PressButton();

		/**
		*  @brief
		*    Release button
		*
		*  @param[in] bClick
		*    If 'true', the button will emit a click event
		*/
		void ReleaseButton(bool bClick);

		/**
		*  @brief
		*    Called when the timer has fired
		*/
		void OnTimer();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Button options
		PLCore::String		m_sText;			/**< Text that is displayed on the button */
		Image				m_cImage;			/**< Image that is displayed on the button */
		PLMath::Vector2i	m_vImageSize;		/**< Size of image (usually 16x16) */
		bool				m_bRepeat;			/**< If the button is hold down, emit clicks repeatedly */
		PLCore::uint64		m_nRepeatDelay;		/**< Initial delay (in ms) for repeated clicks */
		PLCore::uint64		m_nRepeatInterval;	/**< Interval (in ms) between repeated clicks */

		// Button state
		bool				m_bPressed;			/**< Is the button currently pressed? */
		bool				m_bMouseIn;			/**< Is the mouse inside the button? */
		bool				m_bMousePressed;	/**< Is there currently a mouse button pressed? */

		// Tools
		Timer				m_cTimer;			/**< Timer for repeated clicks */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_ABSTRACTBUTTON_H__
