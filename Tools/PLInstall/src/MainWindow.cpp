/*********************************************************\
 *  File: MainWindow.cpp                                       *
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


//#include <windows.h>
//#include <stdio.h>
#include <PixelLight.h>
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) 
{
	wnd_main_ui.setupUi(this);
	
	//init text and labels
	initTextAndLabels();
	//init buttons
	initButtons();

	//set default checkbox values
	

	//reset progressbar
	setProgressBar(0);


	//pack gui
	adjustSize();

	//set fixed size for qdialog
	setFixedSize(frameSize().width(),frameSize().height());

	show();

}

MainWindow::~MainWindow()
{
	
}

void MainWindow::initButtons()
{
	//setup button text "run"
	wnd_main_ui.btn_run->setText("Run");

	//setup button text "close"
	wnd_main_ui.btn_close->setText("Close");

	//QObject::connect(wnd_main->btn_run,SIGNAL(clicked()),this,SLOT(runEvent()));
}

void MainWindow::initTextAndLabels() 
{
	//setup checkbox "install" text
	wnd_main_ui.chk_checkInstallation->setText("Install PixelLight Runtime Path");
	//setup checkbox "install" description
	wnd_main_ui.lbl_install->setText("This is the installation checkbox description");;

	//setup checkbox "check installation"
	wnd_main_ui.chk_install->setText("Check PixelLight Runtime Path");
	//setup checkbox "check installation" description
	wnd_main_ui.lbl_checkInstallation->setText("This is the pathcheck ckeckbox description");

	//setup installer description
	wnd_main_ui.lbl_description->setText("This is the general pixellight installer description ... ");


}

void MainWindow::setDefaultCheckboxValues()
{
}

void MainWindow::setProgressBar(int value)
{
	wnd_main_ui.progB_progress->setValue(value);
}