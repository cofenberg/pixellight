/*********************************************************\
 *  File: RTTIBrowserWidget.h                            *
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
