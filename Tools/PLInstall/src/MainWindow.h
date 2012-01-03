/*********************************************************\
 *  File: MainWindow.h                                   *
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


#ifndef __PLINSTALL_MAINWINDOW_H__
#define __PLINSTALL_MAINWINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtGui/QDialog.h>
#include <PLCore/Base/Event/EventHandler.h>
#include "ui_MainWindow.h"	// Automatically created by Qt's uic (output directory is "build/GeneratedQtFiles" within the hand configured Visual Studio files, another directory when using CMake)


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class InstallerFunctions;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Main window
*/
class MainWindow : public QDialog {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Public Qt slots                                       ]
	//[-------------------------------------------------------]
	public slots:


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		MainWindow();
		virtual ~MainWindow();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		void InitButtons();
		void InitTextAndLabels();
		bool RunStart();
		void RunComplete();
		void OnUpdateProgress(int nValue);
		void ShowDialog(const PLCore::String &sMessage) const;
		void ToggleButtons();


	//[-------------------------------------------------------]
	//[ Private Qt slots                                      ]
	//[-------------------------------------------------------]
	private slots:
		void cancelEvent();
		void intallPLRuntimeEvent();
		void checkInstallationEvent();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Ui::MainWindow				 wnd_main_ui;
		InstallerFunctions			*m_pInstallerFunctions;	/**< Installer functions, always valid! */
		PLCore::EventHandler<int>	*m_pProgressEventHandler;
		bool						 m_bIsRunning;
		float						 m_fInstallationProgressStepPercentage;
		float						 m_fInstallationProgressPrecentage;


};


#endif // __PLINSTALL_MAINWINDOW_H__
