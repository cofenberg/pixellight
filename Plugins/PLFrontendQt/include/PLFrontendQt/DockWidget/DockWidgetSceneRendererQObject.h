/*********************************************************\
 *  File: DockWidgetSceneRendererQObject.h               *
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


#ifndef __PLFRONTENDQT_DOCKWIDGET_SCENERENDERER_QOBJECT_H__
#define __PLFRONTENDQT_DOCKWIDGET_SCENERENDERER_QOBJECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>	// For "override"
#include <QtCore/qobject.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class DockWidgetSceneRenderer;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene renderer Qt dock widget class, QObject instance for Qt's signal/slot mechanisms
*
*  @remarks
*    Sadly, it appears that Qt's signal/slot mechanisms can't be used without QObject/Q_OBJECT. But we don't want to do a multiple inheritance
*    like "class DockWidgetSceneRenderer : public QObject, public DockWidgetScene" either because this can cause serious casting issues.
*    So, we need to add another class just to be able to use Qt's signal/slot mechanisms. We can't use an embedded class for this either because
*    Qt's MOC doesn't like this. :/
*/
class DockWidgetSceneRendererQObject : public QObject {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class DockWidgetSceneRenderer;


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
		*  @param[in] cDockWidgetSceneRenderer
		*    Dock widget scene renderer owner instance
		*/
		DockWidgetSceneRendererQObject(DockWidgetSceneRenderer &cDockWidgetSceneRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~DockWidgetSceneRendererQObject();


	//[-------------------------------------------------------]
	//[ Public virtual QObject methods                        ]
	//[-------------------------------------------------------]
	public:
		virtual bool eventFilter(QObject *pQObject, QEvent *pQEvent) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		DockWidgetSceneRenderer *m_pDockWidgetSceneRenderer;	/**< Dock widget scene renderer owner instance, always valid */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_DOCKWIDGET_SCENERENDERER_QOBJECT_H__
