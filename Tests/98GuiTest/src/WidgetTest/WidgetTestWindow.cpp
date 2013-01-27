/*********************************************************\
 *  File: ThemeTestWindow.cpp                            *
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
#include <PLMath/Vector2i.h>
#include <PLGui/Widgets/Layout/Box.h>
#include <PLGui/Widgets/Containers/Splitter.h>
#include <PLGui/Widgets/Containers/ScrollWidget.h>
#include <PLGui/Widgets/Controls/Bitmap.h>
#include <PLGui/Widgets/Controls/Slider.h>
#include <PLGui/Widgets/Controls/ScrollBar.h>
#include <PLGui/Widgets/Controls/CheckBox.h>
#include <PLGui/Widgets/Controls/RadioButton.h>
#include "WidgetTest/WidgetTestWindow.h"


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
pl_implement_class(WidgetTestWindow)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
WidgetTestWindow::WidgetTestWindow(Widget *pParent) : Window(pParent)
{
	// Set title
	SetTitle("Widget Test");

	// Destroy window on close
	AddModifier("PLGui::ModClose", "CloseWindow=1");

	// Add a vertical splitter
	Splitter *pSplitter = new Splitter(GetContentWidget());
	pSplitter->SetOrientation(Vertical);
	pSplitter->SetVisible(true);

	// Set horizontal layout
	pSplitter->GetSide(SideTop)->SetLayout("PLGui::LayoutBox", "Orientation=Horizontal");

	// Add slider
	Slider *pSlider = new Slider(pSplitter->GetSide(SideTop));
//	pSlider->SetEnabled(false);
	pSlider->SetOrientation(Vertical);
	pSlider->SetVisible(true);

	// Add scrollbar
	ScrollBar *pScrollBar = new ScrollBar(pSplitter->GetSide(SideTop));
//	pScrollBar->SetEnabled(false);
	pScrollBar->SetOrientation(Vertical);
	pScrollBar->SetVisible(true);

	// Add check boxes
	m_cButtonGroup1.SetExclusive(false);
	Box *pBox = new Box(pSplitter->GetSide(SideTop));
	pBox->SetOrientation(Vertical);
	pBox->SetVisible(true);
	for (int i=0; i<3; i++) {
		CheckBox *pCheckBox = new CheckBox(pBox->GetContentWidget());
		pCheckBox->SetGroup(&m_cButtonGroup1);
		pCheckBox->SetText(String("Option ") + i);
		pCheckBox->SetVisible(true);
	}

	// Add radio buttons
	pBox = new Box(pSplitter->GetSide(SideTop));
	pBox->SetOrientation(Vertical);
	pBox->SetVisible(true);
	for (int i=0; i<3; i++) {
		RadioButton *pRadioButton = new RadioButton(pBox->GetContentWidget());
		pRadioButton->SetGroup(&m_cButtonGroup2);
		pRadioButton->SetText(String("Option ") + i);
		pRadioButton->SetVisible(true);
	}

	// Add a horizontal splitter
	Splitter *pSplitter2 = new Splitter(pSplitter->GetSide(SideBottom));
	pSplitter2->SetOrientation(Horizontal);
	pSplitter2->SetVisible(true);

	// Set layout
	pSplitter2->GetSide(SideLeft)->SetLayout("PLGui::LayoutBox", "Orientation=Horizontal");

	// Add scroll widget
	ScrollWidget *pScrollWidget = new ScrollWidget(pSplitter2->GetSide(SideLeft));
	pScrollWidget->SetVisible(true);

	// Add bitmap
	Bitmap *pBitmap = new Bitmap(pScrollWidget->GetContentWidget());
	pBitmap->SetImage(Image(*GetGui(), "../Data/background.jpg"));
	pBitmap->SetVisible(true);

	// Set size
	SetSize(Vector2i(640, 480));
}

/**
*  @brief
*    Destructor
*/
WidgetTestWindow::~WidgetTestWindow()
{
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
