/*********************************************************\
 *  File: SceneNodeInfoDelegate.cpp                      *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtGui/QHBoxLayout>
#include <QtGui/QApplication>
#include <QtGui/QDoubleSpinBox>
#include "PLFrontendQt/External/qtcolorbutton.h"
#include "PLFrontendQt/DataModels/SceneNodeInfoDelegate.h"


enum { ColorRole = 33 };


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


ColorEditor::ColorEditor(QWidget *parent) : QWidget(parent),
	m_button(new QtColorButton(this)),
	m_changed(false)
{
	QLayout *layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(m_button);
	connect(m_button, SIGNAL(colorChanged(QColor)), this, SLOT(colorChanged()));
	setFocusProxy(m_button);
}

void ColorEditor::setColor(const QColor &color)
{
	m_button->setColor(color);
	m_changed = false;
}

QColor ColorEditor::color() const
{
	return m_button->color();
}

void ColorEditor::colorChanged()
{
	m_changed = true;
	emit changed(this);
}

bool ColorEditor::changed() const
{
	return m_changed;
}

SceneNodeInfoDelegate::SceneNodeInfoDelegate(QObject *parent) : QStyledItemDelegate (parent)
{
}

QWidget *SceneNodeInfoDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QVariant dataVal = index.data(ColorRole);
	if (dataVal.userType() ==  QMetaType::QColor && index.column() == 1) {
		ColorEditor *editor = new ColorEditor(parent);
		connect(editor, SIGNAL(changed(QWidget*)), this, SIGNAL(commitData(QWidget*)));
		editor->setFocusPolicy(Qt::NoFocus);
		editor->installEventFilter(const_cast<SceneNodeInfoDelegate *>(this));
		return editor;
	} else {
		QWidget *editor = QStyledItemDelegate::createEditor(parent, option, index);

		dataVal = index.data(Qt::EditRole);
		if (dataVal.userType() ==  QMetaType::Double && index.column() == 1) {
			QDoubleSpinBox *spin = ((QDoubleSpinBox*)editor);
			connect(spin, (SIGNAL(valueChanged(double))), this, SLOT(doubleSpinboxChanged(double)));
			spin->setSingleStep(0.05);
		}
		return editor;
	}
}

void SceneNodeInfoDelegate::doubleSpinboxChanged(double)
{
	QDoubleSpinBox *editor = qobject_cast<QDoubleSpinBox *>(sender());
	commitData(editor);
}

void SceneNodeInfoDelegate::setEditorData(QWidget *ed, const QModelIndex &index) const
{
	QVariant dataVal = index.data(ColorRole);
	if (dataVal.userType() ==  QMetaType::QColor && index.column() == 1) {
		const QColor color = qVariantValue<QColor>(dataVal);
		ColorEditor *editor = static_cast<ColorEditor *>(ed);
		editor->setColor(color);
	} else {
		QStyledItemDelegate::setEditorData(ed, index);
	}
}

void SceneNodeInfoDelegate::setModelData(QWidget *ed, QAbstractItemModel *model, const QModelIndex &index) const
{
	QVariant dataVal = index.data(ColorRole);
	if (dataVal.userType() ==  QMetaType::QColor && index.column() == 1) {
		ColorEditor *editor = static_cast<ColorEditor*>(ed);
		if (editor->changed()) {
			QColor color = editor->color();
			model->setData(index, color, Qt::EditRole);
		}
	} else {
		QStyledItemDelegate::setModelData(ed, model, index);
	}
}

void SceneNodeInfoDelegate::updateEditorGeometry(QWidget *ed, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyledItemDelegate::updateEditorGeometry(ed, option, index);
	QVariant dataVal = index.data(ColorRole);
	if (dataVal.userType() ==  QMetaType::QColor && index.column() == 1)
		ed->setGeometry(ed->geometry().adjusted(5, 1, -5, -1));
}

void SceneNodeInfoDelegate::paint(QPainter *painter, const QStyleOptionViewItem &opt, const QModelIndex &index) const
{
	QStyleOptionViewItem option = opt;

	QStyledItemDelegate::paint(painter, option, index);

	QVariant dataVal = index.data(ColorRole);
	if (dataVal.userType() ==  QMetaType::QColor && index.column() == 1) {
		const QColor color = qVariantValue<QColor>(dataVal);
		painter->save();
		painter->setBrushOrigin(option.rect.x(), option.rect.y());
		int xOffset = 8;

		// [TODO]
		//painter->fillRect(QRect(option.rect.left()+xOffset, option.rect.top()+4, option.rect.width()-xOffset*2, option.rect.height()-8), color);

		painter->fillRect(option.rect.adjusted(8, 4, -8, -4), color);
		painter->restore();
	}
}

QSize SceneNodeInfoDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
	return QStyledItemDelegate::sizeHint(option, index) + QSize(0, 5);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
