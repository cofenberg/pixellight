/*********************************************************\
 *  File: GuiTestWindow.cpp                              *
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
using namespace PLGeneral;
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
	m_cTrayIcon.EventMouseButtonClick.Connect(&SlotOnTrayIcon);

	// Add button for 'Notify'
	Button *pButton = new Button(GetContentWidget());
	pButton->SetText("Notify Me");
	pButton->SetVisible(true);
	pButton->SetEnabled(false);
	pButton->EventClicked.Connect(&SlotOnNotify);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Display notification message\"");

	// Add button for 'Window'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Window");
	pButton->SetVisible(true);
	pButton->EventClicked.Connect(&SlotOnWindow);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Create an empty window\"");

	// Add button for 'Simple Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Simple Test");
	pButton->SetVisible(true);
	pButton->EventClicked.Connect(&SlotOnSimpleTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Show test with simple widgets\"");

	// Add button for 'Window Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Window Test");
	pButton->SetVisible(true);
	pButton->EventClicked.Connect(&SlotOnWindowTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Show test window\"");

	// Add button for 'Mouse-Over Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Mouse-Over Test");
	pButton->SetVisible(true);
	pButton->EventClicked.Connect(&SlotOnMouseOverTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Test mouse-over functionality\"");

	// Add button for 'Focus Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Focus Test");
	pButton->SetVisible(true);
	pButton->EventClicked.Connect(&SlotOnFocusTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Test focus functionality\"");

	// Add button for 'Focus Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Widget Test");
	pButton->SetVisible(true);
	pButton->EventClicked.Connect(&SlotOnWidgetTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Test widgets\"");

	// Add button for 'Drag&Drop Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Drag&Drop Test");
	pButton->SetVisible(true);
	pButton->EventClicked.Connect(&SlotOnDragDropTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Test drag&drop functionality\"");

	// Add button for 'Tabs&Menu Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Tabs&Menu Test");
	pButton->SetVisible(true);
	pButton->EventClicked.Connect(&SlotOnTabsAndMenuTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Test tabs and menus\"");

	// Add button for 'Slim Widgets Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Slim Widgets Test");
	pButton->SetVisible(true);
	pButton->EventClicked.Connect(&SlotOnSlimTest);
	pButton->AddModifier("PLGui::ModTooltip", "Tooltip=\"Test slim widgets\"");

	// Add button for 'Theme Test'
	pButton = new Button(GetContentWidget());
	pButton->SetText("Theme Test");
	pButton->SetVisible(true);
	pButton->EventClicked.Connect(&SlotOnThemeTest);
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
//[ Protected virtual WidgetFunctions functions           ]
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
	// Toggle main window visiblity
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
