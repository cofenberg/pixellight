/*********************************************************\
 *  File: ClassInfoWidget.h                              *
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


#ifndef __PLFRONTENDQT_CLASSINFOWIDGET_H__
#define __PLFRONTENDQT_CLASSINFOWIDGET_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtCore/QMap>
#include <QtGui/QWidget>
#include <PLCore/PLCore.h>	// Only needed for compilers which doesn't have nullptr as a builtin type


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
	class QLabel;
	class QTabWidget;
	class QAbstractItemView;
QT_END_NAMESPACE
namespace PLFrontendQt {
	namespace DataModels {
		namespace RTTIInfoModels {
			class ClassInfoModel;
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class information widget
*/
class ClassInfoWidget : public QWidget {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		explicit ClassInfoWidget(QWidget *parent = nullptr, Qt::WindowFlags f = 0);
		virtual ~ClassInfoWidget();
		void SetClassItem(const QString &className);


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		enum ClassElementTypes {
			ClassAttributes,
			ClassSlots,
			ClassSignals,
			ClassProperties,
			ClassConstructors,
			ClassMethods
		};


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		void AddElementTab(ClassElementTypes type, QTabWidget &tabWidget);
		void SetIndexForType(ClassElementTypes type);
		QString GetTabTitleForType(ClassElementTypes type);
		ClassInfoWidget(const ClassInfoWidget &);
		ClassInfoWidget &operator =(const ClassInfoWidget &);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		QLabel										*m_pClassNameLabel;
		QLabel										*m_pDescriptionLabel;
		QMap<int, QAbstractItemView*>				 m_cClassElements;
		DataModels::RTTIInfoModels::ClassInfoModel	*m_pInfoModel;
		QTabWidget									*m_pTabWidget;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_CLASSINFOWIDGET_H__
