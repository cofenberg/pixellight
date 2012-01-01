/*********************************************************\
 *  File: Gui.h                                          *
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


#ifndef __PLVIEWERQT_GUI_H__
#define __PLVIEWERQT_GUI_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtCore/qobject.h>
#include <PLCore/Base/Event/EventHandler.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
class QMenu;
class QLabel;
class QAction;
class QMainWindow;
class QActionGroup;
QT_END_NAMESPACE
namespace PLScene {
	class SceneNode;
	class SceneQuery;
}
namespace PLFrontendQt {
	class FrontendMainWindow;
}
class Application;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Gui class
*/
class Gui : public QObject {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cApplication
		*    Owner application
		*/
		Gui(Application &cApplication);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Gui();

		/**
		*  @brief
		*    Get frontend main window
		*
		*  @return
		*    Frontend main window, can be a null pointer
		*/
		PLFrontendQt::FrontendMainWindow *GetFrontendMainWindow() const;

		/**
		*  @brief
		*    Sets the state text
		*
		*  @param[in] sText
		*    State text
		*/
		void SetStateText(const PLCore::String &sText);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Initializes the main window
		*
		*  @param[in] cQMainWindow
		*    Main window to initialize
		*/
		void InitMainWindow(QMainWindow &cQMainWindow);

		/**
		*  @brief
		*    Called when a camera scene node was found
		*
		*  @param[in] cQuery
		*    Query found the scene node
		*  @param[in] cSceneNode
		*    Found scene node
		*/
		void OnCameraFound(PLScene::SceneQuery &cQuery, PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Fills the window menu recursivity
		*
		*  @param[in] cQMenu
		*    Current Qt menu to fill
		*  @param[in] sBaseClass
		*    Name of the currently used RTTI base class
		*/
		void FillMenuWindowRec(QMenu &cQMenu, const PLCore::String &sBaseClass);


	//[-------------------------------------------------------]
	//[ Private Qt slots (MOC)                                ]
	//[-------------------------------------------------------]
	private slots:
		void QtSlotLoad();
		void QtSlotExit();
		void QtSlotMenuCameraAboutToShow();
		void QtSlotSelectedCamera(QAction *);
		void QtSlotMenuWindowAboutToShow();
		void QtSlotSelectedWindow(QAction *);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<PLScene::SceneQuery &, PLScene::SceneNode &> EventHandlerCameraFound;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Application	 *m_pApplication;			/**< Owner application, always valid */
		// Menu bar
		QMenu		 *m_pQMenuCamera;			/**< Camera Qt menu, can be a null pointer */
		QActionGroup *m_pQActionGroupCamera;	/**< Camera Qt action group, can be a null pointer */
		QMenu		 *m_pQMenuWindow;			/**< Window Qt menu, can be a null pointer */
		QActionGroup *m_pQActionGroupWindow;	/**< Window Qt action group, can be a null pointer */
		// Status bar
		QLabel		 *m_pQLabelStatusBar;		/**< Qt label shown in the status bar of the Qt main window, can be a null pointer */


};


#endif // __PLVIEWERQT_GUI_H__
