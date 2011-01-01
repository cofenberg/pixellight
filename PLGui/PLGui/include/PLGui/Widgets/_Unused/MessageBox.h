/*********************************************************\
 *  File: MessageBox.h                                   *
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


#ifndef __PLGUI_MESSAGEBOX_H__
#define __PLGUI_MESSAGEBOX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include <PLGeneral/String/String.h>
#include "PLGui/Widgets/Windows/Dialog.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Label;
class Button;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Message box
*/
class MessageBox : public Dialog {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, MessageBox, "PLGui", PLGui::Dialog, "Message box")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
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
		*    Pointer to parent widget
		*  @param[in] nType
		*    Message box type
		*  @param[in] sTitle
		*    Message box title
		*  @param[in] sText
		*    Message box text
		*/
		PLGUI_API MessageBox(Widget *pParent = NULL, EMessageBox nType = MessageBoxOk, const PLGeneral::String &sTitle = "Message Box", const PLGeneral::String &sText = "Message");

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nType
		*    Message box type
		*  @param[in] sTitle
		*    Message box title
		*  @param[in] sText
		*    Message box text
		*/
		PLGUI_API MessageBox(EMessageBox nType, const PLGeneral::String &sTitle, const PLGeneral::String &sText);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~MessageBox();

		/**
		*  @brief
		*    Get message box type
		*
		*  @return
		*    Type of message box
		*/
		PLGUI_API EMessageBox GetType() const;

		/**
		*  @brief
		*    Get text
		*
		*  @return
		*    Text
		*/
		PLGUI_API PLGeneral::String GetText() const;

		/**
		*  @brief
		*    Set text
		*
		*  @param[in] sText
		*    Text
		*/
		PLGUI_API void SetText(const PLGeneral::String &sText);

		/**
		*  @brief
		*    Get button text
		*
		*  @param[in] nButton
		*    Button ID
		*
		*  @return
		*    Text
		*/
		PLGUI_API PLGeneral::String GetButtonText(EMessageBoxButton nButton) const;

		/**
		*  @brief
		*    Set button text
		*
		*  @param[in] nButton
		*    Button ID
		*  @param[in] sText
		*    Text
		*/
		PLGUI_API void SetButtonText(EMessageBoxButton nButton, const PLGeneral::String &sText);


	//[-------------------------------------------------------]
	//[ Private virtual Dialog functions                      ]
	//[-------------------------------------------------------]
	private:
		PLGUI_API virtual void OnCloseDialog(int nResult);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Create message box
		*
		*  @param[in] nType
		*    Message box type
		*  @param[in] sTitle
		*    Message box title
		*  @param[in] sText
		*    Message box text
		*/
		void CreateMessageBox(EMessageBox nType, const PLGeneral::String &sTitle, const PLGeneral::String &sText);

		/**
		*  @brief
		*    Button 'Ok' has been clicked
		*/
		void OnButtonOk();

		/**
		*  @brief
		*    Button 'Cancel' has been clicked
		*/
		void OnButtonCancel();

		/**
		*  @brief
		*    Button 'Yes' has been clicked
		*/
		void OnButtonYes();

		/**
		*  @brief
		*    Button 'No' has been clicked
		*/
		void OnButtonNo();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Event handlers
		PLCore::EventHandler<>	EventHandlerOk;
		PLCore::EventHandler<>	EventHandlerCancel;
		PLCore::EventHandler<>	EventHandlerYes;
		PLCore::EventHandler<>	EventHandlerNo;

		// Data
		EMessageBox			 m_nType;			/**< Message box type */
		PLGeneral::String	 m_sText;			/**< Message box text */

		// Widgets
		Label				*m_pLabel;			/**< Text label */
		Box					*m_pBox;			/**< Button box */
		Button				*m_pButtonOk;		/**< Button 'Ok' */
		Button				*m_pButtonCancel;	/**< Button 'Cancel' */
		Button				*m_pButtonYes;		/**< Button 'Yes' */
		Button				*m_pButtonNo;		/**< Button 'No' */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_MESSAGEBOX_H__
