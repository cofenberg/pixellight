/*********************************************************\
 *  File: QPLDebugDialog.h                               *
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


#ifndef __PLFRONTENDQT_QPLDEBUGDIALOG_H__
#define __PLFRONTENDQT_QPLDEBUGDIALOG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtCore/QModelIndex>
#include <QtGui/QWidget>
#include <PLCore/Base/Event/EventHandler.h>
#include "PLFrontendQt/PLFrontendQt.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace Ui {
	class DebugView;
}
namespace PLFrontendQt {
	class QPLSceneContext;
	namespace DataModels {
		class SceneGraphTreeModel;
		class SceneNodeInfoModel;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
class PLFRONTENDQT_API QPLDebugDialog : public QWidget {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		explicit QPLDebugDialog(QWidget *parent = nullptr, Qt::WindowFlags f = 0);
		
		/**
		*  @brief
		*    Set scene context for which the information should be shown
		*
		*  @param[in] context
		*    the scene context to be used
		* 
		*  @param[in] hideSceneStartNode
		*    specifies if the start node of the scene should be hidden
		*/
		
		void SetContext(QPLSceneContext *context, bool hideSceneStartNode = false);


	//[-------------------------------------------------------]
	//[ Public Qt slots (MOC)                                 ]
	//[-------------------------------------------------------]
	public slots:
		void OnSceneContextUpdate();


	//[-------------------------------------------------------]
	//[ Private Qt slots (MOC)                                ]
	//[-------------------------------------------------------]
	private slots:
		void on_sceneTree_activated(QModelIndex index);
		void onSceneChanged();
		void onBeginSceneChanged();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		QPLSceneContext					*m_context;
		Ui::DebugView					*ui;
		DataModels::SceneGraphTreeModel	*graphModel;
		DataModels::SceneNodeInfoModel	*nodeInfoModel;
		PLCore::EventHandler<>			 EventHandlerSceneContextUpdate;
		bool							 m_hideSceneStartNode;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_QPLDEBUGDIALOG_H__
