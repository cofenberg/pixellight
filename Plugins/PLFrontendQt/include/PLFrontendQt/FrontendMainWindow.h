/*********************************************************\
 *  File: FrontendMainWindow.h                           *
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


#ifndef __PLFRONTENDQT_FRONTENDMAINWINDOW_H__
#define __PLFRONTENDQT_FRONTENDMAINWINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>	// For "override"
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4127)	// "warning C4127: conditional expression is constant"
	#include <QtGui/qmainwindow.h>
PL_WARNING_POP
#include "PLFrontendQt/PLFrontendQt.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Frontend;
class DockWidgetManager;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Qt frontend main window
*/
class FrontendMainWindow : public QMainWindow {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Frontend;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the dock widget manager of this main window
		*
		*  @return
		*    The dock widget manager of this main window
		*/
		PLFRONTENDQT_API DockWidgetManager &GetDockWidgetManager();
		virtual bool eventFilter(QObject *pQObject, QEvent *pQEvent);

		/**
		*  @brief
		*    Sets the update interval
		*
		*  @param[in] nUpdateInterval
		*    Update interval in milliseconds, "0" to disable updates
		*
		*  @note
		*    - By default an update interval of 10 milliseconds resulting in 100 FPS is set
		*/
		PLFRONTENDQT_API void SetUpdateInterval(int nUpdateInterval = 100);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFrontendQt
		*    Owner frontend implementation
		*/
		FrontendMainWindow(Frontend &cFrontendQt);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~FrontendMainWindow();

		/**
		*  @brief
		*    If the widget is not visible yet, make it visible right now
		*/
		void MakeVisible();


	//[-------------------------------------------------------]
	//[ Protected virtual QObject functions                   ]
	//[-------------------------------------------------------]
	protected:
		virtual void timerEvent(QTimerEvent *pQTimerEvent) override;


	//[-------------------------------------------------------]
	//[ Protected virtual QWidget functions                   ]
	//[-------------------------------------------------------]
	protected:
		virtual void keyPressEvent(QKeyEvent *) override;
		virtual void focusInEvent(QFocusEvent *) override;
		virtual void focusOutEvent(QFocusEvent *) override;
		virtual void paintEvent(QPaintEvent *) override;
		virtual void resizeEvent(QResizeEvent *) override;
		virtual void dragEnterEvent(QDragEnterEvent *) override;
		virtual void dropEvent(QDropEvent *) override;
		#if defined(Q_WS_WIN)
			virtual bool winEvent(MSG *message, long *result) override;
		#endif
		#if defined(Q_WS_X11)
			virtual bool x11Event(XEvent *);
		#endif


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Frontend		  *m_pFrontendQt;			/**< Owner frontend implementation, always valid! */
		bool			   m_bVisible;				/**< Was the widget made visible? (independent of the real Qt widget visibility state) */
		int				   m_nUpdateInterval;		/**< Update interval in milliseconds */
		int				   m_nUpdateTimerID;		/**< Update timer ID, "0" means no timer */
		DockWidgetManager *m_pDockWidgetManager;	/**< Dock widget manager of this main window, can be a null pointer */
		bool			   m_bInitialized;			/**< Is the frontend already initialized? */
		QWidget			  *m_pRenderWidget;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_FRONTENDMAINWINDOW_H__
