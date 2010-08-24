/*********************************************************\
 *  File: DragDropWidget.cpp                             *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
using namespace PLGeneral;
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
	m_pLabel(NULL),
	m_pButtonClear(NULL),
	m_pButtonCopy(NULL),
	m_pButtonPaste(NULL)
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
	m_pButtonClear->EventClicked.Connect(&EventHandlerClear);
	m_pButtonClear->SetText("Clear");
	m_pButtonClear->SetVisible(true);

	// Add button 'Copy'
	m_pButtonCopy = new Button(GetContentWidget());
	m_pButtonCopy->EventClicked.Connect(&EventHandlerCopy);
	m_pButtonCopy->SetText("Copy");
	m_pButtonCopy->SetVisible(true);

	// Add button 'Paste'
	m_pButtonPaste = new Button(GetContentWidget());
	m_pButtonPaste->EventClicked.Connect(&EventHandlerPaste);
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
//[ Public virtual Widget functions                       ]
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
			m_sText += sFile + "\n";
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
