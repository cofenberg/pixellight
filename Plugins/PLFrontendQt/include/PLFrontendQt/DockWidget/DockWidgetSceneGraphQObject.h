/*********************************************************\
 *  File: DockWidgetSceneGraphQObject.h                  *
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


#ifndef __PLFRONTENDQT_DOCKWIDGET_SCENEGRAPH_QOBJECT_H__
#define __PLFRONTENDQT_DOCKWIDGET_SCENEGRAPH_QOBJECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtCore/qobject.h>
#include "PLFrontendQt/Widget/SceneGraphMenu.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
	class QPoint;
	class QModelIndex;
QT_END_NAMESPACE
namespace PLFrontendQt {
	class DockWidgetSceneGraph;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene graph Qt dock widget class, QObject instance for Qt's signal/slot mechanisms
*
*  @remarks
*    Sadly, it appears that Qt's signal/slot mechanisms can't be used without QObject/Q_OBJECT. But we don't want to do a multiple inheritance
*    like "class DockWidgetSceneGraph : public QObject, public DockWidgetScene" either because this can cause serious casting issues. So, we
*    need to add another class just to be able to use Qt's signal/slot mechanisms. We can't use an embedded class for this either because
*    Qt's MOC doesn't like this. :/
*/
class DockWidgetSceneGraphQObject : public QObject {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class DockWidgetSceneGraph;


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Filter types
		*/
		enum EFilterTypes {
			BySceneNodeName,	/**< Filter by scene node name */
			ByClassName			/**< Filter by scene node class name */
		};


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cDockWidgetSceneGraph
		*    Dock widget scene graph owner instance
		*/
		DockWidgetSceneGraphQObject(DockWidgetSceneGraph &cDockWidgetSceneGraph);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~DockWidgetSceneGraphQObject();

		/**
		*  @brief
		*    Updates the scene graph tree view
		*
		*  @param[in] nAction
		*    Performed action
		*  @param[in] pCreatedObject
		*    The created object if reason is "SceneGraphMenu::ActionAdded", otherwise a null pointer
		*/
		void UpdateTreeView(SceneGraphMenu::EAction nAction, PLCore::Object *pCreatedObject);


	//[-------------------------------------------------------]
	//[ Private Qt slots (MOC)                                ]
	//[-------------------------------------------------------]
	private slots:
		void QtSlotTreeViewDoubleClicked(const QModelIndex &cQModelIndex);
		void QtSlotCustomContextMenuRequested(const QPoint &cQPoint);
		void QtSlotFilterTypeChanged(int filterId);
		void QtSlotFilterChanged(const QString &text);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		DockWidgetSceneGraph *m_pDockWidgetSceneGraph;	/**< Dock widget scene graph owner instance, always valid */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_DOCKWIDGET_SCENEGRAPH_QOBJECT_H__
