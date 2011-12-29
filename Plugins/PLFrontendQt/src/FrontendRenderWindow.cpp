/*********************************************************\
 *  File: FrontendRenderWindow.cpp                       *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLFrontendQt/FrontendRenderWindow.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FrontendRenderWindow::FrontendRenderWindow(QWidget *pParent) : QWidget(pParent, Qt::MSWindowsOwnDC)	// Same settings as used in Qt's QGLWidget
{
	// Disable window system background to avoid "white flickering" caused by automatic overdraw
	// (same settings as used in Qt's QGLWidget)
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);

	// Now, there's still "black flickering" - in order to get rid of this we're not using any built-in paint engines of Qt
	// -> Overwrite the "QPaintDevice::paintEngine()"-method and just return a null pointer
	// -> Set the following attribute
	setAttribute(Qt::WA_OpaquePaintEvent, true);

	// ... at this point, we should be finally flicker-free...
}

/**
*  @brief
*    Destructor
*/
FrontendRenderWindow::~FrontendRenderWindow()
{
}


//[-------------------------------------------------------]
//[ Protected virtual QPaintDevice functions              ]
//[-------------------------------------------------------]
QPaintEngine *FrontendRenderWindow::paintEngine() const
{
	#if defined(Q_WS_WIN)
		// We're not using any built-in paint engines of Qt ("flickering"-avoidance)
		return nullptr;
	#else
		// On Linux there's no "flickering"-issue and when returning a null pointer in here
		// "QPainter::begin: Paint device returned engine == 0, type: 1" will be written
		// into the console - all the time.

		// Call base implementation
		return QWidget::paintEngine();
	#endif
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
