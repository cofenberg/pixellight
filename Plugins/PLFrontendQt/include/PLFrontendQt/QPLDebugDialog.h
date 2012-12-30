/*********************************************************\
 *  File: QPLDebugDialog.h                               *
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
