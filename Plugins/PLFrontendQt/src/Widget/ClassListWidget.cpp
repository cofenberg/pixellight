/*********************************************************\
 *  File: ClassListWidget.cpp                            *
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
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include "PLFrontendQt/DataModels/RTTIInfoModels/ClassListModel.h"
#include "PLFrontendQt/DataModels/RTTIInfoModels/ClassListSortAndFilterModel.h"
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/Widget/ClassListWidget.h"
#include "PLFrontendQt/External/filterwidget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendQt {
using namespace DataModels::RTTIInfoModels;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
ClassListWidget::ClassListWidget(ClassListType listType,QWidget *parent, Qt::WindowFlags f): QWidget(parent, f)
, m_bFirstLevelAlwaysExpanded(listType == HierachicalView)
{
	QBoxLayout *boxLayout = new QVBoxLayout;
	setLayout(boxLayout);

	FilterWidget *filterWidget = new FilterWidget(this, FilterWidget::LayoutAlignNone);
	filterWidget->setRefuseFocus(true);
	
	connect(filterWidget, SIGNAL(filterChanged(QString)),this, SLOT(filterChanged(QString)));
	
	boxLayout->addWidget(filterWidget);
	
	m_pClassListModel = new ClassListModel(listType == HierachicalView, this);
	
	// Setup the sort and filter proxy model
	// The filtering is case insensitive
	m_pSortAndFilterProxyModel = new ClassListSortAndFilterModel(this);
	m_pSortAndFilterProxyModel->setSourceModel(m_pClassListModel);
	m_pSortAndFilterProxyModel->setDynamicSortFilter(true);
	m_pSortAndFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	m_pSortAndFilterProxyModel->sort(0);
	
	m_pView = new QTreeView(this);
	m_pView->setModel(m_pSortAndFilterProxyModel);
	layout()->addWidget(m_pView);
	// Connect signal of QAbstractItemView directly to own signal, with this the class don't need to implement a slot to deliver the signal to the outside world.
	connect(m_pView, SIGNAL(activated(QModelIndex)), this, SIGNAL(activated(QModelIndex)));
	
	if(m_bFirstLevelAlwaysExpanded)
		m_pView->expandToDepth(0);
}

ClassListWidget:: ~ClassListWidget()
{
}

//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
ClassListWidget::ClassListWidget(const ClassListWidget &)
{
}

ClassListWidget &ClassListWidget::operator =(const ClassListWidget &)
{
	return *this;
}


//[-------------------------------------------------------]
//[ Private Qt slots (MOC)                                ]
//[-------------------------------------------------------]
void ClassListWidget::filterChanged(const QString &text)
{
	m_pSortAndFilterProxyModel->setFilterString(text);
	if(m_bFirstLevelAlwaysExpanded && m_pSortAndFilterProxyModel->hasChildren())
	{
		m_pView->expandToDepth(0);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
