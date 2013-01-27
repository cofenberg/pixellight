/*********************************************************\
 *  File: FilterWidgetWithFilterTypSelector.cpp          *
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
#include "PLFrontendQt/Widget/FilterWidgetWithFilterTypSelector.h"
#include <QtGui/QHBoxLayout>
#include <QtGui/QToolButton>
#include <QtGui/QMenu>
#include "PLFrontendQt/External/filterwidget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
FilterWidgetWithFilterTypSelector::FilterWidgetWithFilterTypSelector(QWidget* parent): QWidget(parent)
{
	setLayout(new QHBoxLayout);
	m_pfilterToolButton = new QToolButton(this);
	m_pfilterToolButton->setToolTip(tr("Filter"));
	m_pfilterToolButton->setAutoRaise(true);
	m_pfilterToolButton->setIconSize(QSize(16,16));
	m_pfilterToolButton->setIcon(QIcon::fromTheme("view-filter", QIcon(":/stock_standard_filter")));
	m_pfilterToolButton->setPopupMode(QToolButton::InstantPopup);
	m_pfilterToolButton->setMenu(new QMenu(this));
	
	connect(m_pfilterToolButton->menu(), SIGNAL(triggered(QAction*)), this, SLOT(filterTypeTriggerd(QAction*)));
	
	layout()->addWidget(m_pfilterToolButton);
	
	FilterWidget *filterWidget = new FilterWidget(this, FilterWidget::LayoutAlignNone);
	filterWidget->setRefuseFocus(true);
	connect(filterWidget, SIGNAL(filterChanged(QString)), this, SIGNAL(filterChanged(QString)));
	layout()->addWidget(filterWidget);
	
	m_pActionGroup = new QActionGroup(this);
}

void FilterWidgetWithFilterTypSelector::AddFilterType(const QString& name, int filterId, bool initialChecked)
{
	QAction *action = m_pfilterToolButton->menu()->addAction(name);
	m_pActionGroup->addAction(action);
	action->setCheckable(true);
	action->setChecked(initialChecked);
	action->setData(filterId);
}

void FilterWidgetWithFilterTypSelector::filterTypeTriggerd(QAction * action)
{
	emit filterTypeChanged(action->data().toInt());
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
