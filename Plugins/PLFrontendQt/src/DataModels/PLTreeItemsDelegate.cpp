/*********************************************************\
 *  File: PLTreeItemsDelegate.cpp                        *
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
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtGui/QHBoxLayout>
#include <QtGui/QApplication>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QComboBox>
#include "PLFrontendQt/External/qtcolorbutton.h"
#include "PLFrontendQt/DataModels/PLTreeItemsDelegate.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarTreeItemTypes.h"


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

PLTreeItemsDelegate::PLTreeItemsDelegate(QObject *parent) : QStyledItemDelegate (parent)
{
}

QWidget *PLTreeItemsDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QVariant dataVal = index.data(ColorRole);
	QVariant plTreeItemtype = index.data(PLDynVarTreeItemTypes::DynVarItemTypeRole);
	
	PLDynVarTreeItemTypes::DynVarTreeItemTypes dynVarType = plTreeItemtype.isValid() ? (PLDynVarTreeItemTypes::DynVarTreeItemTypes)plTreeItemtype.toInt() : PLDynVarTreeItemTypes::Unknown;
	
	if (dataVal.userType() ==  QMetaType::QColor && index.column() == 1) {
		ColorEditor *editor = new ColorEditor(parent);
		connect(editor, SIGNAL(changed(QWidget*)), this, SIGNAL(commitData(QWidget*)));
		editor->setFocusPolicy(Qt::NoFocus);
		editor->installEventFilter(const_cast<PLTreeItemsDelegate *>(this));
		return editor;
	} else if ( dynVarType == PLDynVarTreeItemTypes::Enum && index.column() == 1) {
		QMap<QString, QVariant> enumValues = index.data(PLDynVarTreeItemTypes::DynVarEnumValues).toMap();
		
		
		// Create the combobox and populate it
		QComboBox *cb = new QComboBox(parent);
		QMapIterator<QString, QVariant> iterator(enumValues);
		while (iterator.hasNext()) {
			iterator.next();
			QString sKey(iterator.key());
			QVariant cValue(iterator.value());
			cb->addItem(sKey, cValue);
		}
		connect(cb, (SIGNAL(currentIndexChanged(int))), this, SLOT(currentComboboxIndexChanged(int)));
		return cb;
	} else {
		if (index.column() != 1)
			return QStyledItemDelegate::createEditor(parent, option, index);
		
		dataVal = index.data(Qt::EditRole);
		
		QWidget *editor;
		
		if (dataVal.userType() == QMetaType::Float) {
			editor = new QDoubleSpinBox(parent);
		} else {
			editor = QStyledItemDelegate::createEditor(parent, option, index);
		}

		// int8 type
		if (dynVarType == PLDynVarTreeItemTypes::Int8) {
			QSpinBox *spin = ((QSpinBox*)editor);
			spin->setRange(-128, 127);
		} else if (dynVarType == PLDynVarTreeItemTypes::Int16) {
			QSpinBox *spin = ((QSpinBox*)editor);
			spin->setRange(-32768, 32767);
		} else if (dynVarType == PLDynVarTreeItemTypes::UInt8) {
			QSpinBox *spin = ((QSpinBox*)editor);
			spin->setRange(0, 255);
		} else if (dynVarType == PLDynVarTreeItemTypes::UInt16) {
			QSpinBox *spin = ((QSpinBox*)editor);
			spin->setRange(0, 65535);
		} else if (dynVarType == PLDynVarTreeItemTypes::Double || dynVarType == PLDynVarTreeItemTypes::Float)  {
			QDoubleSpinBox *spin = ((QDoubleSpinBox*)editor);
			connect(spin, (SIGNAL(valueChanged(double))), this, SLOT(doubleSpinboxChanged(double)));
			spin->setSingleStep(0.05);
		}
		return editor;
	}
}

void PLTreeItemsDelegate::doubleSpinboxChanged(double)
{
	QDoubleSpinBox *editor = qobject_cast<QDoubleSpinBox *>(sender());
	commitData(editor);
}

void PLTreeItemsDelegate::currentComboboxIndexChanged(int index)
{
	if (index == -1)
		return;
	
	QComboBox *editor = qobject_cast<QComboBox *>(sender());
	commitData(editor);
}

void PLTreeItemsDelegate::setEditorData(QWidget *ed, const QModelIndex &index) const
{
	QVariant dataVal = index.data(ColorRole);
	if (dataVal.userType() ==  QMetaType::QColor && index.column() == 1) {
		const QColor color = qVariantValue<QColor>(dataVal);
		ColorEditor *editor = static_cast<ColorEditor *>(ed);
		editor->setColor(color);
	} else if (QComboBox *cb = qobject_cast<QComboBox *>(ed)) {
		QString currentValue = index.data(Qt::DisplayRole).toString();
		cb->setCurrentIndex(cb->findText(currentValue));
	} else {
		QStyledItemDelegate::setEditorData(ed, index);
	}
}

void PLTreeItemsDelegate::setModelData(QWidget *ed, QAbstractItemModel *model, const QModelIndex &index) const
{
	QVariant dataVal = index.data(ColorRole);
	if (dataVal.userType() ==  QMetaType::QColor && index.column() == 1) {
		ColorEditor *editor = static_cast<ColorEditor*>(ed);
		if (editor->changed()) {
			QColor color = editor->color();
			model->setData(index, color, Qt::EditRole);
		}
	} else if(QComboBox *cb = qobject_cast<QComboBox *>(ed)) {
        // save the user data of the currentIndex of the combo box as the current value of the item
        model->setData(index, cb->itemData(cb->currentIndex()), Qt::EditRole);
	} else {
		QStyledItemDelegate::setModelData(ed, model, index);
	}
}

void PLTreeItemsDelegate::updateEditorGeometry(QWidget *ed, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyledItemDelegate::updateEditorGeometry(ed, option, index);
	QVariant dataVal = index.data(ColorRole);
	if (dataVal.userType() ==  QMetaType::QColor && index.column() == 1)
		ed->setGeometry(ed->geometry().adjusted(5, 1, -5, -1));
}

void PLTreeItemsDelegate::paint(QPainter *painter, const QStyleOptionViewItem &opt, const QModelIndex &index) const
{
	QStyleOptionViewItem option = opt;

	QStyledItemDelegate::paint(painter, option, index);

	QVariant dataVal = index.data(ColorRole);
	if (dataVal.userType() ==  QMetaType::QColor && index.column() == 1) {
		const QColor color = qVariantValue<QColor>(dataVal);
		painter->save();
		
		const int pixSize = 10;
		QBrush br(color);
		{
			QPixmap pm(2 * pixSize, 2 * pixSize);
			QPainter pmp(&pm);
			pmp.fillRect(0, 0, pixSize, pixSize, Qt::white);
			pmp.fillRect(pixSize, pixSize, pixSize, pixSize, Qt::white);
			pmp.fillRect(0, pixSize, pixSize, pixSize, Qt::black);
			pmp.fillRect(pixSize, 0, pixSize, pixSize, Qt::black);
			pmp.fillRect(0, 0, 2 * pixSize, 2 * pixSize, color);
			br = QBrush(pm);
		}
		
		painter->setBrushOrigin(option.rect.x(), option.rect.y());

		// [TODO]
		// int xOffset = 8;
		//painter->fillRect(QRect(option.rect.left()+xOffset, option.rect.top()+4, option.rect.width()-xOffset*2, option.rect.height()-8), color);

		painter->fillRect(option.rect.adjusted(8, 4, -8, -4), br);
		painter->restore();
	}
}

QSize PLTreeItemsDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
	return QStyledItemDelegate::sizeHint(option, index) + QSize(0, 5);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
