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
	//disable cancel button
	wnd_main_ui.btn_cancel->setEnabled(false);

	//set default checkbox values 
	setDefaultCheckboxValues();
	
	//connect button slots
	QObject::connect(wnd_main_ui.btn_run,SIGNAL(clicked()),this,SLOT(runEvent()));
	QObject::connect(wnd_main_ui.btn_cancel,SIGNAL(clicked()),this,SLOT(cancelEvent()));
}

void MainWindow::initTextAndLabels() 
{
	//setup checkbox "install" text
	wnd_main_ui.chk_checkInstallation->setText("<b>Install PixelLight Runtime Path</b>");
	//setup checkbox "install" description
	wnd_main_ui.lbl_install->setText("This is the installation checkbox description");;

	//setup checkbox "check installation"
	wnd_main_ui.chk_install->setText("<b>Check PixelLight Runtime Path</b>");
	//setup checkbox "check installation" description
	wnd_main_ui.lbl_checkInstallation->setText("This is the pathcheck ckeckbox description");
	
	//setup installer description
	wnd_main_ui.lbl_description->setText("<br>"\
		"PixelLight Installer will set all needed variables for the Pixellight Runtime.<br>"\
		"<br>"\
		"Hompage: <a href='http://www.pixellight.org'>www.pixellight.org</a><br>"\
		"Forum: <a href='http://dev.pixellight.org/forum/'>dev.pixellight.org/forum/</a><br>"\
		"<br>"\
		"PixelLight is released under the terms of the <a href='http://pixellight.org/site/index.php/page/11.html'> GNU Lesser General Public License</a>.");
	
	//setup button text "run"
	wnd_main_ui.btn_run->setText("Run");
	//setup button text "cancel"
	wnd_main_ui.btn_cancel->setText("Cancel");
	//setup button text "close"
	wnd_main_ui.btn_close->setText("Close");

}

void MainWindow::setDefaultCheckboxValues()
{	
	//Enable checkboxes on startup. The default process will install PL and check the installation.
	wnd_main_ui.chk_install->setChecked(true);
	wnd_main_ui.chk_checkInstallation->setChecked(true);
}

void MainWindow::runComplete()
{
		m_bIsRunning = false;
		//enable checkboxes
		wnd_main_ui.chk_install->setEnabled(true);
		wnd_main_ui.chk_checkInstallation->setEnabled(true);

		//reset buttons
		wnd_main_ui.btn_run->setEnabled(true);
		wnd_main_ui.btn_cancel->setEnabled(false);

}

void MainWindow::onUpdateProgress(int value)
{
	m_installationProgressPrecentage = m_installationProgressPrecentage + m_installationProgressStepPercentage;
	wnd_main_ui.progB_progress->setValue(m_installationProgressPrecentage);

	if(m_installationProgressPrecentage >= 100.0)
		runComplete();
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

		//reset progress bar 
		wnd_main_ui.progB_progress->setValue(0);
		m_installationProgressPrecentage = 0;

		bool install = wnd_main_ui.chk_install->isChecked();
		bool check = wnd_main_ui.chk_checkInstallation->isChecked();

		int installationProcessSteps = 0;

		//calculate overall progress steps
		if(install) {
			installationProcessSteps += m_pInstallerFunctions->getInstallRuntimeProgressSteps();
		}

		if(check) {
			installationProcessSteps += m_pInstallerFunctions->getCheckRuntimeProgressSteps();
		}

		m_installationProgressStepPercentage = 100.0 / (double) installationProcessSteps;

		//[TODO] invoce installation and/or check
		if(install) {
			m_pInstallerFunctions->installRuntime();
		}

		if(check) {
			m_pInstallerFunctions->checkRuntimeInstallation();
		}
	}
}


void MainWindow::cancelEvent()
{
	if(m_bIsRunning) {
		//[TODO] cancel progress

		runComplete();
	}
}