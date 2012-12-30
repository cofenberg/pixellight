/*********************************************************\
 *  File: QPLRenderWindow.h                              *
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


#ifndef __PLFRONTENDQT_QPLRENDERWINDOW_H__
#define __PLFRONTENDQT_QPLRENDERWINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/Types.h>
#include <PLRenderer/Renderer/SurfaceWindowHandler.h>
#include "PLFrontendQt/FrontendRenderWindow.h"


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
class PLFRONTENDQT_API QPLRenderWindow : public FrontendRenderWindow, public PLRenderer::SurfaceWindowHandler {


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
