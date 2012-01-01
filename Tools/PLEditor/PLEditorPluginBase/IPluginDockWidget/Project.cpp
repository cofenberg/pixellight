/*********************************************************\
 *  File: Project.cpp                                  *
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
#include "IPluginDockWidget/Project.h"
#include <QDesktopServices>
#include <QUrl>

enum ActionIds {
	OpenWithSystemEditor,
};

//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEditorPluginBase {


//[-------------------------------------------------------]
//[ Public virtual PLEditor::IPluginDockWidget methods    ]
//[-------------------------------------------------------]
Project::EType Project::getType() const
{
	return TypeDockWidget;
}

QString Project::getName() const
{
	return "Project";
}

Qt::DockWidgetArea Project::InitialArea()
{
	return Qt::DockWidgetArea::BottomDockWidgetArea;
}

PLEditor::IPlugin* Project::Clone() const
{
	return new Project();
}

//[-------------------------------------------------------]
//[ Public methods                                        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
Project::Project()
{
	m_cTreeView.setModel(&m_cModel);
	m_cTreeView.setContextMenuPolicy(Qt::CustomContextMenu);
	this->setWidget(&m_cTreeView);
	
	setWindowTitle(getName());
	
	connect(&m_cTreeView, SIGNAL(customContextMenuRequested( const QPoint& )), SLOT(showContextMenu(const QPoint &)));
	
	QAction* pAction = m_cContextMenu.addAction("Open");
	pAction->setData((int)ActionIds::OpenWithSystemEditor);
}

/**
*  @brief
*    Destructor
*/
Project::~Project()
{
}

void Project::SetProjectDir(const QString strProjectDir)
{
	m_cModel.setRootPath(strProjectDir);
}

void Project::showContextMenu(const QPoint &point)
{
	QModelIndex index (m_cTreeView.indexAt(point));
	if (index.isValid()) {
		
		QAction *pAction = m_cContextMenu.exec(m_cTreeView.mapToGlobal(point));
		if (pAction)
		{
			ActionIds id = (ActionIds)pAction->data().toInt();
			if (id == ActionIds::OpenWithSystemEditor)
			{
				QUrl filePath (m_cModel.filePath(index));
				QDesktopServices::openUrl(filePath);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEditorPluginBase
