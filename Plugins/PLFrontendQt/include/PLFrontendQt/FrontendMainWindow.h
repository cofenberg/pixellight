/*********************************************************\
 *  File: FrontendMainWindow.h                           *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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

		/**
		*  @brief
		*    Gets the render window which is used by this main window
		*
		*  @return
		*    The render window, assumed to be always valid (but check for null pointer if you feel more safe this way)
		*/
		PLFRONTENDQT_API QWidget *GetRenderWindow() const;


	//[-------------------------------------------------------]
	//[ Public virtual QObject methods                        ]
	//[-------------------------------------------------------]
	public:
		virtual bool eventFilter(QObject *pQObject, QEvent *pQEvent) override;


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
		virtual void paintEvent(QPaintEvent *) override;
		virtual void resizeEvent(QResizeEvent *) override;
		virtual void dragEnterEvent(QDragEnterEvent *) override;
		virtual void dropEvent(QDropEvent *) override;
		#if defined(Q_WS_WIN)
			virtual bool winEvent(MSG *message, long *result) override;
		#elif defined(Q_WS_X11)
			virtual bool x11Event(XEvent *) override;
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
		QWidget			  *m_pRenderWidget;			/**< Pointer to the render window, always valid! */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_FRONTENDMAINWINDOW_H__
