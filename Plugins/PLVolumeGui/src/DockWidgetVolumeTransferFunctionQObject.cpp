/*********************************************************\
 *  File: DockWidgetVolumeTransferFunctionQObject.cpp    *
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
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
