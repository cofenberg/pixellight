/*********************************************************\
 *  File: TestWindow.cpp                                 *
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
#include <PLGui/Gui/Gui.h>
#include <PLGui/Widgets/Controls/Button.h>
#include <PLGui/Widgets/Controls/ToggleButton.h>
#include "Window/TestWindow.h"


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
pl_implement_class(TestWindow)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TestWindow::TestWindow(Widget *pParent) : Window(pParent),
	SlotOnToggleFullscreen(this),
	SlotOnToggleTitleBar(this),
	SlotOnToggleBorder(this),
	SlotOnToggleTopmost(this),
	SlotOnToggleTaskbar(this),
	m_pButtonTitleBar(nullptr),
	m_pButtonBorder(nullptr),
	m_pButtonTopmost(nullptr)
{
	// Set name
	SetName("TestWindow");

	// Set title
	SetTitle("Window Test");

	// Destroy window on close
	AddModifier("PLGui::ModClose", "CloseWindow=1");

	// Let us switch to fullscreen with ALT+ENTER
	AddModifier("PLGui::ModFullscreen", "");

	// Set layout
	GetContentWidget()->SetLayout("LayoutBox", "Orientation=Vertical");
	GetContentWidget()->GetLayoutHints().SetPadding(SizeHint(SizeHint::Pixel, 25));

	// Make not resizable and disable maximize button
	SetResizable(false);
	SetSystemButtons(SystemButtonMinimize | SystemButtonClose);

	// Add button to toggle fullscreen mode
	m_pButtonFullscreen = new Button(GetContentWidget());
	m_pButtonFullscreen->SetText("Fullscreen Mode");
	m_pButtonFullscreen->SetVisible(true);
	m_pButtonFullscreen->SignalClicked.Connect(SlotOnToggleFullscreen);

	// Add button to toggle title bar visibility
	m_pButtonTitleBar = new Button(GetContentWidget());
	m_pButtonTitleBar->SetText("Title Bar");
	m_pButtonTitleBar->SetVisible(true);
	m_pButtonTitleBar->SignalClicked.Connect(SlotOnToggleTitleBar);

	// Add button to toggle border visibility
	m_pButtonBorder = new Button(GetContentWidget());
	m_pButtonBorder->SetText("Border");
	m_pButtonBorder->SetVisible(true);
	m_pButtonBorder->SignalClicked.Connect(SlotOnToggleBorder);

	// Add button to toggle topmost-state
	m_pButtonTopmost = new ToggleButton(GetContentWidget());
	m_pButtonTopmost->SetText("Stay On Top");
	m_pButtonTopmost->SetVisible(true);
	m_pButtonTopmost->SignalToggled.Connect(SlotOnToggleTopmost);

	// Add button to toggle taskbar-visibility
	m_pButtonTaskbar = new ToggleButton(GetContentWidget());
	m_pButtonTaskbar->SetText("Show In Taskbar");
	m_pButtonTaskbar->SetState(IsShowInTaskbar() ? Checked : NotChecked);
	m_pButtonTaskbar->SetVisible(true);
	m_pButtonTaskbar->SignalToggled.Connect(SlotOnToggleTaskbar);

	// Set size
	SetSize(Vector2i(640, 480));
}

/**
*  @brief
*    Destructor
*/
TestWindow::~TestWindow()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Toggle fullscreen mode
*/
void TestWindow::OnToggleFullscreen()
{
	SetWindowState(GetWindowState() != StateFullscreen ? StateFullscreen : StateNormal);
}

/**
*  @brief
*    Toggle title bar visibility
*/
void TestWindow::OnToggleTitleBar()
{
	SetShowTitleBar(!GetShowTitleBar());
}

/**
*  @brief
*    Toggle border visibility
*/
void TestWindow::OnToggleBorder()
{
	SetShowBorder(!GetShowBorder());
}

/**
*  @brief
*    Toggle topmost state
*/
void TestWindow::OnToggleTopmost(ECheckState nState)
{
	SetTopmost(nState == Checked);
}

/**
*  @brief
*    Toggle taskbar visibility
*/
void TestWindow::OnToggleTaskbar(ECheckState nState)
{
	SetShowInTaskbar(nState == Checked);
	m_pButtonTaskbar->SetFocus();
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
