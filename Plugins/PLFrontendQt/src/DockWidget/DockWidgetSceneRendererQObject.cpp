/*********************************************************\
 *  File: DockWidgetSceneRendererQObject.cpp             *
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
#include <QtGui/qevent.h>
#include <QtGui/qdockwidget.h>
#include <PLCore/Base/Class.h>
#include <PLScene/Compositing/SceneRenderer.h>
#include <PLEngine/Application/EngineApplication.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DataModels/SceneRendererDataModel/SceneRendererDataModel.h"
#include "PLFrontendQt/DockWidget/DockWidgetSceneRenderer.h"
#include "PLFrontendQt/DockWidget/DockWidgetSceneRendererQObject.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DockWidgetSceneRendererQObject::DockWidgetSceneRendererQObject(DockWidgetSceneRenderer &cDockWidgetSceneRenderer) :
	m_pDockWidgetSceneRenderer(&cDockWidgetSceneRenderer)
{
}

/**
*  @brief
*    Destructor
*/
DockWidgetSceneRendererQObject::~DockWidgetSceneRendererQObject()
{
}


//[-------------------------------------------------------]
//[ Public virtual QObject methods                        ]
//[-------------------------------------------------------]
bool DockWidgetSceneRendererQObject::eventFilter(QObject *pQObject, QEvent *pQEvent)
{
	// Widget is shown (do only take it into account if there's a valid scene renderer model instance)
	DataModels::SceneRendererDataModel::SceneRendererDataModel *pSceneRendererDataModel = m_pDockWidgetSceneRenderer->m_pSceneRendererDataModel;
	if (pSceneRendererDataModel && pQEvent->type() == QEvent::Show) {
		// Get encapsulated Qt dock widget
		QDockWidget *pQDockWidget = m_pDockWidgetSceneRenderer->GetQDockWidget();
		if (pQObject == pQDockWidget) {
			// The encapsulated Qt dock widget is shown, ensure that we have a scene renderer
			if (!pSceneRendererDataModel->GetSceneRenderer()) {
				// Set a default scene renderer to have a decent standard behavior
				SceneRenderer *pSceneRenderer = nullptr;
				{
					CoreApplication *pApplication = CoreApplication::GetApplication();
					if (pApplication && pApplication->IsInstanceOf("PLEngine::EngineApplication"))
						pSceneRenderer = static_cast<PLEngine::EngineApplication*>(pApplication)->GetSceneRendererTool().GetSceneRenderer();
					m_pDockWidgetSceneRenderer->SelectSceneRenderer(pSceneRenderer);
				}

				// Set window title
				QString sQStringWindowTitle = pQDockWidget->tr(m_pDockWidgetSceneRenderer->GetClass()->GetProperties().Get("Title"));
				if (pSceneRenderer) {
					sQStringWindowTitle += ": ";
					sQStringWindowTitle += QtStringAdapter::PLToQt('\"' + pSceneRenderer->GetName() + '\"');	// Put it into quotes to make it possible to see e.g. trailing spaces
				}
				pQDockWidget->setWindowTitle(sQStringWindowTitle);
			}

			// We do not filter out the event because we add only additional handling
		}
	}

	// Pass the event on to the parent class
	return QObject::eventFilter(pQObject, pQEvent);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
