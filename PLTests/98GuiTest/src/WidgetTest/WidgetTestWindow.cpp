/*********************************************************\
 *  File: ThemeTestWindow.cpp                            *
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
using namespace PLGeneral;
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
	pBitmap->SetImage(Image(*GetGui(), "PLGui/background.jpg"));
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
