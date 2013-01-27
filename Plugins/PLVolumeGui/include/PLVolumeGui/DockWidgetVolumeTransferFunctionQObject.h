/*********************************************************\
 *  File: DockWidgetVolumeTransferFunctionQObject.h      *
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


#ifndef __PLVOLUMEGUI_DOCKWIDGET_VOLUME_TRANSFERFUNCTION_QOBJECT_H__
#define __PLVOLUMEGUI_DOCKWIDGET_VOLUME_TRANSFERFUNCTION_QOBJECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>	// For "override"
#include <QtCore/qobject.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolumeGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class DockWidgetVolumeTransferFunction;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Volume transfer function Qt dock widget class, QObject instance for Qt's signal/slot mechanisms
*
*  @remarks
*    Sadly, it appears that Qt's signal/slot mechanisms can't be used without QObject/Q_OBJECT. But we don't want to do a multiple inheritance
*    like "class DockWidgetVolumeTransferFunction : public QObject, public DockWidgetVolume" either because this can cause serious casting issues.
*    So, we need to add another class just to be able to use Qt's signal/slot mechanisms. We can't use an embedded class for this either because
*    Qt's MOC doesn't like this. :/
*/
class DockWidgetVolumeTransferFunctionQObject : public QObject {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class DockWidgetVolumeTransferFunction;


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cDockWidgetVolumeTransferFunction
		*    Dock widget volume transfer function owner instance
		*/
		DockWidgetVolumeTransferFunctionQObject(DockWidgetVolumeTransferFunction &cDockWidgetVolumeTransferFunction);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~DockWidgetVolumeTransferFunctionQObject();


	//[-------------------------------------------------------]
	//[ Public virtual QObject methods                        ]
	//[-------------------------------------------------------]
	public:
		virtual bool eventFilter(QObject *pQObject, QEvent *pQEvent) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		DockWidgetVolumeTransferFunction *m_pDockWidgetVolumeTransferFunction;	/**< Dock widget volume transfer function owner instance, always valid */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeGui


#endif // __PLVOLUMEGUI_DOCKWIDGET_VOLUME_TRANSFERFUNCTION_QOBJECT_H__
