/*********************************************************\
 *  File: MainWindow.cpp                                 *
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
#include <QtGui/QMessageBox>
#include <PLFrontendQt/QtStringAdapter.h>
#include "InstallerFunctions.h"
#include "MainWindow.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
MainWindow::MainWindow() :
	m_pInstallerFunctions(new InstallerFunctions()),
	m_bIsRunning(false)
{
	// Connect event for progress updates
	m_pProgressEventHandler = new EventHandler<int>(&MainWindow::OnUpdateProgress, this);
	m_pInstallerFunctions->ConnectProgressEventHandler(m_pProgressEventHandler);

	// Setup the UI
	wnd_main_ui.setupUi(this);

	// Initialize text and labels
	InitTextAndLabels();

	// Initialize buttons
	InitButtons();

	// Pack GUI
	adjustSize();

	// Set fixed size for the dialog
	setFixedSize(frameSize().width(), frameSize().height());

	show();
}

MainWindow::~MainWindow()
{
	// Cleanup
	delete m_pInstallerFunctions;
	if (m_pProgressEventHandler)
		delete m_pProgressEventHandler;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
void MainWindow::InitButtons()
{
	// Disable cancel button
	wnd_main_ui.btn_cancel->setEnabled(false);

	// Connect button slots
	QObject::connect(wnd_main_ui.btn_cancel,			SIGNAL(clicked()), this, SLOT(cancelEvent()));
	QObject::connect(wnd_main_ui.btn_install,			SIGNAL(clicked()), this, SLOT(intallPLRuntimeEvent()));
	QObject::connect(wnd_main_ui.btn_checkInstallation,	SIGNAL(clicked()), this, SLOT(checkInstallationEvent()));
}

void MainWindow::InitTextAndLabels()
{
	QFont cQFont = wnd_main_ui.btn_install->font();
	cQFont.setBold(true);

	// Setup button "install" text
	wnd_main_ui.btn_install->setText(" Install PixelLight Runtime Path ");
	wnd_main_ui.btn_install->setFont(cQFont);

	// Setup button "install" description
	wnd_main_ui.lbl_install->setText("\n\nThis is the installation checkbox description");

	// Setup button "check installation"
	wnd_main_ui.btn_checkInstallation->setText(" Check PixelLight Runtime Path ");
	wnd_main_ui.btn_checkInstallation->setFont(cQFont);

	// Setup button "check installation" description
	wnd_main_ui.lbl_checkInstallation->setText("\n\nThis is the pathcheck ckeckbox description");

	// Setup installer description
	wnd_main_ui.lbl_description->setText("<br>"\
		"PixelLight Installer will set all needed variables for the PixelLight Runtime.<br>"\
		"<br>"\
		"Homepage: <a href='http://www.pixellight.org'>www.pixellight.org</a><br>"\
		"Forum: <a href='http://dev.pixellight.org/forum/'>dev.pixellight.org/forum/</a><br>"\
		"<br>"\
		"PixelLight is released under the terms of the <a href='http://pixellight.org/site/index.php/page/11.html'> GNU Lesser General Public License</a>.");

	// Setup button text "cancel"
	wnd_main_ui.btn_cancel->setText("Cancel");

	// Setup button text "close"
	wnd_main_ui.btn_close->setText("Close");
}

bool MainWindow::RunStart()
{
	if (m_bIsRunning) {
		// Error -> already a running task, this can't happen
	} else {
		m_bIsRunning = true;
		ToggleButtons();

		// Reset progress bar
		wnd_main_ui.progB_progress->setValue(0);
		m_fInstallationProgressPrecentage = 0.0f;
	}

	return m_bIsRunning;
}

void MainWindow::RunComplete()
{
	if (m_bIsRunning) {
		m_bIsRunning = false;
		ToggleButtons();
	}
}

void MainWindow::OnUpdateProgress(int nValue)
{
	m_fInstallationProgressPrecentage = m_fInstallationProgressPrecentage + (m_fInstallationProgressStepPercentage * nValue);
	wnd_main_ui.progB_progress->setValue(m_fInstallationProgressPrecentage);

	if (m_fInstallationProgressPrecentage >= 100.0f)
		RunComplete();
}

void MainWindow::ShowDialog(const String &sMessage) const
{
	QMessageBox cQMessageBox;
	cQMessageBox.setText(PLFrontendQt::QtStringAdapter::PLToQt(sMessage));
	cQMessageBox.exec();
}

void MainWindow::ToggleButtons()
{
	wnd_main_ui.btn_cancel->setEnabled(m_bIsRunning);
	wnd_main_ui.btn_install->setEnabled(!m_bIsRunning);
	wnd_main_ui.btn_checkInstallation->setEnabled(!m_bIsRunning);
}


//[-------------------------------------------------------]
//[ Private Qt slots                                      ]
//[-------------------------------------------------------]
void MainWindow::cancelEvent()
{
	if (m_bIsRunning) {
		// [TODO] Cancel progress
		RunComplete();
	}
}

void MainWindow::intallPLRuntimeEvent()
{
	if (RunStart()) {
		// Get the number of installation steps
		const int nInstallationProcessSteps = m_pInstallerFunctions->GetInstallRuntimeProgressSteps();

		// Calculate progress bar steps
		m_fInstallationProgressStepPercentage = 100.0f / static_cast<float>(nInstallationProcessSteps);

		ShowDialog(m_pInstallerFunctions->InstallRuntime() ? m_pInstallerFunctions->GetLastSuccessMessage() : m_pInstallerFunctions->GetLastErrorDescription());

		RunComplete();
	} else {
		// This should not happen
	}
}

void MainWindow::checkInstallationEvent()
{
	if (RunStart()) {
		// Get the number of installation steps
		const int nCheckInstallationProcessSteps = m_pInstallerFunctions->GetCheckRuntimeProgressSteps();

		// Calculate progress bar steps
		m_fInstallationProgressStepPercentage = 100.0f / static_cast<float>(nCheckInstallationProcessSteps);

		ShowDialog(m_pInstallerFunctions->CheckRuntimeInstallation() ? m_pInstallerFunctions->GetLastSuccessMessage() : m_pInstallerFunctions->GetLastErrorDescription());

		RunComplete();
	} else {
		// This should never happen
	}
}
