/*********************************************************\
 *  File: QPLRenderWindow.h                              *
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


#ifndef __PLFRONTENDQT_QPLRENDERWINDOW_H__
#define __PLFRONTENDQT_QPLRENDERWINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtGui/QWidget>
#include <PLRenderer/Renderer/Types.h>
#include <PLRenderer/Renderer/SurfaceWindowHandler.h>
#include "PLFrontendQt/PLFrontendQt.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class SurfacePainter;
	class RendererContext;
}
namespace PLFrontendQt {
	class QPLContext;
	class InputHandler;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
class PLFRONTENDQT_API QPLRenderWindow : public QWidget, public PLRenderer::SurfaceWindowHandler {


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
		*  @param[in] parent
		*    parent widget of this widget
		*/
		QPLRenderWindow(QPLContext *pContext, const PLRenderer::DisplayMode *pDisplayMode = nullptr, QWidget *parent = nullptr);
		QPLRenderWindow(QWidget *parent = nullptr);
		void SetupWindow(QPLContext *pContext, const PLRenderer::DisplayMode *pDisplayMode = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~QPLRenderWindow();

		/**
		*  @brief
		*    Get SurfacePainter for this window
		*
		*  @return
		*    Pointer to surface painter of this window, can be a null pointer
		*/
		PLRenderer::SurfacePainter *GetPainter();

		QPLContext *GetContext();

		void SetInputHandler(InputHandler *pInputHandler);

		void ChangeContext(QPLContext *pNewContext);


	//[-------------------------------------------------------]
	//[ Protected virtual QObject functions                   ]
	//[-------------------------------------------------------]
	protected:
		virtual void timerEvent(QTimerEvent *pQTimerEvent) override;


	//[-------------------------------------------------------]
	//[ Protected virtual QPaintDevice functions              ]
	//[-------------------------------------------------------]
	protected:
		// [TODO]Bad idea to return here a nullptr under linux, with this set qt spams the stdout with a warning on each redraw:
		// QPainter::begin: Paint device returned engine == 0, type: 1
		// (the problem seems also only windows related and when aero is active)
		// see: http://stackoverflow.com/questions/1750011/opengl-window-cleared-with-no-wm-paint-message for possible, and better solution
		virtual QPaintEngine *paintEngine() const;


	//[-------------------------------------------------------]
	//[ Protected virtual QWidget functions                   ]
	//[-------------------------------------------------------]
	protected:
		virtual void paintEvent(QPaintEvent *) override;
		virtual void mousePressEvent(QMouseEvent* ) override;
		virtual void mouseReleaseEvent(QMouseEvent* ) override;
		virtual void mouseMoveEvent(QMouseEvent* ) override;
		virtual void keyPressEvent(QKeyEvent* ) override;
		virtual void keyReleaseEvent(QKeyEvent* ) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Set surface painter created by the QPLContext for this window
		*/
		void SetPainter();

		void InitWindow(const PLRenderer::DisplayMode *pDisplayMode);


	//[-------------------------------------------------------]
	//[ Private Qt slots (MOC)                                ]
	//[-------------------------------------------------------]
	private slots:
		void OnContextChanged();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		int						 m_nWindowRedrawTimerID;	/**< Window redraw timer */
		QPLContext				*m_pContext;
		PLRenderer::DisplayMode	 m_sDisplayMode;			/**< Display mode information */
		InputHandler			*m_pInputHandler;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_QPLRENDERWINDOW_H__
