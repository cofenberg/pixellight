/*********************************************************\
 *  File: DragDropWidget.h                               *
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


#ifndef __PLSAMPLE99_DRAGDROPWIDGET_H__
#define __PLSAMPLE99_DRAGDROPWIDGET_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include <PLGeneral/String/String.h>
#include <PLGui/Widgets/Containers/ContainerWidget.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGui {
	class Label;
	class Button;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Test widget that shows drag&drop functionality
*/
class DragDropWidget : public PLGui::ContainerWidget {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, DragDropWidget, "", PLGui::ContainerWidget, "Test widget that shows drag&drop functionality")
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
		*/
		DragDropWidget(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~DragDropWidget();


	//[-------------------------------------------------------]
	//[ Public virtual Widget functions                       ]
	//[-------------------------------------------------------]
	public:
		virtual void OnDrop(const PLGui::DataObject &cData);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Clear data
		*/
		void OnClear();

		/**
		*  @brief
		*    Copy data to clipboard
		*/
		void OnCopy();

		/**
		*  @brief
		*    Paste data from clipboard
		*/
		void OnPaste();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Event handlers
		PLCore::EventHandler<>	EventHandlerClear;
		PLCore::EventHandler<>	EventHandlerCopy;
		PLCore::EventHandler<>	EventHandlerPaste;

		// Widgets
		PLGui::Label  *m_pLabel;			/**< Text label */
		PLGui::Button *m_pButtonClear;		/**< Button 'Clear' */
		PLGui::Button *m_pButtonCopy;		/**< Button 'Copy' */
		PLGui::Button *m_pButtonPaste;		/**< Button 'Paste' */

		// Data
		PLGeneral::String m_sText;		/**< Text */


};


#endif // __PLSAMPLE99_DRAGDROPWIDGET_H__
