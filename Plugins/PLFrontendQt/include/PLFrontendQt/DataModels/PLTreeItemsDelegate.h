/*********************************************************\
 *  File: PLTreeItemsDelegate.h                          *
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
