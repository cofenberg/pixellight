/*********************************************************\
 *  File: SlimTestWindow.cpp                             *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Gui/Gui.h>
#include <PLGui/Widgets/Layout/Box.h>
#include <PLGui/Widgets/Containers/ScrollWidget.h>
#include <PLGui/Widgets/Controls/Button.h>
#include <PLGui/Widgets/Slim/SlimEntry.h>
#include "SlimTest/SlimTestWindow.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGui;


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(SlimTestWindow)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SlimTestWindow::SlimTestWindow(Widget *pParent) : Window(pParent),
	SlotOnLeft(this),
	SlotOnRight(this),
	m_pButtonLeft(nullptr),
	m_pButtonRight(nullptr)
{
	// Set title
	SetTitle("Slim Widgets Test");

	// Close window on close
	AddModifier("PLGui::ModClose", "CloseWindow=1");

	// Set layout
	GetContentWidget()->SetLayout("LayoutBox", "Orientation=Horizontal");
	GetContentWidget()->GetLayoutHints().SetPadding(SizeHint(SizeHint::Pixel, 25));

	// Add left container
	m_pContainerLeft = new ScrollWidget(GetContentWidget());
	m_pContainerLeft->SetVisible(true);
	m_pContainerLeft->GetContentWidget()->SetLayout("LayoutBox", "Orientation=Vertical");
	m_pContainerLeft->GetContentWidget()->SetSize(Vector2i(512, 1024));

		// Add entry
		SlimEntry *pEntry = new SlimEntry(m_pContainerLeft->GetContentWidget());
		pEntry->SetVisible(true);

	// Add button box
	m_pButtonBox = new Box(GetContentWidget());
	m_pButtonBox->SetOrientation(Vertical);
	m_pButtonBox->SetVisible(true);

		// Add left button
		m_pButtonLeft = new Button(m_pButtonBox->GetContentWidget());
		m_pButtonLeft->SetText("<<");
		m_pButtonLeft->SetVisible(true);
		m_pButtonLeft->SignalClicked.Connect(&SlotOnLeft);

		// Add right button
		m_pButtonRight = new Button(m_pButtonBox->GetContentWidget());
		m_pButtonRight->SetText(">>");
		m_pButtonRight->SetVisible(true);
		m_pButtonRight->SignalClicked.Connect(&SlotOnRight);

	// Add right container
	m_pContainerRight = new ScrollWidget(GetContentWidget());
	m_pContainerRight->SetVisible(true);
	m_pContainerRight->GetContentWidget()->SetLayout("LayoutBox", "Orientation=Vertical");

		// Add entry
		pEntry = new SlimEntry(m_pContainerRight->GetContentWidget());
		pEntry->SetVisible(true);

	// Set size
	SetSize(Vector2i(640, 480));
}

/**
*  @brief
*    Destructor
*/
SlimTestWindow::~SlimTestWindow()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Left button pressed
*/
void SlimTestWindow::OnLeft()
{
}

/**
*  @brief
*    Right button pressed
*/
void SlimTestWindow::OnRight()
{
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
