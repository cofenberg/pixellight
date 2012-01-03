/*********************************************************\
 *  File: SlimTestWindow.cpp                             *
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
