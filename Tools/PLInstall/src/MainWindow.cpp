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


#include "InstallerFunctions.h"
#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
	m_pInstallerFunctions(new InstallerFunctions()),
	m_bIsRunning(false)
{
	//connect event for progress updates
	m_pProgressEventHandler = new PLCore::EventHandler<int> (&MainWindow::onUpdateProgress, this);
	m_pInstallerFunctions->connectProgressEventHandler(m_pProgressEventHandler);

	wnd_main_ui.setupUi(this);
	
	//init text and labels
	initTextAndLabels();
	//init buttons
	initButtons();

	//pack gui
	adjustSize();

	//set fixed size for qdialog
	setFixedSize(frameSize().width(),frameSize().height());

	show();

}

MainWindow::~MainWindow()
{
	if(m_pInstallerFunctions)
		delete m_pInstallerFunctions;
}

void MainWindow::initButtons()
{
	//setup button text "run"
	wnd_main_ui.btn_run->setText("Run");

	//setup button text "cancel"
	wnd_main_ui.btn_cancel->setText("Cancel");
	wnd_main_ui.btn_cancel->setEnabled(false);

	//setup button text "close"
	wnd_main_ui.btn_close->setText("Close");

	//set default checkbox values 
	setDefaultCheckboxValues();
	
	//connect button slots
	QObject::connect(wnd_main_ui.btn_run,SIGNAL(clicked()),this,SLOT(runEvent()));
	QObject::connect(wnd_main_ui.btn_cancel,SIGNAL(clicked()),this,SLOT(cancelEvent()));
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
	//Enable checkboxes on startup. The default process will install PL and check the installation.
	wnd_main_ui.chk_install->setChecked(true);
	wnd_main_ui.chk_checkInstallation->setChecked(true);
}

void MainWindow::onUpdateProgress(int value)
{
	value = wnd_main_ui.progB_progress->value() + value;
	wnd_main_ui.progB_progress->setValue(value);
}
	
void MainWindow::runEvent()
{
	if(!m_bIsRunning) {


		//toggle isRunning flag
		m_bIsRunning = true;

		//lock the checkboxes and change buttons
		wnd_main_ui.btn_run->setEnabled(false);
		wnd_main_ui.btn_cancel->setEnabled(true);
		
		wnd_main_ui.chk_install->setEnabled(false);
		wnd_main_ui.chk_checkInstallation->setEnabled(false);

		bool install = wnd_main_ui.chk_install->isChecked();
		bool check = wnd_main_ui.chk_checkInstallation->isChecked();

		//calculate overall progress steps
	
		//[TODO] invoce installation and/or check
	}
}


void MainWindow::cancelEvent()
{
	if(m_bIsRunning) {
		//[TODO] cancel progress



		m_bIsRunning = false;
		//enable checkboxes
		wnd_main_ui.chk_install->setEnabled(true);
		wnd_main_ui.chk_checkInstallation->setEnabled(true);

		//reset change button text
		wnd_main_ui.btn_run->setEnabled(true);
		wnd_main_ui.btn_cancel->setEnabled(false);

	}
}