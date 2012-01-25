/*********************************************************\
 *  File: PLTreeItemsDelegate.h                          *
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


#ifndef __PLFRONTENDQT_PLTREEITEMSDELEGATE_H__
#define __PLFRONTENDQT_PLTREEITEMSDELEGATE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtGui/QStyledItemDelegate>
#include <PLCore/PLCore.h>	// Only needed for compilers which doesn't have nullptr as a builtin type
#include "PLFrontendQt/PLFrontendQt.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class QtColorButton;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Item delegate mainly for models useable which use internally PLDynVarTreeItems
*
*  @remarks
*    This item delegate adds additional (rudimentary) features when handling edits:
*    - Showing a color chooser button for RTTI members which represent a color
*    - Showing a spin edit box when floating point values should be edit with directly
*      setting the value to the RTTI member when changing the value in the edit control
*    - Showing a combobox for enum values
*/
class PLFRONTENDQT_API PLTreeItemsDelegate : public QStyledItemDelegate {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		explicit PLTreeItemsDelegate(QObject *parent = nullptr);
		QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

		void setEditorData(QWidget *ed, const QModelIndex &index) const;
		void setModelData(QWidget *ed, QAbstractItemModel *model, const QModelIndex &index) const;

		void updateEditorGeometry(QWidget *ed, const QStyleOptionViewItem &option, const QModelIndex &index) const;
		void paint(QPainter *painter, const QStyleOptionViewItem &opt, const QModelIndex &index) const;

		QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index)const;


	//[-------------------------------------------------------]
	//[ Private Qt slots (MOC)                                ]
	//[-------------------------------------------------------]
	private slots:
		void doubleSpinboxChanged(double);
		void currentComboboxIndexChanged(int);


};


/**
*  @brief
*    Color editor
*/
class ColorEditor : public QWidget {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Qt signals (MOC)                                      ]
	//[-------------------------------------------------------]
	signals:
		void changed(QWidget *widget);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		explicit ColorEditor(QWidget *parent = nullptr);

		void setColor(const QColor &color);
		QColor color() const;
		bool changed() const;


	//[-------------------------------------------------------]
	//[ Private Qt slots (MOC)                                ]
	//[-------------------------------------------------------]
	private slots:
		void colorChanged();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		QtColorButton *m_button;
		bool		   m_changed;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt


#endif // __PLFRONTENDQT_PLTREEITEMSDELEGATE_H__