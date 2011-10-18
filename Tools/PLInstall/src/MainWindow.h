/*********************************************************\
 *  File: MainWindow.h                                       *
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QDialog.h>
#include "ui_MainWindow.h"

//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class InstallerFunctions;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    [TODO] write a description
*
*  @note
*    [TODO] write node
*/
class MainWindow : QDialog
{	
	
	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")
	
	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:

		MainWindow(QWidget *parent = 0);
		~MainWindow();
		
		void updateProgress(int value);
	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]	
	private:
		void initButtons();
		void initTextAndLabels();

		void setDefaultCheckboxValues();

	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Ui::MainWindow wnd_main_ui;
		InstallerFunctions *m_pInstallerFunctions;
		bool m_bIsRunning;
		
	//[-------------------------------------------------------]
	//[ public qt slots                                      ]
	//[-------------------------------------------------------]
	public slots:
	
	//[-------------------------------------------------------]
	//[ Private qt slots                                      ]
	//[-------------------------------------------------------]
	private slots:
		void runEvent();
		void cancelEvent();


};

#endif // MAINWINDOW_H