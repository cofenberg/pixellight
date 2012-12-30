/*********************************************************\
 *  File: ClassInfoWidget.h                              *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
