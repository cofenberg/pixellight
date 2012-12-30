/*********************************************************\
 *  File: ClassListWidget.cpp                            *
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
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include "PLFrontendQt/DataModels/RTTIInfoModels/ClassListModel.h"
#include "PLFrontendQt/DataModels/TreeSortAndFilterProxyModel.h"
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/Widget/ClassListWidget.h"
#include "PLFrontendQt/External/filterwidget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendQt {
using namespace DataModels;
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
	m_pSortAndFilterProxyModel = new TreeSortAndFilterProxyModel(this);
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
