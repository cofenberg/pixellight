/*********************************************************\
 *  File: RTTIBrowserWidget.h                            *
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


#ifndef __PLFRONTENDQT_RTTIBROWSERWIDGET_H__
#define __PLFRONTENDQT_RTTIBROWSERWIDGET_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtGui/QWidget>
#include "PLFrontendQt/PLFrontendQt.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
	class QTreeView;
	class QTabWidget;
	class QModelIndex;
	class QAbstractItemModel;
QT_END_NAMESPACE
namespace PLFrontendQt {
	class ClassListWidget;
	class ClassInfoWidget;
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
*    RTTI browser widget
*/
class PLFRONTENDQT_API RTTIBrowserWidget : public QWidget {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		explicit RTTIBrowserWidget(QWidget *parent = nullptr, Qt::WindowFlags f = 0);
		virtual ~RTTIBrowserWidget();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		void CreateTabView(const QString &tabName, ClassListWidget *widget);
		RTTIBrowserWidget(const RTTIBrowserWidget &);
		RTTIBrowserWidget &operator =(const RTTIBrowserWidget &);


	//[-------------------------------------------------------]
	//[ Private Qt slots (MOC)                                ]
	//[-------------------------------------------------------]
	private slots:
		void OnTreeItemActivated(const QModelIndex &index);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		ClassListWidget		*m_pModuleClassListWidget;
		ClassListWidget		*m_pHierarchicalClassListWidget;
		ClassInfoWidget		*m_pClassInfoWidget;
		QTabWidget			*m_ptabWidget;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_RTTIBROWSERWIDGET_H__
