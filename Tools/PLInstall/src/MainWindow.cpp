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

#include <QtGui/QMessageBox>
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
	// cleanup
	if(m_pInstallerFunctions)
		delete m_pInstallerFunctions;

	if(m_pProgressEventHandler)
		delete m_pProgressEventHandler;
}

void MainWindow::initButtons()
{
	//disable cancel button
	wnd_main_ui.btn_cancel->setEnabled(false);
		
	//connect button slots
	QObject::connect(wnd_main_ui.btn_cancel,SIGNAL(clicked()),this,SLOT(cancelEvent()));
	QObject::connect(wnd_main_ui.btn_install,SIGNAL(clicked()),this,SLOT(intallPLRuntimeEvent()));
	QObject::connect(wnd_main_ui.btn_checkInstallation,SIGNAL(clicked()),this,SLOT(checkInstallationEvent()));
}

void MainWindow::initTextAndLabels() 
{
	//setup button "install" text
	wnd_main_ui.btn_install->setText(QString(" Install PixelLight Runtime Path "));
	QFont font = wnd_main_ui.btn_install->font();
	font.setBold(true);
	wnd_main_ui.btn_install->setFont(font);
	//setup button "install" description
	wnd_main_ui.lbl_install->setText("\n\nThis is the installation checkbox description");

	//setup button "check installation"
	wnd_main_ui.btn_checkInstallation->setText(" Check PixelLight Runtime Path ");
	wnd_main_ui.btn_checkInstallation->setFont(font);

	//setup button "check installation" description
	wnd_main_ui.lbl_checkInstallation->setText("\n\nThis is the pathcheck ckeckbox description");
	
	//setup installer description
	wnd_main_ui.lbl_description->setText("<br>"\
		"PixelLight Installer will set all needed variables for the Pixellight Runtime.<br>"\
		"<br>"\
		"Hompage: <a href='http://www.pixellight.org'>www.pixellight.org</a><br>"\
		"Forum: <a href='http://dev.pixellight.org/forum/'>dev.pixellight.org/forum/</a><br>"\
		"<br>"\
		"PixelLight is released under the terms of the <a href='http://pixellight.org/site/index.php/page/11.html'> GNU Lesser General Public License</a>.");
	
	//setup button text "cancel"
	wnd_main_ui.btn_cancel->setText("Cancel");
	//setup button text "close"
	wnd_main_ui.btn_close->setText("Close");

}

bool MainWindow::runStart() 
{
	if(!m_bIsRunning)
	{
		m_bIsRunning = true;
		toggleButtons();
		
		//reset progress bar 
		wnd_main_ui.progB_progress->setValue(0);
		m_installationProgressPrecentage = 0;

	} else {
		//Error -> allready a running task
		//this can't happen
	}

	return m_bIsRunning;
}

void MainWindow::runComplete()
{
	if(m_bIsRunning)
	{
		m_bIsRunning = false;
		toggleButtons();
	}
}

void MainWindow::onUpdateProgress(int value)
{
	m_installationProgressPrecentage = m_installationProgressPrecentage + (m_installationProgressStepPercentage * value);
	wnd_main_ui.progB_progress->setValue(m_installationProgressPrecentage);

	if(m_installationProgressPrecentage >= 100.0)
		runComplete();
}

void MainWindow::showDialog(PLCore::String msg)
{
	QMessageBox msgBox;
	QString text = msg.GetASCII();
	//text.append(msg.GetASCII());
	msgBox.setText(text);
	msgBox.exec();
}

void MainWindow::toggleButtons()
{
	wnd_main_ui.btn_cancel->setEnabled(m_bIsRunning);
		
	wnd_main_ui.btn_install->setEnabled(!m_bIsRunning);
	wnd_main_ui.btn_checkInstallation->setEnabled(!m_bIsRunning);
}

void MainWindow::cancelEvent()
{
	if(m_bIsRunning) {
		//[TODO] cancel progress

		runComplete();
	}
}


void MainWindow::intallPLRuntimeEvent() 
{
	if(runStart()) {
		//get the installation steps 
		int installationProcessSteps = m_pInstallerFunctions->getInstallRuntimeProgressSteps();
	
		//calculate progress bar steps
		m_installationProgressStepPercentage = 100.0 / (double) installationProcessSteps;

		bool retInstallation = false;
		retInstallation = m_pInstallerFunctions->installRuntime();
		if(!retInstallation)
			showDialog(m_pInstallerFunctions->getLastErrorDescription());
		else
			showDialog(m_pInstallerFunctions->getLastSuccessMessage());

		runComplete();
	} else {
		//this should not happen
	}
}

void MainWindow::checkInstallationEvent()
{
	if(runStart()) {
		
		//get the installation steps 
		int checkInstallationProcessSteps = m_pInstallerFunctions->getCheckRuntimeProgressSteps();
	
		//calculate progress bar steps
		m_installationProgressStepPercentage = 100.0 / (double) checkInstallationProcessSteps;

		bool retCheckInstallation = false;
		retCheckInstallation = m_pInstallerFunctions->checkRuntimeInstallation();
		if(!retCheckInstallation)
			showDialog(m_pInstallerFunctions->getLastErrorDescription());
		else
			showDialog(m_pInstallerFunctions->getLastSuccessMessage());

		runComplete();
	} else {
		//This should never happen	
	}
}