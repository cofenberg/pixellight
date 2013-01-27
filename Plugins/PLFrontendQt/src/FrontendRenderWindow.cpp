/*********************************************************\
 *  File: FrontendRenderWindow.cpp                       *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
