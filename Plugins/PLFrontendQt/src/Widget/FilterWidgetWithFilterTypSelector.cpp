/*********************************************************\
 *  File: FilterWidgetWithFilterTypSelector.cpp          *
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
#include "PLFrontendQt/Widget/FilterWidgetWithFilterTypSelector.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QMenu>
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
