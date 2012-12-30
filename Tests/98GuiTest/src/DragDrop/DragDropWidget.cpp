/*********************************************************\
 *  File: DragDropWidget.cpp                             *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Gui/Gui.h>
#include <PLGui/Gui/ClipBoard.h>
#include <PLGui/Gui/Data/DataObject.h>
#include <PLGui/Widgets/Controls/Label.h>
#include <PLGui/Widgets/Controls/Button.h>
#include "DragDropWidget.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLGraphics;
using namespace PLGui;


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(DragDropWidget)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DragDropWidget::DragDropWidget(Widget *pParent) : ContainerWidget(pParent),
	EventHandlerClear(&DragDropWidget::OnClear, this),
	EventHandlerCopy (&DragDropWidget::OnCopy,  this),
	EventHandlerPaste(&DragDropWidget::OnPaste, this),
	m_pLabel(nullptr),
	m_pButtonClear(nullptr),
	m_pButtonCopy(nullptr),
	m_pButtonPaste(nullptr)
{
	// Set background color
	SetBackgroundColor(Color4::Gray);

	// Set layout
	GetContentWidget()->SetLayout("LayoutBox", "Orientation=Vertical");

	// Add label
	m_pLabel = new Label(GetContentWidget());
	m_pLabel->SetWrap(TextWrap);
	m_pLabel->SetText("<empty>");
	m_pLabel->SetVisible(true);

	// Add button 'Clear'
	m_pButtonClear = new Button(GetContentWidget());
	m_pButtonClear->SignalClicked.Connect(EventHandlerClear);
	m_pButtonClear->SetText("Clear");
	m_pButtonClear->SetVisible(true);

	// Add button 'Copy'
	m_pButtonCopy = new Button(GetContentWidget());
	m_pButtonCopy->SignalClicked.Connect(EventHandlerCopy);
	m_pButtonCopy->SetText("Copy");
	m_pButtonCopy->SetVisible(true);

	// Add button 'Paste'
	m_pButtonPaste = new Button(GetContentWidget());
	m_pButtonPaste->SignalClicked.Connect(EventHandlerPaste);
	m_pButtonPaste->SetText("Paste");
	m_pButtonPaste->SetVisible(true);

	// Adjust content
	AdjustContent();
}

/**
*  @brief
*    Destructor
*/
DragDropWidget::~DragDropWidget()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLGui::Widget functions                ]
//[-------------------------------------------------------]
void DragDropWidget::OnDrop(const DataObject &cData)
{
	// Files
	if (cData.GetType() == DataFiles) {
		// Get file list
		const Container<String> &lstFiles = cData.GetFiles();

		// Add files to text
		for (uint32 i=0; i<lstFiles.GetNumOfElements(); i++) {
			// Get filename
			// [TODO] If we use unicode here, we get some strange symbols displayed in the label.
			//        Guess there is a unicode problem, either in Label or in RegEx.
			String sFile = lstFiles[i].GetASCII();

			// Add filename
			m_sText += sFile + '\n';
		}
	}

	// Set new text
	m_pLabel->SetText(m_sText);

	// Adjust content
	AdjustContent();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Clear data
*/
void DragDropWidget::OnClear()
{
	// Clear data
	m_sText = "";

	// Set new text
	m_pLabel->SetText(m_sText);

	// Adjust content
	AdjustContent();
}

/**
*  @brief
*    Copy data to clipboard
*/
void DragDropWidget::OnCopy()
{
	// Copy text to clipboard
	GetGui()->GetClipBoard().SetText(m_sText);
}

/**
*  @brief
*    Paste data from clipboard
*/
void DragDropWidget::OnPaste()
{
	// Get text from clipboard
	String sText = GetGui()->GetClipBoard().GetText();
	if (sText.GetLength() > 0) {
		// Add text
		m_sText += sText;
	}

	// Set new text
	m_pLabel->SetText(m_sText);

	// Adjust content
	AdjustContent();
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
