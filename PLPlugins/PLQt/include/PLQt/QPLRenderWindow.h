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


#ifndef __PLQT_QPLRENDERWINDOW_H__
#define __PLQT_QPLRENDERWINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtGui/QWidget>
#include <PLRenderer/Renderer/Types.h>
#include <PLRenderer/Renderer/SurfaceWindowHandler.h>
#include "PLQt/PLQt.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class SurfacePainter;
	class RendererContext;
}
namespace PLQt {
	class QPLContext;
	class InputHandler;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
class PLQT_API QPLRenderWindow : public QWidget, public PLRenderer::SurfaceWindowHandler {


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
		QPLRenderWindow(QPLContext *pContext, bool updateContext = true, const PLRenderer::DisplayMode *pDisplayMode = nullptr, QWidget *parent = nullptr);
		QPLRenderWindow(QWidget *parent = nullptr);
		void SetupWindow(QPLContext *pContext, bool updateContext = true, const PLRenderer::DisplayMode *pDisplayMode = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~QPLRenderWindow();

		/**
		*  @brief
		*    Let PL draw one frame
		*/
		void Update();

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
	//[ Protected virtual QWidget functions                   ]
	//[-------------------------------------------------------]
	protected:
		virtual void paintEvent(QPaintEvent *);
		virtual void resizeEvent(QResizeEvent *);
		virtual void showEvent(QShowEvent *);
		virtual void mousePressEvent(QMouseEvent* );
		virtual void mouseReleaseEvent(QMouseEvent* );
		virtual void mouseMoveEvent(QMouseEvent* );
		virtual void keyPressEvent(QKeyEvent* );
		virtual void keyReleaseEvent(QKeyEvent* );


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
		QPLContext				*m_pContext;
		PLRenderer::DisplayMode	 m_sDisplayMode;	/**< Display mode information */
		bool					 m_bUpdateContext;
		InputHandler			*m_pInputHandler;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLQt


#endif // __PLQT_QPLRENDERWINDOW_H__
