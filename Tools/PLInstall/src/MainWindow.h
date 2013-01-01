/*********************************************************\
 *  File: MainWindow.h                                   *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
