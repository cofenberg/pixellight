/*********************************************************\
 *  File: FrontendMainWindow.h                           *
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


#ifndef __PLFRONTENDQT_FRONTENDMAINWINDOW_H__
#define __PLFRONTENDQT_FRONTENDMAINWINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtGui/qmainwindow.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Frontend;


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
	//[ Protected virtual QPaintDevice functions              ]
	//[-------------------------------------------------------]
	protected:
		virtual QPaintEngine *paintEngine() const override;


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


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Frontend *m_pFrontendQt;			/**< Owner frontend implementation, always valid! */
		bool	  m_bVisible;				/**< Was the widget made visible? (independent of the real Qt widget visibility state) */
		int		  m_nWindowRedrawTimerID;	/**< Window redraw timer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_FRONTENDMAINWINDOW_H__
