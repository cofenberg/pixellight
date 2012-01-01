/*********************************************************\
 *  File: TestWindow.cpp                                 *
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
#include <PLCore/System/System.h>
#include <PLCore/System/Console.h>
#include <PLGui/Gui/Gui.h>
#include <PLGui/Gui/Data/ButtonGroup.h>
#include <PLGui/Gui/Resources/Menu.h>
#include <PLGui/Widgets/Widget.h>
#include <PLGui/Widgets/Controls/Label.h>
#include <PLGui/Widgets/Controls/Button.h>
#include <PLGui/Widgets/Controls/ToggleButton.h>
#include <PLGui/Widgets/Controls/CheckBox.h>
#include <PLGui/Widgets/Controls/RadioButton.h>
#include <PLGui/Widgets/Controls/BitmapButton.h>
#include <PLGui/Widgets/Controls/BitmapToggleButton.h>
#include <PLGui/Widgets/Controls/MenuBar.h>
//#include <PLGui/Widgets/Controls/TabBar.h>
#include <PLGui/Widgets/Popups/PopupMenu.h>
#include "TestWindow.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLGui;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TestWindow::TestWindow(Widget *pParent) : Window(pParent),
	EventHandlerTrayClicked(&TestWindow::TrayClicked, this),
	EventHandlerClicked(&TestWindow::ButtonClicked, this),
	EventHandlerPressed(&TestWindow::ButtonPressed, this),
	EventHandlerReleased(&TestWindow::ButtonReleased, this),
	EventHandlerMenu(&TestWindow::MenuClicked, this),
	m_pLabel(nullptr),
	m_pButton(nullptr),
	m_pToggleButton(nullptr),
	m_pClickTest(nullptr),
	m_pPressedTest(nullptr),
	m_pBitmapButton(nullptr),
	m_pBitmapToggleButton(nullptr),
	m_cMenu(*GetGui()),
	m_pMenuBar(nullptr),
//	m_pTabBar(nullptr),
	m_pPopupMenu(nullptr),
	m_cTrayIcon(*GetGui()),
	m_bClicked(false)
{
	// Create a tray icon
	m_cTrayIcon.SetTooltip(L"Hallo!!");
	m_cTrayIcon.SetIcon(Image(*Gui::GetSystemGui()));
	m_cTrayIcon.EventMouseButtonDown.Connect(EventHandlerTrayClicked);

	// Create some widgets
	m_pLabel = new Label(GetContentWidget());
		m_pLabel->SetText("Hallo!");
		m_pLabel->SetPos(Vector2i(10, 30));
		m_pLabel->SetSize(Vector2i(200, 32));
		m_pLabel->SetVisible(true);
	m_pButton = new Button(GetContentWidget());
		m_pButton->SetImage(Image(*Gui::GetSystemGui(), "PLGui/copy.png"));
		m_pButton->SetText("Button");
		m_pButton->SetPos(Vector2i(10, 70));
		m_pButton->SetSize(Vector2i(120, 32));
		m_pButton->SetVisible(true);
		m_pButton->SetRepeat(true);
		m_pButton->SetRepeatDelay(1000);
		m_pButton->SetRepeatInterval(250);
	m_pToggleButton = new ToggleButton(GetContentWidget());
		m_pToggleButton->SetText("Toggle");
		m_pToggleButton->SetPos(Vector2i(10, 110));
		m_pToggleButton->SetSize(Vector2i(120, 32));
		m_pToggleButton->SetVisible(true);
	m_cCheckGroup.SetExclusive(false);
	for (int i=0; i<4; i++) {
		m_pCheckBoxes[i] = new CheckBox(GetContentWidget());
			m_pCheckBoxes[i]->SetGroup(&m_cCheckGroup);
			m_pCheckBoxes[i]->SetPartiallyAllowed(true);
			m_pCheckBoxes[i]->SetState(PartiallyChecked);
			m_pCheckBoxes[i]->SetText(String("Check Box ") + i);
			m_pCheckBoxes[i]->SetPos(Vector2i(10, 150 + i*20));
			m_pCheckBoxes[i]->SetSize(Vector2i(100, 20));
			m_pCheckBoxes[i]->SetVisible(true);
		m_pRadioButtons[i] = new RadioButton(GetContentWidget());
			m_pRadioButtons[i]->SetGroup(&m_cRadioGroup);
			m_pRadioButtons[i]->SetState(Checked);
			m_pRadioButtons[i]->SetText(String("Radio Button ") + i);
			m_pRadioButtons[i]->SetPos(Vector2i(150, 150 + i*20));
			m_pRadioButtons[i]->SetSize(Vector2i(100, 20));
			m_pRadioButtons[i]->SetVisible(true);
	}

	m_pClickTest = new Widget(GetContentWidget());
		m_pClickTest->SetBackgroundColor(Color4::Red);
		m_pClickTest->SetPos(Vector2i(150, 70));
		m_pClickTest->SetSize(Vector2i(32, 32));
		m_pClickTest->SetVisible(true);
	m_pPressedTest = new Widget(GetContentWidget());
		m_pPressedTest->SetBackgroundColor(Color4::Blue);
		m_pPressedTest->SetPos(Vector2i(200, 70));
		m_pPressedTest->SetSize(Vector2i(32, 32));
		m_pPressedTest->SetVisible(true);
	m_pBitmapButton = new BitmapButton(GetContentWidget());
		m_pBitmapButton->SetImageEnabled (Image(*Gui::GetSystemGui(), "PLGui/button.png"));
		m_pBitmapButton->SetImageDisabled(Image(*Gui::GetSystemGui(), "PLGui/button-inactive.png"));
		m_pBitmapButton->SetImageSelected(Image(*Gui::GetSystemGui(), "PLGui/button-over.png"));
		m_pBitmapButton->SetImagePressed (Image(*Gui::GetSystemGui(), "PLGui/button-pressed.png"));
		m_pBitmapButton->SetPos(Vector2i(10, 230));
		m_pBitmapButton->SetSize(Vector2i(64, 64));
		m_pBitmapButton->SetVisible(true);
	m_pBitmapToggleButton = new BitmapToggleButton(GetContentWidget());
		m_pBitmapToggleButton->SetImageDisabled  (Image(*Gui::GetSystemGui(), "PLGui/button-inactive.png"));
		m_pBitmapToggleButton->SetImageUnselected(NotChecked,		Image(*Gui::GetSystemGui(), "PLGui/button-off.png"));
		m_pBitmapToggleButton->SetImageUnselected(PartiallyChecked,	Image(*Gui::GetSystemGui(), "PLGui/button-on.png"));
		m_pBitmapToggleButton->SetImageUnselected(Checked,			Image(*Gui::GetSystemGui(), "PLGui/button-on.png"));
		m_pBitmapToggleButton->SetImageSelected  (NotChecked,		Image(*Gui::GetSystemGui(), "PLGui/button-over-off.png"));
		m_pBitmapToggleButton->SetImageSelected  (PartiallyChecked,	Image(*Gui::GetSystemGui(), "PLGui/button-over-on.png"));
		m_pBitmapToggleButton->SetImageSelected  (Checked,			Image(*Gui::GetSystemGui(), "PLGui/button-over-on.png"));
		m_pBitmapToggleButton->SetPos(Vector2i(10, 300));
		m_pBitmapToggleButton->SetSize(Vector2i(64, 64));
		m_pBitmapToggleButton->SetVisible(true);

	// Connect event handlers to button
	m_pButton->SignalClicked .Connect(EventHandlerClicked);
	m_pButton->SignalPressed .Connect(EventHandlerPressed);
	m_pButton->SignalReleased.Connect(EventHandlerReleased);

	// Create menu
	Menu *pMenuFile = new Menu(*GetGui());
		pMenuFile->SetText("&File");
		pMenuFile->AddItem("&Open");
		pMenuFile->AddItem("&Close");
		pMenuFile->AddSeparator();
		pMenuFile->AddItem("&Quit");
	Menu *pMenuEdit = new Menu(*GetGui());
		pMenuEdit->SetText("&Edit");
		pMenuEdit->AddItem("&Copy");
		pMenuEdit->AddItem("Cu&t");
		pMenuEdit->AddItem("&Paste");
	Menu *pMenuView = new Menu(*GetGui());
		pMenuView->SetText("&View");
		pMenuView->AddItem("View &All");
		pMenuView->AddItem("View &None");
	Menu *pMenuWindow = new Menu(*GetGui());
		pMenuWindow->SetText("&Window");
		pMenuWindow->AddItem("&Next");
		pMenuWindow->AddItem("&Previous");
		pMenuWindow->AddItem("&Close");
		pMenuWindow->AddItem( "Close &All");
	Menu *pMenuHelp = new Menu(*GetGui());
		pMenuHelp->SetText("&Help");
		pMenuHelp->AddItem("&Help");
		pMenuHelp->AddItem("&About");
	m_cMenu.SetText("&Menu");
	m_cMenu.AddSubMenu(pMenuFile);
	m_cMenu.AddSubMenu(pMenuEdit);
	m_cMenu.AddSubMenu(pMenuView);
	m_cMenu.AddSubMenu(pMenuWindow);
	m_cMenu.AddSubMenu(pMenuHelp);
	m_cMenu.AddSeparator();
	m_cMenu.AddItem("&Restore");
	m_cMenu.AddSeparator();

	// Add a menu bar
	m_pMenuBar = new MenuBar(GetContentWidget());
//		m_pMenuBar->SetSubmenuOrientationVert(Up);
		m_pMenuBar->SetMenu(&m_cMenu);
		m_pMenuBar->SetPos(Vector2i::Zero);
//		m_pMenuBar->SetSize(Vector2i(GetContentWidget()->GetSize().x, 26));
		m_pMenuBar->SetSize(Vector2i(640, 26));
		m_pMenuBar->SetVisible(true);

	// Add a tab bar
	/*
	m_pTabBar = new TabBar(GetContentWidget());
		m_pTabBar->AddTab("Test1");
		m_pTabBar->AddTab("Test2");
		m_pTabBar->AddTab("Test3");
		m_pTabBar->AddTab("Test4");
		m_pTabBar->AddTab("Test5");
		m_pTabBar->AddTab("Test6");
		m_pTabBar->SetPos(Vector2i(0, 370));
//		m_pTabBar->SetSize(Vector2i(GetContentWidget()->GetSize().x, 20));
		m_pTabBar->SetSize(Vector2i(640, 20));
		m_pTabBar->SetVisible(true);
	*/

	// Add a popup menu
	m_pPopupMenu = new PopupMenu(GetContentWidget());
		m_pPopupMenu->SetMenu(&m_cMenu);
		m_pPopupMenu->SetPos(Vector2i(300, 70));
		m_pPopupMenu->SetSize(Vector2i(100, 200));
		m_pPopupMenu->SetVisible(true);

	// Connect event handlers to menus
	m_pMenuBar->SignalItemClicked.Connect(EventHandlerMenu);
	m_pPopupMenu->SignalItemClicked.Connect(EventHandlerMenu);
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
void TestWindow::ButtonClicked()
{
	m_bClicked = !m_bClicked;
	m_pClickTest->SetBackgroundColor(m_bClicked ? Color4::Green : Color4::Red);
	m_pClickTest->Redraw();
}

void TestWindow::ButtonPressed()
{
	m_pPressedTest->SetBackgroundColor(Color4::Yellow);
	m_pPressedTest->Redraw();
}

void TestWindow::ButtonReleased()
{
	m_pPressedTest->SetBackgroundColor(Color4::Blue);
	m_pPressedTest->Redraw();
}

void TestWindow::MenuClicked(uint32 nID)
{
	System::GetInstance()->GetConsole().Print(String::Format("Menu item '%d' clicked\n", nID));
	if (nID ==  3)
		GetGui()->Exit();
	if (nID == 20)
		m_cTrayIcon.SetVisible(true);
	if (nID == 21)
		m_cTrayIcon.SetVisible(false);
}

void TestWindow::TrayClicked(uint32 nButton, const Vector2i &vPos)
{
	// Toggle window visibility
	SetVisible(!IsVisible());
}
