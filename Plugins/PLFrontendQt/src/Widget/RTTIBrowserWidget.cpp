/*********************************************************\
 *  File: RTTIBrowserWidget.cpp                          *
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
#include <QtGui/QSplitter>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include "PLFrontendQt/DataModels/RTTIInfoModels/ClassListModel.h"
#include "PLFrontendQt/Widget/ClassInfoWidget.h"
#include "PLFrontendQt/Widget/RTTIBrowserWidget.h"
#include "PLFrontendQt/Widget/ClassListWidget.h"
#include "PLFrontendQt/External/filterwidget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
using namespace DataModels::RTTIInfoModels;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
RTTIBrowserWidget::RTTIBrowserWidget(QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f)
{
	setLayout(new QVBoxLayout);

	QSplitter *splitter = new QSplitter(this);
	splitter->setOrientation(Qt::Horizontal);
	layout()->addWidget(splitter);
	

	m_ptabWidget = new QTabWidget(this);

	splitter->addWidget(m_ptabWidget);

	m_pModuleClassListWidget = new ClassListWidget(ClassListWidget::ModuleView, this);
	CreateTabView(tr("Module View"), m_pModuleClassListWidget);

	m_pHierarchicalClassListWidget = new ClassListWidget(ClassListWidget::HierachicalView, this);
	CreateTabView(tr("Class View"), m_pHierarchicalClassListWidget);

	m_pClassInfoWidget = new ClassInfoWidget(splitter);
	splitter->addWidget(m_pClassInfoWidget);
	m_pClassInfoWidget->setVisible(false);
}

RTTIBrowserWidget::~RTTIBrowserWidget()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
void RTTIBrowserWidget::CreateTabView(const QString &tabName, ClassListWidget *widget)
{
	m_ptabWidget->addTab(widget, tabName);
	connect(widget, SIGNAL(activated(const QModelIndex&)), this, SLOT(OnTreeItemActivated(const QModelIndex&)));
}

RTTIBrowserWidget::RTTIBrowserWidget(const RTTIBrowserWidget &)
{
}

RTTIBrowserWidget &RTTIBrowserWidget::operator =(const RTTIBrowserWidget &)
{
	return *this;
}


//[-------------------------------------------------------]
//[ Private Qt slots (MOC)                                ]
//[-------------------------------------------------------]
void RTTIBrowserWidget::OnTreeItemActivated(const QModelIndex &index)
{
	bool isModule = index.data(ClassListModel::ClassListItemType).toBool();
	m_pClassInfoWidget->setVisible(!isModule);
	if (!isModule)
		m_pClassInfoWidget->SetClassItem(index.data(ClassListModel::ClassListNameRole).toString());
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
