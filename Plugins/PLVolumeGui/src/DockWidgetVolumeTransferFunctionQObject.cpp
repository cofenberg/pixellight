/*********************************************************\
 *  File: DockWidgetVolumeTransferFunctionQObject.cpp    *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLVolumeGui/DockWidgetVolumeTransferFunctionQObject.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolumeGui {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DockWidgetVolumeTransferFunctionQObject::DockWidgetVolumeTransferFunctionQObject(DockWidgetVolumeTransferFunction &cDockWidgetVolumeTransferFunction) :
	m_pDockWidgetVolumeTransferFunction(&cDockWidgetVolumeTransferFunction)
{
}

/**
*  @brief
*    Destructor
*/
DockWidgetVolumeTransferFunctionQObject::~DockWidgetVolumeTransferFunctionQObject()
{
}


//[-------------------------------------------------------]
//[ Public virtual QObject methods                        ]
//[-------------------------------------------------------]
bool DockWidgetVolumeTransferFunctionQObject::eventFilter(QObject *pQObject, QEvent *pQEvent)
{
	// Pass the event on to the parent class
	return QObject::eventFilter(pQObject, pQEvent);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeGui
