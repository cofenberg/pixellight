/*********************************************************\
 *  File: FrontendMainWindow.cpp                         *
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
#include <QtCore/qcoreevent.h>
#include "PLFrontendQt/Frontend.h"
#include "PLFrontendQt/FrontendMainWindow.h"


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
FrontendMainWindow::FrontendMainWindow(Frontend &cFrontendQt) :
	m_pFrontendQt(&cFrontendQt),
	m_nWindowRedrawTimerID(startTimer(10))
{
}

/**
*  @brief
*    Destructor
*/
FrontendMainWindow::~FrontendMainWindow()
{
	// Stop window redraw timer
	if (m_nWindowRedrawTimerID) {
		killTimer(m_nWindowRedrawTimerID);
		m_nWindowRedrawTimerID = 0;
	}
}


//[-------------------------------------------------------]
//[ Protected virtual QObject functions                   ]
//[-------------------------------------------------------]
void FrontendMainWindow::timerEvent(QTimerEvent *pQTimerEvent)
{
	if (pQTimerEvent->timerId() == m_nWindowRedrawTimerID) {
		// [TODO] Update stuff
		m_pFrontendQt->OnDraw();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
