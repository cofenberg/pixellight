/*********************************************************\
 *  File: QTableViewWithCopy.h                           *
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


#ifndef __PLFRONTENDQT_QTABLEVIEWWTHCOPY_H__
#define __PLFRONTENDQT_QTABLEVIEWWTHCOPY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4127)	// "warning C4127: conditional expression is constant"
	PL_WARNING_DISABLE(4251)	// "'QPainterPath::d_ptr' : class 'QScopedPointer<T,Cleanup>' needs to have dll-interface to be used by clients of class 'QPainterPath'"
	PL_WARNING_DISABLE(4800)	// "'const quint32' : forcing value to bool 'true' or 'false' (performance warning)"
	PL_WARNING_DISABLE(4512)	// "'QForeachContainer<T>' : assignment operator could not be generated with"
	PL_WARNING_DISABLE(4530)	// "C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	#include <QtGui/qtableview.h>
PL_WARNING_POP
#include "PLFrontendQt/PLFrontendQt.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    QTableView with support for copy
*/
class PLFRONTENDQT_API QTableViewWithCopy : public QTableView {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		QTableViewWithCopy();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~QTableViewWithCopy();


	//[-------------------------------------------------------]
	//[ Protected virtual QWidget functions                   ]
	//[-------------------------------------------------------]
	protected:
		virtual void keyPressEvent(QKeyEvent *) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_QTABLEVIEWWTHCOPY_H__
