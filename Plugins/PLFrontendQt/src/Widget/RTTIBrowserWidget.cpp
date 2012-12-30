/*********************************************************\
 *  File: RTTIBrowserWidget.cpp                          *
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
