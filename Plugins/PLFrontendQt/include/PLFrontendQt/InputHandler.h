/*********************************************************\
 *  File: InputHandler.h                                 *
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


#ifndef __PLFRONTENDQT_INPUTHANDLER_H__
#define __PLFRONTENDQT_INPUTHANDLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLFrontendQt/PLFrontendQt.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class QKeyEvent;
class QMouseEvent;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Input handler interface
*/
class PLFRONTENDQT_API InputHandler {


	//[-------------------------------------------------------]
	//[ Public virtual InputHandler functions                 ]
	//[-------------------------------------------------------]
	public:
		virtual ~InputHandler() {}
		virtual void mousePressEvent(QMouseEvent*) = 0;
		virtual void mouseReleaseEvent(QMouseEvent*) = 0;
		virtual void mouseMoveEvent(QMouseEvent*) = 0;
		virtual void keyPressEvent(QKeyEvent*) = 0;
		virtual void keyReleaseEvent(QKeyEvent*) = 0;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_INPUTHANDLER_H__
