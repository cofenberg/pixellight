/*********************************************************\
 *  File: DragDropWidget.h                               *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLSAMPLE99_DRAGDROPWIDGET_H__
#define __PLSAMPLE99_DRAGDROPWIDGET_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include <PLCore/String/String.h>
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
		*    Pointer to parent widget
		*/
		DragDropWidget(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~DragDropWidget();


	//[-------------------------------------------------------]
	//[ Public virtual PLGui::Widget functions                ]
	//[-------------------------------------------------------]
	public:
		virtual void OnDrop(const PLGui::DataObject &cData) override;


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
		PLCore::String m_sText;		/**< Text */


};


#endif // __PLSAMPLE99_DRAGDROPWIDGET_H__
