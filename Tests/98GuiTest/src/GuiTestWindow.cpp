/*********************************************************\
 *  File: GuiTestWindow.cpp                              *
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
#include <PLGui/Widgets/Controls/Button.h>
#include <PLGui/Widgets/Windows/Window.h>
#include "SimpleTest/SimpleTestWindow.h"
#include "MouseOver/MouseOverWindow.h"
#include "Focus/FocusWindow.h"
#include "Window/TestWindow.h"
#include "WidgetTest/WidgetTestWindow.h"
//#include "DragDrop/DragDropWindow.h"
#include "TabsAndMenu/TabsAndMenuWindow.h"
//#include "SlimTest/SlimTestWindow.h"
#include "ThemeTest/ThemeTestWindow.h"
#include "GuiTestWindow.h"

// [DEBUG]
#include <stdio.h>


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
pl_implement_class(GuiTestWindow)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
GuiTestWindow::GuiTestWindow(Widget *pParent) : Window(pParent),
	SlotOnTrayIcon(this),
	SlotOnNotify(this),
	SlotOnWindow(this),
	SlotOnSimpleTest(this),
	SlotOnWindowTest(this),
	SlotOnMouseOverTest(this),
	SlotOnFocusTest(this),
	SlotOnWidgetTest(this),
	SlotOnDragDropTest(this),
	SlotOnTabsAndMenuTest(this),
	SlotOnSlimTest(this),
	SlotOnThemeTest(this),
	m_cTrayIcon(*GetGui())
{
	// Set title
	SetTitle("PLGui test");

	// Exit application on close
	AddModifier("PLGui::ModClose", "ExitApplication=1");

	// Set layout
	GetContentWidget()->SetLayout("LayoutBox", "Orientation=Vertical");
	GetContentWidget()->GetLayoutHints().SetPadding(SizeHint(SizeHint::Pixel, 25));

	// Connect tray icon event
	m_cTrayIcon.EventMouseButtonClick.Connect(SlotOnTrayIcon);

	// Add button for 'Notify'
	Button *pButton = new Button(GetContentWidget());
	pButton->SetText("Notify Me");
	pButton->SetVisible(true);
	pButton->SetEnabled(false);
	pButton->SignalClicked.Connect(SlotOnNotify);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Display notification message\"");

	// Add button for 'Window'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Window");
	pButton->SetVisible(true);
	pButton->SignalClicked.Connect(SlotOnWindow);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Create an empty window\"");

	// Add button for 'Simple Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Simple Test");
	pButton->SetVisible(true);
	pButton->SignalClicked.Connect(SlotOnSimpleTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Show test with simple widgets\"");

	// Add button for 'Window Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Window Test");
	pButton->SetVisible(true);
	pButton->SignalClicked.Connect(SlotOnWindowTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Show test window\"");

	// Add button for 'Mouse-Over Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Mouse-Over Test");
	pButton->SetVisible(true);
	pButton->SignalClicked.Connect(SlotOnMouseOverTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Test mouse-over functionality\"");

	// Add button for 'Focus Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Focus Test");
	pButton->SetVisible(true);
	pButton->SignalClicked.Connect(SlotOnFocusTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Test focus functionality\"");

	// Add button for 'Focus Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Widget Test");
	pButton->SetVisible(true);
	pButton->SignalClicked.Connect(SlotOnWidgetTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Test widgets\"");

	// Add button for 'Drag&Drop Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Drag&Drop Test");
	pButton->SetVisible(true);
	pButton->SignalClicked.Connect(SlotOnDragDropTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Test drag&drop functionality\"");

	// Add button for 'Tabs&Menu Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Tabs&Menu Test");
	pButton->SetVisible(true);
	pButton->SignalClicked.Connect(SlotOnTabsAndMenuTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Test tabs and menus\"");

	// Add button for 'Slim Widgets Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Slim Widgets Test");
	pButton->SetVisible(true);
	pButton->SignalClicked.Connect(SlotOnSlimTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Test slim widgets\"");

	// Add button for 'Theme Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Theme Test");
	pButton->SetVisible(true);
	pButton->SignalClicked.Connect(SlotOnThemeTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Test theme functionality\"");

	// Set size
	SetSize(Vector2i(800, 600));
}

/**
*  @brief
*    Destructor
*/
GuiTestWindow::~GuiTestWindow()
{
}


