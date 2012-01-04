/*********************************************************\
 *  File: ClassInfoWidget.cpp                            *
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
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QFormLayout>
#include <QtGui/QSortFilterProxyModel>
#include <QtGui/QAbstractProxyModel>
#include <PLCore/Base/Class.h>
#include <PLCore/Base/ClassManager.h>
#include "PLFrontendQt/DataModels/RTTIInfoModels/ClassInfoModel.h"
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/Widget/ClassInfoWidget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendQt {
using namespace DataModels::RTTIInfoModels;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
ClassInfoWidget::ClassInfoWidget(QWidget *parent, Qt::WindowFlags f): QWidget(parent, f)
{
	QBoxLayout *boxLayout = new QVBoxLayout;
	setLayout(boxLayout);

	m_pInfoModel = new ClassInfoModel(this);

	m_pClassNameLabel = new QLabel(this);
	m_pClassNameLabel->setWordWrap(true);
	m_pClassNameLabel->setAlignment(Qt::AlignLeft| Qt::AlignTop);
	m_pDescriptionLabel = new QLabel(this);
	m_pDescriptionLabel->setWordWrap(true);
	m_pDescriptionLabel->setAlignment(Qt::AlignLeft| Qt::AlignTop);

	QGridLayout *gridLayout = new QGridLayout;
	boxLayout->addLayout(gridLayout);
	gridLayout->setHorizontalSpacing(10);

	QLabel *label = new QLabel(tr("Name:"));
	label->setAlignment(Qt::AlignLeft| Qt::AlignTop);
	gridLayout->addWidget(label, 0, 0);

	gridLayout->addWidget(m_pClassNameLabel, 0, 1);

	label = new QLabel(tr("Description:"));
	label->setAlignment(Qt::AlignLeft| Qt::AlignTop);
	gridLayout->addWidget(label, 1, 0);

	gridLayout->addWidget(m_pDescriptionLabel, 1, 1);
	gridLayout->setColumnStretch(1,1);

	m_pTabWidget = new QTabWidget(this);
	layout()->addWidget(m_pTabWidget);

	// Same order as described within the "PixelLightConventions"-document
	AddElementTab(ClassProperties, *m_pTabWidget);
	AddElementTab(ClassAttributes, *m_pTabWidget);
	AddElementTab(ClassConstructors, *m_pTabWidget);
	AddElementTab(ClassMethods, *m_pTabWidget);
	AddElementTab(ClassSignals, *m_pTabWidget);
	AddElementTab(ClassSlots, *m_pTabWidget);
}

ClassInfoWidget:: ~ClassInfoWidget()
{
}

void ClassInfoWidget::SetClassItem(const QString &className)
{
	const Class *pClass = ClassManager::GetInstance()->GetClass(QtStringAdapter::QtToPL(className));

	m_pInfoModel->SetClassItem(*pClass);

	m_pClassNameLabel->setText(className);
	m_pDescriptionLabel->setText(pClass ? QtStringAdapter::PLToQt(pClass->GetDescription()) : "");

	// Same order as described within the "PixelLightConventions"-document
	SetIndexForType(ClassProperties);
	SetIndexForType(ClassAttributes);
	SetIndexForType(ClassConstructors);
	SetIndexForType(ClassMethods);
	SetIndexForType(ClassSignals);
	SetIndexForType(ClassSlots);
}

ClassInfoWidget::ClassInfoWidget(const ClassInfoWidget &)
{
}

ClassInfoWidget &ClassInfoWidget::operator =(const ClassInfoWidget &)
{
	return *this;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
void ClassInfoWidget::AddElementTab(ClassElementTypes type, QTabWidget &tabWidget)
{
	if (!m_cClassElements.contains(type)) {
		QString tabName = GetTabTitleForType(type);
		
		if (tabName.length()) {
			QAbstractItemView *view = new QListView(&tabWidget);
			m_cClassElements.insert(type, view);
			
			QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
			proxyModel->setDynamicSortFilter(true);
			proxyModel->setSourceModel(m_pInfoModel);
			proxyModel->sort(0);
			view->setModel(proxyModel);
			tabWidget.addTab(view, tabName);
		}
	}
}

void ClassInfoWidget::SetIndexForType(ClassElementTypes type)
{
	if (m_cClassElements.contains(type)) {
		QModelIndex rootIndex;
		switch (type) {
			case ClassAttributes:
				rootIndex = m_pInfoModel->index(1, 0);
				break;

			case ClassSlots:
				rootIndex = m_pInfoModel->index(2, 0);
				break;

			case ClassSignals:
				rootIndex = m_pInfoModel->index(3, 0);
				break;

			case ClassProperties:
				rootIndex = m_pInfoModel->index(4, 0);
				break;

			case ClassConstructors:
				rootIndex = m_pInfoModel->index(5, 0);
				break;

			case ClassMethods:
				rootIndex = m_pInfoModel->index(6, 0);
				break;

			default:
				return;
		}
		const QModelIndex &childIndex =  rootIndex.child(0,0);
		QAbstractItemView *view = m_cClassElements[type];
		if (!childIndex.isValid())
			m_pTabWidget->removeTab(m_pTabWidget->indexOf(view));
		else {
			QAbstractProxyModel *proxyModel = static_cast<QAbstractProxyModel*>(view->model());
			view->setRootIndex(proxyModel->mapFromSource(rootIndex));
			m_pTabWidget->addTab(view, GetTabTitleForType(type));
		}
	}
}

QString ClassInfoWidget::GetTabTitleForType(ClassElementTypes type)
{
	QString tabName;
	switch (type) {
		case ClassAttributes:
			tabName = tr("Attributes");
			break;

		case ClassSlots:
			tabName = tr("Slots");
			break;

		case ClassSignals:
			tabName = tr("Signals");
			break;

		case ClassProperties:
			tabName = tr("Properties");
			break;

		case ClassConstructors:
			tabName = tr("Constructors");
			break;

		case ClassMethods:
			tabName = tr("Methods");
			break;
	}
	return tabName;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
