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
#include <QtGui/QTreeView>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QSortFilterProxyModel>
#include "PLFrontendQt/DataModels/RTTIInfoModels/ClassListModel.h"
#include "PLFrontendQt/Widget/ClassInfoWidget.h"
#include "PLFrontendQt/Widget/RTTIBrowserWidget.h"


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

	m_pModuleClassListModel = new ClassListModel(false, this);
	CreateTabView(tr("Module View"), m_pModuleClassListModel);

	m_pHierarchicalClassListModel = new ClassListModel(true, this);
	CreateTabView(tr("Class View"), m_pHierarchicalClassListModel)->expandToDepth(0);	// Everything is derived from "PLCore::Object", expand this level by default

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
QTreeView *RTTIBrowserWidget::CreateTabView(const QString &tabName, QAbstractItemModel *model)
{
	QTreeView *tree = new QTreeView(this);
	QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setDynamicSortFilter(true);
	proxyModel->setSourceModel(model);
	proxyModel->sort(0);
	tree->setModel(proxyModel);
	tree->setModel(proxyModel);
	m_ptabWidget->addTab(tree, tabName);
	connect(tree, SIGNAL(activated(const QModelIndex&)), this, SLOT(OnTreeItemActivated(const QModelIndex&)));
	return tree;
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
		m_pClassInfoWidget->SetClassItem(index.data(ClassListModel::ClassNameRole).toString());
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