//[-------------------------------------------------------]
//[ Protected virtual PLGui::WidgetFunctions functions    ]
//[-------------------------------------------------------]
void GuiTestWindow::OnShow()
{
	// Show tray icon
	m_cTrayIcon.SetIcon(GetIcon());
	m_cTrayIcon.SetVisible(true);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
void GuiTestWindow::OnTrayIcon(uint32, const Vector2i&)
{
	// Toggle main window visibility
	bool bVisible = !IsVisible();
	SetVisible(bVisible);
	if (bVisible) {
		// Activate window
		Activate();
	}
}

void GuiTestWindow::OnNotify()
{
	m_cTrayIcon.ShowNotification("Notification", "Hello...");
}

void GuiTestWindow::OnWindow()
{
	// Create window
	Window *pWindow = new Window();
	pWindow->AddModifier("PLGui::ModClose", "CloseWindow=1");
	pWindow->SetIcon(GetIcon());
	pWindow->SetPos(Vector2i(300, 300));
	pWindow->SetSize(Vector2i(640, 480));
	pWindow->SetVisible(true);
	pWindow->Activate();
}

void GuiTestWindow::OnSimpleTest()
{
	// Simple test
	SimpleTestWindow *pWindow = new SimpleTestWindow();
	pWindow->SetIcon(GetIcon());
	pWindow->SetPos(Vector2i(150, 150));
	pWindow->SetVisible(true);
	pWindow->Activate();
}

void GuiTestWindow::OnWindowTest()
{
	// Window test
	TestWindow *pWindow = new TestWindow();
	pWindow->SetIcon(GetIcon());
	pWindow->SetPos(Vector2i(250, 250));
	pWindow->SetVisible(true);
	pWindow->Activate();
}

void GuiTestWindow::OnMouseOverTest()
{
	// MouseOver test
	MouseOverWindow *pWindow = new MouseOverWindow();
	pWindow->SetIcon(GetIcon());
	pWindow->SetPos(Vector2i(250, 150));
	pWindow->SetVisible(true);
	pWindow->Activate();
}

void GuiTestWindow::OnFocusTest()
{
	// Focus test
	FocusWindow *pWindow = new FocusWindow();
	pWindow->SetIcon(GetIcon());
	pWindow->SetPos(Vector2i(250, 150));
	pWindow->SetVisible(true);
	pWindow->Activate();
}

void GuiTestWindow::OnWidgetTest()
{
	// Widget test
	WidgetTestWindow *pWindow = new WidgetTestWindow();
	pWindow->SetIcon(GetIcon());
	pWindow->SetPos(Vector2i(250, 150));
	pWindow->SetVisible(true);
	pWindow->Activate();
}

void GuiTestWindow::OnDragDropTest()
{
	/*
	// Drag&Drop test
	DragDropWindow *pWindow = new DragDropWindow();
	pWindow->SetIcon(GetIcon());
	pWindow->SetPos(Vector2i(350, 50));
	pWindow->SetVisible(true);
	pWindow->Activate();
	*/
}

void GuiTestWindow::OnTabsAndMenuTest()
{
	// Tabs&Menu test
	TabsAndMenuWindow *pWindow = new TabsAndMenuWindow();
	pWindow->SetIcon(GetIcon());
	pWindow->SetPos(Vector2i(400, 300));
	pWindow->SetVisible(true);
	pWindow->Activate();
}

void GuiTestWindow::OnSlimTest()
{
	/*
	// Slim widgets test
	SlimTestWindow *pWindow = new SlimTestWindow();
	pWindow->SetIcon(GetIcon());
	pWindow->SetPos(Vector2i(400, 300));
	pWindow->SetVisible(true);
	pWindow->Activate();
	*/
}

void GuiTestWindow::OnThemeTest()
{
	// Slim widgets test
	ThemeTestWindow *pWindow = new ThemeTestWindow();
	pWindow->SetIcon(GetIcon());
	pWindow->SetPos(Vector2i(400, 300));
	pWindow->SetVisible(true);
	pWindow->Activate();
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
